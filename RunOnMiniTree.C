#define RunOnMiniTree_cxx

/* Class includes */
#include "RunOnMiniTree.h"
/* c++ includes */
#include <cassert>
#include <ctime>
#include <sys/stat.h>

class Options{
  
public:
  std::string Sample ;
  std::string BaseDir;
  std::string SysVar ;
  std::string RunType;
  double Lumi        ;
  int LfvType        ;
  bool useBjet       ;
  bool ttbarCR       ;
  bool usePU         ;
  bool doPtRw        ;
  bool WjetCR        ;
  bool metCut        ;
  bool pTlep         ;
  bool SSpair        ;
  bool OSpair        ;
  bool AntiIso       ;
  bool NoTauID       ;
  bool TauFake       ;
  bool TauFakePt     ;
  bool TauFakeEta    ;
  bool QcdCR         ;
  bool DphiRev       ;
  bool BlindData     ;
  bool Blind         ;
  bool doEvtList     ;
  bool useTopSherpa  ;
  bool debug         ;
  bool verbose       ;
  unsigned long long singleEvent;
  std::string GetDateTime(){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer,80,"%d.%m.%Y_%I.%M.%S",timeinfo);
    std::string str(buffer);
    return str;
  }
  
  void SetDefault(){
    Sample        = ""       ;
    BaseDir       = "Ntuples";
    SysVar        = ""       ;
    RunType       = ""       ;
    Lumi          = 36.2     ;
    LfvType       = 1        ;
    useBjet       = false    ;
    ttbarCR       = false    ;
    usePU         = true     ;
    doPtRw        = false    ;
    WjetCR        = false    ;
    metCut        = false    ;
    pTlep         = false    ;
    SSpair        = false    ;
    OSpair        = false    ;
    AntiIso       = false    ;
    NoTauID       = false    ;
    TauFake       = false    ;
    TauFakePt     = false    ;
    TauFakeEta    = false    ;
    QcdCR         = false    ;
    DphiRev       = false    ;
    BlindData     = false    ;
    Blind         = false    ;
    doEvtList     = false    ;
    useTopSherpa  = false    ;
    debug         = false    ;
    verbose       = false    ;
    singleEvent   = 0        ;
  }

  bool checkOpt(char* opt, char* value){
    std::string val = value;
    if( 0==val.find("-") ){
      std::cout << "WARNING:: Option " << opt <<
	" requires value -> skipping " << std::endl;
      return false;
    }
    return true;
  }
  
};

int main( int argc, char* argv[] ) {

  assert(argc>1);
  Options opt;
  opt.SetDefault();
  bool printHelp = false;
  
  for(int i = 1; i < argc; ++i){
    if( !strcmp(argv[i],"--Sample")             ){
      if( opt.checkOpt(argv[i],argv[i+1]) )        opt.Sample  = argv[i+1]; }
    else if( !strcmp(argv[i],"--BaseDir")       ){
      if( opt.checkOpt(argv[i],argv[i+1]) )        opt.BaseDir = argv[i+1]; }
    else if( !strcmp(argv[i],"--SysVar")        ){
      if( opt.checkOpt(argv[i],argv[i+1]) )        opt.SysVar  = argv[i+1]; }
    else if( !strcmp(argv[i],"--RunType")       ){
      if( opt.checkOpt(argv[i],argv[i+1]) )        opt.RunType = argv[i+1]; }
    else if( !strcmp(argv[i],"--Lumi")          ){
      if( opt.checkOpt(argv[i],argv[i+1]) )        opt.Lumi    = std::stod(argv[i+1]); }
    else if( !strcmp(argv[i],"--LFVtype")       ){
      if( opt.checkOpt(argv[i],argv[i+1]) )        opt.LfvType = std::stoi(argv[i+1]); }
    else if( !strcmp(argv[i],"--UseBjet")       ){ opt.useBjet       = true; }
    else if( !strcmp(argv[i],"--ttbarCR")       ){ opt.ttbarCR       = true; }
    else if( !strcmp(argv[i],"--UsePU")         ){ opt.usePU         = true; }
    else if( !strcmp(argv[i],"--doPtRw")        ){ opt.doPtRw        = true; }
    else if( !strcmp(argv[i],"--WjetCR")        ){ opt.WjetCR        = true; }
    else if( !strcmp(argv[i],"--metCut")        ){ opt.metCut        = true; }
    else if( !strcmp(argv[i],"--pTlep")         ){ opt.pTlep         = true; }
    else if( !strcmp(argv[i],"--SSpair")        ){ opt.SSpair        = true; }
    else if( !strcmp(argv[i],"--OSpair")        ){ opt.OSpair        = true; }
    else if( !strcmp(argv[i],"--AntiIso")       ){ opt.AntiIso       = true; }
    else if( !strcmp(argv[i],"--NoTauID")       ){ opt.NoTauID       = true; }
    else if( !strcmp(argv[i],"--TauFake")       ){ opt.TauFake       = true; }
    else if( !strcmp(argv[i],"--useTauFakePt")  ){ opt.TauFakePt     = true; }
    else if( !strcmp(argv[i],"--useTauFakeEta") ){ opt.TauFakeEta    = true; }
    else if( !strcmp(argv[i],"--QcdCR")         ){ opt.QcdCR         = true; }
    else if( !strcmp(argv[i],"--DphiRev")       ){ opt.DphiRev       = true; }
    else if( !strcmp(argv[i],"--BlindData")     ){ opt.BlindData     = true; }
    else if( !strcmp(argv[i],"--Blind")         ){ opt.Blind         = true; }
    else if( !strcmp(argv[i],"--doEvtList")     ){ opt.doEvtList     = true; }
    else if( !strcmp(argv[i],"--useTopSherpa")  ){ opt.useTopSherpa  = true; }
    else if( !strcmp(argv[i],"--singleEvent")   ){ opt.singleEvent   = std::stoull(argv[i+1]); }
    else if( !strcmp(argv[i],"--debug")         ){ opt.debug         = true; }
    else if( !strcmp(argv[i],"--verbose")       ){ opt.verbose       = true; }
    else if( !strcmp(argv[i],"--help")          ){ printHelp         = true; }
  }
  
  if(opt.verbose) opt.debug = true;
  
  if( printHelp ){
    std::cout << "RunOnMiniTree: Run LFV selection on MiniTrees !!" << std::endl;
    std::cout << "  Usage  :  RunOnMiniTree [Options]"         << std::endl;
    std::cout << "              --Sample        [Specify kind of sample to run on. Options"            << std::endl;
    std::cout << "                               are: 'data', 'Top', 'Wjets', 'DY','DiBoson']"         << std::endl;
    std::cout << "              --SysVar        [Specify the Syst Unc. Set]"                           << std::endl;
    std::cout << "              --RunType       [Specify the run type]"                                << std::endl;
    std::cout << "              --LFVtype       [Set lfv channel]"                                     << std::endl;
    std::cout << "              --BaseDir       [Specify base location of minitree:"                   << std::endl;
    std::cout << "                               default is 'Ntuples']"                                << std::endl;
    std::cout << "              --Lumi          [Set integrated lumi: default is 35.7 fb^-1]"          << std::endl;
    std::cout << "              --UseBjet       [Enable b-jet veto: default is 'false']"               << std::endl;
    std::cout << "              --ttbarCR       [Enable ttbar CR: default is 'false']"                 << std::endl;
    std::cout << "              --UsePU         [Use PileUp weight: default is ''true']"               << std::endl;
    std::cout << "              --doPtRw        [Apply pT Re-weight: default is 'false']"              << std::endl;
    std::cout << "              --WjetCR        [Enable W+jets CR cuts: default is 'false']"           << std::endl;
    std::cout << "              --metCut        [Enable met<30 GeV cut: default is 'false']"           << std::endl;
    std::cout << "              --pTlep         [Enable lep pT cut: default is 'false']"               << std::endl;
    std::cout << "              --SSpair        [Select same-sign pairs: default is 'false']"          << std::endl;
    std::cout << "              --OSpair        [Select opp-sign pairs: default is 'false']"           << std::endl;
    std::cout << "              --AntiIso       [Select anti-iso leptons: default is 'false']"         << std::endl;
    std::cout << "              --NoTauID       [Disable/reverse Tau ID: default is 'false']"          << std::endl;
    std::cout << "              --TauFake       [Apply Tau Fake-rate: default is 'false']"             << std::endl;
    std::cout << "              --useTauFakePt  [Apply Tau Fake-rate vs pT: default is 'false']"       << std::endl;
    std::cout << "              --useTauFakeEta [Apply Tau Fake-rate vs eta: default is 'false']"      << std::endl;
    std::cout << "              --QcdCR         [Enable Qcd CR cuts: default is 'false']"              << std::endl;
    std::cout << "              --DphiRev       [Enable Reversing Dphi cut: default is 'false']"       << std::endl;
    std::cout << "              --Blind         [Blind mll'>600 GeV reg: default is 'false']"          << std::endl;
    std::cout << "              --BlindData     [Blind data only: default is 'false']"                 << std::endl;
    std::cout << "              --doEvtList     [Make data event list: default is 'false']"            << std::endl;
    std::cout << "              --useTopSherpa  [Enable using Sherpa ttbar: default is 'false']"       << std::endl;
    std::cout << "              --singleEvent   [Specify event number to debug: default is '0' (all)]" << std::endl;
    std::cout << "              --debug         [Set debug mode: default is 'false']"                  << std::endl;
    std::cout << "              --verbose       [Set verbose mode: default is 'false']"                << std::endl;
    std::cout << "              --help          [Print this help]"                                     << std::endl;
    exit(0);
  }

  if( opt.singleEvent!=0) opt.verbose = true;
  
  if(opt.debug){
    std::cout << "Calling RunOnMiniTree Class with options: " << std::endl;
    std::cout << "  Sample        = " << opt.Sample        << std::endl;
    std::cout << "  SysVar        = " << opt.SysVar        << std::endl;
    std::cout << "  RunType       = " << opt.RunType       << std::endl;
    std::cout << "  LFVtype       = " << opt.LfvType       << std::endl;
    std::cout << "  BaseDir       = " << opt.BaseDir       << std::endl;
    std::cout << "  Lumi          = " << opt.Lumi          << std::endl;
    std::cout << "  UseBjet       = " << opt.useBjet       << std::endl;
    std::cout << "  ttbarCR       = " << opt.ttbarCR       << std::endl;
    std::cout << "  UsePU         = " << opt.usePU         << std::endl;
    std::cout << "  doPtRw        = " << opt.doPtRw        << std::endl;
    std::cout << "  WjetCR        = " << opt.WjetCR        << std::endl;
    std::cout << "  metCut        = " << opt.metCut        << std::endl;
    std::cout << "  pTlep         = " << opt.pTlep         << std::endl;
    std::cout << "  SSpair        = " << opt.SSpair        << std::endl;
    std::cout << "  OSpair        = " << opt.OSpair        << std::endl;
    std::cout << "  AntiIso       = " << opt.AntiIso       << std::endl;
    std::cout << "  NoTauID       = " << opt.NoTauID       << std::endl;
    std::cout << "  TauFake       = " << opt.TauFake       << std::endl;
    std::cout << "  TauFakePt     = " << opt.TauFakePt     << std::endl;
    std::cout << "  TauFakeEta    = " << opt.TauFakeEta    << std::endl;
    std::cout << "  QcdCR         = " << opt.QcdCR         << std::endl;
    std::cout << "  DPhiRev       = " << opt.DphiRev       << std::endl;
    std::cout << "  BlindData     = " << opt.BlindData     << std::endl;
    std::cout << "  Blind         = " << opt.Blind         << std::endl;
    std::cout << "  doEvtList     = " << opt.doEvtList     << std::endl;
    std::cout << "  useTopSherpa  = " << opt.useTopSherpa  << std::endl;
    std::cout << "  singleEvent   = " << opt.singleEvent   << std::endl;
    std::cout << "  debug         = " << opt.debug         << std::endl;
    std::cout << "  verbose       = " << opt.verbose       << std::endl;
  }

  RunOnMiniTree *romt = new RunOnMiniTree(opt.RunType,   opt.Sample,       opt.BaseDir,
					  opt.SysVar,    opt.Lumi,         opt.LfvType,
					  opt.useBjet,   opt.ttbarCR,      opt.usePU,
					  opt.doPtRw,    opt.WjetCR,       opt.metCut,
					  opt.pTlep,     opt.SSpair,       opt.OSpair,
					  opt.AntiIso,   opt.NoTauID,      opt.TauFake,
					  opt.TauFakePt, opt.TauFakeEta,   opt.QcdCR, 
					  opt.DphiRev,   opt.Blind,        opt.BlindData, 
					  opt.doEvtList, opt.useTopSherpa, opt.singleEvent, 
					  opt.debug,     opt.verbose);
  
  romt->Process();
  return 0;
  
}


RunOnMiniTree :: RunOnMiniTree(std::string runType, std::string sample,
			       std::string baseDir, std::string sysVar,
			       double lumi,     int lfvType,    bool useBjet,
			       bool ttbarCR,    bool usePuRw,   bool doPtRw,
			       bool WjetCR,     bool metCut,    bool pTlep,
			       bool ssPair,     bool osPair,    bool antiIso,
			       bool noTauID,    bool tauFake,   bool tauFakePt,
			       bool tauFakeEta, bool QcdCR,     bool DphiRev,
			       bool Blind,      bool BlindData, bool doEvtList,
			       bool useTopSherpa, unsigned long long singleEvent, 
			       bool debug,      bool verbose){

  SetAtlasStyle();
  /* Set Global options */
  m_runType     = runType;
  m_sample      = sample;
  m_baseDir     = baseDir;
  m_lumi        = lumi;
  m_lfvType     = lfvType;
  m_sysVar      = sysVar;
  m_useBjet     = useBjet;
  m_ttbarCR     = ttbarCR;
  m_usePuRw     = usePuRw;
  m_doPtRw      = doPtRw;
  m_wjetCR      = WjetCR;
  m_metCut      = metCut;
  m_pTlep       = pTlep;
  m_ssPair      = ssPair;
  m_osPair      = osPair;
  m_antiIso     = antiIso; 
  m_noTauID     = noTauID;
  m_tauFr       = tauFake;
  m_tauFr_pT    = tauFakePt;
  m_tauFr_eta   = tauFakeEta;
  m_qcdCR       = QcdCR;
  m_dphiRev     = DphiRev;
  m_blindData   = BlindData;
  m_blind       = Blind;
  m_evtList     = doEvtList;
  m_useSherpa   = useTopSherpa;
  m_runEvent    = singleEvent;
  m_debug       = debug;
  m_verbose     = verbose;
  /* Set General variables */
  m_ElId   = 11;
  m_MuId   = 13;
  m_TauId  = 15;
  m_pi     = TMath::Pi();

  if(m_sysVar.find("PtRw")!=std::string::npos){
    std::cout << "< RunOnMiniTree :: Init() > :: found PtRw Sys: "
	      << "enabling pTrw ... " << std::endl;
    m_doPtRw=true;
  }
  if(m_sysVar.find("Comp_Sys")!=std::string::npos){
    std::cout << "< RunOnMiniTree :: Init() > :: found TauFake_Comp_Sys: "
	      << "enabling tauFR vs pT only ... " << std::endl;
     m_tauFr_pT=true;
  }
  
}

void RunOnMiniTree :: Process(){

  SetLFVtypes();
  SetTreeName();
  SetInputDir(m_sample);
  LoadInputs();
  FindTauFakeRateBoundaries();
  DefineSamples();
  DefineOutHistograms();
  SetOutputDir();
  DefineOutFile();

  /* loop over all samples */
  for(int ch=0; ch<(int)m_sampleName.size(); ch++){
    
    std::cout << "< RunOnMiniTree :: Process() > :: Processing Sample = "
	      << m_sampleName.at(ch) << std::endl;
    m_EvtProcessed.clear();
    OpenMiniTree( m_sampleName.at(ch) );
    if(m_evtList && m_sampleName.at(ch)=="data")
      OpenEventListFile();
    LoadAndSetTree();
    m_Nevents = FindTotalEventsSample( m_sampleName.at(ch) );
    SetHistoErrors( m_sampleName.at(ch),ch );
    LoopOnEvents( m_sampleName.at(ch) );
    CloseMiniTree();
  }
  StoreHistograms();
  CleanMemory();
  
}

std::pair<int,double> RunOnMiniTree :: FindMaxBin(TH1F* h){
  
  int bin = 0; double pt=0;
  for(Int_t b=1; b<h->GetNbinsX()+1; b++){
    bin = b;
    pt  = h->GetBinLowEdge(b)+h->GetBinWidth(b);
    if(m_verbose)
      std::cout << "< RunOnMiniTree :: FindMaxBin() > ::  Content = "
		<< h->GetBinContent(b) << "  Bin = " << b
		<< " Max pT = "<<pt<<std::endl;
  }
  std::pair<int,double> m_p = std::make_pair(bin,pt);
  return m_p;
  
}

std::pair<int,double> RunOnMiniTree :: FindMaxBin(TH2F* h){
  
  int bin = 0; double pt=0;
  for(Int_t b=1; b<h->GetNbinsX()+1; b++){
    bin = b;
    pt  = h->GetXaxis()->GetBinLowEdge(b)+h->GetXaxis()->GetBinWidth(b);
    if(m_verbose)
      std::cout << "< RunOnMiniTree :: FindMaxBin() > ::  Content = "
		<< h->GetBinContent(b) << "  Bin = " << b
		<< " Max pT = "<<pt<<std::endl;
  }
  std::pair<int,double> m_p = std::make_pair(bin,pt);
  return m_p;

}


void RunOnMiniTree :: SetLFVtypes(){
  
  if(m_lfvType==1)      { m_lfvName = "e#mu";    m_lfvSt = "emu";   }
  else if(m_lfvType==2) { m_lfvName = "e#tau";   m_lfvSt = "etau";  }
  else if(m_lfvType==3) { m_lfvName = "#mu#tau"; m_lfvSt = "mutau"; }

}

