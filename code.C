std::vector<std::string> GetSystematics(int LFVtype, bool useBjet){

  /* making syst list */
  std::vector<std::string> sysVar;

  sysVar.push_back( "TopFit_Sys"     );
  if(LFVtype==2)
    sysVar.push_back( "TopScale_SysDown" );
  else
    sysVar.push_back( "TopScale_SysUp" );
  sysVar.push_back( "PDF_Sys"        );
  sysVar.push_back( "PU_SysUp"       );
  sysVar.push_back( "PtRw_Sys"       );
  if( LFVtype==1 || LFVtype==2){
    sysVar.push_back( "ElTrg_SysUp"   );
    sysVar.push_back( "ElID_SysUp"    );
    sysVar.push_back( "ElReco_SysUp"  );
    sysVar.push_back( "ElIso_SysUp"   );
    sysVar.push_back( "ElSme_SysUp"   );
    sysVar.push_back( "ElScale_SysUp" );
  }
  if( LFVtype==1 || LFVtype==3){
    sysVar.push_back( "MuTrg_SysUp"    );
    sysVar.push_back( "MuReco_SysUp"   );
    sysVar.push_back( "MuIso_SysUp"    );
    sysVar.push_back( "MuTTVA_SysUp"   );
    sysVar.push_back( "MuSmeID_SysUp"  );
    sysVar.push_back( "MuSmeMS_SysUp"  );
    sysVar.push_back( "MuScale_SysUp"  );
    sysVar.push_back( "MuSagRes_SysUp" );
  }                
  if( LFVtype==2 || LFVtype==3){
    sysVar.push_back( "TaJetID_SysUp"      );
    sysVar.push_back( "TaReco_SysUp"       );
    sysVar.push_back( "TaEleOlr_SysUp"     );
    sysVar.push_back( "TaSme_SysUp"        );
    sysVar.push_back( "TauFake_StatUp"     );
    sysVar.push_back( "TauFake_BDT_SysUp"  );
    sysVar.push_back( "TauFake_CR_Sys"     );
    sysVar.push_back( "TauFake_Comp_SysUp" );
    sysVar.push_back( "Multijet_kMJ_Stat"  );
    if( LFVtype==2 )
      sysVar.push_back( "Multijet_kMJ_Sys" );
  }
  sysVar.push_back( "JtJvtSF_SysUp"  );
  sysVar.push_back( "JtSme_SysUp"    );
  sysVar.push_back( "JtUncNP1_SysUp" );
  if( useBjet ){
    sysVar.push_back( "BtagSF_Beff_SysUp"    );
    sysVar.push_back( "BtagSF_Ceff_SysUp"    );
    sysVar.push_back( "BtagSF_Leff_SysUp"    );
    sysVar.push_back( "BtagSF_ExtCeff_SysUp" );
    sysVar.push_back( "BtagSF_ExtEff_SysUp"  );
  } 
  sysVar.push_back( "MetResPara"     );
  sysVar.push_back( "MetScl_SysUp"   );
  sysVar.push_back( "Total" );

  return sysVar;
  
}
