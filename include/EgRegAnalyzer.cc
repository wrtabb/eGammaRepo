#include "EgRegAnalyzer.hh"
#include "NtupleLocations.h"

EgRegAnalyzer::EgRegAnalyzer(TString step,VarName var){
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

 LoadTree();
 InitBranches(step);
 cout << "Trees loaded from files: " << endl;
 cout << inputFile << endl;
 cout << "Number of entries: " << tree->GetEntries() << endl; 
 cout << friendFile << endl;
 cout << "Number of entries: " << treeFriend->GetEntries() << endl; 
}//end constructor

void EgRegAnalyzer::LoadTree(){
 TFile*file = new TFile(inputFile);
 TFile*fileFriend = new TFile(friendFile);
 tree = (TTree*)file->Get(treeName);
 treeFriend = (TTree*)fileFriend->Get(treeNameFriend);
 tree->AddFriend(treeFriend);
}//end LoadTree

void EgRegAnalyzer::InitBranches(TString step){
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

void EgRegAnalyzer::GetPlots(TString step,VarName var){
 TString histTitle[nEtaRanges] = {
  "0.0 < #lbar#eta#cbar < 0.8",
  "0.8 < #lbar#eta#cbar < 1.5",
  "1.5 < #lbar#eta#cbar < 2.0",
  "2.0 < #lbar#eta#cbar < 2.5",
  "2.5 < #lbar#eta#cbar < 3.0",
  "3.0 < #lbar#eta#cbar < 3.5"
 };
 TString histName[nEtaRanges] = {
  "hTar0eta08",
  "hTar08eta15",
  "hTar15eta20",
  "hTar20eta25",
  "hTar25eta30",
  "hTar30eta35"
 };
 TString canvasName[nEtaRanges] = {
  "cTar0eta08",
  "cTar08eta15",
  "cTar15eta20",
  "cTar20eta25",
  "cTar25eta30",
  "cTar30eta35"
 };
 int nBins;
 float lowBin,highBin;
 TString xAxisLabel;
 if(var==ENERGY_TARGET){
  nBins = 50;
  lowBin = 0;
  highBin = 3.0;
  xAxisLabel = "E_{True}/E_{Corrected}";
 }//end if energy target

 for(int i=0;i<nEtaRanges;i++){
  hist[i] = new TH1D(histName[i],"",nBins,lowBin,highBin);
  hist[i]->SetTitle(histTitle[i]);
  hist[i]->SetMarkerStyle(20);
  canvas[i] = new TCanvas(canvasName[i],"",0,0,1000,1000);
  canvas[i]->SetGrid();
  canvas[i]->SetLogy();
 }

 Long64_t nEntries = tree->GetEntries();
 for(Long64_t i=0;i<nEntries;i++){
  counter(i,nEntries,step);
  tree->GetEntry(i);
  eta = abs(mcObject.eta);
  tar = 1.0/invTar;
  if(eta < 0.8) hist[0]->Fill(tar);
  if(eta >= 0.8 && eta < 1.5) hist[1]->Fill(tar);
  if(eta >= 1.5 && eta < 2.0) hist[2]->Fill(tar);
  if(eta >= 2.0 && eta < 2.5) hist[3]->Fill(tar);
  if(eta >= 2.5 && eta < 3.0) hist[4]->Fill(tar);
  if(eta >= 3.0 && eta < 3.5) hist[5]->Fill(tar);
 }//end event loop
 
 for(int i=0;i<nEtaRanges;i++){
  TString saveName = "/home/hep/wrtabb/git/DY-Analysis/plots/Egamma/";
  saveName += histName[i];
  saveName += "_"+step;
  saveName += ".png";
  canvas[i]->cd();
  hist[i]->Draw("PE");
  canvas[i]->SaveAs(saveName);
 }
}//end GetPlots

void EgRegAnalyzer::counter(Long64_t i,Long64_t N,TString name)
{
  int P = 100*(i)/(N);
  TTimeStamp eventTimeStamp;
  if(i%(N/100)==0) {
    cout << name << ": [Time: " << eventTimeStamp.AsString("s") << "] " << P
      << "%" << endl;
  }
  return;
}

