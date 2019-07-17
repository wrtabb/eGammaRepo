void histDraw(TH1D*hist,TString plotName,TString titleName,bool logX=false,bool logY=false);
void profDraw(TProfile*hist1,TProfile*hist2,TProfile*hist3,bool logX=false,bool logY=false);
void histDraw2D(TH2*hist,TString plotName,TString titleName,bool logX=false,bool logY=false,bool logZ=false);
void counter(Long64_t i,Long64_t N,TString name);

void histDraw(TH1D*hist,TString plotName,TString titleName,bool logX,bool logY){
 TCanvas*canvas = new TCanvas("canvas","",0,0,1200,1000);
 canvas->SetGrid();
 if(logX) canvas->SetLogx();
 if(logY) canvas->SetLogy();
 hist->SetFillColor(kRed+2);
 hist->SetTitle(titleName);
 hist->Draw("PE");
 TString saveName = "/home/hep/wrtabb/git/DY-Analysis/plots/Egamma/";
 saveName += plotName;
 saveName += ".png";
 canvas->SaveAs(saveName);
}
 
void profDraw(TProfile*hist1,TProfile*hist2,TProfile*hist3,bool logX,bool logY){
 TLegend*legend = new TLegend(0.84,0.8,0.97,0.92);
  legend->SetTextSize(0.02);
  legend->AddEntry(hist1,"0 < p_{T} < 200");
  legend->AddEntry(hist2,"100 < p_{T} < 200");
  legend->AddEntry(hist3,"200 < p_{T}");
 TCanvas*canvas = new TCanvas("canvas","",0,0,1200,1000);
 canvas->SetGrid();
 if(logX) canvas->SetLogx();
 if(logY) canvas->SetLogy();
 hist1->SetTitle("Corrected energy/True energy");
 hist1->Draw("PE");
 hist2->Draw("PEsame");
 hist3->Draw("PEsame");
 legend->Draw("same");
 TString saveName = "/home/hep/wrtabb/git/DY-Analysis/plots/Egamma/";
 saveName += "eRatioProfiles_v2";
 saveName += ".png";
 canvas->SaveAs(saveName);
}

void histDraw2D(TH2*hist,TString plotName,TString titleName,bool logX,bool logY,bool logZ){
 TCanvas*canvas = new TCanvas("canvas","",0,0,1000,1000);
 canvas->SetLeftMargin(0.12);
 canvas->SetRightMargin(0.16);
 canvas->SetGrid();
 hist->GetYaxis()->SetTitleOffset(1.8);
 if(logX){
  canvas->SetLogx();
  hist->GetXaxis()->SetNoExponent();
  hist->GetXaxis()->SetMoreLogLabels();
 }
 if(logY){
  canvas->SetLogy();
  hist->GetYaxis()->SetNoExponent();
  hist->GetYaxis()->SetMoreLogLabels();
 }
 if(logZ){
  canvas->SetLogz();
 }

 hist->SetTitle(titleName);
 hist->Draw("colz");
 gPad->Update();
 TPaletteAxis*palette = (TPaletteAxis*)hist->GetListOfFunctions()->FindObject("palette");
 palette->SetX1NDC(0.845);
 palette->SetY1NDC(0.1);
 palette->SetX2NDC(0.89);
 palette->SetY2NDC(0.9);

 TString saveName = "/home/hep/wrtabb/git/DY-Analysis/plots/Egamma/";
 saveName += plotName;
 saveName += "_v2.png";
 canvas->SaveAs(saveName);
}

void counter(Long64_t i,Long64_t N,TString name)
{
  int P = 100*(i)/(N);
  TTimeStamp eventTimeStamp;
  if(i%(N/100)==0) {
    cout << name << ": [Time: " << eventTimeStamp.AsString("s") << "] " << P
      << "%" << endl;
  }
  return;
}

