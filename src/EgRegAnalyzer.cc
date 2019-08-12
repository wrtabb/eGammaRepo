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

void EgRegAnalyzer::Plot2DHist(VarType varX,VarType varY,TString step)
{
 gStyle->SetOptStat(0);
 gStyle->SetPalette(1);
 VariableHandler*variableX = new VariableHandler(varX);
 VariableHandler*variableY = new VariableHandler(varY);
 std::vector<float> vecX = variableX->GetRangeLimits();
 std::vector<float> vecY = variableY->GetRangeLimits();
 Long64_t nEvents = tree->GetEntries();
 int nBinsX = variableX->GetNRanges();
 int nBinsY = variableY->GetNRanges();
 float rangeX[nBinsX];
 float rangeY[nBinsY];
 TString xAxisTitle = variableX->GetVarTitle();
 TString yAxisTitle = variableY->GetVarTitle();

 for(int i=0;i<=nBinsX;i++){
  rangeX[i] = vecX.at(i);
 }
 for(int i=0;i<=nBinsY;i++){
  rangeY[i] = vecY.at(i);
 }

 TH2D*hist = new TH2D("hist","",nBinsX,rangeX,nBinsY,rangeY);
 hist->GetXaxis()->SetTitle(xAxisTitle);
 hist->GetYaxis()->SetTitle(yAxisTitle);
 
 hist->GetYaxis()->SetTitleOffset(1.8);

 double fillX,fillY;
 for(Long64_t j=0;j<nEvents;j++){
  counter(j,nEvents,"Loading events");
  tree->GetEntry(j);
  if     (varX==ETA)          fillX = mcObject.eta;
  else if(varX==ABS_ETA)      fillX = abs(mcObject.eta);
  else if(varX==INV_TAR)      fillX = invTar;
  else if(varX==INV_TAR_CORR) fillX = invTar*mean;
  else if(varX==MEAN)         fillX = mean;
  else {
   cout << "Variable not found" << endl;
   return;
  }

  if     (varY==ETA)          fillY = mcObject.eta;
  else if(varY==ABS_ETA)      fillY = abs(mcObject.eta);
  else if(varY==INV_TAR)      fillY = invTar;
  else if(varY==INV_TAR_CORR) fillY = invTar*mean;
  else if(varY==MEAN)         fillY = mean;
  else {
   cout << "Variable not found" << endl;
   return;
  }

  hist->Fill(fillX,fillY);
 }//end event loop
 TString saveName = "/home/hep/wrtabb/git/DY-Analysis/plots/Egamma/";

 TCanvas*canvas=new TCanvas("canvas","",1000,1000);
 canvas->SetGrid();
 canvas->SetLeftMargin(0.12);
 canvas->SetRightMargin(0.16);
 hist->Draw("colz");
 gPad->Update();
 TPaletteAxis*palette = (TPaletteAxis*)hist->GetListOfFunctions()->FindObject("palette");
 palette->SetX1NDC(0.845);
 palette->SetY1NDC(0.1);
 palette->SetX2NDC(0.89);
 palette->SetY2NDC(0.9);

 TString save2D = saveName;
 save2D += "h2D_";
 save2D += variableX->GetVarName() + "_";
 save2D += variableY->GetVarName() + step;
 save2D += ".png";
 canvas->SaveAs(save2D);

 TProfile*profile = (TProfile*)hist->ProfileX(); 
 profile->GetYaxis()->SetRangeUser(0,2);
 profile->SetMarkerStyle(20);
 profile->GetXaxis()->SetTitle(xAxisTitle);
 profile->GetYaxis()->SetTitle(yAxisTitle);
 TCanvas*canvas2=new TCanvas("canvas2","",1000,1000);
 canvas2->SetGrid();
 profile->Draw("pe");

 TString saveProf = saveName;
 saveProf += "hProfile_";
 saveProf += variableX->GetVarName() + "_";
 saveProf += variableY->GetVarName() + step;
 saveProf += ".png";
 canvas2->SaveAs(saveProf);
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