void RunOnMiniTree :: SetTreeName(){
  
  if( m_sample=="data" || m_sysVar=="Nominal"       ||
      m_sysVar.find("PU")      !=std::string::npos  ||
      m_sysVar.find("Reco")    !=std::string::npos  ||
      m_sysVar.find("Iso")     !=std::string::npos  ||
      m_sysVar.find("Trg")     !=std::string::npos  ||
      m_sysVar.find("ElID")    !=std::string::npos  ||
      m_sysVar.find("TTVA")    !=std::string::npos  ||
      m_sysVar.find("EleOlr")  !=std::string::npos  ||
      m_sysVar.find("JetID")   !=std::string::npos  ||
      m_sysVar.find("JvtSF")   !=std::string::npos  ||
      m_sysVar.find("BtagSF")  !=std::string::npos  ||
      m_sysVar.find("TopScale")!=std::string::npos  ||
      m_sysVar.find("TauFake") !=std::string::npos  ||
      m_sysVar.find("Multijet")!=std::string::npos  ||
      m_sysVar.find("TopFit")  !=std::string::npos  ||
      m_sysVar.find("PDF")     !=std::string::npos  ||
      m_sysVar.find("PtRw")    !=std::string::npos   ){
    m_treeName = "lfv";
  }
  else{
    m_treeName = "lfv_"+m_sysVar;
  }
  std::cout << "< RunOnMiniTree :: SetTreeName() > ::  Sample = " << m_sample
	    << " Variation = " << m_sysVar << " Tree = "
	    << m_treeName << std::endl;
  
}

void RunOnMiniTree :: SetInputDir(std::string sample){

  std::cout << "< RunOnMiniTree :: SetInputDir() > :: ";
  if(m_antiIso && !m_noTauID){
    std::cout << "case AntiIso Only -> ";
    m_InDir = m_baseDir+"/NTUP_QCD_LepFake/";
  }
  else if(!m_antiIso && m_noTauID){
    std::cout << "case NoTauId Only -> ";
    if(sample!="Wjets"){
      std::cout << " Non W+jets samples -> ";
      m_InDir = m_baseDir+"/NTUP_Main/";
    }
    else{
      std::cout << " W+jets samples -> ";
      if(m_sysVar=="TauFake_BDT_SysUp")
	m_InDir = m_baseDir+"/NTUP_Wjet_BDT050/";
      else if(m_sysVar=="TauFake_BDT_SysDown")
	m_InDir = m_baseDir+"/NTUP_Wjet_BDT030/";
      else if(m_sysVar=="TauFake_NoBDT")
	m_InDir = m_baseDir+"/NTUP_Wjet_NoBDT/";
      else
	m_InDir = m_baseDir+"/NTUP_Wjet_BDT040/";
    }
  }
  else if(m_antiIso && m_noTauID){
    std::cout << "case AntiIso+NoTauId Only -> ";
    m_InDir = m_baseDir+"/NTUP_QCD_DoubleFake/";
  }
  else{
    std::cout << "case Main Directory -> ";
    m_InDir = m_baseDir+"/NTUP_Main/";
  }
  std::cout << " m_InDir = " << m_InDir << std::endl;
  
}

void RunOnMiniTree :: SetOutputDir(){
  
  if( m_useBjet ){ m_OutDir = "Bjet";  }
  else{            m_OutDir = "NoBjet"; }

  if(m_runType.find("TopExtra")!=std::string::npos)      m_OutDir += "/topExtraInput";

  if(m_runType.find("ttbarCR")!=std::string::npos){      m_OutDir += "/ttbarCR";
    if(m_useSherpa)                                      m_OutDir += "_Sherpa";
  }
  if(m_runType.find("revDphi")!=std::string::npos)       m_OutDir += "/revDphi";
  if(m_runType.find("WjetCR")!=std::string::npos)        m_OutDir += "/WjetCR";
  if(m_runType.find("WjetSR")!=std::string::npos)        m_OutDir += "/WjetSR";
  
  if(m_runType.find("QcdReg1")!=std::string::npos)       m_OutDir += "/QcdReg1";
  if(m_runType.find("QcdReg2")!=std::string::npos)       m_OutDir += "/QcdReg2";
  if(m_runType.find("QcdReg3")!=std::string::npos)       m_OutDir += "/QcdReg3";

  if(m_runType.find("WjetNoTauId")!=std::string::npos)   m_OutDir += "/WjetNoTauId";

  if(m_runType.find("SS")!=std::string::npos)            m_OutDir += "_SS";
  if(m_runType.find("OS")!=std::string::npos)            m_OutDir += "_OS";

  if(m_runType.find("LepFake")!=std::string::npos)       m_OutDir += "/LepFake/";
  else if(m_runType.find("DoubFake")!=std::string::npos) m_OutDir += "/DoubFake/";
  else                                                   m_OutDir += "/";
     
  std::cout << "< RunOnMiniTree :: SetOutputDir() > :: Out Directory is "
	    << m_OutDir << std::endl;
  CheckOutDir();
  
}

void RunOnMiniTree :: CheckOutDir(){

  std::string tmp_s = m_OutDir;
  std::string delim = "/";
  size_t pos = 0;
  while( (pos = tmp_s.find(delim)) != std::string::npos ){
    m_dirs.push_back( tmp_s.substr(0, pos) );
    tmp_s.erase(0, pos + delim.length());
  }

  m_tmpOutDir = "";
  for(uint i=0; i<m_dirs.size(); i++){
    struct stat st;
    m_tmpOutDir+=m_dirs.at(i)+"/";
    if(stat(m_tmpOutDir.c_str(),&st) == 0){
      std::cout << "< RunOnMiniTree :: CheckOutDir() > :: "
		<< "\033[1;32m Out Directory " << m_tmpOutDir
		<< " already present!\033[0m" << std::endl;
    }
    else{
      std::cout << "< RunOnMiniTree :: CheckOutDir() > :: "
		<< "\033[1;34m Creating Directory " << m_tmpOutDir
		<< " ... \033[0m" << std::endl;
      int outD = system( ("mkdir "+m_tmpOutDir).c_str() );
      if(outD!=0)
	std::cout << "< RunOnMiniTree :: CheckOutDir() > :: "
		  << "\033[1;31m Directory " << m_tmpOutDir
		  << " could not be created!\033[0m" << std::endl;
    }
  }
  m_dirs.clear();
  
}

void RunOnMiniTree :: LoadInputs(){

  if(m_verbose)
    std::cout << "< RunOnMiniTree :: LoadInputs() > :: loading input histos " << std::endl;

  m_pdfIn  = new TFile("VarInputs/PDFVariation.root");
  m_pdfDb  = (TH1F*)m_pdfIn->Get("PDFVar_Dib");
  m_pdfTop = (TH1F*)m_pdfIn->Get("PDFVar_Top");

  if(m_useBjet)
    m_scaleIn = new TFile("VarInputs/TopScaleVariation_BjetVeto.root");
  else
    m_scaleIn = new TFile("VarInputs/TopScaleVariation.root");
  m_scaleUp = (TH1F*)m_scaleIn->Get( ("hTopScaleUp_"+m_lfvSt).c_str()   );
  m_scaleDw = (TH1F*)m_scaleIn->Get( ("hTopScaleDown_"+m_lfvSt).c_str() );
  
  if(m_useBjet)
    m_tauFrIn = new TFile("VarInputs/TauFakeFactors_BjetVeto.root");
  else
    m_tauFrIn = new TFile("VarInputs/TauFakeFactors.root");
  
  if(m_sysVar=="TauFake_BDT_SysUp"){
    m_FR1p_pT    = (TH1F*)m_tauFrIn->Get( "Tau_pT_Fraction_1prong_BDT_SysUp"    );
    m_FR3p_pT    = (TH1F*)m_tauFrIn->Get( "Tau_pT_Fraction_3prong_BDT_SysUp"    );
    m_FR1p_Eta   = (TH1F*)m_tauFrIn->Get( "Tau_Eta_Fraction_1prong_BDT_SysUp"   );
    m_FR3p_Eta   = (TH1F*)m_tauFrIn->Get( "Tau_Eta_Fraction_3prong_BDT_SysUp"   );
    m_FR1p_pTeta = (TH2F*)m_tauFrIn->Get( "Tau_pTeta_Fraction_1prong_BDT_SysUp" );
    m_FR3p_pTeta = (TH2F*)m_tauFrIn->Get( "Tau_pTeta_Fraction_3prong_BDT_SysUp" );
  }
  else if(m_sysVar=="TauFake_BDT_SysDown"){
    m_FR1p_pT    = (TH1F*)m_tauFrIn->Get( "Tau_pT_Fraction_1prong_BDT_SysDown"    );
    m_FR3p_pT    = (TH1F*)m_tauFrIn->Get( "Tau_pT_Fraction_3prong_BDT_SysDown"    );
    m_FR1p_Eta   = (TH1F*)m_tauFrIn->Get( "Tau_Eta_Fraction_1prong_BDT_SysDown"   );
    m_FR3p_Eta   = (TH1F*)m_tauFrIn->Get( "Tau_Eta_Fraction_3prong_BDT_SysDown"   );
    m_FR1p_pTeta = (TH2F*)m_tauFrIn->Get( "Tau_pTeta_Fraction_1prong_BDT_SysDown" );
    m_FR3p_pTeta = (TH2F*)m_tauFrIn->Get( "Tau_pTeta_Fraction_3prong_BDT_SysDown" );
  }
  else if(m_sysVar=="TauFake_CR_Sys"){
    m_FR1p_pT    = (TH1F*)m_tauFrIn->Get( "Tau_pT_Fraction_1prong_SysCR"    );
    m_FR3p_pT    = (TH1F*)m_tauFrIn->Get( "Tau_pT_Fraction_3prong_SysCR"    );
    m_FR1p_Eta   = (TH1F*)m_tauFrIn->Get( "Tau_Eta_Fraction_1prong_SysCR"   );
    m_FR3p_Eta   = (TH1F*)m_tauFrIn->Get( "Tau_Eta_Fraction_3prong_SysCR"   );
    m_FR1p_pTeta = (TH2F*)m_tauFrIn->Get( "Tau_pTeta_Fraction_1prong_SysCR" );
    m_FR3p_pTeta = (TH2F*)m_tauFrIn->Get( "Tau_pTeta_Fraction_3prong_SysCR" );
  }
  else if(m_sysVar=="TauFake_StatUp"){
    m_FR1p_pT    = (TH1F*)m_tauFrIn->Get( "Tau_pT_Fraction_1prong_StatUp"    );
    m_FR3p_pT    = (TH1F*)m_tauFrIn->Get( "Tau_pT_Fraction_3prong_StatUp"    );
    m_FR1p_Eta   = (TH1F*)m_tauFrIn->Get( "Tau_Eta_Fraction_1prong_StatUp"   );
    m_FR3p_Eta   = (TH1F*)m_tauFrIn->Get( "Tau_Eta_Fraction_3prong_StatUp"   );
    m_FR1p_pTeta = (TH2F*)m_tauFrIn->Get( "Tau_pTeta_Fraction_1prong_StatUp" );
    m_FR3p_pTeta = (TH2F*)m_tauFrIn->Get( "Tau_pTeta_Fraction_3prong_StatUp" );
  }
  else if(m_sysVar=="TauFake_StatDown"){
    m_FR1p_pT    = (TH1F*)m_tauFrIn->Get( "Tau_pT_Fraction_1prong_StatDown"    );
    m_FR3p_pT    = (TH1F*)m_tauFrIn->Get( "Tau_pT_Fraction_3prong_StatDown"    );
    m_FR1p_Eta   = (TH1F*)m_tauFrIn->Get( "Tau_Eta_Fraction_1prong_StatDown"   );
    m_FR3p_Eta   = (TH1F*)m_tauFrIn->Get( "Tau_Eta_Fraction_3prong_StatDown"   );
    m_FR1p_pTeta = (TH2F*)m_tauFrIn->Get( "Tau_pTeta_Fraction_1prong_StatDown" );
    m_FR3p_pTeta = (TH2F*)m_tauFrIn->Get( "Tau_pTeta_Fraction_3prong_StatDown" );
  }
  else if(m_sysVar=="TauFake_NoBDT"){
    m_FR1p_pT    = (TH1F*)m_tauFrIn->Get( "Tau_pT_Fraction_1prong_NoBDT"    );
    m_FR3p_pT    = (TH1F*)m_tauFrIn->Get( "Tau_pT_Fraction_3prong_NoBDT"    );
    m_FR1p_Eta   = (TH1F*)m_tauFrIn->Get( "Tau_Eta_Fraction_1prong_NoBDT"   );
    m_FR3p_Eta   = (TH1F*)m_tauFrIn->Get( "Tau_Eta_Fraction_3prong_NoBDT"   );
    m_FR1p_pTeta = (TH2F*)m_tauFrIn->Get( "Tau_pTeta_Fraction_1prong_NoBDT" );
    m_FR3p_pTeta = (TH2F*)m_tauFrIn->Get( "Tau_pTeta_Fraction_3prong_NoBDT" );
  }
  else if(m_sysVar=="TauFake_Comp_SysUp"){
    m_FR1p_pT = (TH1F*)m_tauFrIn->Get( "Tau_pT_Fraction_1prong_Comp_SysUp" );
    m_FR3p_pT = (TH1F*)m_tauFrIn->Get( "Tau_pT_Fraction_3prong_Comp_SysUp" );
  }
   else if(m_sysVar=="TauFake_Comp_SysDown"){
    m_FR1p_pT = (TH1F*)m_tauFrIn->Get( "Tau_pT_Fraction_1prong_Comp_SysDown" );
    m_FR3p_pT = (TH1F*)m_tauFrIn->Get( "Tau_pT_Fraction_3prong_Comp_SysDown" );
   }
  else{
    m_FR1p_pT    = (TH1F*)m_tauFrIn->Get( "Tau_pT_Fraction_1prong_Nom"    );
    m_FR3p_pT    = (TH1F*)m_tauFrIn->Get( "Tau_pT_Fraction_3prong_Nom"    );
    m_FR1p_Eta   = (TH1F*)m_tauFrIn->Get( "Tau_Eta_Fraction_1prong_Nom"   );
    m_FR3p_Eta   = (TH1F*)m_tauFrIn->Get( "Tau_Eta_Fraction_3prong_Nom"   );
    m_FR1p_pTeta = (TH2F*)m_tauFrIn->Get( "Tau_pTeta_Fraction_1prong_Nom" );
    m_FR3p_pTeta = (TH2F*)m_tauFrIn->Get( "Tau_pTeta_Fraction_3prong_Nom" );
  }

  FillPtWeightsVec();
  
}

void RunOnMiniTree :: FindTauFakeRateBoundaries(){

  if(m_verbose)
    std::cout << "< RunOnMiniTree :: FindTauFakeRateBoundaries() > :: " 
	      << "detectin tau FR boundaries ... " << std::endl;

  /* Find Max Bin of Tau Fake Factor */
  if(m_tauFr_pT){
    MaxBin_1p = FindMaxBin(m_FR1p_pT).first;
    MaxBin_3p = FindMaxBin(m_FR3p_pT).first;
    MaxPt_1p  = FindMaxBin(m_FR1p_pT).second;
    MaxPt_3p  = FindMaxBin(m_FR3p_pT).second;
  }
  else if(m_tauFr_eta){
    MaxBin_1p = FindMaxBin(m_FR1p_pT).first;
    MaxBin_3p = FindMaxBin(m_FR3p_pT).first;
    MaxPt_1p  = FindMaxBin(m_FR1p_pT).second;
    MaxPt_3p  = FindMaxBin(m_FR3p_pT).second;
  }
  else{
    MaxBin_1p = FindMaxBin(m_FR1p_pTeta).first;
    MaxBin_3p = FindMaxBin(m_FR3p_pTeta).first;
    MaxPt_1p  = FindMaxBin(m_FR1p_pTeta).second;
    MaxPt_3p  = FindMaxBin(m_FR3p_pTeta).second;
  }
  
}

void RunOnMiniTree :: DefineOutFile(){

  std::string outName = m_OutDir+"Plots_"+m_sysVar+"_"+m_lfvSt;
  if(m_blind)                                              outName += "_Blind";
  else if(m_blindData)                                     outName += "_BlindData";
  else if(m_runType.find("Signal")!=std::string::npos)     outName += "_Signals";
  else if(m_runType=="WjetsMC")                            outName += "_WjetsMC";
  if(m_doPtRw && m_sysVar.find("PtRw")==std::string::npos) outName += "_PtRw";
  
  outName += ".root";
  
  if(m_sample=="data")
    m_Output = new TFile( outName.c_str(),"RECREATE");
  else
    m_Output = new TFile( outName.c_str(),"UPDATE");
  
  if(m_verbose)
    std::cout << "< RunOnMiniTree :: DefineOutFile() > :: "
	      << " OutFileName = " << outName << std::endl;

}

void RunOnMiniTree :: OpenMiniTree(std::string name){

  if( name=="data" ){ m_Input = new TFile( (m_InDir+name+".root").c_str() ); }
  else              { m_Input = new TFile( (m_InDir+name+".root").c_str() ); }
  
}

void RunOnMiniTree :: CloseMiniTree(){

  m_Input->Close();
  
}

void RunOnMiniTree :: LoadAndSetTree(){

  InitTreeVariables();
  SetTreeAndBranches();
  
}

