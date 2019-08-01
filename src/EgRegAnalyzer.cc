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

//-----Get and plot any one variable-----//
void EgRegAnalyzer::Get1DPlots(TString step,VarName var){
 if(var==NONE){
  cout << "No var selected" << endl;
  return;
 }
 gROOT->SetBatch(true);
 TString nub;
 TString drawStyle;
 TString xAxisLabel;
 int nBins;
 float lowBin = 0.0;
 float highBin = 2.00;

 if(var==ENERGY_TARGET_INV){
  nub = "InvTar";
  nBins = 200;
  drawStyle = "PE";
  xAxisLabel = "E_{Raw}/E_{True}";
 }
 else if(var==ENERGY_TARGET_CORR_INV){
  nub = "InvTarCorr";
  nBins = 200;
  drawStyle = "PE";
  xAxisLabel = "E_{Raw}/E_{True}";
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
  "h"+nub+"_"+step+"_00eta08",
  "h"+nub+"_"+step+"_08eta15",
  "h"+nub+"_"+step+"_15eta20",
  "h"+nub+"_"+step+"_20eta25",
  "h"+nub+"_"+step+"_25eta"
 };
 TString canvasName[nEtaRanges] = {
  "c"+nub+"_"+step+"_00eta08",
  "c"+nub+"_"+step+"_08eta15",
  "c"+nub+"_"+step+"_15eta20",
  "c"+nub+"_"+step+"_20eta25",
  "c"+nub+"_"+step+"_25eta"
 };

 for(int i=0;i<nEtaRanges;i++){
  hist[i] = new TH1D(histName[i],"",nBins,lowBin,highBin);
  hist[i]->SetTitle(histTitle[i]);
  hist[i]->SetMarkerStyle(20);
  hist[i]->GetXaxis()->SetTitle(xAxisLabel);
  canvas[i] = new TCanvas(canvasName[i],"",0,0,1000,1000);
  canvas[i]->SetGrid();
  canvas[i]->SetLogy();
 }

 Long64_t nEntries = tree->GetEntries();
 for(Long64_t i=0;i<nEntries;i++){
  float fill = -9999;
  counter(i,nEntries,step+"_"+nub);
  tree->GetEntry(i);
  eta = abs(mcObject.eta);
  if(var==ENERGY_TARGET_INV)      fill = invTar;
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

//-----Plot target and target/correction together
void EgRegAnalyzer::PlotTarAndCorrected(TString step,TString histName1,TString histName2){
 gROOT->SetBatch(true);
 gStyle->SetOptStat(0);
 TFile*inFile = new TFile(saveFileName);
 TH1D*hist1 = (TH1D*)inFile->Get(histName1);
 TH1D*hist2 = (TH1D*)inFile->Get(histName2);
 hist1->SetFillColor(kWhite);
 hist2->SetFillColor(kWhite);
 hist1->SetMarkerStyle(25);
 hist2->SetMarkerStyle(20);
 hist1->SetMarkerColor(kRed);
 hist2->SetMarkerColor(kBlue);
 TLegend*legend = new TLegend(0.1,0.8,0.3,0.9);
 legend->AddEntry(hist1,"invTarget");
 legend->AddEntry(hist2,"invTargetCorrected");

 TCanvas*canvas = new TCanvas("canvas","",0,0,1200,1000);
 canvas->SetGrid();
 canvas->SetLogy();
 hist1->Draw("pe");
 hist2->Draw("pe,same");
 legend->Draw("same");
 canvas->SaveAs(plotLocation+histName1+"_"+histName2+".png");
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

