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
#include "sstream"
#include "iomanip"
#include "vector"
/* Other includes */
#include "Utils.h"

void kMJ_Fits(std::string lfvType, bool useBjet);

/* members */
bool m_debug;