void RunOnMiniTree :: DefineSamples(){

  if(m_verbose)
    std::cout << "< RunOnMiniTree :: DefineSamples() > :: " 
	      <<"defining samples ... " << std::endl;
  
  /* data */
  if(m_sample=="data")
    m_sampleName.push_back( "data" );

  /* signal */
  else if(m_sample.find("Zprime")!=std::string::npos ||
	  m_sample.find("QBH")   !=std::string::npos || 
	  m_sample.find("SVT")   !=std::string::npos  ){
    m_sampleName.push_back( (m_sample+"_"+m_lfvSt).c_str() );
  }
  
  /* DiBoson */
  else if(m_sample=="DiBoson"){
    m_sampleName.push_back( "DiBoson_llll"               );
    m_sampleName.push_back( "DiBoson_lllvOFMinus"        );
    m_sampleName.push_back( "DiBoson_lllvOFPlus"         );
    m_sampleName.push_back( "DiBoson_lllvSFMinus"        );
    m_sampleName.push_back( "DiBoson_lllvSFPlus"         );
    m_sampleName.push_back( "DiBoson_WplvWmqq"           );
    m_sampleName.push_back( "DiBoson_WpqqWmlv"           );
    m_sampleName.push_back( "DiBoson_WlvZqq"             );
    m_sampleName.push_back( "DiBoson_WqqZll"             );
    m_sampleName.push_back( "DiBoson_WqqZvv"             );
    m_sampleName.push_back( "DiBoson_ZqqZll"             );
    m_sampleName.push_back( "DiBoson_ZqqZvv"             );
    m_sampleName.push_back( "DiBoson_evev_50M150"        );
    m_sampleName.push_back( "DiBoson_evev_150M500"       );
    m_sampleName.push_back( "DiBoson_evev_500M1000"      );
    m_sampleName.push_back( "DiBoson_evev_1000M2000"     );
    m_sampleName.push_back( "DiBoson_evev_2000M3000"     );
    m_sampleName.push_back( "DiBoson_evev_3000M4000"     );
    m_sampleName.push_back( "DiBoson_evev_4000M5000"     );
    m_sampleName.push_back( "DiBoson_evev_5000M"         );
    m_sampleName.push_back( "DiBoson_muvmuv_50M150"      );
    m_sampleName.push_back( "DiBoson_muvmuv_150M500"     );
    m_sampleName.push_back( "DiBoson_muvmuv_500M1000"    );
    m_sampleName.push_back( "DiBoson_muvmuv_1000M2000"   );
    m_sampleName.push_back( "DiBoson_muvmuv_2000M3000"   );
    m_sampleName.push_back( "DiBoson_muvmuv_3000M4000"   );
    m_sampleName.push_back( "DiBoson_muvmuv_4000M5000"   );
    m_sampleName.push_back( "DiBoson_muvmuv_5000M"       );
    m_sampleName.push_back( "DiBoson_evmuv_0M150"        );
    m_sampleName.push_back( "DiBoson_evmuv_150M500"      );
    m_sampleName.push_back( "DiBoson_evmuv_500M1000"     );
    m_sampleName.push_back( "DiBoson_evmuv_1000M2000"    );
    m_sampleName.push_back( "DiBoson_evmuv_2000M3000"    );
    m_sampleName.push_back( "DiBoson_evmuv_3000M4000"    );
    m_sampleName.push_back( "DiBoson_evmuv_4000M5000"    );
    m_sampleName.push_back( "DiBoson_evmuv_M5000"        );
    m_sampleName.push_back( "DiBoson_evtauv_0M150"       );
    m_sampleName.push_back( "DiBoson_evtauv_150M500"     );
    m_sampleName.push_back( "DiBoson_evtauv_500M1000"    );
    m_sampleName.push_back( "DiBoson_evtauv_1000M2000"   );
    m_sampleName.push_back( "DiBoson_evtauv_2000M3000"   );
    m_sampleName.push_back( "DiBoson_evtauv_3000M4000"   );
    m_sampleName.push_back( "DiBoson_evtauv_4000M5000"   );
    m_sampleName.push_back( "DiBoson_evtauv_M5000"       );
    m_sampleName.push_back( "DiBoson_muvtauv_0M150"      );
    m_sampleName.push_back( "DiBoson_muvtauv_150M500"    );
    m_sampleName.push_back( "DiBoson_muvtauv_500M1000"   );
    m_sampleName.push_back( "DiBoson_muvtauv_1000M2000"  );
    m_sampleName.push_back( "DiBoson_muvtauv_2000M3000"  );
    m_sampleName.push_back( "DiBoson_muvtauv_3000M4000"  );
    m_sampleName.push_back( "DiBoson_muvtauv_4000M5000"  );
    m_sampleName.push_back( "DiBoson_muvtauv_M5000"      );
    m_sampleName.push_back( "DiBoson_tauvtauv_0M150"     );
    m_sampleName.push_back( "DiBoson_tauvtauv_150M500"   );
    m_sampleName.push_back( "DiBoson_tauvtauv_500M1000"  );
    m_sampleName.push_back( "DiBoson_tauvtauv_1000M2000" );
    m_sampleName.push_back( "DiBoson_tauvtauv_2000M3000" );
    m_sampleName.push_back( "DiBoson_tauvtauv_3000M4000" );
    m_sampleName.push_back( "DiBoson_tauvtauv_4000M5000" );
    m_sampleName.push_back( "DiBoson_tauvtauv_M5000"     );
  }

  /* DYee */
  else if(m_sample=="DYee"){
    m_sampleName.push_back( "Zee"            );
    m_sampleName.push_back( "DYee_120M180"   );
    m_sampleName.push_back( "DYee_180M250"   );
    m_sampleName.push_back( "DYee_250M400"   );
    m_sampleName.push_back( "DYee_400M600"   );
    m_sampleName.push_back( "DYee_600M800"   );
    m_sampleName.push_back( "DYee_800M1000"  );
    m_sampleName.push_back( "DYee_1000M1250" );
    m_sampleName.push_back( "DYee_1250M1500" );
    m_sampleName.push_back( "DYee_1500M1750" );
    m_sampleName.push_back( "DYee_1750M2000" );
    m_sampleName.push_back( "DYee_2000M2250" );
    m_sampleName.push_back( "DYee_2250M2500" );
    m_sampleName.push_back( "DYee_2500M2750" );
    m_sampleName.push_back( "DYee_2750M3000" );
    m_sampleName.push_back( "DYee_3000M3500" );
    m_sampleName.push_back( "DYee_3500M4000" );
    m_sampleName.push_back( "DYee_4000M4500" );
    m_sampleName.push_back( "DYee_4500M5000" );
    m_sampleName.push_back( "DYee_5000M"     );
  }

  /* DYmumu */
  else if(m_sample=="DYmumu"){
    m_sampleName.push_back( "Zmumu"            );
    m_sampleName.push_back( "DYmumu_120M180"   );
    m_sampleName.push_back( "DYmumu_180M250"   );
    m_sampleName.push_back( "DYmumu_250M400"   );
    m_sampleName.push_back( "DYmumu_400M600"   );
    m_sampleName.push_back( "DYmumu_600M800"   );
    m_sampleName.push_back( "DYmumu_800M1000"  );
    m_sampleName.push_back( "DYmumu_1000M1250" );
    m_sampleName.push_back( "DYmumu_1250M1500" );
    m_sampleName.push_back( "DYmumu_1500M1750" );
    m_sampleName.push_back( "DYmumu_1750M2000" );
    m_sampleName.push_back( "DYmumu_2000M2250" );
    m_sampleName.push_back( "DYmumu_2250M2500" );
    m_sampleName.push_back( "DYmumu_2500M2750" );
    m_sampleName.push_back( "DYmumu_2750M3000" );
    m_sampleName.push_back( "DYmumu_3000M3500" );
    m_sampleName.push_back( "DYmumu_3500M4000" );
    m_sampleName.push_back( "DYmumu_4000M4500" );
    m_sampleName.push_back( "DYmumu_4500M5000" );
    m_sampleName.push_back( "DYmumu_5000M"     );
  }

  /* DYtautau */
  else if(m_sample=="DYtautau"){
    m_sampleName.push_back( "Ztautau"            );
    m_sampleName.push_back( "DYtautau_120M180"   );
    m_sampleName.push_back( "DYtautau_180M250"   );
    m_sampleName.push_back( "DYtautau_250M400"   );
    m_sampleName.push_back( "DYtautau_400M600"   );
    m_sampleName.push_back( "DYtautau_600M800"   );
    m_sampleName.push_back( "DYtautau_800M1000"  );
    m_sampleName.push_back( "DYtautau_1000M1250" );
    m_sampleName.push_back( "DYtautau_1250M1500" );
    m_sampleName.push_back( "DYtautau_1500M1750" );
    m_sampleName.push_back( "DYtautau_1750M2000" );
    m_sampleName.push_back( "DYtautau_2000M2250" );
    m_sampleName.push_back( "DYtautau_2250M2500" );
    m_sampleName.push_back( "DYtautau_2500M2750" );
    m_sampleName.push_back( "DYtautau_2750M3000" );
    m_sampleName.push_back( "DYtautau_3000M3500" );
    m_sampleName.push_back( "DYtautau_3500M4000" );
    m_sampleName.push_back( "DYtautau_4000M4500" );
    m_sampleName.push_back( "DYtautau_4500M5000" );
    m_sampleName.push_back( "DYtautau_5000M"     );
  }

  /* Zll */
  else if(m_sample=="Zgamma"){
    m_sampleName.push_back( "Zee"     );
    m_sampleName.push_back( "Zmumu"   );
    m_sampleName.push_back( "Ztautau" );
  }

  /* DYll */
  else if(m_sample=="DYgamma"){
    m_sampleName.push_back( "DYee_120M180"       );
    m_sampleName.push_back( "DYee_180M250"       );
    m_sampleName.push_back( "DYee_250M400"       );
    m_sampleName.push_back( "DYee_400M600"       );
    m_sampleName.push_back( "DYee_600M800"       );
    m_sampleName.push_back( "DYee_800M1000"      );
    m_sampleName.push_back( "DYee_1000M1250"     );
    m_sampleName.push_back( "DYee_1250M1500"     );
    m_sampleName.push_back( "DYee_1500M1750"     );
    m_sampleName.push_back( "DYee_1750M2000"     );
    m_sampleName.push_back( "DYee_2000M2250"     );
    m_sampleName.push_back( "DYee_2250M2500"     );
    m_sampleName.push_back( "DYee_2500M2750"     );
    m_sampleName.push_back( "DYee_2750M3000"     );
    m_sampleName.push_back( "DYee_3000M3500"     );
    m_sampleName.push_back( "DYee_3500M4000"     );
    m_sampleName.push_back( "DYee_4000M4500"     );
    m_sampleName.push_back( "DYee_4500M5000"     );
    m_sampleName.push_back( "DYee_5000M"         );
    m_sampleName.push_back( "DYmumu_120M180"     );
    m_sampleName.push_back( "DYmumu_180M250"     );
    m_sampleName.push_back( "DYmumu_250M400"     );
    m_sampleName.push_back( "DYmumu_400M600"     );
    m_sampleName.push_back( "DYmumu_600M800"     );
    m_sampleName.push_back( "DYmumu_800M1000"    );
    m_sampleName.push_back( "DYmumu_1000M1250"   );
    m_sampleName.push_back( "DYmumu_1250M1500"   );
    m_sampleName.push_back( "DYmumu_1500M1750"   );
    m_sampleName.push_back( "DYmumu_1750M2000"   );
    m_sampleName.push_back( "DYmumu_2000M2250"   );
    m_sampleName.push_back( "DYmumu_2250M2500"   );
    m_sampleName.push_back( "DYmumu_2500M2750"   );
    m_sampleName.push_back( "DYmumu_2750M3000"   );
    m_sampleName.push_back( "DYmumu_3000M3500"   );
    m_sampleName.push_back( "DYmumu_3500M4000"   );
    m_sampleName.push_back( "DYmumu_4000M4500"   );
    m_sampleName.push_back( "DYmumu_4500M5000"   );
    m_sampleName.push_back( "DYmumu_5000M"       );
    m_sampleName.push_back( "DYtautau_120M180"   );
    m_sampleName.push_back( "DYtautau_180M250"   );
    m_sampleName.push_back( "DYtautau_250M400"   );
    m_sampleName.push_back( "DYtautau_400M600"   );
    m_sampleName.push_back( "DYtautau_600M800"   );
    m_sampleName.push_back( "DYtautau_800M1000"  );
    m_sampleName.push_back( "DYtautau_1000M1250" );
    m_sampleName.push_back( "DYtautau_1250M1500" );
    m_sampleName.push_back( "DYtautau_1500M1750" );
    m_sampleName.push_back( "DYtautau_1750M2000" );
    m_sampleName.push_back( "DYtautau_2000M2250" );
    m_sampleName.push_back( "DYtautau_2250M2500" );
    m_sampleName.push_back( "DYtautau_2500M2750" );
    m_sampleName.push_back( "DYtautau_2750M3000" );
    m_sampleName.push_back( "DYtautau_3000M3500" );
    m_sampleName.push_back( "DYtautau_3500M4000" );
    m_sampleName.push_back( "DYtautau_4000M4500" );
    m_sampleName.push_back( "DYtautau_4500M5000" );
    m_sampleName.push_back( "DYtautau_5000M"     );
  }

  /* Z/DY */
  else if(m_sample=="DY"){
    m_sampleName.push_back( "Zee"                );
    m_sampleName.push_back( "DYee_120M180"       );
    m_sampleName.push_back( "DYee_180M250"       );
    m_sampleName.push_back( "DYee_250M400"       );
    m_sampleName.push_back( "DYee_400M600"       );
    m_sampleName.push_back( "DYee_600M800"       );
    m_sampleName.push_back( "DYee_800M1000"      );
    m_sampleName.push_back( "DYee_1000M1250"     );
    m_sampleName.push_back( "DYee_1250M1500"     );
    m_sampleName.push_back( "DYee_1500M1750"     );
    m_sampleName.push_back( "DYee_1750M2000"     );
    m_sampleName.push_back( "DYee_2000M2250"     );
    m_sampleName.push_back( "DYee_2250M2500"     );
    m_sampleName.push_back( "DYee_2500M2750"     );
    m_sampleName.push_back( "DYee_2750M3000"     );
    m_sampleName.push_back( "DYee_3000M3500"     );
    m_sampleName.push_back( "DYee_3500M4000"     );
    m_sampleName.push_back( "DYee_4000M4500"     );
    m_sampleName.push_back( "DYee_4500M5000"     );
    m_sampleName.push_back( "DYee_5000M"         );
    m_sampleName.push_back( "Zmumu"              );
    m_sampleName.push_back( "DYmumu_120M180"     );
    m_sampleName.push_back( "DYmumu_180M250"     );
    m_sampleName.push_back( "DYmumu_250M400"     );
    m_sampleName.push_back( "DYmumu_400M600"     );
    m_sampleName.push_back( "DYmumu_600M800"     );
    m_sampleName.push_back( "DYmumu_800M1000"    );
    m_sampleName.push_back( "DYmumu_1000M1250"   );
    m_sampleName.push_back( "DYmumu_1250M1500"   );
    m_sampleName.push_back( "DYmumu_1500M1750"   );
    m_sampleName.push_back( "DYmumu_1750M2000"   );
    m_sampleName.push_back( "DYmumu_2000M2250"   );
    m_sampleName.push_back( "DYmumu_2250M2500"   );
    m_sampleName.push_back( "DYmumu_2500M2750"   );
    m_sampleName.push_back( "DYmumu_2750M3000"   );
    m_sampleName.push_back( "DYmumu_3000M3500"   );
    m_sampleName.push_back( "DYmumu_3500M4000"   );
    m_sampleName.push_back( "DYmumu_4000M4500"   );
    m_sampleName.push_back( "DYmumu_4500M5000"   );
    m_sampleName.push_back( "DYmumu_5000M"       );
    m_sampleName.push_back( "Ztautau"            );
    m_sampleName.push_back( "DYtautau_120M180"   );
    m_sampleName.push_back( "DYtautau_180M250"   );
    m_sampleName.push_back( "DYtautau_250M400"   );
    m_sampleName.push_back( "DYtautau_400M600"   );
    m_sampleName.push_back( "DYtautau_600M800"   );
    m_sampleName.push_back( "DYtautau_800M1000"  );
    m_sampleName.push_back( "DYtautau_1000M1250" );
    m_sampleName.push_back( "DYtautau_1250M1500" );
    m_sampleName.push_back( "DYtautau_1500M1750" );
    m_sampleName.push_back( "DYtautau_1750M2000" );
    m_sampleName.push_back( "DYtautau_2000M2250" );
    m_sampleName.push_back( "DYtautau_2250M2500" );
    m_sampleName.push_back( "DYtautau_2500M2750" );
    m_sampleName.push_back( "DYtautau_2750M3000" );
    m_sampleName.push_back( "DYtautau_3000M3500" );
    m_sampleName.push_back( "DYtautau_3500M4000" );
    m_sampleName.push_back( "DYtautau_4000M4500" );
    m_sampleName.push_back( "DYtautau_4500M5000" );
    m_sampleName.push_back( "DYtautau_5000M"     );
  }
  
  /* ttbar and single-top */
  else if(m_sample=="Top"){
    if(m_sysVar=="TopScale_SysUp") //&& m_runType=="TopExtra")
      m_sampleName.push_back( "ttbar_incl_SysUp" );
    else if(m_sysVar=="TopScale_SysDown") //&& m_runType=="TopExtra")
      m_sampleName.push_back( "ttbar_incl_SysDown" );
    else if(m_useSherpa){
      m_sampleName.push_back( "ttbar_ee_0M150"         );
      m_sampleName.push_back( "ttbar_ee_150M250"       );
      m_sampleName.push_back( "ttbar_ee_250M500"       );
      m_sampleName.push_back( "ttbar_ee_500M1000"      );
      m_sampleName.push_back( "ttbar_ee_1000M2000"     );
      m_sampleName.push_back( "ttbar_ee_2000M3000"     );
      m_sampleName.push_back( "ttbar_ee_3000M4000"     );
      m_sampleName.push_back( "ttbar_ee_4000M5000"     );
      m_sampleName.push_back( "ttbar_ee_5000M"         );
      m_sampleName.push_back( "ttbar_mumu_0M150"       );
      m_sampleName.push_back( "ttbar_mumu_150M250"     );
      m_sampleName.push_back( "ttbar_mumu_250M500"     );
      m_sampleName.push_back( "ttbar_mumu_500M1000"    );
      m_sampleName.push_back( "ttbar_mumu_1000M2000"   );
      m_sampleName.push_back( "ttbar_mumu_2000M3000"   );
      m_sampleName.push_back( "ttbar_mumu_3000M4000"   );
      m_sampleName.push_back( "ttbar_mumu_4000M5000"   );
      m_sampleName.push_back( "ttbar_mumu_5000M"       );
      m_sampleName.push_back( "ttbar_emu_0M150"        );
      m_sampleName.push_back( "ttbar_emu_150M500"      );
      m_sampleName.push_back( "ttbar_emu_500M1000"     );
      m_sampleName.push_back( "ttbar_emu_1000M2000"    );
      m_sampleName.push_back( "ttbar_emu_2000M3000"    );
      m_sampleName.push_back( "ttbar_emu_M3000"        );
      m_sampleName.push_back( "ttbar_etau_0M150"       );
      m_sampleName.push_back( "ttbar_etau_150M500"     );
      m_sampleName.push_back( "ttbar_etau_500M1000"    );
      m_sampleName.push_back( "ttbar_etau_1000M2000"   );
      m_sampleName.push_back( "ttbar_etau_2000M3000"   );
      m_sampleName.push_back( "ttbar_etau_M3000"       );
      m_sampleName.push_back( "ttbar_etau_M3000"       );
      m_sampleName.push_back( "ttbar_mutau_0M150"      );
      m_sampleName.push_back( "ttbar_mutau_150M500"    );
      m_sampleName.push_back( "ttbar_mutau_500M1000"   );
      m_sampleName.push_back( "ttbar_mutau_1000M2000"  );
      m_sampleName.push_back( "ttbar_mutau_2000M3000"  );
      m_sampleName.push_back( "ttbar_mutau_M3000"      );
      m_sampleName.push_back( "ttbar_tautau_0M150"     );
      m_sampleName.push_back( "ttbar_tautau_150M500"   );
      m_sampleName.push_back( "ttbar_tautau_500M1000"  );
      m_sampleName.push_back( "ttbar_tautau_1000M2000" );
      m_sampleName.push_back( "ttbar_tautau_2000M3000" );
      m_sampleName.push_back( "ttbar_tautau_M3000"     );
    }
    else
      m_sampleName.push_back( "ttbar_incl" );
    m_sampleName.push_back( "Wt_antitop" );
    m_sampleName.push_back( "Wt_top"     );
  }

  /* ttbar MB and single-top */
  else if(m_sample=="Top_MB"){
    m_sampleName.push_back( "ttbar_ee_0M150"         );
    m_sampleName.push_back( "ttbar_ee_150M250"       );
    m_sampleName.push_back( "ttbar_ee_250M500"       );
    m_sampleName.push_back( "ttbar_ee_500M1000"      );
    m_sampleName.push_back( "ttbar_ee_1000M2000"     );
    m_sampleName.push_back( "ttbar_ee_2000M3000"     );
    m_sampleName.push_back( "ttbar_ee_3000M4000"     );
    m_sampleName.push_back( "ttbar_ee_4000M5000"     );
    m_sampleName.push_back( "ttbar_ee_5000M"         );
    m_sampleName.push_back( "ttbar_mumu_0M150"       );
    m_sampleName.push_back( "ttbar_mumu_150M250"     );
    m_sampleName.push_back( "ttbar_mumu_250M500"     );
    m_sampleName.push_back( "ttbar_mumu_500M1000"    );
    m_sampleName.push_back( "ttbar_mumu_1000M2000"   );
    m_sampleName.push_back( "ttbar_mumu_2000M3000"   );
    m_sampleName.push_back( "ttbar_mumu_3000M4000"   );
    m_sampleName.push_back( "ttbar_mumu_4000M5000"   );
    m_sampleName.push_back( "ttbar_mumu_5000M"       );
    m_sampleName.push_back( "ttbar_emu_0M150"        );
    m_sampleName.push_back( "ttbar_emu_150M500"      );
    m_sampleName.push_back( "ttbar_emu_500M1000"     );
    m_sampleName.push_back( "ttbar_emu_1000M2000"    );
    m_sampleName.push_back( "ttbar_emu_2000M3000"    );
    m_sampleName.push_back( "ttbar_emu_M3000"        );
    m_sampleName.push_back( "ttbar_etau_0M150"       );
    m_sampleName.push_back( "ttbar_etau_150M500"     );
    m_sampleName.push_back( "ttbar_etau_500M1000"    );
    m_sampleName.push_back( "ttbar_etau_1000M2000"   );
    m_sampleName.push_back( "ttbar_etau_2000M3000"   );
    m_sampleName.push_back( "ttbar_etau_M3000"       );
    m_sampleName.push_back( "ttbar_etau_M3000"       );
    m_sampleName.push_back( "ttbar_mutau_0M150"      );
    m_sampleName.push_back( "ttbar_mutau_150M500"    );
    m_sampleName.push_back( "ttbar_mutau_500M1000"   );
    m_sampleName.push_back( "ttbar_mutau_1000M2000"  );
    m_sampleName.push_back( "ttbar_mutau_2000M3000"  );
    m_sampleName.push_back( "ttbar_mutau_M3000"      );
    m_sampleName.push_back( "ttbar_tautau_0M150"     );
    m_sampleName.push_back( "ttbar_tautau_150M500"   );
    m_sampleName.push_back( "ttbar_tautau_500M1000"  );
    m_sampleName.push_back( "ttbar_tautau_1000M2000" );
    m_sampleName.push_back( "ttbar_tautau_2000M3000" );
    m_sampleName.push_back( "ttbar_tautau_M3000"     );
    m_sampleName.push_back( "Wt_antitop" );
    m_sampleName.push_back( "Wt_top"     );
  }
  
  /* ttbar */
  else if(m_sample=="ttbar"){
    m_sampleName.push_back( "ttbar_incl" );
  }
  else if(m_sample=="ttbar_ScaleDown"){
    m_sampleName.push_back( "ttbar_incl_SysDown" );
  }
  else if(m_sample=="ttbar_ScaleUp"){
    m_sampleName.push_back( "ttbar_incl_SysUp" );
  }

  /* ttbar MB */
  else if(m_sample=="ttbar_MB"){
    m_sampleName.push_back( "ttbar_ee_0M150"         );
    m_sampleName.push_back( "ttbar_ee_150M250"       );
    m_sampleName.push_back( "ttbar_ee_250M500"       );
    m_sampleName.push_back( "ttbar_ee_500M1000"      );
    m_sampleName.push_back( "ttbar_ee_1000M2000"     );
    m_sampleName.push_back( "ttbar_ee_2000M3000"     );
    m_sampleName.push_back( "ttbar_ee_3000M4000"     );
    m_sampleName.push_back( "ttbar_ee_4000M5000"     );
    m_sampleName.push_back( "ttbar_ee_5000M"         );
    m_sampleName.push_back( "ttbar_mumu_0M150"       );
    m_sampleName.push_back( "ttbar_mumu_150M250"     );
    m_sampleName.push_back( "ttbar_mumu_250M500"     );
    m_sampleName.push_back( "ttbar_mumu_500M1000"    );
    m_sampleName.push_back( "ttbar_mumu_1000M2000"   );
    m_sampleName.push_back( "ttbar_mumu_2000M3000"   );
    m_sampleName.push_back( "ttbar_mumu_3000M4000"   );
    m_sampleName.push_back( "ttbar_mumu_4000M5000"   );
    m_sampleName.push_back( "ttbar_mumu_5000M"       );
    m_sampleName.push_back( "ttbar_emu_0M150"        );
    m_sampleName.push_back( "ttbar_emu_150M500"      );
    m_sampleName.push_back( "ttbar_emu_500M1000"     );
    m_sampleName.push_back( "ttbar_emu_1000M2000"    );
    m_sampleName.push_back( "ttbar_emu_2000M3000"    );
    m_sampleName.push_back( "ttbar_emu_M3000"        );
    m_sampleName.push_back( "ttbar_etau_0M150"       );
    m_sampleName.push_back( "ttbar_etau_150M500"     );
    m_sampleName.push_back( "ttbar_etau_500M1000"    );
    m_sampleName.push_back( "ttbar_etau_1000M2000"   );
    m_sampleName.push_back( "ttbar_etau_2000M3000"   );
    m_sampleName.push_back( "ttbar_etau_M3000"       );
    m_sampleName.push_back( "ttbar_etau_M3000"       );
    m_sampleName.push_back( "ttbar_mutau_0M150"      );
    m_sampleName.push_back( "ttbar_mutau_150M500"    );
    m_sampleName.push_back( "ttbar_mutau_500M1000"   );
    m_sampleName.push_back( "ttbar_mutau_1000M2000"  );
    m_sampleName.push_back( "ttbar_mutau_2000M3000"  );
    m_sampleName.push_back( "ttbar_mutau_M3000"      );
    m_sampleName.push_back( "ttbar_tautau_0M150"     );
    m_sampleName.push_back( "ttbar_tautau_150M500"   );
    m_sampleName.push_back( "ttbar_tautau_500M1000"  );
    m_sampleName.push_back( "ttbar_tautau_1000M2000" );
    m_sampleName.push_back( "ttbar_tautau_2000M3000" );
    m_sampleName.push_back( "ttbar_tautau_M3000"     );
  }
  
  /* single top */
  else if(m_sample=="singleTop"){
    m_sampleName.push_back( "Wt_antitop" );
    m_sampleName.push_back( "Wt_top"     );
  }

  /* ttV */
  else if(m_sample=="ttV"){
    m_sampleName.push_back( "ttll"    );
    m_sampleName.push_back( "ttZnnqq" );
    m_sampleName.push_back( "ttW"     );
  }

  /* Wjets */
  else if(m_sample=="Wjets_Sherpa2.1"){
    m_sampleName.push_back( "Wmunu_Pt0_70_CVetoBVeto"          );
    m_sampleName.push_back( "Wmunu_Pt0_70_CFilterBVeto"        );
    m_sampleName.push_back( "Wmunu_Pt0_70_BFilter"             );
    m_sampleName.push_back( "Wmunu_Pt70_140_CVetoBVeto"        );
    m_sampleName.push_back( "Wmunu_Pt70_140_CFilterBVeto"      );
    m_sampleName.push_back( "Wmunu_Pt70_140_BFilter"           );
    m_sampleName.push_back( "Wmunu_Pt140_280_CVetoBVeto"       );
    m_sampleName.push_back( "Wmunu_Pt140_280_CFilterBVeto"     );
    m_sampleName.push_back( "Wmunu_Pt140_280_BFilter"          );
    m_sampleName.push_back( "Wmunu_Pt280_500_CVetoBVeto"       );
    m_sampleName.push_back( "Wmunu_Pt280_500_CFilterBVeto"     );
    m_sampleName.push_back( "Wmunu_Pt280_500_BFilter"          );
    m_sampleName.push_back( "Wmunu_Pt500_700_CVetoBVeto"       );
    m_sampleName.push_back( "Wmunu_Pt500_700_CFilterBVeto"     );
    m_sampleName.push_back( "Wmunu_Pt500_700_BFilter"          );
    m_sampleName.push_back( "Wmunu_Pt700_1000_CVetoBVeto"      );
    m_sampleName.push_back( "Wmunu_Pt700_1000_CFilterBVeto"    );
    m_sampleName.push_back( "Wmunu_Pt700_1000_BFilter"         );
    m_sampleName.push_back( "Wmunu_Pt1000_2000_CVetoBVeto"     );
    m_sampleName.push_back( "Wmunu_Pt1000_2000_CFilterBVeto"   );
    m_sampleName.push_back( "Wmunu_Pt1000_2000_BFilter"        );
    m_sampleName.push_back( "Wmunu_Pt2000_E_CMS_CVetoBVeto"    );
    m_sampleName.push_back( "Wmunu_Pt2000_E_CMS_CFilterBVeto"  );
    m_sampleName.push_back( "Wmunu_Pt2000_E_CMS_BFilter"       );
    m_sampleName.push_back( "Wenu_Pt0_70_CVetoBVeto"           );
    m_sampleName.push_back( "Wenu_Pt0_70_CFilterBVeto"         );
    m_sampleName.push_back( "Wenu_Pt0_70_BFilter"              );
    m_sampleName.push_back( "Wenu_Pt70_140_CVetoBVeto"         );
    m_sampleName.push_back( "Wenu_Pt70_140_CFilterBVeto"       );
    m_sampleName.push_back( "Wenu_Pt70_140_BFilter"            );
    m_sampleName.push_back( "Wenu_Pt140_280_CVetoBVeto"        );
    m_sampleName.push_back( "Wenu_Pt140_280_CFilterBVeto"      );
    m_sampleName.push_back( "Wenu_Pt140_280_BFilter"           );
    m_sampleName.push_back( "Wenu_Pt280_500_CVetoBVeto"        );
    m_sampleName.push_back( "Wenu_Pt280_500_CFilterBVeto"      );
    m_sampleName.push_back( "Wenu_Pt280_500_BFilter"           );
    m_sampleName.push_back( "Wenu_Pt500_700_CVetoBVeto"        );
    m_sampleName.push_back( "Wenu_Pt500_700_CFilterBVeto"      );
    m_sampleName.push_back( "Wenu_Pt500_700_BFilter"           );
    m_sampleName.push_back( "Wenu_Pt700_1000_CVetoBVeto"       );
    m_sampleName.push_back( "Wenu_Pt700_1000_CFilterBVeto"     );
    m_sampleName.push_back( "Wenu_Pt700_1000_BFilter"          );
    m_sampleName.push_back( "Wenu_Pt1000_2000_CVetoBVeto"      );
    m_sampleName.push_back( "Wenu_Pt1000_2000_CFilterBVeto"    );
    m_sampleName.push_back( "Wenu_Pt1000_2000_BFilter"         );
    m_sampleName.push_back( "Wenu_Pt2000_E_CMS_CVetoBVeto"     );
    m_sampleName.push_back( "Wenu_Pt2000_E_CMS_CFilterBVeto"   );
    m_sampleName.push_back( "Wenu_Pt2000_E_CMS_BFilter"        );
    m_sampleName.push_back( "Wtaunu_Pt0_70_CVetoBVeto"         );
    m_sampleName.push_back( "Wtaunu_Pt0_70_CFilterBVeto"       );
    m_sampleName.push_back( "Wtaunu_Pt0_70_BFilter"            );
    m_sampleName.push_back( "Wtaunu_Pt70_140_CVetoBVeto"       );
    m_sampleName.push_back( "Wtaunu_Pt70_140_CFilterBVeto"     );
    m_sampleName.push_back( "Wtaunu_Pt70_140_BFilter"          );
    m_sampleName.push_back( "Wtaunu_Pt140_280_CVetoBVeto"      );
    m_sampleName.push_back( "Wtaunu_Pt140_280_CFilterBVeto"    );
    m_sampleName.push_back( "Wtaunu_Pt140_280_BFilter"         );
    m_sampleName.push_back( "Wtaunu_Pt280_500_CVetoBVeto"      );
    m_sampleName.push_back( "Wtaunu_Pt280_500_CFilterBVeto"    );
    m_sampleName.push_back( "Wtaunu_Pt280_500_BFilter"         );
    m_sampleName.push_back( "Wtaunu_Pt500_700_CVetoBVeto"      );
    m_sampleName.push_back( "Wtaunu_Pt500_700_CFilterBVeto"    );
    m_sampleName.push_back( "Wtaunu_Pt500_700_BFilter"         );
    m_sampleName.push_back( "Wtaunu_Pt700_1000_CVetoBVeto"     );
    m_sampleName.push_back( "Wtaunu_Pt700_1000_CFilterBVeto"   );
    m_sampleName.push_back( "Wtaunu_Pt700_1000_BFilter"        );
    m_sampleName.push_back( "Wtaunu_Pt1000_2000_CVetoBVeto"    );
    m_sampleName.push_back( "Wtaunu_Pt1000_2000_CFilterBVeto"  );
    m_sampleName.push_back( "Wtaunu_Pt1000_2000_BFilter"       );
    m_sampleName.push_back( "Wtaunu_Pt2000_E_CMS_CVetoBVeto"   );
    m_sampleName.push_back( "Wtaunu_Pt2000_E_CMS_CFilterBVeto" );
    m_sampleName.push_back( "Wtaunu_Pt2000_E_CMS_BFilter"      );
  }

  /* W+jets */
  else if(m_sample=="Wjets"){
    m_sampleName.push_back( "Wmunu_MAXHTPTV0_70_CVetoBVeto"       );
    m_sampleName.push_back( "Wmunu_MAXHTPTV0_70_CFilterBVeto"     );
    m_sampleName.push_back( "Wmunu_MAXHTPTV0_70_BFilter"          );
    m_sampleName.push_back( "Wmunu_MAXHTPTV70_140_CVetoBVeto"     );
    m_sampleName.push_back( "Wmunu_MAXHTPTV70_140_CFilterBVeto"   );
    m_sampleName.push_back( "Wmunu_MAXHTPTV70_140_BFilter"        );
    m_sampleName.push_back( "Wmunu_MAXHTPTV140_280_CVetoBVeto"    );
    m_sampleName.push_back( "Wmunu_MAXHTPTV140_280_CFilterBVeto"  );
    m_sampleName.push_back( "Wmunu_MAXHTPTV140_280_BFilter"       );
    m_sampleName.push_back( "Wmunu_MAXHTPTV280_500_CVetoBVeto"    );
    m_sampleName.push_back( "Wmunu_MAXHTPTV280_500_CFilterBVeto"  );
    m_sampleName.push_back( "Wmunu_MAXHTPTV280_500_BFilter"       );
    m_sampleName.push_back( "Wmunu_MAXHTPTV500_1000"              );
    m_sampleName.push_back( "Wmunu_MAXHTPTV1000_E_CMS"            );
    m_sampleName.push_back( "Wenu_MAXHTPTV0_70_CVetoBVeto"        );
    m_sampleName.push_back( "Wenu_MAXHTPTV0_70_CFilterBVeto"      );
    m_sampleName.push_back( "Wenu_MAXHTPTV0_70_BFilter"           );
    m_sampleName.push_back( "Wenu_MAXHTPTV70_140_CVetoBVeto"      );
    m_sampleName.push_back( "Wenu_MAXHTPTV70_140_CFilterBVeto"    );
    m_sampleName.push_back( "Wenu_MAXHTPTV70_140_BFilter"         );
    m_sampleName.push_back( "Wenu_MAXHTPTV140_280_CVetoBVeto"     );
    m_sampleName.push_back( "Wenu_MAXHTPTV140_280_CFilterBVeto"   );
    m_sampleName.push_back( "Wenu_MAXHTPTV140_280_BFilter"        );
    m_sampleName.push_back( "Wenu_MAXHTPTV280_500_CVetoBVeto"     );
    m_sampleName.push_back( "Wenu_MAXHTPTV280_500_CFilterBVeto"   );
    m_sampleName.push_back( "Wenu_MAXHTPTV280_500_BFilter"        );
    m_sampleName.push_back( "Wenu_MAXHTPTV500_1000"               );
    m_sampleName.push_back( "Wenu_MAXHTPTV1000_E_CMS"             );
    m_sampleName.push_back( "Wtaunu_MAXHTPTV0_70_CVetoBVeto"      );
    m_sampleName.push_back( "Wtaunu_MAXHTPTV0_70_CFilterBVeto"    );
    m_sampleName.push_back( "Wtaunu_MAXHTPTV0_70_BFilter"         );
    m_sampleName.push_back( "Wtaunu_MAXHTPTV70_140_CVetoBVeto"    );
    m_sampleName.push_back( "Wtaunu_MAXHTPTV70_140_CFilterBVeto"  );
    m_sampleName.push_back( "Wtaunu_MAXHTPTV70_140_BFilter"       );
    m_sampleName.push_back( "Wtaunu_MAXHTPTV140_280_CVetoBVeto"   );
    m_sampleName.push_back( "Wtaunu_MAXHTPTV140_280_CFilterBVeto" );
    m_sampleName.push_back( "Wtaunu_MAXHTPTV140_280_BFilter"      );
    m_sampleName.push_back( "Wtaunu_MAXHTPTV280_500_CVetoBVeto"   );
    m_sampleName.push_back( "Wtaunu_MAXHTPTV280_500_CFilterBVeto" );
    m_sampleName.push_back( "Wtaunu_MAXHTPTV280_500_BFilter"      );
    m_sampleName.push_back( "Wtaunu_MAXHTPTV500_1000"             );
    m_sampleName.push_back( "Wtaunu_MAXHTPTV1000_E_CMS"           );
  }
  
}

