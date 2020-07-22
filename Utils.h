/* ROOT includes */
#include <TLegend.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TLatex.h>
#include <TStyle.h>
#include <TROOT.h>
/* C++ includes */
#include "iostream"

TCanvas *CreateCanvas(std::string name);

TPad *CreateTopPad(std::string name, std::string Htype);

TPad *CreateBottomPad(std::string name, std::string Htype);

TLegend *CreateLegend(Double_t v1, Double_t v2, Double_t v3, Double_t v4);

void SetATLASStyle(bool useStat);

void DrawLabels(bool hasRatio, bool isConf, bool isPaper,
		bool is2015,   bool is2016, bool noLumi);

void DrawChannel(std::string lfvType, bool hasRatio, bool useBjet);
