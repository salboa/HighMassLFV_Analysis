/* ROOT includes */
#include <TH1F.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TApplication.h>
#include <TRint.h>
#include <TF1.h>
#include <TVirtualFitter.h>
/* C++ includes */
#include "iostream"
#include "fstream"
#include "iomanip"
#include "vector"
#include "set"
/* Other includes */
#include "Utils.h"

void DataEvtListScan(std::string lfvType, bool useBjet,
		     std::string list1,   std::string list2);

void DrawPlot(std::string lfvType, bool useBjet);

void SetRatioPlot(TH1F *ratio, Int_t color=kBlack, Int_t marker=20,
		  bool isRatio=true);

/* members */
bool m_debug;
