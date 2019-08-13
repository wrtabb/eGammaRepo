#include "../include/VariableHandler.hh"

const TString VariableHandler::varNames[] = {
 "undefined",
 "eta",
 "absEta",
 "invTar",
 "invTarCorr",
 "mean",
 "sigma"
};
const TString VariableHandler::varLatexNames[] = {
 "undefined",
 "#eta",
 "#cbar#eta#cbar",
 "E_{raw}/E_{true}",
 "corrected E_{raw}/E_{true}",
 "mean",
 "#sigma"
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
  float bin = -2.5;
  float dBin = 0.1;
  const int numbins = 52;
  for(int i=0;i<numbins;i++){
   rangeLimits.push_back(bin);
   bin += dBin;
  }
 }
 else if(varType == ABS_ETA){
  float bin = 0.0;
  float dBin = 0.1;
  const int numbins = 27;
  for(int i=0;i<numbins;i++){
   rangeLimits.push_back(bin);
   bin += dBin;
  }
 }
 else if(varType == INV_TAR || varType == INV_TAR_CORR){
  float bin = 0.65;
  float dBin = 0.005;
  const int numbins = 92;
  for(int i=0;i<numbins;i++){
   rangeLimits.push_back(bin);
   bin += dBin;
  }
 }
 else if(varType == MEAN){
  float bin = 0.0;
  float dBin = 0.05;
  const int numbins = 41;
  for(int i=0;i<numbins;i++){
   rangeLimits.push_back(bin);
   bin += dBin;
  }
 }
 else if(varType == SIGMA){
  float bin = 0.0;
  float dBin = 0.01;
  const int numbins = 50;
  for(int i=0;i<numbins;i++){
   rangeLimits.push_back(bin);
   bin += dBin;
  }
 }
 nBins = GetNRanges();
}

VariableHandler::~VariableHandler()
{
}

std::vector<float> VariableHandler::GetRangeLimits()
{
 return rangeLimits;
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

//-----Get upper and lower boundaries-----//
float VariableHandler::GetLowRange()
{
 return rangeLimits.at(0);
}

float VariableHandler::GetHighRange()
{
 return rangeLimits.at(nBins);
}

bool VariableHandler::InRange(float var)
{
 bool result = true;
 if(var<rangeLimits.at(0) || var>rangeLimits.at(nBins)) result=false;
 return result;
}

int VariableHandler::GetRangeIndex(float var)
{
 int result = -1;
 for(int i=0;i<nBins;i++){
  if(var>=rangeLimits.at(i) && var < rangeLimits.at(i+1)){
   result = i;
   break;
  }
 }
 return result;
}

float VariableHandler::GetRangeLeft(float var)
{
 float result = -1e9;
 if(InRange(var)){
  result=rangeLimits.at(GetRangeIndex(var));
 }
 return result;
}

float VariableHandler::GetRangeRight(float var)
{
 float result = 1e9;
 if(InRange(var)){
  result = rangeLimits.at(GetRangeIndex(var)+1);
 }
 return result;
}
