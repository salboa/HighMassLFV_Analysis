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

void TopScale(int LFVtype, bool useBjet);

void CheckOutDir(std::string m_OutDir);

void MakeRatio(TH1F* nominal, TH1F* varied, TH1F* &ratio);

std::vector<std::string> m_dirs;
std::string m_tmpOutDir;
