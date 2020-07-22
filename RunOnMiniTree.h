#ifndef RunOnMiniTree_H
#define RunOnMiniTree_H

/* C++ includes */
#include "iostream"
#include "fstream"
#include "set"
#include "map"
#include <sys/stat.h>

/* ROOT includes */
#include <TH1.h>
#include <TH2.h>
#include <TObject.h>
#include <TTree.h>
#include <TFile.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TColor.h>
#include <TMath.h>
#include <TChain.h>

class RunOnMiniTree{

 public:
  
  /****************/
  /* Constructors */
  /****************/
  RunOnMiniTree(std::string runType, std::string sample, std::string baseDir,
		std::string sysVar,  double lumi, int lfvType, bool useBjet,
		bool ttbarCR, bool usePuRw,  bool doPtRw,  bool WjetCR,
		bool metCut,  bool pTlep,    bool ssPair,  bool osPair,
		bool antiIso, bool noTauID,  bool tauFake, bool tauFakePt,
		bool tauFakeEta, bool QcdCR, bool DphiRev, bool Blind,
		bool BlindData,  bool doEvtList, bool useTopSherpa,
		unsigned long long singleEvent,  bool debug, 
		bool verbose);
  
  /****************/
  /*   Methods    */
  /****************/

  /* Main Process */
  void Process();

  /* Fin Max Bin */
  std::pair<int,double> FindMaxBin(TH1F* h);
  std::pair<int,double> FindMaxBin(TH2F* h);

  /* Set input Tree Name */
  void SetTreeName();

  /* Set LFV types */
  void SetLFVtypes();

  /* Set Input/Output Directory */
  void SetInputDir(std::string name);
  void SetOutputDir();

  /* Load Input Files and Histograms */
  void LoadInputs();

  /* Find Tau Fake Rate Boundaries */
  void FindTauFakeRateBoundaries();

  /* Define Samples */
  void DefineSamples();

  /* Define Out Histograms */
  void DefineOutHistograms();

  /* Set Histogram Errors */
  void SetHistoErrors(std::string name, int itr);

  /* Define OutFile */
  void DefineOutFile();

  /* Check existence OutDir */
  void CheckOutDir();

  /* Open/Close Mini Tree */
  void OpenMiniTree(std::string name);
  void CloseMiniTree();

  /* Init Tree in MiniTree */
  void LoadAndSetTree();
  void InitTreeVariables();
  void SetTreeAndBranches();

  /* Find Total Events Sample */
  double FindTotalEventsSample(std::string name);

  /* Loop on Events */
  void LoopOnEvents(std::string name);

  /* Retrieve Weights */
  double GetEventWeight();
  double GetTauFakeRateWeight();
  double GetPDFWeight(double mass, std::string name);
  double GetTopScaleWeight(double mass, std::string name);
  double GetPtReWgtWeight(double dlep_pt, std::string name);
    
  /* Store Histograms */
  void StoreHistograms();

  /* Set Atlas Style */
  void SetAtlasStyle();
  
  /* Clean */
  void CleanMemory();

  /* Open Data Event List File */
  void OpenEventListFile();
  
  /* Write Event On File */
  void WriteEventOnFile();

  /* Evaluate Transverse Mass */
  double GetTransverseMass();

  /* Compute Delta phi */
  double ComputeDeltaPhi(double phi1, double phi2);

  /* Get pT Rw weights */
  void FillPtWeightsVec();
  
 protected:
  std::string m_lfvName  ;
  std::string m_lfvSt    ;
  std::string m_treeName ;
  std::string m_InDir    ;
  std::string m_OutDir   ;

  std::ofstream m_outStream;

  TFile *m_pdfIn, *m_scaleIn, *m_tauFrIn;
  TFile *m_Input, *m_Output;
  TH1F *m_pdfDb, *m_pdfTop, *m_scaleUp, *m_scaleDw;
  TH1F *m_FR1p_pT, *m_FR3p_pT, *m_FR1p_Eta, *m_FR3p_Eta;
  TH2F *m_FR1p_pTeta, *m_FR3p_pTeta;

