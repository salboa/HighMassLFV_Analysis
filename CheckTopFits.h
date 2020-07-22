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
#include <sys/stat.h>
#include "Utils.h"

void CheckTopFits(int LFVtype, bool useBjet, bool addSys);

void CheckOutDir(std::string m_OutDir);

void DrawDistro(std::string sysVar, std::string lfvType, bool useBjet);

std::vector<std::string> m_dirs;
std::string m_tmpOutDir;

TH1F *Input, *Fit, *ratio, *ratioLine;
TCanvas *cs;
TPad *p1, *p2;
