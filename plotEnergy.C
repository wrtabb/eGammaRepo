#include "/home/hep/wrtabb/git/DY-Analysis/headers/headerFunctions.h"
#include "egRegTree.h"

const TString fileLoc = "../input_trees/DoubleElectron_FlatPt-1To300_2017ConditionsFlatPU0to70_105X_mc2017_realistic_v5-v2_AODSIM_EgRegTreeV5Refined.root";
const TString fileLocFriend = "/home/hep/wrtabb/EgRegresTrainerLegacy/resultsEleV5/regEleEcalTrk2017UL_RealIC_stdVar_stdCuts_ntrees1500_applied.root";
const TString treeName = "egRegTree";
const TString treeNameFriend = "egRegTreeFriend";
float ele_energy,mc_energy,sc_rawEnergy,mean;

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
 TBranch*b_sc;

 tree->SetBranchAddress("ele",&ele_energy,&b_ele);
 tree->SetBranchAddress("mc",&mc_energy,&b_mc);
 tree->SetBranchAddress("mean",&mean,&b_mean);
 tree->SetBranchAddress("sc",&sc_rawEnergy,&b_sc);

 TH1D*hEleE = new TH1D("hEleE","",100,0,3750);
 hEleE->SetMarkerStyle(20);
 TH1D*hMCE = new TH1D("hMCE","",100,0,3000);
 hMCE->SetMarkerStyle(25);
 TH1D*hEreg = new TH1D("hEreg","",100,0,3000);
 TH1D*hEres = new TH1D("hEres","",100,0,3000);
 TH1D*hEresRestricted = new TH1D("hEresRestricted","",100,0,5);
 TH1D*hSCE = new TH1D("hSCE","",300,0,3200);
 hSCE->SetMarkerStyle(25);
 TH1D*hCorr = new TH1D("hCorr","",100,0.05,2.15);
 hCorr->SetMarkerStyle(20);

 double eReg,eRes;
 Long64_t nentries = tree->GetEntries();
 for(Long64_t i=0;i<nentries;i++){
  counter(i,nentries);
  tree->GetEntry(i);

  eReg = ele_energy*mean;
  eRes = mc_energy - eReg;

  hEleE->Fill(ele_energy);
  hMCE->Fill(mc_energy);
  hEreg->Fill(eReg);
  hEres->Fill(eRes);
  hEresRestricted->Fill(eRes);
  hSCE->Fill(sc_rawEnergy);
  hCorr->Fill(mean);
 }

 TCanvas*canvas = new TCanvas("canvas","",0,0,1200,1000);
 canvas->SetGrid();
 tree->Draw("ele.energy");
 hEleE->Draw("PE,same");

 TFile*saveFile = new TFile("save.root","RECREATE");
 hEleE->Write();
 hMCE->Write();
 hSCE->Write();
 hEreg->Write();
 hEres->Write();
 hEresRestricted->Write();
 saveFile->Close();
}//end plotEnergy
