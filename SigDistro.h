#include <TROOT.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TF1.h>
#include <TFile.h>
#include <TApplication.h>
#include <TRint.h>
/* C++ includes */
#include <iomanip>
#include <iostream>
/* Other includes */
#include "Utils.h"

void DefineGlobals(int lfvType);
void SigDistro(int LFVtype, bool useBjet, bool normalize);
void SigSysDistro(int LFVtype, bool useBjet, bool normalize, std::string model);
void SetHistoStyle(TH1F* hV, int i, double Xmin, bool normalize, bool forceStyle=false);
std::vector<TH1F*> GetHistos(std::string Mp, int lfvType);
TH1F* MakeRatio(TH1F* Nom, TH1F *Var);
void SetRatioPlot(TH1F *ratio, int i, double Xmin);
  
bool m_debug;
std::vector<std::string> sysVar, name;
TFile *dist;
std::vector<int> Cols, Lin;
