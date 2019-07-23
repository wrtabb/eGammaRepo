#include "./headers/EgRegAnalyzer.h"
#include "./headers/Functions.h"

void plotEReg(TString step);

void egReg()
{
 for(int i=0;i<4;i++){
  if(i==1) continue;//not plotting step2
  cout << endl;
  cout << "********************" << endl;
  cout << "* Processing step" << i+1 << " *" << endl;
  cout << "********************" << endl;
  cout << endl;
  TString step = "step";
  step += i+1;
  plotEReg(step);
 }
}

void plotEReg(TString step){
 //-----Initialize EgRegAnalyzaer Class-----//
 EgRegAnalyzer*egamma = new EgRegAnalyzer(step);

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
  "eRatioEta_0pT100_"+step,
  "eRatioEta_100pT200_"+step,
  "eRatioEta_200pTAndUp_"+step
 };
 TString profName = "eRatioEta_profile_"+step;

 //-----Initialize histograms-----//
 for(int j=0;j<n;j++){
  hERatioVsEta[j] = new TH2D(eRatioVsEtaName[j],"",100,-3.5,3.5,100,0,5);
  hERatioVsEta[j]->GetYaxis()->SetTitle("E_{corr}/E_{True}");
  hERatioVsEta[j]->GetXaxis()->SetTitle("#eta");
 }
 float mcE,scE,eleE,pt,eta,corr,realSigma,trkP,trkPErr;
 float eReg,eRes,eDiff,eTrueRawRatio,eCorrTrueRatio,eSCeleRatio;
 Long64_t nentries = egamma->GetNEntries();

 //-----Begin loop over events-----//
 for(Long64_t i=0;i<nentries;i++){
  counter(i,nentries,step);
  egamma->GetEgEntry(i);
  egamma->GetParameters(mcE,scE,eleE,pt,eta,corr,realSigma,step);
  eReg = egamma->GetEReg(step); 
  eCorrTrueRatio = eReg/mcE;

  if(pt<ptBreak1) hERatioVsEta[0]->Fill(eta,eCorrTrueRatio);
  else if(pt>ptBreak1 && pt<ptBreak2)
   hERatioVsEta[1]->Fill(eta,eCorrTrueRatio);
  else hERatioVsEta[2]->Fill(eta,eCorrTrueRatio);
 }

 for(int i=0;i<n;i++){
  hERatioProfile[i] = (TProfile*)hERatioVsEta[i]->ProfileX();
  hERatioProfile[i]->SetMarkerStyle(20);
  hERatioProfile[i]->GetYaxis()->SetTitle("E_{corr}/E_{true}");
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
 egamma->DeleteTree();
}