void RunOnMiniTree :: DefineOutHistograms(){

  if(m_verbose)
    std::cout << "< RunOnMiniTree :: LoadOutHistograms() > :: " 
	      << "defining out histos ... " << std::endl;

  /* Histos Bins Setting */
  int mllBins = 60; //80;
  double xmin = 80;
  double xmax = 10000;
  double logxmin = TMath::Log10(xmin);
  double logxmax = TMath::Log10(xmax);
  double binwidth = (logxmax-logxmin)/double(mllBins);
  double mllX[mllBins];
  mllX[0] = xmin;
  for(int i=1;i<=mllBins;i++){
    mllX[i] = TMath::Power(10,logxmin+i*binwidth);
  }

  int ptBins = 15;
  Double_t ptX[] = {40,   100,  160,  220,  280,  380,  480,  580,  780,  980, 
		    1200, 1400, 2000, 3000, 4000, 5000};
  
  int ptllBins = 14;
  Double_t ptllX[] = {0, 50, 100, 150, 200, 250, 350, 460, 700, 1000, 1400,
		      2000, 3000, 4000, 5000};
  
  int EtallBins = 28;/*56*/ Double_t EtallWd = 10;
  int PhiBins   = 20; Double_t PhiWd   = TMath::Pi();
  int MetBins   = 25; Double_t MetMax  = 1000.;
  int NjetBins  = 20; Double_t NjetMax = 20;
  int EtaBins   = 16; Double_t EtaWd   = 2.5;
  int MtBins    = 50; Double_t MtMax   = 1000;

  std::vector<std::string> Nstr;
  Nstr.push_back("");
  //Nstr.push_back("PDF_");
  //Nstr.push_back("SCALE_");

  for(uint i=0; i<Nstr.size(); i++){

    /* mll */
    hmll = new TH1F( ("hmll_"+Nstr.at(i)+m_sample).c_str(),
		     ("hmll_"+Nstr.at(i)+m_sample).c_str(),
		     mllBins, mllX);
    hmll->GetXaxis()->SetTitle( ("m_{"+m_lfvName+"} [GeV]").c_str() );
    Vmll.push_back(hmll);

    hmllCorr = new TH1F( ("hmllCorr_"+Nstr.at(i)+m_sample).c_str(),
			 ("hmllCorr_"+Nstr.at(i)+m_sample).c_str(),
			 mllBins, mllX);
    hmllCorr->GetXaxis()->SetTitle( ("m_{"+m_lfvName+"} [GeV]").c_str() );
    VmllC.push_back(hmllCorr);

    /* ptll */
    hptll = new TH1F( ("hptll_"+Nstr.at(i)+m_sample).c_str(),
		      ("hptll_"+Nstr.at(i)+m_sample).c_str(),
		      ptllBins, ptllX);
    hptll->GetXaxis()->SetTitle( ("p_{T}^{"+m_lfvName+"} [GeV]").c_str() );
    Vptll.push_back(hptll);
  
    hptllCorr = new TH1F( ("hptllCorr_"+Nstr.at(i)+m_sample).c_str(),
			  ("hptllCorr_"+Nstr.at(i)+m_sample).c_str(),
			  ptllBins, ptllX);
    hptllCorr->GetXaxis()->SetTitle( ("p_{T}^{"+m_lfvName+"} [GeV]").c_str() );
    VptllC.push_back(hptllCorr);


    /* etall and phill */
    hetall = new TH1F( ("hetall_"+Nstr.at(i)+m_sample).c_str(),
		       ("hetall_"+Nstr.at(i)+m_sample).c_str(),
		       EtallBins, -EtallWd, EtallWd);
    hetall->GetXaxis()->SetTitle( ("#eta_{"+m_lfvName+"}").c_str() );
    Vetall.push_back(hetall);
  
    hphill = new TH1F( ("hphill_"+Nstr.at(i)+m_sample).c_str(),
		       ("hphill_"+Nstr.at(i)+m_sample).c_str(),
		       PhiBins, -PhiWd, PhiWd);
    hphill->GetXaxis()->SetTitle( ("#phi_{"+m_lfvName+"}").c_str() );
    Vphill.push_back(hphill);

    /* met and njet */
    hmet = new TH1F( ("hmet_"+Nstr.at(i)+m_sample).c_str(),
		     ("hmet_"+Nstr.at(i)+m_sample).c_str(),
		     MetBins, 0, MetMax);
    hmet->GetXaxis()->SetTitle( "E_{T}^{miss} [GeV]" );
    Vmet.push_back(hmet);

    hnjet   = new TH1F( ("hnjet_"+Nstr.at(i)+m_sample).c_str(),
		        ("hnjet_"+Nstr.at(i)+m_sample).c_str(),
			NjetBins, 0, NjetMax);
    hnjet->GetXaxis()->SetTitle("N_{jets}");
    Vnjet.push_back(hnjet);

    /* mT */
    hmt = new TH1F( ("hmt_"+Nstr.at(i)+m_sample).c_str(),
		    ("hmt_"+Nstr.at(i)+m_sample).c_str(),
		    MtBins, 0, MtMax);
    hmt->GetXaxis()->SetTitle("m_{T}");
    Vmt.push_back(hmt);

    /* Muon */
    hmu_pt = new TH1F( ("hmu_pt_"+Nstr.at(i)+m_sample).c_str(),
		       ("hmu_pt_"+Nstr.at(i)+m_sample).c_str(),
		       ptBins, ptX);
    hmu_pt->GetXaxis()->SetTitle("p_{T}^{#mu} [GeV]");
    Vmu_pt.push_back(hmu_pt);
    
    hmu_eta = new TH1F( ("hmu_eta_"+Nstr.at(i)+m_sample).c_str(),
			("hmu_eta_"+Nstr.at(i)+m_sample).c_str(),
			EtaBins, -EtaWd, EtaWd);
    hmu_eta->GetXaxis()->SetTitle("#eta_{#mu}");
    Vmu_eta.push_back(hmu_eta);
    
    hmu_phi = new TH1F( ("hmu_phi_"+Nstr.at(i)+m_sample).c_str(),
			("hmu_phi_"+Nstr.at(i)+m_sample).c_str(),
			PhiBins, -PhiWd, PhiWd);
    hmu_phi->GetXaxis()->SetTitle("#phi_{#mu}");
    Vmu_phi.push_back(hmu_phi);

    /* Electron */
    hel_pt = new TH1F( ("hel_pt_"+Nstr.at(i)+m_sample).c_str(),
		       ("hel_pt_"+Nstr.at(i)+m_sample).c_str(),
		       ptBins, ptX);
    hel_pt->GetXaxis()->SetTitle("p_{T}^{e} [GeV]");
    Vel_pt.push_back(hel_pt);
    
    hel_eta = new TH1F( ("hel_eta_"+Nstr.at(i)+m_sample).c_str(),
			("hel_eta_"+Nstr.at(i)+m_sample).c_str(),
			EtaBins, -EtaWd, EtaWd);
    hel_eta->GetXaxis()->SetTitle("#eta_{e}");
    Vel_eta.push_back(hel_eta);
    
    hel_phi = new TH1F( ("hel_phi_"+Nstr.at(i)+m_sample).c_str(),
			("hel_phi_"+Nstr.at(i)+m_sample).c_str(),
			PhiBins, -PhiWd, PhiWd);
    hel_phi->GetXaxis()->SetTitle("#phi_{e}");
    Vel_phi.push_back(hel_phi);

    /* Tau */
    hta_pt = new TH1F( ("hta_pt_"+Nstr.at(i)+m_sample).c_str(),
		       ("hta_pt_"+Nstr.at(i)+m_sample).c_str(),
		       ptBins, ptX);
    hta_pt->GetXaxis()->SetTitle("p_{T}^{#tau} [GeV]");
    Vta_pt.push_back(hta_pt);
    
    hta_eta = new TH1F( ("hta_eta_"+Nstr.at(i)+m_sample).c_str(),
			("hta_eta_"+Nstr.at(i)+m_sample).c_str(),
			EtaBins, -EtaWd, EtaWd);
    hta_eta->GetXaxis()->SetTitle("#eta_{#tau}");
    Vta_eta.push_back(hta_eta);
    
    hta_phi = new TH1F( ("hta_phi_"+Nstr.at(i)+m_sample).c_str(),
			("hta_phi_"+Nstr.at(i)+m_sample).c_str(),
			PhiBins, -PhiWd, PhiWd);
    hta_phi->GetXaxis()->SetTitle("#phi_{#tau}");
    Vta_phi.push_back(hta_phi);
    
  }

}

