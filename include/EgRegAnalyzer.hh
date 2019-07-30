#ifndef EgRegAnalyzer_HH
#define EgRegAnalyzer_HH
#include <TTree.h>
#include <TFile.h>
#include <TString.h>
#include <iostream>
#include <TH1D.h>
#include <TCanvas.h>
#include <TTimeStamp.h>
#include <TSystem.h>
#include <TROOT.h>

using namespace std;

enum VarName {
 ENERGY_CORRECTION,
 ENERGY_TARGET,
};

class EgRegAnalyzer
{
public:

 EgRegAnalyzer(TString step);

 TString inputFile;
 TString friendFile;
 TString treeName = "egRegTree";
 TString treeNameFriend = "egRegTreeFriend";

 TTree*tree;
 TTree*treeFriend;
 TFile*file;
 TFile*fileFriend;

 float nentries;
 float eleE;
 float mcE;
 float scE;
 float eta;
 float trkP;
 float trkPErr;
 float pt;
 float mean;
 float invTar;
 float realSigma;
 float regIdealMean;
 float regIdealSigma;
 float regRealSigma;
 float regRealMean;
 const static int nEtaRanges = 5;

 TH1D*hist[nEtaRanges];
 TCanvas*canvas[nEtaRanges];

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

 struct SSFULLStruct {
  float e3x3,e5x5,seedClusEnergy,eMax,e2nd,eLeftRightDiffSumRatio,eTopBottomDiffSumRatio,
  sigmaIEtaIEta,sigmaIEtaIPhi,sigmaIPhiIPhi,e2x5Max,e2x5Top,e2x5Bottom,e2x5Left,e2x5Right,
  eTop,eBottom,eLeft,eRight;
 };

 EleStruct eleObject;
 SCStruct scObject;
 MCStruct mcObject;
 SSFULLStruct ssObject;

 void LoadTree();
 void InitBranches(TString step);
 void Get1DPlots(TString step,VarName var);  
 void counter(Long64_t i,Long64_t N,TString name);
};

#endif
