#include "NtupleLocations.h"
#include <TTree.h>
#include <TFile.h>

#include <iostream>
using namespace std;

class EgRegAnalyzer
{
public:
 TString fileLoc;
 TString fileLocFriend;
 TString treeName = "egRegTree";
 TString treeNameFriend = "egRegTreeFriend";

 TTree*tree;//input trees
 TTree*treeFriend;//result trees
 TFile*file;
 TFile*fileFriend;

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

 //-----Parameters-----//
 float nentries;
 float eleE;
 float mcE;
 float scE;
 float eta;
 float trkP;
 float trkPErr;
 float pt;
 float mean;
 float realSigma;
 float regIdealMean;
 float regRealSigma;

 //-----Constructor-----//
 EgRegAnalyzer(TString step){
  if     (step=="step1"){
   fileLocFriend = baseResultsEle+step1;
   fileLoc = baseInputsEle+idealIC;
  }
  else if(step=="step2"){
   fileLocFriend = baseResultsEle+step2;
   fileLoc = fileLocFriend;
  }
  else if(step=="step3"){
   fileLocFriend = baseResultsEle+step3;
   fileLoc = fileLocFriend;
  }
  else if(step=="step4"){
   fileLocFriend = baseResultsEle+step4;
   fileLoc = baseInputsEle+realIC;
  }
  else {
   cout << "ERROR: No step settings!!!" << endl;
  }

  LoadTree(fileLoc,fileLocFriend,treeName,treeNameFriend,step);
  TurnOnBranches(step);
 };

 //-----Load trees-----//
 void LoadTree(TString fileLoc,TString fileLocFriend,TString treeName,TString treeNameFriend,TString step){
  cout << "--------------------------------" << endl;
  cout << "Loading file: " << fileLoc << endl;
  cout << "Loading tree: " << treeName << endl;
  TFile*file = new TFile(fileLoc);
  tree = (TTree*)file->Get(treeName);
  cout << "Loading file: " << fileLocFriend << endl;
  cout << "Loading tree: " << treeNameFriend << endl;
  if(step=="step1"||step=="step4"){
   fileFriend = new TFile(fileLocFriend);
   treeFriend = (TTree*)fileFriend->Get(treeNameFriend);
  }
  else treeFriend = (TTree*)file->Get(treeNameFriend);
  tree->AddFriend(treeFriend);
  cout << "--------------------------------" << endl;
 };

 //-----Initialize branches in tree-----//
 void TurnOnBranches(TString step){
  TBranch*b_ele;
  TBranch*b_mc;
  TBranch*b_mean;
  TBranch*b_sc;
  TBranch*b_regIdealMean;
  TBranch*b_regRealSigma;

  tree->SetBranchAddress("ele",&eleObject,&b_ele);
  tree->SetBranchAddress("mc",&mcObject,&b_mc);
  tree->SetBranchAddress("mean",&mean,&b_mean);
  tree->SetBranchAddress("sc",&scObject,&b_sc);
  if(step=="step2"||step=="step3"){
   tree->SetBranchAddress("regIdealMean",&regIdealMean,&b_regIdealMean);
  }
  if(step=="step3"){
   tree->SetBranchAddress("regRealSigma",&regRealSigma,&b_regRealSigma);
  }
 }

 //-----Get number of entries in tree-----//
 Long64_t GetNEntries(){
  return tree->GetEntries();
 }

 //-----Get value of parameters for event-----//
 void GetParameters(float &eleE,float &mcE,float &scE,float &pt,float &eta,float &corr,float &realSigma,TString step){
  eleE = eleObject.energy;
  mcE = mcObject.energy;
  pt = mcObject.pt;
  scE = scObject.rawEnergy + scObject.rawESEnergy;
  eta = mcObject.eta;
  if(step=="step2"||step=="step3") corr = regIdealMean;
  else corr = mean;
  trkP = eleObject.trkPMode;
  trkPErr = eleObject.trkPModeErr;
  realSigma = regRealSigma;
 }

 //---Get value of eReg-----//
 float GetEReg(TString step){
  float eleE = eleObject.energy;
  float mcE = mcObject.energy;
  float pt = mcObject.pt;
  float scE = scObject.rawEnergy + scObject.rawESEnergy;
  float eta = mcObject.eta;
  float trkP = eleObject.trkPMode;
  float trkPErr = eleObject.trkPModeErr;
  float eReg;

  if(step=="step2"||step=="step3") 
   eReg = regIdealMean*scE;
  else if(step=="step1")
   eReg = mean*scE;
  else if(step=="step4")
   eReg = mean*eleE;
  else eReg = -1000;
  return eReg;
 }

 //-----Get entry from tree-----//
 Long64_t GetEgEntry(Long64_t i){
  return tree->GetEntry(i);
 }
};//end class

