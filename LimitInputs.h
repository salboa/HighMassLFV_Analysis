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

void LimitInputs(int LFVtype,    bool useBjet,   std::string process,
		 bool useSmooth, bool sigShapes, bool rmAbs,
		 bool useVisMass);

void SignalShapes(std::string Dir,     std::string lfvType,
		  std::string process, std::vector<std::string> sysVar);
