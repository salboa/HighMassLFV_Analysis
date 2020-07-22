/* program includes */
#include "CreateSysBands.h"
#include "ATLASstyle.C"

int main( int argc, char* argv[] ) {

  bool useBjet        = false  ;
  bool isBlind        = false  ;
  bool debug          = false  ;
  bool isttCR         = false  ;
  bool isRevDphi      = false  ;
  bool isSherpa       = false  ;
  bool addStatUnc     = false  ;
  int lfvType         = -1     ;
  std::string process = "BkgSM";
  bool printHelp      = false  ;
  for(int i = 1; i < argc; ++i){
    if( !strcmp(argv[i],"--useBjet")         ){ useBjet    = true; }
    else if( !strcmp(argv[i],"--isBlind")    ){ isBlind    = true; }
    else if( !strcmp(argv[i],"--process")    ){ process    = argv[i+1]; }
    else if( !strcmp(argv[i],"--lfvType")    ){ lfvType    = std::stoi(argv[i+1]); }
    else if( !strcmp(argv[i],"--isttCR")     ){ isttCR     = true; }
    else if( !strcmp(argv[i],"--isRevDphi")  ){ isRevDphi  = true; }
    else if( !strcmp(argv[i],"--isSherpa")   ){ isSherpa   = true; }
    else if( !strcmp(argv[i],"--addStatUnc") ){ addStatUnc = true; }
    else if( !strcmp(argv[i],"--debug")      ){ debug      = true; }
    else if( !strcmp(argv[i],"--help")       ){ printHelp  = true; }
    else{
      if(std::string(argv[i]).find("--")!=std::string::npos)
	std::cout << "WARNING:: Option " << argv[i] << " not recognized: "
		  << "skipping!" << std::endl;
    }
  }
  if(printHelp){
    std::cout << " CreatSysBands: make Sys Bands!" << std::endl;
    std::cout << "                Options: "                       << std::endl;
    std::cout << "                 --useBjet   [Enable b-jet veto:"
	      << " default is 'false' "                            << std::endl;
    std::cout << "                 --lfvType   [Choose lfv channel:"
	      << " options are '1,2,3'] "                          << std::endl;
    std::cout << "                 --process   [Define process:"
	      << " default is 'BkgSM' "                            << std::endl;
    std::cout << "                 --isBlind   [Enable Blind analysis:"
	      << " default is 'false'] "                           << std::endl;
    std::cout << "                 --isttCR    [Enable ttbar CR:"
	      << " default is 'false'] "                           << std::endl;
    std::cout << "                 --isRevDphi [Enable revDphi analysis:"
	      << " default is 'false'] "                           << std::endl;
    std::cout << "                 --isSherpa  [Enable Sherpa ttbar:"
	      << " default is 'false'] "                           << std::endl;
    std::cout << "                 --addStatUnc [Enable MC Stat Unc:"
	      << " default is 'false'] "                           << std::endl;
    std::cout << "                 --debug      [Enable debug]"    << std::endl;
    std::cout << "                 --help       [Print this help]" << std::endl;
    exit(0);
  }

  if(lfvType==-1){
    std::cout << "< CreateSysBands() >:: lfvType not set!"
	      << " Possible options: 1,2,3" << std::endl;
    exit(0);
  }
  
  std::cout << " CreatSysBands Options set: "         << std::endl;
  std::cout << "         useBjet    = " << useBjet    << std::endl;
  std::cout << "         lfvType    = " << lfvType    << std::endl;
  std::cout << "         process    = " << process    << std::endl;
  std::cout << "         isBlind    = " << isBlind    << std::endl;
  std::cout << "         isttCR     = " << isttCR     << std::endl;
  std::cout << "         isRevDphi  = " << isRevDphi  << std::endl;
  std::cout << "         isSherpa   = " << isSherpa   << std::endl;
  std::cout << "         addStatUnc = " << addStatUnc << std::endl;
  std::cout << "         debug      = " << debug      << std::endl;

  m_debug = debug;
  if(lfvType==1 && process=="Multijet")
    CreateSysBands(useBjet, isBlind, isttCR, isSherpa);
  else
    CreateSysBands(lfvType, useBjet, isBlind, isttCR, isRevDphi,
		   isSherpa, process, addStatUnc);
  
  return 0;
}

