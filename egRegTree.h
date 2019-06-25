//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun 25 11:25:04 2019 by ROOT version 6.12/07
// from TTree egRegTree/
// found on file: ../input_trees/DoubleElectron_FlatPt-1To300_2017ConditionsFlatPU0to70_105X_mc2017_realistic_v5-v2_AODSIM_EgRegTreeV5Refined.root
//////////////////////////////////////////////////////////

#ifndef egRegTree_h
#define egRegTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class egRegTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           nrVert;
   Float_t         rho;
   Float_t         nrPUInt;
   Float_t         nrPUIntTrue;
   Int_t           evt_runnr;
   Int_t           evt_lumiSec;
   Int_t           evt_eventnr;
   Float_t         sc_rawEnergy;
   Float_t         sc_rawESEnergy;
   Float_t         sc_etaWidth;
   Float_t         sc_phiWidth;
   Float_t         sc_seedClusEnergy;
   Float_t         sc_numberOfClusters;
   Float_t         sc_numberOfSubClusters;
   Float_t         sc_clusterMaxDR;
   Float_t         sc_clusterMaxDRDPhi;
   Float_t         sc_clusterMaxDRDEta;
   Float_t         sc_clusterMaxDRRawEnergy;
   Float_t         sc_corrEnergy;
   Float_t         sc_scEta;
   Float_t         sc_scPhi;
   Float_t         sc_seedEta;
   Float_t         sc_seedPhi;
   Float_t         sc_dEtaSeedSC;
   Float_t         sc_dPhiSeedSC;
   Float_t         sc_isEB;
   Float_t         sc_iEtaOrX;
   Float_t         sc_iPhiOrY;
   Float_t         sc_iEtaMod5;
   Float_t         sc_iPhiMod2;
   Float_t         sc_iEtaMod20;
   Float_t         sc_iPhiMod20;
   Float_t         sc_etaGapCode;
   Float_t         sc_phiGapCode;
   Float_t         sc_nearbyChanStatus;
   Float_t         sc_corrEnergyAlt;
   Float_t         sc_rawEnergyAlt;
   Float_t         sc_nrClusAlt;
   Float_t         sc_scSinTheta;
   Float_t         sc_seedSinTheta;
   Float_t         ssFull_e3x3;
   Float_t         ssFull_e5x5;
   Float_t         ssFull_seedClusEnergy;
   Float_t         ssFull_eMax;
   Float_t         ssFull_e2nd;
   Float_t         ssFull_eLeftRightDiffSumRatio;
   Float_t         ssFull_eTopBottomDiffSumRatio;
   Float_t         ssFull_sigmaIEtaIEta;
   Float_t         ssFull_sigmaIEtaIPhi;
   Float_t         ssFull_sigmaIPhiIPhi;
   Float_t         ssFull_e2x5Max;
   Float_t         ssFull_e2x5Top;
   Float_t         ssFull_e2x5Bottom;
   Float_t         ssFull_e2x5Left;
   Float_t         ssFull_e2x5Right;
   Float_t         ssFull_eTop;
   Float_t         ssFull_eBottom;
   Float_t         ssFull_eLeft;
   Float_t         ssFull_eRight;
   Float_t         ssFrac_e3x3;
   Float_t         ssFrac_e5x5;
   Float_t         ssFrac_seedClusEnergy;
   Float_t         ssFrac_eMax;
   Float_t         ssFrac_e2nd;
   Float_t         ssFrac_eLeftRightDiffSumRatio;
   Float_t         ssFrac_eTopBottomDiffSumRatio;
   Float_t         ssFrac_sigmaIEtaIEta;
   Float_t         ssFrac_sigmaIEtaIPhi;
   Float_t         ssFrac_sigmaIPhiIPhi;
   Float_t         ssFrac_e2x5Max;
   Float_t         ssFrac_e2x5Top;
   Float_t         ssFrac_e2x5Bottom;
   Float_t         ssFrac_e2x5Left;
   Float_t         ssFrac_e2x5Right;
   Float_t         ssFrac_eTop;
   Float_t         ssFrac_eBottom;
   Float_t         ssFrac_eLeft;
   Float_t         ssFrac_eRight;
   Float_t         ele_et;
   Float_t         ele_energy;
   Float_t         ele_energyErr;
   Float_t         ele_ecalEnergy;
   Float_t         ele_ecalEnergyErr;
   Float_t         ele_eta;
   Float_t         ele_phi;
   Float_t         ele_trkEtaMode;
   Float_t         ele_trkPhiMode;
   Float_t         ele_trkPMode;
   Float_t         ele_trkPModeErr;
   Float_t         ele_fbrem;
   Float_t         ele_corrMean;
   Float_t         ele_corrSigma;
   Float_t         ele_hademTow;
   Float_t         ele_hademCone;
   Float_t         ele_trkPInn;
   Float_t         ele_trkPtInn;
   Float_t         ele_trkPVtx;
   Float_t         ele_trkPOut;
   Float_t         ele_trkChi2;
   Float_t         ele_trkNDof;
   Float_t         ele_ecalDrivenSeed;
   Float_t         ele_nrSatCrys;
   Float_t         ele_scRawEnergy;
   Float_t         ele_scRawESEnergy;
   Float_t         pho_et;
   Float_t         pho_energy;
   Float_t         pho_energyErr;
   Float_t         pho_eta;
   Float_t         pho_phi;
   Float_t         pho_corrMean;
   Float_t         pho_corrSigma;
   Float_t         pho_hademTow;
   Float_t         pho_hademCone;
   Float_t         pho_nrSatCrys;
   Float_t         pho_scRawEnergy;
   Float_t         pho_scRawESEnergy;
   Float_t         eleSSFull_e3x3;
   Float_t         eleSSFull_e5x5;
   Float_t         eleSSFull_seedClusEnergy;
   Float_t         eleSSFull_eMax;
   Float_t         eleSSFull_e2nd;
   Float_t         eleSSFull_eLeftRightDiffSumRatio;
   Float_t         eleSSFull_eTopBottomDiffSumRatio;
   Float_t         eleSSFull_sigmaIEtaIEta;
   Float_t         eleSSFull_sigmaIEtaIPhi;
   Float_t         eleSSFull_sigmaIPhiIPhi;
   Float_t         eleSSFull_e2x5Max;
   Float_t         eleSSFull_e2x5Top;
   Float_t         eleSSFull_e2x5Bottom;
   Float_t         eleSSFull_e2x5Left;
   Float_t         eleSSFull_e2x5Right;
   Float_t         eleSSFull_eTop;
   Float_t         eleSSFull_eBottom;
   Float_t         eleSSFull_eLeft;
   Float_t         eleSSFull_eRight;
   Float_t         phoSSFull_e3x3;
   Float_t         phoSSFull_e5x5;
   Float_t         phoSSFull_seedClusEnergy;
   Float_t         phoSSFull_eMax;
   Float_t         phoSSFull_e2nd;
   Float_t         phoSSFull_eLeftRightDiffSumRatio;
   Float_t         phoSSFull_eTopBottomDiffSumRatio;
   Float_t         phoSSFull_sigmaIEtaIEta;
   Float_t         phoSSFull_sigmaIEtaIPhi;
   Float_t         phoSSFull_sigmaIPhiIPhi;
   Float_t         phoSSFull_e2x5Max;
   Float_t         phoSSFull_e2x5Top;
   Float_t         phoSSFull_e2x5Bottom;
   Float_t         phoSSFull_e2x5Left;
   Float_t         phoSSFull_e2x5Right;
   Float_t         phoSSFull_eTop;
   Float_t         phoSSFull_eBottom;
   Float_t         phoSSFull_eLeft;
   Float_t         phoSSFull_eRight;
   Float_t         mc_energy;
   Float_t         mc_pt;
   Float_t         mc_eta;
   Float_t         mc_phi;
   Float_t         mc_pdgId;
   Float_t         mc_status;
   Float_t         mc_dR;
   Float_t         clus1_clusterRawEnergy;
   Float_t         clus1_clusterDEtaToSeed;
   Float_t         clus1_clusterDPhiToSeed;
   Float_t         clus2_clusterRawEnergy;
   Float_t         clus2_clusterDEtaToSeed;
   Float_t         clus2_clusterDPhiToSeed;
   Float_t         clus3_clusterRawEnergy;
   Float_t         clus3_clusterDEtaToSeed;
   Float_t         clus3_clusterDPhiToSeed;

   // List of branches
   TBranch        *b_nrVert;   //!
   TBranch        *b_rho;   //!
   TBranch        *b_nrPUInt;   //!
   TBranch        *b_nrPUIntTrue;   //!
   TBranch        *b_evt;   //!
   TBranch        *b_sc;   //!
   TBranch        *b_ssFull;   //!
   TBranch        *b_ssFrac;   //!
   TBranch        *b_ele;   //!
   TBranch        *b_pho;   //!
   TBranch        *b_eleSSFull;   //!
   TBranch        *b_phoSSFull;   //!
   TBranch        *b_mc;   //!
   TBranch        *b_clus1;   //!
   TBranch        *b_clus2;   //!
   TBranch        *b_clus3;   //!

   egRegTree(TTree *tree=0);
   virtual ~egRegTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef egRegTree_cxx
