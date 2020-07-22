/* program includes */
#include "MakeSystPlots.h"
#include "Utils.C"

int main( int argc, char* argv[] ) {

  int lfvType        = -1;
  std::string Htype  = "mllCorr";
  std::string sysVar = "";
  bool useBjet       = false;
  bool isBlind       = false;
  bool useGUI        = false;
  bool useOrig       = false;
  bool useAllSys     = false;
  bool printHelp     = false;
  for(int i = 1; i < argc; ++i){
    if( !strcmp(argv[i],"--lfvType")        ){ lfvType   = std::stoi(argv[i+1]); }
    else if( !strcmp(argv[i],"--Htype")     ){ Htype     = argv[i+1]; }
    else if( !strcmp(argv[i],"--sysVar")    ){ sysVar    = argv[i+1]; }
    else if( !strcmp(argv[i],"--isBlind")   ){ isBlind   = true; }
    else if( !strcmp(argv[i],"--useBjet")   ){ useBjet   = true; }
    else if( !strcmp(argv[i],"--useAllSys") ){ useAllSys = true; }
    else if( !strcmp(argv[i],"--useGUI")    ){ useGUI    = true; }
    else if( !strcmp(argv[i],"--useOrig")   ){ useOrig   = true; }
    else if( !strcmp(argv[i],"--help")      ){ printHelp = true; }
    else{
      if(std::string(argv[i]).find("--")!=std::string::npos)
	std::cout << "WARNING:: Option " << argv[i] << " not recognized: "
		  << "skipping!" << std::endl;
    }
  }
  if(printHelp){
    std::cout << " MakeSystPlots: make syst. uncert. plots!"   << std::endl;
    std::cout << "                Options: "                   << std::endl;
    std::cout << "                --useBjet [Enable b-jet veto:"
	      << " default is 'false'] "                       << std::endl;
    std::cout << "                --isBlind [Enable Blind analysis:"
	      << " default is 'false'] "                       << std::endl;
    std::cout << "                --useGUI  [Enable GUI mode:"
	      << " default is 'false'] "                       << std::endl;
    std::cout << "                --useOrig [Use Original distros:"
	      << " default is 'false'] "                       << std::endl;
    std::cout << "                --Htype   [Choose distribution: "
	      << " default is 'mllCorr']"                      << std::endl;
    std::cout << "                --sysVar  [Choose sysVar: "
	      << " default is '']"                             << std::endl;
    std::cout << "                --lfvType [Choose lfv channel: "
	      << " options 1,2,3']"                            << std::endl;
    std::cout << "                --useAllSys [Use BDT/Comp sys:"
	      << " default is 'false'] "                       << std::endl;
    std::cout << "                --help    [Print this help]" << std::endl;
    exit(0);
  }

  if(lfvType==-1){
    std::cout << "< MakeSystPlots() >:: lfvType not set!"
	      << " Possible options: 1,2,3" << std::endl;
    exit(0);
  }

  std::cout << "< MakeSystPlots() >:: Options set " << std::endl;
  std::cout << "                       useBjet   = " << useBjet   << std::endl;
  std::cout << "                       lfvType   = " << lfvType   << std::endl;
  std::cout << "                       isBlind   = " << isBlind   << std::endl;
  std::cout << "                       Htype     = " << Htype     << std::endl;
  std::cout << "                       sysVar    = " << sysVar    << std::endl;
  std::cout << "                       useGUI    = " << useGUI    << std::endl;
  std::cout << "                       useAllSys = " << useAllSys << std::endl;
  std::cout << "                       useOrig   = " << useOrig   << std::endl;

  TRint *myApp = new TRint("RootSession",&argc,argv,NULL,0);
  if(sysVar=="")
    MakeSystPlots(lfvType, Htype, useBjet, isBlind, useOrig, useAllSys);
  else
    CompareProcSys(lfvType, Htype, sysVar, useBjet, isBlind);
  
  if(useGUI){
    std::cout << "< MakeSystPlots() >:: using Rint -> ROOT will remain "
	      << "opened ... " << std::endl;
    myApp->Run();
  }

  return 0;
  
}

void SetLegendStyle(TLegend *leg){

  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  
}

void SetHistoOption(TH1F *h){

  h->GetYaxis()->SetTitle("Systematic Uncertanty [%]");
  h->GetYaxis()->SetTitleOffset(1.65);
  h->GetXaxis()->SetMoreLogLabels(kTRUE);
  h->GetXaxis()->SetNoExponent(kTRUE);
  h->GetYaxis()->SetMoreLogLabels(kTRUE);
  h->GetYaxis()->SetNoExponent(kTRUE);
  h->GetYaxis()->CenterTitle(kTRUE);
  h->GetYaxis()->SetRangeUser(0.01,100000);
  h->GetXaxis()->SetRangeUser(100,7000);
  h->SetLineWidth(2);
  
}

