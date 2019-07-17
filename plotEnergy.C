#include "Functions.h"
#include "NtupleLocations.h"

void getParameters(double &mcE,double &scE,double &eleE,double &pt,double &eta);

//-----Set step to study and ideal or real ICs-----//
const TString step = "step1";
const TString stepLoc = step1;
const TString inputIC = "idealIC";
const TString inputICLoc = idealIC;

const TString fileLoc = baseInputsEle+inputICLoc;
const TString fileLocFriend = baseResultsEle+stepLoc;

const TString treeName = "egRegTree";
const TString treeNameFriend = "egRegTreeFriend";
float mean;

const int energyBinLow = 0;
const int energyBinHigh = 3750;
const int nBinsEnergy = 100;
 struct EleStruct {
  float et,energy,energyErr,ecalEnergy,ecalEnergyErr,eta,phi,trkEtaMode,trkPhiMode,trkPMode,
  trkPModeErr,fbrem,corrMean,corrSigma,hademTow,hademCone,trkPInn,trkPtInn,trkPVtx,trkPOut,
  trkChi2,trkNDof,ecalDrivenSeed,nrSatCrys,scRawEnergy,scRawESEnergy;
 };

 struct SCStruct {
 float rawEnergy,rawESEnergy,etaWidth,phiWidth,seedClusEnergy,numberOfClusters,
  numberOfSubClusters,clusterMaxDR,clusterMaxDRDPhi,clusterMaxDRDEta,clusterMaxDRRawEnergy,
  corrEnergy,scEta,scPhi,seedEta,seedPhi,dEtaSeedSC,dPhiSeedSC,isEB,iEtaOrX,iPhiOrY,iEtaMod5,
  iPhiMod2,iEtaMod20,iPhiMod20,etaGapCode,phiGapCode,nearbyChanStatus,corrEnergyAlt,
  rawEnergyAlt,nrClusAlt,scSinTheta,seedSinTheta;
 };

 struct MCStruct {
  float energy,pt,eta,phi,pdgId,status,dR;
 };
 
 EleStruct eleObject;
 SCStruct scObject;
 MCStruct  mcObject;

void plotEnergy()
{
 gStyle->SetOptStat(0);
 gStyle->SetPalette(1);

 //-----Load trees-----//
 cout << "Loading file: " << fileLoc << endl;
 cout << "Loading tree: " << treeName << endl;
 TFile*file = new TFile(fileLoc);
 TTree*tree = (TTree*)file->Get(treeName);

 cout << "Loading file: " << fileLocFriend << endl;
 cout << "Loading tree: " << treeNameFriend << endl;
 TFile*fileFriend = new TFile(fileLocFriend);
 TTree*treeFriend = (TTree*)fileFriend->Get(treeNameFriend);

 tree->AddFriend(treeFriend);
 cout << endl;


 //-----Define branches-----//
 TBranch*b_ele;
 TBranch*b_mc;
 TBranch*b_mean;
 TBranch*b_sc;

 //-----Set branch addresses-----//
 tree->SetBranchAddress("ele",&eleObject,&b_ele);
 tree->SetBranchAddress("mc",&mcObject,&b_mc);
 tree->SetBranchAddress("mean",&mean,&b_mean);
 tree->SetBranchAddress("sc",&scObject,&b_sc);
 
 //-----Define histograms-----//
 const int n = 3;
 double ptBreak1 = 100; 
 double ptBreak2 = 200;
 TH2D*hERatioVsEta[n];
 TProfile*hERatioProfile[n];
 double eReg,eRes,eDiff,eTrueRawRatio,eCorrTrueRatio,eSCeleRatio;
 Long64_t nentries = tree->GetEntries();

 TString eRatioVsEtaTitle[n] = {
  "Corrected energy/True energy: p_{T} < 100",
  "Corrected energy/True energy: 100 < p_{T} < 200",
  "Corrected energy/True energy: 200 < p_{T}"
 };

 TString eRatioVsEtaName[n] = {
  "eRatioEta_0pT100"+step+"_"+inputIC,
  "eRatioEta_100pT200"+step+"_"+inputIC,
  "eRatioEta_200pTAndUp"+step+"_"+inputIC,
 };

 for(int j=0;j<n;j++){
  hERatioVsEta[j] = new TH2D(eRatioVsEtaName[j],"",100,-3.5,3.5,100,0,5);
  hERatioVsEta[j]->GetYaxis()->SetTitle("E_{corr}/E_{True}");
  hERatioVsEta[j]->GetXaxis()->SetTitle("#eta");
 }

 double mcE,scE,eleE,pt,eta;
 //-----Loop over events in tree-----//
 for(Long64_t i=0;i<nentries;i++){
  counter(i,nentries,"plotEgamma");

  //-----Get entry from tree-----//
  tree->GetEntry(i);
  getParameters(mcE,scE,eleE,pt,eta);

  if(step=="step1"||step=="step2"){
   eReg = scE*mean;
   eDiff = mcE-eReg;
  } 
  else eReg = 0;
  
  eTrueRawRatio = mcE/scE;
  eCorrTrueRatio = eReg/mcE;

  if(pt<ptBreak1) hERatioVsEta[0]->Fill(eta,eCorrTrueRatio);
  else if(pt>ptBreak1 && pt<ptBreak2) 
   hERatioVsEta[1]->Fill(eta,eCorrTrueRatio);
  else hERatioVsEta[2]->Fill(eta,eCorrTrueRatio);
 }

 //-----Make plots-----//
 for(int i=0;i<n;i++){
  TString profileName = eRatioVsEtaName[i];
  profileName += "Prof";
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
 profDraw(hERatioProfile[0],hERatioProfile[1],hERatioProfile[2]);

 //-----Save histograms-----//
 TFile*saveFile = new TFile("save.root","RECREATE");
 for(int i=0;i<n;i++){
  hERatioProfile[i]->Write();
  hERatioVsEta[i]->Write();
 }

 saveFile->Close();
}//end plotEnergy

void getParameters(double &mcE,double &scE,double &eleE,double &pt,double &eta){
 mcE = mcObject.energy;
 scE = scObject.rawEnergy+scObject.rawESEnergy;
 eleE = eleObject.energy;
 pt = mcObject.pt;
 eta = mcObject.eta;
}