egRegTree::egRegTree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../input_trees/DoubleElectron_FlatPt-1To300_2017ConditionsFlatPU0to70_105X_mc2017_realistic_v5-v2_AODSIM_EgRegTreeV5Refined.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("../input_trees/DoubleElectron_FlatPt-1To300_2017ConditionsFlatPU0to70_105X_mc2017_realistic_v5-v2_AODSIM_EgRegTreeV5Refined.root");
      }
      f->GetObject("egRegTree",tree);

   }
   Init(tree);
}

egRegTree::~egRegTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t egRegTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t egRegTree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void egRegTree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("nrVert", &nrVert, &b_nrVert);
   fChain->SetBranchAddress("rho", &rho, &b_rho);
   fChain->SetBranchAddress("nrPUInt", &nrPUInt, &b_nrPUInt);
   fChain->SetBranchAddress("nrPUIntTrue", &nrPUIntTrue, &b_nrPUIntTrue);
   fChain->SetBranchAddress("evt", &evt_runnr, &b_evt);
   fChain->SetBranchAddress("sc", &sc_rawEnergy, &b_sc);
   fChain->SetBranchAddress("ssFull", &ssFull_e3x3, &b_ssFull);
   fChain->SetBranchAddress("ssFrac", &ssFrac_e3x3, &b_ssFrac);
   fChain->SetBranchAddress("ele", &ele_et, &b_ele);
   fChain->SetBranchAddress("pho", &pho_et, &b_pho);
   fChain->SetBranchAddress("eleSSFull", &eleSSFull_e3x3, &b_eleSSFull);
   fChain->SetBranchAddress("phoSSFull", &phoSSFull_e3x3, &b_phoSSFull);
   fChain->SetBranchAddress("mc", &mc_energy, &b_mc);
   fChain->SetBranchAddress("clus1", &clus1_clusterRawEnergy, &b_clus1);
   fChain->SetBranchAddress("clus2", &clus2_clusterRawEnergy, &b_clus2);
   fChain->SetBranchAddress("clus3", &clus3_clusterRawEnergy, &b_clus3);
   Notify();
}

Bool_t egRegTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void egRegTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t egRegTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef egRegTree_cxx
