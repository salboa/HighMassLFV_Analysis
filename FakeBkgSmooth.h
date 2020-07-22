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

void FakeBkgSmooth(std::string chanName, bool useBjet);

/* members */
bool m_debug;
