#ifndef VariableHandler_HH
#define VariableHandler_HH
#include <TString.h>

enum VarType{
 UNDEF = 0,
 ETA,
 ABS_ETA,
 INV_TAR,
 INV_TAR_CORR
};

class VariableHandler
{
public:
 static const TString varNames[];
 static const TString varLatexNames[];
 int nBins;
 TString varName;
 TString varTitle;

 VariableHandler(VarType varType = UNDEF);
 ~VariableHandler();

 int GetNRanges(); 
 float GetLowRange();
 float GetHighRange();
 std::vector<float> GetRangeLimits();

 TString GetVarName();
 TString GetVarTitle();
 std::vector<float> rangeLimits;
};

#endif