void MakeSystPlots(int LFVtype, std::string Htype, bool useBjet,
		   bool isBlind, bool useOrig, bool useAllSys){
  
  SetATLASStyle();
  TH1::SetDefaultSumw2(kTRUE);

  std::string lfvType = "";
  if(LFVtype==1)      { lfvType="emu";   }
  else if(LFVtype==2) { lfvType="etau";  }
  else if(LFVtype==3) { lfvType="mutau"; }

  std::cout << "Drawing Systematic Variations for Channel "
	    << lfvType << std::endl;	    
  
  std::string Dir = "";
  if(useBjet){ Dir = "Bjet/";   }
  else       { Dir = "NoBjet/"; }

  std::string fName = Dir+"PercentVariations_"+lfvType;
  if(isBlind)
    fName += "_Blind";
  
  if(useOrig && LFVtype==2)
    Htype = "mllCorr_Orig";
  
  TFile *input = new TFile( (fName+".root").c_str() );
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
  TH1F *JtSme_SysUp          = NULL;	 TH1F *JtSme_SysDown          = NULL;
  TH1F *JtUncNP1_SysUp       = NULL;	 TH1F *JtUncNP1_SysDown       = NULL;
  TH1F *JtUncNP2_SysUp       = NULL;	 TH1F *JtUncNP2_SysDown       = NULL;
  TH1F *JtUncNP3_SysUp       = NULL;	 TH1F *JtUncNP3_SysDown       = NULL;
  TH1F *JtUncETA_SysUp       = NULL;	 TH1F *JtUncETA_SysDown       = NULL;
  TH1F *JtJvtSF_SysUp        = NULL;     TH1F *JtJvtSF_SysDown        = NULL;
  TH1F *MetResPer_SysUp      = NULL;     TH1F *MetResPer_SysDown      = NULL;
  TH1F *MetResPara_SysUp     = NULL;     TH1F *MetResPara_SysDown     = NULL;
  TH1F *MetScl_SysUp         = NULL;     TH1F *MetScl_SysDown         = NULL;
  TH1F *TopFit_SysUp         = NULL;     TH1F *TopFit_SysDown         = NULL;
  TH1F *TopScale_SysUp       = NULL;     TH1F *TopScale_SysDown       = NULL;
  TH1F *PDF_SysUp            = NULL;     TH1F *PDF_SysDown            = NULL;
  TH1F *TauFake_BDT_SysUp    = NULL;     TH1F *TauFake_BDT_SysDown    = NULL;
  TH1F *TauFake_StatUp       = NULL;     TH1F *TauFake_StatDown       = NULL;
  TH1F *TauFake_CR_Sys       = NULL;
  TH1F *TauFake_Comp_SysUp   = NULL;     TH1F *TauFake_Comp_SysDown   = NULL;
  TH1F *PU_SysUp             = NULL;     TH1F *PU_SysDown             = NULL;
  TH1F *Multijet_kMJ_Stat    = NULL;     TH1F *Multijet_kMJ_Sys       = NULL;
  TH1F *TauFake_SysUp        = NULL;     TH1F *TauFake_SysDown        = NULL;
  
  /* Retrieving Plots */
  if(LFVtype==1 || LFVtype==3){
    MuReco_StatUp   = (TH1F*)input->Get( (Htype+"_PercVar_MuReco_StatUp").c_str()  );
    MuReco_SysUp    = (TH1F*)input->Get( (Htype+"_PercVar_MuReco_SysUp").c_str()   );
    MuIso_StatUp    = (TH1F*)input->Get( (Htype+"_PercVar_MuIso_StatUp").c_str()   );
    MuIso_SysUp     = (TH1F*)input->Get( (Htype+"_PercVar_MuIso_SysUp").c_str()    );
    MuTrg_StatUp    = (TH1F*)input->Get( (Htype+"_PercVar_MuTrg_StatUp").c_str()   );
    MuTrg_SysUp     = (TH1F*)input->Get( (Htype+"_PercVar_MuTrg_SysUp").c_str()    );
    MuTTVA_StatUp   = (TH1F*)input->Get( (Htype+"_PercVar_MuTTVA_StatUp").c_str()  );
    MuTTVA_SysUp    = (TH1F*)input->Get( (Htype+"_PercVar_MuTTVA_SysUp").c_str()   );
    MuSmeID_SysUp   = (TH1F*)input->Get( (Htype+"_PercVar_MuSmeID_SysUp").c_str()  );
    MuSmeMS_SysUp   = (TH1F*)input->Get( (Htype+"_PercVar_MuSmeMS_SysUp").c_str()  );
    MuScale_SysUp   = (TH1F*)input->Get( (Htype+"_PercVar_MuScale_SysUp").c_str()  );
    MuSagRho_SysUp  = (TH1F*)input->Get( (Htype+"_PercVar_MuSagRho_SysUp").c_str() );
    MuSagRes_SysUp  = (TH1F*)input->Get( (Htype+"_PercVar_MuSagRes_SysUp").c_str() );
    
    MuReco_StatDown  = (TH1F*)input->Get( (Htype+"_PercVar_MuReco_StatDown").c_str()  );
    MuReco_SysDown   = (TH1F*)input->Get( (Htype+"_PercVar_MuReco_SysDown").c_str()   ); 
    MuIso_StatDown   = (TH1F*)input->Get( (Htype+"_PercVar_MuIso_StatDown").c_str()   ); 
    MuIso_SysDown    = (TH1F*)input->Get( (Htype+"_PercVar_MuIso_SysDown").c_str()    );  
    MuTrg_StatDown   = (TH1F*)input->Get( (Htype+"_PercVar_MuTrg_StatDown").c_str()   ); 
    MuTrg_SysDown    = (TH1F*)input->Get( (Htype+"_PercVar_MuTrg_SysDown").c_str()    );
    MuTTVA_StatDown  = (TH1F*)input->Get( (Htype+"_PercVar_MuTTVA_StatDown").c_str()  );
    MuTTVA_SysDown   = (TH1F*)input->Get( (Htype+"_PercVar_MuTTVA_SysDown").c_str()   );
    MuSmeID_SysDown  = (TH1F*)input->Get( (Htype+"_PercVar_MuSmeID_SysDown").c_str()  );
    MuSmeMS_SysDown  = (TH1F*)input->Get( (Htype+"_PercVar_MuSmeMS_SysDown").c_str()  );
    MuScale_SysDown  = (TH1F*)input->Get( (Htype+"_PercVar_MuScale_SysDown").c_str()  );
    MuSagRho_SysDown = (TH1F*)input->Get( (Htype+"_PercVar_MuSagRho_SysDown").c_str() );
    MuSagRes_SysDown = (TH1F*)input->Get( (Htype+"_PercVar_MuSagRes_SysDown").c_str() );
  }
  if(LFVtype==1 || LFVtype==2){
    ElReco_SysUp    = (TH1F*)input->Get( (Htype+"_PercVar_ElReco_SysUp").c_str()  );
    ElID_SysUp      = (TH1F*)input->Get( (Htype+"_PercVar_ElID_SysUp").c_str()    );
    ElIso_SysUp     = (TH1F*)input->Get( (Htype+"_PercVar_ElIso_SysUp").c_str()   );
    ElTrg_SysUp     = (TH1F*)input->Get( (Htype+"_PercVar_ElTrg_SysUp").c_str()   );
    ElSme_SysUp     = (TH1F*)input->Get( (Htype+"_PercVar_ElSme_SysUp").c_str()   );
    ElScale_SysUp   = (TH1F*)input->Get( (Htype+"_PercVar_ElScale_SysUp").c_str() );

    ElReco_SysDown  = (TH1F*)input->Get( (Htype+"_PercVar_ElReco_SysDown").c_str()  );
    ElID_SysDown    = (TH1F*)input->Get( (Htype+"_PercVar_ElID_SysDown").c_str()    );
    ElIso_SysDown   = (TH1F*)input->Get( (Htype+"_PercVar_ElIso_SysDown").c_str()   );
    ElTrg_SysDown   = (TH1F*)input->Get( (Htype+"_PercVar_ElTrg_SysDown").c_str()   );
    ElSme_SysDown   = (TH1F*)input->Get( (Htype+"_PercVar_ElSme_SysDown").c_str()   );
    ElScale_SysDown = (TH1F*)input->Get( (Htype+"_PercVar_ElScale_SysDown").c_str() );
  }
  if(LFVtype==2 || LFVtype==3){
    TaReco_SysUp       = (TH1F*)input->Get( (Htype+"_PercVar_TaReco_SysUp").c_str()       );
    TaRecoHpt_SysUp    = (TH1F*)input->Get( (Htype+"_PercVar_TaRecoHpt_SysUp").c_str()    );
    TaEleOlr_SysUp     = (TH1F*)input->Get( (Htype+"_PercVar_TaEleOlr_SysUp").c_str()     );
    TaJetID_SysUp      = (TH1F*)input->Get( (Htype+"_PercVar_TaJetID_SysUp").c_str()      );
    TaJetIDHpt_SysUp   = (TH1F*)input->Get( (Htype+"_PercVar_TaJetIDHpt_SysUp").c_str()   );
    TaSme_SysUp        = (TH1F*)input->Get( (Htype+"_PercVar_TaSme_SysUp").c_str()        );
    TaSmeDet_SysUp     = (TH1F*)input->Get( (Htype+"_PercVar_TaSmeDet_SysUp").c_str()     );
    TaSmeMod_SysUp     = (TH1F*)input->Get( (Htype+"_PercVar_TaSmeMod_SysUp").c_str()     );
    
    TaReco_SysDown     = (TH1F*)input->Get( (Htype+"_PercVar_TaReco_SysDown").c_str()     );
    TaRecoHpt_SysDown  = (TH1F*)input->Get( (Htype+"_PercVar_TaRecoHpt_SysDown").c_str()  );
    TaEleOlr_SysDown   = (TH1F*)input->Get( (Htype+"_PercVar_TaEleOlr_SysDown").c_str()   );
    TaJetID_SysDown    = (TH1F*)input->Get( (Htype+"_PercVar_TaJetID_SysDown").c_str()    );
    TaJetIDHpt_SysDown = (TH1F*)input->Get( (Htype+"_PercVar_TaJetIDHpt_SysDown").c_str() );
    TaSme_SysDown      = (TH1F*)input->Get( (Htype+"_PercVar_TaSme_SysDown").c_str()      );
    TaSmeDet_SysDown   = (TH1F*)input->Get( (Htype+"_PercVar_TaSmeDet_SysDown").c_str()   );
    TaSmeMod_SysDown   = (TH1F*)input->Get( (Htype+"_PercVar_TaSmeMod_SysDown").c_str()   );
  }
  if(useBjet){
    BtagSF_Beff_SysUp    = (TH1F*)input->Get( (Htype+"_PercVar_BtagSF_Beff_SysUp").c_str()    );
    BtagSF_Ceff_SysUp    = (TH1F*)input->Get( (Htype+"_PercVar_BtagSF_Ceff_SysUp").c_str()    );
    BtagSF_Leff_SysUp    = (TH1F*)input->Get( (Htype+"_PercVar_BtagSF_Leff_SysUp").c_str()    );
    BtagSF_ExtCeff_SysUp = (TH1F*)input->Get( (Htype+"_PercVar_BtagSF_ExtCeff_SysUp").c_str() );
    BtagSF_ExtEff_SysUp  = (TH1F*)input->Get( (Htype+"_PercVar_BtagSF_ExtEff_SysUp").c_str()  );

    BtagSF_Beff_SysDown    = (TH1F*)input->Get( (Htype+"_PercVar_BtagSF_Beff_SysDown").c_str()    );
    BtagSF_Ceff_SysDown    = (TH1F*)input->Get( (Htype+"_PercVar_BtagSF_Ceff_SysDown").c_str()    );
    BtagSF_Leff_SysDown    = (TH1F*)input->Get( (Htype+"_PercVar_BtagSF_Leff_SysDown").c_str()    );
    BtagSF_ExtCeff_SysDown = (TH1F*)input->Get( (Htype+"_PercVar_BtagSF_ExtCeff_SysDown").c_str() );
    BtagSF_ExtEff_SysDown  = (TH1F*)input->Get( (Htype+"_PercVar_BtagSF_ExtEff_SysDown").c_str()  );
  }

  JtSme_SysUp      = (TH1F*)input->Get( (Htype+"_PercVar_JtSme_SysUp").c_str()    );
  JtUncNP1_SysUp   = (TH1F*)input->Get( (Htype+"_PercVar_JtUncNP1_SysUp").c_str() );
  JtUncNP2_SysUp   = (TH1F*)input->Get( (Htype+"_PercVar_JtUncNP2_SysUp").c_str() );
  JtUncNP3_SysUp   = (TH1F*)input->Get( (Htype+"_PercVar_JtUncNP3_SysUp").c_str() );
  JtUncETA_SysUp   = (TH1F*)input->Get( (Htype+"_PercVar_JtUncETA_SysUp").c_str() );
  JtJvtSF_SysUp    = (TH1F*)input->Get( (Htype+"_PercVar_JtJvtSF_SysUp").c_str()  );
  MetResPara_SysUp = (TH1F*)input->Get( (Htype+"_PercVar_MetResPara").c_str()     );
  MetResPer_SysUp  = (TH1F*)input->Get( (Htype+"_PercVar_MetResPer").c_str()      );
  MetScl_SysUp     = (TH1F*)input->Get( (Htype+"_PercVar_MetScl_SysUp").c_str()   );

  JtSme_SysDown      = (TH1F*)input->Get( (Htype+"_PercVar_JtSme_SysUp").c_str()    );
  JtUncNP1_SysDown   = (TH1F*)input->Get( (Htype+"_PercVar_JtUncNP1_SysDown").c_str() );
  JtUncNP2_SysDown   = (TH1F*)input->Get( (Htype+"_PercVar_JtUncNP2_SysDown").c_str() );
  JtUncNP3_SysDown   = (TH1F*)input->Get( (Htype+"_PercVar_JtUncNP3_SysDown").c_str() );
  JtUncETA_SysDown   = (TH1F*)input->Get( (Htype+"_PercVar_JtUncETA_SysDown").c_str() );
  JtJvtSF_SysDown    = (TH1F*)input->Get( (Htype+"_PercVar_JtJvtSF_SysDown").c_str()  );
  MetResPara_SysDown = (TH1F*)input->Get( (Htype+"_PercVar_MetResPara").c_str()       );
  MetResPer_SysDown  = (TH1F*)input->Get( (Htype+"_PercVar_MetResPer").c_str()        );
  MetScl_SysDown     = (TH1F*)input->Get( (Htype+"_PercVar_MetScl_SysDown").c_str()   );

  TopFit_SysUp     = (TH1F*)input->Get( (Htype+"_PercVar_TopFit_Sys").c_str()     );
  TopScale_SysUp   = (TH1F*)input->Get( (Htype+"_PercVar_TopScale_SysUp").c_str() );
  PDF_SysUp        = (TH1F*)input->Get( (Htype+"_PercVar_PDF_Sys").c_str()        );
  PU_SysUp         = (TH1F*)input->Get( (Htype+"_PercVar_PU_SysUp").c_str()       );
  
  TopFit_SysDown   = (TH1F*)input->Get( (Htype+"_PercVar_TopFit_Sys").c_str()       );
  TopScale_SysDown = (TH1F*)input->Get( (Htype+"_PercVar_TopScale_SysDown").c_str() );
  PDF_SysDown      = (TH1F*)input->Get( (Htype+"_PercVar_PDF_Sys").c_str()          );
  PU_SysDown       = (TH1F*)input->Get( (Htype+"_PercVar_PU_SysDown").c_str()       );

  if(LFVtype==2 || LFVtype==3){
    TauFake_StatUp       = (TH1F*)input->Get( (Htype+"_PercVar_TauFake_StatUp").c_str()       );
    TauFake_StatDown     = (TH1F*)input->Get( (Htype+"_PercVar_TauFake_StatDown").c_str()     );
    TauFake_BDT_SysUp    = (TH1F*)input->Get( (Htype+"_PercVar_TauFake_BDT_SysUp").c_str()    );
    TauFake_BDT_SysDown  = (TH1F*)input->Get( (Htype+"_PercVar_TauFake_BDT_SysDown").c_str()  );
    TauFake_CR_Sys       = (TH1F*)input->Get( (Htype+"_PercVar_TauFake_CR_Sys").c_str()       );
    TauFake_Comp_SysUp   = (TH1F*)input->Get( (Htype+"_PercVar_TauFake_Comp_SysUp").c_str()   );
    TauFake_Comp_SysDown = (TH1F*)input->Get( (Htype+"_PercVar_TauFake_Comp_SysDown").c_str() );
    Multijet_kMJ_Stat    = (TH1F*)input->Get( (Htype+"_PercVar_Multijet_kMJ_Stat").c_str()    );
    if(LFVtype==2)
      Multijet_kMJ_Sys   = (TH1F*)input->Get( (Htype+"_PercVar_Multijet_kMJ_Sys").c_str()     );
    
    TauFake_SysUp        = (TH1F*)input->Get( (Htype+"_PercVar_TauFake_SysUp").c_str()        );
    TauFake_SysDown      = (TH1F*)input->Get( (Htype+"_PercVar_TauFake_SysDown").c_str()      );
  }
    
  std::vector<TH1F*> MuonUp, ElecUp, TauUp, JetUp, MetUp, TopUp;
  std::vector<TH1F*> MuonDw, ElecDw, TauDw, JetDw, MetDw, TopDw;
  std::vector<int>   MuonCol, MuonLin, ElecCol, ElecLin;
  std::vector<int>   TauCol,  TauLin,  JetCol,  JetLin;
  std::vector<int>   MetCol,  MetLin,  TopCol,  TopLin;
  std::vector<std::string> MuonNm, ElecNm, TauNm, JetNm, MetNm, TopNm;

  /* Muon */
  if(LFVtype==1 || LFVtype==3){
    MuonUp.push_back( MuReco_StatUp  ); MuonDw.push_back( MuReco_StatDown );
    MuonUp.push_back( MuReco_SysUp   );	MuonDw.push_back( MuReco_SysDown   );
    MuonUp.push_back( MuIso_StatUp   );	MuonDw.push_back( MuIso_StatDown   );
    MuonUp.push_back( MuIso_SysUp    );	MuonDw.push_back( MuIso_SysDown    );
    MuonUp.push_back( MuTrg_StatUp   );	MuonDw.push_back( MuTrg_StatDown   );
    MuonUp.push_back( MuTrg_SysUp    );	MuonDw.push_back( MuTrg_SysDown    );
    MuonUp.push_back( MuTTVA_StatUp  );	MuonDw.push_back( MuTTVA_StatDown  );
    MuonUp.push_back( MuTTVA_SysUp   );	MuonDw.push_back( MuTTVA_SysDown   );
    MuonUp.push_back( MuSmeID_SysUp  );	MuonDw.push_back( MuSmeID_SysDown  );
    MuonUp.push_back( MuSmeMS_SysUp  );	MuonDw.push_back( MuSmeMS_SysDown  );
    MuonUp.push_back( MuScale_SysUp  );	MuonDw.push_back( MuScale_SysDown  );
    MuonUp.push_back( MuSagRho_SysUp ); MuonDw.push_back( MuSagRho_SysDown );
    MuonUp.push_back( MuSagRes_SysUp ); MuonDw.push_back( MuSagRes_SysDown );
      
    MuonNm.push_back( "MuReco_Stat"  );
    MuonNm.push_back( "MuReco_Sys"   );
    MuonNm.push_back( "MuIso_Stat"   );
    MuonNm.push_back( "MuIso_Sys"    );
    MuonNm.push_back( "MuTrg_Stat"   );
    MuonNm.push_back( "MuTrg_Sys"    );
    MuonNm.push_back( "MuTTVA_Stat"  );
    MuonNm.push_back( "MuTTVA_Sys"   );
    
    MuonNm.push_back( "MuSmeID_Sys"  );
    MuonNm.push_back( "MuSmeMS_Sys"  );
    MuonNm.push_back( "MuScale_Sys"  );
    MuonNm.push_back( "MuSagRho_Sys" );
    MuonNm.push_back( "MuSagRes_Sys" );
    
    MuonCol.push_back( kOrange-7 );  MuonLin.push_back( 1 );
    MuonCol.push_back( kBlack    );  MuonLin.push_back( 9 );
    MuonCol.push_back( kGreen+1  );  MuonLin.push_back( 4 );
    MuonCol.push_back( kRed      );  MuonLin.push_back( 2 );
    MuonCol.push_back( kGray+1   );  MuonLin.push_back( 3 );
    MuonCol.push_back( kBlue     );  MuonLin.push_back( 8 );
    MuonCol.push_back( kCyan     );  MuonLin.push_back( 7 );
    MuonCol.push_back( kMagenta  );  MuonLin.push_back( 5 );
    MuonCol.push_back( kOrange   );  MuonLin.push_back( 1 );
    MuonCol.push_back( kCyan     );  MuonLin.push_back( 8 );
    MuonCol.push_back( kGreen+1  );  MuonLin.push_back( 7 );
    MuonCol.push_back( kRed      );  MuonLin.push_back( 6 );
    MuonCol.push_back( kBlue     );  MuonLin.push_back( 2 );
  }

  /* Electron */
  if(LFVtype==1 || LFVtype==2){
    ElecUp.push_back( ElReco_SysUp  );   ElecDw.push_back( ElReco_SysDown  );
    ElecUp.push_back( ElID_SysUp    );	 ElecDw.push_back( ElID_SysDown    );
    ElecUp.push_back( ElIso_SysUp   );	 ElecDw.push_back( ElIso_SysDown   );
    ElecUp.push_back( ElTrg_SysUp   );	 ElecDw.push_back( ElTrg_SysDown   );
    ElecUp.push_back( ElSme_SysUp   );	 ElecDw.push_back( ElSme_SysDown   );
    ElecUp.push_back( ElScale_SysUp );	 ElecDw.push_back( ElScale_SysDown );

    ElecNm.push_back( "ElReco_Sys"  );
    ElecNm.push_back( "ElID_Sys"    );
    ElecNm.push_back( "ElIso_Sys"   );
    ElecNm.push_back( "ElTrg_Sys"   );
    ElecNm.push_back( "ElSme_Sys"   );
    ElecNm.push_back( "ElScale_Sys" );

    ElecCol.push_back( kBlack   );   ElecLin.push_back( 1 );
    ElecCol.push_back( kMagenta );   ElecLin.push_back( 7 );
    ElecCol.push_back( kRed     );   ElecLin.push_back( 8 );
    ElecCol.push_back( kBlue    );   ElecLin.push_back( 9 );
    ElecCol.push_back( kOrange  );   ElecLin.push_back( 1 );
    ElecCol.push_back( kGreen+1 );   ElecLin.push_back( 7 );
  }

  /* Taus */
  if(LFVtype==2 || LFVtype==3){
    TauUp.push_back( TaReco_SysUp       );   TauDw.push_back( TaReco_SysDown       );
    TauUp.push_back( TaRecoHpt_SysUp    );   TauDw.push_back( TaRecoHpt_SysDown    );
    TauUp.push_back( TaEleOlr_SysUp     );   TauDw.push_back( TaEleOlr_SysDown     );
    TauUp.push_back( TaJetID_SysUp      );   TauDw.push_back( TaJetID_SysDown      );
    TauUp.push_back( TaJetIDHpt_SysUp   );   TauDw.push_back( TaJetIDHpt_SysDown   );
    TauUp.push_back( TaSme_SysUp        );   TauDw.push_back( TaSme_SysDown        );
    TauUp.push_back( TaSmeDet_SysUp     );   TauDw.push_back( TaSmeDet_SysDown     );
    TauUp.push_back( TaSmeMod_SysUp     );   TauDw.push_back( TaSmeMod_SysDown     );
    
    TauUp.push_back( TauFake_StatUp     );   TauDw.push_back( TauFake_StatDown     );
    TauUp.push_back( TauFake_CR_Sys     );   TauDw.push_back( TauFake_CR_Sys       );
    if(useAllSys){
      TauUp.push_back( TauFake_BDT_SysUp  );   TauDw.push_back( TauFake_BDT_SysDown  );
      TauUp.push_back( TauFake_Comp_SysUp );   TauDw.push_back( TauFake_Comp_SysDown );
    }
    TauUp.push_back( TauFake_SysUp );        TauDw.push_back( TauFake_SysDown );
    TauUp.push_back( Multijet_kMJ_Stat  );   TauDw.push_back( Multijet_kMJ_Stat    );
    if(LFVtype==2){
      TauUp.push_back( Multijet_kMJ_Sys );   TauDw.push_back( Multijet_kMJ_Sys     );
    }

    TauNm.push_back( "TaReco_Sys"        );
    TauNm.push_back( "TaRecoHpt_Sys"     );
    TauNm.push_back( "TaEleOlr_Sys"      );
    TauNm.push_back( "TaJetID_Sys"       );
    TauNm.push_back( "TaJetIDHpt_Sys"    );
    TauNm.push_back( "TaSme_Sys"         );
    TauNm.push_back( "TaSmeDet_Sys"      );
    TauNm.push_back( "TaSmeMod_Sys"      );
    
    TauNm.push_back( "TaFake_Stat"       );
    TauNm.push_back( "TaFake_CR_Sys"     );
    if(useAllSys){
      TauNm.push_back( "TaFake_BDT_Sys"  );
      TauNm.push_back( "TaFake_Comp_Sys" );
    }
    TauNm.push_back( "TaFake_Sys"        );
    TauNm.push_back( "Multijet_kMJ_Stat" );
    if(LFVtype==2)
      TauNm.push_back( "Multijet_kMJ_Sys" );

    TauCol.push_back( kOrange-7 );  TauLin.push_back( 1 );
    TauCol.push_back( kBlack    );  TauLin.push_back( 9 );
    TauCol.push_back( kGreen+1  );  TauLin.push_back( 4 );
    TauCol.push_back( kRed      );  TauLin.push_back( 2 );
    TauCol.push_back( kGray+1   );  TauLin.push_back( 3 );

    TauCol.push_back( kBlue     );  TauLin.push_back( 9 );
    TauCol.push_back( kCyan     );  TauLin.push_back( 1 );
    TauCol.push_back( kBlack    );  TauLin.push_back( 4 );
    TauCol.push_back( kOrange-7 );  TauLin.push_back( 9 );
    TauCol.push_back( kRed      );  TauLin.push_back( 2 );
    if(useAllSys){
      TauCol.push_back( kMagenta );  TauLin.push_back( 7 );
      TauCol.push_back( kGray+1  );  TauLin.push_back( 7 );
    }
    TauCol.push_back( kCyan+2   );  TauLin.push_back( 3 );
    TauCol.push_back( kGreen+1  );  TauLin.push_back( 5 );
    if(LFVtype==2){
      TauCol.push_back( kOrange-3 );  TauLin.push_back( 8 );
    }
  }

  /* Jets */
  JetUp.push_back( JtSme_SysUp    );  JetDw.push_back( JtSme_SysDown    );
  JetUp.push_back( JtUncNP1_SysUp );  JetDw.push_back( JtUncNP1_SysDown );
  JetUp.push_back( JtUncNP2_SysUp );  JetDw.push_back( JtUncNP2_SysDown );
  JetUp.push_back( JtUncNP3_SysUp );  JetDw.push_back( JtUncNP3_SysDown );
  JetUp.push_back( JtUncETA_SysUp );  JetDw.push_back( JtUncETA_SysDown );
  JetUp.push_back( JtJvtSF_SysUp  );  JetDw.push_back( JtJvtSF_SysDown  );

  JetNm.push_back( "JtSme_Sys"    );
  JetNm.push_back( "JtUncNP1_Sys" );
  JetNm.push_back( "JtUncNP2_Sys" );
  JetNm.push_back( "JtUncNP3_Sys" );
  JetNm.push_back( "JtUncETA_Sys" );
  JetNm.push_back( "JtJvtSF_Sys"  );
  
  if(useBjet){
    JetUp.push_back( BtagSF_Beff_SysUp    );  JetDw.push_back( BtagSF_Beff_SysDown    );
    JetUp.push_back( BtagSF_Ceff_SysUp    );  JetDw.push_back( BtagSF_Ceff_SysDown    );
    JetUp.push_back( BtagSF_Leff_SysUp    );  JetDw.push_back( BtagSF_Leff_SysDown    );
    JetUp.push_back( BtagSF_ExtCeff_SysUp );  JetDw.push_back( BtagSF_ExtCeff_SysDown );
    JetUp.push_back( BtagSF_ExtEff_SysUp  );  JetDw.push_back( BtagSF_ExtEff_SysDown  );
    
    JetNm.push_back( "BtagSF_Beff_Sys"    );
    JetNm.push_back( "BtagSF_Ceff_Sys"    );
    JetNm.push_back( "BtagSF_Leff_Sys"    );
    JetNm.push_back( "BtagSF_ExtCeff_Sys" );
    JetNm.push_back( "BtagSF_ExtEff_Sys"  );
  }
   
  JetCol.push_back( kBlack   );  JetLin.push_back( 1 );
  JetCol.push_back( kRed     );  JetLin.push_back( 8 );
  JetCol.push_back( kBlue    );  JetLin.push_back( 7 );
  JetCol.push_back( kCyan    );  JetLin.push_back( 3 );
  JetCol.push_back( kGreen+1 );  JetLin.push_back( 2 );
  
  JetCol.push_back( kGreen+1 );  JetLin.push_back( 1 );
  JetCol.push_back( kBlue    );  JetLin.push_back( 8 );
  JetCol.push_back( kMagenta );  JetLin.push_back( 7 );
  JetCol.push_back( kRed     );  JetLin.push_back( 3 );
  JetCol.push_back( kOrange  );  JetLin.push_back( 2 );
  JetCol.push_back( kBlack   );  JetLin.push_back( 5 );

  /* MET */
  MetUp.push_back( MetResPara_SysUp );  MetDw.push_back( MetResPara_SysDown );
  MetUp.push_back( MetResPer_SysUp  );  MetDw.push_back( MetResPer_SysDown  );
  MetUp.push_back( MetScl_SysUp     );  MetDw.push_back( MetScl_SysDown     );

  MetNm.push_back( "MetResPara_Sys" );
  MetNm.push_back( "MetResPer_Sys"  );
  MetNm.push_back( "MetScl_Sys"     );

  MetCol.push_back( kBlack   );  MetLin.push_back( 1 );
  MetCol.push_back( kRed     );  MetLin.push_back( 8 );
  MetCol.push_back( kBlue    );  MetLin.push_back( 7 );

  /* Top */
  TopUp.push_back( TopFit_SysUp   );  TopDw.push_back( TopFit_SysDown   );
  if(LFVtype==2){
    TopUp.push_back( TopScale_SysDown );  TopDw.push_back( TopScale_SysDown );
  }
  else{
    TopUp.push_back( TopScale_SysUp );  TopDw.push_back( TopScale_SysDown );
  }
  TopUp.push_back( PDF_SysUp      );  TopDw.push_back( PDF_SysDown      );
  TopUp.push_back( PU_SysUp       );  TopDw.push_back( PU_SysDown       );

  TopNm.push_back( "TopFit_Sys"   );
  TopNm.push_back( "TopScale_Sys" );
  TopNm.push_back( "PDF_Sys"      );
  TopNm.push_back( "PU_Sys"       );

  TopCol.push_back( kBlack   );  TopLin.push_back( 1 );
  TopCol.push_back( kRed     );  TopLin.push_back( 8 );
  TopCol.push_back( kBlue    );  TopLin.push_back( 7 );
  TopCol.push_back( kGreen+1 );  TopLin.push_back( 5 );
  
  
  TCanvas *MuSFUP=NULL, *MuSFDW=NULL, *MuSHUP=NULL, *MuSHDW=NULL;
  TCanvas *ElSFUP=NULL, *ElSFDW=NULL, *ElSHUP=NULL, *ElSHDW=NULL;
  TCanvas *TaSFUP=NULL, *TaSFDW=NULL, *TaSHUP=NULL, *TaSHDW=NULL;
  TCanvas *JtSFUP=NULL, *JtSFDW=NULL, *JtSHUP=NULL, *JtSHDW=NULL;
  TCanvas *MetUP =NULL, *MetDW =NULL, *TopUP =NULL, *TopDW =NULL;

  TLegend *L_MuSFUP=NULL, *L_MuSFDW=NULL, *L_MuSHUP=NULL, *L_MuSHDW=NULL;
  TLegend *L_ElSFUP=NULL, *L_ElSFDW=NULL, *L_ElSHUP=NULL, *L_ElSHDW=NULL;
  TLegend *L_TaSFUP=NULL, *L_TaSFDW=NULL, *L_TaSHUP=NULL, *L_TaSHDW=NULL;
  TLegend *L_JtSFUP=NULL, *L_JtSFDW=NULL, *L_JtSHUP=NULL, *L_JtSHDW=NULL;
  TLegend *L_MetUP =NULL, *L_MetDW =NULL, *L_TopUP =NULL, *L_TopDW =NULL;

  if(LFVtype==1 || LFVtype==3){
    MuSFUP = new TCanvas("MuSFUP","MuSFUP",0,0,600,600);
    MuSFDW = new TCanvas("MuSFDW","MuSFDW",0,0,600,600);
    MuSHUP = new TCanvas("MuSHUP","MuSHUP",0,0,600,600);
    MuSHDW = new TCanvas("MuSHDW","MuSHDW",0,0,600,600);
    L_MuSFUP  = new TLegend(0.57,0.53,0.95,0.93);
    L_MuSFDW  = new TLegend(0.57,0.53,0.95,0.93);
    L_MuSHUP  = new TLegend(0.17,0.49,0.61,0.77);
    L_MuSHDW  = new TLegend(0.17,0.49,0.61,0.77);
  }
  if(LFVtype==1 || LFVtype==2){
    ElSFUP = new TCanvas("ElSFUP","ElSFUP",0,0,600,600);
    ElSFDW = new TCanvas("ElSFDW","ElSFDW",0,0,600,600);
    ElSHUP = new TCanvas("ElSHUP","ElSHUP",0,0,600,600); 
    ElSHDW = new TCanvas("ElSHDW","ElSHDW",0,0,600,600);
    if(useBjet){
      L_ElSFUP  = new TLegend(0.19,0.54,0.54,0.75);
      L_ElSFDW  = new TLegend(0.19,0.54,0.54,0.75);
    }
    else{
      L_ElSFUP  = new TLegend(0.59,0.70,0.94,0.91);
      L_ElSFDW  = new TLegend(0.59,0.70,0.94,0.91);
    }
    L_ElSHUP  = new TLegend(0.17,0.61,0.56,0.74);
    L_ElSHDW  = new TLegend(0.17,0.61,0.56,0.74);
  }
  if(LFVtype==2 || LFVtype==3){
    TaSFUP = new TCanvas("TaSFUP","TaSFUP",0,0,600,600);
    TaSFDW = new TCanvas("TaSFDW","TaSFDW",0,0,600,600);
    TaSHUP = new TCanvas("TaSHUP","TaSHUP",0,0,600,600); 
    TaSHDW = new TCanvas("TaSHDW","TaSHDW",0,0,600,600);
    L_TaSFUP  = new TLegend(0.18,0.54,0.62,0.75);
    L_TaSFDW  = new TLegend(0.18,0.54,0.62,0.75);
    L_TaSHUP  = new TLegend(0.57,0.63,0.99,0.91);
    L_TaSHDW  = new TLegend(0.57,0.63,0.99,0.91);
  }

  JtSFUP = new TCanvas("JtSFUP","JtSFUP",0,0,600,600);
  JtSFDW = new TCanvas("JtSFDW","JtSFDW",0,0,600,600);
  JtSHUP = new TCanvas("JtSHUP","JtSHUP",0,0,600,600);
  JtSHDW = new TCanvas("JtSHDW","JtSHDW",0,0,600,600);
  L_JtSFUP  = new TLegend(0.16,0.49,0.63,0.77);
  L_JtSFDW  = new TLegend(0.16,0.49,0.63,0.77);
  L_JtSHUP  = new TLegend(0.18,0.51,0.62,0.76);
  L_JtSHDW  = new TLegend(0.18,0.51,0.62,0.76);

  MetUP = new TCanvas("MetUP","MetUP",0,0,600,600);
  MetDW = new TCanvas("MetDW","MetDW",0,0,600,600);
  TopUP = new TCanvas("TopUP","TopUP",0,0,600,600);
  TopDW = new TCanvas("TopDW","TopDW",0,0,600,600);
  L_MetUP  = new TLegend(0.17,0.57,0.61,0.78);
  L_MetDW  = new TLegend(0.17,0.57,0.61,0.78);
  L_TopUP  = new TLegend(0.17,0.57,0.61,0.78);
  L_TopDW  = new TLegend(0.17,0.57,0.61,0.78);

  std::string Suffix = "";
  if(useBjet){ Suffix += "_bjetVeto"; }
  Suffix += ".pdf";
  
  /* Muon SF Up and Down */
  if(LFVtype==1 || LFVtype==3){
    
    std::cout << "< MakeSystPlots() > :: Drawing Muon Sys Up ... " << std::endl;
    SetLegendStyle(L_MuSFUP);
    SetLegendStyle(L_MuSHUP);
    for(uint h=0; h<MuonUp.size(); h++){
      MuonUp.at(h)->SetLineColor(MuonCol.at(h));
      MuonUp.at(h)->SetLineStyle(MuonLin.at(h));
      SetHistoOption( MuonUp.at(h) );
      if(h<8){
	MuSFUP->cd();
	MuSFUP->SetLogy(true);
	MuSFUP->SetLogx(true);
	MuonUp.at(h)->Draw("same");
	L_MuSFUP->AddEntry( MuonUp.at(h),
			    (MuonNm.at(h)+"Up").c_str(),"l" );
      }
      else{
	MuSHUP->cd();
	MuSHUP->SetLogy(true);
	MuSHUP->SetLogx(true);
	MuonUp.at(h)->Draw("same");
	L_MuSHUP->AddEntry( MuonUp.at(h),
			    (MuonNm.at(h)+"Up").c_str(),"l" );
      }
    }
    MuSFUP->cd(); L_MuSFUP->Draw(); DrawLabels(false,false,false,false,false,false,true);
    MuSHUP->cd(); L_MuSHUP->Draw(); DrawLabels(false,false,false,false,false,false,true);
    MuSFUP->SaveAs( ("Plots/Sys/MuonSF_SysUp_"+lfvType+Suffix).c_str() );
    MuSHUP->SaveAs( ("Plots/Sys/MuonSH_SysUp_"+lfvType+Suffix).c_str() );

    std::cout << "< MakeSystPlots() > :: Drawing Muon Sys Down ... " << std::endl;
    SetLegendStyle(L_MuSFDW);
    SetLegendStyle(L_MuSHDW);
    for(uint h=0; h<MuonDw.size(); h++){
      MuonDw.at(h)->SetLineColor(MuonCol.at(h));
      MuonDw.at(h)->SetLineStyle(MuonLin.at(h));
      SetHistoOption( MuonDw.at(h) );
      if(h<8){
	MuSFDW->cd();
	MuSFDW->SetLogy(true);
	MuSFDW->SetLogx(true);
	MuonDw.at(h)->Draw("same");
	L_MuSFDW->AddEntry( MuonDw.at(h),
			    (MuonNm.at(h)+"Down").c_str(),"l" );
      }
      else{
	MuSHDW->cd();
	MuSHDW->SetLogy(true);
	MuSHDW->SetLogx(true);
	MuonDw.at(h)->Draw("same");
	L_MuSHDW->AddEntry( MuonDw.at(h),
			    (MuonNm.at(h)+"Down").c_str(),"l" );
      }
    }
    MuSFDW->cd(); L_MuSFDW->Draw(); DrawLabels(false,false,false,false,false,false,true);
    MuSHDW->cd(); L_MuSHDW->Draw(); DrawLabels(false,false,false,false,false,false,true);
    MuSFDW->SaveAs( ("Plots/Sys/MuonSF_SysDown_"+lfvType+Suffix).c_str() );
    MuSHDW->SaveAs( ("Plots/Sys/MuonSH_SysDown_"+lfvType+Suffix).c_str() );
  }
  
  /* Electron SF Up and Down */
  if(LFVtype==1 || LFVtype==2){

    std::cout << "< MakeSystPlots() > :: Drawing Elec Sys Up ... " << std::endl;
    SetLegendStyle(L_ElSFUP);
    SetLegendStyle(L_ElSHUP);
    for(uint h=0; h<ElecUp.size(); h++){
      ElecUp.at(h)->SetLineColor(ElecCol.at(h));
      ElecUp.at(h)->SetLineStyle(ElecLin.at(h));
      SetHistoOption( ElecUp.at(h) );
      if(h<4){
	ElSFUP->cd();
	ElSFUP->SetLogy(true);
	ElSFUP->SetLogx(true);
	ElecUp.at(h)->Draw("same");
	L_ElSFUP->AddEntry( ElecUp.at(h),
			    (ElecNm.at(h)+"Up").c_str(),"l" );
      }
      else{
	ElSHUP->cd();
	ElSHUP->SetLogy(true);
	ElSHUP->SetLogx(true);
	ElecUp.at(h)->Draw("same");
	L_ElSHUP->AddEntry( ElecUp.at(h),
			    (ElecNm.at(h)+"Up").c_str(),"l" );
      }
    }
    ElSFUP->cd(); L_ElSFUP->Draw(); DrawLabels(false,false,false,false,false,false,true);
    ElSHUP->cd(); L_ElSHUP->Draw(); DrawLabels(false,false,false,false,false,false,true);
    ElSFUP->SaveAs( ("Plots/Sys/ElecSF_SysUp_"+lfvType+Suffix).c_str() );
    ElSHUP->SaveAs( ("Plots/Sys/ElecSH_SysUp_"+lfvType+Suffix).c_str() );

    std::cout << "< MakeSystPlots() > :: Drawing Elec Sys Down ... " << std::endl;
    SetLegendStyle(L_ElSFDW);
    SetLegendStyle(L_ElSHDW);
    for(uint h=0; h<ElecDw.size(); h++){
      ElecDw.at(h)->SetLineColor(ElecCol.at(h));
      ElecDw.at(h)->SetLineStyle(ElecLin.at(h));
      SetHistoOption( ElecDw.at(h) );
      if(h<4){
	ElSFDW->cd();
	ElSFDW->SetLogy(true);
	ElSFDW->SetLogx(true);
	ElecDw.at(h)->Draw("same");
	L_ElSFDW->AddEntry( ElecDw.at(h),
			    (ElecNm.at(h)+"Down").c_str(),"l" );
      }
      else{
	ElSHDW->cd();
	ElSHDW->SetLogy(true);
	ElSHDW->SetLogx(true);
	ElecDw.at(h)->Draw("same");
	L_ElSHDW->AddEntry( ElecDw.at(h),
			    (ElecNm.at(h)+"Down").c_str(),"l" );
      }
    }
    ElSFDW->cd(); L_ElSFDW->Draw(); DrawLabels(false,false,false,false,false,false,true);
    ElSHDW->cd(); L_ElSHDW->Draw(); DrawLabels(false,false,false,false,false,false,true);
    ElSFDW->SaveAs( ("Plots/Sys/ElecSF_SysDown_"+lfvType+Suffix).c_str() );
    ElSHDW->SaveAs( ("Plots/Sys/ElecSH_SysDown_"+lfvType+Suffix).c_str() );
  }

  /* Tau SF Up and Down */
  if(LFVtype==2 || LFVtype==3){

    std::cout << "< MakeSystPlots() > :: Drawing Tau Sys Up ... " << std::endl;
    SetLegendStyle(L_TaSFUP);
    SetLegendStyle(L_TaSHUP);
    for(uint h=0; h<TauUp.size(); h++){
      std::cout <<" h = "<< h<<" name = "<< TauNm.at(h) << std::endl;
      TauUp.at(h)->SetLineColor(TauCol.at(h));
      TauUp.at(h)->SetLineStyle(TauLin.at(h));
      SetHistoOption( TauUp.at(h) );
      if(h<5){
	TaSFUP->cd();
	TaSFUP->SetLogy(true);
	TaSFUP->SetLogx(true);
	TauUp.at(h)->Draw("same");
	L_TaSFUP->AddEntry( TauUp.at(h),
			    (TauNm.at(h)+"Up").c_str(),"l" );
      }
      else{
	TaSHUP->cd();
	TaSHUP->SetLogy(true);
	TaSHUP->SetLogx(true);
	TauUp.at(h)->Draw("same");
	L_TaSHUP->AddEntry( TauUp.at(h),
			    (TauNm.at(h)+"Up").c_str(),"l" );
      }
    }
    TaSFUP->cd(); L_TaSFUP->Draw(); DrawLabels(false,false,false,false,false,false,true);
    TaSHUP->cd(); L_TaSHUP->Draw(); DrawLabels(false,false,false,false,false,false,true);
    TaSFUP->SaveAs( ("Plots/Sys/TauSF_SysUp_"+lfvType+Suffix).c_str() );
    TaSHUP->SaveAs( ("Plots/Sys/TauSH_SysUp_"+lfvType+Suffix).c_str() );

    std::cout << "< MakeSystPlots() > :: Drawing Tau Sys Down ... " << std::endl;
    SetLegendStyle(L_TaSFDW);
    SetLegendStyle(L_TaSHDW);
    for(uint h=0; h<TauDw.size(); h++){
      TauDw.at(h)->SetLineColor(TauCol.at(h));
      TauDw.at(h)->SetLineStyle(TauLin.at(h));
      SetHistoOption( TauDw.at(h) );
      if(h<5){
	TaSFDW->cd();
	TaSFDW->SetLogy(true);
	TaSFDW->SetLogx(true);
	TauDw.at(h)->Draw("same");
	L_TaSFDW->AddEntry( TauDw.at(h),
			    (TauNm.at(h)+"Down").c_str(),"l" );
      }
      else{
	TaSHDW->cd();
	TaSHDW->SetLogy(true);
	TaSHDW->SetLogx(true);
	TauDw.at(h)->Draw("same");
	L_TaSHDW->AddEntry( TauDw.at(h),
			    (TauNm.at(h)+"Down").c_str(),"l" );
      }
    }
    TaSFDW->cd(); L_TaSFDW->Draw(); DrawLabels(false,false,false,false,false,false,true);
    TaSHDW->cd(); L_TaSHDW->Draw(); DrawLabels(false,false,false,false,false,false,true);
    TaSFDW->SaveAs( ("Plots/Sys/TauSF_SysDown_"+lfvType+Suffix).c_str() );
    TaSHDW->SaveAs( ("Plots/Sys/TauSH_SysDown_"+lfvType+Suffix).c_str() );
  }
  
  /* Jet SF Up and Down */
  std::cout << "< MakeSystPlots() > :: Drawing Jet Sys Up ... " << std::endl;
  SetLegendStyle(L_JtSFUP);
  SetLegendStyle(L_JtSHUP);
  for(uint h=0; h<JetUp.size(); h++){
    JetUp.at(h)->SetLineColor(JetCol.at(h));
    JetUp.at(h)->SetLineStyle(JetLin.at(h));
    SetHistoOption( JetUp.at(h) );
    if(h<5){
      JtSHUP->cd();
      JtSHUP->SetLogy(true);
      JtSHUP->SetLogx(true);
      JetUp.at(h)->Draw("same");
      L_JtSHUP->AddEntry( JetUp.at(h),
  			  (JetNm.at(h)+"Up").c_str(),"l" );
    }
    else{
      JtSFUP->cd();
      JtSFUP->SetLogy(true);
      JtSFUP->SetLogx(true);
      JetUp.at(h)->Draw("same");
      L_JtSFUP->AddEntry( JetUp.at(h),
  			  (JetNm.at(h)+"Up").c_str(),"l" );
    }
  }
  JtSFUP->cd(); L_JtSFUP->Draw(); DrawLabels(false,false,false,false,false,false,true);
  JtSHUP->cd(); L_JtSHUP->Draw(); DrawLabels(false,false,false,false,false,false,true);
  JtSFUP->SaveAs( ("Plots/Sys/JetSF_SysUp_"+lfvType+Suffix).c_str() );
  JtSHUP->SaveAs( ("Plots/Sys/JetSH_SysUp_"+lfvType+Suffix).c_str() );

  std::cout << "< MakeSystPlots() > :: Drawing Jet Sys Down ... " << std::endl;
  SetLegendStyle(L_JtSFDW);
  SetLegendStyle(L_JtSHDW);
  for(uint h=0; h<JetDw.size(); h++){
    JetDw.at(h)->SetLineColor(JetCol.at(h));
    JetDw.at(h)->SetLineStyle(JetLin.at(h));
    SetHistoOption( JetDw.at(h) );
    if(h<5){
      JtSHDW->cd();
      JtSHDW->SetLogy(true);
      JtSHDW->SetLogx(true);
      JetDw.at(h)->Draw("same");
      L_JtSHDW->AddEntry( JetDw.at(h),
			  (JetNm.at(h)+"Down").c_str(),"l" );
    }
    else{
      JtSFDW->cd();
      JtSFDW->SetLogy(true);
      JtSFDW->SetLogx(true);
      JetDw.at(h)->Draw("same");
      L_JtSFDW->AddEntry( JetDw.at(h),
			  (JetNm.at(h)+"Down").c_str(),"l" );
    }
  }
  JtSFDW->cd(); L_JtSFDW->Draw(); DrawLabels(false,false,false,false,false,false,true);
  JtSHDW->cd(); L_JtSHDW->Draw(); DrawLabels(false,false,false,false,false,false,true);
  JtSFDW->SaveAs( ("Plots/Sys/JetSF_SysDown_"+lfvType+Suffix).c_str() );
  JtSHDW->SaveAs( ("Plots/Sys/JetSH_SysDown_"+lfvType+Suffix).c_str() );
  
  /* Met Up and Down */
  std::cout << "< MakeSystPlots() > :: Drawing Met Sys Up ... " << std::endl;
  SetLegendStyle(L_MetUP);
  for(uint h=0; h<MetUp.size(); h++){
    MetUp.at(h)->SetLineColor(MetCol.at(h));
    MetUp.at(h)->SetLineStyle(MetLin.at(h));
    SetHistoOption( MetUp.at(h) );
    MetUP->cd();
    MetUP->SetLogy(true);
    MetUP->SetLogx(true);
    MetUp.at(h)->Draw("same");
    L_MetUP->AddEntry( MetUp.at(h),
		       (MetNm.at(h)+"Up").c_str(),"l" );
  }
  MetUP->cd(); L_MetUP->Draw(); DrawLabels(false,false,false,false,false,false,true);
  MetUP->SaveAs( ("Plots/Sys/Met_SysUp_"+lfvType+Suffix).c_str() );
  
  std::cout << "< MakeSystPlots() > :: Drawing Met Sys Down ... " << std::endl;
  SetLegendStyle(L_MetDW);
  for(uint h=0; h<MetDw.size(); h++){
    MetDw.at(h)->SetLineColor(MetCol.at(h));
    MetDw.at(h)->SetLineStyle(MetLin.at(h));
    SetHistoOption( MetDw.at(h) );
    MetDW->cd();
    MetDW->SetLogy(true);
    MetDW->SetLogx(true);
    MetDw.at(h)->Draw("same");
    L_MetDW->AddEntry( MetDw.at(h),
		       (MetNm.at(h)+"Down").c_str(),"l" );
  }
  MetDW->cd(); L_MetDW->Draw(); DrawLabels(false,false,false,false,false,false,true);
  MetDW->SaveAs( ("Plots/Sys/Met_SysDown_"+lfvType+Suffix).c_str() );

  /* Top Up and Down */
  std::cout << "< MakeSystPlots() > :: Drawing Top Sys Up ... " << std::endl;
  SetLegendStyle(L_TopUP);
  for(uint h=0; h<TopUp.size(); h++){
    TopUp.at(h)->SetLineColor(TopCol.at(h));
    TopUp.at(h)->SetLineStyle(TopLin.at(h));
    SetHistoOption( TopUp.at(h) );
    TopUP->cd();
    TopUP->SetLogy(true);
    TopUP->SetLogx(true);
    TopUp.at(h)->Draw("same");
    L_TopUP->AddEntry( TopUp.at(h),
		       (TopNm.at(h)+"Up").c_str(),"l" );
  }
  TopUP->cd(); L_TopUP->Draw(); DrawLabels(false,false,false,false,false,false,true);
  TopUP->SaveAs( ("Plots/Sys/Top_SysUp_"+lfvType+Suffix).c_str() );
  
  std::cout << "< MakeSystPlots() > :: Drawing Top Sys Down ... " << std::endl;
  SetLegendStyle(L_TopDW);
  for(uint h=0; h<TopDw.size(); h++){
    TopDw.at(h)->SetLineColor(TopCol.at(h));
    TopDw.at(h)->SetLineStyle(TopLin.at(h));
    SetHistoOption( TopDw.at(h) );
    TopDW->cd();
    TopDW->SetLogy(true);
    TopDW->SetLogx(true);
    TopDw.at(h)->Draw("same");
    L_TopDW->AddEntry( TopDw.at(h),
		       (TopNm.at(h)+"Down").c_str(),"l" );
  }
  TopDW->cd(); L_TopDW->Draw(); DrawLabels(false,false,false,false,false,false,true);
  TopDW->SaveAs( ("Plots/Sys/Top_SysDown_"+lfvType+Suffix).c_str() );

}

