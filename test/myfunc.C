
Double_t myfunction(Double_t *x, Double_t *par);
void myfunc();
void myfit(TString hist);
void allHists();

//starting values for parameters
float scale =  2.5e6;
float mean = 1.0;
float sigmaL = 0.05;
float sigmaR = 0.05;
float alphaL = 1.0;
float alphaR = 0.5;

//Fitting range
float xLow = 0.6;
float xHigh = 1.1;

Double_t myfunction(Double_t *x, Double_t *par)
{
  Float_t xx =x[0];
  //Double_t f = par[0]*TMath::Gaus(xx,par[1],par[2]);
  double dx = (xx-par[1]) ;
  double sigma = dx<0 ? par[2]: par[3] ;
  double alpha = dx<0 ? par[4]: par[5] ;
  double f = 2*sigma*sigma + alpha*dx*dx ;
  return par[0]*exp(-dx*dx/f) ;
}
void myfunc()
{
   TF1 *f1 = new TF1("myfunc",myfunction,xLow,xHigh,6);
   f1->SetNpx(100000);
   f1->SetParameters(scale,mean,sigmaL,sigmaR,alphaL,alphaR);
   f1->SetParNames("constant","mean","sigmaL","sigmaR","alphaL","alphaR");

   TCanvas*canvas = new TCanvas("canvas","",0,0,1200,1000);
   canvas->SetGrid();
   canvas->SetLogy();
   f1->Draw();
}
void myfit(TString hist = "hInvTar_step4_00eta08")
{
   TFile*file = new TFile("../data/saveData.root");
   TH1D*h1 = (TH1D*)file->Get(hist);
   h1->GetXaxis()->SetRangeUser(xLow,xHigh);
   if(!h1) cout << hist << " failed to load!!!" << endl;
   else cout << hist << "loaded." << endl;
   TF1*f1 = (TF1*)gROOT->GetFunction("myfunc");
   f1->SetNpx(100000);
   f1->SetParameters(scale,mean,sigmaL,sigmaR,alphaL,alphaR);
   h1->Draw("pe");
   h1->Fit("myfunc","RP");
}
void allHists()
{
 ifstream inputHists("../data/histList.txt");
 TString h;
 while(true){
  inputHists >> h;
  if(inputHists.eof()) break;
  myfit(h);
 }
 inputHists.close();
}
