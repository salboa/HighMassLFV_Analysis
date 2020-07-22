/* ROOT includes */
#include <TH1F.h>
#include <THStack.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TStyle.h>
#include <TLine.h>
#include <TROOT.h>
#include <TGraphAsymmErrors.h>
#include <TApplication.h>
#include <TRint.h>
/* C++ includes */
#include "iostream"
#include "sstream"
#include "iomanip"
#include "vector"
/* Other includes */
#include "Utils.h"

void DerivePtRw(int lfvType, bool useBjet, bool isBlind, bool isttCR,
		bool useSherpa, bool useRwted, bool useSignal, bool applyWgt);

void CompareMass(std::string lfvType, bool useBjet);

void SetRatio(TH1F* ratio, int color);

/* members */
std::vector<double> m_data;
std::vector<double> m_top;
std::vector<double> m_dy;
std::vector<double> m_db;
std::vector<double> m_mjet;
std::vector<double> m_edge;
bool m_verbose;
bool m_debug;
