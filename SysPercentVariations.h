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
#include <iostream>

void SysPercentVariations(int LFVtype,   std::string Htype, bool useBjet,
			  bool isBlind,  bool isttCR,       bool isRevDphi,
			  bool isSherpa, bool isSignal,     bool rmAbs);

void SysPercentVariations(bool useBjet, bool isBlind, bool isttCR,
			  bool isSherpa);

bool m_debug;
