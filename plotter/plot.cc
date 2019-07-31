#include "../include/EgRegAnalyzer.hh"
#include "../include/NtupleLocations.h"

//I set a default step at step4 because this is the final step from regression
//If you want to run on any other step, just define it when calling the function
//Define step = "all" to loop over all steps
//This was written to plot one variable, if plotting several, it loops over them
//separately and is inefficient

void plot(TString step = "step4")
{

 if(step=="all"){
  for(int i=0;i<4;i++){
   if(i == 1) continue;
   TString step = "step";
   step += i+1;
   EgRegAnalyzer*egReg = new EgRegAnalyzer(step);
   egReg->Get1DPlots(step,ENERGY_TARGET_INV);
   egReg->Get1DPlots(step,ENERGY_TARGET_CORR_INV);
   egReg->PlotCruijff(step);
  }
 }
  EgRegAnalyzer*egReg = new EgRegAnalyzer(step);
  egReg->PlotCruijff(step);
  egReg->Get1DPlots(step,ENERGY_TARGET_INV);
  egReg->Get1DPlots(step,ENERGY_TARGET_CORR_INV);
}
