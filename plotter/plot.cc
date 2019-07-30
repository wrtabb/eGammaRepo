#include "../include/EgRegAnalyzer.hh"
#include "../include/NtupleLocations.h"

void plot()
{
 //gROOT->SetBatch(true);
 VarName var;
 for(int i=0;i<4;i++){
  if(i == 1) continue;
  TString step = "step";
  step += i+1;
  EgRegAnalyzer*egReg = new EgRegAnalyzer(step);
  egReg->Get1DPlots(step,ENERGY_CORRECTION);
  egReg->Get1DPlots(step,ENERGY_TARGET);
 }
}
