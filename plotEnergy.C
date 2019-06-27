#include "Functions.h"

const TString fileLoc = "/home/hep/wrtabb/input_trees/DoubleElectron_FlatPt-1To300_2017ConditionsFlatPU0to70_105X_mc2017_realistic_v5-v2_AODSIM_EgRegTreeV5Refined.root";
const TString fileLocFriend = "/home/hep/wrtabb/EgRegresTrainerLegacy/resultsEleV5/regEleEcalTrk2017UL_RealIC_stdVar_stdCuts_ntrees1500_applied.root";
const TString treeName = "egRegTree";
const TString treeNameFriend = "egRegTreeFriend";
float mean;

const int energyBinLow = 0;
const int energyBinHigh = 3750;
const int nBinsEnergy = 100;

void plotEnergy()
{
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

 if(!tree){
  cout << "Error loading tree!!!!!!!!" << endl;
  return;
 }

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
 TH1D*hEleE = new TH1D("hEleE","",nBinsEnergy,energyBinLow,energyBinHigh);
 TH1D*hMCE = new TH1D("hMCE","",nBinsEnergy,energyBinLow,energyBinHigh);
 TH1D*hEreg = new TH1D("hEreg","",nBinsEnergy,energyBinLow,energyBinHigh);
 TH1D*hEres = new TH1D("hEres","",2*nBinsEnergy,-energyBinHigh,energyBinHigh);
 TH1D*hEresRestricted = new TH1D("hEresRestricted","",200,-5,5);
 TH1D*hSCE = new TH1D("hSCE","",nBinsEnergy,energyBinLow,energyBinHigh);
 TH1D*hCorrection = new TH1D("hCorrection","",100,0,2.5);
 TH1D*hTrueRawRatio = new TH1D("hTrueRawRatio","",100,0.6,2.0);

 double eReg,eRes,eRatio;
 Long64_t nentries = tree->GetEntries();
 
 //-----Loop over events in tree-----//
 for(Long64_t i=0;i<nentries;i++){
  counter(i,nentries,"plotEgamma");

  //-----Get entry from tree-----//
  tree->GetEntry(i);
  eReg = eleObject.energy*mean;
  eRes = mcObject.energy - eReg;
  eRatio = mcObject.energy/eleObject.energy;

  //-----Fill histograms from tree-----//
  hEleE->Fill(eleObject.energy);
  hMCE->Fill(mcObject.energy);
  hEreg->Fill(eReg);
  hEres->Fill(eRes);
  hEresRestricted->Fill(eRes);
  hSCE->Fill(scObject.rawEnergy);
  hCorrection->Fill(mean);
  hTrueRawRatio->Fill(eRatio);
 }

 //-----Make plots-----//
 histDraw(hEleE,"eleEnergy","Electron energy");
 histDraw(hMCE,"mcEnergy","MC energy");
 histDraw(hEreg,"regEnergy","Corrected energy");
 histDraw(hEres,"resEnergy","Energy residuals");
 histDraw(hEresRestricted,"resEnergyRestrictedRange","Energy residuals");
 histDraw(hSCE,"scEnergy","Supercluster raw energy");
 histDraw(hCorrection,"correctionEnergy","Energy correction");
 histDraw(hTrueRawRatio,"trueRawRatio","True to raw energy ratio",false,true);

 //-----Save histograms-----//
 TFile*saveFile = new TFile("save.root","RECREATE");
 hEleE->Write();
 hMCE->Write();
 hSCE->Write();
 hEreg->Write();
 hEres->Write();
 hEresRestricted->Write();
 saveFile->Close();
}//end plotEnergy

