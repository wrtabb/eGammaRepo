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
 InitBranches();
 cout << "Trees loaded from files: " << endl;
 cout << inputFile << endl;
 cout << "Number of entries: " << tree->GetEntries() << endl; 
 cout << friendFile << endl;
 cout << "Number of entries: " << treeFriend->GetEntries() << endl; 
}//end constructor

//-----Load trees-----//
void EgRegAnalyzer::LoadTree(){
 TFile*file = new TFile(inputFile);
 TFile*fileFriend = new TFile(friendFile);
 tree = (TTree*)file->Get(treeName);
 treeFriend = (TTree*)fileFriend->Get(treeNameFriend);
 tree->AddFriend(treeFriend);
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

//-----Get and plot any one variable-----//
void EgRegAnalyzer::Get1DPlots(TString step,VarName var){
 if(var==NONE){
  cout << "No var selected" << endl;
  return;
 }
 gROOT->SetBatch(true);
 TString nub;
 TString xAxisLabel;
 TString drawStyle;
 int nBins;
 float lowBin = 0;
 float highBin = 0;

 if(var==ENERGY_TARGET){
  nub = "Tar";
  nBins = 50;
  lowBin = 0;
  highBin = 3.0;
  xAxisLabel = "E_{True}/E_{Raw}";
  drawStyle = "PE";
 }
 else if(var==ENERGY_TARGET_INV){
  nub = "InvTar";
  nBins = 50;
  lowBin = 0;
  highBin = 3.0;
  xAxisLabel = "E_{Raw}/E_{True}";
  drawStyle = "PE";
 }
 else if(var==ENERGY_CORRECTION){
  nub = "Corr";
  nBins = 50;
  lowBin = 0;
  highBin = 2.0;
  xAxisLabel = "Energy correction";
  drawStyle = "hist";
 }
 else if(var==ENERGY_TARGET_CORR){
  nub = "TarCorr";
  nBins = 50;
  lowBin = 0;
  highBin = 3.0;
  xAxisLabel = "E_{True}/E_{Corrected}";
  drawStyle = "PE";
 }
 else if(var==ENERGY_TARGET_CORR_INV){
  nub = "InvTarCorr";
  nBins = 50;
  lowBin = 0;
  highBin = 3.0;
  xAxisLabel = "E_{Corrected}/E_{True}";
  drawStyle = "PE";
 }
 else {
  cout << "Var not set!" << endl;
 }
 TString histTitle[nEtaRanges] = {
  "0.0 < #cbar#eta#cbar < 0.8",
  "0.8 < #cbar#eta#cbar < 1.5",
  "1.5 < #cbar#eta#cbar < 2.0",
  "2.0 < #cbar#eta#cbar < 2.5",
  "2.5 < #cbar#eta#cbar"
 };
 TString histName[nEtaRanges] = {
  "h"+nub+"_"+step+"_0eta08",
  "h"+nub+"_"+step+"_08eta15",
  "h"+nub+"_"+step+"_15eta20",
  "h"+nub+"_"+step+"_20eta25",
  "h"+nub+"_"+step+"_25eta"
 };
 TString canvasName[nEtaRanges] = {
  "c"+nub+"_"+step+"_0eta08",
  "c"+nub+"_"+step+"_08eta15",
  "c"+nub+"_"+step+"_15eta20",
  "c"+nub+"_"+step+"_20eta25",
  "c"+nub+"_"+step+"_25eta"
 };

 for(int i=0;i<nEtaRanges;i++){
  hist[i] = new TH1D(histName[i],"",nBins,lowBin,highBin);
  hist[i]->SetTitle(histTitle[i]);
  hist[i]->SetMarkerStyle(20);
  hist[i]->SetFillColor(kYellow-2);
  hist[i]->GetXaxis()->SetTitle(xAxisLabel);
  canvas[i] = new TCanvas(canvasName[i],"",0,0,1000,1000);
  canvas[i]->SetGrid();
  if(var!=ENERGY_CORRECTION) canvas[i]->SetLogy();
 }

 Long64_t nEntries = tree->GetEntries();
 for(Long64_t i=0;i<nEntries;i++){
  float fill = -9999;
  counter(i,nEntries,step+"_"+nub);
  tree->GetEntry(i);
  eta = abs(mcObject.eta);
  if     (var==ENERGY_TARGET)          fill = 1/invTar;
  else if(var==ENERGY_TARGET_INV)      fill = invTar;
  else if(var==ENERGY_CORRECTION)      fill = mean;
  else if(var==ENERGY_TARGET_CORR)     fill = 1/(invTar*mean);
  else if(var==ENERGY_TARGET_CORR_INV) fill = invTar*mean;
  else cout << "ERROR: var not selected!" << endl;
  if(eta < 0.8) hist[0]->Fill(fill);
  else if(eta >= 0.8 && eta < 1.5) hist[1]->Fill(fill);
  else if(eta >= 1.5 && eta < 2.0) hist[2]->Fill(fill);
  else if(eta >= 2.0 && eta < 2.5) hist[3]->Fill(fill);
  else if(eta >= 2.5) hist[4]->Fill(fill);
 }//end event loop
 
 TFile*saveFile = new TFile(saveFileName,"update");
 for(int i=0;i<nEtaRanges;i++){
  TString saveName = plotLocation; 
  saveName += histName[i];
  saveName += ".png";
  canvas[i]->cd();
  hist[i]->Draw(drawStyle);
  canvas[i]->SaveAs(saveName);
  hist[i]->Write();
 }
 saveFile->Close();
}//end GetTargetPlots

//-----Plotting invTar to fit with Cruijff function-----//
void EgRegAnalyzer::PlotCruijff(TString step){
 TH1D*hInvTarget = new TH1D("hInvTarget","",50,0.65,1.10);
 TH1D*hInvTargetCorrected = new TH1D("hInvTargetCorrected","",50,0.65,1.10);
 hInvTargetCorrected->SetMarkerStyle(20);
 Long64_t nEntries = tree->GetEntries();
 float rawE,mcE;
 for(Long64_t i=0;i<nEntries;i++){
  float fill = -9999;
  counter(i,nEntries,"CruijffPlotter_"+step);
  tree->GetEntry(i);
  eta = abs(mcObject.eta);
  rawE = (scObject.rawEnergy+scObject.rawESEnergy);
  mcE = mcObject.energy;
  if(eta>1.44) continue;
  hInvTarget->Fill(invTar);
  hInvTargetCorrected->Fill(invTar/mean);  
 }
 TCanvas*canvas = new TCanvas("canvas","",0,0,1200,1000);
 canvas->SetGrid();
 TLegend*legend = new TLegend(0,0.9,0.2,1);
 legend->AddEntry(hInvTarget,"Inverse target");
 legend->AddEntry(hInvTargetCorrected,"1/(target*correction)");
 hInvTarget->Draw("hist");
 hInvTargetCorrected->Draw("pe,same");
 legend->Draw("same");
 TString saveName = plotLocation;
 saveName += "targetPlots_"+step+".png";
 canvas->SaveAs(saveName);
}

//-----Counter for keeping track of progress-----//
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

