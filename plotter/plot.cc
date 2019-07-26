#include "../include/EgRegAnalyzer.hh"
#include "../include/NtupleLocations.h"

void plot()
{
 VarName var = ENERGY_TARGET;

 for(int i=0;i<4;i++){
  if(i == 1) continue;
  TString step = "step";
  step += i+1;
  EgRegAnalyzer*egReg = new EgRegAnalyzer(step,var);
  egReg->GetPlots(step,var);
 }
}
