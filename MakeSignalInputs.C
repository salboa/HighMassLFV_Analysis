#include <TH1F.h>
#include <TH2F.h>
#include <TF1.h>
#include <THStack.h>
#include <TLegend.h>
#include <TFile.h>
#include <TMath.h>
#include <TLine.h>
#include <TGraphAsymmErrors.h>
#include <TCanvas.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

void MakeSignalInputs(std::string lfvType){

  gROOT->LoadMacro("/home/marc/Documents/Physics/preselectionTreeAnalysis/outputLewisDY/NonResStyle/AtlasStyleRatio.C");
  gROOT->LoadMacro("/home/marc/Downloads/atlasstyle-00-03-05/AtlasUtils.C");
  //SetAtlasStyle();
  
  TFile *FILE_emuBackground = TFile::Open("../MergedMassPlots_emu.root","OPEN");
  TFile *FILE_etauBackground = TFile::Open("../MergedMassPlots_etau.root","OPEN");
  TFile *FILE_mutauBackground = TFile::Open("../MergedMassPlots_mutau.root","OPEN");

  TH1D* hmll_data_emu=(TH1D*)FILE_emuBackground->Get("hmll_data");
  TH1D* hmll_data_etau=(TH1D*)FILE_etauBackground->Get("hmll_data");
  TH1D* hmll_data_mutau=(TH1D*)FILE_mutauBackground->Get("hmll_data");
  TH1D* hmll_Nominal_emu=(TH1D*)FILE_emuBackground->Get("hmll_Nominal");
  TH1D* hmll_Nominal_etau=(TH1D*)FILE_etauBackground->Get("hmll_Nominal");
  TH1D* hmll_Nominal_mutau=(TH1D*)FILE_mutauBackground->Get("hmll_Nominal");
  //Zprime+QBH+RPV files
  TFile *emuFile   = TFile::Open("Plots_Nominal_emu_Signals.root"  ,"OPEN");
  //TFile *emuFile   = TFile::Open("Plots_Nominal_emu_Signals_bjet.root"  ,"OPEN");
  TFile *etauFile  = TFile::Open("Plots_Nominal_etau_Signals.root" ,"OPEN");
  TFile *mutauFile = TFile::Open("Plots_Nominal_mutau_Signals.root","OPEN");
  
  TObjArray* SignalObjZprime_emu = new TObjArray();
  TObjArray* SignalObjQBHRS_emu = new TObjArray();
  TObjArray* SignalObjRPV_emu = new TObjArray();

  TObjArray* SignalObjZprime_etau = new TObjArray();
  TObjArray* SignalObjQBHRS_etau = new TObjArray();
  TObjArray* SignalObjRPV_etau = new TObjArray();

  TObjArray* SignalObjZprime_mutau = new TObjArray();
  TObjArray* SignalObjQBHRS_mutau = new TObjArray();
  TObjArray* SignalObjRPV_mutau = new TObjArray();

  // Zprime histograms
  TH1D* Zprime500_emu =(TH1D*)emuFile->Get("hmllCorr_Zprime0500"); 
  TH1D* Zprime600_emu =(TH1D*)emuFile->Get("hmllCorr_Zprime0600"); 
  TH1D* Zprime700_emu =(TH1D*)emuFile->Get("hmllCorr_Zprime0700"); 
  TH1D* Zprime800_emu =(TH1D*)emuFile->Get("hmllCorr_Zprime0800"); 
  TH1D* Zprime900_emu =(TH1D*)emuFile->Get("hmllCorr_Zprime0900"); 
  TH1D* Zprime1000_emu=(TH1D*)emuFile->Get("hmllCorr_Zprime1000");
  TH1D* Zprime1100_emu=(TH1D*)emuFile->Get("hmllCorr_Zprime1100");
  TH1D* Zprime1200_emu=(TH1D*)emuFile->Get("hmllCorr_Zprime1200");
  TH1D* Zprime1300_emu=(TH1D*)emuFile->Get("hmllCorr_Zprime1300");
  TH1D* Zprime1400_emu=(TH1D*)emuFile->Get("hmllCorr_Zprime1400");
  TH1D* Zprime1500_emu=(TH1D*)emuFile->Get("hmllCorr_Zprime1500");
  TH1D* Zprime1600_emu=(TH1D*)emuFile->Get("hmllCorr_Zprime1600");
  TH1D* Zprime1700_emu=(TH1D*)emuFile->Get("hmllCorr_Zprime1700");
  TH1D* Zprime1800_emu=(TH1D*)emuFile->Get("hmllCorr_Zprime1800");
  TH1D* Zprime1900_emu=(TH1D*)emuFile->Get("hmllCorr_Zprime1900");
  TH1D* Zprime2000_emu=(TH1D*)emuFile->Get("hmllCorr_Zprime2000");
  TH1D* Zprime2200_emu=(TH1D*)emuFile->Get("hmllCorr_Zprime2200");
  TH1D* Zprime2400_emu=(TH1D*)emuFile->Get("hmllCorr_Zprime2400");
  TH1D* Zprime2600_emu=(TH1D*)emuFile->Get("hmllCorr_Zprime2600");
  TH1D* Zprime2800_emu=(TH1D*)emuFile->Get("hmllCorr_Zprime2800");
  TH1D* Zprime3000_emu=(TH1D*)emuFile->Get("hmllCorr_Zprime3000");
  TH1D* Zprime3500_emu=(TH1D*)emuFile->Get("hmllCorr_Zprime3500");
  TH1D* Zprime4000_emu=(TH1D*)emuFile->Get("hmllCorr_Zprime4000");
  TH1D* Zprime4500_emu=(TH1D*)emuFile->Get("hmllCorr_Zprime4500");
  TH1D* Zprime5000_emu=(TH1D*)emuFile->Get("hmllCorr_Zprime5000");

  TH1D* Zprime500_etau =(TH1D*)etauFile->Get("hmllCorr_Zprime0500"); 
  TH1D* Zprime600_etau =(TH1D*)etauFile->Get("hmllCorr_Zprime0600"); 
  TH1D* Zprime700_etau =(TH1D*)etauFile->Get("hmllCorr_Zprime0700"); 
  TH1D* Zprime800_etau =(TH1D*)etauFile->Get("hmllCorr_Zprime0800"); 
  TH1D* Zprime900_etau =(TH1D*)etauFile->Get("hmllCorr_Zprime0900"); 
  TH1D* Zprime1000_etau=(TH1D*)etauFile->Get("hmllCorr_Zprime1000");
  TH1D* Zprime1100_etau=(TH1D*)etauFile->Get("hmllCorr_Zprime1100");
  TH1D* Zprime1200_etau=(TH1D*)etauFile->Get("hmllCorr_Zprime1200");
  TH1D* Zprime1300_etau=(TH1D*)etauFile->Get("hmllCorr_Zprime1300");
  TH1D* Zprime1400_etau=(TH1D*)etauFile->Get("hmllCorr_Zprime1400");
  TH1D* Zprime1500_etau=(TH1D*)etauFile->Get("hmllCorr_Zprime1500");
  TH1D* Zprime1600_etau=(TH1D*)etauFile->Get("hmllCorr_Zprime1600");
  TH1D* Zprime1700_etau=(TH1D*)etauFile->Get("hmllCorr_Zprime1700");
  TH1D* Zprime1800_etau=(TH1D*)etauFile->Get("hmllCorr_Zprime1800");
  TH1D* Zprime1900_etau=(TH1D*)etauFile->Get("hmllCorr_Zprime1900");
  TH1D* Zprime2000_etau=(TH1D*)etauFile->Get("hmllCorr_Zprime2000");
  TH1D* Zprime2200_etau=(TH1D*)etauFile->Get("hmllCorr_Zprime2200");
  TH1D* Zprime2400_etau=(TH1D*)etauFile->Get("hmllCorr_Zprime2400");
  TH1D* Zprime2600_etau=(TH1D*)etauFile->Get("hmllCorr_Zprime2600");
  TH1D* Zprime2800_etau=(TH1D*)etauFile->Get("hmllCorr_Zprime2800");
  TH1D* Zprime3000_etau=(TH1D*)etauFile->Get("hmllCorr_Zprime3000");
  TH1D* Zprime3500_etau=(TH1D*)etauFile->Get("hmllCorr_Zprime3500");
  TH1D* Zprime4000_etau=(TH1D*)etauFile->Get("hmllCorr_Zprime4000");
  TH1D* Zprime4500_etau=(TH1D*)etauFile->Get("hmllCorr_Zprime4500");
  TH1D* Zprime5000_etau=(TH1D*)etauFile->Get("hmllCorr_Zprime5000");
  
  TH1D* Zprime500_mutau =(TH1D*)mutauFile->Get("hmllCorr_Zprime0500"); 
  TH1D* Zprime600_mutau =(TH1D*)mutauFile->Get("hmllCorr_Zprime0600"); 
  TH1D* Zprime700_mutau =(TH1D*)mutauFile->Get("hmllCorr_Zprime0700"); 
  TH1D* Zprime800_mutau =(TH1D*)mutauFile->Get("hmllCorr_Zprime0800"); 
  TH1D* Zprime900_mutau =(TH1D*)mutauFile->Get("hmllCorr_Zprime0900"); 
  TH1D* Zprime1000_mutau=(TH1D*)mutauFile->Get("hmllCorr_Zprime1000");
  TH1D* Zprime1100_mutau=(TH1D*)mutauFile->Get("hmllCorr_Zprime1100");
  TH1D* Zprime1200_mutau=(TH1D*)mutauFile->Get("hmllCorr_Zprime1200");
  TH1D* Zprime1300_mutau=(TH1D*)mutauFile->Get("hmllCorr_Zprime1300");
  TH1D* Zprime1400_mutau=(TH1D*)mutauFile->Get("hmllCorr_Zprime1400");
  TH1D* Zprime1500_mutau=(TH1D*)mutauFile->Get("hmllCorr_Zprime1500");
  TH1D* Zprime1600_mutau=(TH1D*)mutauFile->Get("hmllCorr_Zprime1600");
  TH1D* Zprime1700_mutau=(TH1D*)mutauFile->Get("hmllCorr_Zprime1700");
  TH1D* Zprime1800_mutau=(TH1D*)mutauFile->Get("hmllCorr_Zprime1800");
  TH1D* Zprime1900_mutau=(TH1D*)mutauFile->Get("hmllCorr_Zprime1900");
  TH1D* Zprime2000_mutau=(TH1D*)mutauFile->Get("hmllCorr_Zprime2000");
  TH1D* Zprime2200_mutau=(TH1D*)mutauFile->Get("hmllCorr_Zprime2200");
  TH1D* Zprime2400_mutau=(TH1D*)mutauFile->Get("hmllCorr_Zprime2400");
  TH1D* Zprime2600_mutau=(TH1D*)mutauFile->Get("hmllCorr_Zprime2600");
  TH1D* Zprime2800_mutau=(TH1D*)mutauFile->Get("hmllCorr_Zprime2800");
  TH1D* Zprime3000_mutau=(TH1D*)mutauFile->Get("hmllCorr_Zprime3000");
  TH1D* Zprime3500_mutau=(TH1D*)mutauFile->Get("hmllCorr_Zprime3500");
  TH1D* Zprime4000_mutau=(TH1D*)mutauFile->Get("hmllCorr_Zprime4000");
  TH1D* Zprime4500_mutau=(TH1D*)mutauFile->Get("hmllCorr_Zprime4500");
  TH1D* Zprime5000_mutau=(TH1D*)mutauFile->Get("hmllCorr_Zprime5000");

  // QBH Histograms
  TH1D* QBHRS1000_emu=(TH1D*)emuFile->Get("hmllCorr_QBH1000_n1");
  TH1D* QBHRS1500_emu=(TH1D*)emuFile->Get("hmllCorr_QBH1500_n1");
  TH1D* QBHRS2000_emu=(TH1D*)emuFile->Get("hmllCorr_QBH2000_n1");
  TH1D* QBHRS2500_emu=(TH1D*)emuFile->Get("hmllCorr_QBH2500_n1");
  TH1D* QBHRS3000_emu=(TH1D*)emuFile->Get("hmllCorr_QBH3000_n1");
  TH1D* QBHRS3500_emu=(TH1D*)emuFile->Get("hmllCorr_QBH3500_n1");
  TH1D* QBHRS4000_emu=(TH1D*)emuFile->Get("hmllCorr_QBH4000_n1");
  TH1D* QBHRS4500_emu=(TH1D*)emuFile->Get("hmllCorr_QBH4500_n1");
  TH1D* QBHRS5000_emu=(TH1D*)emuFile->Get("hmllCorr_QBH5000_n1");
  TH1D* QBHRS5500_emu=(TH1D*)emuFile->Get("hmllCorr_QBH5500_n1");
  TH1D* QBHRS6000_emu=(TH1D*)emuFile->Get("hmllCorr_QBH6000_n1");

  TH1D* QBHRS1000_etau=(TH1D*)etauFile->Get("hmllCorr_QBH1000_n1");
  TH1D* QBHRS1500_etau=(TH1D*)etauFile->Get("hmllCorr_QBH1500_n1");
  TH1D* QBHRS2000_etau=(TH1D*)etauFile->Get("hmllCorr_QBH2000_n1");
  TH1D* QBHRS2500_etau=(TH1D*)etauFile->Get("hmllCorr_QBH2500_n1");
  TH1D* QBHRS3000_etau=(TH1D*)etauFile->Get("hmllCorr_QBH3000_n1");
  TH1D* QBHRS3500_etau=(TH1D*)etauFile->Get("hmllCorr_QBH3500_n1");
  TH1D* QBHRS4000_etau=(TH1D*)etauFile->Get("hmllCorr_QBH4000_n1");
  TH1D* QBHRS4500_etau=(TH1D*)etauFile->Get("hmllCorr_QBH4500_n1");
  TH1D* QBHRS5000_etau=(TH1D*)etauFile->Get("hmllCorr_QBH5000_n1");
  TH1D* QBHRS5500_etau=(TH1D*)etauFile->Get("hmllCorr_QBH5500_n1");
  TH1D* QBHRS6000_etau=(TH1D*)etauFile->Get("hmllCorr_QBH6000_n1");

  TH1D* QBHRS1000_mutau=(TH1D*)mutauFile->Get("hmllCorr_QBH1000_n1");
  TH1D* QBHRS1500_mutau=(TH1D*)mutauFile->Get("hmllCorr_QBH1500_n1");
  TH1D* QBHRS2000_mutau=(TH1D*)mutauFile->Get("hmllCorr_QBH2000_n1");
  TH1D* QBHRS2500_mutau=(TH1D*)mutauFile->Get("hmllCorr_QBH2500_n1");
  TH1D* QBHRS3000_mutau=(TH1D*)mutauFile->Get("hmllCorr_QBH3000_n1");
  TH1D* QBHRS3500_mutau=(TH1D*)mutauFile->Get("hmllCorr_QBH3500_n1");
  TH1D* QBHRS4000_mutau=(TH1D*)mutauFile->Get("hmllCorr_QBH4000_n1");
  TH1D* QBHRS4500_mutau=(TH1D*)mutauFile->Get("hmllCorr_QBH4500_n1");
  TH1D* QBHRS5000_mutau=(TH1D*)mutauFile->Get("hmllCorr_QBH5000_n1");
  TH1D* QBHRS5500_mutau=(TH1D*)mutauFile->Get("hmllCorr_QBH5500_n1");
  TH1D* QBHRS6000_mutau=(TH1D*)mutauFile->Get("hmllCorr_QBH6000_n1");

  TH1D* RPV500_emu =(TH1D*)emuFile->Get("hmllCorr_SVT0500");
  TH1D* RPV600_emu =(TH1D*)emuFile->Get("hmllCorr_SVT0600");
  TH1D* RPV700_emu =(TH1D*)emuFile->Get("hmllCorr_SVT0700");
  TH1D* RPV800_emu =(TH1D*)emuFile->Get("hmllCorr_SVT0800");
  TH1D* RPV900_emu =(TH1D*)emuFile->Get("hmllCorr_SVT0900");
  TH1D* RPV1000_emu=(TH1D*)emuFile->Get("hmllCorr_SVT1000");
  TH1D* RPV1100_emu=(TH1D*)emuFile->Get("hmllCorr_SVT1100");
  TH1D* RPV1200_emu=(TH1D*)emuFile->Get("hmllCorr_SVT1200");
  TH1D* RPV1300_emu=(TH1D*)emuFile->Get("hmllCorr_SVT1300");
  TH1D* RPV1400_emu=(TH1D*)emuFile->Get("hmllCorr_SVT1400");
  TH1D* RPV1500_emu=(TH1D*)emuFile->Get("hmllCorr_SVT1500");
  TH1D* RPV1600_emu=(TH1D*)emuFile->Get("hmllCorr_SVT1600");
  TH1D* RPV1700_emu=(TH1D*)emuFile->Get("hmllCorr_SVT1700");
  TH1D* RPV1800_emu=(TH1D*)emuFile->Get("hmllCorr_SVT1800");
  TH1D* RPV1900_emu=(TH1D*)emuFile->Get("hmllCorr_SVT1900");
  TH1D* RPV2000_emu=(TH1D*)emuFile->Get("hmllCorr_SVT2000");
  TH1D* RPV2200_emu=(TH1D*)emuFile->Get("hmllCorr_SVT2200");
  TH1D* RPV2400_emu=(TH1D*)emuFile->Get("hmllCorr_SVT2400");
  TH1D* RPV2600_emu=(TH1D*)emuFile->Get("hmllCorr_SVT2600");
  TH1D* RPV2800_emu=(TH1D*)emuFile->Get("hmllCorr_SVT2800");
  TH1D* RPV3000_emu=(TH1D*)emuFile->Get("hmllCorr_SVT3000");
  TH1D* RPV3500_emu=(TH1D*)emuFile->Get("hmllCorr_SVT3500");
  TH1D* RPV4000_emu=(TH1D*)emuFile->Get("hmllCorr_SVT4000");
  TH1D* RPV4500_emu=(TH1D*)emuFile->Get("hmllCorr_SVT4500");
  TH1D* RPV5000_emu=(TH1D*)emuFile->Get("hmllCorr_SVT5000");

  TH1D* RPV500_etau =(TH1D*)etauFile->Get("hmllCorr_SVT0500");
  TH1D* RPV600_etau =(TH1D*)etauFile->Get("hmllCorr_SVT0600");
  TH1D* RPV700_etau =(TH1D*)etauFile->Get("hmllCorr_SVT0700");
  TH1D* RPV800_etau =(TH1D*)etauFile->Get("hmllCorr_SVT0800");
  TH1D* RPV900_etau =(TH1D*)etauFile->Get("hmllCorr_SVT0900");
  TH1D* RPV1000_etau=(TH1D*)etauFile->Get("hmllCorr_SVT1000");
  TH1D* RPV1100_etau=(TH1D*)etauFile->Get("hmllCorr_SVT1100");
  TH1D* RPV1200_etau=(TH1D*)etauFile->Get("hmllCorr_SVT1200");
  TH1D* RPV1300_etau=(TH1D*)etauFile->Get("hmllCorr_SVT1300");
  TH1D* RPV1400_etau=(TH1D*)etauFile->Get("hmllCorr_SVT1400");
  TH1D* RPV1500_etau=(TH1D*)etauFile->Get("hmllCorr_SVT1500");
  TH1D* RPV1600_etau=(TH1D*)etauFile->Get("hmllCorr_SVT1600");
  TH1D* RPV1700_etau=(TH1D*)etauFile->Get("hmllCorr_SVT1700");
  TH1D* RPV1800_etau=(TH1D*)etauFile->Get("hmllCorr_SVT1800");
  TH1D* RPV1900_etau=(TH1D*)etauFile->Get("hmllCorr_SVT1900");
  TH1D* RPV2000_etau=(TH1D*)etauFile->Get("hmllCorr_SVT2000");
  TH1D* RPV2200_etau=(TH1D*)etauFile->Get("hmllCorr_SVT2200");
  TH1D* RPV2400_etau=(TH1D*)etauFile->Get("hmllCorr_SVT2400");
  TH1D* RPV2600_etau=(TH1D*)etauFile->Get("hmllCorr_SVT2600");
  TH1D* RPV2800_etau=(TH1D*)etauFile->Get("hmllCorr_SVT2800");
  TH1D* RPV3000_etau=(TH1D*)etauFile->Get("hmllCorr_SVT3000");
  TH1D* RPV3500_etau=(TH1D*)etauFile->Get("hmllCorr_SVT3500");
  TH1D* RPV4000_etau=(TH1D*)etauFile->Get("hmllCorr_SVT4000");
  TH1D* RPV4500_etau=(TH1D*)etauFile->Get("hmllCorr_SVT4500");
  TH1D* RPV5000_etau=(TH1D*)etauFile->Get("hmllCorr_SVT5000");
  
  TH1D* RPV500_mutau =(TH1D*)mutauFile->Get("hmllCorr_SVT0500");
  TH1D* RPV600_mutau =(TH1D*)mutauFile->Get("hmllCorr_SVT0600");
  TH1D* RPV700_mutau =(TH1D*)mutauFile->Get("hmllCorr_SVT0700");
  TH1D* RPV800_mutau =(TH1D*)mutauFile->Get("hmllCorr_SVT0800");
  TH1D* RPV900_mutau =(TH1D*)mutauFile->Get("hmllCorr_SVT0900");
  TH1D* RPV1000_mutau=(TH1D*)mutauFile->Get("hmllCorr_SVT1000");
  TH1D* RPV1100_mutau=(TH1D*)mutauFile->Get("hmllCorr_SVT1100");
  TH1D* RPV1200_mutau=(TH1D*)mutauFile->Get("hmllCorr_SVT1200");
  TH1D* RPV1300_mutau=(TH1D*)mutauFile->Get("hmllCorr_SVT1300");
  TH1D* RPV1400_mutau=(TH1D*)mutauFile->Get("hmllCorr_SVT1400");
  TH1D* RPV1500_mutau=(TH1D*)mutauFile->Get("hmllCorr_SVT1500");
  TH1D* RPV1600_mutau=(TH1D*)mutauFile->Get("hmllCorr_SVT1600");
  TH1D* RPV1700_mutau=(TH1D*)mutauFile->Get("hmllCorr_SVT1700");
  TH1D* RPV1800_mutau=(TH1D*)mutauFile->Get("hmllCorr_SVT1800");
  TH1D* RPV1900_mutau=(TH1D*)mutauFile->Get("hmllCorr_SVT1900");
  TH1D* RPV2000_mutau=(TH1D*)mutauFile->Get("hmllCorr_SVT2000");
  TH1D* RPV2200_mutau=(TH1D*)mutauFile->Get("hmllCorr_SVT2200");
  TH1D* RPV2400_mutau=(TH1D*)mutauFile->Get("hmllCorr_SVT2400");
  TH1D* RPV2600_mutau=(TH1D*)mutauFile->Get("hmllCorr_SVT2600");
  TH1D* RPV2800_mutau=(TH1D*)mutauFile->Get("hmllCorr_SVT2800");
  TH1D* RPV3000_mutau=(TH1D*)mutauFile->Get("hmllCorr_SVT3000");
  TH1D* RPV3500_mutau=(TH1D*)mutauFile->Get("hmllCorr_SVT3500");
  TH1D* RPV4000_mutau=(TH1D*)mutauFile->Get("hmllCorr_SVT4000");
  TH1D* RPV4500_mutau=(TH1D*)mutauFile->Get("hmllCorr_SVT4500");
  TH1D* RPV5000_mutau=(TH1D*)mutauFile->Get("hmllCorr_SVT5000");

  // Calculate Ae
  double AccZprime1_emu  = Zprime500_emu->GetEntries() /20000.0;
  double AccZprime2_emu  = Zprime600_emu->GetEntries() /20000.0;
  double AccZprime3_emu  = Zprime700_emu->GetEntries() /20000.0;
  double AccZprime4_emu  = Zprime800_emu->GetEntries() /20000.0;
  double AccZprime5_emu  = Zprime900_emu->GetEntries() /20000.0; 
  double AccZprime6_emu  = Zprime1000_emu->GetEntries()/18000.0;
  double AccZprime7_emu  = Zprime1100_emu->GetEntries()/20000.0;
  double AccZprime8_emu  = Zprime1200_emu->GetEntries()/20000.0;
  double AccZprime9_emu  = Zprime1300_emu->GetEntries()/20000.0;
  double AccZprime10_emu = Zprime1400_emu->GetEntries()/20000.0;
  double AccZprime11_emu = Zprime1500_emu->GetEntries()/20000.0; 
  double AccZprime12_emu = Zprime1600_emu->GetEntries()/20000.0;
  double AccZprime13_emu = Zprime1700_emu->GetEntries()/20000.0;
  double AccZprime14_emu = Zprime1800_emu->GetEntries()/20000.0;
  double AccZprime15_emu = Zprime1900_emu->GetEntries()/20000.0;
  double AccZprime16_emu = Zprime2000_emu->GetEntries()/20000.0; 
  double AccZprime17_emu = Zprime2200_emu->GetEntries()/20000.0;
  double AccZprime18_emu = Zprime2400_emu->GetEntries()/20000.0;
  double AccZprime19_emu = Zprime2600_emu->GetEntries()/20000.0;
  double AccZprime20_emu = Zprime2800_emu->GetEntries()/20000.0;
  double AccZprime21_emu = Zprime3000_emu->GetEntries()/20000.0; 
  double AccZprime22_emu = Zprime3500_emu->GetEntries()/20000.0;
  double AccZprime23_emu = Zprime4000_emu->GetEntries()/20000.0;
  double AccZprime24_emu = Zprime4500_emu->GetEntries()/20000.0;
  double AccZprime25_emu = Zprime5000_emu->GetEntries()/18000.0;

  double AccZprime1_etau  = Zprime500_etau->GetEntries() /20000.0;
  double AccZprime2_etau  = Zprime600_etau->GetEntries() /20000.0;
  double AccZprime3_etau  = Zprime700_etau->GetEntries() /20000.0;
  double AccZprime4_etau  = Zprime800_etau->GetEntries() /20000.0;
  double AccZprime5_etau  = Zprime900_etau->GetEntries() /20000.0; 
  double AccZprime6_etau  = Zprime1000_etau->GetEntries()/18000.0;
  double AccZprime7_etau  = Zprime1100_etau->GetEntries()/20000.0;
  double AccZprime8_etau  = Zprime1200_etau->GetEntries()/20000.0;
  double AccZprime9_etau  = Zprime1300_etau->GetEntries()/20000.0;
  double AccZprime10_etau = Zprime1400_etau->GetEntries()/20000.0;
  double AccZprime11_etau = Zprime1500_etau->GetEntries()/19000.0; 
  double AccZprime12_etau = Zprime1600_etau->GetEntries()/20000.0;
  double AccZprime13_etau = Zprime1700_etau->GetEntries()/20000.0;
  double AccZprime14_etau = Zprime1800_etau->GetEntries()/20000.0;
  double AccZprime15_etau = Zprime1900_etau->GetEntries()/20000.0;
  double AccZprime16_etau = Zprime2000_etau->GetEntries()/18000.0; 
  double AccZprime17_etau = Zprime2200_etau->GetEntries()/20000.0;
  double AccZprime18_etau = Zprime2400_etau->GetEntries()/20000.0;
  double AccZprime19_etau = Zprime2600_etau->GetEntries()/20000.0;
  double AccZprime20_etau = Zprime2800_etau->GetEntries()/18000.0;
  double AccZprime21_etau = Zprime3000_etau->GetEntries()/20000.0; 
  double AccZprime22_etau = Zprime3500_etau->GetEntries()/20000.0;
  double AccZprime23_etau = Zprime4000_etau->GetEntries()/18000.0;
  double AccZprime24_etau = Zprime4500_etau->GetEntries()/20000.0;
  double AccZprime25_etau = Zprime5000_etau->GetEntries()/20000.0;

  double AccZprime1_mutau  = Zprime500_mutau->GetEntries() /20000.0;
  double AccZprime2_mutau  = Zprime600_mutau->GetEntries() /20000.0;
  double AccZprime3_mutau  = Zprime700_mutau->GetEntries() /20000.0;
  double AccZprime4_mutau  = Zprime800_mutau->GetEntries() /20000.0;
  double AccZprime5_mutau  = Zprime900_mutau->GetEntries() /20000.0; 
  double AccZprime6_mutau  = Zprime1000_mutau->GetEntries()/20000.0;
  double AccZprime7_mutau  = Zprime1100_mutau->GetEntries()/20000.0;
  double AccZprime8_mutau  = Zprime1200_mutau->GetEntries()/19000.0;
  double AccZprime9_mutau  = Zprime1300_mutau->GetEntries()/20000.0;
  double AccZprime10_mutau = Zprime1400_mutau->GetEntries()/17000.0;
  double AccZprime11_mutau = Zprime1500_mutau->GetEntries()/20000.0; 
  double AccZprime12_mutau = Zprime1600_mutau->GetEntries()/20000.0;
  double AccZprime13_mutau = Zprime1700_mutau->GetEntries()/20000.0;
  double AccZprime14_mutau = Zprime1800_mutau->GetEntries()/20000.0;
  double AccZprime15_mutau = Zprime1900_mutau->GetEntries()/19000.0;
  double AccZprime16_mutau = Zprime2000_mutau->GetEntries()/20000.0; 
  double AccZprime17_mutau = Zprime2200_mutau->GetEntries()/20000.0;
  double AccZprime18_mutau = Zprime2400_mutau->GetEntries()/20000.0;
  double AccZprime19_mutau = Zprime2600_mutau->GetEntries()/20000.0;
  double AccZprime20_mutau = Zprime2800_mutau->GetEntries()/20000.0;
  double AccZprime21_mutau = Zprime3000_mutau->GetEntries()/20000.0; 
  double AccZprime22_mutau = Zprime3500_mutau->GetEntries()/19000.0;
  double AccZprime23_mutau = Zprime4000_mutau->GetEntries()/20000.0;
  double AccZprime24_mutau = Zprime4500_mutau->GetEntries()/19000.0;
  double AccZprime25_mutau = Zprime5000_mutau->GetEntries()/18000.0;
  // Acceptance*Eff curves
  const int nZprime = 25;
  const double xZprime[nZprime] = {0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.5, 4.0, 4.5, 5.0 };

  const double yZprime_emu[nZprime] = { AccZprime1_emu, 
					AccZprime2_emu, 
					AccZprime3_emu, 
					AccZprime4_emu, 
					AccZprime5_emu, 
					AccZprime6_emu, 
					AccZprime7_emu, 
					AccZprime8_emu, 
					AccZprime9_emu, 
					AccZprime10_emu, 
					AccZprime11_emu, 
					AccZprime14_emu, 
					AccZprime14_emu, 
					AccZprime14_emu, 
					AccZprime15_emu, 
					AccZprime16_emu, 
					AccZprime17_emu, 
					AccZprime18_emu, 
					AccZprime19_emu, 
					AccZprime20_emu, 
					AccZprime21_emu, 
					AccZprime22_emu, 
					AccZprime23_emu, 
					AccZprime24_emu, 
					AccZprime25_emu };

  const double yZprime_etau[nZprime] = { AccZprime1_etau, 
					AccZprime2_etau, 
					AccZprime3_etau, 
					AccZprime4_etau, 
					AccZprime5_etau, 
					AccZprime6_etau, 
					AccZprime7_etau, 
					AccZprime8_etau, 
					AccZprime9_etau, 
					AccZprime10_etau, 
					AccZprime11_etau, 
					AccZprime12_etau, 
					AccZprime13_etau, 
					AccZprime14_etau, 
					AccZprime15_etau, 
					AccZprime16_etau, 
					AccZprime17_etau, 
					AccZprime18_etau, 
					AccZprime19_etau, 
					AccZprime20_etau, 
					AccZprime21_etau, 
					AccZprime22_etau, 
					AccZprime23_etau, 
					AccZprime24_etau, 
					AccZprime25_etau };

  const double yZprime_mutau[nZprime] = { AccZprime1_mutau, 
					AccZprime2_mutau, 
					AccZprime3_mutau, 
					AccZprime4_mutau, 
					AccZprime5_mutau, 
					AccZprime6_mutau, 
					AccZprime7_mutau, 
					AccZprime8_mutau, 
					AccZprime9_mutau, 
					AccZprime10_mutau, 
					AccZprime11_mutau, 
					AccZprime12_mutau, 
					AccZprime13_mutau, 
					AccZprime14_mutau, 
					AccZprime15_mutau, 
					AccZprime16_mutau, 
					AccZprime17_mutau, 
					AccZprime18_mutau, 
					AccZprime19_mutau, 
					AccZprime20_mutau, 
					AccZprime21_mutau, 
					AccZprime22_mutau, 
					AccZprime23_mutau, 
					AccZprime24_mutau, 
					AccZprime25_mutau };

  const int nQBH = 11;
  const double xQBH_RS[nQBH] = {1.0, 1.5,  2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0 };

  const double yQBHRS_emu[nQBH] = { QBHRS1000_emu->GetEntries()/20000.0, 
				    QBHRS1500_emu->GetEntries()/20000.0, 
				    QBHRS2000_emu->GetEntries()/20000.0, 
				    QBHRS2500_emu->GetEntries()/18000.0, 
				    QBHRS3000_emu->GetEntries()/20000.0, 
				    QBHRS3500_emu->GetEntries()/20000.0, 
				    QBHRS4000_emu->GetEntries()/20000.0, 
				    QBHRS4500_emu->GetEntries()/20000.0, 
				    QBHRS5000_emu->GetEntries()/20000.0, 
				    QBHRS5500_emu->GetEntries()/20000.0, 
				    QBHRS6000_emu->GetEntries()/18000.0   };
  
  const double yQBHRS_etau[nQBH] = { QBHRS1000_etau->GetEntries()/20000.0, 
				     QBHRS1500_etau->GetEntries()/20000.0, 
				     QBHRS2000_etau->GetEntries()/20000.0, 
				     QBHRS2500_etau->GetEntries()/20000.0, 
				     QBHRS3000_etau->GetEntries()/20000.0, 
				     QBHRS3500_etau->GetEntries()/18000.0, 
				     QBHRS4000_etau->GetEntries()/20000.0, 
				     QBHRS4500_etau->GetEntries()/20000.0, 
				     QBHRS5000_etau->GetEntries()/20000.0, 
				     QBHRS5500_etau->GetEntries()/20000.0, 
				     QBHRS6000_etau->GetEntries()/18000.0   };
  
  const double yQBHRS_mutau[nQBH] = { QBHRS1000_mutau->GetEntries()/20000.0, 
				      QBHRS1500_mutau->GetEntries()/20000.0, 
				      QBHRS2000_mutau->GetEntries()/20000.0, 
				      QBHRS2500_mutau->GetEntries()/20000.0, 
				      QBHRS3000_mutau->GetEntries()/20000.0, 
				      QBHRS3500_mutau->GetEntries()/20000.0, 
				      QBHRS4000_mutau->GetEntries()/20000.0, 
				      QBHRS4500_mutau->GetEntries()/20000.0, 
				      QBHRS5000_mutau->GetEntries()/20000.0, 
				      QBHRS5500_mutau->GetEntries()/19000.0, 
				      QBHRS6000_mutau->GetEntries()/20000.0   };
  

  // Calculate Ae RPV SUSY
  double AccRPV1_emu  = RPV500_emu->GetEntries() /20000.0;
  double AccRPV2_emu  = RPV600_emu->GetEntries() /20000.0;
  double AccRPV3_emu  = RPV700_emu->GetEntries() /20000.0;
  double AccRPV4_emu  = RPV800_emu->GetEntries() /20000.0;
  double AccRPV5_emu  = RPV900_emu->GetEntries() /20000.0; 
  double AccRPV6_emu  = RPV1000_emu->GetEntries()/20000.0;
  double AccRPV7_emu  = RPV1100_emu->GetEntries()/20000.0;
  double AccRPV8_emu  = RPV1200_emu->GetEntries()/20000.0;
  double AccRPV9_emu  = RPV1300_emu->GetEntries()/20000.0;
  double AccRPV10_emu = RPV1400_emu->GetEntries()/20000.0;
  double AccRPV11_emu = RPV1500_emu->GetEntries()/20000.0; 
  double AccRPV12_emu = RPV1600_emu->GetEntries()/20000.0;
  double AccRPV13_emu = RPV1700_emu->GetEntries()/19000.0;
  double AccRPV14_emu = RPV1800_emu->GetEntries()/20000.0;
  double AccRPV15_emu = RPV1900_emu->GetEntries()/20000.0;
  double AccRPV16_emu = RPV2000_emu->GetEntries()/20000.0; 
  double AccRPV17_emu = RPV2200_emu->GetEntries()/20000.0;
  double AccRPV18_emu = RPV2400_emu->GetEntries()/19000.0;
  double AccRPV19_emu = RPV2600_emu->GetEntries()/20000.0;
  double AccRPV20_emu = RPV2800_emu->GetEntries()/20000.0;
  double AccRPV21_emu = RPV3000_emu->GetEntries()/20000.0; 
  double AccRPV22_emu = RPV3500_emu->GetEntries()/20000.0;
  double AccRPV23_emu = RPV4000_emu->GetEntries()/20000.0;
  double AccRPV24_emu = RPV4500_emu->GetEntries()/20000.0;
  double AccRPV25_emu = RPV5000_emu->GetEntries()/20000.0;

  double AccRPV1_etau  = 0.64*RPV500_etau->GetEntries() /19000.0;
  double AccRPV2_etau  = 0.64*RPV600_etau->GetEntries() /20000.0;
  double AccRPV3_etau  = 0.64*RPV700_etau->GetEntries() /20000.0;
  double AccRPV4_etau  = 0.64*RPV800_etau->GetEntries() /20000.0;
  double AccRPV5_etau  = 0.64*RPV900_etau->GetEntries() /20000.0; 
  double AccRPV6_etau  = 0.64*RPV1000_etau->GetEntries()/20000.0;
  double AccRPV7_etau  = 0.64*RPV1100_etau->GetEntries()/18000.0;
  double AccRPV8_etau  = 0.64*RPV1200_etau->GetEntries()/20000.0;
  double AccRPV9_etau  = 0.64*RPV1300_etau->GetEntries()/20000.0;
  double AccRPV10_etau = 0.64*RPV1400_etau->GetEntries()/20000.0;
  double AccRPV11_etau = 0.64*RPV1500_etau->GetEntries()/18000.0; 
  double AccRPV12_etau = 0.64*RPV1600_etau->GetEntries()/20000.0;
  double AccRPV13_etau = 0.64*RPV1700_etau->GetEntries()/20000.0;
  double AccRPV14_etau = 0.64*RPV1800_etau->GetEntries()/20000.0;
  double AccRPV15_etau = 0.64*RPV1900_etau->GetEntries()/20000.0;
  double AccRPV16_etau = 0.64*RPV2000_etau->GetEntries()/20000.0; 
  double AccRPV17_etau = 0.64*RPV2200_etau->GetEntries()/20000.0;
  double AccRPV18_etau = 0.64*RPV2400_etau->GetEntries()/20000.0;
  double AccRPV19_etau = 0.64*RPV2600_etau->GetEntries()/20000.0;
  double AccRPV20_etau = 0.64*RPV2800_etau->GetEntries()/18000.0;
  double AccRPV21_etau = 0.64*RPV3000_etau->GetEntries()/20000.0; 
  double AccRPV22_etau = 0.64*RPV3500_etau->GetEntries()/18000.0;
  double AccRPV23_etau = 0.64*RPV4000_etau->GetEntries()/20000.0;
  double AccRPV24_etau = 0.64*RPV4500_etau->GetEntries()/20000.0;
  double AccRPV25_etau = 0.64*RPV5000_etau->GetEntries()/20000.0;

  double AccRPV1_mutau  = 0.64*RPV500_mutau->GetEntries() /20000.0;
  double AccRPV2_mutau  = 0.64*RPV600_mutau->GetEntries() /20000.0;
  double AccRPV3_mutau  = 0.64*RPV700_mutau->GetEntries() /20000.0;
  double AccRPV4_mutau  = 0.64*RPV800_mutau->GetEntries() /20000.0;
  double AccRPV5_mutau  = 0.64*RPV900_mutau->GetEntries() /20000.0; 
  double AccRPV6_mutau  = 0.64*RPV1000_mutau->GetEntries()/19000.0;
  double AccRPV7_mutau  = 0.64*RPV1100_mutau->GetEntries()/20000.0;
  double AccRPV8_mutau  = 0.64*RPV1200_mutau->GetEntries()/20000.0;
  double AccRPV9_mutau  = 0.64*RPV1300_mutau->GetEntries()/20000.0;
  double AccRPV10_mutau = 0.64*RPV1400_mutau->GetEntries()/20000.0;
  double AccRPV11_mutau = 0.64*RPV1500_mutau->GetEntries()/20000.0; 
  double AccRPV12_mutau = 0.64*RPV1600_mutau->GetEntries()/20000.0;
  double AccRPV13_mutau = 0.64*RPV1700_mutau->GetEntries()/20000.0;
  double AccRPV14_mutau = 0.64*RPV1800_mutau->GetEntries()/20000.0;
  double AccRPV15_mutau = 0.64*RPV1900_mutau->GetEntries()/20000.0;
  double AccRPV16_mutau = 0.64*RPV2000_mutau->GetEntries()/20000.0; 
  double AccRPV17_mutau = 0.64*RPV2200_mutau->GetEntries()/20000.0;
  double AccRPV18_mutau = 0.64*RPV2400_mutau->GetEntries()/20000.0;
  double AccRPV19_mutau = 0.64*RPV2600_mutau->GetEntries()/20000.0;
  double AccRPV20_mutau = 0.64*RPV2800_mutau->GetEntries()/20000.0;
  double AccRPV21_mutau = 0.64*RPV3000_mutau->GetEntries()/20000.0; 
  double AccRPV22_mutau = 0.64*RPV3500_mutau->GetEntries()/19000.0;
  double AccRPV23_mutau = 0.64*RPV4000_mutau->GetEntries()/20000.0;
  double AccRPV24_mutau = 0.64*RPV4500_mutau->GetEntries()/19000.0;
  double AccRPV25_mutau = 0.64*RPV5000_mutau->GetEntries()/20000.0;
  // Acceptance*Eff curves
  const int nRPV = 25;
  const double xRPV[nRPV] = {0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.5, 4.0, 4.5, 5.0 };

  const double yRPV_emu[nRPV] = { AccRPV1_emu, 
					AccRPV2_emu, 
					AccRPV3_emu, 
					AccRPV4_emu, 
					AccRPV5_emu, 
					AccRPV6_emu, 
					AccRPV7_emu, 
					AccRPV8_emu, 
					AccRPV9_emu, 
					AccRPV10_emu, 
					AccRPV11_emu, 
					AccRPV12_emu, 
					AccRPV13_emu, 
					AccRPV14_emu, 
					AccRPV15_emu, 
					AccRPV16_emu, 
					AccRPV17_emu, 
					AccRPV18_emu, 
					AccRPV19_emu, 
					AccRPV20_emu, 
					AccRPV21_emu, 
					AccRPV22_emu, 
					AccRPV23_emu, 
					AccRPV24_emu, 
					AccRPV25_emu };

  const double yRPV_etau[nRPV] = { AccRPV1_etau, 
					AccRPV2_etau, 
					AccRPV3_etau, 
					AccRPV4_etau, 
					AccRPV5_etau, 
					AccRPV6_etau, 
					AccRPV7_etau, 
					AccRPV8_etau, 
					AccRPV9_etau, 
					AccRPV10_etau, 
					AccRPV11_etau, 
					AccRPV12_etau, 
					AccRPV13_etau, 
					AccRPV14_etau, 
					AccRPV15_etau, 
					AccRPV16_etau, 
					AccRPV17_etau, 
					AccRPV18_etau, 
					AccRPV19_etau, 
					AccRPV20_etau, 
					AccRPV21_etau, 
					AccRPV22_etau, 
					AccRPV23_etau, 
					AccRPV24_etau, 
					AccRPV25_etau };

  const double yRPV_mutau[nRPV] = { AccRPV1_mutau, 
					AccRPV2_mutau, 
					AccRPV3_mutau, 
					AccRPV4_mutau, 
					AccRPV5_mutau, 
					AccRPV6_mutau, 
					AccRPV7_mutau, 
					AccRPV8_mutau, 
					AccRPV9_mutau, 
					AccRPV10_mutau, 
					AccRPV11_mutau, 
					AccRPV12_mutau, 
					AccRPV13_mutau, 
					AccRPV14_mutau, 
					AccRPV15_mutau, 
					AccRPV16_mutau, 
					AccRPV17_mutau, 
					AccRPV18_mutau, 
					AccRPV19_mutau, 
					AccRPV20_mutau, 
					AccRPV21_mutau, 
					AccRPV22_mutau, 
					AccRPV23_mutau, 
					AccRPV24_mutau, 
					AccRPV25_mutau };


  // Set up TGraph
  TGraph* ZprimeAcceptance_emu; ZprimeAcceptance_emu = new TGraph( nZprime, xZprime, yZprime_emu );
  TGraph* ZprimeAcceptance_etau; ZprimeAcceptance_etau = new TGraph( nZprime, xZprime, yZprime_etau );
  TGraph* ZprimeAcceptance_mutau; ZprimeAcceptance_mutau = new TGraph( nZprime, xZprime, yZprime_mutau );

  TGraph* RPVAcceptance_emu; RPVAcceptance_emu = new TGraph( nZprime, xZprime, yRPV_emu );
  TGraph* RPVAcceptance_etau; RPVAcceptance_etau = new TGraph( nZprime, xZprime, yRPV_etau );
  TGraph* RPVAcceptance_mutau; RPVAcceptance_mutau = new TGraph( nZprime, xZprime, yRPV_mutau );

  TGraph* QBHRSAcceptance_emu; QBHRSAcceptance_emu = new TGraph( nQBH, xQBH_RS, yQBHRS_emu );
  TGraph* QBHRSAcceptance_etau; QBHRSAcceptance_etau = new TGraph( nQBH, xQBH_RS, yQBHRS_etau );
  TGraph* QBHRSAcceptance_mutau; QBHRSAcceptance_mutau = new TGraph( nQBH, xQBH_RS, yQBHRS_mutau );

  // Set up TF1 and fit Ae
  TF1 *funcZprime_emu = new TF1("funcZprime_emu","pol6" );
  funcZprime_emu->SetLineColor(kBlue);     
  TF1 *funcQBHRS_emu = new TF1("funcQBHRS_emu","pol3" );
  funcQBHRS_emu->SetLineColor(kGreen);  
  TF1 *funcRPV_emu = new TF1("funcRPV_emu","pol6" );
  funcRPV_emu->SetLineColor(kBlack);  

  funcZprime_emu->SetMarkerColor(kBlue);  
  funcQBHRS_emu->SetMarkerColor(kGreen);  
  funcRPV_emu->SetMarkerColor(kBlack);  
  
  funcZprime_emu->SetLineStyle(1);  
  funcQBHRS_emu->SetLineStyle(3);  
  funcRPV_emu->SetLineStyle(4);  
  
  QBHRSAcceptance_emu->Fit(funcQBHRS_emu);
  ZprimeAcceptance_emu->Fit(funcZprime_emu);
  RPVAcceptance_emu->Fit(funcRPV_emu);
  
  TF1 *funcZprime_etau = new TF1("funcZprime_etau","pol6" );
  funcZprime_etau->SetLineColor(kBlue);  
  TF1 *funcQBHRS_etau = new TF1("funcQBHRS_etau","pol3" );
  funcQBHRS_etau->SetLineColor(kGreen);
  TF1 *funcRPV_etau = new TF1("funcRPV_etau","pol6" );
  funcRPV_etau->SetLineColor(kBlack);  

  funcZprime_etau->SetLineStyle(1);  
  funcQBHRS_etau->SetLineStyle(3);  
  funcRPV_etau->SetLineStyle(4); 
  
  QBHRSAcceptance_etau->Fit(funcQBHRS_etau);
  ZprimeAcceptance_etau->Fit(funcZprime_etau);
  RPVAcceptance_etau->Fit(funcRPV_etau);
  
  TF1 *funcZprime_mutau = new TF1("funcZprime_mutau","pol6", 0.5,5.0 );
  funcZprime_mutau->SetLineColor(kBlue);  
  TF1 *funcQBHRS_mutau = new TF1("funcQBHRS_mutau","pol3" );
  funcQBHRS_mutau->SetLineColor(kGreen);
  TF1 *funcRPV_mutau = new TF1("funcRPV_mutau","pol6" );
  funcRPV_mutau->SetLineColor(kBlack);   
  
  funcZprime_mutau->SetLineStyle(1);  
  funcQBHRS_mutau->SetLineStyle(3);  
  funcRPV_mutau->SetLineStyle(4);  
  
  funcZprime_mutau->SetMarkerStyle(21);  
  funcQBHRS_mutau->SetMarkerStyle(20);  
  funcRPV_mutau->SetMarkerStyle(22);

  funcZprime_etau->SetMarkerStyle(21);  
  funcQBHRS_etau->SetMarkerStyle(22);  
  funcRPV_etau->SetMarkerStyle(20);
  
  funcZprime_emu->SetMarkerStyle(21);  
  funcQBHRS_emu->SetMarkerStyle(22);  
  funcRPV_emu->SetMarkerStyle(20);
  
  QBHRSAcceptance_mutau->Fit(funcQBHRS_mutau);
  ZprimeAcceptance_mutau->Fit(funcZprime_mutau);
  RPVAcceptance_mutau->Fit(funcRPV_mutau);
  
  char writetext1[100];
  char writetext2[100];
  char writetext6[100];
  char writetext66[100];
  char writetext7[100];
  char writetext8[100];
  char writetext9[100];
  char writetext10[100];
  char writetext11[100];
  TLatex *t = new TLatex();
  t->SetNDC(1);
  t->SetTextAlign(13);
  t->SetTextColor(kBlack);
  t->SetTextSize(0.04);
  
  sprintf(writetext1,"#font[72]{ATLAS} Work in Progress");
  sprintf(writetext9,"#sqrt{s} = 13 TeV, 1.0 fb^{-1}");
   
  
  // Draw Acceptance curves
  TCanvas *A11_emu = new TCanvas( "A11_emu", "plots 11_emu",  0,0,600,600 );
  A11_emu->cd();	

  RPVAcceptance_emu->SetMarkerColor(kBlack);
  RPVAcceptance_emu->SetMarkerStyle(20);
  RPVAcceptance_emu->SetMarkerSize(0.9); 
  ZprimeAcceptance_emu->SetMarkerColor(kBlue);
  ZprimeAcceptance_emu->SetMarkerStyle(21);
  ZprimeAcceptance_emu->SetMarkerSize(0.9);
  QBHRSAcceptance_emu->SetMarkerColor(kGreen);
  QBHRSAcceptance_emu->SetMarkerStyle(22);
  QBHRSAcceptance_emu->SetMarkerSize(0.9);
  
  QBHRSAcceptance_emu->GetXaxis()->SetLabelSize(0.04);
  QBHRSAcceptance_emu->GetXaxis()->SetRangeUser(0.5,5.0);
  QBHRSAcceptance_emu->GetYaxis()->SetRangeUser(0.0,1.0);
  QBHRSAcceptance_emu->GetYaxis()->SetTitleOffset(1.4);
  
  QBHRSAcceptance_emu->GetXaxis()->SetTitle("Pole Mass [TeV]");
  QBHRSAcceptance_emu->GetYaxis()->SetTitle("A#epsilon");
  QBHRSAcceptance_emu->SetTitle("");
  
  QBHRSAcceptance_emu->Draw("AP");
  ZprimeAcceptance_emu->Draw("SameP");
  RPVAcceptance_emu->Draw("SameP");
  
  TLegend* leg;
  leg = new TLegend(0.6,0.4,0.8,0.6);
  
  leg->SetFillColor(0);leg->SetBorderSize(0);leg->SetTextSize(0.03);
  leg->AddEntry(funcZprime_emu,"Z'","PL");
  leg->AddEntry(funcQBHRS_emu,"QBH RS n=1","PL");
  leg->AddEntry(funcRPV_emu,"RPV #tilde{#nu}_{#tau}","PL");
  //leg->AddEntry(funcQBHADD_emu,"QBH ADD n=6","L");
  leg->Draw(); 
  
  t->DrawLatex(0.43,0.87,"#it{#bf{ATLAS} }Simulation");
  t->DrawLatex(0.43,0.81,"e#mu channel");
  t->DrawLatex(0.43,0.75,"#sqrt{s} = 13 TeV");
  
  TCanvas *A11_etau = new TCanvas( "A11_etau", "plots 11_etau", 0,0,600,600 );
  A11_etau->cd();	
  
  RPVAcceptance_etau->SetMarkerColor(kBlack);
  RPVAcceptance_etau->SetMarkerStyle(20);
  RPVAcceptance_etau->SetMarkerSize(0.9); 
  ZprimeAcceptance_etau->SetMarkerColor(kBlue);
  ZprimeAcceptance_etau->SetMarkerStyle(21);
  ZprimeAcceptance_etau->SetMarkerSize(0.9);
  QBHRSAcceptance_etau->SetMarkerColor(kGreen);
  QBHRSAcceptance_etau->SetMarkerStyle(22);
  QBHRSAcceptance_etau->SetMarkerSize(0.9);
  QBHRSAcceptance_etau->SetTitle("");

  QBHRSAcceptance_etau->GetXaxis()->SetRangeUser(0.5,5.0);
  QBHRSAcceptance_etau->GetYaxis()->SetRangeUser(0.0,0.4);
  QBHRSAcceptance_etau->GetYaxis()->SetTitleOffset(1.4);
  QBHRSAcceptance_etau->GetXaxis()->SetLabelSize(0.04);

  QBHRSAcceptance_etau->GetXaxis()->SetTitle("Pole Mass [TeV]");
  QBHRSAcceptance_etau->GetYaxis()->SetTitle("A#epsilon");

  QBHRSAcceptance_etau->Draw("AP");
  ZprimeAcceptance_etau->Draw("SameP");
  RPVAcceptance_etau->Draw("SameP");

  TLegend* leg2;
  leg2 = new TLegend(0.6,0.4,0.8,0.6);

  leg2->SetFillColor(0);leg2->SetBorderSize(0);leg2->SetTextSize(0.03);
  leg2->AddEntry(funcZprime_emu,"Z'","PL");
  leg2->AddEntry(funcQBHRS_emu,"QBH RS n=1","PL");
  leg2->AddEntry(funcRPV_emu,"RPV #tilde{#nu}_{#tau}","PL");
  leg2->Draw(); 

  t->DrawLatex(0.43,0.87,"#it{#bf{ATLAS} }Simulation");
  t->DrawLatex(0.43,0.81,"e#tau channel");
  t->DrawLatex(0.43,0.75,"#sqrt{s} = 13 TeV");


  TCanvas *A11_mutau = new TCanvas( "A11_mutau", "plots 11_mutau", 0,0,600,600 );
  A11_mutau->cd();	
 
  RPVAcceptance_mutau->SetMarkerColor(kBlack);
  RPVAcceptance_mutau->SetMarkerStyle(20);
  RPVAcceptance_mutau->SetMarkerSize(0.9); 
  ZprimeAcceptance_mutau->SetMarkerColor(kBlue);
  ZprimeAcceptance_mutau->SetMarkerStyle(21);
  ZprimeAcceptance_mutau->SetMarkerSize(0.9);
  QBHRSAcceptance_mutau->SetMarkerColor(kGreen);
  QBHRSAcceptance_mutau->SetMarkerStyle(22);
  QBHRSAcceptance_mutau->SetMarkerSize(0.9);
  QBHRSAcceptance_mutau->SetTitle("");

  QBHRSAcceptance_mutau->GetXaxis()->SetLabelSize(0.04);
  QBHRSAcceptance_mutau->GetXaxis()->SetRangeUser(0.5,5.0);
  QBHRSAcceptance_mutau->GetYaxis()->SetRangeUser(0.0,0.3);
  QBHRSAcceptance_mutau->GetYaxis()->SetTitleOffset(1.4);

  QBHRSAcceptance_mutau->GetXaxis()->SetTitle("Pole Mass [TeV]");
  QBHRSAcceptance_mutau->GetYaxis()->SetTitle("A#epsilon");

  QBHRSAcceptance_mutau->Draw("AP");
  ZprimeAcceptance_mutau->Draw("SameP");
  RPVAcceptance_mutau->Draw("SameP");

  TLegend* leg3;
  leg3 = new TLegend(0.6,0.4,0.8,0.6);

  leg3->SetFillColor(0);leg3->SetBorderSize(0);leg3->SetTextSize(0.03);
  leg3->AddEntry(funcZprime_emu,"Z'","PL");
  leg3->AddEntry(funcQBHRS_emu,"QBH RS n=1","PL");
  leg3->AddEntry(funcRPV_emu,"RPV #tilde{#nu}_{#tau}","PL");
  leg3->Draw(); 

  t->DrawLatex(0.43,0.87,"#it{#bf{ATLAS} }Simulation");
  t->DrawLatex(0.43,0.81,"#mu#tau channel");
  t->DrawLatex(0.43,0.75,"#sqrt{s} = 13 TeV");

  TCanvas *A12 = new TCanvas( "A12", "plots 12", 0,0,600,600 );
  A12->cd();	

  /*ZprimeAcceptance_emu->SetLineColor(0);
    ZprimeAcceptance_etau->SetLineColor(0);
    ZprimeAcceptance_mutau->SetLineColor(0);

    ZprimeAcceptance_mutau->GetXaxis()->SetLabelSize(0.04);
    ZprimeAcceptance_mutau->GetXaxis()->SetRangeUser(0.5,5.0);
    ZprimeAcceptance_mutau->GetYaxis()->SetRangeUser(0.0,0.53);
    ZprimeAcceptance_mutau->GetYaxis()->SetTitleOffset(1.4);
        
    ZprimeAcceptance_mutau->GetXaxis()->SetTitle("Pole Mass [TeV]");
    ZprimeAcceptance_mutau->GetYaxis()->SetTitle("A#epsilon");

    ZprimeAcceptance_mutau->Draw("AL");
    ZprimeAcceptance_etau->Draw("SameL");
    ZprimeAcceptance_emu->Draw("SameL");
	    
    TLegend* leg4;
    leg4 = new TLegend(0.6,0.4,0.8,0.6);

    leg4->SetFillColor(0);leg4->SetBorderSize(0);leg4->SetTextSize(0.03);
    leg4->AddEntry(funcZprime_emu,"LFV Z' e#mu channel","L");
    leg4->AddEntry(funcZprime_etau,"LFV Z' e#tau channel","L");
    leg4->AddEntry(funcZprime_mutau,"LFV Z' #mu#tau channel","L");
    leg4->Draw(); 
	 	
    t->DrawLatex(0.53,0.70,"#it{#bf{ATLAS} }Simulation");
    t->DrawLatex(0.53,0.64,"#sqrt{s} = 13 TeV");
    t->DrawLatex(0.53,0.58,"b-jet Veto");*/

  //Set up histogram names for array
  QBHRS1000_emu->SetName("0");
  QBHRS1500_emu->SetName("1");
  QBHRS2000_emu->SetName("2");
  QBHRS2500_emu->SetName("3");
  QBHRS3000_emu->SetName("4");
  QBHRS3500_emu->SetName("5");
  QBHRS4000_emu->SetName("6");
  QBHRS4500_emu->SetName("7");
  QBHRS5000_emu->SetName("8");
  QBHRS5500_emu->SetName("9");
  QBHRS6000_emu->SetName("10");

  Zprime500_emu->SetName("0");
  Zprime600_emu->SetName("1");
  Zprime700_emu->SetName("2");
  Zprime800_emu->SetName("3");
  Zprime900_emu->SetName("4");
  Zprime1000_emu->SetName("5");
  Zprime1100_emu->SetName("6");
  Zprime1200_emu->SetName("7");
  Zprime1300_emu->SetName("8");
  Zprime1400_emu->SetName("9");
  Zprime1500_emu->SetName("10");
  Zprime1600_emu->SetName("11");
  Zprime1700_emu->SetName("12");
  Zprime1800_emu->SetName("13");
  Zprime1900_emu->SetName("14");
  Zprime2000_emu->SetName("15");
  Zprime2200_emu->SetName("16");
  Zprime2400_emu->SetName("17");
  Zprime2600_emu->SetName("18");
  Zprime2800_emu->SetName("19");
  Zprime3000_emu->SetName("20");
  Zprime3500_emu->SetName("21");
  Zprime4000_emu->SetName("22");
  Zprime4500_emu->SetName("23");
  Zprime5000_emu->SetName("24");

  RPV500_emu->SetName("0");
  RPV600_emu->SetName("1");
  RPV700_emu->SetName("2");
  RPV800_emu->SetName("3");
  RPV900_emu->SetName("4");
  RPV1000_emu->SetName("5");
  RPV1100_emu->SetName("6");
  RPV1200_emu->SetName("7");
  RPV1300_emu->SetName("8");
  RPV1400_emu->SetName("9");
  RPV1500_emu->SetName("10");
  RPV1600_emu->SetName("11");
  RPV1700_emu->SetName("12");
  RPV1800_emu->SetName("13");
  RPV1900_emu->SetName("14");
  RPV2000_emu->SetName("15");
  RPV2200_emu->SetName("16");
  RPV2400_emu->SetName("17");
  RPV2600_emu->SetName("18");
  RPV2800_emu->SetName("19");
  RPV3000_emu->SetName("20");
  RPV3500_emu->SetName("21");
  RPV4000_emu->SetName("22");
  RPV4500_emu->SetName("23");
  RPV5000_emu->SetName("24");

  SignalObjQBHRS_emu->Add(QBHRS1000_emu); 
  SignalObjQBHRS_emu->Add(QBHRS1500_emu); 
  SignalObjQBHRS_emu->Add(QBHRS2000_emu); 
  SignalObjQBHRS_emu->Add(QBHRS2500_emu); 
  SignalObjQBHRS_emu->Add(QBHRS3000_emu); 
  SignalObjQBHRS_emu->Add(QBHRS3500_emu); 
  SignalObjQBHRS_emu->Add(QBHRS4000_emu); 
  SignalObjQBHRS_emu->Add(QBHRS4500_emu); 
  SignalObjQBHRS_emu->Add(QBHRS5000_emu); 
  SignalObjQBHRS_emu->Add(QBHRS5500_emu); 
  SignalObjQBHRS_emu->Add(QBHRS6000_emu); 
  SignalObjZprime_emu->Add(Zprime500_emu); 
  SignalObjZprime_emu->Add(Zprime600_emu); 
  SignalObjZprime_emu->Add(Zprime700_emu); 
  SignalObjZprime_emu->Add(Zprime800_emu); 
  SignalObjZprime_emu->Add(Zprime900_emu); 
  SignalObjZprime_emu->Add(Zprime1000_emu); 
  SignalObjZprime_emu->Add(Zprime1100_emu);   
  SignalObjZprime_emu->Add(Zprime1200_emu); 
  SignalObjZprime_emu->Add(Zprime1300_emu);  
  SignalObjZprime_emu->Add(Zprime1400_emu); 
  SignalObjZprime_emu->Add(Zprime1500_emu); 
  SignalObjZprime_emu->Add(Zprime1600_emu); 
  SignalObjZprime_emu->Add(Zprime1700_emu); 
  SignalObjZprime_emu->Add(Zprime1800_emu); 
  SignalObjZprime_emu->Add(Zprime1900_emu); 
  SignalObjZprime_emu->Add(Zprime2000_emu); 
  SignalObjZprime_emu->Add(Zprime2200_emu); 
  SignalObjZprime_emu->Add(Zprime2400_emu); 
  SignalObjZprime_emu->Add(Zprime2600_emu); 
  SignalObjZprime_emu->Add(Zprime2800_emu); 
  SignalObjZprime_emu->Add(Zprime3000_emu); 
  SignalObjZprime_emu->Add(Zprime3500_emu); 
  SignalObjZprime_emu->Add(Zprime4000_emu); 
  SignalObjZprime_emu->Add(Zprime4500_emu); 
  SignalObjZprime_emu->Add(Zprime5000_emu);
  SignalObjRPV_emu->Add(RPV500_emu); 
  SignalObjRPV_emu->Add(RPV600_emu); 
  SignalObjRPV_emu->Add(RPV700_emu); 
  SignalObjRPV_emu->Add(RPV800_emu); 
  SignalObjRPV_emu->Add(RPV900_emu); 
  SignalObjRPV_emu->Add(RPV1000_emu); 
  SignalObjRPV_emu->Add(RPV1100_emu);   
  SignalObjRPV_emu->Add(RPV1200_emu); 
  SignalObjRPV_emu->Add(RPV1300_emu);  
  SignalObjRPV_emu->Add(RPV1400_emu); 
  SignalObjRPV_emu->Add(RPV1500_emu); 
  SignalObjRPV_emu->Add(RPV1600_emu); 
  SignalObjRPV_emu->Add(RPV1700_emu); 
  SignalObjRPV_emu->Add(RPV1800_emu); 
  SignalObjRPV_emu->Add(RPV1900_emu); 
  SignalObjRPV_emu->Add(RPV2000_emu); 
  SignalObjRPV_emu->Add(RPV2200_emu); 
  SignalObjRPV_emu->Add(RPV2400_emu); 
  SignalObjRPV_emu->Add(RPV2600_emu); 
  SignalObjRPV_emu->Add(RPV2800_emu); 
  SignalObjRPV_emu->Add(RPV3000_emu); 
  SignalObjRPV_emu->Add(RPV3500_emu); 
  SignalObjRPV_emu->Add(RPV4000_emu); 
  SignalObjRPV_emu->Add(RPV4500_emu); 
  SignalObjRPV_emu->Add(RPV5000_emu);

  //Set up histogram names for array
  QBHRS1000_etau->SetName("0");
  QBHRS1500_etau->SetName("1");
  QBHRS2000_etau->SetName("2");
  QBHRS2500_etau->SetName("3");
  QBHRS3000_etau->SetName("4");
  QBHRS3500_etau->SetName("5");
  QBHRS4000_etau->SetName("6");
  QBHRS4500_etau->SetName("7");
  QBHRS5000_etau->SetName("8");
  QBHRS5500_etau->SetName("9");
  QBHRS6000_etau->SetName("10");

  Zprime500_etau->SetName("0");
  Zprime600_etau->SetName("1");
  Zprime700_etau->SetName("2");
  Zprime800_etau->SetName("3");
  Zprime900_etau->SetName("4");
  Zprime1000_etau->SetName("5");
  Zprime1100_etau->SetName("6");
  Zprime1200_etau->SetName("7");
  Zprime1300_etau->SetName("8");
  Zprime1400_etau->SetName("9");
  Zprime1500_etau->SetName("10");
  Zprime1600_etau->SetName("11");
  Zprime1700_etau->SetName("12");
  Zprime1800_etau->SetName("13");
  Zprime1900_etau->SetName("14");
  Zprime2000_etau->SetName("15");
  Zprime2200_etau->SetName("16");
  Zprime2400_etau->SetName("17");
  Zprime2600_etau->SetName("18");
  Zprime2800_etau->SetName("19");
  Zprime3000_etau->SetName("20");
  Zprime3500_etau->SetName("21");
  Zprime4000_etau->SetName("22");
  Zprime4500_etau->SetName("23");
  Zprime5000_etau->SetName("24");

  RPV500_etau->SetName("0");
  RPV600_etau->SetName("1");
  RPV700_etau->SetName("2");
  RPV800_etau->SetName("3");
  RPV900_etau->SetName("4");
  RPV1000_etau->SetName("5");
  RPV1100_etau->SetName("6");
  RPV1200_etau->SetName("7");
  RPV1300_etau->SetName("8");
  RPV1400_etau->SetName("9");
  RPV1500_etau->SetName("10");
  RPV1600_etau->SetName("11");
  RPV1700_etau->SetName("12");
  RPV1800_etau->SetName("13");
  RPV1900_etau->SetName("14");
  RPV2000_etau->SetName("15");
  RPV2200_etau->SetName("16");
  RPV2400_etau->SetName("17");
  RPV2600_etau->SetName("18");
  RPV2800_etau->SetName("19");
  RPV3000_etau->SetName("20");
  RPV3500_etau->SetName("21");
  RPV4000_etau->SetName("22");
  RPV4500_etau->SetName("23");
  RPV5000_etau->SetName("24");

  SignalObjQBHRS_etau->Add(QBHRS1000_etau); 
  SignalObjQBHRS_etau->Add(QBHRS1500_etau); 
  SignalObjQBHRS_etau->Add(QBHRS2000_etau); 
  SignalObjQBHRS_etau->Add(QBHRS2500_etau); 
  SignalObjQBHRS_etau->Add(QBHRS3000_etau); 
  SignalObjQBHRS_etau->Add(QBHRS3500_etau); 
  SignalObjQBHRS_etau->Add(QBHRS4000_etau); 
  SignalObjQBHRS_etau->Add(QBHRS4500_etau); 
  SignalObjQBHRS_etau->Add(QBHRS5000_etau); 
  SignalObjQBHRS_etau->Add(QBHRS5500_etau); 
  SignalObjQBHRS_etau->Add(QBHRS6000_etau); 
  SignalObjZprime_etau->Add(Zprime500_etau); 
  SignalObjZprime_etau->Add(Zprime600_etau); 
  SignalObjZprime_etau->Add(Zprime700_etau); 
  SignalObjZprime_etau->Add(Zprime800_etau); 
  SignalObjZprime_etau->Add(Zprime900_etau); 
  SignalObjZprime_etau->Add(Zprime1000_etau); 
  SignalObjZprime_etau->Add(Zprime1100_etau);   
  SignalObjZprime_etau->Add(Zprime1200_etau); 
  SignalObjZprime_etau->Add(Zprime1300_etau);  
  SignalObjZprime_etau->Add(Zprime1400_etau); 
  SignalObjZprime_etau->Add(Zprime1500_etau); 
  SignalObjZprime_etau->Add(Zprime1600_etau); 
  SignalObjZprime_etau->Add(Zprime1700_etau); 
  SignalObjZprime_etau->Add(Zprime1800_etau); 
  SignalObjZprime_etau->Add(Zprime1900_etau); 
  SignalObjZprime_etau->Add(Zprime2000_etau); 
  SignalObjZprime_etau->Add(Zprime2200_etau); 
  SignalObjZprime_etau->Add(Zprime2400_etau); 
  SignalObjZprime_etau->Add(Zprime2600_etau); 
  SignalObjZprime_etau->Add(Zprime2800_etau); 
  SignalObjZprime_etau->Add(Zprime3000_etau); 
  SignalObjZprime_etau->Add(Zprime3500_etau); 
  SignalObjZprime_etau->Add(Zprime4000_etau); 
  SignalObjZprime_etau->Add(Zprime4500_etau); 
  SignalObjZprime_etau->Add(Zprime5000_etau);

  SignalObjRPV_etau->Add(RPV500_etau); 
  SignalObjRPV_etau->Add(RPV600_etau); 
  SignalObjRPV_etau->Add(RPV700_etau); 
  SignalObjRPV_etau->Add(RPV800_etau); 
  SignalObjRPV_etau->Add(RPV900_etau); 
  SignalObjRPV_etau->Add(RPV1000_etau); 
  SignalObjRPV_etau->Add(RPV1100_etau);   
  SignalObjRPV_etau->Add(RPV1200_etau); 
  SignalObjRPV_etau->Add(RPV1300_etau);  
  SignalObjRPV_etau->Add(RPV1400_etau); 
  SignalObjRPV_etau->Add(RPV1500_etau); 
  SignalObjRPV_etau->Add(RPV1600_etau); 
  SignalObjRPV_etau->Add(RPV1700_etau); 
  SignalObjRPV_etau->Add(RPV1800_etau); 
  SignalObjRPV_etau->Add(RPV1900_etau); 
  SignalObjRPV_etau->Add(RPV2000_etau); 
  SignalObjRPV_etau->Add(RPV2200_etau); 
  SignalObjRPV_etau->Add(RPV2400_etau); 
  SignalObjRPV_etau->Add(RPV2600_etau); 
  SignalObjRPV_etau->Add(RPV2800_etau); 
  SignalObjRPV_etau->Add(RPV3000_etau); 
  SignalObjRPV_etau->Add(RPV3500_etau); 
  SignalObjRPV_etau->Add(RPV4000_etau); 
  SignalObjRPV_etau->Add(RPV4500_etau); 
  SignalObjRPV_etau->Add(RPV5000_etau);


  //Set up histogram names for array
  QBHRS1000_mutau->SetName("0");
  QBHRS1500_mutau->SetName("1");
  QBHRS2000_mutau->SetName("2");
  QBHRS2500_mutau->SetName("3");
  QBHRS3000_mutau->SetName("4");
  QBHRS3500_mutau->SetName("5");
  QBHRS4000_mutau->SetName("6");
  QBHRS4500_mutau->SetName("7");
  QBHRS5000_mutau->SetName("8");
  QBHRS5500_mutau->SetName("9");
  QBHRS6000_mutau->SetName("10");

  Zprime500_mutau->SetName("0");
  Zprime600_mutau->SetName("1");
  Zprime700_mutau->SetName("2");
  Zprime800_mutau->SetName("3");
  Zprime900_mutau->SetName("4");
  Zprime1000_mutau->SetName("5");
  Zprime1100_mutau->SetName("6");
  Zprime1200_mutau->SetName("7");
  Zprime1300_mutau->SetName("8");
  Zprime1400_mutau->SetName("9");
  Zprime1500_mutau->SetName("10");
  Zprime1600_mutau->SetName("11");
  Zprime1700_mutau->SetName("12");
  Zprime1800_mutau->SetName("13");
  Zprime1900_mutau->SetName("14");
  Zprime2000_mutau->SetName("15");
  Zprime2200_mutau->SetName("16");
  Zprime2400_mutau->SetName("17");
  Zprime2600_mutau->SetName("18");
  Zprime2800_mutau->SetName("19");
  Zprime3000_mutau->SetName("20");
  Zprime3500_mutau->SetName("21");
  Zprime4000_mutau->SetName("22");
  Zprime4500_mutau->SetName("23");
  Zprime5000_mutau->SetName("24");

  RPV500_mutau->SetName("0");
  RPV600_mutau->SetName("1");
  RPV700_mutau->SetName("2");
  RPV800_mutau->SetName("3");
  RPV900_mutau->SetName("4");
  RPV1000_mutau->SetName("5");
  RPV1100_mutau->SetName("6");
  RPV1200_mutau->SetName("7");
  RPV1300_mutau->SetName("8");
  RPV1400_mutau->SetName("9");
  RPV1500_mutau->SetName("10");
  RPV1600_mutau->SetName("11");
  RPV1700_mutau->SetName("12");
  RPV1800_mutau->SetName("13");
  RPV1900_mutau->SetName("14");
  RPV2000_mutau->SetName("15");
  RPV2200_mutau->SetName("16");
  RPV2400_mutau->SetName("17");
  RPV2600_mutau->SetName("18");
  RPV2800_mutau->SetName("19");
  RPV3000_mutau->SetName("20");
  RPV3500_mutau->SetName("21");
  RPV4000_mutau->SetName("22");
  RPV4500_mutau->SetName("23");
  RPV5000_mutau->SetName("24");
 
  SignalObjQBHRS_mutau->Add(QBHRS1000_mutau); 
  SignalObjQBHRS_mutau->Add(QBHRS1500_mutau); 
  SignalObjQBHRS_mutau->Add(QBHRS2000_mutau); 
  SignalObjQBHRS_mutau->Add(QBHRS2500_mutau); 
  SignalObjQBHRS_mutau->Add(QBHRS3000_mutau); 
  SignalObjQBHRS_mutau->Add(QBHRS3500_mutau); 
  SignalObjQBHRS_mutau->Add(QBHRS4000_mutau); 
  SignalObjQBHRS_mutau->Add(QBHRS4500_mutau); 
  SignalObjQBHRS_mutau->Add(QBHRS5000_mutau); 
  SignalObjQBHRS_mutau->Add(QBHRS5500_mutau); 
  SignalObjQBHRS_mutau->Add(QBHRS6000_mutau); 
  SignalObjZprime_mutau->Add(Zprime500_mutau); 
  SignalObjZprime_mutau->Add(Zprime600_mutau); 
  SignalObjZprime_mutau->Add(Zprime700_mutau); 
  SignalObjZprime_mutau->Add(Zprime800_mutau); 
  SignalObjZprime_mutau->Add(Zprime900_mutau); 
  SignalObjZprime_mutau->Add(Zprime1000_mutau); 
  SignalObjZprime_mutau->Add(Zprime1100_mutau);   
  SignalObjZprime_mutau->Add(Zprime1200_mutau); 
  SignalObjZprime_mutau->Add(Zprime1300_mutau);  
  SignalObjZprime_mutau->Add(Zprime1400_mutau); 
  SignalObjZprime_mutau->Add(Zprime1500_mutau); 
  SignalObjZprime_mutau->Add(Zprime1600_mutau); 
  SignalObjZprime_mutau->Add(Zprime1700_mutau); 
  SignalObjZprime_mutau->Add(Zprime1800_mutau); 
  SignalObjZprime_mutau->Add(Zprime1900_mutau); 
  SignalObjZprime_mutau->Add(Zprime2000_mutau); 
  SignalObjZprime_mutau->Add(Zprime2200_mutau); 
  SignalObjZprime_mutau->Add(Zprime2400_mutau); 
  SignalObjZprime_mutau->Add(Zprime2600_mutau); 
  SignalObjZprime_mutau->Add(Zprime2800_mutau); 
  SignalObjZprime_mutau->Add(Zprime3000_mutau); 
  SignalObjZprime_mutau->Add(Zprime3500_mutau); 
  SignalObjZprime_mutau->Add(Zprime4000_mutau); 
  SignalObjZprime_mutau->Add(Zprime4500_mutau); 
  SignalObjZprime_mutau->Add(Zprime5000_mutau);

  SignalObjRPV_mutau->Add(RPV500_mutau); 
  SignalObjRPV_mutau->Add(RPV600_mutau); 
  SignalObjRPV_mutau->Add(RPV700_mutau); 
  SignalObjRPV_mutau->Add(RPV800_mutau); 
  SignalObjRPV_mutau->Add(RPV900_mutau); 
  SignalObjRPV_mutau->Add(RPV1000_mutau); 
  SignalObjRPV_mutau->Add(RPV1100_mutau);   
  SignalObjRPV_mutau->Add(RPV1200_mutau); 
  SignalObjRPV_mutau->Add(RPV1300_mutau);  
  SignalObjRPV_mutau->Add(RPV1400_mutau); 
  SignalObjRPV_mutau->Add(RPV1500_mutau); 
  SignalObjRPV_mutau->Add(RPV1600_mutau); 
  SignalObjRPV_mutau->Add(RPV1700_mutau); 
  SignalObjRPV_mutau->Add(RPV1800_mutau); 
  SignalObjRPV_mutau->Add(RPV1900_mutau); 
  SignalObjRPV_mutau->Add(RPV2000_mutau); 
  SignalObjRPV_mutau->Add(RPV2200_mutau); 
  SignalObjRPV_mutau->Add(RPV2400_mutau); 
  SignalObjRPV_mutau->Add(RPV2600_mutau); 
  SignalObjRPV_mutau->Add(RPV2800_mutau); 
  SignalObjRPV_mutau->Add(RPV3000_mutau); 
  SignalObjRPV_mutau->Add(RPV3500_mutau); 
  SignalObjRPV_mutau->Add(RPV4000_mutau); 
  SignalObjRPV_mutau->Add(RPV4500_mutau); 
  SignalObjRPV_mutau->Add(RPV5000_mutau);

  // Set up input file for BAT
  TFile* fout_emu = new TFile("../BAT_Zprime_elmu_bjet.root","RECREATE");

  SignalObjZprime_emu->Write("Template",1);
  funcZprime_emu->SetName("AcceptanceEff"); funcZprime_emu->Write();

  fout_emu->Close();

  TFile* fout2_emu = new TFile("../BAT_QBH_elmu_RS_bjet.root","RECREATE");

  SignalObjQBHRS_emu->Write("Template",1);
  funcQBHRS_emu->SetName("AcceptanceEff"); funcQBHRS_emu->Write();

  fout2_emu->Close();


  TFile* fout4_emu = new TFile("../BAT_RPVSUSY_elmu_bjet.root","RECREATE");

  SignalObjRPV_emu->Write("Template",1);
  funcRPV_emu->SetName("AcceptanceEff"); funcRPV_emu->Write();

  fout4_emu->Close();

  TFile* fout_etau = new TFile("../BAT_Zprime_eltau_bjet.root","RECREATE");

  SignalObjZprime_etau->Write("Template",1);
  funcZprime_etau->SetName("AcceptanceEff"); funcZprime_etau->Write();

  fout_etau->Close();

  TFile* fout2_etau = new TFile("../BAT_QBH_eltau_RS_bjet.root","RECREATE");

  SignalObjQBHRS_etau->Write("Template",1);
  funcQBHRS_etau->SetName("AcceptanceEff"); funcQBHRS_etau->Write();

  fout2_etau->Close();

  TFile* fout4_etau = new TFile("../BAT_RPVSUSY_eltau_bjet.root","RECREATE");

  SignalObjRPV_etau->Write("Template",1);
  funcRPV_etau->SetName("AcceptanceEff"); funcRPV_etau->Write();

  fout4_etau->Close();

  TFile* fout_mutau = new TFile("../BAT_Zprime_mutau_bjet.root","RECREATE");

  SignalObjZprime_mutau->Write("Template",1);
  funcZprime_mutau->SetName("AcceptanceEff"); funcZprime_mutau->Write();

  fout_mutau->Close();

  TFile* fout2_mutau = new TFile("../BAT_QBH_mutau_RS_bjet.root","RECREATE");

  SignalObjQBHRS_mutau->Write("Template",1);
  funcQBHRS_mutau->SetName("AcceptanceEff"); funcQBHRS_mutau->Write();

  fout2_mutau->Close();

  TFile* fout4_mutau = new TFile("../BAT_RPVSUSY_mutau_bjet.root","RECREATE");

  SignalObjRPV_mutau->Write("Template",1);
  funcRPV_mutau->SetName("AcceptanceEff"); funcRPV_mutau->Write();

  fout4_mutau->Close();

} // end of program
