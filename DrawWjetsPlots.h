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

void DrawShape(std::string lfvType, std::string Htype, bool useBjet);

void DeriveSys(std::string lfvType, std::string Htype, bool useBjet);

void DrawMCcomp(std::string lfvType, std::string Htype, bool useBjet);

void SetRatio(TH1F* ratio, int color);

/* members */
bool m_debug;
Double_t m_xMin;
Double_t m_xMax;
