#include "VariableHandler.hh"

const TString VariableHandler::varNames[] = {
 "undefined",
 "eta",
 "absEta",
 "invTar",
 "invTarCorr",
 "mean"
};
const TString VariableHandler::varLatexNames[] = {
 "undefined",
 "#eta",
 "#cbar#eta#cbar",
 "E_{raw}/E_{true}",
 "corrected E_{raw}/E_{true}",
 "mean"
};

VariableHandler::VariableHandler(VarType varType)
{
 varName = varNames[varType];
 varTitle = varLatexNames[varType];

 if(varType == UNDEF){
  rangeLimits = {};
  return;
 }
 else if(varType == ETA){
  rangeLimits = {-2.5,-2.0,-1.5,-1.0,-0.5,0.0,0.5,1.0,1.5,2.0,2.5};
 }
 else if(varType == ABS_ETA){
  rangeLimits = {0.0,0.5,1.0,1.5,2.0,2.5};
 }
 else if(varType == INV_TAR || varType == INV_TAR_CORR){
  rangeLimits = {0.65, 0.655, 0.66, 0.665, 0.67, 0.675, 0.68, 0.685, 0.69, 0.695, 
                 0.70, 0.705, 0.71, 0.715, 0.72, 0.725, 0.73, 0.735, 0.74, 0.745, 
                 0.75, 0.755, 0.76, 0.765, 0.77, 0.775, 0.78, 0.785, 0.79, 0.795, 
                 0.80, 0.805, 0.81, 0.815, 0.82, 0.825, 0.83, 0.835, 0.84, 0.845, 
                 0.85, 0.855, 0.86, 0.865, 0.87, 0.875, 0.88, 0.885, 0.89, 0.895, 
                 0.90, 0.905, 0.91, 0.915, 0.92, 0.925, 0.93, 0.935, 0.94, 0.945, 
                 0.95, 0.955, 0.96, 0.965, 0.97, 0.975, 0.98, 0.985, 0.99, 0.995, 
                 1.00, 1.005, 1.01, 1.015, 1.02, 1.025, 1.03, 1.035, 1.04, 1.045, 
                 1.05, 1.055, 1.06, 1.065, 1.07, 1.075, 1.08, 1.085, 1.09, 1.095, 
                 1.10};
 }
 else if(varType == MEAN){
  rangeLimits = {0.0,0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,
                 0.7,0.75,0.8,0.85,0.9,0.95,1.0,1.05,1.1,1.15,1.2,1.25,1.3,1.35,
                 1.4,1.45,1.5,1.55,1.6,1.65,1.7,1.75,1.8,1.85,1.9,1.95,2.0};
 }
 nBins = GetNRanges();
}

VariableHandler::~VariableHandler()
{
}

//-----Find how many bins there are-----//
int VariableHandler::GetNRanges()
{
 return rangeLimits.size()-1;
}
//-----Get variable name-----//
TString VariableHandler::GetVarName()
{
 return varName;
}

//-----Get variable title (in Latex)-----//
TString VariableHandler::GetVarTitle()
{
 return varTitle;
}
//-----Get lower boundary for plot-----//
float VariableHandler::GetLowRange()
{
 return rangeLimits.at(0);
}

//-----Get upper boundary for plot-----//
float VariableHandler::GetHighRange()
{
 return rangeLimits.at(nBins);
}
std::vector<float> VariableHandler::GetRangeLimits()
{
return rangeLimits;
}
