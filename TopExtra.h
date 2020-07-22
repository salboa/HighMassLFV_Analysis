/* ROOT includes */
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TFile.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TColor.h>
/* C++ includes */
#include <sys/stat.h>

void TopExtra(int LFVtype, bool useBjet, bool exclScale,
	      bool addSys, bool addPtRw);

void CheckOutDir(std::string m_OutDir);

std::vector<std::string> m_dirs;
std::string m_tmpOutDir;
