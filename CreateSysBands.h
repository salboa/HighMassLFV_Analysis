/* ROOT includes */
#include <TH1.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TROOT.h>
#include <TGraphAsymmErrors.h>
#include <TLatex.h>

/* C++ includes */
#include <iostream>

void CreateSysBands(int LFVtype, bool useBjet, bool isBlind, bool isttCR,
		    bool isRevDphi, bool isSherpa, std::string Process, bool addStatUnc);

void CreateSysBands(bool useBjet, bool isBlind, bool isttCR, bool isSherpa);

bool m_debug;