void RunOnMiniTree :: SetHistoErrors(std::string name, int itr){

  if(name=="data"){
    for(uint i=0; i<Vmll.size(); i++){
      Vmll.at(i)->SetBinErrorOption(TH1::kPoisson);
      VmllC.at(i)->SetBinErrorOption(TH1::kPoisson);
      Vptll.at(i)->SetBinErrorOption(TH1::kPoisson);
      VptllC.at(i)->SetBinErrorOption(TH1::kPoisson);
      Vphill.at(i)->SetBinErrorOption(TH1::kPoisson);
      Vetall.at(i)->SetBinErrorOption(TH1::kPoisson);
      Vmu_eta.at(i)->SetBinErrorOption(TH1::kPoisson);
      Vmu_phi.at(i)->SetBinErrorOption(TH1::kPoisson);
      Vmu_pt.at(i)->SetBinErrorOption(TH1::kPoisson);
      Vel_eta.at(i)->SetBinErrorOption(TH1::kPoisson);
      Vel_phi.at(i)->SetBinErrorOption(TH1::kPoisson);
      Vel_pt.at(i)->SetBinErrorOption(TH1::kPoisson);
      Vta_eta.at(i)->SetBinErrorOption(TH1::kPoisson);
      Vta_phi.at(i)->SetBinErrorOption(TH1::kPoisson);
      Vta_pt.at(i)->SetBinErrorOption(TH1::kPoisson);
      Vnjet.at(i)->SetBinErrorOption(TH1::kPoisson);
      Vmet.at(i)->SetBinErrorOption(TH1::kPoisson);
      Vmt.at(i)->SetBinErrorOption(TH1::kPoisson);
    }
  }
  else{
    if(itr==0){
      for(uint i=0; i<Vmll.size(); i++){
	Vmll.at(i)->Sumw2();
	VmllC.at(i)->Sumw2();
	Vptll.at(i)->Sumw2();
	VptllC.at(i)->Sumw2();
	Vphill.at(i)->Sumw2();
	Vetall.at(i)->Sumw2();
	Vmu_eta.at(i)->Sumw2();
	Vmu_phi.at(i)->Sumw2();
	Vmu_pt.at(i)->Sumw2();
	Vel_eta.at(i)->Sumw2();
	Vel_phi.at(i)->Sumw2();
	Vel_pt.at(i)->Sumw2();
	Vta_eta.at(i)->Sumw2();
	Vta_phi.at(i)->Sumw2();
	Vta_pt.at(i)->Sumw2();
	Vnjet.at(i)->Sumw2();
	Vmet.at(i)->Sumw2();
	Vmt.at(i)->Sumw2();
      }
    }
  }
  
}

double RunOnMiniTree :: FindTotalEventsSample(std::string name){

  double evt = 1;
  if( name!="data" ){
    TH1F *info =  (TH1F*)m_Input->Get("MCInfo");
    evt = info->GetBinContent(2);
  }
  return evt;
  
}

void RunOnMiniTree :: InitTreeVariables(){
  
  dilepMass                  = 0;
  dilepCorrMass              = 0;
  dilepPt                    = 0;
  dilepCorrPt                = 0;
  dilepEta                   = 0;
  dilepPhi                   = 0;
  weight                     = 0;
  mcweight                   = 0;
  weightWjetSF               = 0;
  puweight                   = 0;
  puweight_SysUp             = 0;
  puweight_SysDown           = 0;
  Lep_Id                     = 0;
  Lep_pt                     = 0;
  Lep_eta                    = 0;
  Lep_phi                    = 0;
  Lep_nProngs                = 0;
  Lep_TrigSF                 = 0;
  Lep_RecoSF                 = 0;
  Lep_IDSF                   = 0;
  Lep_IsoSF                  = 0;
  Lep_TrigSF_StatUp          = 0;
  Lep_TrigSF_StatDown        = 0;
  Lep_TrigSF_SysUp           = 0;
  Lep_TrigSF_SysDown         = 0;
  Lep_RecoSF_StatUp          = 0;
  Lep_RecoSF_StatDown        = 0;
  Lep_RecoSF_SysUp           = 0;
  Lep_RecoSF_SysDown         = 0;
  Lep_RecoSF_Hpt_SysUp       = 0;
  Lep_RecoSF_Hpt_SysDown     = 0;
  Lep_IDSF_StatUp            = 0;
  Lep_IDSF_StatDown          = 0;
  Lep_IDSF_SysUp             = 0;
  Lep_IDSF_SysDown           = 0;
  Lep_IDSF_Hpt_SysUp         = 0;
  Lep_IDSF_Hpt_SysDown       = 0;
  Lep_IsoSF_StatUp           = 0;
  Lep_IsoSF_StatDown         = 0;
  Lep_IsoSF_SysUp            = 0;
  Lep_IsoSF_SysDown          = 0;
  Lep_TtvaSF                 = 0;
  Lep_TtvaSF_StatUp          = 0;
  Lep_TtvaSF_StatDown        = 0;
  Lep_TtvaSF_SysUp           = 0;
  Lep_TtvaSF_SysDown         = 0;
  Lep_L1CaloSF               = 0;
  Lep_ElOlrSF                = 0;
  Lep_ElOlrSF_SysUp          = 0;
  Lep_ElOlrSF_SysDown        = 0;
  Jet_pt                     = 0;
  Jet_eta                    = 0;
  Jet_phi                    = 0;
  Jet_JvtSF                  = 0;
  Jet_JvtSF_SysUp            = 0;
  Jet_JvtSF_SysDown          = 0;
  Jet_BtagSF                 = 0;
  Jet_BtagSF_Beff_SysUp      = 0;
  Jet_BtagSF_Beff_SysDown    = 0;
  Jet_BtagSF_Ceff_SysUp      = 0;
  Jet_BtagSF_Ceff_SysDown    = 0;
  Jet_BtagSF_Leff_SysUp      = 0;
  Jet_BtagSF_Leff_SysDown    = 0;
  Jet_BtagSF_ExtCeff_SysUp   = 0;
  Jet_BtagSF_ExtCeff_SysDown = 0;
  Jet_BtagSF_ExtEff_SysUp    = 0;
  Jet_BtagSF_ExtEff_SysDown  = 0;
  
}