  TTree *m_InTree;

  std::vector<std::string> m_sampleName;
  std::vector<std::string> m_dirs;
  std::string m_tmpOutDir;

  std::vector<double> m_pTwgt;
  
  TH1F *hmll,   *hmllCorr, *hptll, *hptllCorr;
  TH1F *hetall, *hphill,   *hmet,  *hnjet,    *hmt;
  TH1F *hmu_pt, *hmu_eta,  *hmu_phi;
  TH1F *hel_pt, *hel_eta,  *hel_phi;
  TH1F *hta_pt, *hta_eta,  *hta_phi;

  std::vector<TH1F*> Vmll,   VmllC,   Vptll,  VptllC;
  std::vector<TH1F*> Vetall, Vphill,  Vmet,   Vnjet,  Vmt;
  std::vector<TH1F*> Vmu_pt, Vmu_eta, Vmu_phi;
  std::vector<TH1F*> Vel_pt, Vel_eta, Vel_phi;
  std::vector<TH1F*> Vta_pt, Vta_eta, Vta_phi;

  std::set< std::pair<Int_t,ULong64_t> > m_EvtProcessed;
  
 private:
  /* class options */
  std::string m_sample ;
  std::string m_baseDir;
  std::string m_sysVar ;
  std::string m_runType;
  double m_lumi        ;
  int m_lfvType        ;
  bool m_useBjet       ;
  bool m_ttbarCR       ;
  bool m_usePuRw       ;
  bool m_doPtRw        ;
  bool m_wjetCR        ;
  bool m_metCut        ;
  bool m_pTlep         ;
  bool m_ssPair        ;
  bool m_osPair        ;
  bool m_antiIso       ;
  bool m_noTauID       ;
  bool m_tauFr         ;
  bool m_tauFr_pT      ;
  bool m_tauFr_eta     ;
  bool m_qcdCR         ;
  bool m_dphiRev       ;
  bool m_blindData     ;
  bool m_blind         ;
  bool m_evtList       ;
  bool m_useSherpa     ;
  bool m_debug         ;
  bool m_verbose       ;
  unsigned long long m_runEvent;
  
  /* class variables */
  int m_TauId;
  int m_MuId;
  int m_ElId;
  double m_Nevents;
  double m_pi;
    
  /* Tau Fake Rate Boundaries */
  Int_t MaxBin_1p, MaxBin_3p;
  double MaxPt_1p, MaxPt_3p;
  
