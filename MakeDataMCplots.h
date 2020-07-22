/* ROOT includes */
#include <TH1F.h>
#include <THStack.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TLine.h>
#include <TMath.h>
#include <TArrow.h>
#include <TGraphAsymmErrors.h>
#include <TApplication.h>
#include <TRint.h>

/* C++ includes */
#include "iostream"
#include "vector"
#include "sstream"
#include "iomanip"

/* Other Includes */
#include "Utils.h"

TLine* DefineHorizLine(Double_t Yval, Double_t Xmin, Double_t Xmax);

void PrintYieldRegions(std::vector<TH1F*> Plots, std::vector<TH1F*> Systs);

void PrintYields(std::vector<TH1F*> Plots, std::vector<TH1F*> Systs);

TGraphAsymmErrors* myTGraphErrorsDivide(TGraphAsymmErrors* g1,
					TGraphAsymmErrors* g2);

TGraphAsymmErrors* PrepareRatio(TH1F *data, TH1F *MC, bool isData);

std::pair<double,double> FindPlotRange(std::string LFVtype, std::string Htype,
				       bool isttCR, bool isRevDphi, TH1F *h);

double FindMaxValue(TH1F* h, double Val);

double FindMinValue(TH1F* h, double Val);

void SetPlotRange(TH1F* h, double Xmin, double Xmax);

void MakePlots(int LFVtype, std::string Htype, std::string Dir,
	       std::string SigMp);

std::string GetOutName(std::string Htype);

TLegend* CreateFillLegend(int LFVtype, std::vector<TH1F*> Plots,
			  TGraphAsymmErrors *Band);

/* Global Variables */
bool m_useSysBand;
bool m_addStatInBand;
bool m_useData;
bool m_showQCD;
bool m_isBlindData;
bool m_isBlind;
bool m_isttCR;
bool m_isRevDphi;
bool m_isSherpa;
bool m_useBjet;
bool m_useErrOnBkg;
bool m_usePtRw;
bool m_useSignal;
bool m_useSmooth;

