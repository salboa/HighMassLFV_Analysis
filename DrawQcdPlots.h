/* ROOT includes */
#include <TH1F.h>
#include <THStack.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TApplication.h>
#include <TRint.h>
/* C++ includes */
#include "iostream"
#include "sstream"
#include "iomanip"
#include "vector"
/* Other includes */
#include "Utils.h"

void CRplots(std::string lfvType, std::string Htype, std::string charge,
	     std::string Reg, bool isFFcat, bool useBjet, bool isttCR,
	     bool isRevDphi, bool useRatio);

void DeriveKfactor(std::string lfvType, std::string Htype, bool isFFcat,
		   bool useBjet,        bool isttCR,       bool isRevDphi,
		   bool useNoPtCut,     bool doProngs);

void DrawShape(std::string lfvType, std::string Htype, bool useBjet,
	       bool isttCR, bool isRevDphi);

void DeriveSys(std::string lfvType, std::string Htype, bool useBjet,
	       bool isttCR, bool isRevDphi);

void SysElecMuon(bool useBjet);

void SysLepTau(std::string lfvType, std::string Htype, std::string Dir);

void CompareFakeCategories(std::string lfvType, bool useBjet,
			   bool isttCR, bool isRevDphi);

void CompareProngs(std::string lfvType, bool useBjet);

std::vector<TH1F*> RetrieveHistos(std::string lfvType, std::string Htype,
				  std::string Fname);

TH1F* GetMultijet(std::vector<TH1F*> vecH, std::string RegName);

void SetRatioPlot(TH1F *ratio, Int_t color=kBlack, Int_t marker=20,
		  bool isRatio=true);

/* members */
std::vector<TH1F*> m_vecH;
bool m_debug;
