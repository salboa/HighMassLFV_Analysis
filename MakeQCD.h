/* ROOT includes */
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TFile.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TColor.h>
#include <TMath.h>
#include <TLatex.h>
#include <TF1.h>
/* C++ includes */
#include "iostream"

void MakeQCD(int lfvType,    std::string charge, bool addSys,    bool useBjet,
	     bool isttCR,    bool useSmooth,     bool isFFcat,   bool isBlind,
	     bool isRevDphi, bool usePtRw,       bool scaleWjet, bool isSherpa,
	     std::string nProngs);

void MakeQCD_emu(std::string sysVar, std::string Dir, bool useBjet,
		 bool useSmooth, bool isBlind, bool usePtRw);

void MakeQCD_tau(std::string sysVar, std::string lfvType, std::string Dir,
		 std::string charge, bool useBjet,        bool isFFcat,
		 bool isBlind,       bool usePtRw,        bool scaleWjet,
		 std::string nProngs);

double WjetTranFact(TFile *SR, TFile *CR);

void CopyFromNominal(std::string Dir, std::string lfvType,
		     bool useBjet, bool isBlind);

TH1F *ChangeShape(TH1F*qcd);

TFile *m_out, *m_qcdemu;

bool m_debug;