void RunOnMiniTree :: SetTreeAndBranches(){
  
  m_InTree = (TTree*)m_Input->Get( m_treeName.c_str() );
  m_InTree->SetBranchStatus("*",1);

  InitTreeVariables();
    
  m_InTree->SetBranchAddress("event", &event, &b_event);
  m_InTree->SetBranchAddress("run", &run, &b_run);
  m_InTree->SetBranchAddress("mcweight", &mcweight, &b_mcweight);
  m_InTree->SetBranchAddress("weightWjetSF", &weightWjetSF, &b_weightWjetSF);
  m_InTree->SetBranchAddress("puweight", &puweight, &b_puweight);
  m_InTree->SetBranchAddress("puweight_SysUp", &puweight_SysUp, &b_puweight_SysUp);
  m_InTree->SetBranchAddress("puweight_SysDown", &puweight_SysDown, &b_puweight_SysDown);
  m_InTree->SetBranchAddress("weight", &weight, &b_weight);
  m_InTree->SetBranchAddress("xsec", &xsec, &b_xsec);
  m_InTree->SetBranchAddress("kfact", &kfact, &b_kfact);
  m_InTree->SetBranchAddress("met_px", &met_px, &b_met_px);
  m_InTree->SetBranchAddress("met_py", &met_py, &b_met_py);
  m_InTree->SetBranchAddress("met_phi", &met_phi, &b_met_phi);
  m_InTree->SetBranchAddress("met_et", &met_et, &b_met_et);
  m_InTree->SetBranchAddress("met_sumet", &met_sumet, &b_met_sumet);
  m_InTree->SetBranchAddress("channel", &channel, &b_channel);
  m_InTree->SetBranchAddress("dilepMass", &dilepMass, &b_dilepMass);
  m_InTree->SetBranchAddress("dilepCorrMass", &dilepCorrMass, &b_dilepCorrMass);
  m_InTree->SetBranchAddress("dilepPt", &dilepPt, &b_dilepPt);
  m_InTree->SetBranchAddress("dilepCorrPt", &dilepCorrPt, &b_dilepCorrPt);
  m_InTree->SetBranchAddress("dilepEta", &dilepEta, &b_dilepEta);
  m_InTree->SetBranchAddress("dilepPhi", &dilepPhi, &b_dilepPhi);
  m_InTree->SetBranchAddress("isTauContr", &isTauContr, &b_isTauContr);
  m_InTree->SetBranchAddress("isKeepEvent", &isKeepEvent, &b_isKeepEvent);
  m_InTree->SetBranchAddress("isBTBGood", &isBTBGood, &b_isBTBGood);
  m_InTree->SetBranchAddress("isOSGood", &isOSGood, &b_isOSGood);
  m_InTree->SetBranchAddress("isBjetEvt", &isBjetEvt, &b_isBjetEvt);
  m_InTree->SetBranchAddress("Lep_Id", &Lep_Id, &b_Lep_Id);
  m_InTree->SetBranchAddress("Lep_pt", &Lep_pt, &b_Lep_pt);
  m_InTree->SetBranchAddress("Lep_eta", &Lep_eta, &b_Lep_eta);
  m_InTree->SetBranchAddress("Lep_phi", &Lep_phi, &b_Lep_phi);
  m_InTree->SetBranchAddress("Lep_nProngs"  , &Lep_nProngs  , &b_Lep_nProngs);
  m_InTree->SetBranchAddress("Lep_TrigSF"   , &Lep_TrigSF   , &b_Lep_TrigSF);
  m_InTree->SetBranchAddress("Lep_RecoSF"   , &Lep_RecoSF   , &b_Lep_RecoSF);
  m_InTree->SetBranchAddress("Lep_IDSF"     , &Lep_IDSF     , &b_Lep_IDSF);
  m_InTree->SetBranchAddress("Lep_IsoSF"    , &Lep_IsoSF    , &b_Lep_IsoSF);
  m_InTree->SetBranchAddress("Lep_TtvaSF"   , &Lep_TtvaSF   , &b_Lep_TtvaSF);
  m_InTree->SetBranchAddress("Lep_L1CaloSF" , &Lep_L1CaloSF , &b_Lep_L1CaloSF);
  m_InTree->SetBranchAddress("Lep_ElOlrSF"  , &Lep_ElOlrSF  , &b_Lep_ElOlrSF);
  m_InTree->SetBranchAddress("Lep_TrigSF_StatUp"          , &Lep_TrigSF_StatUp          , &b_Lep_TrigSF_StatUp);
  m_InTree->SetBranchAddress("Lep_TrigSF_StatDown"        , &Lep_TrigSF_StatDown        , &b_Lep_TrigSF_StatDown);
  m_InTree->SetBranchAddress("Lep_TrigSF_SysUp"           , &Lep_TrigSF_SysUp           , &b_Lep_TrigSF_SysUp);
  m_InTree->SetBranchAddress("Lep_TrigSF_SysDown"         , &Lep_TrigSF_SysDown         , &b_Lep_TrigSF_SysDown);
  m_InTree->SetBranchAddress("Lep_RecoSF_StatUp"          , &Lep_RecoSF_StatUp          , &b_Lep_RecoSF_StatUp);
  m_InTree->SetBranchAddress("Lep_RecoSF_StatDown"        , &Lep_RecoSF_StatDown        , &b_Lep_RecoSF_StatDown);
  m_InTree->SetBranchAddress("Lep_RecoSF_SysUp"           , &Lep_RecoSF_SysUp           , &b_Lep_RecoSF_SysUp);
  m_InTree->SetBranchAddress("Lep_RecoSF_SysDown"         , &Lep_RecoSF_SysDown         , &b_Lep_RecoSF_SysDown);
  m_InTree->SetBranchAddress("Lep_RecoSF_Hpt_SysUp"       , &Lep_RecoSF_Hpt_SysUp       , &b_Lep_RecoSF_Hpt_SysUp);
  m_InTree->SetBranchAddress("Lep_RecoSF_Hpt_SysDown"     , &Lep_RecoSF_Hpt_SysDown     , &b_Lep_RecoSF_Hpt_SysDown);
  m_InTree->SetBranchAddress("Lep_IDSF_StatUp"            , &Lep_IDSF_StatUp            , &b_Lep_IDSF_StatUp);
  m_InTree->SetBranchAddress("Lep_IDSF_StatDown"          , &Lep_IDSF_StatDown          , &b_Lep_IDSF_StatDown);
  m_InTree->SetBranchAddress("Lep_IDSF_SysUp"             , &Lep_IDSF_SysUp             , &b_Lep_IDSF_SysUp);
  m_InTree->SetBranchAddress("Lep_IDSF_SysDown"           , &Lep_IDSF_SysDown           , &b_Lep_IDSF_SysDown);
  m_InTree->SetBranchAddress("Lep_IDSF_Hpt_SysUp"         , &Lep_IDSF_Hpt_SysUp         , &b_Lep_IDSF_Hpt_SysUp);
  m_InTree->SetBranchAddress("Lep_IDSF_Hpt_SysDown"       , &Lep_IDSF_Hpt_SysDown       , &b_Lep_IDSF_Hpt_SysDown);
  m_InTree->SetBranchAddress("Lep_IsoSF_StatUp"           , &Lep_IsoSF_StatUp           , &b_Lep_IsoSF_StatUp);
  m_InTree->SetBranchAddress("Lep_IsoSF_StatDown"         , &Lep_IsoSF_StatDown         , &b_Lep_IsoSF_StatDown);
  m_InTree->SetBranchAddress("Lep_IsoSF_SysUp"            , &Lep_IsoSF_SysUp            , &b_Lep_IsoSF_SysUp);
  m_InTree->SetBranchAddress("Lep_IsoSF_SysDown"          , &Lep_IsoSF_SysDown          , &b_Lep_IsoSF_SysDown);
  m_InTree->SetBranchAddress("Lep_TtvaSF_StatUp"          , &Lep_TtvaSF_StatUp          , &b_Lep_TtvaSF_StatUp);
  m_InTree->SetBranchAddress("Lep_TtvaSF_StatDown"        , &Lep_TtvaSF_StatDown        , &b_Lep_TtvaSF_StatDown);
  m_InTree->SetBranchAddress("Lep_TtvaSF_SysUp"           , &Lep_TtvaSF_SysUp           , &b_Lep_TtvaSF_SysUp);
  m_InTree->SetBranchAddress("Lep_TtvaSF_SysDown"         , &Lep_TtvaSF_SysDown         , &b_Lep_TtvaSF_SysDown);
  m_InTree->SetBranchAddress("Lep_ElOlrSF_SysUp"          , &Lep_ElOlrSF_SysUp          , &b_Lep_ElOlrSF_SysUp);
  m_InTree->SetBranchAddress("Lep_ElOlrSF_SysDown"        , &Lep_ElOlrSF_SysDown        , &b_Lep_ElOlrSF_SysDown);
  m_InTree->SetBranchAddress("Jet_pt"                     , &Jet_pt                     , &b_Jet_pt);
  m_InTree->SetBranchAddress("Jet_eta"                    , &Jet_eta                    , &b_Jet_eta);
  m_InTree->SetBranchAddress("Jet_phi"                    , &Jet_phi                    , &b_Jet_phi);
  m_InTree->SetBranchAddress("Jet_JvtSF"                  , &Jet_JvtSF                  , &b_Jet_JvtSF);
  m_InTree->SetBranchAddress("Jet_JvtSF_SysUp"            , &Jet_JvtSF_SysUp            , &b_Jet_JvtSF_SysUp);
  m_InTree->SetBranchAddress("Jet_JvtSF_SysDown"          , &Jet_JvtSF_SysDown          , &b_Jet_JvtSF_SysDown);
  m_InTree->SetBranchAddress("Jet_BtagSF"                 , &Jet_BtagSF                 , &b_Jet_BtagSF);
  m_InTree->SetBranchAddress("Jet_BtagSF_Beff_SysUp"      , &Jet_BtagSF_Beff_SysUp      , &b_Jet_BtagSF_Beff_SysUp);
  m_InTree->SetBranchAddress("Jet_BtagSF_Beff_SysDown"    , &Jet_BtagSF_Beff_SysDown    , &b_Jet_BtagSF_Beff_SysDown);
  m_InTree->SetBranchAddress("Jet_BtagSF_Ceff_SysUp"      , &Jet_BtagSF_Ceff_SysUp      , &b_Jet_BtagSF_Ceff_SysUp);
  m_InTree->SetBranchAddress("Jet_BtagSF_Ceff_SysDown"    , &Jet_BtagSF_Ceff_SysDown    , &b_Jet_BtagSF_Ceff_SysDown);
  m_InTree->SetBranchAddress("Jet_BtagSF_Leff_SysUp"      , &Jet_BtagSF_Leff_SysUp      , &b_Jet_BtagSF_Leff_SysUp);
  m_InTree->SetBranchAddress("Jet_BtagSF_Leff_SysDown"    , &Jet_BtagSF_Leff_SysDown    , &b_Jet_BtagSF_Leff_SysDown);
  m_InTree->SetBranchAddress("Jet_BtagSF_ExtCeff_SysUp"   , &Jet_BtagSF_ExtCeff_SysUp   , &b_Jet_BtagSF_ExtCeff_SysUp);
  m_InTree->SetBranchAddress("Jet_BtagSF_ExtCeff_SysDown" , &Jet_BtagSF_ExtCeff_SysDown , &b_Jet_BtagSF_ExtCeff_SysDown);
  m_InTree->SetBranchAddress("Jet_BtagSF_ExtEff_SysUp"    , &Jet_BtagSF_ExtEff_SysUp    , &b_Jet_BtagSF_ExtEff_SysUp);
  m_InTree->SetBranchAddress("Jet_BtagSF_ExtEff_SysDown"  , &Jet_BtagSF_ExtEff_SysDown  , &b_Jet_BtagSF_ExtEff_SysDown);

}

