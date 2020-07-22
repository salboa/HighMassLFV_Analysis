/* program includes */
#include "AddContributions.h"
#include "SysHandler.C"
#include "ATLASstyle.C"

int main( int argc, char* argv[] ) {

  bool useBjet   = false;
  bool addSys    = false;
  bool exclTop   = false;
  bool isttCR    = false;
  bool isBlind   = false;
  bool isRevDphi = false;
  bool usePtRw   = false;
  bool isSherpa  = false;
  bool useSmooth = false;
  bool printHelp = false;
  int lfvType = -1;
  for(int i = 1; i < argc; ++i){
    if( !strcmp(argv[i],"--useBjet")        ){ useBjet   = true; }
    else if( !strcmp(argv[i],"--addSys")    ){ addSys    = true; }
    else if( !strcmp(argv[i],"--exclTop")   ){ exclTop   = true; }
    else if( !strcmp(argv[i],"--isttCR")    ){ isttCR    = true; }
    else if( !strcmp(argv[i],"--isBlind")   ){ isBlind   = true; }
    else if( !strcmp(argv[i],"--isRevDphi") ){ isRevDphi = true; }
    else if( !strcmp(argv[i],"--usePtRw")   ){ usePtRw   = true; }
    else if( !strcmp(argv[i],"--isSherpa")  ){ isSherpa  = true; }
    else if( !strcmp(argv[i],"--useSmooth") ){ useSmooth = true; }
    else if( !strcmp(argv[i],"--lfvType")   ){ lfvType   = std::stoi(argv[i+1]); }
    else if( !strcmp(argv[i],"--help")      ){ printHelp = true; }
    else{
      if(std::string(argv[i]).find("--")!=std::string::npos)
	std::cout << "WARNING:: Option " << argv[i] << " not recognized: "
		  << "skipping!" << std::endl;
    }
  }
  if(printHelp){
    std::cout << " AddContributions: add Top and W+jets plots! "  << std::endl;
    std::cout << "                 Options: "                     << std::endl;
    std::cout << "                  --useBjet   [Enable b-jet veto:"
	      << " default is 'false']"                           << std::endl;
    std::cout << "                  --addSys    [Add systematics:"
	      << " defualt is 'false']"                           << std::endl;
    std::cout << "                  --exclTop   [Exclude Top:" 
	      << " default is 'false']"                           << std::endl;
    std::cout << "                  --isttCR    [Enable ttbar CR:" 
	      << " default is 'false']"                           << std::endl;
    std::cout << "                  --isBlind   [Enable Blind analysis:" 
	      << " default is 'false']"                           << std::endl;
    std::cout << "                  --isRevDphi [Enable revDphi analysis:" 
	      << " default is 'false']"                           << std::endl;
    std::cout << "                  --usePtRw   [Enable pT_ll reweighting:"
	      << " default is 'false']"                           << std::endl;
    std::cout << "                  --isSherpa  [Enable Sherpa ttbar:" 
	      << " default is 'false']"                           << std::endl;
    std::cout << "                  --useSmooth [Enable qcd mll smoothing:"
	      << " default is 'false']"                           << std::endl;
    std::cout << "                  --lfvType   [Choose lfv channel: "
	      << " options are '1,2,3'] "                         << std::endl;
    std::cout << "                  --help      [Print this help]" << std::endl;
    exit(0);
  }

  if(lfvType==-1){
    std::cout << "< AddContributions() >:: lfvType not set!"
	      << " Possible options: 1,2,3" << std::endl;
    exit(0);
  }

  if(isBlind || isRevDphi || isttCR){
    std::cout << "< AddContributions() >:: isBlind or isRevDphi option set:"
	      << " enabling exclTop option as well!" << std::endl;
    exclTop=true;
  }
  std::cout << "< AddContributions() >:: Options set "          << std::endl;
  std::cout << "                     useBjet   = " << useBjet   << std::endl;
  std::cout << "                     lfvType   = " << lfvType   << std::endl;
  std::cout << "                     addSys    = " << addSys    << std::endl;
  std::cout << "                     exclTop   = " << exclTop   << std::endl;
  std::cout << "                     isttCR    = " << isttCR    << std::endl;
  std::cout << "                     isBlind   = " << isBlind   << std::endl;
  std::cout << "                     isRevDphi = " << isRevDphi << std::endl;
  std::cout << "                     usePtRw   = " << usePtRw   << std::endl;
  std::cout << "                     isSherpa  = " << isSherpa  << std::endl;
  std::cout << "                     useSmooth = " << useSmooth << std::endl;
  
  AddContributions(useBjet,addSys,exclTop,isttCR,isBlind,isRevDphi,
		   usePtRw,isSherpa,lfvType,useSmooth);
  
  return 0;
  
}