  /* Tree variables */
  ULong64_t       event;
  Int_t           run;
  Double_t        dilepMass;
  Double_t        dilepCorrMass;
  Double_t        dilepPt;
  Double_t        dilepCorrPt;
  Double_t        dilepEta;
  Double_t        dilepPhi;
  Double_t        mcweight;
  Double_t        puweight;
  Double_t        puweight_SysUp;
  Double_t        puweight_SysDown;
  Double_t        weight;
  Double_t        weightWjetSF;
  Double_t        xsec;
  Double_t        kfact;
  Double_t        met_px;
  Double_t        met_py;
  Double_t        met_phi;
  Double_t        met_et;
  Double_t        met_sumet;
  Int_t           channel;
  Bool_t          isTauContr;
  Bool_t          isKeepEvent;
  Bool_t          isBTBGood;
  Bool_t          isOSGood;
  Bool_t          isBjetEvt;
  std::vector<int>     *Lep_Id;
  std::vector<double>  *Lep_pt;
  std::vector<double>  *Lep_eta;
  std::vector<double>  *Lep_phi;
  std::vector<double>  *Lep_TrigSF;
  std::vector<double>  *Lep_RecoSF;
  std::vector<double>  *Lep_IDSF;
  std::vector<double>  *Lep_IsoSF;
  std::vector<double>  *Lep_TtvaSF;
  std::vector<double>  *Lep_L1CaloSF;
  std::vector<double>  *Lep_ElOlrSF;
  std::vector<int>     *Lep_nProngs;
  std::vector<double>  *Lep_TrigSF_StatUp;
  std::vector<double>  *Lep_TrigSF_StatDown;
  std::vector<double>  *Lep_TrigSF_SysUp;
  std::vector<double>  *Lep_TrigSF_SysDown;
  std::vector<double>  *Lep_RecoSF_StatUp;
  std::vector<double>  *Lep_RecoSF_StatDown;
  std::vector<double>  *Lep_RecoSF_SysUp;
  std::vector<double>  *Lep_RecoSF_SysDown;
  std::vector<double>  *Lep_RecoSF_Hpt_SysUp;
  std::vector<double>  *Lep_RecoSF_Hpt_SysDown;
  std::vector<double>  *Lep_IDSF_StatUp;
  std::vector<double>  *Lep_IDSF_StatDown;
  std::vector<double>  *Lep_IDSF_SysUp;
  std::vector<double>  *Lep_IDSF_SysDown;
  std::vector<double>  *Lep_IDSF_Hpt_SysUp;
  std::vector<double>  *Lep_IDSF_Hpt_SysDown;
  std::vector<double>  *Lep_IsoSF_StatUp;
  std::vector<double>  *Lep_IsoSF_StatDown;
  std::vector<double>  *Lep_IsoSF_SysUp;
  std::vector<double>  *Lep_IsoSF_SysDown;
  std::vector<double>  *Lep_TtvaSF_StatUp;
  std::vector<double>  *Lep_TtvaSF_StatDown;
  std::vector<double>  *Lep_TtvaSF_SysUp;
  std::vector<double>  *Lep_TtvaSF_SysDown;
  std::vector<double>  *Lep_ElOlrSF_SysUp;
  std::vector<double>  *Lep_ElOlrSF_SysDown;
  std::vector<double>  *Jet_pt;
  std::vector<double>  *Jet_eta;
  std::vector<double>  *Jet_phi;
  std::vector<double>  *Jet_JvtSF;
  std::vector<double>  *Jet_JvtSF_SysUp;
  std::vector<double>  *Jet_JvtSF_SysDown;
  std::vector<double>  *Jet_BtagSF;
  std::vector<double>  *Jet_BtagSF_Beff_SysUp;
  std::vector<double>  *Jet_BtagSF_Beff_SysDown;
  std::vector<double>  *Jet_BtagSF_Ceff_SysUp;
  std::vector<double>  *Jet_BtagSF_Ceff_SysDown;
  std::vector<double>  *Jet_BtagSF_Leff_SysUp;
  std::vector<double>  *Jet_BtagSF_Leff_SysDown;
  std::vector<double>  *Jet_BtagSF_ExtCeff_SysUp;
  std::vector<double>  *Jet_BtagSF_ExtCeff_SysDown;
  std::vector<double>  *Jet_BtagSF_ExtEff_SysUp;
  std::vector<double>  *Jet_BtagSF_ExtEff_SysDown;