void CompareProcSys(int LFVtype, std::string HType, std::string sysVar,
		    bool useBjet, bool isBlind){

  SetATLASStyle();
  TH1::SetDefaultSumw2(kTRUE);

  std::string lfvType = "";
  if(LFVtype==1)      { lfvType="emu";   }
  else if(LFVtype==2) { lfvType="etau";  }
  else if(LFVtype==3) { lfvType="mutau"; }

  std::cout << "Comparing " << sysVar << " Systematic Variations for Channel "
	    << lfvType << " and all processes" << std::endl;
  
  std::string Dir = "";
  if(useBjet){ Dir = "Bjet/";   }
  else       { Dir = "NoBjet/"; }

  std::string fName = Dir+"PercentVariations_"+lfvType;
  if(isBlind)
    fName += "_Blind";

  TFile *TopF = new TFile( (fName+"_Top.root").c_str()     );
  TFile *DbF  = new TFile( (fName+"_DiBoson.root").c_str() );
  TFile *DyF  = new TFile( (fName+"_DY.root").c_str()      );
  TFile *MjF  = NULL;
  
  TH1F *Top      = (TH1F*)TopF->Get( (HType+"_PercVar_"+sysVar).c_str() );
  TH1F *DiBoson  = (TH1F*)DbF ->Get( (HType+"_PercVar_"+sysVar).c_str() );
  TH1F *DY       = (TH1F*)DyF ->Get( (HType+"_PercVar_"+sysVar).c_str() );
  TH1F *Multijet = NULL;
  if(LFVtype>1){
    MjF  = new TFile( (fName+"_Multijet.root").c_str() );
    Multijet = (TH1F*)MjF->Get( (HType+"_PercVar_"+sysVar).c_str() );
  }
  
  TCanvas *sys = new TCanvas("sys","sys",0,0,600,600);
  sys->cd();
  sys->SetLogy(true);
  sys->SetLogx(true);

  SetHistoOption(Top);
  Top->SetLineColor(kBlack);
  DiBoson->SetLineColor(kRed);
  DY->SetLineColor(kBlue);
  if(LFVtype>1)
    Multijet->SetLineColor(kGreen+10);

  Top->Draw("hist");
  DiBoson->Draw("histsame");
  DY->Draw("histsame");
  if(LFVtype>1)
    Multijet->Draw("histsame");

  DrawLabels(false,false,false,false,false,false,true);
  DrawChannel(lfvType);

  TLegend *leg = new TLegend(0.67,0.70,0.97,0.91);
  SetLegendStyle(leg);
  leg->AddEntry(Top    ,"Top"    ,"l");
  leg->AddEntry(DiBoson,"DiBoson","l");
  leg->AddEntry(DY     ,"DY"     ,"l");
  if(LFVtype>1)
    leg->AddEntry(Multijet, "W+jets and Multijet","l");

  leg->Draw();
  
}
