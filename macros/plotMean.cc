#include "../include/VariableHandler.hh"
#include "../include/EgRegAnalyzer.hh"
#include <TH1D.h>


void plotMean()
{
 EgRegAnalyzer*egReg = new EgRegAnalyzer("step4");
 egReg->LoadTree();
 egReg->InitBranches();
 egReg->Plot2DHist(ETA,MEAN,"step4");
}