double RunOnMiniTree :: GetEventWeight(){

  double tmp_weight = mcweight;
  if(m_usePuRw){
    if(m_sysVar=="PU_SysUp")
      tmp_weight *= puweight_SysUp;
    else if(m_sysVar=="PU_SysDown")
      tmp_weight *= puweight_SysDown;
    else
      tmp_weight *= puweight;
  }

  /* retrieve jets weights */
  double jetwgt = 1;
  for(uint j=0; j<Jet_pt->size(); j++){
    if(m_sysVar=="JtJvtSF_SysUp")
      jetwgt *= Jet_JvtSF_SysUp->at(j);
    else if(m_sysVar=="JtJvtSF_SysDown")
      jetwgt *= Jet_JvtSF_SysDown->at(j);
    else
      jetwgt *= Jet_JvtSF->at(j);
  }
  
  /* add btag weights to jet weigths */
  if(m_useBjet){
    for(uint j=0; j<Jet_pt->size(); j++){
      if(m_sysVar=="BtagSF_Beff_SysUp")
	jetwgt *= Jet_BtagSF_Beff_SysUp->at(j);
      else if(m_sysVar=="BtagSF_Beff_SysDown")
	jetwgt *= Jet_BtagSF_Beff_SysDown->at(j);
      else if(m_sysVar=="BtagSF_Ceff_SysUp")
	jetwgt *= Jet_BtagSF_Ceff_SysUp->at(j);
      else if(m_sysVar=="BtagSF_Ceff_SysDown")
	jetwgt *= Jet_BtagSF_Ceff_SysDown->at(j);
      else if(m_sysVar=="BtagSF_Leff_SysUp")
	jetwgt *= Jet_BtagSF_Leff_SysUp->at(j);
      else if(m_sysVar=="BtagSF_Leff_SysDown")
	jetwgt *= Jet_BtagSF_Leff_SysDown->at(j);
      else if(m_sysVar=="BtagSF_ExtCeff_SysUp")
	jetwgt *= Jet_BtagSF_ExtCeff_SysUp->at(j);
      else if(m_sysVar=="BtagSF_ExtCeff_SysDown")
	jetwgt *= Jet_BtagSF_ExtCeff_SysDown->at(j);
      else if(m_sysVar=="BtagSF_ExtEff_SysUp")
	jetwgt *= Jet_BtagSF_ExtEff_SysUp->at(j);
      else if(m_sysVar=="BtagSF_ExtEff_SysDown")
	jetwgt *= Jet_BtagSF_ExtEff_SysDown->at(j);
      else
	jetwgt *= Jet_BtagSF->at(j);
    }
  }

  /* dealing muon weights systematics */
  if(m_sysVar=="MuReco_StatUp"){
    tmp_weight *= Lep_TrigSF->at(0)*Lep_IDSF->at(0)*Lep_IsoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_TrigSF->at(1)*Lep_IDSF->at(1)*Lep_IsoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
    if(abs(Lep_Id->at(0))==13)
      tmp_weight *= Lep_RecoSF_StatUp->at(0)*Lep_RecoSF->at(1);
    else
      tmp_weight *= Lep_RecoSF_StatUp->at(1)*Lep_RecoSF->at(0);
  }
  else if(m_sysVar=="MuReco_StatDown"){
    tmp_weight *= Lep_TrigSF->at(0)*Lep_IDSF->at(0)*Lep_IsoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_TrigSF->at(1)*Lep_IDSF->at(1)*Lep_IsoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
    if(abs(Lep_Id->at(0))==13)
      tmp_weight *= Lep_RecoSF_StatDown->at(0)*Lep_RecoSF->at(1);
    else
      tmp_weight *= Lep_RecoSF_StatDown->at(1)*Lep_RecoSF->at(0);
  }
  else if(m_sysVar=="MuReco_SysUp"){
    tmp_weight *= Lep_TrigSF->at(0)*Lep_IDSF->at(0)*Lep_IsoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_TrigSF->at(1)*Lep_IDSF->at(1)*Lep_IsoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
    if(abs(Lep_Id->at(0))==13)
      tmp_weight *= Lep_RecoSF_SysUp->at(0)*Lep_RecoSF->at(1);
    else
      tmp_weight *= Lep_RecoSF_SysUp->at(1)*Lep_RecoSF->at(0);
  }
  else if(m_sysVar=="MuReco_SysDown"){
    tmp_weight *= Lep_TrigSF->at(0)*Lep_IDSF->at(0)*Lep_IsoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_TrigSF->at(1)*Lep_IDSF->at(1)*Lep_IsoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
    if(abs(Lep_Id->at(0))==13)
      tmp_weight *= Lep_RecoSF_SysDown->at(0)*Lep_RecoSF->at(1);
    else
      tmp_weight *= Lep_RecoSF_SysDown->at(1)*Lep_RecoSF->at(0);
  }
  else if(m_sysVar=="MuIso_StatUp"){
    tmp_weight *= Lep_TrigSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_TrigSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
    if(abs(Lep_Id->at(0))==13)
      tmp_weight *= Lep_IsoSF_StatUp->at(0)*Lep_IsoSF->at(1);
    else
      tmp_weight *= Lep_IsoSF_StatUp->at(1)*Lep_IsoSF->at(0);
  }
  else if(m_sysVar=="MuIso_StatDown"){
    tmp_weight *= Lep_TrigSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_TrigSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
    if(abs(Lep_Id->at(0))==13)
      tmp_weight *= Lep_IsoSF_StatDown->at(0)*Lep_IsoSF->at(1);
    else
      tmp_weight *= Lep_IsoSF_StatDown->at(1)*Lep_IsoSF->at(0);
  }
  else if(m_sysVar=="MuIso_SysUp"){
    tmp_weight *= Lep_TrigSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_TrigSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
    if(abs(Lep_Id->at(0))==13)
      tmp_weight *= Lep_IsoSF_SysUp->at(0)*Lep_IsoSF->at(1);
    else
      tmp_weight *= Lep_IsoSF_SysUp->at(1)*Lep_IsoSF->at(0);
  }
  else if(m_sysVar=="MuIso_SysDown"){
    tmp_weight *= Lep_TrigSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_TrigSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
    if(abs(Lep_Id->at(0))==13)
      tmp_weight *= Lep_IsoSF_SysDown->at(0)*Lep_IsoSF->at(1);
    else
      tmp_weight *= Lep_IsoSF_SysDown->at(1)*Lep_IsoSF->at(0);
  }
  else if(m_sysVar=="MuTrg_StatUp"){
    tmp_weight *= Lep_IsoSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_IsoSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
    if(abs(Lep_Id->at(0))==13)
      tmp_weight *= Lep_TrigSF_StatUp->at(0)*Lep_TrigSF->at(1);
    else
      tmp_weight *= Lep_TrigSF_StatUp->at(1)*Lep_TrigSF->at(0);
  }
  else if(m_sysVar=="MuTrg_StatDown"){
    tmp_weight *= Lep_IsoSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_IsoSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
    if(abs(Lep_Id->at(0))==13)
      tmp_weight *= Lep_TrigSF_StatDown->at(0)*Lep_TrigSF->at(1);
    else
      tmp_weight *= Lep_TrigSF_StatDown->at(1)*Lep_TrigSF->at(0);
  }
  else if(m_sysVar=="MuTrg_SysUp"){
    tmp_weight *= Lep_IsoSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_IsoSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
    if(abs(Lep_Id->at(0))==13)
      tmp_weight *= Lep_TrigSF_SysUp->at(0)*Lep_TrigSF->at(1);
    else
      tmp_weight *= Lep_TrigSF_SysUp->at(1)*Lep_TrigSF->at(0);
  }
  else if(m_sysVar=="MuTrg_SysDown"){
    tmp_weight *= Lep_IsoSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_IsoSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
    if(abs(Lep_Id->at(0))==13)
      tmp_weight *= Lep_TrigSF_SysDown->at(0)*Lep_TrigSF->at(1);
    else
      tmp_weight *= Lep_TrigSF_SysDown->at(1)*Lep_TrigSF->at(0);
  }
  else if(m_sysVar=="MuTTVA_StatUp"){
    tmp_weight *= Lep_IsoSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_L1CaloSF->at(1)*Lep_TrigSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_IsoSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TrigSF->at(1)*Lep_ElOlrSF->at(1);
    if(abs(Lep_Id->at(0))==13)
      tmp_weight *= Lep_TtvaSF_StatUp->at(0)*Lep_TtvaSF->at(1);
    else
      tmp_weight *= Lep_TtvaSF_StatUp->at(1)*Lep_TtvaSF->at(0);
  }
  else if(m_sysVar=="MuTTVA_StatDown"){
    tmp_weight *= Lep_IsoSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_L1CaloSF->at(1)*Lep_TrigSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_IsoSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TrigSF->at(1)*Lep_ElOlrSF->at(1);
    if(abs(Lep_Id->at(0))==13)
      tmp_weight *= Lep_TtvaSF_StatDown->at(0)*Lep_TtvaSF->at(1);
    else
      tmp_weight *= Lep_TtvaSF_StatDown->at(1)*Lep_TtvaSF->at(0);
  }
  else if(m_sysVar=="MuTTVA_SysUp"){
    tmp_weight *= Lep_IsoSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_L1CaloSF->at(1)*Lep_TrigSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_IsoSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TrigSF->at(1)*Lep_ElOlrSF->at(1);
    if(abs(Lep_Id->at(0))==13)
      tmp_weight *= Lep_TtvaSF_SysUp->at(0)*Lep_TtvaSF->at(1);
    else
      tmp_weight *= Lep_TtvaSF_SysUp->at(1)*Lep_TtvaSF->at(0);
  }
  else if(m_sysVar=="MuTTVA_SysDown"){
    tmp_weight *= Lep_IsoSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_L1CaloSF->at(1)*Lep_TrigSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_IsoSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TrigSF->at(1)*Lep_ElOlrSF->at(1);
    if(abs(Lep_Id->at(0))==13)
      tmp_weight *= Lep_TtvaSF_SysDown->at(0)*Lep_TtvaSF->at(1);
    else
      tmp_weight *= Lep_TtvaSF_SysDown->at(1)*Lep_TtvaSF->at(0);
  }

  /* dealing electron weights systematics */
  else if(m_sysVar=="ElReco_SysUp"){
    tmp_weight *= Lep_TrigSF->at(0)*Lep_IDSF->at(0)*Lep_IsoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_TrigSF->at(1)*Lep_IDSF->at(1)*Lep_IsoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
    if(abs(Lep_Id->at(0))==11)
      tmp_weight *= Lep_RecoSF_SysUp->at(0)*Lep_RecoSF->at(1);
    else
      tmp_weight *= Lep_RecoSF_SysUp->at(1)*Lep_RecoSF->at(0);
  }
  else if(m_sysVar=="ElReco_SysDown"){
    tmp_weight *= Lep_TrigSF->at(0)*Lep_IDSF->at(0)*Lep_IsoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_TrigSF->at(1)*Lep_IDSF->at(1)*Lep_IsoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
    if(abs(Lep_Id->at(0))==11)
      tmp_weight *= Lep_RecoSF_SysDown->at(0)*Lep_RecoSF->at(1);
    else
      tmp_weight *= Lep_RecoSF_SysDown->at(1)*Lep_RecoSF->at(0);
  }
  else if(m_sysVar=="ElID_SysUp"){
    tmp_weight *= Lep_TrigSF->at(0)*Lep_RecoSF->at(0)*Lep_IsoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_TrigSF->at(1)*Lep_RecoSF->at(1)*Lep_IsoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
    if(abs(Lep_Id->at(0))==11)
      tmp_weight *= Lep_IDSF_SysUp->at(0)*Lep_IDSF->at(1);
    else
      tmp_weight *= Lep_IDSF_SysUp->at(1)*Lep_IDSF->at(0);
  }
  else if(m_sysVar=="ElID_SysDown"){
    tmp_weight *= Lep_TrigSF->at(0)*Lep_RecoSF->at(0)*Lep_IsoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_TrigSF->at(1)*Lep_RecoSF->at(1)*Lep_IsoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
    if(abs(Lep_Id->at(0))==11)
      tmp_weight *= Lep_IDSF_SysDown->at(0)*Lep_IDSF->at(1);
    else
      tmp_weight *= Lep_IDSF_SysDown->at(1)*Lep_IDSF->at(0);
  }
  else if(m_sysVar=="ElIso_SysUp"){
    tmp_weight *= Lep_TrigSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_TrigSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
    if(abs(Lep_Id->at(0))==11)
      tmp_weight *= Lep_IsoSF_SysUp->at(0)*Lep_IsoSF->at(1);
    else
      tmp_weight *= Lep_IsoSF_SysUp->at(1)*Lep_IsoSF->at(0);
  }
  else if(m_sysVar=="ElIso_SysDown"){
    tmp_weight *= Lep_TrigSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_TrigSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
    if(abs(Lep_Id->at(0))==11)
      tmp_weight *= Lep_IsoSF_SysDown->at(0)*Lep_IsoSF->at(1);
    else
      tmp_weight *= Lep_IsoSF_SysDown->at(1)*Lep_IsoSF->at(0);
  }
  else if(m_sysVar=="ElTrg_SysUp"){
    tmp_weight *= Lep_IsoSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_IsoSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
    if(abs(Lep_Id->at(0))==11)
      tmp_weight *= Lep_TrigSF_SysUp->at(0)*Lep_TrigSF->at(1);
    else
      tmp_weight *= Lep_TrigSF_SysUp->at(1)*Lep_TrigSF->at(0);
  }
  else if(m_sysVar=="ElTrg_SysDown"){
    tmp_weight *= Lep_IsoSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_IsoSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
    if(abs(Lep_Id->at(0))==11)
      tmp_weight *= Lep_TrigSF_SysDown->at(0)*Lep_TrigSF->at(1);
    else
      tmp_weight *= Lep_TrigSF_SysDown->at(1)*Lep_TrigSF->at(0);
  }
  
  /* dealing tau weights systematics */
  else if(m_sysVar=="TaReco_SysUp"){
    tmp_weight *= Lep_IsoSF->at(0)*Lep_IDSF->at(0)*Lep_TrigSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_IsoSF->at(1)*Lep_IDSF->at(1)*Lep_TrigSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
    if(abs(Lep_Id->at(0))==15)
      tmp_weight *= Lep_RecoSF_SysUp->at(0)*Lep_RecoSF->at(1);
    else
      tmp_weight *= Lep_RecoSF_SysUp->at(1)*Lep_RecoSF->at(0);
  }
  else if(m_sysVar=="TaReco_SysDown"){
    tmp_weight *= Lep_IsoSF->at(0)*Lep_IDSF->at(0)*Lep_TrigSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_IsoSF->at(1)*Lep_IDSF->at(1)*Lep_TrigSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
    if(abs(Lep_Id->at(0))==15)
      tmp_weight *= Lep_RecoSF_SysDown->at(0)*Lep_RecoSF->at(1);
    else
      tmp_weight *= Lep_RecoSF_SysDown->at(1)*Lep_RecoSF->at(0);
  }
  else if(m_sysVar=="TaRecoHpt_SysUp"){
    tmp_weight *= Lep_IsoSF->at(0)*Lep_IDSF->at(0)*Lep_TrigSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_IsoSF->at(1)*Lep_IDSF->at(1)*Lep_TrigSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
    if(abs(Lep_Id->at(0))==15)
      tmp_weight *= Lep_RecoSF_Hpt_SysUp->at(0)*Lep_RecoSF->at(1);
    else
      tmp_weight *= Lep_RecoSF_Hpt_SysUp->at(1)*Lep_RecoSF->at(0);
  }
  else if(m_sysVar=="TaRecoHpt_SysDown"){
    tmp_weight *= Lep_IsoSF->at(0)*Lep_IDSF->at(0)*Lep_TrigSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_IsoSF->at(1)*Lep_IDSF->at(1)*Lep_TrigSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
    if(abs(Lep_Id->at(0))==15)
      tmp_weight *= Lep_RecoSF_Hpt_SysDown->at(0)*Lep_RecoSF->at(1);
    else
      tmp_weight *= Lep_RecoSF_Hpt_SysDown->at(1)*Lep_RecoSF->at(0);
  }
  else if(m_sysVar=="TaJetID_SysUp"){
    tmp_weight *= Lep_IsoSF->at(0)*Lep_RecoSF->at(0)*Lep_TrigSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_IsoSF->at(1)*Lep_RecoSF->at(1)*Lep_TrigSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
    if(abs(Lep_Id->at(0))==15)
      tmp_weight *= Lep_IDSF_SysUp->at(0)*Lep_IDSF->at(1);
    else
      tmp_weight *= Lep_IDSF_SysUp->at(1)*Lep_IDSF->at(0);
  }
  else if(m_sysVar=="TaJetID_SysDown"){
    tmp_weight *= Lep_IsoSF->at(0)*Lep_RecoSF->at(0)*Lep_TrigSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_IsoSF->at(1)*Lep_RecoSF->at(1)*Lep_TrigSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
    if(abs(Lep_Id->at(0))==15)
      tmp_weight *= Lep_IDSF_SysDown->at(0)*Lep_IDSF->at(1);
    else
      tmp_weight *= Lep_IDSF_SysDown->at(1)*Lep_IDSF->at(0);
  }
  else if(m_sysVar=="TaJetIDHpt_SysUp"){
    tmp_weight *= Lep_IsoSF->at(0)*Lep_RecoSF->at(0)*Lep_TrigSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_IsoSF->at(1)*Lep_RecoSF->at(1)*Lep_TrigSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
    if(abs(Lep_Id->at(0))==15)
      tmp_weight *= Lep_IDSF_Hpt_SysUp->at(0)*Lep_IDSF->at(1);
    else
      tmp_weight *= Lep_IDSF_Hpt_SysUp->at(1)*Lep_IDSF->at(0);
  }
  else if(m_sysVar=="TaJetIDHpt_SysDown"){
    tmp_weight *= Lep_IsoSF->at(0)*Lep_RecoSF->at(0)*Lep_TrigSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_IsoSF->at(1)*Lep_RecoSF->at(1)*Lep_TrigSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
    if(abs(Lep_Id->at(0))==15)
      tmp_weight *= Lep_IDSF_Hpt_SysDown->at(0)*Lep_IDSF->at(1);
    else
      tmp_weight *= Lep_IDSF_Hpt_SysDown->at(1)*Lep_IDSF->at(0);
  }
  else if(m_sysVar=="TaEleOlr_SysUp"){
    tmp_weight *= Lep_IsoSF->at(0)*Lep_RecoSF->at(0)*Lep_TrigSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_IDSF->at(0);
    tmp_weight *= Lep_IsoSF->at(1)*Lep_RecoSF->at(1)*Lep_TrigSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_IDSF->at(1);
    if(abs(Lep_Id->at(0))==15)
      tmp_weight *= Lep_ElOlrSF_SysUp->at(0)*Lep_ElOlrSF->at(1);
    else
      tmp_weight *= Lep_ElOlrSF_SysUp->at(1)*Lep_ElOlrSF->at(0);
  }
  else if(m_sysVar=="TaEleOlr_SysDown"){
    tmp_weight *= Lep_IsoSF->at(0)*Lep_RecoSF->at(0)*Lep_TrigSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_IDSF->at(0);
    tmp_weight *= Lep_IsoSF->at(1)*Lep_RecoSF->at(1)*Lep_TrigSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_IDSF->at(1);
    if(abs(Lep_Id->at(0))==15)
      tmp_weight *= Lep_ElOlrSF_SysDown->at(0)*Lep_ElOlrSF->at(1);
    else
      tmp_weight *= Lep_ElOlrSF_SysDown->at(1)*Lep_ElOlrSF->at(0);
  }

  /* dealing btag weights systematics */
  else{ 
    tmp_weight *= Lep_IsoSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_TrigSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
    tmp_weight *= Lep_IsoSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_TrigSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
  }

  /* adding jet weights to leptons weights */
  tmp_weight *= jetwgt;

  if(m_verbose)
    std::cout << "< RunOnMiniTree :: GetEventWeight() > :: tmp_weight = "
	      << tmp_weight << std::endl;

  return tmp_weight;
  
}

double RunOnMiniTree :: GetTauFakeRateWeight(){

  double tmp_tfWgt = 1;
  int taupos = -1;
  int binX   = 0;
  int binY   = 0;

  if( abs(Lep_Id->at(0))==m_TauId ){      taupos = 0; }
  else if( abs(Lep_Id->at(1))==m_TauId ){ taupos = 1; }

  if(m_tauFr_pT){
    
    if(Lep_nProngs->at(taupos)==1){
      if(Lep_pt->at(taupos)>MaxPt_1p){ binX = MaxBin_1p; }
      else{ binX = m_FR1p_pT->FindBin(Lep_pt->at(taupos)); }
      tmp_tfWgt = m_FR1p_pT->GetBinContent(binX);
    }
    else if(Lep_nProngs->at(taupos)==3){
      if(Lep_pt->at(taupos)>MaxPt_3p){ binX = MaxBin_3p; }
      else{ binX = m_FR3p_pT->FindBin(Lep_pt->at(taupos)); }
      tmp_tfWgt = m_FR3p_pT->GetBinContent(binX);
    }
    
  }
  else if(m_tauFr_eta){
    
    if(Lep_nProngs->at(taupos)==1){
      binX = m_FR1p_Eta->FindBin(Lep_eta->at(taupos));
      tmp_tfWgt = m_FR1p_Eta->GetBinContent(binX);
    }
    else if(Lep_nProngs->at(taupos)==3){
      binX = m_FR3p_Eta->FindBin(Lep_eta->at(taupos));
      tmp_tfWgt = m_FR3p_Eta->GetBinContent(binX);
    }
    
  }
  else{

    if(Lep_nProngs->at(taupos)==1){
      if(Lep_pt->at(taupos)>MaxPt_1p){ binX = MaxBin_1p; }
      else{ binX = m_FR1p_pTeta->GetXaxis()->FindBin(Lep_pt->at(taupos)); }
      binY = m_FR1p_pTeta->GetYaxis()->FindBin(abs(Lep_eta->at(taupos)));
      tmp_tfWgt = m_FR1p_pTeta->GetBinContent(binX,binY);
    }
    else if(Lep_nProngs->at(taupos)==3){
      if(Lep_pt->at(taupos)>MaxPt_3p){ binX = MaxBin_3p; }
      else{ binX = m_FR3p_pTeta->GetXaxis()->FindBin(Lep_pt->at(taupos)); }
      binY = m_FR3p_pTeta->GetYaxis()->FindBin(abs(Lep_eta->at(taupos)));
      tmp_tfWgt = m_FR3p_pTeta->GetBinContent(binX,binY);
    }
    
  }
  if(m_verbose)
    std::cout << "< RunOnMiniTree :: GetTauFakeRateWeight() > :: "
	      << "tmp_tfWgt = " <<  tmp_tfWgt << std::endl;
  return tmp_tfWgt;
  
}

double RunOnMiniTree :: GetPDFWeight(double mass, std::string name){

  double tmp_pdfWgt = 1;
  if(m_sysVar.find("PDF_Sys")!=std::string::npos && name!="data"){
    Int_t bin = m_pdfTop->FindBin( mass );
    tmp_pdfWgt = m_pdfTop->GetBinContent(bin)*m_pdfDb->GetBinContent(bin);
  }
  if(m_verbose)
    std::cout << "< RunOnMiniTree :: GetPDFWeight() > :: m_{ll} = "
	      << mass << " tmp_pdfWgt = " << tmp_pdfWgt << std::endl;
  return tmp_pdfWgt;
  
}

double RunOnMiniTree :: GetTopScaleWeight(double mass, std::string name){

  double tmp_sclWgt = 1;
  if(m_runType!="TopExtra" && name=="ttbar_incl"){
    Int_t bin = -1;
    if(m_sysVar=="TopScale_SysUp"){
      bin        = m_scaleUp->FindBin( mass );
      tmp_sclWgt = m_scaleUp->GetBinContent( bin );
    }
    else if(m_sysVar=="TopScale_SysDown"){
      bin        = m_scaleDw->FindBin( mass );
      tmp_sclWgt = m_scaleDw->GetBinContent( bin );
    }
  }
  if(m_verbose)
    std::cout << "< RunOnMiniTree :: GetTopScaleWeight() > :: m_{ll} = "
	      << mass << " tmp_sclWgt = " << tmp_sclWgt << std::endl;
  return tmp_sclWgt;
  
}

double RunOnMiniTree :: GetPtReWgtWeight(double dlep_pt, std::string name){

  double tmp_ptWgt = 1;

  if( m_doPtRw &&
      (name.find("ttbar")!=std::string::npos ||
       name=="Wt_antitop" || name=="Wt_top")    ){

    if( dlep_pt<50.                        ){ tmp_ptWgt = m_pTwgt.at(0); }
    else if( dlep_pt>50.  && dlep_pt<100.  ){ tmp_ptWgt = m_pTwgt.at(1); }
    else if( dlep_pt>100. && dlep_pt<150.  ){ tmp_ptWgt = m_pTwgt.at(2); }
    else if( dlep_pt>150. && dlep_pt<200.  ){ tmp_ptWgt = m_pTwgt.at(3); }
    else if( dlep_pt>200. && dlep_pt<250.  ){ tmp_ptWgt = m_pTwgt.at(4); }
    else if( dlep_pt>250. && dlep_pt<350.  ){ tmp_ptWgt = m_pTwgt.at(5); }
    else if( dlep_pt>350. && dlep_pt<460.  ){ tmp_ptWgt = m_pTwgt.at(6); }
    else if( dlep_pt>460. && dlep_pt<700.  ){ tmp_ptWgt = m_pTwgt.at(7); }
    else if( dlep_pt>700. && dlep_pt<1000. ){ tmp_ptWgt = m_pTwgt.at(8); }
    
  }
  if(m_verbose)
    std::cout << "< RunOnMiniTree :: GetPtReWgtWeight() > :: pT_{ll} = "
	      << dlep_pt << " tmp_ptWgt = " << tmp_ptWgt << std::endl;
  return tmp_ptWgt;

}

