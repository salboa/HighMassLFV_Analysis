/* program includes */
#include "MergeContributions.h"
#include "SysHandler.C"
#include "ATLASstyle.C"

int main( int argc, char* argv[] ) {

  bool useBjet   = false;
  bool addSys    = false;
  bool isttCR    = false;
  bool isBlind   = false;
  bool isRevDphi = false;
  bool usePtRw   = false;
  bool isSherpa  = false;
  bool useSmooth = false;
  bool debug     = false;
  bool printHelp = false;
  int lfvType = -1;
  for(int i = 1; i < argc; ++i){
    if( !strcmp(argv[i],"--useBjet")        ){ useBjet   = true; }
    else if( !strcmp(argv[i],"--addSys")    ){ addSys    = true; }
    else if( !strcmp(argv[i],"--isttCR")    ){ isttCR    = true; }
    else if( !strcmp(argv[i],"--isBlind")   ){ isBlind   = true; }
    else if( !strcmp(argv[i],"--isRevDphi") ){ isRevDphi = true; }
    else if( !strcmp(argv[i],"--usePtRw")   ){ usePtRw   = true; }
    else if( !strcmp(argv[i],"--isSherpa")  ){ isSherpa  = true; }
    else if( !strcmp(argv[i],"--useSmooth") ){ useSmooth = true; }
    else if( !strcmp(argv[i],"--lfvType")   ){ lfvType   = std::stoi(argv[i+1]); }
    else if( !strcmp(argv[i],"--debug")     ){ debug     = true; }
    else if( !strcmp(argv[i],"--help")      ){ printHelp = true; }
    else{
      if(std::string(argv[i]).find("--")!=std::string::npos)
	std::cout << "WARNING:: Option " << argv[i] << " not recognized: "
		  << "skipping!" << std::endl;
    }
  }
  if(printHelp){
    std::cout << " MergeContributions: make Qcd+Wjets and total!"  << std::endl;
    std::cout << "                 Options: "                      << std::endl;
    std::cout << "                  --useBjet   [Enable b-jet veto:"
	      << " default is 'false' "                            << std::endl;
    std::cout << "                  --addSys    [Add Systematics:"
	      << " default is 'false'] "                           << std::endl;
    std::cout << "                  --isttCR    [Enable ttbar CR:"
	      << " default is 'false'] "                           << std::endl;
    std::cout << "                  --isBlind   [Enable Blind analysis:"
	      << " default is 'false'] "                           << std::endl;
    std::cout << "                  --isRevDphi [Enable revDphi analysis:"
	      
	      << " default is 'false'] "                           << std::endl;
    std::cout << "                  --usePtRw   [Enable pT_ll reweighting:"
	      << " default is 'false'] "                           << std::endl;
    std::cout << "                  --isSherpa  [Enable Sherpa ttbar:"
	      << " default is 'false'] "                           << std::endl;
    std::cout << "                  --useSmooth [Enable qcd mll smoothing:"
	      << " default is 'false']"                            << std::endl;
    std::cout << "                  --lfvType   [Choose lfv channel: "
	      << " options are '1,2,3'] "                          << std::endl;
    std::cout << "                  --debug     [Enable debug]"    << std::endl;
    std::cout << "                  --help      [Print this help]" << std::endl;
    exit(0);
  }

  if(lfvType==-1){
    std::cout << "< MergeContributions() >:: lfvType not set!"
	      << " Possible options: 1,2,3" << std::endl;
    exit(0);
  }
  
  std::cout << " < MergeContributions() >:: Options set "         << std::endl;
  std::cout << "                       useBjet   = " << useBjet   << std::endl;
  std::cout << "                       addSys    = " << addSys    << std::endl;
  std::cout << "                       isttCR    = " << isttCR    << std::endl;
  std::cout << "                       isBlind   = " << isBlind   << std::endl;
  std::cout << "                       isRevDphi = " << isRevDphi << std::endl;
  std::cout << "                       usePtRw   = " << usePtRw   << std::endl;
  std::cout << "                       isSherpa  = " << isSherpa  << std::endl;
  std::cout << "                       useSmooth = " << useSmooth << std::endl;
  std::cout << "                       lfvType   = " << lfvType   << std::endl;
  std::cout << "                       debug     = " << debug     << std::endl;

  m_debug = debug;
  MergeContributions(lfvType,addSys,isttCR,useBjet,isBlind,
		     isRevDphi,usePtRw,isSherpa,useSmooth);
  
  return 0;
  
}

