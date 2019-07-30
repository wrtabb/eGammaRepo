#include "/home/hep/wrtabb/Egamma/include/EgRegAnalyzer.hh"
#include "/home/hep/wrtabb/Egamma/include/NtupleLocations.h"

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

void EgRegAnalyzer::Get1DPlots(TString step,VarName var){
 gROOT->SetBatch(true);
 TString nub;
 TString xAxisLabel;
 TString drawStyle;
 int nBins;
 float lowBin,highBin;

 if(var==ENERGY_TARGET){
  nub = "Tar";
  nBins = 50;
  lowBin = 0;
  highBin = 3.0;
  xAxisLabel = "E_{True}/E_{Corrected}";
  drawStyle = "PE";
 }
 if(var==ENERGY_CORRECTION){
  nub = "Corr";
  nBins = 50;
  lowBin = 0;
  highBin = 2.0;
  xAxisLabel = "Energy correction";
  drawStyle = "hist";
 }

 TString histTitle[nEtaRanges] = {
  "0.0 < #cbar#eta#cbar < 0.8",
  "0.8 < #cbar#eta#cbar < 1.5",
  "1.5 < #cbar#eta#cbar < 2.0",
  "2.0 < #cbar#eta#cbar < 2.5",
  "2.5 < #cbar#eta#cbar"
 };
 TString histName[nEtaRanges] = {
  "h"+nub+"0eta08",
  "h"+nub+"08eta15",
  "h"+nub+"15eta20",
  "h"+nub+"20eta25",
  "h"+nub+"25eta"
 };
 TString canvasName[nEtaRanges] = {
  "c"+nub+"0eta08",
  "c"+nub+"08eta15",
  "c"+nub+"15eta20",
  "c"+nub+"20eta25",
  "c"+nub+"25eta"
 };

 for(int i=0;i<nEtaRanges;i++){
  hist[i] = new TH1D(histName[i],"",nBins,lowBin,highBin);
  hist[i]->SetTitle(histTitle[i]);
  hist[i]->SetMarkerStyle(20);
  hist[i]->SetFillColor(kYellow-2);
  hist[i]->GetXaxis()->SetTitle(xAxisLabel);
  canvas[i] = new TCanvas(canvasName[i],"",0,0,1000,1000);
  canvas[i]->SetGrid();
  if(var==ENERGY_TARGET) canvas[i]->SetLogy();
 }

 Long64_t nEntries = tree->GetEntries();
 for(Long64_t i=0;i<nEntries;i++){
  float fill;
  counter(i,nEntries,step+"_"+nub);
  tree->GetEntry(i);
  eta = abs(mcObject.eta);
  if(var==ENERGY_TARGET) fill = 1/invTar;
  else if(var==ENERGY_CORRECTION) fill = mean;
  else cout << "ERROR: var not selected!" << endl;
  if(eta < 0.8) hist[0]->Fill(fill);
  else if(eta >= 0.8 && eta < 1.5) hist[1]->Fill(fill);
  else if(eta >= 1.5 && eta < 2.0) hist[2]->Fill(fill);
  else if(eta >= 2.0 && eta < 2.5) hist[3]->Fill(fill);
  else if(eta >= 2.5) hist[4]->Fill(fill);
 }//end event loop
 
 for(int i=0;i<nEtaRanges;i++){
  TString saveName = "/home/hep/wrtabb/git/DY-Analysis/plots/Egamma/";
  saveName += histName[i];
  saveName += "_"+step;
  saveName += ".png";
  canvas[i]->cd();
  hist[i]->Draw(drawStyle);
  canvas[i]->SaveAs(saveName);
 }
}//end GetTargetPlots

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