void RunOnMiniTree :: FillPtWeightsVec(){

  if(m_lfvType==1){
    //if(m_useBjet){
    //  m_pTwgt.push_back( 0.927778  ); //0.931393  );
    //  m_pTwgt.push_back( 1.05965   ); //1.06455   );
    //  m_pTwgt.push_back( 1.08201   );
    //  m_pTwgt.push_back( 0.535384  ); //0.566616  );
    //  m_pTwgt.push_back( 0.900277  ); // 1.03215  );
    //  m_pTwgt.push_back( 0.356621  ); //0.179379  );
    //  m_pTwgt.push_back( 0.0669627 ); //-0.187325 );
    //  m_pTwgt.push_back( 0.0669627 );
    //  m_pTwgt.push_back( 1.0       );
    //}
    //else{            //blind      //unblind
    m_pTwgt.push_back( 1.0      ); //0.979533 );
    m_pTwgt.push_back( 1.0      ); //0.985082 );
    m_pTwgt.push_back( 0.944094 ); //1.0      ); //1.00363  );
    m_pTwgt.push_back( 0.740838 ); //0.806859 ); //0.819327 );
    m_pTwgt.push_back( 0.75194  ); //1.02671  ); //1.02398  );
    m_pTwgt.push_back( 0.744103 ); //0.617289 ); //0.55366  );
    m_pTwgt.push_back( 0.404776 ); //0.089598 ); //0.235479 );
    m_pTwgt.push_back( 0.420361 ); //0.150901 ); //0.329042 );
    m_pTwgt.push_back( 0.743724 ); //1.0      );
    //}
  }
  else if(m_lfvType==2){
    m_pTwgt.push_back( 1.18278  ); //1.91789  ); //1.87563    );
    m_pTwgt.push_back( 1.12924  ); //0.77795  ); //0.753395   );
    m_pTwgt.push_back( 1.19036  ); //0.810529 ); //0.744588   );
    m_pTwgt.push_back( 1.11843  ); //0.854134 ); //0.772619   );
    m_pTwgt.push_back( 0.8753   ); //0.884524 ); //0.764686   );
    m_pTwgt.push_back( 0.94777  ); //0.728667 ); //0.708572   );
    m_pTwgt.push_back( 0.767252 ); //0.029763 ); //0.020845   ); //-0.0550845 );
    m_pTwgt.push_back( 0.568276 ); //0.894775 );
    m_pTwgt.push_back( 0.037463 ); //1.0      ); //-3.43816   );
  }
  else if(m_lfvType==3){
    m_pTwgt.push_back( 0.952524 ); //1.52674  ); //1.54691  );
    m_pTwgt.push_back( 1.08276  ); //0.90369  ); //0.903021 );
    m_pTwgt.push_back( 0.976941 ); //0.881323 ); //0.865082 );
    m_pTwgt.push_back( 0.925398 ); //0.978025 ); //0.960516 );
    m_pTwgt.push_back( 0.997452 ); //0.992958 ); //0.969973 );
    m_pTwgt.push_back( 0.709794  ); //0.941696 ); //0.827638 );
    m_pTwgt.push_back( 0.662462 ); //1.54788  ); //1.27569  );
    m_pTwgt.push_back( 0.403563 ); //0.257008 );
    m_pTwgt.push_back( 0.308858 ); //1.0      );
  }

}

void RunOnMiniTree :: LoopOnEvents(std::string name){

  Int_t Nentries = (Int_t)m_InTree->GetEntries();
  for(Int_t en=0; en<Nentries; en++){
    m_InTree->GetEntry(en);

    if( m_runEvent!=0 )
      if( event!=m_runEvent ) continue;

    /* check overlap removal */
    if(m_sample!="Zgamma")
      if(isKeepEvent==0) continue;

    /* select only one channel */
    if(channel!=m_lfvType) continue;

    /* apply/reverse DeltaPhi cut */
    if(!m_ttbarCR){ 
      if(m_dphiRev){ if(isBTBGood==1) continue; }
      else{ if(isBTBGood==0) continue; }
    }

    /* apply b-jet veto */
    if(m_useBjet){
      if(isBjetEvt) continue;
    }
    
    /* enable ttbar CR selection */
    if(m_ttbarCR){ 
      if(!isBjetEvt) continue; 
      if(isBTBGood==1) continue;
    }
    
    /* apply qcd CR cuts*/
    if(m_qcdCR){
	if( Lep_pt->at(0)>200. || Lep_pt->at(1)>200. ) continue;
    }

    /* apply SS cut */
    if(m_ssPair){ if(isOSGood) continue; }
    
    /* apply OS cut */
    if(m_osPair){ if(!isOSGood) continue; }

    /* apply w+jets CR cuts*/
    if(m_wjetCR){
      if( met_et<30. ||
	  (Lep_pt->at(0)>150. || Lep_pt->at(1)>150.) ) continue;
    }
    
    /* apply met cut */
    if(m_metCut){ if( met_et<30. ) continue; }

    /* apply pt lep cut */
    if(m_pTlep){
      if(Lep_pt->at(0)>150. || Lep_pt->at(1)>150.) continue;
    }
    
    /* blind data only for mll'>600 GeV */
    if(m_blindData && m_runType=="Main" && name=="data"){
      if(dilepCorrMass>598.0/*600.*/) continue;
    }

    /* blind for mll'>600 GeV */
    if(m_blind){
      if(dilepCorrMass>598.0/*600.*/) continue;
    }

    /* reject high mass events from Zee/Zmumu */
    if(m_sample!="Zgamma"){
      if(name=="Zee" || name=="Zmumu")
	if(dilepCorrMass>600) continue;
    }
    
    /* checking for duplicates */
    const std::pair<Int_t,ULong64_t> RunEvt = std::make_pair(run,event);
    if( m_EvtProcessed.insert(RunEvt).second == false ){
      std::cout << "Found Duplicate in sample " << name
		<< "   -> Skipping! (Run = "      << run << " Event = "
		<< event << ")"  << std::endl;
      continue;
    }

    if(name=="data" && m_evtList){
      WriteEventOnFile();
    }
    
    /* setting event weight */
    double EvtWgt = 1;
    if(name!="data"){
      EvtWgt = GetEventWeight()*m_lumi*( (xsec*kfact)/m_Nevents);
    }
    
    /* retrieving tau fakerate weight */
    double TfrWgt = 1;
    if( m_tauFr && m_lfvType>1 &&
	(name.find("Wmunu") !=std::string::npos ||
	 name.find("Wenu")  !=std::string::npos ||
	 name.find("Wtaunu")!=std::string::npos  ) ){
      TfrWgt = GetTauFakeRateWeight();
    }

    /* retrieving pdf weight */
    double PdfWgt = 1;
    PdfWgt = GetPDFWeight(dilepCorrMass,name);
    
    /* retrieving scale weight */
    double ScaleWgt = 1;
    //ScaleWgt = GetTopScaleWeight(dilepCorrMass,name); //removed because using MC

    /* retrieving pT re-weighting weight */
    double rwPtWgt = GetPtReWgtWeight(dilepCorrPt,name);
    
    if(m_verbose)
      std::cout << "< RunOnMiniTree :: LoopOnEvents() > :: "
		<< " EvtWgt = " << EvtWgt << " TfrWgt = " << TfrWgt
		<< " PdfWgt = " << PdfWgt << " ScaleWgt = " << ScaleWgt
		<< " PtWgt = " << rwPtWgt << std::endl;

    /* Fill histos */
    Vmll.at(0)  ->Fill( dilepMass          , EvtWgt*TfrWgt*PdfWgt*ScaleWgt*rwPtWgt );
    VmllC.at(0) ->Fill( dilepCorrMass      , EvtWgt*TfrWgt*PdfWgt*ScaleWgt*rwPtWgt );
    Vptll.at(0) ->Fill( dilepPt            , EvtWgt*TfrWgt*PdfWgt*ScaleWgt*rwPtWgt );
    VptllC.at(0)->Fill( dilepCorrPt        , EvtWgt*TfrWgt*PdfWgt*ScaleWgt*rwPtWgt );
    Vphill.at(0)->Fill( dilepPhi           , EvtWgt*TfrWgt*PdfWgt*ScaleWgt*rwPtWgt );
    Vetall.at(0)->Fill( dilepEta           , EvtWgt*TfrWgt*PdfWgt*ScaleWgt*rwPtWgt );
    Vmet.at(0)  ->Fill( met_et             , EvtWgt*TfrWgt*PdfWgt*ScaleWgt*rwPtWgt );
    Vnjet.at(0) ->Fill( Jet_pt->size()     , EvtWgt*TfrWgt*PdfWgt*ScaleWgt*rwPtWgt );
    Vmt.at(0)   ->Fill( GetTransverseMass(), EvtWgt*TfrWgt*PdfWgt*ScaleWgt*rwPtWgt );
    for(uint i=0; i<Lep_Id->size(); i++){
      if( abs(Lep_Id->at(i))==m_MuId ){
	Vmu_eta.at(0)->Fill( Lep_eta->at(i), EvtWgt*TfrWgt*PdfWgt*ScaleWgt*rwPtWgt );
	Vmu_phi.at(0)->Fill( Lep_phi->at(i), EvtWgt*TfrWgt*PdfWgt*ScaleWgt*rwPtWgt );
	Vmu_pt.at(0) ->Fill( Lep_pt->at(i) , EvtWgt*TfrWgt*PdfWgt*ScaleWgt*rwPtWgt );
      }
      if( abs(Lep_Id->at(i))==m_ElId ){
	Vel_eta.at(0)->Fill( Lep_eta->at(i), EvtWgt*TfrWgt*PdfWgt*ScaleWgt*rwPtWgt );
	Vel_phi.at(0)->Fill( Lep_phi->at(i), EvtWgt*TfrWgt*PdfWgt*ScaleWgt*rwPtWgt );
	Vel_pt.at(0) ->Fill( Lep_pt->at(i) , EvtWgt*TfrWgt*PdfWgt*ScaleWgt*rwPtWgt );
      }
      if( abs(Lep_Id->at(i))==m_TauId ){
	Vta_eta.at(0)->Fill( Lep_eta->at(i), EvtWgt*TfrWgt*PdfWgt*ScaleWgt*rwPtWgt );
	Vta_phi.at(0)->Fill( Lep_phi->at(i), EvtWgt*TfrWgt*PdfWgt*ScaleWgt*rwPtWgt );
	Vta_pt.at(0) ->Fill( Lep_pt->at(i) , EvtWgt*TfrWgt*PdfWgt*ScaleWgt*rwPtWgt );
      }
    }
    
  }
  
}

void RunOnMiniTree :: SetAtlasStyle(){
  
  TStyle *atlasStyle= new TStyle("ATLAS","Atlas style");
  
  /*use plain black on white colors*/
  Int_t icol=0; // WHITE
  atlasStyle->SetFrameBorderMode(icol);
  atlasStyle->SetFrameFillColor(icol);
  atlasStyle->SetCanvasBorderMode(icol);
  atlasStyle->SetCanvasColor(icol);
  atlasStyle->SetPadBorderMode(icol);
  atlasStyle->SetPadColor(icol);
  atlasStyle->SetStatColor(icol);
  /*don't use: white fill color for *all* objects*/
  //atlasStyle->SetFillColor(icol); 

  /*set the paper & margin sizes*/
  atlasStyle->SetPaperSize(20,26);

  /*set margin sizes*/
  atlasStyle->SetPadTopMargin(0.05);
  atlasStyle->SetPadRightMargin(0.05);
  atlasStyle->SetPadBottomMargin(0.16);
  atlasStyle->SetPadLeftMargin(0.14);

  /*set title offsets (for axis label)*/
  atlasStyle->SetTitleXOffset(1.4);
  atlasStyle->SetTitleYOffset(1.4);

  /*use large fonts*/
  //Int_t font=72; // Helvetica italics
  Int_t font=42; // Helvetica
  Double_t tsize=0.04; //io=0.04
  atlasStyle->SetTextFont(font);

  atlasStyle->SetTextSize(tsize);
  atlasStyle->SetLabelFont(font,"x");
  atlasStyle->SetTitleFont(font,"x");
  atlasStyle->SetLabelFont(font,"y");
  atlasStyle->SetTitleFont(font,"y");
  atlasStyle->SetLabelFont(font,"z");
  atlasStyle->SetTitleFont(font,"z");

  atlasStyle->SetLabelSize(tsize,"x");
  atlasStyle->SetTitleSize(tsize,"x");
  atlasStyle->SetLabelSize(tsize,"y");
  atlasStyle->SetTitleSize(tsize,"y");
  atlasStyle->SetLabelSize(tsize,"z");
  atlasStyle->SetTitleSize(tsize,"z");

  /*use bold lines and markers*/
  atlasStyle->SetMarkerStyle(20);
  atlasStyle->SetMarkerSize(1.2);
  atlasStyle->SetHistLineWidth(2.);
  atlasStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

  /*get rid of X error bars*/
  //atlasStyle->SetErrorX(0.001);
  /*get rid of error bar caps*/
  atlasStyle->SetEndErrorSize(0.);

  /*do not display any of the standard histogram decorations*/
  atlasStyle->SetOptTitle(0);
  //atlasStyle->SetOptStat(1111);
  atlasStyle->SetOptStat(0);
  //atlasStyle->SetOptFit(1111);
  atlasStyle->SetOptFit(0);

  /*put tick marks on top and RHS of plots*/
  atlasStyle->SetPadTickX(1);
  atlasStyle->SetPadTickY(1);

  gROOT->SetStyle("ATLAS");
  gROOT->ForceStyle();
  
}

void RunOnMiniTree :: StoreHistograms(){
    
  m_Output->cd();
  for(uint i=0; i<Vmll.size(); i++){
    if( (m_runType!="Main" /*&& m_sample!="Top"*/) ||
	(m_runType=="Main" && m_sample!="Top")  ||
	m_blind || m_doPtRw)
      VmllC.at(i)->Write();
    if(m_runType!="TopExtra"){
      Vmll.at(i)->Write();
      Vptll.at(i)->Write();
      VptllC.at(i)->Write();
      Vphill.at(i)->Write();
      Vetall.at(i)->Write();
      Vmu_eta.at(i)->Write();
      Vmu_phi.at(i)->Write();
      Vmu_pt.at(i)->Write();
      Vel_eta.at(i)->Write();
      Vel_phi.at(i)->Write();
      Vel_pt.at(i)->Write();
      Vta_eta.at(i)->Write();
      Vta_phi.at(i)->Write();
      Vta_pt.at(i)->Write();
      Vnjet.at(i)->Write();
      Vmet.at(i)->Write();
      Vmt.at(i)->Write();
    }
  }
  
}    

void RunOnMiniTree :: CleanMemory(){

  m_Output->Close();
  
  if(m_evtList)
    m_outStream.close();
      
  /* clean histos vectors */
  Vmll.clear();
  VmllC.clear();
  Vptll.clear();
  VptllC.clear();
  Vphill.clear();
  Vetall.clear();
  Vmu_eta.clear();
  Vmu_phi.clear();
  Vmu_pt.clear();
  Vel_eta.clear();
  Vel_phi.clear();
  Vel_pt.clear();
  Vta_eta.clear();
  Vta_phi.clear();
  Vta_pt.clear();
  Vnjet.clear();
  Vmet.clear();
  Vmt.clear();
  /* clean histos */
  hmll->Delete();
  hmllCorr->Delete();
  hptll->Delete();
  hptllCorr->Delete();
  hphill->Delete();
  hetall->Delete();
  hnjet->Delete();
  hmet->Delete();
  hmt->Delete();
  hmu_eta->Delete();
  hmu_phi->Delete();
  hmu_pt->Delete();
  hel_eta->Delete();
  hel_phi->Delete();
  hel_pt->Delete();
  hta_eta->Delete();
  hta_phi->Delete();
  hta_pt->Delete();

  /* clean scale and pdf*/
  m_pdfDb->Delete();
  m_pdfTop->Delete();
  m_scaleUp->Delete();
  m_scaleDw->Delete();
  m_pdfIn->Close();
  m_scaleIn->Close();
  
  /* clean fake rate */
  m_FR1p_pT->Delete();
  m_FR3p_pT->Delete();
  if(m_sysVar.find("Comp_Sys")==std::string::npos){
    m_FR1p_Eta->Delete();
    m_FR3p_Eta->Delete();
    m_FR1p_pTeta->Delete();
    m_FR3p_pTeta->Delete();
  }
  m_tauFrIn->Close();

  /* clean pT rw weights */
  m_pTwgt.clear();
  
}

void RunOnMiniTree :: OpenEventListFile(){

  std::cout << "opening list file " << std::endl;
  m_outStream.open( ("DataList_"+m_lfvSt+".dat").c_str() );
  
}

void RunOnMiniTree :: WriteEventOnFile(){

  m_outStream << "runNumber = " << run << " , eventNumber = " << event << std::endl;
  
}

double RunOnMiniTree :: GetTransverseMass(){

  double m_mT     = -999;
  double m_lepPt  = -999;
  double m_lepPhi = -999;
  if(channel==2){
    if(abs(Lep_Id->at(0))==m_ElId){
      m_lepPt = Lep_pt->at(0); m_lepPhi = Lep_phi->at(0);
    }
    else{
      m_lepPt = Lep_pt->at(1); m_lepPhi = Lep_phi->at(1);
    }
  }
  else if(channel==3){
    if(abs(Lep_Id->at(0))==m_MuId){
      m_lepPt = Lep_pt->at(0); m_lepPhi = Lep_phi->at(0);
    }
    else{
      m_lepPt = Lep_pt->at(1); m_lepPhi = Lep_phi->at(1);
    }
  }

  m_mT = sqrt( 2*m_lepPt*met_et*
	       ( 1.0 - cos( ComputeDeltaPhi(m_lepPhi,met_phi) ) ) );

  if( m_verbose )
    std::cout << "< RunOnMiniTree :: GetTransverseMass() > :: mT = "
	      << m_mT << std::endl;
	       
  //mT =  sqrt( 2*Electron.Pt()*MET_Et*( 1.0 - cos( DeltaPhi(
  //Electron.Phi(), MET_Phi ) ) ) );

  return m_mT;
  
}

double RunOnMiniTree :: ComputeDeltaPhi(double phi1, double phi2){
  
  double m_Dphi = phi1-phi2;
  if( fabs(m_Dphi)>m_pi ) {
    if( m_Dphi>0 ){
      m_Dphi = 2*m_pi-m_Dphi;
    }
    else{
      m_Dphi = 2*m_pi+m_Dphi;
    }
  }
  
  if( m_verbose )
    std::cout << "< RunOnMiniTree :: ComputeDeltaPhi() > :: Dphi = "
	      << m_Dphi << std::endl;

  return m_Dphi;
  
}
