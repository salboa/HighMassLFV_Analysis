#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TFile.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TColor.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TMath.h>
#include <TGraphErrors.h>
#include <TApplication.h>
#include <TRint.h>
/* C++ includes */
#include "iostream"
#include "set"
/* Other includes */
#include "Utils.h"

void SetHistoStyle(TH1F *h, std::vector<std::string> PeriodsName);

TLegend* MakeLegend(std::vector<TGraphErrors*> Histos);

void DataPeriodPlot(int lfvType, bool useBjet, bool divLumi);

std::vector<TGraphErrors*> FillHistAndUnc(Int_t Bins, double SystErr,
					  std::vector<std::string> PeriodsName,
					  std::map<std::string, double> DataN,
					  std::map<std::string, double> MCExp,
					  TH1F *hdata);

bool m_debug;
