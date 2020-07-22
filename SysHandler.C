std::vector<std::string> GetSysList(int LFVtype, bool useBjet,
				    bool addSys, bool exclNom=false,
				    bool isTopFitCheck=false,
				    bool exclScale=false,
				    bool isSignal=false,
				    bool exclPtRw=false){

  /* making syst list */
  std::vector<std::string> sysVar;
  if(!exclNom)
    sysVar.push_back( "Nominal" );
  if(addSys){
    if( LFVtype==1 || LFVtype==3){
      sysVar.push_back( "MuReco_StatUp"    );
      sysVar.push_back( "MuReco_StatDown"  );
      sysVar.push_back( "MuReco_SysUp"     );
      sysVar.push_back( "MuReco_SysDown"   );
      sysVar.push_back( "MuIso_StatUp"     );
      sysVar.push_back( "MuIso_StatDown"   );
      sysVar.push_back( "MuIso_SysUp"      );
      sysVar.push_back( "MuIso_SysDown"    );
      sysVar.push_back( "MuTrg_StatUp"     );
      sysVar.push_back( "MuTrg_StatDown"   );
      sysVar.push_back( "MuTrg_SysUp"      );
      sysVar.push_back( "MuTrg_SysDown"    );
      sysVar.push_back( "MuTTVA_StatUp"    );
      sysVar.push_back( "MuTTVA_StatDown"  );
      sysVar.push_back( "MuTTVA_SysUp"     );
      sysVar.push_back( "MuTTVA_SysDown"   );
      sysVar.push_back( "MuSmeID_SysUp"    );
      sysVar.push_back( "MuSmeID_SysDown"  );
      sysVar.push_back( "MuSmeMS_SysUp"    );
      sysVar.push_back( "MuSmeMS_SysDown"  );
      sysVar.push_back( "MuScale_SysUp"    );
      sysVar.push_back( "MuScale_SysDown"  );
      sysVar.push_back( "MuSagRho_SysUp"   );
      sysVar.push_back( "MuSagRho_SysDown" );
      sysVar.push_back( "MuSagRes_SysUp"   );
      sysVar.push_back( "MuSagRes_SysDown" );
    }                
    if( LFVtype==1 || LFVtype==2){
      sysVar.push_back( "ElReco_SysUp"    );
      sysVar.push_back( "ElReco_SysDown"  );
      sysVar.push_back( "ElID_SysUp"      );
      sysVar.push_back( "ElID_SysDown"    );
      sysVar.push_back( "ElIso_SysUp"     );
      sysVar.push_back( "ElIso_SysDown"   );
      sysVar.push_back( "ElTrg_SysUp"     );
      sysVar.push_back( "ElTrg_SysDown"   );
      sysVar.push_back( "ElSme_SysUp"     );
      sysVar.push_back( "ElSme_SysDown"   );
      sysVar.push_back( "ElScale_SysUp"   );
      sysVar.push_back( "ElScale_SysDown" );
    }
    
    if( LFVtype==2 || LFVtype==3){
      sysVar.push_back( "TaReco_SysUp"       );
      sysVar.push_back( "TaReco_SysDown"     );
      sysVar.push_back( "TaRecoHpt_SysUp"    );
      sysVar.push_back( "TaRecoHpt_SysDown"  );
      sysVar.push_back( "TaEleOlr_SysUp"     );
      sysVar.push_back( "TaEleOlr_SysDown"   );
      sysVar.push_back( "TaJetID_SysUp"      );
      sysVar.push_back( "TaJetID_SysDown"    );
      sysVar.push_back( "TaJetIDHpt_SysUp"   );
      sysVar.push_back( "TaJetIDHpt_SysDown" );
      sysVar.push_back( "TaSme_SysUp"        );
      sysVar.push_back( "TaSme_SysDown"      );
      sysVar.push_back( "TaSmeDet_SysUp"     );
      sysVar.push_back( "TaSmeDet_SysDown"   );
      sysVar.push_back( "TaSmeMod_SysUp"     );
      sysVar.push_back( "TaSmeMod_SysDown"   );
    }
    
    sysVar.push_back( "JtJvtSF_SysUp"    );
    sysVar.push_back( "JtJvtSF_SysDown"  );
    sysVar.push_back( "JtSme_SysUp"      );
    sysVar.push_back( "JtUncNP1_SysUp"   );
    sysVar.push_back( "JtUncNP1_SysDown" );
    sysVar.push_back( "JtUncNP2_SysUp"   );
    sysVar.push_back( "JtUncNP2_SysDown" );
    sysVar.push_back( "JtUncNP3_SysUp"   );
    sysVar.push_back( "JtUncNP3_SysDown" );
    sysVar.push_back( "JtUncETA_SysUp"   );
    sysVar.push_back( "JtUncETA_SysDown" );
    sysVar.push_back( "MetResPara"       );
    sysVar.push_back( "MetResPer"        );
    sysVar.push_back( "MetScl_SysUp"     );
    sysVar.push_back( "MetScl_SysDown"   );
    sysVar.push_back( "PU_SysUp"         );
    sysVar.push_back( "PU_SysDown"       );
    
    if( useBjet ){
      sysVar.push_back( "BtagSF_Beff_SysUp"      );
      sysVar.push_back( "BtagSF_Beff_SysDown"    );
      sysVar.push_back( "BtagSF_Ceff_SysUp"      );
      sysVar.push_back( "BtagSF_Ceff_SysDown"    );
      sysVar.push_back( "BtagSF_Leff_SysUp"      );
      sysVar.push_back( "BtagSF_Leff_SysDown"    );
      sysVar.push_back( "BtagSF_ExtCeff_SysUp"   );
      sysVar.push_back( "BtagSF_ExtCeff_SysDown" );
      sysVar.push_back( "BtagSF_ExtEff_SysUp"    );
      sysVar.push_back( "BtagSF_ExtEff_SysDown"  );
    }      

    if(!isSignal){
      if(!isTopFitCheck){
	sysVar.push_back( "TopFit_Sys" );
	if( LFVtype==2 || LFVtype==3){
	  sysVar.push_back( "TauFake_StatUp"       );
	  sysVar.push_back( "TauFake_StatDown"     );
	  sysVar.push_back( "TauFake_BDT_SysUp"    );
	  sysVar.push_back( "TauFake_BDT_SysDown"  );
	  sysVar.push_back( "TauFake_CR_Sys"       );
	  sysVar.push_back( "TauFake_Comp_SysUp"   );
	  sysVar.push_back( "TauFake_Comp_SysDown" );
	  sysVar.push_back( "Multijet_kMJ_Stat"    );
	  if( LFVtype==2 )
	    sysVar.push_back( "Multijet_kMJ_Sys"    );
	}
      }
    
      sysVar.push_back( "PDF_Sys"  );
      if(!exclPtRw)
	sysVar.push_back( "PtRw_Sys" );
    
      if(!exclScale){
	sysVar.push_back( "TopScale_SysUp"   );
	sysVar.push_back( "TopScale_SysDown" );
      }
    }
    
  }

  return sysVar;
  
}

std::vector<std::string> GetMultijetSysList(){

  /* making syst list */
  std::vector<std::string> sysVar;
  sysVar.push_back( "mT"      );
  sysVar.push_back( "met"     );
  sysVar.push_back( "MCplus"  );
  sysVar.push_back( "MCminus" );
  sysVar.push_back( "jetsys"  );

  return sysVar;

}

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