void MergeContributions(int LFVtype, bool addSys, bool isttCR, bool useBjet,
			bool isBlind, bool isRevDphi, bool usePtRw,
			bool isSherpa, bool useSmooth){

  SetATLASStyle();
  TH1::SetDefaultSumw2(kTRUE);

  std::string lfvType = "";
  if(LFVtype==1)      { lfvType="emu";   }
  else if(LFVtype==2) { lfvType="etau";  }
  else if(LFVtype==3) { lfvType="mutau"; }

  std::cout << "< MergeContributions() > :: Merging contributions for Channel "
	    << lfvType << std::endl;
  
  std::string Dir = "";
  if(useBjet){ Dir += "Bjet/";   }
  else{        Dir += "NoBjet/"; }

  bool noPtRw = false;
  if(isttCR)    {
    Dir += "ttbarCR";
    if(isSherpa) Dir += "_Sherpa";
    Dir += "/";
    noPtRw = true;
  }
  if(isRevDphi){
    Dir += "revDphi/";
    noPtRw = true;
  }
  
  std::vector<std::string> sysVar = GetSysList(LFVtype,useBjet,addSys,
					       false,false,false,false,
					       noPtRw);
    TFile *InFile = NULL;

  TH1F *Hdy_mllCorr = NULL , *Hdy_ptllCorr = NULL , *Hdy_etall = NULL ;
  TH1F *Hdy_phill   = NULL , *Hdy_njet     = NULL , *Hdy_met   = NULL ;
  TH1F *Hdy_muEta   = NULL , *Hdy_muPhi    = NULL , *Hdy_muPt  = NULL ;
  TH1F *Hdy_elEta   = NULL , *Hdy_elPhi    = NULL , *Hdy_elPt  = NULL ;
  TH1F *Hdy_taEta   = NULL , *Hdy_taPhi    = NULL , *Hdy_taPt  = NULL ;
  TH1F *Hdy_mll     = NULL , *Hdy_ptll     = NULL , *Hdy_mt    = NULL ;

  TH1F *Hdb_mllCorr = NULL , *Hdb_ptllCorr = NULL , *Hdb_etall = NULL ;
  TH1F *Hdb_phill   = NULL , *Hdb_njet     = NULL , *Hdb_met   = NULL ;
  TH1F *Hdb_muEta   = NULL , *Hdb_muPhi    = NULL , *Hdb_muPt  = NULL ;
  TH1F *Hdb_elEta   = NULL , *Hdb_elPhi    = NULL , *Hdb_elPt  = NULL ;
  TH1F *Hdb_taEta   = NULL , *Hdb_taPhi    = NULL , *Hdb_taPt  = NULL ;
  TH1F *Hdb_mll     = NULL , *Hdb_ptll     = NULL , *Hdb_mt    = NULL ;

  TH1F *Htop_mllCorr = NULL , *Htop_ptllCorr = NULL , *Htop_etall = NULL ;
  TH1F *Htop_phill   = NULL , *Htop_njet     = NULL , *Htop_met   = NULL ;
  TH1F *Htop_muEta   = NULL , *Htop_muPhi    = NULL , *Htop_muPt  = NULL ;
  TH1F *Htop_elEta   = NULL , *Htop_elPhi    = NULL , *Htop_elPt  = NULL ;
  TH1F *Htop_taEta   = NULL , *Htop_taPhi    = NULL , *Htop_taPt  = NULL ;
  TH1F *Htop_mll     = NULL , *Htop_ptll     = NULL , *Htop_mt    = NULL ;

  TH1F *Hwjet_mllCorr = NULL , *Hwjet_ptllCorr = NULL , *Hwjet_etall = NULL ;
  TH1F *Hwjet_phill   = NULL , *Hwjet_njet     = NULL , *Hwjet_met   = NULL ;
  TH1F *Hwjet_muEta   = NULL , *Hwjet_muPhi    = NULL , *Hwjet_muPt  = NULL ;
  TH1F *Hwjet_elEta   = NULL , *Hwjet_elPhi    = NULL , *Hwjet_elPt  = NULL ;
  TH1F *Hwjet_taEta   = NULL , *Hwjet_taPhi    = NULL , *Hwjet_taPt  = NULL ;
  TH1F *Hwjet_mll     = NULL , *Hwjet_ptll     = NULL , *Hwjet_mt    = NULL ;

  TH1F *Hqcd_mllCorr = NULL , *Hqcd_ptllCorr = NULL , *Hqcd_etall = NULL ;
  TH1F *Hqcd_phill   = NULL , *Hqcd_njet     = NULL , *Hqcd_met   = NULL ;
  TH1F *Hqcd_muEta   = NULL , *Hqcd_muPhi    = NULL , *Hqcd_muPt  = NULL ;
  TH1F *Hqcd_elEta   = NULL , *Hqcd_elPhi    = NULL , *Hqcd_elPt  = NULL ;
  TH1F *Hqcd_taEta   = NULL , *Hqcd_taPhi    = NULL , *Hqcd_taPt  = NULL ;
  TH1F *Hqcd_mll     = NULL , *Hqcd_ptll     = NULL , *Hqcd_mt    = NULL ;
  TH1F *Hqcd_mllCorr_Orig = NULL;
  
  TH1F *Hqw_mllCorr = NULL , *Hqw_ptllCorr = NULL , *Hqw_etall = NULL ;
  TH1F *Hqw_phill   = NULL , *Hqw_njet     = NULL , *Hqw_met   = NULL ;
  TH1F *Hqw_muEta   = NULL , *Hqw_muPhi    = NULL , *Hqw_muPt  = NULL ;
  TH1F *Hqw_elEta   = NULL , *Hqw_elPhi    = NULL , *Hqw_elPt  = NULL ;
  TH1F *Hqw_taEta   = NULL , *Hqw_taPhi    = NULL , *Hqw_taPt  = NULL ;
  TH1F *Hqw_mll     = NULL , *Hqw_ptll     = NULL , *Hqw_mt    = NULL ;
  TH1F *Hqw_mllCorr_Orig = NULL;
  
  TH1F *Htot_mllCorr = NULL , *Htot_ptllCorr = NULL , *Htot_etall = NULL ;
  TH1F *Htot_phill   = NULL , *Htot_njet     = NULL , *Htot_met   = NULL ;
  TH1F *Htot_muEta   = NULL , *Htot_muPhi    = NULL , *Htot_muPt  = NULL ;
  TH1F *Htot_elEta   = NULL , *Htot_elPhi    = NULL , *Htot_elPt  = NULL ;
  TH1F *Htot_taEta   = NULL , *Htot_taPhi    = NULL , *Htot_taPt  = NULL ;
  TH1F *Htot_mll     = NULL , *Htot_ptll     = NULL , *Htot_mt    = NULL ;
  TH1F *Htot_mllCorr_Orig = NULL;
  
  for(uint i=0; i<sysVar.size(); i++){

    std::cout << "< MergeContributions() >:: Processing Sys = "
	      << sysVar.at(i) << std::endl;

    std::string fName = Dir+"Plots_"+sysVar.at(i)+"_"+lfvType;
    if(isBlind)  { fName += "_Blind";  }
    if(usePtRw)  { fName += "_PtRw";   }
    if(useSmooth){ fName += "_Smooth"; }
    
    InFile = new TFile( (fName+".root").c_str(), "UPDATE" );
    
    /* retrieve all plots */
    Hdy_mllCorr  = (TH1F*)InFile->Get( "hmllCorr_DY"  );
    Hdy_mll      = (TH1F*)InFile->Get( "hmll_DY"      );
    Hdy_ptllCorr = (TH1F*)InFile->Get( "hptllCorr_DY" );
    Hdy_ptll     = (TH1F*)InFile->Get( "hptll_DY"     );
    Hdy_phill    = (TH1F*)InFile->Get( "hphill_DY"    );
    Hdy_etall    = (TH1F*)InFile->Get( "hetall_DY"    );
    Hdy_muEta    = (TH1F*)InFile->Get( "hmu_eta_DY"   );
    Hdy_muPhi    = (TH1F*)InFile->Get( "hmu_phi_DY"   );
    Hdy_muPt     = (TH1F*)InFile->Get( "hmu_pt_DY"    );
    Hdy_elEta    = (TH1F*)InFile->Get( "hel_eta_DY"   );
    Hdy_elPhi    = (TH1F*)InFile->Get( "hel_phi_DY"   );
    Hdy_elPt     = (TH1F*)InFile->Get( "hel_pt_DY"    );
    Hdy_taEta    = (TH1F*)InFile->Get( "hta_eta_DY"   );
    Hdy_taPhi    = (TH1F*)InFile->Get( "hta_phi_DY"   );
    Hdy_taPt     = (TH1F*)InFile->Get( "hta_pt_DY"    );
    Hdy_njet     = (TH1F*)InFile->Get( "hnjet_DY"     );
    Hdy_met      = (TH1F*)InFile->Get( "hmet_DY"      );
    Hdy_mt       = (TH1F*)InFile->Get( "hmt_DY"       );
    
    Hdb_mllCorr  = (TH1F*)InFile->Get( "hmllCorr_DiBoson"  );
    Hdb_mll      = (TH1F*)InFile->Get( "hmll_DiBoson"      );
    Hdb_ptllCorr = (TH1F*)InFile->Get( "hptllCorr_DiBoson" );
    Hdb_ptll     = (TH1F*)InFile->Get( "hptll_DiBoson"     );
    Hdb_phill    = (TH1F*)InFile->Get( "hphill_DiBoson"    );
    Hdb_etall    = (TH1F*)InFile->Get( "hetall_DiBoson"    );
    Hdb_muEta    = (TH1F*)InFile->Get( "hmu_eta_DiBoson"   );
    Hdb_muPhi    = (TH1F*)InFile->Get( "hmu_phi_DiBoson"   );
    Hdb_muPt     = (TH1F*)InFile->Get( "hmu_pt_DiBoson"    );
    Hdb_elEta    = (TH1F*)InFile->Get( "hel_eta_DiBoson"   );
    Hdb_elPhi    = (TH1F*)InFile->Get( "hel_phi_DiBoson"   );
    Hdb_elPt     = (TH1F*)InFile->Get( "hel_pt_DiBoson"    );
    Hdb_taEta    = (TH1F*)InFile->Get( "hta_eta_DiBoson"   );
    Hdb_taPhi    = (TH1F*)InFile->Get( "hta_phi_DiBoson"   );
    Hdb_taPt     = (TH1F*)InFile->Get( "hta_pt_DiBoson"    );
    Hdb_njet     = (TH1F*)InFile->Get( "hnjet_DiBoson"     );
    Hdb_met      = (TH1F*)InFile->Get( "hmet_DiBoson"      );
    Hdb_mt       = (TH1F*)InFile->Get( "hmt_DiBoson"       );
    
    Htop_mllCorr  = (TH1F*)InFile->Get( "hmllCorr_Top"  );
    Htop_mll      = (TH1F*)InFile->Get( "hmll_Top"      );
    Htop_ptllCorr = (TH1F*)InFile->Get( "hptllCorr_Top" );
    Htop_ptll     = (TH1F*)InFile->Get( "hptll_Top"     );
    Htop_phill    = (TH1F*)InFile->Get( "hphill_Top"    );
    Htop_etall    = (TH1F*)InFile->Get( "hetall_Top"    );
    Htop_muEta    = (TH1F*)InFile->Get( "hmu_eta_Top"   );
    Htop_muPhi    = (TH1F*)InFile->Get( "hmu_phi_Top"   );
    Htop_muPt     = (TH1F*)InFile->Get( "hmu_pt_Top"    );
    Htop_elEta    = (TH1F*)InFile->Get( "hel_eta_Top"   );
    Htop_elPhi    = (TH1F*)InFile->Get( "hel_phi_Top"   );
    Htop_elPt     = (TH1F*)InFile->Get( "hel_pt_Top"    );
    Htop_taEta    = (TH1F*)InFile->Get( "hta_eta_Top"   );
    Htop_taPhi    = (TH1F*)InFile->Get( "hta_phi_Top"   );
    Htop_taPt     = (TH1F*)InFile->Get( "hta_pt_Top"    );
    Htop_njet     = (TH1F*)InFile->Get( "hnjet_Top"     );
    Htop_met      = (TH1F*)InFile->Get( "hmet_Top"      );
    Htop_mt       = (TH1F*)InFile->Get( "hmt_Top"       );
    
    Hqcd_mllCorr  = (TH1F*)InFile->Get( "hmllCorr_qcd"  );
    Hqcd_mll      = (TH1F*)InFile->Get( "hmll_qcd"      );
    Hqcd_ptllCorr = (TH1F*)InFile->Get( "hptllCorr_qcd" );
    Hqcd_ptll     = (TH1F*)InFile->Get( "hptll_qcd"     );
    Hqcd_phill    = (TH1F*)InFile->Get( "hphill_qcd"    );
    Hqcd_etall    = (TH1F*)InFile->Get( "hetall_qcd"    );
    Hqcd_muEta    = (TH1F*)InFile->Get( "hmu_eta_qcd"   );
    Hqcd_muPhi    = (TH1F*)InFile->Get( "hmu_phi_qcd"   );
    Hqcd_muPt     = (TH1F*)InFile->Get( "hmu_pt_qcd"    );
    Hqcd_elEta    = (TH1F*)InFile->Get( "hel_eta_qcd"   );
    Hqcd_elPhi    = (TH1F*)InFile->Get( "hel_phi_qcd"   );
    Hqcd_elPt     = (TH1F*)InFile->Get( "hel_pt_qcd"    );
    Hqcd_taEta    = (TH1F*)InFile->Get( "hta_eta_qcd"   );
    Hqcd_taPhi    = (TH1F*)InFile->Get( "hta_phi_qcd"   );
    Hqcd_taPt     = (TH1F*)InFile->Get( "hta_pt_qcd"    );
    Hqcd_njet     = (TH1F*)InFile->Get( "hnjet_qcd"     );
    Hqcd_met      = (TH1F*)InFile->Get( "hmet_qcd"      );
    Hqcd_mt       = (TH1F*)InFile->Get( "hmt_qcd"       );
    if(LFVtype==2)
      Hqcd_mllCorr_Orig = (TH1F*)InFile->Get( "hmllCorr_qcd_Orig" );

    if(LFVtype>1){
      Hwjet_mllCorr  = (TH1F*)InFile->Get( "hmllCorr_Wjets"  );
      Hwjet_mll      = (TH1F*)InFile->Get( "hmll_Wjets"      );
      Hwjet_ptllCorr = (TH1F*)InFile->Get( "hptllCorr_Wjets" );
      Hwjet_ptll     = (TH1F*)InFile->Get( "hptll_Wjets"     );
      Hwjet_phill    = (TH1F*)InFile->Get( "hphill_Wjets"    );
      Hwjet_etall    = (TH1F*)InFile->Get( "hetall_Wjets"    );
      Hwjet_muEta    = (TH1F*)InFile->Get( "hmu_eta_Wjets"   );
      Hwjet_muPhi    = (TH1F*)InFile->Get( "hmu_phi_Wjets"   );
      Hwjet_muPt     = (TH1F*)InFile->Get( "hmu_pt_Wjets"    );
      Hwjet_elEta    = (TH1F*)InFile->Get( "hel_eta_Wjets"   );
      Hwjet_elPhi    = (TH1F*)InFile->Get( "hel_phi_Wjets"   );
      Hwjet_elPt     = (TH1F*)InFile->Get( "hel_pt_Wjets"    );
      Hwjet_taEta    = (TH1F*)InFile->Get( "hta_eta_Wjets"   );
      Hwjet_taPhi    = (TH1F*)InFile->Get( "hta_phi_Wjets"   );
      Hwjet_taPt     = (TH1F*)InFile->Get( "hta_pt_Wjets"    );
      Hwjet_njet     = (TH1F*)InFile->Get( "hnjet_Wjets"     );
      Hwjet_met      = (TH1F*)InFile->Get( "hmet_Wjets"      );
      Hwjet_mt       = (TH1F*)InFile->Get( "hmt_Wjets"       );
    }
    
    /* Create new plots */
    Hqw_mllCorr  = (TH1F*)Hdb_mllCorr  ->Clone( "hmllCorr_Multijet"  );
    Hqw_mll      = (TH1F*)Hdb_mllCorr  ->Clone( "hmll_Multijet"      );
    Hqw_ptllCorr = (TH1F*)Hdb_ptllCorr ->Clone( "hptllCorr_Multijet" );
    Hqw_ptll     = (TH1F*)Hdb_ptllCorr ->Clone( "hptll_Multijet"     );
    Hqw_phill    = (TH1F*)Hdb_phill    ->Clone( "hphill_Multijet"    );
    Hqw_etall    = (TH1F*)Hdb_etall    ->Clone( "hetall_Multijet"    );
    Hqw_muEta    = (TH1F*)Hdb_muEta    ->Clone( "hmu_eta_Multijet"   );
    Hqw_muPhi    = (TH1F*)Hdb_muPhi    ->Clone( "hmu_phi_Multijet"   );
    Hqw_muPt     = (TH1F*)Hdb_muPt     ->Clone( "hmu_pt_Multijet"    );
    Hqw_elEta    = (TH1F*)Hdb_elEta    ->Clone( "hel_eta_Multijet"   );
    Hqw_elPhi    = (TH1F*)Hdb_elPhi    ->Clone( "hel_phi_Multijet"   );
    Hqw_elPt     = (TH1F*)Hdb_elPt     ->Clone( "hel_pt_Multijet"    );
    Hqw_taEta    = (TH1F*)Hdb_taEta    ->Clone( "hta_eta_Multijet"   );
    Hqw_taPhi    = (TH1F*)Hdb_taPhi    ->Clone( "hta_phi_Multijet"   );
    Hqw_taPt     = (TH1F*)Hdb_taPt     ->Clone( "hta_pt_Multijet"    );
    Hqw_njet     = (TH1F*)Hdb_njet     ->Clone( "hnjet_Multijet"     );
    Hqw_met      = (TH1F*)Hdb_met      ->Clone( "hmet_Multijet"      );
    Hqw_mt       = (TH1F*)Hdb_mt       ->Clone( "hmt_Multijet"       );
    if(LFVtype==2)
      Hqw_mllCorr_Orig = (TH1F*)Hdb_mllCorr->Clone( "hmllCorr_Multijet_Orig" );

    Hqw_mllCorr  -> Reset();
    Hqw_mll      -> Reset();
    Hqw_ptllCorr -> Reset();
    Hqw_ptll     -> Reset();
    Hqw_phill    -> Reset();
    Hqw_etall    -> Reset();
    Hqw_muEta    -> Reset();
    Hqw_muPhi    -> Reset();
    Hqw_muPt     -> Reset();
    Hqw_elEta    -> Reset();
    Hqw_elPhi    -> Reset();
    Hqw_elPt     -> Reset();
    Hqw_taEta    -> Reset();
    Hqw_taPhi    -> Reset();
    Hqw_taPt     -> Reset();
    Hqw_njet     -> Reset();
    Hqw_met      -> Reset();
    Hqw_mt       -> Reset();
    if(LFVtype==2)
      Hqw_mllCorr_Orig -> Reset();
    
    Htot_mllCorr  = (TH1F*)Hdb_mllCorr  ->Clone( "hmllCorr_BkgTot"  );
    Htot_mll      = (TH1F*)Hdb_mll      ->Clone( "hmll_BkgTot"      );
    Htot_ptllCorr = (TH1F*)Hdb_ptllCorr ->Clone( "hptllCorr_BkgTot" );
    Htot_ptll     = (TH1F*)Hdb_ptll     ->Clone( "hptll_BkgTot"     );
    Htot_phill    = (TH1F*)Hdb_phill    ->Clone( "hphill_BkgTot"    );
    Htot_etall    = (TH1F*)Hdb_etall    ->Clone( "hetall_BkgTot"    );
    Htot_muEta    = (TH1F*)Hdb_muEta    ->Clone( "hmu_eta_BkgTot"   );
    Htot_muPhi    = (TH1F*)Hdb_muPhi    ->Clone( "hmu_phi_BkgTot"   );
    Htot_muPt     = (TH1F*)Hdb_muPt     ->Clone( "hmu_pt_BkgTot"    );
    Htot_elEta    = (TH1F*)Hdb_elEta    ->Clone( "hel_eta_BkgTot"   );
    Htot_elPhi    = (TH1F*)Hdb_elPhi    ->Clone( "hel_phi_BkgTot"   );
    Htot_elPt     = (TH1F*)Hdb_elPt     ->Clone( "hel_pt_BkgTot"    );
    Htot_taEta    = (TH1F*)Hdb_taEta    ->Clone( "hta_eta_BkgTot"   );
    Htot_taPhi    = (TH1F*)Hdb_taPhi    ->Clone( "hta_phi_BkgTot"   );
    Htot_taPt     = (TH1F*)Hdb_taPt     ->Clone( "hta_pt_BkgTot"    );
    Htot_njet     = (TH1F*)Hdb_njet     ->Clone( "hnjet_BkgTot"     );
    Htot_met      = (TH1F*)Hdb_met      ->Clone( "hmet_BkgTot"      );
    Htot_mt       = (TH1F*)Hdb_mt       ->Clone( "hmt_BkgTot"       );
    if(LFVtype==2)
      Htot_mllCorr_Orig = (TH1F*)Hdb_mllCorr->Clone( "hmllCorr_BkgTot_Orig" );
    
    Htot_mllCorr  -> Reset();
    Htot_mll      -> Reset();
    Htot_ptllCorr -> Reset();
    Htot_ptll     -> Reset();
    Htot_phill    -> Reset();
    Htot_etall    -> Reset();
    Htot_muEta    -> Reset();
    Htot_muPhi    -> Reset();
    Htot_muPt     -> Reset();
    Htot_elEta    -> Reset();
    Htot_elPhi    -> Reset();
    Htot_elPt     -> Reset();
    Htot_taEta    -> Reset();
    Htot_taPhi    -> Reset();
    Htot_taPt     -> Reset();
    Htot_njet     -> Reset();
    Htot_met      -> Reset();
    Htot_mt       -> Reset();
    if(LFVtype==2)
      Htot_mllCorr_Orig -> Reset();
    
    /* Make Multijet */
    if(m_debug){
      std::cout << "< MergeContributions() >:: Merging Multi-jets ... " << std::endl;
      std::cout << "                            adding qcd ... " << std::endl;
    }
    Hqw_mllCorr  -> Add( Hqcd_mllCorr  );
    Hqw_mll      -> Add( Hqcd_mll      );
    Hqw_ptllCorr -> Add( Hqcd_ptllCorr );
    Hqw_ptll     -> Add( Hqcd_ptll     );
    Hqw_phill    -> Add( Hqcd_phill    );
    Hqw_etall    -> Add( Hqcd_etall    );
    Hqw_muEta    -> Add( Hqcd_muEta    );
    Hqw_muPhi    -> Add( Hqcd_muPhi    );
    Hqw_muPt     -> Add( Hqcd_muPt     );
    Hqw_elEta    -> Add( Hqcd_elEta    );
    Hqw_elPhi    -> Add( Hqcd_elPhi    );
    Hqw_elPt     -> Add( Hqcd_elPt     );
    Hqw_taEta    -> Add( Hqcd_taEta    );
    Hqw_taPhi    -> Add( Hqcd_taPhi    );
    Hqw_taPt     -> Add( Hqcd_taPt     );
    Hqw_njet     -> Add( Hqcd_njet     );
    Hqw_met      -> Add( Hqcd_met      );
    Hqw_mt       -> Add( Hqcd_mt       );
     if(LFVtype==2)
       Hqw_mllCorr_Orig -> Add( Hqcd_mllCorr_Orig );
     
     if(LFVtype>1){
      
      if(m_debug)
	std::cout << "                            adding W+jets ... " << std::endl;
      
      Hqw_mllCorr  -> Add( Hwjet_mllCorr  );
      Hqw_mll      -> Add( Hwjet_mll      );
      Hqw_ptllCorr -> Add( Hwjet_ptllCorr );
      Hqw_ptll     -> Add( Hwjet_ptll     );
      Hqw_phill    -> Add( Hwjet_phill    );
      Hqw_etall    -> Add( Hwjet_etall    );
      Hqw_muEta    -> Add( Hwjet_muEta    );
      Hqw_muPhi    -> Add( Hwjet_muPhi    );
      Hqw_muPt     -> Add( Hwjet_muPt     );
      Hqw_elEta    -> Add( Hwjet_elEta    );
      Hqw_elPhi    -> Add( Hwjet_elPhi    );
      Hqw_elPt     -> Add( Hwjet_elPt     );
      Hqw_taEta    -> Add( Hwjet_taEta    );
      Hqw_taPhi    -> Add( Hwjet_taPhi    );
      Hqw_taPt     -> Add( Hwjet_taPt     );
      Hqw_njet     -> Add( Hwjet_njet     );
      Hqw_met      -> Add( Hwjet_met      );
      Hqw_mt       -> Add( Hwjet_mt       );
      if(LFVtype==2)
	Hqw_mllCorr_Orig -> Add( Hwjet_mllCorr );
    }

    /* Make BkgTot */
    if(m_debug){
      std::cout << "< MergeContributions() >:: Merging Total ... " << std::endl;
      std::cout << "                            adding DY ... " << std::endl;
    }
    Htot_mllCorr  -> Add( Hdy_mllCorr  );
    Htot_mll      -> Add( Hdy_mll      );
    Htot_ptllCorr -> Add( Hdy_ptllCorr );
    Htot_ptll     -> Add( Hdy_ptll     );
    Htot_phill    -> Add( Hdy_phill    );
    Htot_etall    -> Add( Hdy_etall    );
    Htot_muEta    -> Add( Hdy_muEta    );
    Htot_muPhi    -> Add( Hdy_muPhi    );
    Htot_muPt     -> Add( Hdy_muPt     );
    Htot_elEta    -> Add( Hdy_elEta    );
    Htot_elPhi    -> Add( Hdy_elPhi    );
    Htot_elPt     -> Add( Hdy_elPt     );
    Htot_taEta    -> Add( Hdy_taEta    );
    Htot_taPhi    -> Add( Hdy_taPhi    );
    Htot_taPt     -> Add( Hdy_taPt     );
    Htot_njet     -> Add( Hdy_njet     );
    Htot_met      -> Add( Hdy_met      );
    Htot_mt       -> Add( Hdy_mt       );

    if(m_debug)
      std::cout << "                            adding DiBoson ... " << std::endl;
    
    Htot_mllCorr  -> Add( Hdb_mllCorr  );
    Htot_mll      -> Add( Hdb_mll      );
    Htot_ptllCorr -> Add( Hdb_ptllCorr );
    Htot_ptll     -> Add( Hdb_ptll     );
    Htot_phill    -> Add( Hdb_phill    );
    Htot_etall    -> Add( Hdb_etall    );
    Htot_muEta    -> Add( Hdb_muEta    );
    Htot_muPhi    -> Add( Hdb_muPhi    );
    Htot_muPt     -> Add( Hdb_muPt     );
    Htot_elEta    -> Add( Hdb_elEta    );
    Htot_elPhi    -> Add( Hdb_elPhi    );
    Htot_elPt     -> Add( Hdb_elPt     );
    Htot_taEta    -> Add( Hdb_taEta    );
    Htot_taPhi    -> Add( Hdb_taPhi    );
    Htot_taPt     -> Add( Hdb_taPt     );
    Htot_njet     -> Add( Hdb_njet     );
    Htot_met      -> Add( Hdb_met      );
    Htot_mt       -> Add( Hdb_mt       );

    if(m_debug)
      std::cout << "                            adding Top ... " << std::endl;

    Htot_mllCorr  -> Add( Htop_mllCorr  );
    Htot_mll      -> Add( Htop_mll      );
    Htot_ptllCorr -> Add( Htop_ptllCorr );
    Htot_ptll     -> Add( Htop_ptll     );
    Htot_phill    -> Add( Htop_phill    );
    Htot_etall    -> Add( Htop_etall    );
    Htot_muEta    -> Add( Htop_muEta    );
    Htot_muPhi    -> Add( Htop_muPhi    );
    Htot_muPt     -> Add( Htop_muPt     );
    Htot_elEta    -> Add( Htop_elEta    );
    Htot_elPhi    -> Add( Htop_elPhi    );
    Htot_elPt     -> Add( Htop_elPt     );
    Htot_taEta    -> Add( Htop_taEta    );
    Htot_taPhi    -> Add( Htop_taPhi    );
    Htot_taPt     -> Add( Htop_taPt     );
    Htot_njet     -> Add( Htop_njet     );
    Htot_met      -> Add( Htop_met      );
    Htot_mt       -> Add( Htop_mt       );

    if(m_debug)
      std::cout << "                            adding qcd ... " << std::endl;

    Htot_mllCorr  -> Add( Hqcd_mllCorr  );
    Htot_mll      -> Add( Hqcd_mll      );
    Htot_ptllCorr -> Add( Hqcd_ptllCorr );
    Htot_ptll     -> Add( Hqcd_ptll     );
    Htot_phill    -> Add( Hqcd_phill    );
    Htot_etall    -> Add( Hqcd_etall    );
    Htot_muEta    -> Add( Hqcd_muEta    );
    Htot_muPhi    -> Add( Hqcd_muPhi    );
    Htot_muPt     -> Add( Hqcd_muPt     );
    Htot_elEta    -> Add( Hqcd_elEta    );
    Htot_elPhi    -> Add( Hqcd_elPhi    );
    Htot_elPt     -> Add( Hqcd_elPt     );
    Htot_taEta    -> Add( Hqcd_taEta    );
    Htot_taPhi    -> Add( Hqcd_taPhi    );
    Htot_taPt     -> Add( Hqcd_taPt     );
    Htot_njet     -> Add( Hqcd_njet     );
    Htot_met      -> Add( Hqcd_met      );
    Htot_mt       -> Add( Hqcd_mt       );
    
    if(LFVtype>1){

      if(m_debug)
	std::cout << "                            adding W+jets ... " << std::endl;
      
      Htot_mllCorr  -> Add( Hwjet_mllCorr  );
      Htot_mll      -> Add( Hwjet_mll      );
      Htot_ptllCorr -> Add( Hwjet_ptllCorr );
      Htot_ptll     -> Add( Hwjet_ptll     );
      Htot_phill    -> Add( Hwjet_phill    );
      Htot_etall    -> Add( Hwjet_etall    );
      Htot_muEta    -> Add( Hwjet_muEta    );
      Htot_muPhi    -> Add( Hwjet_muPhi    );
      Htot_muPt     -> Add( Hwjet_muPt     );
      Htot_elEta    -> Add( Hwjet_elEta    );
      Htot_elPhi    -> Add( Hwjet_elPhi    );
      Htot_elPt     -> Add( Hwjet_elPt     );
      Htot_taEta    -> Add( Hwjet_taEta    );
      Htot_taPhi    -> Add( Hwjet_taPhi    );
      Htot_taPt     -> Add( Hwjet_taPt     );
      Htot_njet     -> Add( Hwjet_njet     );
      Htot_met      -> Add( Hwjet_met      );
      Htot_mt       -> Add( Hwjet_mt       );

      if(LFVtype==2){
	Htot_mllCorr_Orig -> Add( Hdy_mllCorr       );
	Htot_mllCorr_Orig -> Add( Hdb_mllCorr       );
	Htot_mllCorr_Orig -> Add( Htop_mllCorr      );
	Htot_mllCorr_Orig -> Add( Hwjet_mllCorr     );
	Htot_mllCorr_Orig -> Add( Hqcd_mllCorr_Orig );
      }
    }
    
    InFile->cd();
    /* Write Histos */
    Hqw_mllCorr   -> Write();
    Hqw_mll       -> Write();
    Hqw_ptllCorr  -> Write();
    Hqw_ptll      -> Write();
    Hqw_phill     -> Write();
    Hqw_etall     -> Write();
    Hqw_muEta     -> Write();
    Hqw_muPhi     -> Write();
    Hqw_muPt      -> Write();
    Hqw_elEta     -> Write();
    Hqw_elPhi     -> Write();
    Hqw_elPt      -> Write();
    Hqw_taEta     -> Write();
    Hqw_taPhi     -> Write();
    Hqw_taPt      -> Write();
    Hqw_njet      -> Write();
    Hqw_met       -> Write();
    Htot_mllCorr  -> Write();
    Htot_mll      -> Write();
    Htot_ptllCorr -> Write();
    Htot_ptll     -> Write();
    Htot_phill    -> Write();
    Htot_etall    -> Write();
    Htot_muEta    -> Write();
    Htot_muPhi    -> Write();
    Htot_muPt     -> Write();
    Htot_elEta    -> Write();
    Htot_elPhi    -> Write();
    Htot_elPt     -> Write();
    Htot_taEta    -> Write();
    Htot_taPhi    -> Write();
    Htot_taPt     -> Write();
    Htot_njet     -> Write();
    Htot_met      -> Write();
    Hqw_mt        -> Write();
    Htot_mt       -> Write();
    if(LFVtype==2){
      Hqw_mllCorr_Orig  -> Write();
      Htot_mllCorr_Orig -> Write();
    }
    
    /* cleaning new histos */
    Hqw_mllCorr   -> Delete();
    Hqw_mll       -> Delete();
    Hqw_ptllCorr  -> Delete();
    Hqw_ptll      -> Delete();
    Hqw_phill     -> Delete();
    Hqw_etall     -> Delete();
    Hqw_muEta     -> Delete();
    Hqw_muPhi     -> Delete();
    Hqw_muPt      -> Delete();
    Hqw_elEta     -> Delete();
    Hqw_elPhi     -> Delete();
    Hqw_elPt      -> Delete();
    Hqw_taEta     -> Delete();
    Hqw_taPhi     -> Delete();
    Hqw_taPt      -> Delete();
    Hqw_njet      -> Delete();
    Hqw_met       -> Delete();
    Htot_mllCorr  -> Delete();
    Htot_mll      -> Delete();
    Htot_ptllCorr -> Delete();
    Htot_ptll     -> Delete();
    Htot_phill    -> Delete();
    Htot_etall    -> Delete();
    Htot_muEta    -> Delete();
    Htot_muPhi    -> Delete();
    Htot_muPt     -> Delete();
    Htot_elEta    -> Delete();
    Htot_elPhi    -> Delete();
    Htot_elPt     -> Delete();
    Htot_taEta    -> Delete();
    Htot_taPhi    -> Delete();
    Htot_taPt     -> Delete();
    Htot_njet     -> Delete();
    Htot_met      -> Delete();
    Hqw_mt        -> Delete();
    Htot_mt       -> Delete();
    if(LFVtype==2){
      Hqw_mllCorr_Orig  -> Delete();
      Htot_mllCorr_Orig -> Delete();   
    }
    /* cleaning input histos */
    Hdy_mllCorr   -> Delete();
    Hdy_mll       -> Delete();
    Hdy_ptllCorr  -> Delete();
    Hdy_ptll      -> Delete();
    Hdy_phill     -> Delete();
    Hdy_etall     -> Delete();
    Hdy_muEta     -> Delete();
    Hdy_muPhi     -> Delete();
    Hdy_muPt      -> Delete();
    Hdy_elEta     -> Delete();
    Hdy_elPhi     -> Delete();
    Hdy_elPt      -> Delete();
    Hdy_taEta     -> Delete();
    Hdy_taPhi     -> Delete();
    Hdy_taPt      -> Delete();
    Hdy_njet      -> Delete();
    Hdy_met       -> Delete();
    Hdy_mt        -> Delete();
    Hdb_mllCorr   -> Delete();
    Hdb_mll       -> Delete();
    Hdb_ptllCorr  -> Delete();
    Hdb_ptll      -> Delete();
    Hdb_phill     -> Delete();
    Hdb_etall     -> Delete();
    Hdb_muEta     -> Delete();
    Hdb_muPhi     -> Delete();
    Hdb_muPt      -> Delete();
    Hdb_elEta     -> Delete();
    Hdb_elPhi     -> Delete();
    Hdb_elPt      -> Delete();
    Hdb_taEta     -> Delete();
    Hdb_taPhi     -> Delete();
    Hdb_taPt      -> Delete();
    Hdb_njet      -> Delete();
    Hdb_met       -> Delete();
    Hdb_mt        -> Delete();
    Htop_mllCorr  -> Delete();
    Htop_mll      -> Delete();
    Htop_ptllCorr -> Delete();
    Htop_ptll     -> Delete();
    Htop_phill    -> Delete();
    Htop_etall    -> Delete();
    Htop_muEta    -> Delete();
    Htop_muPhi    -> Delete();
    Htop_muPt     -> Delete();
    Htop_elEta    -> Delete();
    Htop_elPhi    -> Delete();
    Htop_elPt     -> Delete();
    Htop_taEta    -> Delete();
    Htop_taPhi    -> Delete();
    Htop_taPt     -> Delete();
    Htop_njet     -> Delete();
    Htop_met      -> Delete();
    Htop_mt       -> Delete();
    Hqcd_mllCorr  -> Delete();
    Hqcd_mll      -> Delete();
    Hqcd_ptllCorr -> Delete();
    Hqcd_ptll     -> Delete();
    Hqcd_phill    -> Delete();
    Hqcd_etall    -> Delete();
    Hqcd_muEta    -> Delete();
    Hqcd_muPhi    -> Delete();
    Hqcd_muPt     -> Delete();
    Hqcd_elEta    -> Delete();
    Hqcd_elPhi    -> Delete();
    Hqcd_elPt     -> Delete();
    Hqcd_taEta    -> Delete();
    Hqcd_taPhi    -> Delete();
    Hqcd_taPt     -> Delete();
    Hqcd_njet     -> Delete();
    Hqcd_met      -> Delete();
    Hqcd_mt       -> Delete();
    if(LFVtype>1){
      Hwjet_mllCorr  -> Delete();
      Hwjet_mll      -> Delete();
      Hwjet_ptllCorr -> Delete();
      Hwjet_ptll     -> Delete();
      Hwjet_phill    -> Delete();
      Hwjet_etall    -> Delete();
      Hwjet_muEta    -> Delete();
      Hwjet_muPhi    -> Delete();
      Hwjet_muPt     -> Delete();
      Hwjet_elEta    -> Delete();
      Hwjet_elPhi    -> Delete();
      Hwjet_elPt     -> Delete();
      Hwjet_taEta    -> Delete();
      Hwjet_taPhi    -> Delete();
      Hwjet_taPt     -> Delete();
      Hwjet_njet     -> Delete();
      Hwjet_met      -> Delete();
      Hwjet_mt       -> Delete();
    }
    if(LFVtype==2)
      Hqcd_mllCorr_Orig ->Delete();
    
    /* close files */
    InFile -> Close();
  }
  
}
