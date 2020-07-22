/* ROOT includes */
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TFile.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TColor.h>
#include <TLatex.h>
/* C++ includes */
#include "iostream"

void AddContributions(bool useBjet, bool addSys, bool exclTop, bool isttCR,
		      bool isBlind, bool isRevDphi, bool usePtRw,
		      bool isSherpa, int LFVtype, bool useSmooth);
