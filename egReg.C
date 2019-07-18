#include "./headers/EgRegAnalyzer.h"
#include "./headers/Functions.h"

enum Step {
 STEP1,
 STEP2,
 STEP3,
 STEP4
};

void egReg()
{
 //-----Select step to investigate-----//
 Step nStep = STEP3;

 TString step;
 TString inputIC;

 if(nStep == STEP1){
  step = "step1";
  inputIC = "idealIC";
 }
 else if(nStep == STEP2){
  step = "step2";
  inputIC = "realIC";
 }
 else if(nStep == STEP3){
  step = "step3";
  inputIC = "realIC";
 }
 else if(nStep == STEP4){
  step = "step4";
  inputIC = "realIC";
 }
 else {
  cout << "No step selected!!!" << endl;
  return;
 }

 //-----Initialize EgRegAnalyzaer Class-----//
 EgRegAnalyzer*egamma = new EgRegAnalyzer(step,inputIC);

 gStyle->SetOptStat(0);
 gStyle->SetPalette(1);
 //-----Define pt ranges for histograms-----//
 const int n = 3;
 double ptBreak1 = 100;
 double ptBreak2 = 200;
 TH2D*hERatioVsEta[n];
 TProfile*hERatioProfile[n];

 //-----Define titles and names for histograms-----//
 TString eRatioVsEtaTitle[n] = {
  "Corrected energy/True energy: p_{T} < 100",
  "Corrected energy/True energy: 100 < p_{T} < 200",
  "Corrected energy/True energy: 200 < p_{T}"
 };
 TString eRatioVsEtaName[n] = {
  "eRatioEta_0pT100_"+step+"_"+inputIC,
  "eRatioEta_100pT200_"+step+"_"+inputIC,
  "eRatioEta_200pTAndUp_"+step+"_"+inputIC,
 };
 TString profName = "eRatioEta_profile_"+step+inputIC;

 //-----Initialize histograms-----//
 for(int j=0;j<n;j++){
  hERatioVsEta[j] = new TH2D(eRatioVsEtaName[j],"",100,-3.5,3.5,100,0,5);
  hERatioVsEta[j]->GetYaxis()->SetTitle("E_{corr}/E_{True}");
  hERatioVsEta[j]->GetXaxis()->SetTitle("#eta");
 }

 float mcE,scE,eleE,pt,eta,corr,regIdealMean;
 float eReg,eRes,eDiff,eTrueRawRatio,eCorrTrueRatio,eSCeleRatio;
 Long64_t nentries = egamma->GetNEntries();

 //-----Begin loop over events-----//
 for(Long64_t i=0;i<nentries;i++){
  counter(i,nentries,"plotEgamma");
  egamma->GetEgEntry(i);
  egamma->GetParameters(mcE,scE,eleE,pt,eta,corr,step);
 
  if(step=="step1"||step=="step3"){
   eReg = scE*corr;
  }
  else if(step=="step4"){
   eReg = eleE*corr;
  }
  else if(step=="step2"){
   eReg = 0;
  }
  eDiff = mcE-eReg;
  eTrueRawRatio = mcE/scE;
  eCorrTrueRatio = eReg/mcE;

  if(pt<ptBreak1) hERatioVsEta[0]->Fill(eta,eCorrTrueRatio);
  else if(pt>ptBreak1 && pt<ptBreak2)
   hERatioVsEta[1]->Fill(eta,eCorrTrueRatio);
  else hERatioVsEta[2]->Fill(eta,eCorrTrueRatio);
 }

 for(int i=0;i<n;i++){
  hERatioProfile[i] = (TProfile*)hERatioVsEta[i]->ProfileX();
  hERatioProfile[i]->SetMarkerStyle(20);
  if(i==0){
   hERatioProfile[0]->SetMarkerColor(kRed+2);
   hERatioProfile[0]->SetLineColor(kRed+2);
  }
  else if(i==1){
   hERatioProfile[i]->SetMarkerColor(kBlue+1);
   hERatioProfile[i]->SetLineColor(kBlue+1);
  }
  else if(i==2){
   hERatioProfile[i]->SetMarkerColor(kGreen+2);
   hERatioProfile[i]->SetLineColor(kGreen+2);
  }
  histDraw2D(hERatioVsEta[i],eRatioVsEtaName[i],eRatioVsEtaTitle[i],false,false,true);
 }
 profDraw(profName,hERatioProfile[0],hERatioProfile[1],hERatioProfile[2]);

 TFile*saveFile = new TFile("save.root","RECREATE");
 for(int i=0;i<n;i++){
  hERatioProfile[i]->Write();
  hERatioVsEta[i]->Write();
 }

 saveFile->Close();
}
