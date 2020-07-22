/* ROOT includes */
#include <TH1.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TROOT.h>
#include <TLatex.h>

/* C++ includes */
#include "iostream"
#include "iomanip"

void GetSysValues(int LFVtype, bool useBjet, bool useAllSys);

bool m_debug;
