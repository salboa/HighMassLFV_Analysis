#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TFile.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TColor.h>
#include <TMath.h>
#include "iostream"
#include "set"

std::pair<int,double> FindMaxBin(TH1F* h){
  
  int bin = 0; double pt=0;
  for(Int_t b=1; b<h->GetNbinsX(); b++){
    if( h->GetBinContent(b)>0 ){
      bin = b;
      pt  = h->GetBinLowEdge(b+1);
      //std::cout<<"cont "<<h->GetBinContent(b)<<"  Bin "<<b<<" Lower b+1 "<<pt<<std::endl;
    }
  }
  std::pair<int,double> m_p = std::make_pair(bin,pt);
  return m_p;
  
}

void Variables(std::string sample,
	       double Lumi,
	       int LFVtype,
	       std::string sysVar,
	       bool useBJet=false,
	       bool ttCR=false,
	       bool UseKfact=true,
	       bool usePU=true,
	       bool DopTRW=false,
	       bool WjCR=false,
	       bool SSpair=false,
	       bool AntiIso=false,
	       bool NoTauID=false,
	       bool TauFake=false,
	       bool TauFakeSys=false,
	       bool SplitEta=false,
	       bool QcdCR=false,
	       bool Blind=false){

 // TH1::SetDefaultSumw2(kTRUE);
  
  gROOT->SetStyle("ATLAS");
  gROOT->ForceStyle();

  std::string lfvType = "", lfvSt="";
  if(LFVtype==1)      { lfvType="e#mu";    lfvSt="emu";   }
  else if(LFVtype==2) { lfvType="e#tau";   lfvSt="etau";  }
  else if(LFVtype==3) { lfvType="#mu#tau"; lfvSt="mutau"; }
  
  std::string treename = "";
  if( sample=="data" ||
      sysVar=="Nominal" ||
      sysVar.find("Reco")!=std::string::npos   ||
      sysVar.find("Iso")!=std::string::npos    ||
      sysVar.find("Trg")!=std::string::npos    ||
      sysVar.find("ElID")!=std::string::npos   ||
      sysVar.find("TTVA")!=std::string::npos   ||
      sysVar.find("EleOlr")!=std::string::npos ||
      sysVar.find("JetID")!=std::string::npos  ||
      sysVar.find("JvtSF")!=std::string::npos ||
      sysVar.find("BtagSF")!=std::string::npos  ){
    treename = "lfv";
  }
  else{
    treename = "lfv_"+sysVar;
  }
  std::cout << " Sample = " << sample << " Variation "
	    << sysVar << " Tree " << treename << std::endl;
  
  std::string Dir = "";
  if(AntiIso && !NoTauID)      { cout<<"ANTIISO ONLY"<<endl; Dir = "Feb2016/NTUP_QCD_LepFake/";    }
  else if(!AntiIso && NoTauID) { cout<<"NOTAUID ONLY"<<endl; Dir = "Feb2016/NTUP_Wjet_Pt60/";   } //NTUP_Wjet
  else if(AntiIso && NoTauID)  { cout<<"ANTIISO+NOTAUID ONLY"<<endl;Dir = "Feb2016/NTUP_QCD_DoubleFake/"; }
  else                         { Dir = "Feb2016/NTUP_Main_MediumPt60/";        } //NTUP_Main
  
  TFile* pdfIn = new TFile("PDFVariation.root");
  TH1F* PDF1 = (TH1F*)pdfIn->Get("PDFVar_Dib");
  TH1F* PDF2 = (TH1F*)pdfIn->Get("PDFVar_Top");

  TFile* ScaleIn = new TFile("TopScaleVariation.root");
  TH1F* Scale = (TH1F*)ScaleIn->Get( ("h_TopRatioSys_"+lfvSt).c_str() );

  TFile* FFIn = new TFile("TauFakeFactors_Medium.root");
  TH1F *FF1p = NULL, *FF3p = NULL;
  TH1F *FF1p_bar = NULL, *FF3p_bar = NULL;
  TH1F *FF1p_end = NULL, *FF3p_end = NULL;
  if(TauFakeSys){
    FF1p     = (TH1F*)FFIn->Get( "Tau_pT_Fraction_1prong_Sys"     );
    FF3p     = (TH1F*)FFIn->Get( "Tau_pT_Fraction_3prong_Sys"     );
    FF1p_bar = (TH1F*)FFIn->Get( "Tau_pT_Fraction_1prong_Sys_Bar" );
    FF3p_bar = (TH1F*)FFIn->Get( "Tau_pT_Fraction_3prong_Sys_Bar" );
    FF1p_end = (TH1F*)FFIn->Get( "Tau_pT_Fraction_1prong_Sys_End" );
    FF3p_end = (TH1F*)FFIn->Get( "Tau_pT_Fraction_3prong_Sys_End" );
  }
  else{
    FF1p     = (TH1F*)FFIn->Get( "Tau_pT_Fraction_1prong_Nom"     );
    FF3p     = (TH1F*)FFIn->Get( "Tau_pT_Fraction_3prong_Nom"     );
    FF1p_bar = (TH1F*)FFIn->Get( "Tau_pT_Fraction_1prong_Nom_Bar" );
    FF3p_bar = (TH1F*)FFIn->Get( "Tau_pT_Fraction_3prong_Nom_Bar" );
    FF1p_end = (TH1F*)FFIn->Get( "Tau_pT_Fraction_1prong_Nom_End" );
    FF3p_end = (TH1F*)FFIn->Get( "Tau_pT_Fraction_3prong_Nom_End" );
  }
  
  std::vector<string> SampleName;
  
  /* data */
  if(sample=="data")
    SampleName.push_back( "data" );

  /* signal */
  //if(sample=="Zprime"){ 
  if(sample.find("Zprime")!=std::string::npos ||
     sample.find("QBH")!=std::string::npos    || 
     sample.find("SVT")!=std::string::npos     ){
    SampleName.push_back( (sample+"_"+lfvSt).c_str() );
  }
  
  /* DiBoson */
  if(sample=="DiBoson"){
    SampleName.push_back( "DiBoson_llll"         );
    SampleName.push_back( "DiBoson_lllvOFMinus"  );
    SampleName.push_back( "DiBoson_lllvOFPlus"   );
    SampleName.push_back( "DiBoson_lllvSFMinus"  );
    SampleName.push_back( "DiBoson_lllvSFPlus"   );
    SampleName.push_back( "DiBoson_WplvWmqq"     );
    SampleName.push_back( "DiBoson_WpqqWmlv"     );
    SampleName.push_back( "DiBoson_WlvZqq"       );
    SampleName.push_back( "DiBoson_WqqZll"       );
    SampleName.push_back( "DiBoson_WqqZvv"       );
    SampleName.push_back( "DiBoson_ZqqZll"       );
    //SampleName.push_back( "DiBoson_llvv" ); //to be removed 
    SampleName.push_back( "DiBoson_evmuv_0M150"        );
    SampleName.push_back( "DiBoson_evmuv_150M500"      );
    SampleName.push_back( "DiBoson_evmuv_500M1000"     );
    SampleName.push_back( "DiBoson_evmuv_1000M2000"    );
    SampleName.push_back( "DiBoson_evmuv_2000M3000"    );
    SampleName.push_back( "DiBoson_evmuv_3000M4000"    );
    SampleName.push_back( "DiBoson_evmuv_4000M5000"    );
    SampleName.push_back( "DiBoson_evmuv_M5000"        );
    SampleName.push_back( "DiBoson_evtauv_0M150"       );
    SampleName.push_back( "DiBoson_evtauv_150M500"     );
    SampleName.push_back( "DiBoson_evtauv_500M1000"    );
    SampleName.push_back( "DiBoson_evtauv_1000M2000"   );
    SampleName.push_back( "DiBoson_evtauv_2000M3000"   );
    SampleName.push_back( "DiBoson_evtauv_3000M4000"   );
    SampleName.push_back( "DiBoson_evtauv_4000M5000"   );
    SampleName.push_back( "DiBoson_evtauv_M5000"       );
    SampleName.push_back( "DiBoson_muvtauv_0M150"      );
    SampleName.push_back( "DiBoson_muvtauv_150M500"    );
    SampleName.push_back( "DiBoson_muvtauv_500M1000"   );
    SampleName.push_back( "DiBoson_muvtauv_1000M2000"  );
    SampleName.push_back( "DiBoson_muvtauv_2000M3000"  );
    SampleName.push_back( "DiBoson_muvtauv_3000M4000"  );
    SampleName.push_back( "DiBoson_muvtauv_4000M5000"  );
    SampleName.push_back( "DiBoson_muvtauv_M5000"      );
    SampleName.push_back( "DiBoson_tauvtauv_0M150"     );
    SampleName.push_back( "DiBoson_tauvtauv_150M500"   );
    SampleName.push_back( "DiBoson_tauvtauv_500M1000"  );
    SampleName.push_back( "DiBoson_tauvtauv_1000M2000" );
    SampleName.push_back( "DiBoson_tauvtauv_2000M3000" );
    SampleName.push_back( "DiBoson_tauvtauv_3000M4000" );
    SampleName.push_back( "DiBoson_tauvtauv_4000M5000" );
    SampleName.push_back( "DiBoson_tauvtauv_M5000"     );
  }

  /*DY*/
  if(sample=="DYtautau"){
    SampleName.push_back( "Ztautau" );
    SampleName.push_back( "DYtautau_120M180"   );
    SampleName.push_back( "DYtautau_180M250"   );
    SampleName.push_back( "DYtautau_250M400"   );
    SampleName.push_back( "DYtautau_400M600"   );
    SampleName.push_back( "DYtautau_600M800"   );
    SampleName.push_back( "DYtautau_800M1000"  );
    SampleName.push_back( "DYtautau_1000M1250" );
    SampleName.push_back( "DYtautau_1250M1500" );
    SampleName.push_back( "DYtautau_1500M1750" );
    SampleName.push_back( "DYtautau_1750M2000" );
    SampleName.push_back( "DYtautau_2000M2250" );
    SampleName.push_back( "DYtautau_2250M2500" );
    SampleName.push_back( "DYtautau_2500M2750" );
    SampleName.push_back( "DYtautau_2750M3000" );
    SampleName.push_back( "DYtautau_3000M3500" );
    SampleName.push_back( "DYtautau_3500M4000" );
    SampleName.push_back( "DYtautau_4000M4500" );
    SampleName.push_back( "DYtautau_4500M5000" );
    SampleName.push_back( "DYtautau_5000M"     );
  }
  if(sample=="DYee"){
    //SampleName.push_back( "DYee_70M120"        );
    SampleName.push_back( "Zee" );
    SampleName.push_back( "DYee_120M180"       );
    SampleName.push_back( "DYee_180M250"       );
    SampleName.push_back( "DYee_250M400"       );
    SampleName.push_back( "DYee_400M600"       );
    SampleName.push_back( "DYee_600M800"       );
    SampleName.push_back( "DYee_800M1000"      );
    SampleName.push_back( "DYee_1000M1250"     );
    SampleName.push_back( "DYee_1250M1500"     );
    SampleName.push_back( "DYee_1500M1750"     );
    SampleName.push_back( "DYee_1750M2000"     );
    SampleName.push_back( "DYee_2000M2250"     );
    SampleName.push_back( "DYee_2250M2500"     );
    SampleName.push_back( "DYee_2500M2750"     );
    SampleName.push_back( "DYee_2750M3000"     );
    SampleName.push_back( "DYee_3000M3500"     );
    SampleName.push_back( "DYee_3500M4000"     );
    SampleName.push_back( "DYee_4000M4500"     );
    SampleName.push_back( "DYee_4500M5000"     );
    SampleName.push_back( "DYee_5000M"         );
  }
  
  if(sample=="DYmumu"){
    //SampleName.push_back( "DYmumu_70M120"      );
    SampleName.push_back( "Zmumu" );
    SampleName.push_back( "DYmumu_120M180"     );
    SampleName.push_back( "DYmumu_180M250"     );
    //SampleName.push_back( "DYmumu_250M400"     );
    SampleName.push_back( "DYmumu_400M600"     );
    SampleName.push_back( "DYmumu_600M800"     );
    SampleName.push_back( "DYmumu_800M1000"    );
    SampleName.push_back( "DYmumu_1000M1250"   );
    SampleName.push_back( "DYmumu_1250M1500"   );
    SampleName.push_back( "DYmumu_1500M1750"   );
    SampleName.push_back( "DYmumu_1750M2000"   );
    SampleName.push_back( "DYmumu_2000M2250"   );
    SampleName.push_back( "DYmumu_2250M2500"   );
    SampleName.push_back( "DYmumu_2500M2750"   );
    SampleName.push_back( "DYmumu_2750M3000"   );
    SampleName.push_back( "DYmumu_3000M3500"   );
    SampleName.push_back( "DYmumu_3500M4000"   );
    SampleName.push_back( "DYmumu_4000M4500"   );
    SampleName.push_back( "DYmumu_4500M5000"   );
    SampleName.push_back( "DYmumu_5000M"       );
  }
  if(sample=="DY"){
    SampleName.push_back( "Ztautau" );
    SampleName.push_back( "DYtautau_120M180"   );
    SampleName.push_back( "DYtautau_180M250"   );
    SampleName.push_back( "DYtautau_250M400"   );
    SampleName.push_back( "DYtautau_400M600"   );
    SampleName.push_back( "DYtautau_600M800"   );
    SampleName.push_back( "DYtautau_800M1000"  );
    SampleName.push_back( "DYtautau_1000M1250" );
    SampleName.push_back( "DYtautau_1250M1500" );
    SampleName.push_back( "DYtautau_1500M1750" );
    SampleName.push_back( "DYtautau_1750M2000" );
    SampleName.push_back( "DYtautau_2000M2250" );
    SampleName.push_back( "DYtautau_2250M2500" );
    SampleName.push_back( "DYtautau_2500M2750" );
    SampleName.push_back( "DYtautau_2750M3000" );
    SampleName.push_back( "DYtautau_3000M3500" );
    SampleName.push_back( "DYtautau_3500M4000" );
    SampleName.push_back( "DYtautau_4000M4500" );
    SampleName.push_back( "DYtautau_4500M5000" );
    SampleName.push_back( "DYtautau_5000M"     );
    //SampleName.push_back( "DYee_70M120"        );
    SampleName.push_back( "Zee" );
    SampleName.push_back( "DYee_120M180"       );
    SampleName.push_back( "DYee_180M250"       );
    SampleName.push_back( "DYee_250M400"       );
    SampleName.push_back( "DYee_400M600"       );
    SampleName.push_back( "DYee_600M800"       );
    SampleName.push_back( "DYee_800M1000"      );
    SampleName.push_back( "DYee_1000M1250"     );
    SampleName.push_back( "DYee_1250M1500"     );
    SampleName.push_back( "DYee_1500M1750"     );
    SampleName.push_back( "DYee_1750M2000"     );
    SampleName.push_back( "DYee_2000M2250"     );
    SampleName.push_back( "DYee_2250M2500"     );
    SampleName.push_back( "DYee_2500M2750"     );
    SampleName.push_back( "DYee_2750M3000"     );
    SampleName.push_back( "DYee_3000M3500"     );
    SampleName.push_back( "DYee_3500M4000"     );
    SampleName.push_back( "DYee_4000M4500"     );
    SampleName.push_back( "DYee_4500M5000"     );
    SampleName.push_back( "DYee_5000M"         );
    //SampleName.push_back( "DYmumu_70M120"      );
    SampleName.push_back( "Zmumu"              );
    SampleName.push_back( "DYmumu_120M180"     );
    SampleName.push_back( "DYmumu_180M250"     );
    //SampleName.push_back( "DYmumu_250M400"     );
    SampleName.push_back( "DYmumu_400M600"     );
    SampleName.push_back( "DYmumu_600M800"     );
    SampleName.push_back( "DYmumu_800M1000"    );
    SampleName.push_back( "DYmumu_1000M1250"   );
    SampleName.push_back( "DYmumu_1250M1500"   );
    SampleName.push_back( "DYmumu_1500M1750"   );
    SampleName.push_back( "DYmumu_1750M2000"   );
    SampleName.push_back( "DYmumu_2000M2250"   );
    SampleName.push_back( "DYmumu_2250M2500"   );
    SampleName.push_back( "DYmumu_2500M2750"   );
    SampleName.push_back( "DYmumu_2750M3000"   );
    SampleName.push_back( "DYmumu_3000M3500"   );
    SampleName.push_back( "DYmumu_3500M4000"   );
    SampleName.push_back( "DYmumu_4000M4500"   );
    SampleName.push_back( "DYmumu_4500M5000"   );
    SampleName.push_back( "DYmumu_5000M"       );
  }
  
  /* ttbar and single-top */
  if(sample=="Top"){
    SampleName.push_back( "ttbar_incl" ); //to be removed
    //SampleName.push_back( "ttbar_0M150"     );
    //SampleName.push_back( "ttbar_150M500"   );
    //SampleName.push_back( "ttbar_500M1000"  );
    //SampleName.push_back( "ttbar_1000M2000" );
    //SampleName.push_back( "ttbar_2000M3000" );
    //SampleName.push_back( "ttbar_3000M4000" );
    //SampleName.push_back( "ttbar_4000M5000" );
    //SampleName.push_back( "ttbar_M5000"     );
    SampleName.push_back( "Wt_antitop"      );
    SampleName.push_back( "Wt_top"          );
  }
  
  /* ttbar and single-top scale up */
  if(sample=="Top_ScaleUp"){
    SampleName.push_back( "ttbar_incl_SysUp" );
    SampleName.push_back( "Wt_antitop"       );
    SampleName.push_back( "Wt_top"           );
  }
  
  /* ttbar and single-top scale down */
  if(sample=="Top_ScaleDown"){
    SampleName.push_back( "ttbar_incl_SysDown" );
    SampleName.push_back( "Wt_antitop"         );
    SampleName.push_back( "Wt_top"             );
  }

  /* ttbar Sherpa Incl/mass-binned */
  if(sample=="ttbar_SherpaMB"){
    SampleName.push_back( "ttbar_0M150"     );
    SampleName.push_back( "ttbar_150M500"   );
    SampleName.push_back( "ttbar_500M1000"  );
    SampleName.push_back( "ttbar_1000M2000" );
    SampleName.push_back( "ttbar_2000M3000" );
    SampleName.push_back( "ttbar_3000M4000" );
    SampleName.push_back( "ttbar_4000M5000" );
    SampleName.push_back( "ttbar_M5000"     );
  }
  if(sample=="ttbar_SherpaIncl"){
    SampleName.push_back( "ttbar_Sherpa_DiLep"    );
    SampleName.push_back( "ttbar_Sherpa_SingLepP" );
    SampleName.push_back( "ttbar_Sherpa_SingLepM" );
    SampleName.push_back( "Wt_antitop"      );
    SampleName.push_back( "Wt_top"          );
  }
  
  /* ttbar Powheg Incl/mass-binned */
  if(sample=="ttbar_PowhegIncl"){
    SampleName.push_back( "ttbar_incl" );
    SampleName.push_back( "Wt_antitop"      );
    SampleName.push_back( "Wt_top"          );
  }
  if(sample=="ttbar_PowhegMB"){
    SampleName.push_back( "ttbar_incl" );
    //SampleName.push_back( "ttbar_1100MTT1300" );
    SampleName.push_back( "ttbar_1300MTT1500" );
    SampleName.push_back( "ttbar_1500MTT1700" );
    SampleName.push_back( "ttbar_1700MTT2000" );
    SampleName.push_back( "ttbar_MTT2000" );
  }

  if(sample=="ttbar_410000"){
    SampleName.push_back( "ttbar_incl" );
  }
  if(sample=="ttbar_410001"){
    SampleName.push_back( "ttbar_incl_SysDown" );
  }
  if(sample=="ttbar_410002"){
    SampleName.push_back( "ttbar_incl_SysUp" );
  }
  if(sample=="ttbar_410003"){
    SampleName.push_back( "ttbar_410003" );
  }
  if(sample=="ttbar_410009"){
    SampleName.push_back( "ttbar_dilep" );    
  }

  /* Wjets */
  if(sample=="Wjets_Powheg"){
    SampleName.push_back( "Wminusmunu"  );
    SampleName.push_back( "Wminustaunu" );
    SampleName.push_back( "Wminusenu"   );
    SampleName.push_back( "Wplusmunu"   );
    SampleName.push_back( "Wplustaunu"  );
    SampleName.push_back( "Wplusenu"    );
    SampleName.push_back( "Wplusenu_120M180"      );
    SampleName.push_back( "Wplusenu_180M250"      );
    SampleName.push_back( "Wplusenu_250M400"      );
    SampleName.push_back( "Wplusenu_400M600"      );
    SampleName.push_back( "Wplusenu_600M800"      );
    SampleName.push_back( "Wplusenu_800M1000"     );
    SampleName.push_back( "Wplusenu_1000M1250"    );
    SampleName.push_back( "Wplusenu_1250M1500"    );
    SampleName.push_back( "Wplusenu_1500M1750"    );
    SampleName.push_back( "Wplusenu_1750M2000"    ); //not present for FakeTau
    SampleName.push_back( "Wplusenu_2000M2250"    );
    SampleName.push_back( "Wplusenu_2250M2500"    );
    SampleName.push_back( "Wplusenu_2500M2750"    );
    SampleName.push_back( "Wplusenu_2750M3000"    );
    SampleName.push_back( "Wplusenu_3000M3500"    );
    SampleName.push_back( "Wplusenu_3500M4000"    );
    SampleName.push_back( "Wplusenu_4000M4500"    );
    SampleName.push_back( "Wplusenu_4500M5000"    );
    SampleName.push_back( "Wplusenu_5000M"        );
    SampleName.push_back( "Wminenu_120M180"       );
    SampleName.push_back( "Wminenu_180M250"       );
    SampleName.push_back( "Wminenu_250M400"       );
    SampleName.push_back( "Wminenu_400M600"       );
    SampleName.push_back( "Wminenu_600M800"       );
    SampleName.push_back( "Wminenu_800M1000"      );
    SampleName.push_back( "Wminenu_1000M1250"     );
    SampleName.push_back( "Wminenu_1250M1500"     );
    SampleName.push_back( "Wminenu_1500M1750"     );
    SampleName.push_back( "Wminenu_1750M2000"     );
    SampleName.push_back( "Wminenu_2000M2250"     );
    SampleName.push_back( "Wminenu_2250M2500"     );
    SampleName.push_back( "Wminenu_2500M2750"     );
    SampleName.push_back( "Wminenu_2750M3000"     );
    SampleName.push_back( "Wminenu_3000M3500"     );
    SampleName.push_back( "Wminenu_3500M4000"     );
    SampleName.push_back( "Wminenu_4000M4500"     );
    SampleName.push_back( "Wminenu_4500M5000"     );
    SampleName.push_back( "Wminenu_5000M"         );
    SampleName.push_back( "Wplusmunu_120M180"     );
    SampleName.push_back( "Wplusmunu_180M250"     );
    SampleName.push_back( "Wplusmunu_250M400"     );
    SampleName.push_back( "Wplusmunu_400M600"     );
    SampleName.push_back( "Wplusmunu_600M800"     );
    SampleName.push_back( "Wplusmunu_800M1000"    );
    SampleName.push_back( "Wplusmunu_1000M1250"   );
    SampleName.push_back( "Wplusmunu_1250M1500"   );
    SampleName.push_back( "Wplusmunu_1500M1750"   );
    SampleName.push_back( "Wplusmunu_1750M2000"   );
    SampleName.push_back( "Wplusmunu_2000M2250"   );
    SampleName.push_back( "Wplusmunu_2250M2500"   );
    SampleName.push_back( "Wplusmunu_2500M2750"   );
    SampleName.push_back( "Wplusmunu_2750M3000"   );
    SampleName.push_back( "Wplusmunu_3000M3500"   );
    SampleName.push_back( "Wplusmunu_3500M4000"   );
    SampleName.push_back( "Wplusmunu_4000M4500"   );
    SampleName.push_back( "Wplusmunu_4500M5000"   );
    SampleName.push_back( "Wplusmunu_5000M"       );
    SampleName.push_back( "Wminmunu_120M180"      );
    SampleName.push_back( "Wminmunu_180M250"      );
    SampleName.push_back( "Wminmunu_250M400"      );
    SampleName.push_back( "Wminmunu_400M600"      );
    SampleName.push_back( "Wminmunu_600M800"      );
    SampleName.push_back( "Wminmunu_800M1000"     );
    SampleName.push_back( "Wminmunu_1000M1250"    );
    SampleName.push_back( "Wminmunu_1250M1500"    );
    SampleName.push_back( "Wminmunu_1500M1750"    );
    SampleName.push_back( "Wminmunu_1750M2000"    );
    SampleName.push_back( "Wminmunu_2000M2250"    );
    SampleName.push_back( "Wminmunu_2250M2500"    );
    SampleName.push_back( "Wminmunu_2500M2750"    );
    SampleName.push_back( "Wminmunu_2750M3000"    );
    SampleName.push_back( "Wminmunu_3000M3500"    );
    SampleName.push_back( "Wminmunu_3500M4000"    );
    SampleName.push_back( "Wminmunu_4000M4500"    );
    SampleName.push_back( "Wminmunu_4500M5000"    );
    SampleName.push_back( "Wminmunu_5000M"        );
    SampleName.push_back( "Wplustaunu_120M180"    );
    SampleName.push_back( "Wplustaunu_180M250"    );
    SampleName.push_back( "Wplustaunu_250M400"    );
    SampleName.push_back( "Wplustaunu_400M600"    );
    SampleName.push_back( "Wplustaunu_600M800"    );
    SampleName.push_back( "Wplustaunu_800M1000"   );
    SampleName.push_back( "Wplustaunu_1000M1250"  );
    SampleName.push_back( "Wplustaunu_1250M1500"  );
    SampleName.push_back( "Wplustaunu_1500M1750"  );
    SampleName.push_back( "Wplustaunu_1750M2000"  );
    SampleName.push_back( "Wplustaunu_2000M2250"  );
    SampleName.push_back( "Wplustaunu_2250M2500"  );
    SampleName.push_back( "Wplustaunu_2500M2750"  );
    SampleName.push_back( "Wplustaunu_2750M3000"  );
    SampleName.push_back( "Wplustaunu_3000M3500"  );
    SampleName.push_back( "Wplustaunu_3500M4000"  );
    SampleName.push_back( "Wplustaunu_4000M4500"  );
    SampleName.push_back( "Wplustaunu_4500M5000"  );
    SampleName.push_back( "Wplustaunu_5000M"      );
    SampleName.push_back( "Wmintaunu_120M180"     );
    SampleName.push_back( "Wmintaunu_180M250"     );
    SampleName.push_back( "Wmintaunu_250M400"     );
    SampleName.push_back( "Wmintaunu_400M600"     );
    SampleName.push_back( "Wmintaunu_600M800"     );
    SampleName.push_back( "Wmintaunu_800M1000"    );
    SampleName.push_back( "Wmintaunu_1000M1250"   );
    SampleName.push_back( "Wmintaunu_1250M1500"   );
    SampleName.push_back( "Wmintaunu_1500M1750"   );
    SampleName.push_back( "Wmintaunu_1750M2000"   );
    SampleName.push_back( "Wmintaunu_2000M2250"   );
    SampleName.push_back( "Wmintaunu_2250M2500"   );
    SampleName.push_back( "Wmintaunu_2500M2750"   );
    SampleName.push_back( "Wmintaunu_2750M3000"   );
    SampleName.push_back( "Wmintaunu_3000M3500"   );
    SampleName.push_back( "Wmintaunu_3500M4000"   );
    SampleName.push_back( "Wmintaunu_4000M4500"   );
    SampleName.push_back( "Wmintaunu_4500M5000"   );
    SampleName.push_back( "Wmintaunu_5000M"       );
  }

  if(sample=="Wjets"){
    SampleName.push_back( "Wmunu_Pt0_70_CVetoBVeto"          );
    SampleName.push_back( "Wmunu_Pt0_70_CFilterBVeto"        );
    SampleName.push_back( "Wmunu_Pt0_70_BFilter"             );
    SampleName.push_back( "Wmunu_Pt70_140_CVetoBVeto"        );
    SampleName.push_back( "Wmunu_Pt70_140_CFilterBVeto"      );
    SampleName.push_back( "Wmunu_Pt70_140_BFilter"           );
    SampleName.push_back( "Wmunu_Pt140_280_CVetoBVeto"       );
    SampleName.push_back( "Wmunu_Pt140_280_CFilterBVeto"     );
    SampleName.push_back( "Wmunu_Pt140_280_BFilter"          );
    SampleName.push_back( "Wmunu_Pt280_500_CVetoBVeto"       );
    SampleName.push_back( "Wmunu_Pt280_500_CFilterBVeto"     );
    SampleName.push_back( "Wmunu_Pt280_500_BFilter"          );
    SampleName.push_back( "Wmunu_Pt500_700_CVetoBVeto"       );
    SampleName.push_back( "Wmunu_Pt500_700_CFilterBVeto"     );
    SampleName.push_back( "Wmunu_Pt500_700_BFilter"          );
    SampleName.push_back( "Wmunu_Pt700_1000_CVetoBVeto"      );
    SampleName.push_back( "Wmunu_Pt700_1000_CFilterBVeto"    );
    SampleName.push_back( "Wmunu_Pt700_1000_BFilter"         );
    SampleName.push_back( "Wmunu_Pt1000_2000_CVetoBVeto"     );
    SampleName.push_back( "Wmunu_Pt1000_2000_CFilterBVeto"   );
    SampleName.push_back( "Wmunu_Pt1000_2000_BFilter"        );
    SampleName.push_back( "Wmunu_Pt2000_E_CMS_CVetoBVeto"    );
    SampleName.push_back( "Wmunu_Pt2000_E_CMS_CFilterBVeto"  );
    SampleName.push_back( "Wmunu_Pt2000_E_CMS_BFilter"       );
    SampleName.push_back( "Wenu_Pt0_70_CVetoBVeto"           );
    SampleName.push_back( "Wenu_Pt0_70_CFilterBVeto"         );
    SampleName.push_back( "Wenu_Pt0_70_BFilter"              );
    SampleName.push_back( "Wenu_Pt70_140_CVetoBVeto"         );
    SampleName.push_back( "Wenu_Pt70_140_CFilterBVeto"       );
    SampleName.push_back( "Wenu_Pt70_140_BFilter"            );
    SampleName.push_back( "Wenu_Pt140_280_CVetoBVeto"        );
    //SampleName.push_back( "Wenu_Pt140_280_CFilterBVeto"      );
    SampleName.push_back( "Wenu_Pt140_280_BFilter"           );
    SampleName.push_back( "Wenu_Pt280_500_CVetoBVeto"        );
    SampleName.push_back( "Wenu_Pt280_500_CFilterBVeto"      );
    SampleName.push_back( "Wenu_Pt280_500_BFilter"           );
    SampleName.push_back( "Wenu_Pt500_700_CVetoBVeto"        );
    SampleName.push_back( "Wenu_Pt500_700_CFilterBVeto"      );
    SampleName.push_back( "Wenu_Pt500_700_BFilter"           );
    SampleName.push_back( "Wenu_Pt700_1000_CVetoBVeto"       );
    SampleName.push_back( "Wenu_Pt700_1000_CFilterBVeto"     );
    SampleName.push_back( "Wenu_Pt700_1000_BFilter"          );
    SampleName.push_back( "Wenu_Pt1000_2000_CVetoBVeto"      );
    SampleName.push_back( "Wenu_Pt1000_2000_CFilterBVeto"    );
    SampleName.push_back( "Wenu_Pt1000_2000_BFilter"         );
    SampleName.push_back( "Wenu_Pt2000_E_CMS_CVetoBVeto"     );
    SampleName.push_back( "Wenu_Pt2000_E_CMS_CFilterBVeto"   );
    SampleName.push_back( "Wenu_Pt2000_E_CMS_BFilter"        );
    SampleName.push_back( "Wtaunu_Pt0_70_CVetoBVeto"         );
    SampleName.push_back( "Wtaunu_Pt0_70_CFilterBVeto"       );
    SampleName.push_back( "Wtaunu_Pt0_70_BFilter"            );
    SampleName.push_back( "Wtaunu_Pt70_140_CVetoBVeto"       );
    SampleName.push_back( "Wtaunu_Pt70_140_CFilterBVeto"     );
    SampleName.push_back( "Wtaunu_Pt70_140_BFilter"          );
    SampleName.push_back( "Wtaunu_Pt140_280_CVetoBVeto"      );
    SampleName.push_back( "Wtaunu_Pt140_280_CFilterBVeto"    );
    SampleName.push_back( "Wtaunu_Pt140_280_BFilter"         );
    SampleName.push_back( "Wtaunu_Pt280_500_CVetoBVeto"      );
    SampleName.push_back( "Wtaunu_Pt280_500_CFilterBVeto"    );
    SampleName.push_back( "Wtaunu_Pt280_500_BFilter"         );
    //SampleName.push_back( "Wtaunu_Pt500_700_CVetoBVeto"      );
    SampleName.push_back( "Wtaunu_Pt500_700_CFilterBVeto"    );
    SampleName.push_back( "Wtaunu_Pt500_700_BFilter"         );
    SampleName.push_back( "Wtaunu_Pt700_1000_CVetoBVeto"     );
    SampleName.push_back( "Wtaunu_Pt700_1000_CFilterBVeto"   );
    SampleName.push_back( "Wtaunu_Pt700_1000_BFilter"        );
    SampleName.push_back( "Wtaunu_Pt1000_2000_CVetoBVeto"    );
    SampleName.push_back( "Wtaunu_Pt1000_2000_CFilterBVeto"  );
    SampleName.push_back( "Wtaunu_Pt1000_2000_BFilter"       );
    SampleName.push_back( "Wtaunu_Pt2000_E_CMS_CVetoBVeto"   );
    SampleName.push_back( "Wtaunu_Pt2000_E_CMS_CFilterBVeto" );
    SampleName.push_back( "Wtaunu_Pt2000_E_CMS_BFilter"      );
  }

  /* All Backgrounds */
  if(sample=="AllBkg"){
    SampleName.push_back( "DiBoson_llll"         );
    SampleName.push_back( "DiBoson_lllvOFMinus"  );
    SampleName.push_back( "DiBoson_lllvOFPlus"   );
    SampleName.push_back( "DiBoson_lllvSFMinus"  );
    SampleName.push_back( "DiBoson_lllvSFPlus"   );
    SampleName.push_back( "DiBoson_WplvWmqq"     );
    SampleName.push_back( "DiBoson_WpqqWmlv"     );
    SampleName.push_back( "DiBoson_WlvZqq"       );
    SampleName.push_back( "DiBoson_WqqZll"       );
    SampleName.push_back( "DiBoson_WqqZvv"       );
    SampleName.push_back( "DiBoson_ZqqZll"       );
    //SampleName.push_back( "DiBoson_llvv"   ); //to be removed
    SampleName.push_back( "DiBoson_evmuv_0M150"        );
    SampleName.push_back( "DiBoson_evmuv_150M500"      );
    SampleName.push_back( "DiBoson_evmuv_500M1000"     );
    SampleName.push_back( "DiBoson_evmuv_1000M2000"    );
    SampleName.push_back( "DiBoson_evmuv_2000M3000"    );
    SampleName.push_back( "DiBoson_evmuv_3000M4000"    );
    SampleName.push_back( "DiBoson_evmuv_4000M5000"    );
    SampleName.push_back( "DiBoson_evmuv_M5000"        );
    SampleName.push_back( "DiBoson_evtauv_0M150"       );
    SampleName.push_back( "DiBoson_evtauv_150M500"     );
    SampleName.push_back( "DiBoson_evtauv_500M1000"    );
    SampleName.push_back( "DiBoson_evtauv_1000M2000"   );
    SampleName.push_back( "DiBoson_evtauv_2000M3000"   );
    SampleName.push_back( "DiBoson_evtauv_3000M4000"   );
    SampleName.push_back( "DiBoson_evtauv_4000M5000"   );
    SampleName.push_back( "DiBoson_evtauv_M5000"       );
    SampleName.push_back( "DiBoson_muvtauv_0M150"      );
    SampleName.push_back( "DiBoson_muvtauv_150M500"    );
    SampleName.push_back( "DiBoson_muvtauv_500M1000"   );
    SampleName.push_back( "DiBoson_muvtauv_1000M2000"  );
    SampleName.push_back( "DiBoson_muvtauv_2000M3000"  );
    SampleName.push_back( "DiBoson_muvtauv_3000M4000"  );
    SampleName.push_back( "DiBoson_muvtauv_4000M5000"  );
    SampleName.push_back( "DiBoson_muvtauv_M5000"      );
    SampleName.push_back( "DiBoson_tauvtauv_0M150"     );
    SampleName.push_back( "DiBoson_tauvtauv_150M500"   );
    SampleName.push_back( "DiBoson_tauvtauv_500M1000"  );
    SampleName.push_back( "DiBoson_tauvtauv_1000M2000" );
    SampleName.push_back( "DiBoson_tauvtauv_2000M3000" );
    SampleName.push_back( "DiBoson_tauvtauv_3000M4000" );
    SampleName.push_back( "DiBoson_tauvtauv_4000M5000" );
    SampleName.push_back( "DiBoson_tauvtauv_M5000"     );
    SampleName.push_back( "Ztautau" );
    SampleName.push_back( "DYtautau_120M180"   );
    SampleName.push_back( "DYtautau_180M250"   );
    SampleName.push_back( "DYtautau_250M400"   );
    SampleName.push_back( "DYtautau_400M600"   );
    SampleName.push_back( "DYtautau_600M800"   );
    SampleName.push_back( "DYtautau_800M1000"  );
    SampleName.push_back( "DYtautau_1000M1250" );
    SampleName.push_back( "DYtautau_1250M1500" );
    SampleName.push_back( "DYtautau_1500M1750" );
    SampleName.push_back( "DYtautau_1750M2000" );
    SampleName.push_back( "DYtautau_2000M2250" );
    SampleName.push_back( "DYtautau_2250M2500" );
    SampleName.push_back( "DYtautau_2500M2750" );
    SampleName.push_back( "DYtautau_2750M3000" );
    SampleName.push_back( "DYtautau_3000M3500" );
    SampleName.push_back( "DYtautau_3500M4000" );
    SampleName.push_back( "DYtautau_4000M4500" );
    SampleName.push_back( "DYtautau_4500M5000" );
    SampleName.push_back( "DYtautau_5000M"     );
    //SampleName.push_back( "DYee_70M120"        );
    SampleName.push_back( "Zee" );
    SampleName.push_back( "DYee_120M180"       );
    SampleName.push_back( "DYee_180M250"       );
    SampleName.push_back( "DYee_250M400"       );
    SampleName.push_back( "DYee_400M600"       );
    SampleName.push_back( "DYee_600M800"       );
    SampleName.push_back( "DYee_800M1000"      );
    SampleName.push_back( "DYee_1000M1250"     );
    SampleName.push_back( "DYee_1250M1500"     );
    SampleName.push_back( "DYee_1500M1750"     );
    SampleName.push_back( "DYee_1750M2000"     );
    SampleName.push_back( "DYee_2000M2250"     );
    SampleName.push_back( "DYee_2250M2500"     );
    SampleName.push_back( "DYee_2500M2750"     );
    SampleName.push_back( "DYee_2750M3000"     );
    SampleName.push_back( "DYee_3000M3500"     );
    SampleName.push_back( "DYee_3500M4000"     );
    SampleName.push_back( "DYee_4000M4500"     );
    SampleName.push_back( "DYee_4500M5000"     );
    SampleName.push_back( "DYee_5000M"         );
    //SampleName.push_back( "DYmumu_70M120"      );
    SampleName.push_back( "Zmumu"              );
    SampleName.push_back( "DYmumu_120M180"     );
    SampleName.push_back( "DYmumu_180M250"     );
    //SampleName.push_back( "DYmumu_250M400"     );
    SampleName.push_back( "DYmumu_400M600"     );
    SampleName.push_back( "DYmumu_600M800"     );
    SampleName.push_back( "DYmumu_800M1000"    );
    SampleName.push_back( "DYmumu_1000M1250"   );
    SampleName.push_back( "DYmumu_1250M1500"   );
    SampleName.push_back( "DYmumu_1500M1750"   );
    SampleName.push_back( "DYmumu_1750M2000"   );
    SampleName.push_back( "DYmumu_2000M2250"   );
    SampleName.push_back( "DYmumu_2250M2500"   );
    SampleName.push_back( "DYmumu_2500M2750"   );
    SampleName.push_back( "DYmumu_2750M3000"   );
    SampleName.push_back( "DYmumu_3000M3500"   );
    SampleName.push_back( "DYmumu_3500M4000"   );
    SampleName.push_back( "DYmumu_4000M4500"   );
    SampleName.push_back( "DYmumu_4500M5000"   );
    SampleName.push_back( "DYmumu_5000M"       );
    SampleName.push_back( "ttbar_incl"     ); //to be removed
    //SampleName.push_back( "ttbar_0M150"     );
    //SampleName.push_back( "ttbar_150M500"   );
    //SampleName.push_back( "ttbar_500M1000"  );
    //SampleName.push_back( "ttbar_1000M2000" );
    //SampleName.push_back( "ttbar_2000M3000" );
    //SampleName.push_back( "ttbar_3000M4000" );
    //SampleName.push_back( "ttbar_4000M5000" );
    //SampleName.push_back( "ttbar_M5000"     );
    SampleName.push_back( "Wt_antitop"      );
    SampleName.push_back( "Wt_top"          );
    //if(LFVtype!=1){
    //  SampleName.push_back( "Wminusmunu"  );		
    //  SampleName.push_back( "Wminustaunu" );		
    //  SampleName.push_back( "Wminusenu"   );		
    //  SampleName.push_back( "Wplusmunu"   );		
    //  SampleName.push_back( "Wplustaunu"  );		
    //  SampleName.push_back( "Wplusenu"    );		
    //  SampleName.push_back( "Wplusenu_120M180"      );
    //  SampleName.push_back( "Wplusenu_180M250"      );
    //  SampleName.push_back( "Wplusenu_250M400"      );
    //  SampleName.push_back( "Wplusenu_400M600"      );
    //  SampleName.push_back( "Wplusenu_600M800"      );
    //  SampleName.push_back( "Wplusenu_800M1000"     );
    //  SampleName.push_back( "Wplusenu_1000M1250"    );
    //  SampleName.push_back( "Wplusenu_1250M1500"    );
    //  SampleName.push_back( "Wplusenu_1500M1750"    );
    //  SampleName.push_back( "Wplusenu_1750M2000"    );
    //  SampleName.push_back( "Wplusenu_2000M2250"    );
    //  SampleName.push_back( "Wplusenu_2250M2500"    );
    //  SampleName.push_back( "Wplusenu_2500M2750"    );
    //  SampleName.push_back( "Wplusenu_2750M3000"    );
    //  SampleName.push_back( "Wplusenu_3000M3500"    );
    //  SampleName.push_back( "Wplusenu_3500M4000"    );
    //  SampleName.push_back( "Wplusenu_4000M4500"    );
    //  SampleName.push_back( "Wplusenu_4500M5000"    );
    //  SampleName.push_back( "Wplusenu_5000M"        );
    //  SampleName.push_back( "Wminenu_120M180"       );
    //  SampleName.push_back( "Wminenu_180M250"       );
    //  SampleName.push_back( "Wminenu_250M400"       );
    //  SampleName.push_back( "Wminenu_400M600"       );
    //  SampleName.push_back( "Wminenu_600M800"       );
    //  SampleName.push_back( "Wminenu_800M1000"      );
    //  SampleName.push_back( "Wminenu_1000M1250"     );
    //  SampleName.push_back( "Wminenu_1250M1500"     );
    //  SampleName.push_back( "Wminenu_1500M1750"     );
    //  SampleName.push_back( "Wminenu_1750M2000"     );
    //  SampleName.push_back( "Wminenu_2000M2250"     );
    //  SampleName.push_back( "Wminenu_2250M2500"     );
    //  SampleName.push_back( "Wminenu_2500M2750"     );
    //  SampleName.push_back( "Wminenu_2750M3000"     );
    //  SampleName.push_back( "Wminenu_3000M3500"     );
    //  SampleName.push_back( "Wminenu_3500M4000"     );
    //  SampleName.push_back( "Wminenu_4000M4500"     );
    //  SampleName.push_back( "Wminenu_4500M5000"     );
    //  SampleName.push_back( "Wminenu_5000M"         );
    //  SampleName.push_back( "Wplusmunu_120M180"     );
    //  SampleName.push_back( "Wplusmunu_180M250"     );
    //  SampleName.push_back( "Wplusmunu_250M400"     );
    //  SampleName.push_back( "Wplusmunu_400M600"     );
    //  SampleName.push_back( "Wplusmunu_600M800"     );
    //  SampleName.push_back( "Wplusmunu_800M1000"    );
    //  SampleName.push_back( "Wplusmunu_1000M1250"   );
    //  SampleName.push_back( "Wplusmunu_1250M1500"   );
    //  SampleName.push_back( "Wplusmunu_1500M1750"   );
    //  SampleName.push_back( "Wplusmunu_1750M2000"   );
    //  SampleName.push_back( "Wplusmunu_2000M2250"   );
    //  SampleName.push_back( "Wplusmunu_2250M2500"   );
    //  SampleName.push_back( "Wplusmunu_2500M2750"   );
    //  SampleName.push_back( "Wplusmunu_2750M3000"   );
    //  SampleName.push_back( "Wplusmunu_3000M3500"   );
    //  SampleName.push_back( "Wplusmunu_3500M4000"   );
    //  SampleName.push_back( "Wplusmunu_4000M4500"   );
    //  SampleName.push_back( "Wplusmunu_4500M5000"   );
    //  SampleName.push_back( "Wplusmunu_5000M"       );
    //  SampleName.push_back( "Wminmunu_120M180"      );
    //  SampleName.push_back( "Wminmunu_180M250"      );
    //  SampleName.push_back( "Wminmunu_250M400"      );
    //  SampleName.push_back( "Wminmunu_400M600"      );
    //  SampleName.push_back( "Wminmunu_600M800"      );
    //  SampleName.push_back( "Wminmunu_800M1000"     );
    //  SampleName.push_back( "Wminmunu_1000M1250"    );
    //  SampleName.push_back( "Wminmunu_1250M1500"    );
    //  SampleName.push_back( "Wminmunu_1500M1750"    );
    //  SampleName.push_back( "Wminmunu_1750M2000"    );
    //  SampleName.push_back( "Wminmunu_2000M2250"    );
    //  SampleName.push_back( "Wminmunu_2250M2500"    );
    //  SampleName.push_back( "Wminmunu_2500M2750"    );
    //  SampleName.push_back( "Wminmunu_2750M3000"    );
    //  SampleName.push_back( "Wminmunu_3000M3500"    );
    //  SampleName.push_back( "Wminmunu_3500M4000"    );
    //  SampleName.push_back( "Wminmunu_4000M4500"    );
    //  SampleName.push_back( "Wminmunu_4500M5000"    );
    //  SampleName.push_back( "Wminmunu_5000M"        );
    //  SampleName.push_back( "Wplustaunu_120M180"    );
    //  SampleName.push_back( "Wplustaunu_180M250"    );
    //  SampleName.push_back( "Wplustaunu_250M400"    );
    //  SampleName.push_back( "Wplustaunu_400M600"    );
    //  SampleName.push_back( "Wplustaunu_600M800"    );
    //  SampleName.push_back( "Wplustaunu_800M1000"   );
    //  SampleName.push_back( "Wplustaunu_1000M1250"  );
    //  SampleName.push_back( "Wplustaunu_1250M1500"  );
    //  SampleName.push_back( "Wplustaunu_1500M1750"  );
    //  SampleName.push_back( "Wplustaunu_1750M2000"  );
    //  SampleName.push_back( "Wplustaunu_2000M2250"  );
    //  SampleName.push_back( "Wplustaunu_2250M2500"  );
    //  SampleName.push_back( "Wplustaunu_2500M2750"  );
    //  SampleName.push_back( "Wplustaunu_2750M3000"  );
    //  SampleName.push_back( "Wplustaunu_3000M3500"  );
    //  SampleName.push_back( "Wplustaunu_3500M4000"  );
    //  SampleName.push_back( "Wplustaunu_4000M4500"  );
    //  SampleName.push_back( "Wplustaunu_4500M5000"  );
    //  SampleName.push_back( "Wplustaunu_5000M"      );
    //  SampleName.push_back( "Wmintaunu_120M180"     );
    //  SampleName.push_back( "Wmintaunu_180M250"     );
    //  SampleName.push_back( "Wmintaunu_250M400"     );
    //  SampleName.push_back( "Wmintaunu_400M600"     );
    //  SampleName.push_back( "Wmintaunu_600M800"     );
    //  SampleName.push_back( "Wmintaunu_800M1000"    );
    //  SampleName.push_back( "Wmintaunu_1000M1250"   );
    //  SampleName.push_back( "Wmintaunu_1250M1500"   );
    //  SampleName.push_back( "Wmintaunu_1500M1750"   );
    //  SampleName.push_back( "Wmintaunu_1750M2000"   );
    //  SampleName.push_back( "Wmintaunu_2000M2250"   );
    //  SampleName.push_back( "Wmintaunu_2250M2500"   );
    //  SampleName.push_back( "Wmintaunu_2500M2750"   );
    //  SampleName.push_back( "Wmintaunu_2750M3000"   );
    //  SampleName.push_back( "Wmintaunu_3000M3500"   );
    //  SampleName.push_back( "Wmintaunu_3500M4000"   );
    //  SampleName.push_back( "Wmintaunu_4000M4500"   );
    //  SampleName.push_back( "Wmintaunu_4500M5000"   );
    //  SampleName.push_back( "Wmintaunu_5000M"       );
    //}
  }
  
  /* Backgrounds for Syst Unc. */
  if(sample=="Syst"){
    SampleName.push_back( "DiBoson_llll"         );
    SampleName.push_back( "DiBoson_lllvOFMinus"  );
    SampleName.push_back( "DiBoson_lllvOFPlus"   );
    SampleName.push_back( "DiBoson_lllvSFMinus"  );
    SampleName.push_back( "DiBoson_lllvSFPlus"   );
    //SampleName.push_back( "DiBoson_WplvWmqq"     );
    //SampleName.push_back( "DiBoson_WpqqWmlv"     );
    //SampleName.push_back( "DiBoson_WlvZqq"       );
    //SampleName.push_back( "DiBoson_WqqZll"       );
    //SampleName.push_back( "DiBoson_WqqZvv"       );
    //SampleName.push_back( "DiBoson_ZqqZll"       );
    SampleName.push_back( "DiBoson_evmuv_0M150"        );
    SampleName.push_back( "DiBoson_evmuv_150M500"      );
    SampleName.push_back( "DiBoson_evmuv_500M1000"     );
    SampleName.push_back( "DiBoson_evmuv_1000M2000"    );
    SampleName.push_back( "DiBoson_evmuv_2000M3000"    );
    SampleName.push_back( "DiBoson_evmuv_3000M4000"    );
    SampleName.push_back( "DiBoson_evmuv_4000M5000"    );
    SampleName.push_back( "DiBoson_evmuv_M5000"        );
    SampleName.push_back( "DiBoson_evtauv_0M150"       );
    SampleName.push_back( "DiBoson_evtauv_150M500"     );
    SampleName.push_back( "DiBoson_evtauv_500M1000"    );
    SampleName.push_back( "DiBoson_evtauv_1000M2000"   );
    SampleName.push_back( "DiBoson_evtauv_2000M3000"   );
    SampleName.push_back( "DiBoson_evtauv_3000M4000"   );
    SampleName.push_back( "DiBoson_evtauv_4000M5000"   );
    SampleName.push_back( "DiBoson_evtauv_M5000"       );
    SampleName.push_back( "DiBoson_muvtauv_0M150"      );
    SampleName.push_back( "DiBoson_muvtauv_150M500"    );
    SampleName.push_back( "DiBoson_muvtauv_500M1000"   );
    SampleName.push_back( "DiBoson_muvtauv_1000M2000"  );
    SampleName.push_back( "DiBoson_muvtauv_2000M3000"  );
    SampleName.push_back( "DiBoson_muvtauv_3000M4000"  );
    SampleName.push_back( "DiBoson_muvtauv_4000M5000"  );
    SampleName.push_back( "DiBoson_muvtauv_M5000"      );
    SampleName.push_back( "DiBoson_tauvtauv_0M150"     );
    SampleName.push_back( "DiBoson_tauvtauv_150M500"   );
    SampleName.push_back( "DiBoson_tauvtauv_500M1000"  );
    SampleName.push_back( "DiBoson_tauvtauv_1000M2000" );
    SampleName.push_back( "DiBoson_tauvtauv_2000M3000" );
    SampleName.push_back( "DiBoson_tauvtauv_3000M4000" );
    SampleName.push_back( "DiBoson_tauvtauv_4000M5000" );
    SampleName.push_back( "DiBoson_tauvtauv_M5000"     );
    SampleName.push_back( "Ztautau" );
    SampleName.push_back( "DYtautau_120M180"   );
    SampleName.push_back( "DYtautau_180M250"   );
    SampleName.push_back( "DYtautau_250M400"   );
    SampleName.push_back( "DYtautau_400M600"   );
    SampleName.push_back( "DYtautau_600M800"   );
    SampleName.push_back( "DYtautau_800M1000"  );
    SampleName.push_back( "DYtautau_1000M1250" );
    SampleName.push_back( "DYtautau_1250M1500" );
    SampleName.push_back( "DYtautau_1500M1750" );
    SampleName.push_back( "DYtautau_1750M2000" );
    SampleName.push_back( "DYtautau_2000M2250" );
    SampleName.push_back( "DYtautau_2250M2500" );
    SampleName.push_back( "DYtautau_2500M2750" );
    SampleName.push_back( "DYtautau_2750M3000" );
    SampleName.push_back( "DYtautau_3000M3500" );
    SampleName.push_back( "DYtautau_3500M4000" );
    SampleName.push_back( "DYtautau_4000M4500" );
    SampleName.push_back( "DYtautau_4500M5000" );
    SampleName.push_back( "DYtautau_5000M"     );
    //SampleName.push_back( "DYee_70M120"        );
    SampleName.push_back( "Zee" );
    SampleName.push_back( "DYee_120M180"       );
    SampleName.push_back( "DYee_180M250"       );
    SampleName.push_back( "DYee_250M400"       );
    SampleName.push_back( "DYee_400M600"       );
    SampleName.push_back( "DYee_600M800"       );
    SampleName.push_back( "DYee_800M1000"      );
    SampleName.push_back( "DYee_1000M1250"     );
    SampleName.push_back( "DYee_1250M1500"     );
    SampleName.push_back( "DYee_1500M1750"     );
    SampleName.push_back( "DYee_1750M2000"     );
    SampleName.push_back( "DYee_2000M2250"     );
    SampleName.push_back( "DYee_2250M2500"     );
    SampleName.push_back( "DYee_2500M2750"     );
    SampleName.push_back( "DYee_2750M3000"     );
    SampleName.push_back( "DYee_3000M3500"     );
    SampleName.push_back( "DYee_3500M4000"     );
    SampleName.push_back( "DYee_4000M4500"     );
    SampleName.push_back( "DYee_4500M5000"     );
    SampleName.push_back( "DYee_5000M"         );
    //SampleName.push_back( "DYmumu_70M120"      );
    SampleName.push_back( "Zmumu"              );
    SampleName.push_back( "DYmumu_120M180"     );
    SampleName.push_back( "DYmumu_180M250"     );
    //SampleName.push_back( "DYmumu_250M400"     );
    SampleName.push_back( "DYmumu_400M600"     );
    SampleName.push_back( "DYmumu_600M800"     );
    SampleName.push_back( "DYmumu_800M1000"    );
    SampleName.push_back( "DYmumu_1000M1250"   );
    SampleName.push_back( "DYmumu_1250M1500"   );
    SampleName.push_back( "DYmumu_1500M1750"   );
    SampleName.push_back( "DYmumu_1750M2000"   );
    SampleName.push_back( "DYmumu_2000M2250"   );
    SampleName.push_back( "DYmumu_2250M2500"   );
    SampleName.push_back( "DYmumu_2500M2750"   );
    SampleName.push_back( "DYmumu_2750M3000"   );
    SampleName.push_back( "DYmumu_3000M3500"   );
    SampleName.push_back( "DYmumu_3500M4000"   );
    SampleName.push_back( "DYmumu_4000M4500"   );
    SampleName.push_back( "DYmumu_4500M5000"   );
    SampleName.push_back( "DYmumu_5000M"       );
    SampleName.push_back( "ttbar_incl" ); //to be removed
    SampleName.push_back( "Wt_antitop" );
    SampleName.push_back( "Wt_top"     );

    //if(LFVtype!=1){
    //  SampleName.push_back( "Wminusmunu"  );		
    //  SampleName.push_back( "Wminustaunu" );		
    //  SampleName.push_back( "Wminusenu"   );		
    //  SampleName.push_back( "Wplusmunu"   );		
    //  SampleName.push_back( "Wplustaunu"  );		
    //  SampleName.push_back( "Wplusenu"    );		
    //  SampleName.push_back( "Wplusenu_120M180"      );
    //  SampleName.push_back( "Wplusenu_180M250"      );
    //  SampleName.push_back( "Wplusenu_250M400"      );
    //  SampleName.push_back( "Wplusenu_400M600"      );
    //  SampleName.push_back( "Wplusenu_600M800"      );
    //  SampleName.push_back( "Wplusenu_800M1000"     );
    //  SampleName.push_back( "Wplusenu_1000M1250"    );
    //  SampleName.push_back( "Wplusenu_1250M1500"    );
    //  SampleName.push_back( "Wplusenu_1500M1750"    );
    //  SampleName.push_back( "Wplusenu_1750M2000"    );
    //  SampleName.push_back( "Wplusenu_2000M2250"    );
    //  SampleName.push_back( "Wplusenu_2250M2500"    );
    //  SampleName.push_back( "Wplusenu_2500M2750"    );
    //  SampleName.push_back( "Wplusenu_2750M3000"    );
    //  SampleName.push_back( "Wplusenu_3000M3500"    );
    //  SampleName.push_back( "Wplusenu_3500M4000"    );
    //  SampleName.push_back( "Wplusenu_4000M4500"    );
    //  SampleName.push_back( "Wplusenu_4500M5000"    );
    //  SampleName.push_back( "Wplusenu_5000M"        );
    //  SampleName.push_back( "Wminenu_120M180"       );
    //  SampleName.push_back( "Wminenu_180M250"       );
    //  SampleName.push_back( "Wminenu_250M400"       );
    //  SampleName.push_back( "Wminenu_400M600"       );
    //  SampleName.push_back( "Wminenu_600M800"       );
    //  SampleName.push_back( "Wminenu_800M1000"      );
    //  SampleName.push_back( "Wminenu_1000M1250"     );
    //  SampleName.push_back( "Wminenu_1250M1500"     );
    //  SampleName.push_back( "Wminenu_1500M1750"     );
    //  SampleName.push_back( "Wminenu_1750M2000"     );
    //  SampleName.push_back( "Wminenu_2000M2250"     );
    //  SampleName.push_back( "Wminenu_2250M2500"     );
    //  SampleName.push_back( "Wminenu_2500M2750"     );
    //  SampleName.push_back( "Wminenu_2750M3000"     );
    //  SampleName.push_back( "Wminenu_3000M3500"     );
    //  SampleName.push_back( "Wminenu_3500M4000"     );
    //  SampleName.push_back( "Wminenu_4000M4500"     );
    //  SampleName.push_back( "Wminenu_4500M5000"     );
    //  SampleName.push_back( "Wminenu_5000M"         );
    //  SampleName.push_back( "Wplusmunu_120M180"     );
    //  SampleName.push_back( "Wplusmunu_180M250"     );
    //  SampleName.push_back( "Wplusmunu_250M400"     );
    //  SampleName.push_back( "Wplusmunu_400M600"     );
    //  SampleName.push_back( "Wplusmunu_600M800"     );
    //  SampleName.push_back( "Wplusmunu_800M1000"    );
    //  SampleName.push_back( "Wplusmunu_1000M1250"   );
    //  SampleName.push_back( "Wplusmunu_1250M1500"   );
    //  SampleName.push_back( "Wplusmunu_1500M1750"   );
    //  SampleName.push_back( "Wplusmunu_1750M2000"   );
    //  SampleName.push_back( "Wplusmunu_2000M2250"   );
    //  SampleName.push_back( "Wplusmunu_2250M2500"   );
    //  SampleName.push_back( "Wplusmunu_2500M2750"   );
    //  SampleName.push_back( "Wplusmunu_2750M3000"   );
    //  SampleName.push_back( "Wplusmunu_3000M3500"   );
    //  SampleName.push_back( "Wplusmunu_3500M4000"   );
    //  SampleName.push_back( "Wplusmunu_4000M4500"   );
    //  SampleName.push_back( "Wplusmunu_4500M5000"   );
    //  SampleName.push_back( "Wplusmunu_5000M"       );
    //  SampleName.push_back( "Wminmunu_120M180"      );
    //  SampleName.push_back( "Wminmunu_180M250"      );
    //  SampleName.push_back( "Wminmunu_250M400"      );
    //  SampleName.push_back( "Wminmunu_400M600"      );
    //  SampleName.push_back( "Wminmunu_600M800"      );
    //  SampleName.push_back( "Wminmunu_800M1000"     );
    //  SampleName.push_back( "Wminmunu_1000M1250"    );
    //  SampleName.push_back( "Wminmunu_1250M1500"    );
    //  SampleName.push_back( "Wminmunu_1500M1750"    );
    //  SampleName.push_back( "Wminmunu_1750M2000"    );
    //  SampleName.push_back( "Wminmunu_2000M2250"    );
    //  SampleName.push_back( "Wminmunu_2250M2500"    );
    //  SampleName.push_back( "Wminmunu_2500M2750"    );
    //  SampleName.push_back( "Wminmunu_2750M3000"    );
    //  SampleName.push_back( "Wminmunu_3000M3500"    );
    //  SampleName.push_back( "Wminmunu_3500M4000"    );
    //  SampleName.push_back( "Wminmunu_4000M4500"    );
    //  SampleName.push_back( "Wminmunu_4500M5000"    );
    //  SampleName.push_back( "Wminmunu_5000M"        );
    //  SampleName.push_back( "Wplustaunu_120M180"    );
    //  SampleName.push_back( "Wplustaunu_180M250"    );
    //  SampleName.push_back( "Wplustaunu_250M400"    );
    //  SampleName.push_back( "Wplustaunu_400M600"    );
    //  SampleName.push_back( "Wplustaunu_600M800"    );
    //  SampleName.push_back( "Wplustaunu_800M1000"   );
    //  SampleName.push_back( "Wplustaunu_1000M1250"  );
    //  SampleName.push_back( "Wplustaunu_1250M1500"  );
    //  SampleName.push_back( "Wplustaunu_1500M1750"  );
    //  SampleName.push_back( "Wplustaunu_1750M2000"  );
    //  SampleName.push_back( "Wplustaunu_2000M2250"  );
    //  SampleName.push_back( "Wplustaunu_2250M2500"  );
    //  SampleName.push_back( "Wplustaunu_2500M2750"  );
    //  SampleName.push_back( "Wplustaunu_2750M3000"  );
    //  SampleName.push_back( "Wplustaunu_3000M3500"  );
    //  SampleName.push_back( "Wplustaunu_3500M4000"  );
    //  SampleName.push_back( "Wplustaunu_4000M4500"  );
    //  SampleName.push_back( "Wplustaunu_4500M5000"  );
    //  SampleName.push_back( "Wplustaunu_5000M"      );
    //  SampleName.push_back( "Wmintaunu_120M180"     );
    //  SampleName.push_back( "Wmintaunu_180M250"     );
    //  SampleName.push_back( "Wmintaunu_250M400"     );
    //  SampleName.push_back( "Wmintaunu_400M600"     );
    //  SampleName.push_back( "Wmintaunu_600M800"     );
    //  SampleName.push_back( "Wmintaunu_800M1000"    );
    //  SampleName.push_back( "Wmintaunu_1000M1250"   );
    //  SampleName.push_back( "Wmintaunu_1250M1500"   );
    //  SampleName.push_back( "Wmintaunu_1500M1750"   );
    //  SampleName.push_back( "Wmintaunu_1750M2000"   );
    //  SampleName.push_back( "Wmintaunu_2000M2250"   );
    //  SampleName.push_back( "Wmintaunu_2250M2500"   );
    //  SampleName.push_back( "Wmintaunu_2500M2750"   );
    //  SampleName.push_back( "Wmintaunu_2750M3000"   );
    //  SampleName.push_back( "Wmintaunu_3000M3500"   );
    //  SampleName.push_back( "Wmintaunu_3500M4000"   );
    //  SampleName.push_back( "Wmintaunu_4000M4500"   );
    //  SampleName.push_back( "Wmintaunu_4500M5000"   );
    //  SampleName.push_back( "Wmintaunu_5000M"       );
    //}
  }
  
  /* Histos Bins Setting */
  int mllBins = 80;
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
  
  int EtallBins = 56; Double_t EtallWd = 10;
  int PhiBins   = 20; Double_t PhiWd   = TMath::Pi();
  int MetBins   = 25; Double_t MetMax  = 1000.;
  int NjetBins  = 20; Double_t NjetMax = 20;
  int EtaBins   = 16; Double_t EtaWd   = 2.5;
  
  /* mll histos */
  TH1F *hmll = new TH1F(("hmll_"+sample).c_str(),
			("hmll_"+sample).c_str(),
			mllBins, mllX);
  hmll->GetXaxis()->SetTitle( ("m_{"+lfvType+"} [GeV]").c_str() );

  TH1F *hmllCorr = new TH1F(("hmllCorr_"+sample).c_str(),
			    ("hmllCorr_"+sample).c_str(),
			    mllBins, mllX);
  hmllCorr->GetXaxis()->SetTitle( ("m_{"+lfvType+"} [GeV]").c_str() );

  TH1F *hptll = new TH1F(("hptll_"+sample).c_str(),
			 ("hptll_"+sample).c_str(),
			 ptllBins, ptllX);
  hptll->GetXaxis()->SetTitle( ("p_{T}^{"+lfvType+"} [GeV]").c_str() );
  
  TH1F *hptllCorr = new TH1F(("hptllCorr_"+sample).c_str(),
			     ("hptllCorr_"+sample).c_str(),
			     ptllBins, ptllX);
  hptllCorr->GetXaxis()->SetTitle( ("p_{T}^{"+lfvType+"} [GeV]").c_str() );
  
  TH1F *hetall = new TH1F(("hetall_"+sample).c_str(),
			  ("hetall_"+sample).c_str(),
			  EtallBins, -EtallWd, EtallWd);
  hetall->GetXaxis()->SetTitle( ("#eta_{"+lfvType+"}").c_str() );
  
  TH1F *hphill = new TH1F(("hphill_"+sample).c_str(),
			  ("hphill_"+sample).c_str(),
			  PhiBins, -PhiWd, PhiWd);
  hphill->GetXaxis()->SetTitle( ("#phi_{"+lfvType+"}").c_str() );

  TH1F *hmet = new TH1F(("hmet_"+sample).c_str(),
			("hmet_"+sample).c_str(),
			MetBins, 0, MetMax);
  hmet->GetXaxis()->SetTitle( "E_{T}^{miss} [GeV]" );

  TH1F *hnjet   = new TH1F(("hnjet_"+sample).c_str(),
                           ("hnjet_"+sample).c_str(),
                           NjetBins, 0, NjetMax);
  hnjet->GetXaxis()->SetTitle("N_{jets}");
  
  /* Muon histos */
  TH1F *hmu_pt = new TH1F(("hmu_pt_"+sample).c_str(),
			  ("hmu_pt_"+sample).c_str(),
			  ptBins, ptX);
  hmu_pt->GetXaxis()->SetTitle("p_{T}^{#mu} [GeV]");
  
  TH1F *hmu_eta = new TH1F(("hmu_eta_"+sample).c_str(),
			   ("hmu_eta_"+sample).c_str(),
			   EtaBins, -EtaWd, EtaWd);
  hmu_eta->GetXaxis()->SetTitle("#eta_{#mu}");

  TH1F *hmu_phi = new TH1F(("hmu_phi_"+sample).c_str(),
			   ("hmu_phi_"+sample).c_str(),
			   PhiBins, -PhiWd, PhiWd);
  hmu_phi->GetXaxis()->SetTitle("#phi_{#mu}");
  
  /* Electron histos */
  TH1F *hel_pt = new TH1F(("hel_pt_"+sample).c_str(),
			  ("hel_pt_"+sample).c_str(),
			  ptBins, ptX);
  hel_pt->GetXaxis()->SetTitle("p_{T}^{e} [GeV]");
  
  TH1F *hel_eta = new TH1F(("hel_eta_"+sample).c_str(),
			   ("hel_eta_"+sample).c_str(),
			   EtaBins, -EtaWd, EtaWd);
  hel_eta->GetXaxis()->SetTitle("#eta_{e}");
  
  TH1F *hel_phi = new TH1F(("hel_phi_"+sample).c_str(),
			   ("hel_phi_"+sample).c_str(),
			   PhiBins, -PhiWd, PhiWd);
  hel_phi->GetXaxis()->SetTitle("#phi_{e}");

  /* Tau histos */
  TH1F *hta_pt = new TH1F(("hta_pt_"+sample).c_str(),
			  ("hta_pt_"+sample).c_str(),
			  ptBins, ptX);
  hta_pt->GetXaxis()->SetTitle("p_{T}^{#tau} [GeV]");
  
  TH1F *hta_eta = new TH1F(("hta_eta_"+sample).c_str(),
			   ("hta_eta_"+sample).c_str(),
			   EtaBins, -EtaWd, EtaWd);
  hta_eta->GetXaxis()->SetTitle("#eta_{#tau}");
  
  TH1F *hta_phi = new TH1F(("hta_phi_"+sample).c_str(),
			   ("hta_phi_"+sample).c_str(),
			   PhiBins, -PhiWd, PhiWd);
  hta_phi->GetXaxis()->SetTitle("#phi_{#tau}");

  /* PDF Var Histos */
  TH1F *hmll_PDF = new TH1F(("hmll_PDF_"+sample).c_str(),
                            ("hmll_PDF_"+sample).c_str(),
                            mllBins, mllX);
  hmll_PDF->GetXaxis()->SetTitle( ("m_{"+lfvType+"} [GeV]").c_str() );

  TH1F *hmllCorr_PDF = new TH1F(("hmllCorr_PDF_"+sample).c_str(),
                                ("hmllCorr_PDF_"+sample).c_str(),
                                mllBins, mllX);
  hmllCorr_PDF->GetXaxis()->SetTitle( ("m_{"+lfvType+"} [GeV]").c_str() );

  TH1F *hptll_PDF = new TH1F(("hptll_PDF_"+sample).c_str(),
                             ("hptll_PDF_"+sample).c_str(),
                             ptllBins, ptllX);
  hptll_PDF->GetXaxis()->SetTitle( ("p_{T}^{"+lfvType+"} [GeV]").c_str() );

  TH1F *hptllCorr_PDF = new TH1F(("hptllCorr_PDF_"+sample).c_str(),
                                 ("hptllCorr_PDF_"+sample).c_str(),
                                 ptllBins, ptllX);
  hptllCorr_PDF->GetXaxis()->SetTitle( ("p_{T}^{"+lfvType+"} [GeV]").c_str() );

  TH1F *hetall_PDF = new TH1F(("hetall_PDF_"+sample).c_str(),
                              ("hetall_PDF_"+sample).c_str(),
                              EtallBins, -EtallWd, EtallWd);
  hetall_PDF->GetXaxis()->SetTitle( ("#eta_{"+lfvType+"}").c_str() );

  TH1F *hphill_PDF = new TH1F(("hphill_PDF_"+sample).c_str(),
			      ("hphill_PDF_"+sample).c_str(),
			      PhiBins, -PhiWd, PhiWd);
  hphill_PDF->GetXaxis()->SetTitle( ("#phi_{"+lfvType+"}").c_str() );

  TH1F *hmet_PDF = new TH1F(("hmet_PDF_"+sample).c_str(),
			    ("hmet_PDF_"+sample).c_str(),
			    MetBins, 0, MetMax);
  hmet_PDF->GetXaxis()->SetTitle( "E_{T}^{miss} [GeV]" );
  
  TH1F *hnjet_PDF = new TH1F(("hnjet_PDF_"+sample).c_str(),
			     ("hnjet_PDF_"+sample).c_str(),
			     NjetBins, 0, NjetMax);
  hnjet_PDF->GetXaxis()->SetTitle("N_{jets}");

  TH1F *hmu_pt_PDF = new TH1F(("hmu_pt_PDF_"+sample).c_str(),
			      ("hmu_pt_PDF_"+sample).c_str(),
			      ptBins, ptX);
  hmu_pt_PDF->GetXaxis()->SetTitle("p_{T}^{#mu} [GeV]");

  TH1F *hmu_eta_PDF = new TH1F(("hmu_eta_PDF_"+sample).c_str(),
			       ("hmu_eta_PDF_"+sample).c_str(),
			       EtaBins, -EtaWd, EtaWd);
  hmu_eta_PDF->GetXaxis()->SetTitle("#eta_{#mu}");

  TH1F *hmu_phi_PDF = new TH1F(("hmu_phi_PDF_"+sample).c_str(),
			       ("hmu_phi_PDF_"+sample).c_str(),
			       PhiBins, -PhiWd, PhiWd);
  hmu_phi_PDF->GetXaxis()->SetTitle("#phi_{#mu}");

  TH1F *hel_pt_PDF = new TH1F(("hel_pt_PDF_"+sample).c_str(),
			      ("hel_pt_PDF_"+sample).c_str(),
			      ptBins, ptX);
  hel_pt_PDF->GetXaxis()->SetTitle("p_{T}^{e} [GeV]");

  TH1F *hel_eta_PDF = new TH1F(("hel_eta_PDF_"+sample).c_str(),
			       ("hel_eta_PDF_"+sample).c_str(),
			       EtaBins, -EtaWd, EtaWd);
  hel_eta_PDF->GetXaxis()->SetTitle("#eta_{e}");

  TH1F *hel_phi_PDF = new TH1F(("hel_phi_PDF_"+sample).c_str(),
			       ("hel_phi_PDF_"+sample).c_str(),
			       PhiBins, -PhiWd, PhiWd);
  hel_phi_PDF->GetXaxis()->SetTitle("#phi_{e}");

  TH1F *hta_pt_PDF = new TH1F(("hta_pt_PDF_"+sample).c_str(),
			     ("hta_pt_PDF_"+sample).c_str(),
			     ptBins, ptX);
  hta_pt_PDF->GetXaxis()->SetTitle("p_{T}^{#tau} [GeV]");

  TH1F *hta_eta_PDF = new TH1F(("hta_eta_PDF_"+sample).c_str(),
			       ("hta_eta_PDF_"+sample).c_str(),
			       EtaBins, -EtaWd, EtaWd);
  hta_eta_PDF->GetXaxis()->SetTitle("#eta_{#tau}");

  TH1F *hta_phi_PDF = new TH1F(("hta_phi_PDF_"+sample).c_str(),
			       ("hta_phi_PDF_"+sample).c_str(),
			       PhiBins, -PhiWd, PhiWd);
  hta_phi_PDF->GetXaxis()->SetTitle("#phi_{#tau}");

  /* SCALE Var Histos */
  TH1F *hmll_SCALE = new TH1F(("hmll_SCALE_"+sample).c_str(),
			      ("hmll_SCALE_"+sample).c_str(),
			      mllBins, mllX);
  hmll_SCALE->GetXaxis()->SetTitle( ("m_{"+lfvType+"} [GeV]").c_str() );

  TH1F *hmllCorr_SCALE = new TH1F(("hmllCorr_SCALE_"+sample).c_str(),
				  ("hmllCorr_SCALE_"+sample).c_str(),
				  mllBins, mllX);
  hmllCorr_SCALE->GetXaxis()->SetTitle( ("m_{"+lfvType+"} [GeV]").c_str() );

  TH1F *hptll_SCALE = new TH1F(("hptll_SCALE_"+sample).c_str(),
			       ("hptll_SCALE_"+sample).c_str(),
			       ptllBins, ptllX);
  hptll_SCALE->GetXaxis()->SetTitle( ("p_{T}^{"+lfvType+"} [GeV]").c_str() );

  TH1F *hptllCorr_SCALE = new TH1F(("hptllCorr_SCALE_"+sample).c_str(),
				   ("hptllCorr_SCALE_"+sample).c_str(),
				   ptllBins, ptllX);
  hptllCorr_SCALE->GetXaxis()->SetTitle( ("p_{T}^{"+lfvType+"} [GeV]").c_str() );

  TH1F *hetall_SCALE = new TH1F(("hetall_SCALE_"+sample).c_str(),
				("hetall_SCALE_"+sample).c_str(),
				EtallBins, -EtallWd, EtallWd);
  hetall_SCALE->GetXaxis()->SetTitle( ("#eta_{"+lfvType+"}").c_str() );

  TH1F *hphill_SCALE = new TH1F(("hphill_SCALE_"+sample).c_str(),
				("hphill_SCALE_"+sample).c_str(),
				PhiBins, -PhiWd, PhiWd);
  hphill_SCALE->GetXaxis()->SetTitle( ("#phi_{"+lfvType+"}").c_str() );

  TH1F *hmet_SCALE = new TH1F(("hmet_SCALE_"+sample).c_str(),
			      ("hmet_SCALE_"+sample).c_str(),
			      MetBins, 0, MetMax);
  hmet_SCALE->GetXaxis()->SetTitle( "E_{T}^{miss} [GeV]" );

  TH1F *hnjet_SCALE = new TH1F(("hnjet_SCALE_"+sample).c_str(),
			       ("hnjet_SCALE_"+sample).c_str(),
			       NjetBins, 0, NjetMax);
  hnjet_SCALE->GetXaxis()->SetTitle("N_{jets}");

  TH1F *hmu_pt_SCALE = new TH1F(("hmu_pt_SCALE_"+sample).c_str(),
				("hmu_pt_SCALE_"+sample).c_str(),
				ptBins, ptX);
  hmu_pt_SCALE->GetXaxis()->SetTitle("p_{T}^{#mu} [GeV]");

  TH1F *hmu_eta_SCALE = new TH1F(("hmu_eta_SCALE_"+sample).c_str(),
				 ("hmu_eta_SCALE_"+sample).c_str(),
				 EtaBins, -EtaWd, EtaWd);
  hmu_eta_SCALE->GetXaxis()->SetTitle("#eta_{#mu}");

  TH1F *hmu_phi_SCALE = new TH1F(("hmu_phi_SCALE_"+sample).c_str(),
				 ("hmu_phi_SCALE_"+sample).c_str(),
				 PhiBins, -PhiWd, PhiWd);
  hmu_phi_SCALE->GetXaxis()->SetTitle("#phi_{#mu}");
  
  TH1F *hel_pt_SCALE = new TH1F(("hel_pt_SCALE_"+sample).c_str(),
				("hel_pt_SCALE_"+sample).c_str(),
				ptBins, ptX);
  hel_pt_SCALE->GetXaxis()->SetTitle("p_{T}^{e} [GeV]");

  TH1F *hel_eta_SCALE = new TH1F(("hel_eta_SCALE_"+sample).c_str(),
				 ("hel_eta_SCALE_"+sample).c_str(),
				 EtaBins, -EtaWd, EtaWd);
  hel_eta_SCALE->GetXaxis()->SetTitle("#eta_{e}");

  TH1F *hel_phi_SCALE = new TH1F(("hel_phi_SCALE_"+sample).c_str(),
				 ("hel_phi_SCALE_"+sample).c_str(),
				 PhiBins, -PhiWd, PhiWd);
  hel_phi_SCALE->GetXaxis()->SetTitle("#phi_{e}");

  TH1F *hta_pt_SCALE = new TH1F(("hta_pt_SCALE_"+sample).c_str(),
				("hta_pt_SCALE_"+sample).c_str(),
				ptBins, ptX);
  hta_pt_SCALE->GetXaxis()->SetTitle("p_{T}^{#tau} [GeV]");

  TH1F *hta_eta_SCALE = new TH1F(("hta_eta_SCALE_"+sample).c_str(),
				 ("hta_eta_SCALE_"+sample).c_str(),
				 EtaBins, -EtaWd, EtaWd);
  hta_eta_SCALE->GetXaxis()->SetTitle("#eta_{#tau}");

  TH1F *hta_phi_SCALE = new TH1F(("hta_phi_SCALE_"+sample).c_str(),
				 ("hta_phi_SCALE_"+sample).c_str(),
				 PhiBins, -PhiWd, PhiWd);
  hta_phi_SCALE->GetXaxis()->SetTitle("#phi_{#tau}");
  
  TFile *input, *out;
  std::string outname = "Plots_";
  if(sample=="data")
    out = new TFile( (outname+sysVar+"_"+lfvSt+".root").c_str(),"RECREATE");
  else
    out = new TFile( (outname+sysVar+"_"+lfvSt+".root").c_str(),"UPDATE");

  /* duplicates */
  std::set< std::pair<Int_t,ULong64_t> > EvtProcessed;
  
  for( int ch=0; ch<(int)SampleName.size(); ch++){

    std::cout<<"Sample "<<SampleName.at(ch)<<std::endl;
    EvtProcessed.clear();

    if(SampleName.at(ch)=="data")
      input = new TFile( (Dir+SampleName.at(ch)+".root").c_str() );
    else
      input = new TFile( (Dir+SampleName.at(ch)+".root").c_str() );


    double events = 1;
    int poswgt = 1;
    int negwgt = 1;
    
    if(SampleName.at(ch)!="data"){
      TH1F *info =  (TH1F*)input->Get("MCInfo");
      events = info->GetBinContent(2);
    }
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
    Double_t        weight;
    Double_t        weightWjetSF;
    Double_t        xsec;
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
    Bool_t          isBadJetEvt;
    vector<int>     *Lep_Id;
    vector<double>  *Lep_pt;
    vector<double>  *Lep_eta;
    vector<double>  *Lep_phi;
    vector<double>  *Lep_TrigSF;
    vector<double>  *Lep_RecoSF;
    vector<double>  *Lep_IDSF;
    vector<double>  *Lep_IsoSF;
    vector<double>  *Lep_TtvaSF;
    vector<double>  *Lep_L1CaloSF;
    vector<double>  *Lep_ElOlrSF;
    vector<int>     *Lep_nProngs;
    vector<double>  *Lep_TrigSF_StatUp;
    vector<double>  *Lep_TrigSF_StatDown;
    vector<double>  *Lep_TrigSF_SysUp;
    vector<double>  *Lep_TrigSF_SysDown;
    vector<double>  *Lep_RecoSF_StatUp;
    vector<double>  *Lep_RecoSF_StatDown;
    vector<double>  *Lep_RecoSF_SysUp;
    vector<double>  *Lep_RecoSF_SysDown;
    vector<double>  *Lep_RecoSF_Hpt_SysUp;
    vector<double>  *Lep_RecoSF_Hpt_SysDown;
    vector<double>  *Lep_IDSF_StatUp;
    vector<double>  *Lep_IDSF_StatDown;
    vector<double>  *Lep_IDSF_SysUp;
    vector<double>  *Lep_IDSF_SysDown;
    vector<double>  *Lep_IDSF_Hpt_SysUp;
    vector<double>  *Lep_IDSF_Hpt_SysDown;
    vector<double>  *Lep_IsoSF_StatUp;
    vector<double>  *Lep_IsoSF_StatDown;
    vector<double>  *Lep_IsoSF_SysUp;
    vector<double>  *Lep_IsoSF_SysDown;
    vector<double>  *Lep_TtvaSF_StatUp;
    vector<double>  *Lep_TtvaSF_StatDown;
    vector<double>  *Lep_TtvaSF_SysUp;
    vector<double>  *Lep_TtvaSF_SysDown;
    vector<double>  *Lep_ElOlrSF_SysUp;
    vector<double>  *Lep_ElOlrSF_SysDown;
    vector<double>  *Jet_pt;
    vector<double>  *Jet_eta;
    vector<double>  *Jet_phi;
    vector<double>  *Jet_JvtSF;
    vector<double>  *Jet_JvtSF_SysUp;
    vector<double>  *Jet_JvtSF_SysDown;
    vector<double>  *Jet_BtagSF;
    vector<double>  *Jet_BtagSF_Beff_SysUp;
    vector<double>  *Jet_BtagSF_Beff_SysDown;
    vector<double>  *Jet_BtagSF_Ceff_SysUp;
    vector<double>  *Jet_BtagSF_Ceff_SysDown;
    vector<double>  *Jet_BtagSF_Leff_SysUp;
    vector<double>  *Jet_BtagSF_Leff_SysDown;
    vector<double>  *Jet_BtagSF_ExtCeff_SysUp;
    vector<double>  *Jet_BtagSF_ExtCeff_SysDown;
    vector<double>  *Jet_BtagSF_ExtEff_SysUp;
    vector<double>  *Jet_BtagSF_ExtEff_SysDown;

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
    TBranch        *b_isBadJetEvt; //!
    TBranch        *b_mcweight;   //!
    TBranch        *b_weightWjetSF;   //!
    TBranch        *b_puweight;   //!
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

    TTree* InTree = (TTree*)input->Get( treename.c_str() );
    InTree->SetBranchStatus("*",1);

    dilepMass     = 0;
    dilepCorrMass = 0;
    dilepPt       = 0;
    dilepCorrPt   = 0;
    dilepEta      = 0;
    dilepPhi      = 0;
    weight        = 0;
    mcweight      = 0;
    weightWjetSF  = 0;
    puweight      = 0;
    Lep_Id        = 0;
    Lep_pt        = 0;
    Lep_eta       = 0;
    Lep_phi       = 0;
    Lep_nProngs   = 0;
    Lep_TrigSF             = 0;
    Lep_RecoSF             = 0;
    Lep_IDSF               = 0;
    Lep_IsoSF              = 0;
    Lep_TrigSF_StatUp      = 0;
    Lep_TrigSF_StatDown    = 0;
    Lep_TrigSF_SysUp       = 0;
    Lep_TrigSF_SysDown     = 0;
    Lep_RecoSF_StatUp      = 0;
    Lep_RecoSF_StatDown    = 0;
    Lep_RecoSF_SysUp       = 0;
    Lep_RecoSF_SysDown     = 0;
    Lep_RecoSF_Hpt_SysUp   = 0;
    Lep_RecoSF_Hpt_SysDown = 0;
    Lep_IDSF_StatUp        = 0;
    Lep_IDSF_StatDown      = 0;
    Lep_IDSF_SysUp         = 0;
    Lep_IDSF_SysDown       = 0;
    Lep_IDSF_Hpt_SysUp     = 0;
    Lep_IDSF_Hpt_SysDown   = 0;
    Lep_IsoSF_StatUp       = 0;
    Lep_IsoSF_StatDown     = 0;
    Lep_IsoSF_SysUp        = 0;
    Lep_IsoSF_SysDown      = 0;
    Lep_TtvaSF             = 0;
    Lep_TtvaSF_StatUp      = 0;
    Lep_TtvaSF_StatDown    = 0;
    Lep_TtvaSF_SysUp       = 0;
    Lep_TtvaSF_SysDown     = 0;
    Lep_L1CaloSF           = 0;
    Lep_ElOlrSF            = 0;
    Lep_ElOlrSF_SysUp      = 0;
    Lep_ElOlrSF_SysDown    = 0;
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

    InTree->SetBranchAddress("event", &event, &b_event);
    InTree->SetBranchAddress("run", &run, &b_run);
    InTree->SetBranchAddress("mcweight", &mcweight, &b_mcweight);
    InTree->SetBranchAddress("weightWjetSF", &weightWjetSF, &b_weightWjetSF);
    InTree->SetBranchAddress("puweight", &puweight, &b_puweight);
    InTree->SetBranchAddress("weight", &weight, &b_weight);
    InTree->SetBranchAddress("xsec", &xsec, &b_xsec);
    InTree->SetBranchAddress("met_px", &met_px, &b_met_px);
    InTree->SetBranchAddress("met_py", &met_py, &b_met_py);
    InTree->SetBranchAddress("met_phi", &met_phi, &b_met_phi);
    InTree->SetBranchAddress("met_et", &met_et, &b_met_et);
    InTree->SetBranchAddress("met_sumet", &met_sumet, &b_met_sumet);
    InTree->SetBranchAddress("channel", &channel, &b_channel);
    InTree->SetBranchAddress("dilepMass", &dilepMass, &b_dilepMass);
    InTree->SetBranchAddress("dilepCorrMass", &dilepCorrMass, &b_dilepCorrMass);
    InTree->SetBranchAddress("dilepPt", &dilepPt, &b_dilepPt);
    InTree->SetBranchAddress("dilepCorrPt", &dilepCorrPt, &b_dilepCorrPt);
    InTree->SetBranchAddress("dilepEta", &dilepEta, &b_dilepEta);
    InTree->SetBranchAddress("dilepPhi", &dilepPhi, &b_dilepPhi);
    InTree->SetBranchAddress("isTauContr", &isTauContr, &b_isTauContr);
    InTree->SetBranchAddress("isKeepEvent", &isKeepEvent, &b_isKeepEvent);
    InTree->SetBranchAddress("isBTBGood", &isBTBGood, &b_isBTBGood);
    InTree->SetBranchAddress("isOSGood", &isOSGood, &b_isOSGood);
    InTree->SetBranchAddress("isBjetEvt", &isBjetEvt, &b_isBjetEvt);
    InTree->SetBranchAddress("isBadJetEvt", &isBadJetEvt, &b_isBadJetEvt);
    InTree->SetBranchAddress("Lep_Id", &Lep_Id, &b_Lep_Id);
    InTree->SetBranchAddress("Lep_pt", &Lep_pt, &b_Lep_pt);
    InTree->SetBranchAddress("Lep_eta", &Lep_eta, &b_Lep_eta);
    InTree->SetBranchAddress("Lep_phi", &Lep_phi, &b_Lep_phi);
    InTree->SetBranchAddress("Lep_nProngs"  , &Lep_nProngs  , &b_Lep_nProngs);
    InTree->SetBranchAddress("Lep_TrigSF"   , &Lep_TrigSF   , &b_Lep_TrigSF);
    InTree->SetBranchAddress("Lep_RecoSF"   , &Lep_RecoSF   , &b_Lep_RecoSF);
    InTree->SetBranchAddress("Lep_IDSF"     , &Lep_IDSF     , &b_Lep_IDSF);
    InTree->SetBranchAddress("Lep_IsoSF"    , &Lep_IsoSF    , &b_Lep_IsoSF);
    InTree->SetBranchAddress("Lep_TtvaSF"   , &Lep_TtvaSF   , &b_Lep_TtvaSF);
    InTree->SetBranchAddress("Lep_L1CaloSF" , &Lep_L1CaloSF , &b_Lep_L1CaloSF);
    InTree->SetBranchAddress("Lep_ElOlrSF"  , &Lep_ElOlrSF  , &b_Lep_ElOlrSF);
    InTree->SetBranchAddress("Lep_TrigSF_StatUp"     , &Lep_TrigSF_StatUp     , &b_Lep_TrigSF_StatUp);
    InTree->SetBranchAddress("Lep_TrigSF_StatDown"   , &Lep_TrigSF_StatDown   , &b_Lep_TrigSF_StatDown);
    InTree->SetBranchAddress("Lep_TrigSF_SysUp"      , &Lep_TrigSF_SysUp      , &b_Lep_TrigSF_SysUp);
    InTree->SetBranchAddress("Lep_TrigSF_SysDown"    , &Lep_TrigSF_SysDown    , &b_Lep_TrigSF_SysDown);
    InTree->SetBranchAddress("Lep_RecoSF_StatUp"     , &Lep_RecoSF_StatUp     , &b_Lep_RecoSF_StatUp);
    InTree->SetBranchAddress("Lep_RecoSF_StatDown"   , &Lep_RecoSF_StatDown   , &b_Lep_RecoSF_StatDown);
    InTree->SetBranchAddress("Lep_RecoSF_SysUp"      , &Lep_RecoSF_SysUp      , &b_Lep_RecoSF_SysUp);
    InTree->SetBranchAddress("Lep_RecoSF_SysDown"    , &Lep_RecoSF_SysDown    , &b_Lep_RecoSF_SysDown);
    InTree->SetBranchAddress("Lep_RecoSF_Hpt_SysUp"  , &Lep_RecoSF_Hpt_SysUp  , &b_Lep_RecoSF_Hpt_SysUp);
    InTree->SetBranchAddress("Lep_RecoSF_Hpt_SysDown", &Lep_RecoSF_Hpt_SysDown, &b_Lep_RecoSF_Hpt_SysDown);
    InTree->SetBranchAddress("Lep_IDSF_StatUp"       , &Lep_IDSF_StatUp       , &b_Lep_IDSF_StatUp);
    InTree->SetBranchAddress("Lep_IDSF_StatDown"     , &Lep_IDSF_StatDown     , &b_Lep_IDSF_StatDown);
    InTree->SetBranchAddress("Lep_IDSF_SysUp"        , &Lep_IDSF_SysUp        , &b_Lep_IDSF_SysUp);
    InTree->SetBranchAddress("Lep_IDSF_SysDown"      , &Lep_IDSF_SysDown      , &b_Lep_IDSF_SysDown);
    InTree->SetBranchAddress("Lep_IDSF_Hpt_SysUp"    , &Lep_IDSF_Hpt_SysUp    , &b_Lep_IDSF_Hpt_SysUp);
    InTree->SetBranchAddress("Lep_IDSF_Hpt_SysDown"  , &Lep_IDSF_Hpt_SysDown  , &b_Lep_IDSF_Hpt_SysDown);
    InTree->SetBranchAddress("Lep_IsoSF_StatUp"      , &Lep_IsoSF_StatUp      , &b_Lep_IsoSF_StatUp);
    InTree->SetBranchAddress("Lep_IsoSF_StatDown"    , &Lep_IsoSF_StatDown    , &b_Lep_IsoSF_StatDown);
    InTree->SetBranchAddress("Lep_IsoSF_SysUp"       , &Lep_IsoSF_SysUp       , &b_Lep_IsoSF_SysUp);
    InTree->SetBranchAddress("Lep_IsoSF_SysDown"     , &Lep_IsoSF_SysDown     , &b_Lep_IsoSF_SysDown);
    InTree->SetBranchAddress("Lep_TtvaSF_StatUp"     , &Lep_TtvaSF_StatUp     , &b_Lep_TtvaSF_StatUp);
    InTree->SetBranchAddress("Lep_TtvaSF_StatDown"   , &Lep_TtvaSF_StatDown   , &b_Lep_TtvaSF_StatDown);
    InTree->SetBranchAddress("Lep_TtvaSF_SysUp"      , &Lep_TtvaSF_SysUp      , &b_Lep_TtvaSF_SysUp);
    InTree->SetBranchAddress("Lep_TtvaSF_SysDown"    , &Lep_TtvaSF_SysDown    , &b_Lep_TtvaSF_SysDown);
    InTree->SetBranchAddress("Lep_ElOlrSF_SysUp"     , &Lep_ElOlrSF_SysUp     , &b_Lep_ElOlrSF_SysUp);
    InTree->SetBranchAddress("Lep_ElOlrSF_SysDown"   , &Lep_ElOlrSF_SysDown   , &b_Lep_ElOlrSF_SysDown);
    InTree->SetBranchAddress("Jet_pt"                     , &Jet_pt                     , &b_Jet_pt);
    InTree->SetBranchAddress("Jet_eta"                    , &Jet_eta                    , &b_Jet_eta);
    InTree->SetBranchAddress("Jet_phi"                    , &Jet_phi                    , &b_Jet_phi);
    InTree->SetBranchAddress("Jet_JvtSF"                  , &Jet_JvtSF                  , &b_Jet_JvtSF);
    InTree->SetBranchAddress("Jet_JvtSF_SysUp"            , &Jet_JvtSF_SysUp            , &b_Jet_JvtSF_SysUp);
    InTree->SetBranchAddress("Jet_JvtSF_SysDown"          , &Jet_JvtSF_SysDown          , &b_Jet_JvtSF_SysDown);
    InTree->SetBranchAddress("Jet_BtagSF"                 , &Jet_BtagSF                 , &b_Jet_BtagSF);
    InTree->SetBranchAddress("Jet_BtagSF_Beff_SysUp"      , &Jet_BtagSF_Beff_SysUp      , &b_Jet_BtagSF_Beff_SysUp);
    InTree->SetBranchAddress("Jet_BtagSF_Beff_SysDown"    , &Jet_BtagSF_Beff_SysDown    , &b_Jet_BtagSF_Beff_SysDown);
    InTree->SetBranchAddress("Jet_BtagSF_Ceff_SysUp"      , &Jet_BtagSF_Ceff_SysUp      , &b_Jet_BtagSF_Ceff_SysUp);
    InTree->SetBranchAddress("Jet_BtagSF_Ceff_SysDown"    , &Jet_BtagSF_Ceff_SysDown    , &b_Jet_BtagSF_Ceff_SysDown);
    InTree->SetBranchAddress("Jet_BtagSF_Leff_SysUp"      , &Jet_BtagSF_Leff_SysUp      , &b_Jet_BtagSF_Leff_SysUp);
    InTree->SetBranchAddress("Jet_BtagSF_Leff_SysDown"    , &Jet_BtagSF_Leff_SysDown    , &b_Jet_BtagSF_Leff_SysDown);
    InTree->SetBranchAddress("Jet_BtagSF_ExtCeff_SysUp"   , &Jet_BtagSF_ExtCeff_SysUp   , &b_Jet_BtagSF_ExtCeff_SysUp);
    InTree->SetBranchAddress("Jet_BtagSF_ExtCeff_SysDown" , &Jet_BtagSF_ExtCeff_SysDown , &b_Jet_BtagSF_ExtCeff_SysDown);
    InTree->SetBranchAddress("Jet_BtagSF_ExtEff_SysUp"    , &Jet_BtagSF_ExtEff_SysUp    , &b_Jet_BtagSF_ExtEff_SysUp);
    InTree->SetBranchAddress("Jet_BtagSF_ExtEff_SysDown"  , &Jet_BtagSF_ExtEff_SysDown  , &b_Jet_BtagSF_ExtEff_SysDown);
    
    if(SampleName.at(ch)=="data"){
      hmll->SetBinErrorOption(TH1::kPoisson);
      hmllCorr->SetBinErrorOption(TH1::kPoisson);
      hptll->SetBinErrorOption(TH1::kPoisson);
      hptllCorr->SetBinErrorOption(TH1::kPoisson);
      hphill->SetBinErrorOption(TH1::kPoisson);
      hetall->SetBinErrorOption(TH1::kPoisson);
      hmu_eta->SetBinErrorOption(TH1::kPoisson);
      hmu_phi->SetBinErrorOption(TH1::kPoisson);
      hmu_pt->SetBinErrorOption(TH1::kPoisson);
      hel_eta->SetBinErrorOption(TH1::kPoisson);
      hel_phi->SetBinErrorOption(TH1::kPoisson);
      hel_pt->SetBinErrorOption(TH1::kPoisson);
      hta_eta->SetBinErrorOption(TH1::kPoisson);
      hta_phi->SetBinErrorOption(TH1::kPoisson);
      hta_pt->SetBinErrorOption(TH1::kPoisson);
      hnjet->SetBinErrorOption(TH1::kPoisson);
      hmet->SetBinErrorOption(TH1::kPoisson);
    }
    else{
      if(ch==0){
	hmll->Sumw2();
	hmllCorr->Sumw2();
	hptll->Sumw2();
	hptllCorr->Sumw2();
	hphill->Sumw2();
	hetall->Sumw2();
	hmu_eta->Sumw2();
	hmu_phi->Sumw2();
	hmu_pt->Sumw2();
	hel_eta->Sumw2();
	hel_phi->Sumw2();
	hel_pt->Sumw2();
	hta_eta->Sumw2();
	hta_phi->Sumw2();
	hta_pt->Sumw2();
	hnjet->Sumw2();
	hmet->Sumw2();
      }
    }
    
    /* Find Max Bin of Tau Fake Factor */
    Int_t MaxBin_1p     = FindMaxBin(FF1p).first      , MaxBin_3p     = FindMaxBin(FF3p).first     ;
    Int_t MaxBin_1p_bar = FindMaxBin(FF1p_bar).first  , MaxBin_3p_bar = FindMaxBin(FF3p_bar).first ;
    Int_t MaxBin_1p_end = FindMaxBin(FF1p_end).first  , MaxBin_3p_end = FindMaxBin(FF3p_end).first ;
    double MaxPt_1p     = FindMaxBin(FF1p).second     , MaxPt_3p      = FindMaxBin(FF3p).second    ;
    double MaxPt_1p_bar = FindMaxBin(FF1p_bar).second , MaxPt_3p_bar  = FindMaxBin(FF3p_bar).second;
    double MaxPt_1p_end = FindMaxBin(FF1p_end).second , MaxPt_3p_end  = FindMaxBin(FF3p_end).second;
    
    Int_t Nentries = (Int_t)InTree->GetEntries();
    for(Int_t en=0; en<Nentries; en++){
      InTree->GetEntry(en);

      //std::cout<<"entry "<<en<<std::endl;

      if(SampleName.at(ch)=="data")
	if(run>303892) continue;

      if(isBadJetEvt) continue;

      if(isKeepEvent==0) continue;
      
      if(channel!=LFVtype) continue;
      
      if(!ttCR){ if(isBTBGood==0) continue; }
      
      if(useBJet){
	if(ttCR){ if(!isBjetEvt) continue; }
	else{ if(isBjetEvt) continue; } 
      }

      if(QcdCR){
	if( Lep_pt->at(0)>200. || Lep_pt->at(1)>200. ) continue;
      }
      
      if(SSpair){
        if(isOSGood) continue;
      }
      
      if(WjCR){
	if( met_et<30. ||
	    (Lep_pt->at(0)>150. || Lep_pt->at(1)>150.) ) continue;
      }

      if(Blind){
	if(SampleName.at(ch)=="data")
	  if(dilepCorrMass>600.) continue;
      }
      
      double EvtWgt = 1;
      double tmp_weight = mcweight;
      if(usePU)
	tmp_weight *= puweight;
      double jetwgt = 1;
      for(uint j=0; j<Jet_pt->size(); j++){
	if(sysVar=="JtJvtSF_SysUp")
	  jetwgt *= Jet_JvtSF_SysUp->at(j);
	else if(sysVar=="JtJvtSF_SysDown")
	  jetwgt *= Jet_JvtSF_SysDown->at(j);
	else
	  jetwgt *= Jet_JvtSF->at(j);
      }
      if(useBJet){
	for(uint j=0; j<Jet_pt->size(); j++){
	  if(sysVar=="BtagSF_Beff_SysUp")
	    jetwgt *= Jet_BtagSF_Beff_SysUp->at(j);
	  else if(sysVar=="BtagSF_Beff_SysDown")
	    jetwgt *= Jet_BtagSF_Beff_SysDown->at(j);
	  else if(sysVar=="BtagSF_Ceff_SysUp")
	    jetwgt *= Jet_BtagSF_Ceff_SysUp->at(j);
	  else if(sysVar=="BtagSF_Ceff_SysDown")
	    jetwgt *= Jet_BtagSF_Ceff_SysDown->at(j);
	  else if(sysVar=="BtagSF_Leff_SysUp")
	    jetwgt *= Jet_BtagSF_Leff_SysUp->at(j);
	  else if(sysVar=="BtagSF_Leff_SysDown")
	    jetwgt *= Jet_BtagSF_Leff_SysDown->at(j);
	  else if(sysVar=="BtagSF_ExtCeff_SysUp")
	    jetwgt *= Jet_BtagSF_ExtCeff_SysUp->at(j);
	  else if(sysVar=="BtagSF_ExtCeff_SysDown")
	    jetwgt *= Jet_BtagSF_ExtCeff_SysDown->at(j);
	  else if(sysVar=="BtagSF_ExtEff_SysUp")
	    jetwgt *= Jet_BtagSF_ExtEff_SysUp->at(j);
	  else if(sysVar=="BtagSF_ExtEff_SysDown")
	    jetwgt *= Jet_BtagSF_ExtEff_SysDown->at(j);
	  else
	    jetwgt *= Jet_BtagSF->at(j);
	}
      }
      if(sysVar=="MuReco_StatUp"){
	tmp_weight *= Lep_TrigSF->at(0)*Lep_IDSF->at(0)*Lep_IsoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_TrigSF->at(1)*Lep_IDSF->at(1)*Lep_IsoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==13)
	  tmp_weight *= Lep_RecoSF_StatUp->at(0)*Lep_RecoSF->at(1);
	else
	  tmp_weight *= Lep_RecoSF_StatUp->at(1)*Lep_RecoSF->at(0);
      }
      else if(sysVar=="MuReco_StatDown"){
	tmp_weight *= Lep_TrigSF->at(0)*Lep_IDSF->at(0)*Lep_IsoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_TrigSF->at(1)*Lep_IDSF->at(1)*Lep_IsoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==13)
	  tmp_weight *= Lep_RecoSF_StatDown->at(0)*Lep_RecoSF->at(1);
	else
	  tmp_weight *= Lep_RecoSF_StatDown->at(1)*Lep_RecoSF->at(0);
      }
      else if(sysVar=="MuReco_SysUp"){
	tmp_weight *= Lep_TrigSF->at(0)*Lep_IDSF->at(0)*Lep_IsoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_TrigSF->at(1)*Lep_IDSF->at(1)*Lep_IsoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==13)
	  tmp_weight *= Lep_RecoSF_SysUp->at(0)*Lep_RecoSF->at(1);
	else
	  tmp_weight *= Lep_RecoSF_SysUp->at(1)*Lep_RecoSF->at(0);
      }
      else if(sysVar=="MuReco_SysDown"){
	tmp_weight *= Lep_TrigSF->at(0)*Lep_IDSF->at(0)*Lep_IsoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_TrigSF->at(1)*Lep_IDSF->at(1)*Lep_IsoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==13)
	  tmp_weight *= Lep_RecoSF_SysDown->at(0)*Lep_RecoSF->at(1);
	else
	  tmp_weight *= Lep_RecoSF_SysDown->at(1)*Lep_RecoSF->at(0);
      }
      else if(sysVar=="MuIso_StatUp"){
	tmp_weight *= Lep_TrigSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_TrigSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==13)
	  tmp_weight *= Lep_IsoSF_StatUp->at(0)*Lep_IsoSF->at(1);
	else
	  tmp_weight *= Lep_IsoSF_StatUp->at(1)*Lep_IsoSF->at(0);
      }
      else if(sysVar=="MuIso_StatDown"){
	tmp_weight *= Lep_TrigSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_TrigSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==13)
	  tmp_weight *= Lep_IsoSF_StatDown->at(0)*Lep_IsoSF->at(1);
	else
	  tmp_weight *= Lep_IsoSF_StatDown->at(1)*Lep_IsoSF->at(0);
      }
      else if(sysVar=="MuIso_SysUp"){
	tmp_weight *= Lep_TrigSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_TrigSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==13)
	  tmp_weight *= Lep_IsoSF_SysUp->at(0)*Lep_IsoSF->at(1);
	else
	  tmp_weight *= Lep_IsoSF_SysUp->at(1)*Lep_IsoSF->at(0);
      }
      else if(sysVar=="MuIso_SysDown"){
	tmp_weight *= Lep_TrigSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_TrigSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==13)
	  tmp_weight *= Lep_IsoSF_SysDown->at(0)*Lep_IsoSF->at(1);
	else
	  tmp_weight *= Lep_IsoSF_SysDown->at(1)*Lep_IsoSF->at(0);
      }
      else if(sysVar=="MuTrg_StatUp"){
	tmp_weight *= Lep_IsoSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_IsoSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==13)
	  tmp_weight *= Lep_TrigSF_StatUp->at(0)*Lep_TrigSF->at(1);
	else
	  tmp_weight *= Lep_TrigSF_StatUp->at(1)*Lep_TrigSF->at(0);
      }
      else if(sysVar=="MuTrg_StatDown"){
	tmp_weight *= Lep_IsoSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_IsoSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==13)
	  tmp_weight *= Lep_TrigSF_StatDown->at(0)*Lep_TrigSF->at(1);
	else
	  tmp_weight *= Lep_TrigSF_StatDown->at(1)*Lep_TrigSF->at(0);
      }
      else if(sysVar=="MuTrg_SysUp"){
	tmp_weight *= Lep_IsoSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_IsoSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==13)
	  tmp_weight *= Lep_TrigSF_SysUp->at(0)*Lep_TrigSF->at(1);
	else
	  tmp_weight *= Lep_TrigSF_SysUp->at(1)*Lep_TrigSF->at(0);
      }
      else if(sysVar=="MuTrg_SysDown"){
	tmp_weight *= Lep_IsoSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_IsoSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==13)
	  tmp_weight *= Lep_TrigSF_SysDown->at(0)*Lep_TrigSF->at(1);
	else
	  tmp_weight *= Lep_TrigSF_SysDown->at(1)*Lep_TrigSF->at(0);
      }
      else if(sysVar=="MuTTVA_StatUp"){
	tmp_weight *= Lep_IsoSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_L1CaloSF->at(1)*Lep_TrigSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_IsoSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TrigSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==13)
	  tmp_weight *= Lep_TtvaSF_StatUp->at(0)*Lep_TtvaSF->at(1);
	else
	  tmp_weight *= Lep_TtvaSF_StatUp->at(1)*Lep_TtvaSF->at(0);
      }
      else if(sysVar=="MuTTVA_StatDown"){
	tmp_weight *= Lep_IsoSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_L1CaloSF->at(1)*Lep_TrigSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_IsoSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TrigSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==13)
	  tmp_weight *= Lep_TtvaSF_StatDown->at(0)*Lep_TtvaSF->at(1);
	else
	  tmp_weight *= Lep_TtvaSF_StatDown->at(1)*Lep_TtvaSF->at(0);
      }
      else if(sysVar=="MuTTVA_SysUp"){
	tmp_weight *= Lep_IsoSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_L1CaloSF->at(1)*Lep_TrigSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_IsoSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TrigSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==13)
	  tmp_weight *= Lep_TtvaSF_SysUp->at(0)*Lep_TtvaSF->at(1);
	else
	  tmp_weight *= Lep_TtvaSF_SysUp->at(1)*Lep_TtvaSF->at(0);
      }
      else if(sysVar=="MuTTVA_SysDown"){
	tmp_weight *= Lep_IsoSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_L1CaloSF->at(1)*Lep_TrigSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_IsoSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TrigSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==13)
	  tmp_weight *= Lep_TtvaSF_SysDown->at(0)*Lep_TtvaSF->at(1);
	else
	  tmp_weight *= Lep_TtvaSF_SysDown->at(1)*Lep_TtvaSF->at(0);
      }
      else if(sysVar=="ElReco_SysUp"){
	tmp_weight *= Lep_TrigSF->at(0)*Lep_IDSF->at(0)*Lep_IsoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_TrigSF->at(1)*Lep_IDSF->at(1)*Lep_IsoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==11)
	  tmp_weight *= Lep_RecoSF_SysUp->at(0)*Lep_RecoSF->at(1);
	else
	  tmp_weight *= Lep_RecoSF_SysUp->at(1)*Lep_RecoSF->at(0);
      }
      else if(sysVar=="ElReco_SysDown"){
	tmp_weight *= Lep_TrigSF->at(0)*Lep_IDSF->at(0)*Lep_IsoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_TrigSF->at(1)*Lep_IDSF->at(1)*Lep_IsoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==11)
	  tmp_weight *= Lep_RecoSF_SysDown->at(0)*Lep_RecoSF->at(1);
	else
	  tmp_weight *= Lep_RecoSF_SysDown->at(1)*Lep_RecoSF->at(0);
      }
      else if(sysVar=="ElID_SysUp"){
	tmp_weight *= Lep_TrigSF->at(0)*Lep_RecoSF->at(0)*Lep_IsoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_TrigSF->at(1)*Lep_RecoSF->at(1)*Lep_IsoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==11)
	  tmp_weight *= Lep_IDSF_SysUp->at(0)*Lep_IDSF->at(1);
	else
	  tmp_weight *= Lep_IDSF_SysUp->at(1)*Lep_IDSF->at(0);
      }
      else if(sysVar=="ElID_SysDown"){
	tmp_weight *= Lep_TrigSF->at(0)*Lep_RecoSF->at(0)*Lep_IsoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_TrigSF->at(1)*Lep_RecoSF->at(1)*Lep_IsoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==11)
	  tmp_weight *= Lep_IDSF_SysDown->at(0)*Lep_IDSF->at(1);
	else
	  tmp_weight *= Lep_IDSF_SysDown->at(1)*Lep_IDSF->at(0);
      }
      else if(sysVar=="ElIso_SysUp"){
	tmp_weight *= Lep_TrigSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_TrigSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==11)
	  tmp_weight *= Lep_IsoSF_SysUp->at(0)*Lep_IsoSF->at(1);
	else
	  tmp_weight *= Lep_IsoSF_SysUp->at(1)*Lep_IsoSF->at(0);
      }
      else if(sysVar=="ElIso_SysDown"){
	tmp_weight *= Lep_TrigSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_TrigSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==11)
	  tmp_weight *= Lep_IsoSF_SysDown->at(0)*Lep_IsoSF->at(1);
	else
	  tmp_weight *= Lep_IsoSF_SysDown->at(1)*Lep_IsoSF->at(0);
      }
      else if(sysVar=="ElTrg_SysUp"){
	tmp_weight *= Lep_IsoSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_IsoSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==11)
	  tmp_weight *= Lep_TrigSF_SysUp->at(0)*Lep_TrigSF->at(1);
	else
	  tmp_weight *= Lep_TrigSF_SysUp->at(1)*Lep_TrigSF->at(0);
      }
      else if(sysVar=="ElTrg_SysDown"){
	tmp_weight *= Lep_IsoSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_IsoSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==11)
	  tmp_weight *= Lep_TrigSF_SysDown->at(0)*Lep_TrigSF->at(1);
	else
	  tmp_weight *= Lep_TrigSF_SysDown->at(1)*Lep_TrigSF->at(0);
      }
      else if(sysVar=="TaReco_SysUp"){
	tmp_weight *= Lep_IsoSF->at(0)*Lep_IDSF->at(0)*Lep_TrigSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_IsoSF->at(1)*Lep_IDSF->at(1)*Lep_TrigSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==15)
	  tmp_weight *= Lep_RecoSF_SysUp->at(0)*Lep_RecoSF->at(1);
	else
	  tmp_weight *= Lep_RecoSF_SysUp->at(1)*Lep_RecoSF->at(0);
      }
      else if(sysVar=="TaReco_SysDown"){
	tmp_weight *= Lep_IsoSF->at(0)*Lep_IDSF->at(0)*Lep_TrigSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_IsoSF->at(1)*Lep_IDSF->at(1)*Lep_TrigSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==15)
	  tmp_weight *= Lep_RecoSF_SysDown->at(0)*Lep_RecoSF->at(1);
	else
	  tmp_weight *= Lep_RecoSF_SysDown->at(1)*Lep_RecoSF->at(0);
      }
      else if(sysVar=="TaRecoHpt_SysUp"){
	tmp_weight *= Lep_IsoSF->at(0)*Lep_IDSF->at(0)*Lep_TrigSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_IsoSF->at(1)*Lep_IDSF->at(1)*Lep_TrigSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==15)
	  tmp_weight *= Lep_RecoSF_Hpt_SysUp->at(0)*Lep_RecoSF->at(1);
	else
	  tmp_weight *= Lep_RecoSF_Hpt_SysUp->at(1)*Lep_RecoSF->at(0);
      }
      else if(sysVar=="TaRecoHpt_SysDown"){
	tmp_weight *= Lep_IsoSF->at(0)*Lep_IDSF->at(0)*Lep_TrigSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_IsoSF->at(1)*Lep_IDSF->at(1)*Lep_TrigSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==15)
	  tmp_weight *= Lep_RecoSF_Hpt_SysDown->at(0)*Lep_RecoSF->at(1);
	else
	  tmp_weight *= Lep_RecoSF_Hpt_SysDown->at(1)*Lep_RecoSF->at(0);
      }
      else if(sysVar=="TaJetID_SysUp"){
	tmp_weight *= Lep_IsoSF->at(0)*Lep_RecoSF->at(0)*Lep_TrigSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_IsoSF->at(1)*Lep_RecoSF->at(1)*Lep_TrigSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==15)
	  tmp_weight *= Lep_IDSF_SysUp->at(0)*Lep_IDSF->at(1);
	else
	  tmp_weight *= Lep_IDSF_SysUp->at(1)*Lep_IDSF->at(0);
      }
      else if(sysVar=="TaJetID_SysDown"){
	tmp_weight *= Lep_IsoSF->at(0)*Lep_RecoSF->at(0)*Lep_TrigSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_IsoSF->at(1)*Lep_RecoSF->at(1)*Lep_TrigSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==15)
	  tmp_weight *= Lep_IDSF_SysDown->at(0)*Lep_IDSF->at(1);
	else
	  tmp_weight *= Lep_IDSF_SysDown->at(1)*Lep_IDSF->at(0);
      }
      else if(sysVar=="TaJetIDHpt_SysUp"){
	tmp_weight *= Lep_IsoSF->at(0)*Lep_RecoSF->at(0)*Lep_TrigSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_IsoSF->at(1)*Lep_RecoSF->at(1)*Lep_TrigSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==15)
	  tmp_weight *= Lep_IDSF_Hpt_SysUp->at(0)*Lep_IDSF->at(1);
	else
	  tmp_weight *= Lep_IDSF_Hpt_SysUp->at(1)*Lep_IDSF->at(0);
      }
      else if(sysVar=="TaJetIDHpt_SysDown"){
	tmp_weight *= Lep_IsoSF->at(0)*Lep_RecoSF->at(0)*Lep_TrigSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_IsoSF->at(1)*Lep_RecoSF->at(1)*Lep_TrigSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==15)
	  tmp_weight *= Lep_IDSF_Hpt_SysDown->at(0)*Lep_IDSF->at(1);
	else
	  tmp_weight *= Lep_IDSF_Hpt_SysDown->at(1)*Lep_IDSF->at(0);
      }
      else if(sysVar=="TaEleOlr_SysUp"){
	tmp_weight *= Lep_IsoSF->at(0)*Lep_RecoSF->at(0)*Lep_TrigSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_IDSF->at(0);
	tmp_weight *= Lep_IsoSF->at(1)*Lep_RecoSF->at(1)*Lep_TrigSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_IDSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==15)
	  tmp_weight *= Lep_ElOlrSF_SysUp->at(0)*Lep_ElOlrSF->at(1);
	else
	  tmp_weight *= Lep_ElOlrSF_SysUp->at(1)*Lep_ElOlrSF->at(0);
      }
      else if(sysVar=="TaEleOlr_SysDown"){
	tmp_weight *= Lep_IsoSF->at(0)*Lep_RecoSF->at(0)*Lep_TrigSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_IDSF->at(0);
	tmp_weight *= Lep_IsoSF->at(1)*Lep_RecoSF->at(1)*Lep_TrigSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_IDSF->at(1);
	tmp_weight *= jetwgt;
	if(abs(Lep_Id->at(0))==15)
	  tmp_weight *= Lep_ElOlrSF_SysDown->at(0)*Lep_ElOlrSF->at(1);
	else
	  tmp_weight *= Lep_ElOlrSF_SysDown->at(1)*Lep_ElOlrSF->at(0);
      }
      else if(sysVar=="BtagSF_Beff_SysDown"    ||
	      sysVar=="BtagSF_Ceff_SysUp"      ||
	      sysVar=="BtagSF_Ceff_SysDown"    ||
	      sysVar=="BtagSF_Leff_SysUp"      ||
	      sysVar=="BtagSF_Leff_SysDown"    ||
	      sysVar=="BtagSF_ExtCeff_SysUp"   ||
	      sysVar=="BtagSF_ExtCeff_SysDown" ||
	      sysVar=="BtagSF_ExtEff_SysUp"    ||
	      sysVar=="BtagSF_ExtEff_SysDown"  ){
	tmp_weight *= Lep_IsoSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_TrigSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
	tmp_weight *= Lep_IsoSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_TrigSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
	tmp_weight *= jetwgt;
      }
      else{
	if(!useBJet){
	  tmp_weight *= Lep_IsoSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_TrigSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
	  tmp_weight *= Lep_IsoSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_TrigSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
	}
	else{
	  tmp_weight *= Lep_IsoSF->at(0)*Lep_IDSF->at(0)*Lep_RecoSF->at(0)*Lep_TrigSF->at(0)*Lep_L1CaloSF->at(0)*Lep_TtvaSF->at(0)*Lep_ElOlrSF->at(0);
	  tmp_weight *= Lep_IsoSF->at(1)*Lep_IDSF->at(1)*Lep_RecoSF->at(1)*Lep_TrigSF->at(1)*Lep_L1CaloSF->at(1)*Lep_TtvaSF->at(1)*Lep_ElOlrSF->at(1);
	  tmp_weight *= jetwgt;
	}
      }
      
      if(SampleName.at(ch)=="data"){
	EvtWgt = 1;
      }
      else if(SampleName.at(ch)=="ttbar_incl"        ||
	      SampleName.at(ch)=="ttbar_1300MTT1500" ||
	      SampleName.at(ch)=="ttbar_1500MTT1700" ||
	      SampleName.at(ch)=="ttbar_1700MTT2000" ||
	      SampleName.at(ch)=="ttbar_MTT2000"      ){
	
	if(!UseKfact)
	  EvtWgt = tmp_weight*Lumi*((xsec/1.1949)/events);
	else
	  EvtWgt = tmp_weight*Lumi*(xsec/events);
      }
      else if(SampleName.at(ch)=="ttbar_0M150"           ||
      	      SampleName.at(ch)=="ttbar_150M500"         ||
      	      SampleName.at(ch)=="ttbar_500M1000"        ||
      	      SampleName.at(ch)=="ttbar_1000M2000"       ||
      	      SampleName.at(ch)=="ttbar_2000M3000"       ||
      	      SampleName.at(ch)=="ttbar_3000M4000"       ||
      	      SampleName.at(ch)=="ttbar_4000M5000"       ||
      	      SampleName.at(ch)=="ttbar_M5000"           ){
	if(!UseKfact)
	  EvtWgt = tmp_weight*Lumi*(xsec/events);
	else
	  EvtWgt = tmp_weight*Lumi*(xsec*1.1068/events);
      }
      else if(SampleName.at(ch)=="ttbar_Sherpa_DiLep"    ||
	      SampleName.at(ch)=="ttbar_Sherpa_SingLepP" ||
	      SampleName.at(ch)=="ttbar_Sherpa_SingLepM"  ){
	if(!UseKfact)
	  EvtWgt = tmp_weight*Lumi*(xsec/events);
	else
	  EvtWgt = tmp_weight*Lumi*(xsec/events);
      }
      else if(SampleName.at(ch)=="ttbar_410001"){
	EvtWgt = tmp_weight*Lumi*( (783.73*0.543*1.0613*1000)/events);
      }
      else if(SampleName.at(ch)=="ttbar_410002"){
	EvtWgt = tmp_weight*Lumi*( (611.1*0.543*1.3611*1000)/events);
      }
      else if(SampleName.at(ch)=="ttbar_410003"){
	EvtWgt = tmp_weight*Lumi*( (694.59*0.543*1.1975*1000)/events);
      }
      //
      //else if(SampleName.at(ch)=="Wmunu_Pt0_70_CVetoBVeto"          ){ EvtWgt = tmp_weight*Lumi*( (20011.0   *0.8136*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wmunu_Pt0_70_CFilterBVeto"        ){ EvtWgt = tmp_weight*Lumi*( (20033.0   *0.1376*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wmunu_Pt0_70_BFilter"             ){ EvtWgt = tmp_weight*Lumi*( (20020.0   *0.0467*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wmunu_Pt70_140_CVetoBVeto"        ){ EvtWgt = tmp_weight*Lumi*( (589.74    *0.6602*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wmunu_Pt70_140_CFilterBVeto"      ){ EvtWgt = tmp_weight*Lumi*( (590.75    *0.2532*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wmunu_Pt70_140_BFilter"           ){ EvtWgt = tmp_weight*Lumi*( (590.05    *0.087 *0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wmunu_Pt140_280_CVetoBVeto"       ){ EvtWgt = tmp_weight*Lumi*( (84.068    *0.6145*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wmunu_Pt140_280_CFilterBVeto"     ){ EvtWgt = tmp_weight*Lumi*( (84.296    *0.2766*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wmunu_Pt140_280_BFilter"          ){ EvtWgt = tmp_weight*Lumi*( (83.964    *0.1061*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wmunu_Pt280_500_CVetoBVeto"       ){ EvtWgt = tmp_weight*Lumi*( (6.5041    *0.585 *0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wmunu_Pt280_500_CFilterBVeto"     ){ EvtWgt = tmp_weight*Lumi*( (6.0684    *0.2868*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wmunu_Pt280_500_BFilter"          ){ EvtWgt = tmp_weight*Lumi*( (6.1503    *0.1225*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wmunu_Pt500_700_CVetoBVeto"       ){ EvtWgt = tmp_weight*Lumi*( (0.38798   *0.5667*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wmunu_Pt500_700_CFilterBVeto"     ){ EvtWgt = tmp_weight*Lumi*( (0.37959   *0.2909*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wmunu_Pt500_700_BFilter"          ){ EvtWgt = tmp_weight*Lumi*( (0.3807    *0.1367*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wmunu_Pt700_1000_CVetoBVeto"      ){ EvtWgt = tmp_weight*Lumi*( (0.068303  *0.56  *0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wmunu_Pt700_1000_CFilterBVeto"    ){ EvtWgt = tmp_weight*Lumi*( (0.068517  *0.2737*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wmunu_Pt700_1000_BFilter"         ){ EvtWgt = tmp_weight*Lumi*( (0.068219  *0.1425*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wmunu_Pt1000_2000_CVetoBVeto"     ){ EvtWgt = tmp_weight*Lumi*( (0.0089461 *0.5517*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wmunu_Pt1000_2000_CFilterBVeto"   ){ EvtWgt = tmp_weight*Lumi*( (0.0088991 *0.289 *0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wmunu_Pt1000_2000_BFilter"        ){ EvtWgt = tmp_weight*Lumi*( (0.0088975 *0.1488*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wmunu_Pt2000_E_CMS_CVetoBVeto"    ){ EvtWgt = tmp_weight*Lumi*( (2.6342e-05*0.4832*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wmunu_Pt2000_E_CMS_CFilterBVeto"  ){ EvtWgt = tmp_weight*Lumi*( (3.2907e-05*0.3073*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wmunu_Pt2000_E_CMS_BFilter"       ){ EvtWgt = tmp_weight*Lumi*( (2.7767e-05*0.1973*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wenu_Pt0_70_CVetoBVeto"           ){ EvtWgt = tmp_weight*Lumi*( (20029.0   *0.8138*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wenu_Pt0_70_CFilterBVeto"         ){ EvtWgt = tmp_weight*Lumi*( (20015.0   *0.1383*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wenu_Pt0_70_BFilter"              ){ EvtWgt = tmp_weight*Lumi*( (20004.0   *0.047 *0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wenu_Pt70_140_CVetoBVeto"         ){ EvtWgt = tmp_weight*Lumi*( (588.04    *0.6598*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wenu_Pt70_140_CFilterBVeto"       ){ EvtWgt = tmp_weight*Lumi*( (589.12    *0.2561*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wenu_Pt70_140_BFilter"            ){ EvtWgt = tmp_weight*Lumi*( (589.06    *0.0867*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wenu_Pt140_280_CVetoBVeto"        ){ EvtWgt = tmp_weight*Lumi*( (84.102    *0.6154*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wenu_Pt140_280_CFilterBVeto"      ){ EvtWgt = tmp_weight*Lumi*( (84.191    *0.2766*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wenu_Pt140_280_BFilter"           ){ EvtWgt = tmp_weight*Lumi*( (84.128    *0.1061*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wenu_Pt280_500_CVetoBVeto"        ){ EvtWgt = tmp_weight*Lumi*( (6.0923    *0.5817*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wenu_Pt280_500_CFilterBVeto"      ){ EvtWgt = tmp_weight*Lumi*( (6.0796    *0.2875*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wenu_Pt280_500_BFilter"           ){ EvtWgt = tmp_weight*Lumi*( (6.0828    *0.1242*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wenu_Pt500_700_CVetoBVeto"        ){ EvtWgt = tmp_weight*Lumi*( (0.38167   *0.5712*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wenu_Pt500_700_CFilterBVeto"      ){ EvtWgt = tmp_weight*Lumi*( (0.38112   *0.29  *0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wenu_Pt500_700_BFilter"           ){ EvtWgt = tmp_weight*Lumi*( (0.38452   *0.1368*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wenu_Pt700_1000_CVetoBVeto"       ){ EvtWgt = tmp_weight*Lumi*( (0.068378  *0.5572*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wenu_Pt700_1000_CFilterBVeto"     ){ EvtWgt = tmp_weight*Lumi*( (0.067651  *0.2898*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wenu_Pt700_1000_BFilter"          ){ EvtWgt = tmp_weight*Lumi*( (0.072063  *0.1357*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wenu_Pt1000_2000_CVetoBVeto"      ){ EvtWgt = tmp_weight*Lumi*( (0.0087439 *0.5476*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wenu_Pt1000_2000_CFilterBVeto"    ){ EvtWgt = tmp_weight*Lumi*( (0.0088697 *0.284 *0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wenu_Pt1000_2000_BFilter"         ){ EvtWgt = tmp_weight*Lumi*( (0.0088869 *0.1516*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wenu_Pt2000_E_CMS_CVetoBVeto"     ){ EvtWgt = tmp_weight*Lumi*( (3.1287e-05*0.4274*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wenu_Pt2000_E_CMS_CFilterBVeto"   ){ EvtWgt = tmp_weight*Lumi*( (2.5889e-05*0.0941*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wenu_Pt2000_E_CMS_BFilter"        ){ EvtWgt = tmp_weight*Lumi*( (2.9071e-05*0.1314*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wtaunu_Pt0_70_CVetoBVeto"         ){ EvtWgt = tmp_weight*Lumi*( (20024.0   *0.8144*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wtaunu_Pt0_70_CFilterBVeto"       ){ EvtWgt = tmp_weight*Lumi*( (20028.0   *0.1381*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wtaunu_Pt0_70_BFilter"            ){ EvtWgt = tmp_weight*Lumi*( (20015.0   *0.0468*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wtaunu_Pt70_140_CVetoBVeto"       ){ EvtWgt = tmp_weight*Lumi*( (589.14    *0.6574*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wtaunu_Pt70_140_CFilterBVeto"     ){ EvtWgt = tmp_weight*Lumi*( (590.11    *0.2525*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wtaunu_Pt70_140_BFilter"          ){ EvtWgt = tmp_weight*Lumi*( (589.83    *0.0858*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wtaunu_Pt140_280_CVetoBVeto"      ){ EvtWgt = tmp_weight*Lumi*( (84.22     *0.614 *0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wtaunu_Pt140_280_CFilterBVeto"    ){ EvtWgt = tmp_weight*Lumi*( (84.282    *0.2759*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wtaunu_Pt140_280_BFilter"         ){ EvtWgt = tmp_weight*Lumi*( (84.177    *0.1054*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wtaunu_Pt280_500_CVetoBVeto"      ){ EvtWgt = tmp_weight*Lumi*( (6.0858    *0.5844*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wtaunu_Pt280_500_CFilterBVeto"    ){ EvtWgt = tmp_weight*Lumi*( (6.0652    *0.2869*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wtaunu_Pt280_500_BFilter"         ){ EvtWgt = tmp_weight*Lumi*( (6.0788    *0.1206*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wtaunu_Pt500_700_CVetoBVeto"      ){ EvtWgt = tmp_weight*Lumi*( (0.38105   *0.5677*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wtaunu_Pt500_700_CFilterBVeto"    ){ EvtWgt = tmp_weight*Lumi*( (0.37794   *0.2967*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wtaunu_Pt500_700_BFilter"         ){ EvtWgt = tmp_weight*Lumi*( (0.37627   *0.1315*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wtaunu_Pt700_1000_CVetoBVeto"     ){ EvtWgt = tmp_weight*Lumi*( (0.073222  *0.5614*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wtaunu_Pt700_1000_CFilterBVeto"   ){ EvtWgt = tmp_weight*Lumi*( (0.067963  *0.2923*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wtaunu_Pt700_1000_BFilter"        ){ EvtWgt = tmp_weight*Lumi*( (0.067277  *0.1449*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wtaunu_Pt1000_2000_CVetoBVeto"    ){ EvtWgt = tmp_weight*Lumi*( (0.0090285 *0.5558*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wtaunu_Pt1000_2000_CFilterBVeto"  ){ EvtWgt = tmp_weight*Lumi*( (0.0089116 *0.2903*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wtaunu_Pt1000_2000_BFilter"       ){ EvtWgt = tmp_weight*Lumi*( (0.00902   *0.1413*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wtaunu_Pt2000_E_CMS_CVetoBVeto"   ){ EvtWgt = tmp_weight*Lumi*( (2.6193e-05*0.5606*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wtaunu_Pt2000_E_CMS_CFilterBVeto" ){ EvtWgt = tmp_weight*Lumi*( (3.0985e-05*0.2897*0.9702*1000)/events); }
      //else if(SampleName.at(ch)=="Wtaunu_Pt2000_E_CMS_BFilter"      ){ EvtWgt = tmp_weight*Lumi*( (2.9392e-05*0.1804*0.9702*1000)/events); }
      //
      else{
	EvtWgt = tmp_weight*Lumi*(xsec/events);
      }

      const std::pair<Int_t,ULong64_t> RunEvt = std::make_pair(run,event);
      if( EvtProcessed.insert(RunEvt).second == false ){
      	std::cout << "Found Duplicate in sample " << SampleName.at(ch)
      		  << "   -> Skipping! (Run "      << run << " Event "<< event
      		  << " weight " << EvtWgt << ")"  << std::endl;
      	continue;
      }

      if(SampleName.at(ch)=="Zee" || SampleName.at(ch)=="Zmumu")
	if(dilepCorrMass>600) continue;
      
      if(DopTRW){
	if(SampleName.at(ch)=="ttbar_incl"     ||
	   SampleName.at(ch)=="Wt_antitop"     ||
	   SampleName.at(ch)=="Wt_top"          ){
	  std::cout<<"reweight"<<std::endl;
	  std::cout<<"Pre weight EvtWgt "<<EvtWgt<<std::endl;
	  //if( dilepPt>80. && dilepPt<120. )
	  //	  EvtWgt = EvtWgt*8.87641787528991699e-01;
	  if(dilepPt>100. && dilepPt<150. ){
	    EvtWgt = EvtWgt*8.74631285667419434e-01;
      	  std::cout<<"After weight EvtWgt "<<EvtWgt<<std::endl;
	  }
	  else if(dilepPt>150. && dilepPt<200. ){
	    EvtWgt = EvtWgt*6.78350389003753662e-01;
	    std::cout<<"After weight EvtWgt "<<EvtWgt<<std::endl;
	  }
	  else if(dilepPt>200. && dilepPt<250. ){
	    EvtWgt = EvtWgt*4.64112699031829834e-01;
	    std::cout<<"After weight EvtWgt "<<EvtWgt<<std::endl;
	  }
	  else
	    EvtWgt = EvtWgt;
	}
      }
      
      double TfWgt = 1;
      if(TauFake && LFVtype>1 && sample!="data"){
	int taupos = -1;
	if( abs(Lep_Id->at(0))==15 ){      taupos = 0; }
	else if( abs(Lep_Id->at(1))==15 ){ taupos = 1; }
	int bin = 0;
	if(SplitEta){
	  if(Lep_nProngs->at(taupos)==1){
	    if(Lep_eta->at(taupos)<1.05){
	      if(Lep_pt->at(taupos)>MaxPt_1p_bar){ bin=MaxBin_1p_bar; }
	      else{ bin=FF1p_bar->FindBin(Lep_pt->at(taupos));    }
	      TfWgt = FF1p_bar->GetBinContent(bin);
	    }
	    else{
	      if(Lep_pt->at(taupos)>MaxPt_1p_end){ bin=MaxBin_1p_end; }
	      else{ bin=FF1p_end->FindBin(Lep_pt->at(taupos));    }
	      TfWgt = FF1p_end->GetBinContent(bin);
	    }
	  }
	  else if(Lep_nProngs->at(taupos)==3){
	    if(Lep_eta->at(taupos)<1.05){
	      if(Lep_pt->at(taupos)>MaxPt_3p_bar){ bin=MaxBin_3p_bar; }
	      else{ bin=FF3p_bar->FindBin(Lep_pt->at(taupos));    }
	      TfWgt = FF3p_bar->GetBinContent(bin);
	    }
	    else{
	      if(Lep_pt->at(taupos)>MaxPt_3p_end){ bin=MaxBin_3p_end; }
	      else{ bin=FF3p_end->FindBin(Lep_pt->at(taupos));    }
	      TfWgt = FF3p_end->GetBinContent(bin);
	    }
	  }
	}
	else{
	  if(Lep_nProngs->at(taupos)==1){
	    if(Lep_pt->at(taupos)>MaxPt_1p){ bin=MaxBin_1p; }
	    else{ bin=FF1p->FindBin(Lep_pt->at(taupos));    }
	    TfWgt = FF1p->GetBinContent(bin);
	  }
	  else if(Lep_nProngs->at(taupos)==3){
	    if(Lep_pt->at(taupos)>MaxPt_3p){ bin=MaxBin_3p; }
	    else{ bin=FF3p->FindBin(Lep_pt->at(taupos));    }
	    TfWgt = FF3p->GetBinContent(bin);
	  }
	}
	//std::cout<<"Tau_pt "<< Lep_pt->at(taupos)<<" np "<<Lep_nProngs->at(taupos)
	//<<"  Maxpt 1p(3p) "<<MaxPt_1p<<"("<<MaxPt_3p<<") "<<" weight "<<TfWgt<<std::endl;
      }
	
      if(sample=="AllBkg"){
	if( !(SampleName.at(ch)=="ttbar_incl"     ||
              SampleName.at(ch)=="Wt_antitop"     ||
              SampleName.at(ch)=="Wt_top"          )
	    ){
	  //std::cout<<"AllBkg: filling mass for SampleName "
	  //<<SampleName.at(ch)<<std::endl;
	  hmll->Fill( dilepMass, EvtWgt );
	  hmllCorr->Fill( dilepCorrMass, EvtWgt );
	  if(sysVar=="Nominal"){
	    double PdfWgt = 1;
	    Int_t bin = 0;
	    bin = PDF1->FindBin( dilepMass );
	    PdfWgt = PDF1->GetBinContent(bin)*PDF2->GetBinContent(bin);
	    hmll_PDF->Fill( dilepMass, EvtWgt*PdfWgt );
	    bin = PDF1->FindBin( dilepCorrMass );
	    PdfWgt = PDF1->GetBinContent(bin)*PDF2->GetBinContent(bin);
	    hmllCorr_PDF->Fill( dilepCorrMass, EvtWgt*PdfWgt );
	  }
	}
      }
      else if(sample=="Syst"){
	hmll->Fill( dilepMass, EvtWgt );
	hmllCorr->Fill( dilepCorrMass, EvtWgt );
	if(sysVar=="Nominal"){
	  /* pdf var weight */
	  double PdfWgt = 1, PdfWgtC = 1;
	  Int_t bin = 0, binC = 0;
	  bin  = PDF1->FindBin( dilepMass );
	  binC = PDF1->FindBin( dilepCorrMass );
	  PdfWgt  = PDF1->GetBinContent(bin)*PDF2->GetBinContent(bin);
	  PdfWgtC = PDF1->GetBinContent(binC)*PDF2->GetBinContent(binC);
	  /* scale var weight */
	  double ScaleWgt = 1;
          if(SampleName.at(ch)=="ttbar_incl"){
            Int_t Sbin = Scale->FindBin( dilepCorrMass );
            ScaleWgt = Scale->GetBinContent( Sbin );
          }
	  
	  hmll_PDF->Fill( dilepMass, EvtWgt*PdfWgt );
	  hptll_PDF->Fill( dilepPt, EvtWgt*PdfWgt );
	  hmllCorr_PDF->Fill( dilepCorrMass, EvtWgt*PdfWgtC );
	  hptllCorr_PDF->Fill( dilepCorrPt, EvtWgt*PdfWgtC );
	  hetall_PDF->Fill( dilepEta, EvtWgt*PdfWgtC );
	  hphill_PDF->Fill( dilepPhi, EvtWgt*PdfWgtC );
	  hmet_PDF->Fill( met_et, EvtWgt*PdfWgtC );
	  hnjet_PDF->Fill( Jet_pt->size(), EvtWgt*PdfWgtC );
	  
	  hmll_SCALE->Fill( dilepMass, EvtWgt*ScaleWgt );
          hptll_SCALE->Fill( dilepPt, EvtWgt*ScaleWgt );
          hmllCorr_SCALE->Fill( dilepCorrMass, EvtWgt*ScaleWgt );
          hptllCorr_SCALE->Fill( dilepCorrPt, EvtWgt*ScaleWgt );
          hetall_SCALE->Fill( dilepEta, EvtWgt*ScaleWgt );
          hphill_SCALE->Fill( dilepPhi, EvtWgt*ScaleWgt );
          hmet_SCALE->Fill( met_et, EvtWgt*ScaleWgt );
          hnjet_SCALE->Fill( Jet_pt->size(), EvtWgt*ScaleWgt );
	  
	  for(uint i=0; i<Lep_Id->size(); i++){
	    if( abs(Lep_Id->at(i))==13 ){
	      hmu_eta_PDF->Fill( Lep_eta->at(i), EvtWgt*PdfWgtC );
	      hmu_phi_PDF->Fill( Lep_phi->at(i), EvtWgt*PdfWgtC );
	      hmu_pt_PDF->Fill( Lep_pt->at(i), EvtWgt*PdfWgtC );
	      
	      hmu_eta_SCALE->Fill( Lep_eta->at(i), EvtWgt*ScaleWgt );
              hmu_phi_SCALE->Fill( Lep_phi->at(i), EvtWgt*ScaleWgt );
              hmu_pt_SCALE->Fill( Lep_pt->at(i), EvtWgt*ScaleWgt );
	    }
	    if( abs(Lep_Id->at(i))==11 ){
	      hel_eta_PDF->Fill( Lep_eta->at(i), EvtWgt*PdfWgtC );
	      hel_phi_PDF->Fill( Lep_phi->at(i), EvtWgt*PdfWgtC );
	      hel_pt_PDF->Fill( Lep_pt->at(i), EvtWgt*PdfWgtC );
	      
	      hel_eta_SCALE->Fill( Lep_eta->at(i), EvtWgt*ScaleWgt );
              hel_phi_SCALE->Fill( Lep_phi->at(i), EvtWgt*ScaleWgt );
              hel_pt_SCALE->Fill( Lep_pt->at(i), EvtWgt*ScaleWgt );
	    }
	    if( abs(Lep_Id->at(i))==15 ){
	      hta_eta_PDF->Fill( Lep_eta->at(i), EvtWgt*PdfWgtC );
	      hta_phi_PDF->Fill( Lep_phi->at(i), EvtWgt*PdfWgtC );
	      hta_pt_PDF->Fill( Lep_pt->at(i), EvtWgt*PdfWgtC );

	      hta_eta_SCALE->Fill( Lep_eta->at(i), EvtWgt*ScaleWgt );
              hta_phi_SCALE->Fill( Lep_phi->at(i), EvtWgt*ScaleWgt );
              hta_pt_SCALE->Fill( Lep_pt->at(i), EvtWgt*ScaleWgt );
	    }
	  }
	}
      }
      else{
	hmll->Fill( dilepMass, EvtWgt*TfWgt );
	hmllCorr->Fill( dilepCorrMass, EvtWgt*TfWgt );
      }
      hptll->Fill( dilepPt, EvtWgt*TfWgt);
      hptllCorr->Fill( dilepCorrPt, EvtWgt*TfWgt);
      hphill->Fill( dilepPhi, EvtWgt*TfWgt);
      hetall->Fill( dilepEta, EvtWgt*TfWgt);
      hmet->Fill( met_et, EvtWgt*TfWgt );
      hnjet->Fill( Jet_pt->size(), EvtWgt*TfWgt);
      for(uint i=0; i<Lep_Id->size(); i++){
	if( abs(Lep_Id->at(i))==13 ){
	  hmu_eta->Fill( Lep_eta->at(i), EvtWgt*TfWgt );
	  hmu_phi->Fill( Lep_phi->at(i), EvtWgt*TfWgt );
	  hmu_pt->Fill( Lep_pt->at(i), EvtWgt*TfWgt );
	}
	if( abs(Lep_Id->at(i))==11 ){
	  hel_eta->Fill( Lep_eta->at(i), EvtWgt*TfWgt );
	  hel_phi->Fill( Lep_phi->at(i), EvtWgt*TfWgt );
	  hel_pt->Fill( Lep_pt->at(i), EvtWgt*TfWgt );
	}
	if( abs(Lep_Id->at(i))==15 ){
	  hta_eta->Fill( Lep_eta->at(i), EvtWgt*TfWgt );
	  hta_phi->Fill( Lep_phi->at(i), EvtWgt*TfWgt );
	  hta_pt->Fill( Lep_pt->at(i), EvtWgt*TfWgt );
	}
      }
    }
    input->Close();
  }
  
  out->cd();
  hmll->Write();
  hmllCorr->Write();
  if( (sample=="Syst" || sample=="AllBkg") && sysVar=="Nominal" ){
    hmll_PDF->Write();
    hmllCorr_PDF->Write();
    if(sample=="Syst"){
      hptll_PDF->Write();
      hptllCorr_PDF->Write();
      hetall_PDF->Write();
      hphill_PDF->Write();
      hmet_PDF->Write();
      hnjet_PDF->Write();
      hmu_eta_PDF->Write();
      hmu_phi_PDF->Write();
      hmu_pt_PDF->Write();
      hel_eta_PDF->Write();
      hel_phi_PDF->Write();
      hel_pt_PDF->Write();
      hta_eta_PDF->Write();
      hta_phi_PDF->Write();
      hta_pt_PDF->Write();

      hmll_SCALE->Write();
      hmllCorr_SCALE->Write();
      hptll_SCALE->Write();
      hptllCorr_SCALE->Write();
      hetall_SCALE->Write();
      hphill_SCALE->Write();
      hmet_SCALE->Write();
      hnjet_SCALE->Write();
      hmu_eta_SCALE->Write();
      hmu_phi_SCALE->Write();
      hmu_pt_SCALE->Write();
      hel_eta_SCALE->Write();
      hel_phi_SCALE->Write();
      hel_pt_SCALE->Write();
      hta_eta_SCALE->Write();
      hta_phi_SCALE->Write();
      hta_pt_SCALE->Write();
    }
  }
  hptll->Write();
  hptllCorr->Write();
  hphill->Write();
  hetall->Write();
  hmet->Write();
  hmu_eta->Write();
  hmu_phi->Write();
  hmu_pt->Write();
  hel_eta->Write();
  hel_phi->Write();
  hel_pt->Write();
  hta_eta->Write();
  hta_phi->Write();
  hta_pt->Write();
  hnjet->Write();
  out->Close();
  hmll->Delete();
  hmllCorr->Delete();
  hmll_PDF->Delete();
  hmllCorr_PDF->Delete();
  hptll_PDF->Delete();
  hptllCorr_PDF->Delete();
  hetall_PDF->Delete();
  hphill_PDF->Delete();
  hmet_PDF->Delete();
  hnjet_PDF->Delete();
  hmu_eta_PDF->Delete();
  hmu_phi_PDF->Delete();
  hmu_pt_PDF->Delete();
  hel_eta_PDF->Delete();
  hel_phi_PDF->Delete();
  hel_pt_PDF->Delete();
  hta_eta_PDF->Delete();
  hta_phi_PDF->Delete();
  hta_pt_PDF->Delete();
  hmll_SCALE->Delete();
  hmllCorr_SCALE->Delete();
  hptll_SCALE->Delete();
  hptllCorr_SCALE->Delete();
  hetall_SCALE->Delete();
  hphill_SCALE->Delete();
  hmet_SCALE->Delete();
  hnjet_SCALE->Delete();
  hmu_eta_SCALE->Delete();
  hmu_phi_SCALE->Delete();
  hmu_pt_SCALE->Delete();
  hel_eta_SCALE->Delete();
  hel_phi_SCALE->Delete();
  hel_pt_SCALE->Delete();
  hta_eta_SCALE->Delete();
  hta_phi_SCALE->Delete();
  hta_pt_SCALE->Delete();
  hptll->Delete();
  hptllCorr->Delete();
  hphill->Delete();
  hetall->Delete();
  hmet->Delete();
  hmu_eta->Delete();
  hmu_phi->Delete();
  hmu_pt->Delete();
  hel_eta->Delete();
  hel_phi->Delete();
  hel_pt->Delete();
  hta_eta->Delete();
  hta_phi->Delete();
  hta_pt->Delete();
  hnjet->Delete();
  PDF1->Delete();
  PDF2->Delete();
  pdfIn->Close();
  Scale->Delete();
  ScaleIn->Close();
  
}
