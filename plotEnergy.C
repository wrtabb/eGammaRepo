#include "/home/hep/wrtabb/git/DY-Analysis/headers/headerFunctions.h"
#include "egRegTree.h"

const TString fileLoc = "../input_trees/DoubleElectron_FlatPt-1To300_2017ConditionsFlatPU0to70_105X_mc2017_realistic_v5-v2_AODSIM_EgRegTreeV5Refined.root";
const TString fileLocFriend = "/home/hep/wrtabb/EgRegresTrainerLegacy/resultsEleV5/regEleEcalTrk2017UL_RealIC_stdVar_stdCuts_ntrees1500_applied.root";
const TString treeName = "egRegTree";
const TString treeNameFriend = "egRegTreeFriend";
float ele_energy,mc_energy,mean;
float energy;

void plotEnergy()
{
 TFile*file = new TFile(fileLoc);
 TTree*tree = (TTree*)file->Get(treeName);
 TFile*fileFriend = new TFile(fileLocFriend);
 TTree*treeFriend = (TTree*)fileFriend->Get(treeNameFriend);
 tree->AddFriend(treeFriend);
 
 TBranch*b_ele;
 TBranch*b_mc;
 TBranch*b_mean;
 tree->SetBranchAddress("ele",&ele_energy,&b_ele);
 tree->SetBranchAddress("mc",&mc_energy,&b_mc);
 tree->SetBranchAddress("mean",&mean,&b_mean);

 TH1D*hEleE = new TH1D("hEleE","",100,0,3000);
 hEleE->SetMarkerStyle(20);
 TH1D*hMCE = new TH1D("hMCE","",100,0,3000);
 hMCE->SetMarkerStyle(25);
 TH1D*hEreg = new TH1D("hEreg","",100,0,3000);
 TH1D*hEres = new TH1D("hEres","",100,0,3000);
 TH1D*hEresRestricted = new TH1D("hEresRestricted","",300,0,30);
 double eReg,eRes;
 Long64_t nentries = tree->GetEntries();
 for(Long64_t i=0;i<nentries;i++){
  counter(i,nentries);
  tree->GetEntry(i);
  eReg = ele_energy*mean;
  hEreg->Fill(eReg);
  eRes = mc_energy - eReg;
  hEres->Fill(eRes);
 hEresRestricted->Fill(eRes);
 }

 TCanvas*canvas = new TCanvas("canvas","",0,0,1200,1000);
 canvas->SetGrid();
 hEres->Draw("hist");

 TFile*saveFile = new TFile("save.root","RECREATE");
 tree->Write();
 hEleE->Write();
 hMCE->Write();
 hEreg->Write();
 hEres->Write();
 hEresRestricted->Write();
 saveFile->Close();
}//end plotEnergy