void CreateSysBands(int LFVtype, bool useBjet, bool isBlind, bool isttCR,
		    bool isRevDphi, bool isSherpa, std::string Process, bool addStatUnc){
  
  SetATLASStyle();
  TH1::SetDefaultSumw2(kTRUE);
  
  std::string lfvType = "";
  if(LFVtype==1)      { lfvType="emu";   }
  else if(LFVtype==2) { lfvType="etau";  }
  else if(LFVtype==3) { lfvType="mutau"; }

  std::cout << " Making Sys Bands for " << lfvType
	    << " Channel and " << Process << " Background" << std::endl;

  std::string Dir = "";
  if(useBjet){  Dir += "Bjet/";   }
  else{         Dir += "NoBjet/"; }

  if(isttCR)    {
    Dir += "ttbarCR";
    if(isSherpa) Dir += "_Sherpa";
    Dir += "/";
  }
  if(isRevDphi) { Dir += "revDphi/"; }

  /* Define Lumi Var */
  double Lvar = 2.1;

  /* Loading files */
  std::string InName   = Dir+"PercentVariations_"+lfvType;
  std::string OutName  = Dir+"SystematicsBands_"+lfvType;
  std::string DistName = Dir+"Plots_Nominal_"+lfvType;
  if(isBlind){
    InName   += "_Blind";
    OutName  += "_Blind";
    DistName += "_Blind";
  }
  if(Process!="BkgSM"){
    InName     += "_"+Process;
    OutName    += "_"+Process;
  }
  if(addStatUnc) OutName += "_WithStatUnc";

  TFile *distro = NULL;
  TFile *input  = new TFile( (InName+".root").c_str() );
  TFile *out    = new TFile( (OutName+".root").c_str(), "RECREATE" );
  if(addStatUnc) distro = new TFile( (DistName+".root").c_str() );
  
  /* Up */                               /* Down */
  TH1F *MuReco_StatUp        = NULL;     TH1F *MuReco_StatDown        = NULL;
  TH1F *MuReco_SysUp         = NULL;     TH1F *MuReco_SysDown         = NULL;
  TH1F *MuIso_StatUp         = NULL;     TH1F *MuIso_StatDown         = NULL;
  TH1F *MuIso_SysUp          = NULL;     TH1F *MuIso_SysDown          = NULL;
  TH1F *MuTrg_StatUp         = NULL;     TH1F *MuTrg_StatDown         = NULL;
  TH1F *MuTrg_SysUp          = NULL;     TH1F *MuTrg_SysDown          = NULL;
  TH1F *MuTTVA_StatUp        = NULL;     TH1F *MuTTVA_StatDown        = NULL;
  TH1F *MuTTVA_SysUp         = NULL;     TH1F *MuTTVA_SysDown         = NULL;
  TH1F *MuSmeID_SysUp        = NULL;     TH1F *MuSmeID_SysDown        = NULL;
  TH1F *MuSmeMS_SysUp        = NULL;     TH1F *MuSmeMS_SysDown        = NULL;
  TH1F *MuScale_SysUp        = NULL;     TH1F *MuScale_SysDown        = NULL;
  TH1F *MuSagRho_SysUp       = NULL;     TH1F *MuSagRho_SysDown       = NULL;
  TH1F *MuSagRes_SysUp       = NULL;     TH1F *MuSagRes_SysDown       = NULL;
  TH1F *ElReco_SysUp         = NULL;     TH1F *ElReco_SysDown         = NULL;
  TH1F *ElID_SysUp           = NULL;     TH1F *ElID_SysDown           = NULL;
  TH1F *ElIso_SysUp          = NULL;     TH1F *ElIso_SysDown          = NULL;
  TH1F *ElTrg_SysUp          = NULL;     TH1F *ElTrg_SysDown          = NULL;
  TH1F *ElSme_SysUp          = NULL;     TH1F *ElSme_SysDown          = NULL;
  TH1F *ElScale_SysUp        = NULL;     TH1F *ElScale_SysDown        = NULL;
  TH1F *TaReco_SysUp         = NULL;     TH1F *TaReco_SysDown 	      = NULL;
  TH1F *TaRecoHpt_SysUp	     = NULL;     TH1F *TaRecoHpt_SysDown      = NULL;
  TH1F *TaEleOlr_SysUp 	     = NULL;     TH1F *TaEleOlr_SysDown       = NULL;
  TH1F *TaJetID_SysUp 	     = NULL;     TH1F *TaJetID_SysDown	      = NULL;
  TH1F *TaJetIDHpt_SysUp     = NULL;     TH1F *TaJetIDHpt_SysDown     = NULL;
  TH1F *TaSme_SysUp    	     = NULL;     TH1F *TaSme_SysDown  	      = NULL;
  TH1F *TaSmeDet_SysUp 	     = NULL;     TH1F *TaSmeDet_SysDown       = NULL;
  TH1F *TaSmeMod_SysUp 	     = NULL;     TH1F *TaSmeMod_SysDown       = NULL;
  TH1F *BtagSF_Beff_SysUp    = NULL;     TH1F *BtagSF_Beff_SysDown    = NULL;
  TH1F *BtagSF_Ceff_SysUp    = NULL;	 TH1F *BtagSF_Ceff_SysDown    = NULL;
  TH1F *BtagSF_Leff_SysUp    = NULL;	 TH1F *BtagSF_Leff_SysDown    = NULL;
  TH1F *BtagSF_ExtCeff_SysUp = NULL;	 TH1F *BtagSF_ExtCeff_SysDown = NULL;
  TH1F *BtagSF_ExtEff_SysUp  = NULL;	 TH1F *BtagSF_ExtEff_SysDown  = NULL;
  TH1F *JtUncNP1_SysUp       = NULL;	 TH1F *JtUncNP1_SysDown       = NULL;
  TH1F *JtUncNP2_SysUp       = NULL;	 TH1F *JtUncNP2_SysDown       = NULL;
  TH1F *JtUncNP3_SysUp       = NULL;	 TH1F *JtUncNP3_SysDown       = NULL;
  TH1F *JtUncETA_SysUp       = NULL;	 TH1F *JtUncETA_SysDown       = NULL;
  TH1F *JtJvtSF_SysUp        = NULL;     TH1F *JtJvtSF_SysDown        = NULL;
  TH1F *MetScl_SysUp         = NULL;     TH1F *MetScl_SysDown         = NULL;
  TH1F *TopScale_SysUp       = NULL;     TH1F *TopScale_SysDown       = NULL;
  TH1F *PU_SysUp             = NULL;     TH1F *PU_SysDown             = NULL;
  TH1F *TauFake_StatUp       = NULL;     TH1F *TauFake_StatDown       = NULL;
  TH1F *TauFake_BDT_SysUp    = NULL;     TH1F *TauFake_BDT_SysDown    = NULL;
  TH1F *TauFake_CR_Sys       = NULL;     TH1F *JtSme_Sys              = NULL;
  TH1F *TauFake_Comp_SysUp   = NULL;     TH1F *TauFake_Comp_SysDown   = NULL;
  TH1F *TopFit_Sys           = NULL;     TH1F *PDF_Sys                = NULL;
  TH1F *MetResPer_Sys        = NULL;     TH1F *MetResPara_Sys         = NULL;
  TH1F *Multijet_kMJ_Stat    = NULL;     TH1F *Multijet_kMJ_Sys       = NULL;
  /* Distro */
  TH1F *Bkg = NULL;
  
  /* make list of Hist type */
  std::vector<std::string> Htype;
  Htype.push_back( "mllCorr"  );
  Htype.push_back( "mll"      );
  Htype.push_back( "ptllCorr" );
  Htype.push_back( "ptll"     );
  Htype.push_back( "etall"    );
  Htype.push_back( "phill"    );
  Htype.push_back( "njet"     );
  Htype.push_back( "met"      );
  Htype.push_back( "mt"       );
  if(LFVtype==1 || LFVtype==3){
    Htype.push_back( "mu_pt"  );
    Htype.push_back( "mu_eta" );
    Htype.push_back( "mu_phi" );
  }
  if(LFVtype==1 || LFVtype==2){
    Htype.push_back( "el_pt"  );
    Htype.push_back( "el_eta" );
    Htype.push_back( "el_phi" );
  }
  if(LFVtype==2 || LFVtype==3){
    Htype.push_back( "ta_pt"  );
    Htype.push_back( "ta_eta" );
    Htype.push_back( "ta_phi" );
  }
  if(LFVtype==2 && Process=="BkgSM")
    if(!addStatUnc) Htype.push_back( "mllCorr_Orig" );

  for(uint i=0; i<Htype.size(); i++){

    std:: cout << "< CreateSysBands() >:: making Sys Band for"
	       << " distribution = " << Htype.at(i) << std::endl;
    
    if(LFVtype==1 || LFVtype==3){
      MuReco_StatUp    = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_MuReco_StatUp").c_str()  );
      MuReco_SysUp     = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_MuReco_SysUp").c_str()   );
      MuIso_StatUp     = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_MuIso_StatUp").c_str()   );
      MuIso_SysUp      = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_MuIso_SysUp").c_str()    );
      MuTrg_StatUp     = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_MuTrg_StatUp").c_str()   );
      MuTrg_SysUp      = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_MuTrg_SysUp").c_str()    );
      MuTTVA_StatUp    = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_MuTTVA_StatUp").c_str()  );
      MuTTVA_SysUp     = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_MuTTVA_SysUp").c_str()   );
      MuSmeID_SysUp    = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_MuSmeID_SysUp").c_str()  );
      MuSmeMS_SysUp    = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_MuSmeMS_SysUp").c_str()  );
      MuScale_SysUp    = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_MuScale_SysUp").c_str()  );
      MuSagRho_SysUp   = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_MuSagRho_SysUp").c_str() );
      MuSagRes_SysUp   = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_MuSagRes_SysUp").c_str() );
      
      MuReco_StatDown  = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_MuReco_StatDown").c_str()  );
      MuReco_SysDown   = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_MuReco_SysDown").c_str()   ); 
      MuIso_StatDown   = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_MuIso_StatDown").c_str()   ); 
      MuIso_SysDown    = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_MuIso_SysDown").c_str()    );  
      MuTrg_StatDown   = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_MuTrg_StatDown").c_str()   ); 
      MuTrg_SysDown    = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_MuTrg_SysDown").c_str()    );
      MuTTVA_StatDown  = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_MuTTVA_StatDown").c_str()  );
      MuTTVA_SysDown   = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_MuTTVA_SysDown").c_str()   );
      MuSmeID_SysDown  = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_MuSmeID_SysDown").c_str()  );
      MuSmeMS_SysDown  = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_MuSmeMS_SysDown").c_str()  );
      MuScale_SysDown  = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_MuScale_SysDown").c_str()  );
      MuSagRho_SysDown = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_MuSagRho_SysDown").c_str() );
      MuSagRes_SysDown = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_MuSagRes_SysDown").c_str() );
    }
    
    if(LFVtype==1 || LFVtype==2){
      ElReco_SysUp    = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_ElReco_SysUp").c_str()  );
      ElID_SysUp      = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_ElID_SysUp").c_str()    );
      ElIso_SysUp     = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_ElIso_SysUp").c_str()   );
      ElTrg_SysUp     = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_ElTrg_SysUp").c_str()   );
      ElSme_SysUp     = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_ElSme_SysUp").c_str()   );
      ElScale_SysUp   = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_ElScale_SysUp").c_str() );
      
      ElReco_SysDown  = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_ElReco_SysDown").c_str()  );
      ElID_SysDown    = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_ElID_SysDown").c_str()    );
      ElIso_SysDown   = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_ElIso_SysDown").c_str()   );
      ElTrg_SysDown   = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_ElTrg_SysDown").c_str()   );
      ElSme_SysDown   = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_ElSme_SysDown").c_str()   );
      ElScale_SysDown = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_ElScale_SysDown").c_str() );
    }
    
    if(LFVtype==2 || LFVtype==3){
      TaReco_SysUp       = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_TaReco_SysUp").c_str()       );
      TaRecoHpt_SysUp    = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_TaRecoHpt_SysUp").c_str()    );
      TaEleOlr_SysUp     = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_TaEleOlr_SysUp").c_str()     );
      TaJetID_SysUp      = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_TaJetID_SysUp").c_str()      );
      TaJetIDHpt_SysUp   = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_TaJetIDHpt_SysUp").c_str()   );
      TaSme_SysUp        = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_TaSme_SysUp").c_str()        );
      TaSmeDet_SysUp     = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_TaSmeDet_SysUp").c_str()     );
      TaSmeMod_SysUp     = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_TaSmeMod_SysUp").c_str()     );
      
      TaReco_SysDown     = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_TaReco_SysDown").c_str()     );
      TaRecoHpt_SysDown  = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_TaRecoHpt_SysDown").c_str()  );
      TaEleOlr_SysDown   = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_TaEleOlr_SysDown").c_str()   );
      TaJetID_SysDown    = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_TaJetID_SysDown").c_str()    );
      TaJetIDHpt_SysDown = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_TaJetIDHpt_SysDown").c_str() );
      TaSme_SysDown      = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_TaSme_SysDown").c_str()      );
      TaSmeDet_SysDown   = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_TaSmeDet_SysDown").c_str()   );
      TaSmeMod_SysDown   = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_TaSmeMod_SysDown").c_str()   );
    }
    
    JtUncNP1_SysUp   = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_JtUncNP1_SysUp").c_str()       );
    JtUncNP2_SysUp   = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_JtUncNP2_SysUp").c_str()       );
    JtUncNP3_SysUp   = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_JtUncNP3_SysUp").c_str()       );
    JtUncETA_SysUp   = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_JtUncETA_SysUp").c_str()       );
    JtJvtSF_SysUp    = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_JtJvtSF_SysUp").c_str()        );
    MetScl_SysUp     = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_MetScl_SysUp").c_str()         );

    JtUncNP1_SysDown   = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_JtUncNP1_SysDown").c_str()   );
    JtUncNP2_SysDown   = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_JtUncNP2_SysDown").c_str()   );
    JtUncNP3_SysDown   = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_JtUncNP3_SysDown").c_str()   );
    JtUncETA_SysDown   = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_JtUncETA_SysDown").c_str()   );
    JtJvtSF_SysDown    = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_JtJvtSF_SysDown").c_str()    );
    MetScl_SysDown     = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_MetScl_SysDown").c_str()     );

    JtSme_Sys        = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_JtSme_SysUp").c_str()          );
    MetResPara_Sys   = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_MetResPara").c_str()           );
    MetResPer_Sys    = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_MetResPer").c_str()            );

    if(useBjet){
      BtagSF_Beff_SysUp    = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_BtagSF_Beff_SysUp").c_str()    );
      BtagSF_Ceff_SysUp    = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_BtagSF_Ceff_SysUp").c_str()    );
      BtagSF_Leff_SysUp    = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_BtagSF_Leff_SysUp").c_str()    );
      BtagSF_ExtCeff_SysUp = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_BtagSF_ExtCeff_SysUp").c_str() );
      BtagSF_ExtEff_SysUp  = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_BtagSF_ExtEff_SysUp").c_str()  );
      
      BtagSF_Beff_SysDown    = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_BtagSF_Beff_SysDown").c_str()    );
      BtagSF_Ceff_SysDown    = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_BtagSF_Ceff_SysDown").c_str()    );
      BtagSF_Leff_SysDown    = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_BtagSF_Leff_SysDown").c_str()    );
      BtagSF_ExtCeff_SysDown = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_BtagSF_ExtCeff_SysDown").c_str() );
      BtagSF_ExtEff_SysDown  = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_BtagSF_ExtEff_SysDown").c_str()  );
    }

    TopScale_SysUp   = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_TopScale_SysUp").c_str() );
    PU_SysUp         = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_PU_SysUp").c_str()       );
    
    TopScale_SysDown = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_TopScale_SysDown").c_str() );
    PU_SysDown       = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_PU_SysDown").c_str()       );
    
    TopFit_Sys       = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_TopFit_Sys").c_str()     );
    PDF_Sys          = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_PDF_Sys").c_str()        );
    
    if(LFVtype==2 || LFVtype==3){
      TauFake_StatUp       = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_TauFake_StatUp").c_str()       );
      TauFake_BDT_SysUp    = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_TauFake_BDT_SysUp").c_str()    );
      TauFake_Comp_SysUp   = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_TauFake_Comp_SysUp").c_str()   );

      TauFake_StatDown     = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_TauFake_StatDown").c_str()     );
      TauFake_BDT_SysDown  = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_TauFake_BDT_SysDown").c_str()  );
      TauFake_Comp_SysDown = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_TauFake_Comp_SysDown").c_str() );
      
      TauFake_CR_Sys       = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_TauFake_CR_Sys").c_str()       );

      Multijet_kMJ_Stat    = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_Multijet_kMJ_Stat").c_str()    );
      if(LFVtype==2)
	Multijet_kMJ_Sys   = (TH1F*)input->Get( (Htype.at(i)+"_PercVar_Multijet_kMJ_Sys").c_str()     );
    }
    /* Retrieving distribution */
    if(addStatUnc) Bkg = (TH1F*)distro->Get( ("h"+Htype.at(i)+"_BkgTot").c_str() );
    
    std::vector<TH1F*> UpVar, DwVar;
    /* filling Up/Down Variations vector */
    if(LFVtype==1 || LFVtype==3){
      UpVar.push_back( MuReco_StatUp  );
      UpVar.push_back( MuReco_SysUp   );
      UpVar.push_back( MuIso_StatUp   );
      UpVar.push_back( MuIso_SysUp    );
      UpVar.push_back( MuTrg_StatUp   );
      UpVar.push_back( MuTrg_SysUp    );
      UpVar.push_back( MuTTVA_StatUp  );
      UpVar.push_back( MuTTVA_SysUp   );
      UpVar.push_back( MuSmeID_SysUp  );
      UpVar.push_back( MuSmeMS_SysUp  );
      UpVar.push_back( MuScale_SysUp  );
      UpVar.push_back( MuSagRho_SysUp );
      UpVar.push_back( MuSagRes_SysUp );
      
      DwVar.push_back( MuReco_StatDown  );
      DwVar.push_back( MuReco_SysDown   );
      DwVar.push_back( MuIso_StatDown   );
      DwVar.push_back( MuIso_SysDown    );
      DwVar.push_back( MuTrg_StatDown   );
      DwVar.push_back( MuTrg_SysDown    );
      DwVar.push_back( MuTTVA_StatDown  );
      DwVar.push_back( MuTTVA_SysDown   );
      DwVar.push_back( MuSmeID_SysDown  );
      DwVar.push_back( MuSmeMS_SysDown  );
      DwVar.push_back( MuScale_SysDown  );
      DwVar.push_back( MuSagRho_SysDown );
      DwVar.push_back( MuSagRes_SysDown );
    }
    if(LFVtype==1 || LFVtype==2){
      UpVar.push_back( ElReco_SysUp  );
      UpVar.push_back( ElID_SysUp    );
      UpVar.push_back( ElIso_SysUp   );
      UpVar.push_back( ElTrg_SysUp   );
      UpVar.push_back( ElSme_SysUp   );
      UpVar.push_back( ElScale_SysUp );
      
      DwVar.push_back( ElReco_SysDown  );
      DwVar.push_back( ElID_SysDown    );
      DwVar.push_back( ElIso_SysDown   );
      DwVar.push_back( ElTrg_SysDown   );
      DwVar.push_back( ElSme_SysDown   );
      DwVar.push_back( ElScale_SysDown );
    }
    if(LFVtype==2 || LFVtype==3){
      UpVar.push_back( TaReco_SysUp     );
      UpVar.push_back( TaRecoHpt_SysUp  );
      UpVar.push_back( TaEleOlr_SysUp   );
      UpVar.push_back( TaJetID_SysUp    );
      UpVar.push_back( TaJetIDHpt_SysUp );
      UpVar.push_back( TaSme_SysUp      );
      UpVar.push_back( TaSmeDet_SysUp   );
      UpVar.push_back( TaSmeMod_SysUp   );
      
      DwVar.push_back( TaReco_SysDown     );
      DwVar.push_back( TaRecoHpt_SysDown  );
      DwVar.push_back( TaEleOlr_SysDown   );
      DwVar.push_back( TaJetID_SysDown    );
      DwVar.push_back( TaJetIDHpt_SysDown );
      DwVar.push_back( TaSme_SysDown      );
      DwVar.push_back( TaSmeDet_SysDown   );
      DwVar.push_back( TaSmeMod_SysDown   );
    }
    UpVar.push_back( JtSme_Sys      );
    UpVar.push_back( JtUncNP1_SysUp );
    UpVar.push_back( JtUncNP2_SysUp );
    UpVar.push_back( JtUncNP3_SysUp );
    UpVar.push_back( JtUncETA_SysUp );
    UpVar.push_back( JtJvtSF_SysUp  );
    UpVar.push_back( MetResPara_Sys );
    UpVar.push_back( MetResPer_Sys  );
    UpVar.push_back( MetScl_SysUp   );

    DwVar.push_back( JtSme_Sys        );
    DwVar.push_back( JtUncNP1_SysDown );
    DwVar.push_back( JtUncNP2_SysDown );
    DwVar.push_back( JtUncNP3_SysDown );
    DwVar.push_back( JtUncETA_SysDown );
    DwVar.push_back( JtJvtSF_SysDown  );
    DwVar.push_back( MetResPara_Sys   );
    DwVar.push_back( MetResPer_Sys    );
    DwVar.push_back( MetScl_SysDown   );
    
    if(useBjet){
      UpVar.push_back( BtagSF_Beff_SysUp    );
      UpVar.push_back( BtagSF_Ceff_SysUp    );
      UpVar.push_back( BtagSF_Leff_SysUp    );
      UpVar.push_back( BtagSF_ExtCeff_SysUp );
      UpVar.push_back( BtagSF_ExtEff_SysUp  );
      
      DwVar.push_back( BtagSF_Beff_SysDown    );
      DwVar.push_back( BtagSF_Ceff_SysDown    );
      DwVar.push_back( BtagSF_Leff_SysDown    );
      DwVar.push_back( BtagSF_ExtCeff_SysDown );
      DwVar.push_back( BtagSF_ExtEff_SysDown  );
    }

    UpVar.push_back( TopFit_Sys     );
    if(LFVtype==2)
      UpVar.push_back( TopScale_SysDown );
    else
      UpVar.push_back( TopScale_SysUp );
    UpVar.push_back( PDF_Sys        );
    UpVar.push_back( PU_SysUp       );
    
    DwVar.push_back( TopFit_Sys       );
    DwVar.push_back( TopScale_SysDown );
    DwVar.push_back( PDF_Sys          );
    UpVar.push_back( PU_SysDown       );

    if(LFVtype==2 || LFVtype==3){
      UpVar.push_back( TauFake_StatUp     );
      UpVar.push_back( TauFake_BDT_SysUp  );
      UpVar.push_back( TauFake_CR_Sys     );
      UpVar.push_back( TauFake_Comp_SysUp );
      UpVar.push_back( Multijet_kMJ_Stat  );
      if(LFVtype==2)
	UpVar.push_back( Multijet_kMJ_Sys );
      
      DwVar.push_back( TauFake_StatDown     );
      DwVar.push_back( TauFake_BDT_SysDown  );
      DwVar.push_back( TauFake_CR_Sys       );
      DwVar.push_back( TauFake_Comp_SysDown );
      DwVar.push_back( Multijet_kMJ_Stat    );
      if(LFVtype==2)
	DwVar.push_back( Multijet_kMJ_Sys   );
    }

    int Bins = UpVar.at(0)->GetNbinsX();

    if(m_debug){
      std::cout	<< "< CreatSysBands() > :: Distribution = " << Htype.at(i)
		<< " -> Bins = " << Bins << std::endl;
      std::cout << "< CreateSysBands() >::       UpVar size = " << UpVar.size()
		<< " DownVar size = " << DwVar.size() << std::endl;
    }
    
    int Ups = (int)UpVar.size();
    int Dws = (int)DwVar.size();
    std::vector<double> UpVal2, DwVal2;
    std::vector<double> UpVal, DwVal;
    std::vector<double> XVal, XWid;
    
    /* Making +=N^2 */
    if(m_debug)
      std::cout << "< CreatSysBands() > ::       Making +=N^2 ... " << std::endl;
    for(int b=1; b<Bins+1; b++){

      if(m_debug)
	std::cout << "< CreatSysBands() > ::       Proceessing Bin " << b << std::endl;
      
      double val =0;
      for(int u=0; u<Ups; u++){
	val += pow( UpVar.at(u)->GetBinContent(b),2 );
	if(m_debug)
	  std::cout << "< CreatSysBands() > ::       Up VarIndex = " << u
		    << " Up Val (%) = " << UpVar.at(u)->GetBinContent(b)
		    << " +=N^2 = " << val << std::endl;
      }
      if(UpVar.at(0)->GetBinContent(b)!=0)
	val += pow( Lvar,2 );
      if(addStatUnc){
	if(Bkg->GetBinContent(b)!=0)
	  val += pow( (Bkg->GetBinError(b)/Bkg->GetBinContent(b))*100,2 );
      }
      UpVal2.push_back(val);
      val=0;
      for(int d=0; d<Dws; d++){
	val += pow( DwVar.at(d)->GetBinContent(b),2 );
	if(m_debug)
	  std::cout << "< CreatSysBands() > ::       Dw VarIndex = " << d
		    << " Dw Val (%) = " << DwVar.at(d)->GetBinContent(b)
		    << " +=N^2 = " << val << std::endl;
      }
      if(UpVar.at(0)->GetBinContent(b)!=0)
	val += pow( Lvar,2 );
      if(addStatUnc){
	if(Bkg->GetBinContent(b)!=0)
	  val += pow( (Bkg->GetBinError(b)/Bkg->GetBinContent(b))*100,2 );
      }
      DwVal2.push_back( val );
      XVal.push_back( DwVar.at(0)->GetBinCenter(b) );
      XWid.push_back( DwVar.at(0)->GetBinWidth(b) );
    }
  
    /* Making sqrt( +=N^2 ) */
    if(m_debug)
      std::cout << "< CreatSysBands() > ::       Making sqrt(+=N^2) ... " << std::endl;

    for(int uu=0; uu<(int)UpVal2.size(); uu++){
      UpVal.push_back( sqrt(UpVal2.at(uu)) );
    }
    for(int dd=0; dd<(int)DwVal2.size(); dd++){
      DwVal.push_back( sqrt(DwVal2.at(dd)) );
    }
    
    /* Creating Band */
    if(m_debug)
      std::cout << "< CreatSysBands() > ::       Making sys band ... " << std::endl;
    
    Int_t N=Bins;
    Double_t xVal[N], yVal[N];
    Double_t xErr[N], yErrU[N], yErrD[N];
    
    for(int p=1; p<N+1; p++){
      xVal[p-1]  = XVal.at(p-1);
      yVal[p-1]  = 1;
      xErr[p-1]  = XWid.at(p-1)/2;
      yErrU[p-1] =  UpVal.at(p-1)/100;
      yErrD[p-1] =  DwVal.at(p-1)/100;
      
      if(m_debug)
	  std::cout << "< CreatSysBands() > ::       Point = " << p-1
		    << " xVal = " << xVal[p-1]
		    << " upVal (UpVal/100) = " << yErrU[p-1] << " ("
		    << UpVal.at(p-1)/100 << ")" << " downVal (DwVal/100)= "
		    << yErrD[p-1] << " (" << DwVal.at(p-1)/100 << std::endl;
    }

    TGraphAsymmErrors *band = new TGraphAsymmErrors(N, xVal, yVal,
						    xErr, xErr,
						    yErrD, yErrU);
    band->GetXaxis()->SetTitle(UpVar.at(0)->GetXaxis()->GetTitle());
    out->cd();
    band->Write( ("h"+Htype.at(i)+"_SystBand").c_str() );

    if(Htype.at(i)=="mllCorr" || Htype.at(i)=="mll"){

      if(m_debug)
	std::cout << "< CreatSysBands() > ::       Making mllSysUP and "
		  << "mllSysDown bands" << std::endl;
      
      TH1F* mll_up = (TH1F*)UpVar.at(0)->Clone( (Htype.at(i)+"Syst_Up").c_str() );
      mll_up->Reset();
      TH1F* mll_dw = (TH1F*)UpVar.at(0)->Clone( (Htype.at(i)+"Syst_Down").c_str() );
      mll_dw->Reset();
      for(int p=1; p<N+1; p++){
	mll_up->SetBinContent(p, UpVal.at(p-1) );
	mll_dw->SetBinContent(p, DwVal.at(p-1) );
      }
      std::cout<<"Writing mllSysUP and Down band"<<std::endl;
      mll_up->Write( (Htype.at(i)+"_SysUp").c_str() );
      mll_dw->Write( (Htype.at(i)+"_SysDown").c_str() );
      mll_up->Delete();
      mll_dw->Delete();
    }
    /* cleaning */
    if(LFVtype==1 || LFVtype==3){
      MuReco_StatUp->Delete();
      MuReco_SysUp->Delete();
      MuIso_StatUp->Delete();
      MuIso_SysUp->Delete();
      MuTrg_StatUp->Delete();
      MuTrg_SysUp->Delete();
      MuSmeID_SysUp->Delete();
      MuSmeMS_SysUp->Delete();
      MuScale_SysUp->Delete();
      MuReco_StatDown->Delete();
      MuReco_SysDown->Delete();
      MuIso_StatDown->Delete();
      MuIso_SysDown->Delete();
      MuTrg_StatDown->Delete();
      MuTrg_SysDown->Delete();
      MuSmeID_SysDown->Delete();
      MuSmeMS_SysDown->Delete();
      MuScale_SysDown->Delete();
    }
    if(LFVtype==1 || LFVtype==2){
      ElReco_SysUp->Delete();
      ElID_SysUp->Delete();
      ElIso_SysUp->Delete();
      ElTrg_SysUp->Delete();
      ElSme_SysUp->Delete();
      ElScale_SysUp->Delete();
      ElReco_SysDown->Delete();
      ElID_SysDown->Delete();
      ElIso_SysDown->Delete();
      ElTrg_SysDown->Delete();
      ElSme_SysDown->Delete();
      ElScale_SysDown->Delete();
    }
    if(LFVtype==2 || LFVtype==3){
      TaReco_SysUp->Delete();
      TaRecoHpt_SysUp->Delete();
      TaEleOlr_SysUp->Delete();
      TaJetID_SysUp->Delete();
      TaJetIDHpt_SysUp->Delete();
      TaSme_SysUp->Delete();
      TaSmeDet_SysUp->Delete();
      TaSmeMod_SysUp->Delete();
      TaReco_SysDown->Delete();
      TaRecoHpt_SysDown->Delete();
      TaEleOlr_SysDown->Delete();
      TaJetID_SysDown->Delete();
      TaJetIDHpt_SysDown->Delete();
      TaSme_SysDown->Delete();
      TaSmeDet_SysDown->Delete();
      TaSmeMod_SysDown->Delete();;
    }
    JtUncNP1_SysUp->Delete();	
    JtUncNP2_SysUp->Delete();	
    JtUncNP3_SysUp->Delete();
    JtUncETA_SysUp->Delete();
    MetScl_SysUp->Delete();
    JtUncNP1_SysDown->Delete();
    JtUncNP2_SysDown->Delete();
    JtUncNP3_SysDown->Delete();
    JtUncETA_SysDown->Delete();
    MetScl_SysDown->Delete();
    if(useBjet){
      BtagSF_Beff_SysUp->Delete();
      BtagSF_Ceff_SysUp->Delete();
      BtagSF_Leff_SysUp->Delete();
      BtagSF_ExtCeff_SysUp->Delete();
      BtagSF_ExtEff_SysUp->Delete();
      BtagSF_Beff_SysDown->Delete();
      BtagSF_Ceff_SysDown->Delete();
      BtagSF_Leff_SysDown->Delete();
      BtagSF_ExtCeff_SysDown->Delete();
      BtagSF_ExtEff_SysDown->Delete();
    }
    TopScale_SysUp->Delete();
    PU_SysUp->Delete();

    TopScale_SysDown->Delete();
    PU_SysDown->Delete();
    
    TopFit_Sys->Delete();
    PDF_Sys->Delete();
    JtSme_Sys->Delete();
    MetResPer_Sys->Delete();
    MetResPara_Sys->Delete();
    
    if(LFVtype==2 || LFVtype==3){
      TauFake_StatUp->Delete();
      TauFake_BDT_SysUp->Delete();

      TauFake_StatDown->Delete();
      TauFake_BDT_SysDown->Delete();
      TauFake_CR_Sys->Delete();
    }
    if(addStatUnc)
      Bkg->Delete();
  }
  /* closing */
  out->Close();
  input->Close();
  if(addStatUnc)
    distro->Close();
  
}

