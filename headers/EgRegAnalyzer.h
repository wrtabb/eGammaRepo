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

 TTree*tree;
 TTree*treeFriend;
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

 float nentries;
 float eleE;
 float mcE;
 float pt;
 float mean;
 float scE;
 float eta;

EgRegAnalyzer(TString step,TString inputIC){
 if     (step=="step1") fileLocFriend = baseResultsEle+step1;
 else if(step=="step2") fileLocFriend = baseResultsEle+step2;
 else if(step=="step3") fileLocFriend = baseResultsEle+step3;
 else if(step=="step4") fileLocFriend = baseResultsEle+step4;
 else {
  cout << "ERROR: No step settings!!!" << endl;
 }

 if    (inputIC=="idealIC") fileLoc = baseInputsEle+idealIC;
 else if(inputIC=="realIC") fileLoc = baseInputsEle+realIC;
 else {
  cout << "ERROR: no input settings!!!" << endl;
 }

 cout << "--------------------------------" << endl;
 cout << "Loading files: " << endl;
 cout << fileLoc << endl;
 cout << fileLocFriend << endl;
 
 file = new TFile(fileLoc);
 fileFriend = new TFile(fileLocFriend);
 tree = (TTree*)file->Get(treeName); 
 treeFriend = (TTree*)fileFriend->Get(treeNameFriend);
 LoadTree(fileLoc,fileLocFriend,treeName,treeNameFriend);
};

void LoadTree(TString fileLoc,TString fileLocFriend,TString treeName,TString treeNameFriend){
 cout << "Loading file: " << fileLoc << endl;
 cout << "Loading tree: " << treeName << endl;
 TFile*file = new TFile(fileLoc);
 tree = (TTree*)file->Get(treeName);
 cout << "Loading file: " << fileLocFriend << endl;
 cout << "Loading tree: " << treeNameFriend << endl;
 fileFriend = new TFile(fileLocFriend);
 treeFriend = (TTree*)fileFriend->Get(treeNameFriend);

 tree->AddFriend(treeFriend);
 cout << endl;
};

void TurnOnBranches(){
 TBranch*b_ele;
 TBranch*b_mc;
 TBranch*b_mean;
 TBranch*b_sc;

 tree->SetBranchAddress("ele",&eleObject,&b_ele);
 tree->SetBranchAddress("mc",&mcObject,&b_mc);
 tree->SetBranchAddress("mean",&mean,&b_mean);
 tree->SetBranchAddress("sc",&scObject,&b_sc);
}
Long64_t GetNEntries(){
 return tree->GetEntries();
}
void GetParameters(float &eleE,float &mcE,float &scE,float &pt,float &eta,float &corr){
 eleE = eleObject.energy;
 mcE = mcObject.energy;
 pt = mcObject.pt;
 scE = scObject.rawEnergy + scObject.rawESEnergy;
 eta = mcObject.eta;
 corr = mean;
}

Long64_t GetEgEntry(Long64_t i){
 return tree->GetEntry(i);
}
};//end class


