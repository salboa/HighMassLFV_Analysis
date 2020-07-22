/* ROOT includes */
#include <TH1.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TROOT.h>
#include <TApplication.h>
#include <TRint.h>
/* C++ includes */
#include <iostream>
/* Other includes */
#include "Utils.h"

void SetLegendStyle(TLegend *leg);

void SetHistoOption(TH1F *h);

void MakeSystPlots(int LFVtype, std::string HType, bool useBjet,
		   bool isBlind, bool useOrig, bool useAllSys);

void CompareProcSys(int LFVtype, std::string HType, std::string sysVar,
		    bool useBjet, bool isBlind);