  /* Tree Branches */
  TBranch        *b_event;   //!
  TBranch        *b_run;   //!
  TBranch        *b_weight;   //!
  TBranch        *b_dilepMass;   //!
  TBranch        *b_dilepCorrMass;   //!
  TBranch        *b_dilepPt;   //!
  TBranch        *b_dilepCorrPt;   //!
  TBranch        *b_dilepEta;   //!
  TBranch        *b_dilepPhi;   //!
  TBranch        *b_xsec;   //!
  TBranch        *b_kfact;   //!
  TBranch        *b_met_px;   //!
  TBranch        *b_met_py;   //!
  TBranch        *b_met_phi;   //!
  TBranch        *b_met_et;   //!
  TBranch        *b_met_sumet;   //!
  TBranch        *b_channel;   //!
  TBranch        *b_isTauContr;   //!
  TBranch        *b_isKeepEvent;   //!
  TBranch        *b_isBTBGood;  //!
  TBranch        *b_isOSGood;  //!
  TBranch        *b_isBjetEvt;  //!
  TBranch        *b_mcweight;   //!
  TBranch        *b_weightWjetSF;   //!
  TBranch        *b_puweight;   //!
  TBranch        *b_puweight_SysUp;   //!
  TBranch        *b_puweight_SysDown;   //!
  TBranch        *b_Lep_Id;   //!
  TBranch        *b_Lep_pt;   //!
  TBranch        *b_Lep_eta;   //!
  TBranch        *b_Lep_phi;   //!
  TBranch        *b_Lep_TrigSF;   //!
  TBranch        *b_Lep_RecoSF;   //!
  TBranch        *b_Lep_IDSF;   //!
  TBranch        *b_Lep_IsoSF;   //!
  TBranch        *b_Lep_nProngs;  //!
  TBranch        *b_Lep_TrigSF_StatUp;   //!
  TBranch        *b_Lep_TrigSF_StatDown;   //!
  TBranch        *b_Lep_TrigSF_SysUp;   //!
  TBranch        *b_Lep_TrigSF_SysDown;   //!
  TBranch        *b_Lep_RecoSF_StatUp;   //!
  TBranch        *b_Lep_RecoSF_StatDown;   //!
  TBranch        *b_Lep_RecoSF_SysUp;   //!
  TBranch        *b_Lep_RecoSF_SysDown;   //!
  TBranch        *b_Lep_RecoSF_Hpt_SysUp;   //!
  TBranch        *b_Lep_RecoSF_Hpt_SysDown;   //!
  TBranch        *b_Lep_IDSF_StatUp;   //!
  TBranch        *b_Lep_IDSF_StatDown;   //!
  TBranch        *b_Lep_IDSF_SysUp;   //!
  TBranch        *b_Lep_IDSF_SysDown;   //!
  TBranch        *b_Lep_IDSF_Hpt_SysUp;   //!
  TBranch        *b_Lep_IDSF_Hpt_SysDown;   //!
  TBranch        *b_Lep_IsoSF_StatUp;   //!
  TBranch        *b_Lep_IsoSF_StatDown;   //!
  TBranch        *b_Lep_IsoSF_SysUp;   //!
  TBranch        *b_Lep_IsoSF_SysDown;   //!
  TBranch        *b_Lep_TtvaSF;   //!
  TBranch        *b_Lep_TtvaSF_StatUp;  //!
  TBranch        *b_Lep_TtvaSF_StatDown;   //!
  TBranch        *b_Lep_TtvaSF_SysUp;   //!
  TBranch        *b_Lep_TtvaSF_SysDown;   //!
  TBranch        *b_Lep_L1CaloSF;   //!
  TBranch        *b_Lep_ElOlrSF;   //!
  TBranch        *b_Lep_ElOlrSF_SysUp;   //!
  TBranch        *b_Lep_ElOlrSF_SysDown;   //!
  TBranch        *b_Jet_pt;   //!
  TBranch        *b_Jet_eta;   //!
  TBranch        *b_Jet_phi;   //!
  TBranch        *b_Jet_JvtSF;  //!
  TBranch        *b_Jet_JvtSF_SysUp;  //!
  TBranch        *b_Jet_JvtSF_SysDown; //!
  TBranch        *b_Jet_BtagSF;   //!
  TBranch        *b_Jet_BtagSF_Beff_SysUp;   //!
  TBranch        *b_Jet_BtagSF_Beff_SysDown;   //!
  TBranch        *b_Jet_BtagSF_Ceff_SysUp;   //!
  TBranch        *b_Jet_BtagSF_Ceff_SysDown;   //!
  TBranch        *b_Jet_BtagSF_Leff_SysUp;   //!
  TBranch        *b_Jet_BtagSF_Leff_SysDown;   //!
  TBranch        *b_Jet_BtagSF_ExtCeff_SysUp;   //!
  TBranch        *b_Jet_BtagSF_ExtCeff_SysDown;   //!
  TBranch        *b_Jet_BtagSF_ExtEff_SysUp;   //!
  TBranch        *b_Jet_BtagSF_ExtEff_SysDown;   //!
  
};
#endif