void CreateSysBands(bool useBjet, bool isBlind, bool isttCR, bool isSherpa){

  SetATLASStyle();
  TH1::SetDefaultSumw2(kTRUE);

  std::string lfvType = "emu";

  std::cout << " Making Sys Bands for " << lfvType
	    << " Channel and Multijet Background" << std::endl;

  std::string Dir = "";
  if(useBjet){  Dir += "Bjet/";   }
  else{         Dir += "NoBjet/"; }

  if(isttCR)    {
    Dir += "ttbarCR";
    if(isSherpa) Dir += "_Sherpa";
    Dir += "/";
  }

   /* Define Lumi Var */
  double Lvar = 3.2;

  /* Loading files */
  std::string InName  = Dir+"PercentVariations_"+lfvType;
  std::string OutName = Dir+"SystematicsBands_"+lfvType;
  if(isBlind){
    InName  += "_Blind";
    OutName += "_Blind";
  }
  InName  += "_Multijet";
  OutName += "_Multijet";

  TFile *input = new TFile( (InName+".root").c_str() );
  TFile *out   = new TFile( (OutName+".root").c_str(), "RECREATE" );

  /* Sys */
  TH1F *mT  = (TH1F*)input->Get( "mllCorr_PercVar_mT"      );
  TH1F *met = (TH1F*)input->Get( "mllCorr_PercVar_met"     );
  TH1F *mcP = (TH1F*)input->Get( "mllCorr_PercVar_MCplus"  );
  TH1F *mcM = (TH1F*)input->Get( "mllCorr_PercVar_MCminus" );
  TH1F *jet = (TH1F*)input->Get( "mllCorr_PercVar_jetsys"  );

  std:: cout << "< CreateSysBands() >:: making Sys Band for"
	     << " distribution = mllCorr" << std::endl;

  std::vector<TH1F*> UpVar, DwVar;
  UpVar.push_back( mT  );  DwVar.push_back( mT  );
  UpVar.push_back( met );  DwVar.push_back( met );
  UpVar.push_back( mcP );  DwVar.push_back( mcP );
  UpVar.push_back( mcM );  DwVar.push_back( mcM );
  UpVar.push_back( jet );  DwVar.push_back( jet );

  int Bins = UpVar.at(0)->GetNbinsX();

  if(m_debug){
    std::cout << "< CreatSysBands() > :: Distribution = mllCorr"
	      << " -> Bins = " << Bins << std::endl;
    std::cout << "< CreateSysBands() >::       UpVar size = " << UpVar.size()
	      << " DownVar size = " << DwVar.size() << std::endl;
  }

  int Ups = (int)UpVar.size();
  int Dws = (int)DwVar.size();
  std::vector<double> UpVal2, DwVal2;
  std::vector<double> UpVal, DwVal;
  std::vector<double> XVal, XWid;

  /* Making +=N^2 */
  if(m_debug)
    std::cout << "< CreatSysBands() > ::       Making +=N^2 ... " << std::endl;

  for(int b=1; b<Bins+1; b++){
    
    if(m_debug)
      std::cout << "< CreatSysBands() > ::       Proceessing Bin " << b << std::endl;
    
    double val =0;
    for(int u=0; u<Ups; u++){
      val += pow(UpVar.at(u)->GetBinContent(b),2);
      if(m_debug)
	std::cout << "< CreatSysBands() > ::       Up VarIndex = " << u
		  << " Up Val (%) = " << UpVar.at(u)->GetBinContent(b)
		  << " +=N^2 = " << val << std::endl;
    }
    if(UpVar.at(0)->GetBinContent(b)!=0)
      val += pow(Lvar,2);
    UpVal2.push_back(val);
    val=0;
    for(int d=0; d<Dws; d++){
      val += pow(DwVar.at(d)->GetBinContent(b),2);
      if(m_debug)
	std::cout << "< CreatSysBands() > ::       Dw VarIndex = " << d
		  << " Dw Val (%) = " << DwVar.at(d)->GetBinContent(b)
		  << " +=N^2 = " << val << std::endl;
    }
    if(UpVar.at(0)->GetBinContent(b)!=0)
      val += pow(Lvar,2);
    DwVal2.push_back( val );
    XVal.push_back( DwVar.at(0)->GetBinCenter(b) );
    XWid.push_back( DwVar.at(0)->GetBinWidth(b) );
  }
  
  /* Making sqrt( +=N^2 ) */
  if(m_debug)
    std::cout << "< CreatSysBands() > ::       Making sqrt(+=N^2) ... " << std::endl;

  for(int uu=0; uu<(int)UpVal2.size(); uu++){
    UpVal.push_back( sqrt(UpVal2.at(uu)) );
  }
  for(int dd=0; dd<(int)DwVal2.size(); dd++){
    DwVal.push_back( sqrt(DwVal2.at(dd)) );
  }
  
  /* Creating Band */
  if(m_debug)
    std::cout << "< CreatSysBands() > ::       Making sys band ... " << std::endl;
  
  Int_t N=Bins;
  Double_t xVal[N], yVal[N];
  Double_t xErr[N], yErrU[N], yErrD[N];
  
  for(int p=1; p<N+1; p++){
    xVal[p-1]  = XVal.at(p-1);
    yVal[p-1]  = 1;
    xErr[p-1]  = XWid.at(p-1)/2;
    yErrU[p-1] =  UpVal.at(p-1)/100;
    yErrD[p-1] =  DwVal.at(p-1)/100;
    
    if(m_debug)
      std::cout << "< CreatSysBands() > ::       Point = " << p-1
		<< " xVal = " << xVal[p-1]
		<< " upVal (UpVal/100) = " << yErrU[p-1] << " ("
		<< UpVal.at(p-1)/100 << ")" << " downVal (DwVal/100)= "
		<< yErrD[p-1] << " (" << DwVal.at(p-1)/100 << std::endl;
  }
  
  TGraphAsymmErrors *band = new TGraphAsymmErrors(N, xVal, yVal,
						  xErr, xErr,
						  yErrD, yErrU);
  band->GetXaxis()->SetTitle(UpVar.at(0)->GetXaxis()->GetTitle());
  out->cd();
  band->Write( "hmllCorr_SystBand" );
  
  if(m_debug)
    std::cout << "< CreatSysBands() > ::       Making mllSysUP and "
	      << "mllSysDown bands" << std::endl;
  
  TH1F* mll_up = (TH1F*)UpVar.at(0)->Clone( "mllCorrSyst_Up" );
  mll_up->Reset();
  TH1F* mll_dw = (TH1F*)UpVar.at(0)->Clone( "mllCorrSyst_Down" );
  mll_dw->Reset();
  for(int p=1; p<N+1; p++){
    mll_up->SetBinContent(p, UpVal.at(p-1) );
    mll_dw->SetBinContent(p, DwVal.at(p-1) );
  }
  std::cout<<"Writing mllSysUP and Down band"<<std::endl;
  mll_up->Write( "mllCorr_SysUp"   );
  mll_dw->Write( "mllCorr_SysDown" );
  mll_up->Delete();
  mll_dw->Delete();

  /* cleaning */
  mT  -> Delete();
  met -> Delete();
  mcP -> Delete();
  mcM -> Delete();
  jet -> Delete();
  
  /* closing */
  out->Close();
  input->Close();
  
}
