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

void MergeContributions(int LFVtype, bool addSys, bool isttCR, bool useBjet,
			bool isBlind, bool isRevDphi, bool usePtRw,
			bool isSherpa, bool useSmooth);

bool m_debug;