void AddContributions(bool useBjet, bool addSys, bool exclTop, bool isttCR,
		      bool isBlind, bool isRevDphi, bool usePtRw,
		      bool isSherpa, int LFVtype, bool useSmooth){

  SetATLASStyle();
  TH1::SetDefaultSumw2(kTRUE);

  std::string lfvType = "";
  if(LFVtype==1)      { lfvType="emu";   }
  else if(LFVtype==2) { lfvType="etau";  }
  else if(LFVtype==3) { lfvType="mutau"; }

  std::cout << "< AddContributions() >:: Adding Top and W+jets plots for"
	    << " Channel " << lfvType << " to each Sys file "<< std:: endl;


  TFile* topIn = NULL, *out = NULL, *wjetIn = NULL;

  std::string Dir = "";
  if( useBjet ){ Dir += "Bjet/";   }
  else{          Dir += "NoBjet/"; }

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
  
  std::string topInName = "TopFits/Top_"+lfvType;
  if( useBjet ) topInName += "Bjet";
  
  std::string wjetInName = Dir+"WjetNoTauId/Plots_";
  std::string outName = Dir+"Plots_";

  TH1F *Htop = NULL;
  TH1F *Hwjet_mllCorr = NULL , *Hwjet_ptllCorr = NULL , *Hwjet_etall = NULL ;
  TH1F *Hwjet_phill   = NULL , *Hwjet_njet     = NULL , *Hwjet_met   = NULL ;
  TH1F *Hwjet_muEta   = NULL , *Hwjet_muPhi    = NULL , *Hwjet_muPt  = NULL ;
  TH1F *Hwjet_elEta   = NULL , *Hwjet_elPhi    = NULL , *Hwjet_elPt  = NULL ;
  TH1F *Hwjet_taEta   = NULL , *Hwjet_taPhi    = NULL , *Hwjet_taPt  = NULL ;
  TH1F *Hwjet_mll     = NULL , *Hwjet_ptll     = NULL , *Hwjet_mt    = NULL ;
  
  for(uint i=0; i<sysVar.size(); i++){

    std::cout << "< AddContributions() >:: Processing Sys "
	      << sysVar.at(i) << std::endl;

    std::string fName = outName+sysVar.at(i)+"_"+lfvType;
    if(isBlind)  { fName += "_Blind";  }
    if(usePtRw)  { fName += "_PtRw";   }
    if(useSmooth){ fName += "_Smooth"; }
    
    out = new TFile( (fName+".root").c_str(), "UPDATE" );
    
    /* Adding Top */
    if(!exclTop){
      
      topIn = new TFile( (topInName+"Fits.root").c_str() );
      
      if(sysVar.at(i)=="TopFit_Sys"){
	Htop = (TH1F*)topIn->Get( "hmllCorr_Top_Nominal_relUncer" );
	TH1F *mllNom = (TH1F*)topIn->Get( "hmllCorr_Top_Nominal_FIT" );
	TH1F *mllSys = (TH1F*)mllNom->Clone("hmllCorr_Top");
	mllSys->Reset();
	for(int i=1; i<mllNom->GetNbinsX()+1; i++){
	  double scaleTop = Htop->GetBinContent(i);
	  //std::cout << " Bin = " << i << "  scaleTop = "<<scaleTop<<std::endl;
	  mllSys->SetBinContent( i, mllNom->GetBinContent(i)+
				 mllNom->GetBinContent(i)*scaleTop);
	}
	out->cd();
	mllSys->Write("hmllCorr_Top");
	mllNom->Delete();
	mllSys->Delete();
      }
      else if(sysVar.at(i).find("TauFake")  != std::string::npos  ||
	      sysVar.at(i).find("Multijet") != std::string::npos  ){
	Htop = (TH1F*)topIn->Get( "hmllCorr_Top_Nominal_FIT" );
	out->cd();
	Htop->Write("hmllCorr_Top");
	Htop->Delete();
      }
      else{
	Htop = (TH1F*)topIn->Get( ("hmllCorr_Top_"+sysVar.at(i)+"_FIT").c_str() );
	out->cd();
	Htop->Write("hmllCorr_Top");
	Htop->Delete();
      }
    }
    
    /* Adding W+jets */
    if(LFVtype>1){
      if(isBlind){
	if(sysVar.at(i).find("Top")      != std::string::npos ||
	   sysVar.at(i).find("Multijet") != std::string::npos ||
	   sysVar.at(i).find("PDF")      != std::string::npos ||
	   sysVar.at(i).find("PtRw")     != std::string::npos  )
	  wjetIn = new TFile( (wjetInName+"Nominal_"+lfvType+"_Blind.root").c_str() );
	else if(sysVar.at(i)=="TauFake_StatUp")
	  wjetIn = new TFile( (wjetInName+"TauFake_StatUp_"+lfvType+"_Blind.root").c_str() );
	else if(sysVar.at(i)=="TauFake_StatDown")
	  wjetIn = new TFile( (wjetInName+"TauFake_StatDown_"+lfvType+"_Blind.root").c_str() );
	else if(sysVar.at(i)=="TauFake_BDT_SysUp")
	  wjetIn = new TFile( (wjetInName+"TauFake_BDT_SysUp_"+lfvType+"_Blind.root").c_str() );
	else if(sysVar.at(i)=="TauFake_BDT_SysDown")
	  wjetIn = new TFile( (wjetInName+"TauFake_BDT_SysDown_"+lfvType+"_Blind.root").c_str() );
	else if(sysVar.at(i)=="TauFake_CR_Sys")
	  wjetIn = new TFile( (wjetInName+"TauFake_CR_Sys_"+lfvType+"_Blind.root").c_str() );
	else if(sysVar.at(i)=="TauFake_Comp_SysUp")
	  wjetIn = new TFile( (wjetInName+"TauFake_Comp_SysUp_"+lfvType+"_Blind.root").c_str() );
	else if(sysVar.at(i)=="TauFake_Comp_SysDown")
	  wjetIn = new TFile( (wjetInName+"TauFake_Comp_SysDown_"+lfvType+"_Blind.root").c_str() );
	else
	  wjetIn = new TFile( (wjetInName+sysVar.at(i)+"_"+lfvType+"_Blind.root").c_str() );
      }
      else{
	if(sysVar.at(i).find("Top")      != std::string::npos ||
	   sysVar.at(i).find("Multijet") != std::string::npos ||
	   sysVar.at(i).find("PDF")      != std::string::npos ||
	   sysVar.at(i).find("PtRw")     != std::string::npos  )
	  wjetIn = new TFile( (wjetInName+"Nominal_"+lfvType+".root").c_str() );
	else if(sysVar.at(i)=="TauFake_StatUp")
	  wjetIn = new TFile( (wjetInName+"TauFake_StatUp_"+lfvType+".root").c_str() );
	else if(sysVar.at(i)=="TauFake_StatDown")
	  wjetIn = new TFile( (wjetInName+"TauFake_StatDown_"+lfvType+".root").c_str() );
	else if(sysVar.at(i)=="TauFake_BDT_SysUp")
	  wjetIn = new TFile( (wjetInName+"TauFake_BDT_SysUp_"+lfvType+".root").c_str() );
	else if(sysVar.at(i)=="TauFake_BDT_SysDown")
	  wjetIn = new TFile( (wjetInName+"TauFake_BDT_SysDown_"+lfvType+".root").c_str() );
	else if(sysVar.at(i)=="TauFake_SysCR")
	  wjetIn = new TFile( (wjetInName+"TauFake_SysCR_"+lfvType+".root").c_str() );
	else if(sysVar.at(i)=="TauFake_Comp_SysUp")
	  wjetIn = new TFile( (wjetInName+"TauFake_Comp_SysUp_"+lfvType+".root").c_str() );
	else if(sysVar.at(i)=="TauFake_Comp_SysDown")
	  wjetIn = new TFile( (wjetInName+"TauFake_Comp_SysDown_"+lfvType+".root").c_str() );
	else
	  wjetIn = new TFile( (wjetInName+sysVar.at(i)+"_"+lfvType+".root").c_str() );
      }
      
      Hwjet_mllCorr  = (TH1F*)wjetIn->Get( "hmllCorr_Wjets"  );
      if(LFVtype==3){
	double bin38 = Hwjet_mllCorr->GetBinContent(38);
	double bin40 = Hwjet_mllCorr->GetBinContent(40);
	Hwjet_mllCorr->SetBinContent( 39, (bin38+bin40)/2. );
	Hwjet_mllCorr->SetBinError( 39, Hwjet_mllCorr->GetBinError(39) );
      }
      Hwjet_mll      = (TH1F*)wjetIn->Get( "hmll_Wjets"      );
      Hwjet_ptllCorr = (TH1F*)wjetIn->Get( "hptllCorr_Wjets" );
      Hwjet_ptll     = (TH1F*)wjetIn->Get( "hptll_Wjets"     );
      Hwjet_phill    = (TH1F*)wjetIn->Get( "hphill_Wjets"    );
      Hwjet_etall    = (TH1F*)wjetIn->Get( "hetall_Wjets"    );
      Hwjet_muEta    = (TH1F*)wjetIn->Get( "hmu_eta_Wjets"   );
      Hwjet_muPhi    = (TH1F*)wjetIn->Get( "hmu_phi_Wjets"   );
      Hwjet_muPt     = (TH1F*)wjetIn->Get( "hmu_pt_Wjets"    );
      Hwjet_elEta    = (TH1F*)wjetIn->Get( "hel_eta_Wjets"   );
      Hwjet_elPhi    = (TH1F*)wjetIn->Get( "hel_phi_Wjets"   );
      Hwjet_elPt     = (TH1F*)wjetIn->Get( "hel_pt_Wjets"    );
      Hwjet_taEta    = (TH1F*)wjetIn->Get( "hta_eta_Wjets"   );
      Hwjet_taPhi    = (TH1F*)wjetIn->Get( "hta_phi_Wjets"   );
      Hwjet_taPt     = (TH1F*)wjetIn->Get( "hta_pt_Wjets"    );
      Hwjet_njet     = (TH1F*)wjetIn->Get( "hnjet_Wjets"     );
      Hwjet_met      = (TH1F*)wjetIn->Get( "hmet_Wjets"      );
      Hwjet_mt       = (TH1F*)wjetIn->Get( "hmt_Wjets"       );
      out->cd();
      Hwjet_mllCorr  ->Write();
      Hwjet_mll      ->Write();
      Hwjet_ptllCorr ->Write();
      Hwjet_ptll     ->Write();
      Hwjet_phill    ->Write();
      Hwjet_etall    ->Write();
      Hwjet_muEta    ->Write();
      Hwjet_muPhi    ->Write();
      Hwjet_muPt     ->Write();
      Hwjet_elEta    ->Write();
      Hwjet_elPhi    ->Write();
      Hwjet_elPt     ->Write();
      Hwjet_taEta    ->Write();
      Hwjet_taPhi    ->Write();
      Hwjet_taPt     ->Write();
      Hwjet_njet     ->Write();
      Hwjet_met      ->Write();
      Hwjet_mt       ->Write();
      
      Hwjet_mllCorr  ->Delete();
      Hwjet_mll      ->Delete();
      Hwjet_ptllCorr ->Delete();
      Hwjet_ptll     ->Delete();
      Hwjet_phill    ->Delete();
      Hwjet_etall    ->Delete();
      Hwjet_muEta    ->Delete();
      Hwjet_muPhi    ->Delete();
      Hwjet_muPt     ->Delete();
      Hwjet_elEta    ->Delete();
      Hwjet_elPhi    ->Delete();
      Hwjet_elPt     ->Delete();
      Hwjet_taEta    ->Delete();
      Hwjet_taPhi    ->Delete();
      Hwjet_taPt     ->Delete();
      Hwjet_njet     ->Delete();
      Hwjet_met      ->Delete();
      Hwjet_mt       ->Delete();
    }
    
    /* Close Files */
    out->Close();
    if(LFVtype>1)
      wjetIn->Close();
  }
  if(!exclTop)
    topIn->Close();
  
}
