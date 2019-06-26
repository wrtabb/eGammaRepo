#include "/home/hep/wrtabb/git/DY-Analysis/headers/headerFunctions.h"
#include "egRegTree.h"

void histOptions(TH1D*hist);

const TString fileLoc = "/home/hep/wrtabb/input_trees/DoubleElectron_FlatPt-1To300_2017ConditionsFlatPU0to70_105X_mc2017_realistic_v5-v2_AODSIM_EgRegTreeV5Refined.root";
const TString fileLocFriend = "/home/hep/wrtabb/EgRegresTrainerLegacy/resultsEleV5/regEleEcalTrk2017UL_RealIC_stdVar_stdCuts_ntrees1500_applied.root";
const TString treeName = "egRegTree";
const TString treeNameFriend = "egRegTreeFriend";
//float ele_energy,mc_energy,mc_pt,sc_rawEnergy,mean;
//float ele_energyErr,energy;
float mean;

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

 struct GenInfoStruct {
  float energy,pt,eta,phi,pdgId,status,dR;
 };
 
 EleStruct eleObject;
 EleStruct scObject;
 GenInfoStruct  mcObject;

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
 TH1D*hEleE = new TH1D("hEleE","",100,0,3750);
 histOptions(hEleE);
 TH1D*hMCE = new TH1D("hMCE","",100,0,3000);
 histOptions(hMCE);
 TH1D*hEreg = new TH1D("hEreg","",100,0,3000);
 histOptions(hEreg);
 TH1D*hEres = new TH1D("hEres","",100,0,3000);
 histOptions(hEres);
 TH1D*hEresRestricted = new TH1D("hEresRestricted","",100,0,5);
 histOptions(hEresRestricted);
 TH1D*hSCE = new TH1D("hSCE","",300,0,3200);
 histOptions(hSCE);
 TH1D*hCorr = new TH1D("hCorr","",100,0.05,2.15);
 histOptions(hCorr);

 double eReg,eRes;
 Long64_t nentries = tree->GetEntries();
 
 //-----Loop over events in tree-----//
 for(Long64_t i=0;i<nentries;i++){
  counter(i,nentries);

  //-----Get entry from tree-----//
  tree->GetEntry(i);
  eReg = eleObject.energy*mean;
  eRes = mcObject.energy - eReg;

  //-----Fill histograms from tree-----//
  hEleE->Fill(eleObject.energy);
  hMCE->Fill(mcObject.energy);
  hEreg->Fill(eReg);
  hEres->Fill(eRes);
  hEresRestricted->Fill(eRes);
  hSCE->Fill(scObject.scRawEnergy);
  hCorr->Fill(mean);
 }

 //-----Make plots-----//
 TCanvas*canvas = new TCanvas("canvas","",0,0,1200,1000);
 canvas->SetGrid();
 tree->Draw("mc.energy");
 hMCE->Draw("pe,same");
 canvas->SaveAs("/home/hep/wrtabb/git/DY-Analysis/plots/Egamma/mcEnergyComparison.png");

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

void histOptions(TH1D*hist){
 hist->SetMarkerStyle(20);
 return;
}
