#include "EgRegAnalyzer.hh"
#include "VariableHandler.hh"
#include "NtupleLocations.h"

EgRegAnalyzer::EgRegAnalyzer(TString step){
 if(step=="step1"){
  inputFile = baseInputsEle+idealIC;
  friendFile = baseResultsEle+step1;
 }
 else if(step=="step3"){
  inputFile = baseResultsEle+step2;
  friendFile = baseResultsEle+step3;
 }
 else if(step=="step4"){
  inputFile = baseResultsEle+step3;
  friendFile = baseResultsEle+step4;
 }
 else{
  cout << "Step not properly defined!" << endl;
  return;
 }

}//end constructor

//-----Load trees-----//
void EgRegAnalyzer::LoadTree(){
 TFile*file = new TFile(inputFile);
 TFile*fileFriend = new TFile(friendFile);
 tree = (TTree*)file->Get(treeName);
 treeFriend = (TTree*)fileFriend->Get(treeNameFriend);
 tree->AddFriend(treeFriend);

 cout << "Trees loaded from files: " << endl;
 cout << inputFile << endl;
 cout << "Number of entries: " << tree->GetEntries() << endl; 
 cout << friendFile << endl;
 cout << "Number of entries: " << treeFriend->GetEntries() << endl; 
}//end LoadTree

//-----Initialize branches-----//
void EgRegAnalyzer::InitBranches(){
 TBranch*b_ele;
 TBranch*b_mc;
 TBranch*b_mean;
 TBranch*b_sc;
 TBranch*b_ss;
 TBranch*b_invTar;

 tree->SetBranchAddress("ele",&eleObject,&b_ele);
 tree->SetBranchAddress("mc",&mcObject,&b_mc);
 tree->SetBranchAddress("mean",&mean,&b_mean);
 tree->SetBranchAddress("sc",&scObject,&b_sc);
 tree->SetBranchAddress("ssFull",&ssObject,&b_ss);
 tree->SetBranchAddress("invTar",&invTar,&b_invTar);
}//end InitBranches

//-----Plot 1-dimensional histogram-----//
void EgRegAnalyzer::Plot1DHist(VarType var,TString step,TString saveAddendum = "")
{
 gStyle->SetOptStat(0);
 VariableHandler*variable = new VariableHandler(var);
 std::vector<float> vec = variable->GetRangeLimits();
 int nBins = variable->GetNRanges();
 float range[nBins];
 TString xAxisTitle = variable->GetVarTitle();

 for(int i=0;i<=nBins;i++){
  range[i] = vec.at(i);
 }
 TH1D*hist = new TH1D("hist","",nBins,range);
 hist->SetMarkerStyle(20);
 hist->GetXaxis()->SetTitle(xAxisTitle);
 Long64_t nEvents = tree->GetEntries();
 double fill; 
 for(Long64_t j=0;j<nEvents;j++){
  counter(j,nEvents,"Loading events");
  tree->GetEntry(j);         
  if(var==ETA)               fill = mcObject.eta;
  else if(var==ABS_ETA)      fill = abs(mcObject.eta);
  else if(var==INV_TAR)      fill = invTar;
  else if(var==INV_TAR_CORR) fill = invTar*mean;
  else {
   cout << "Variable not found" << endl;
   return;
  }
  hist->Fill(fill);
 }
 
 TCanvas*canvas = new TCanvas("canvas","",0,0,1000,1000);
 canvas->SetGrid();
 hist->Draw("pe");
 TString saveName = "/home/hep/wrtabb/git/DY-Analysis/plots/Egamma/";
 saveName += variable->GetVarName();
 saveName += saveAddendum;
 saveName += "_"+step;
 saveName += ".png";
 canvas->SaveAs(saveName);
 delete canvas;
 delete hist;
}

//-----Counter for keeping track of progress-----//
void EgRegAnalyzer::counter(Long64_t i,Long64_t N,TString name)
{
 int P = 100*(i)/(N);
 TTimeStamp eventTimeStamp;
 if(i%(N/100)==0) {
  cout << name << ": [Time: " << eventTimeStamp.AsString("s") << "] " << P << "%" << endl;
 }
 return;
}

