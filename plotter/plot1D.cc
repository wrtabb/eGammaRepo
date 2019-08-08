#include "VariableHandler.hh"
#include "EgRegAnalyzer.hh"
#include <TH1D.h>


void plot1D(VarType var,TString step="step4")
{
 EgRegAnalyzer*egReg = new EgRegAnalyzer(step);
 egReg->LoadTree();
 egReg->InitBranches();

 egReg->Plot1DHist(var);
}

