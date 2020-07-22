/* program includes */
#include "SysPercentVariations.h"
#include "SysHandler.C"
#include "ATLASstyle.C"

int main( int argc, char* argv[] ) {

  bool useBjet      = false;
  bool isBlind      = false;
  bool isttCR       = false;
  bool isRevDphi    = false;
  bool isSherpa     = false;
  bool debug        = false;
  bool rmAbs        = false;
  std::string Htype = "BkgTot";
  bool isSignal     = false;
  bool printHelp    = false;
  int lfvType = -1;
  for(int i = 1; i < argc; ++i){
    if( !strcmp(argv[i],"--useBjet")        ){ useBjet   = true; }
    else if( !strcmp(argv[i],"--isBlind")   ){ isBlind   = true; }
    else if( !strcmp(argv[i],"--lfvType")   ){ lfvType   = std::stoi(argv[i+1]); }
    else if( !strcmp(argv[i],"--Htype")     ){ Htype     = argv[i+1]; }
    else if( !strcmp(argv[i],"--isttCR")    ){ isttCR    = true; }
    else if( !strcmp(argv[i],"--isRevDphi") ){ isRevDphi = true; }
    else if( !strcmp(argv[i],"--isSherpa")  ){ isSherpa  = true; }
    else if( !strcmp(argv[i],"--isSignal")  ){ isSignal  = true; }
    else if( !strcmp(argv[i],"--rmAbs")     ){ rmAbs     = true; }
    else if( !strcmp(argv[i],"--debug")     ){ debug     = true; }
    else if( !strcmp(argv[i],"--help")      ){ printHelp = true; }
    else{
      if(std::string(argv[i]).find("--")!=std::string::npos)
	std::cout << "WARNING:: Option " << argv[i] << " not recognized: "
		  << "skipping!" << std::endl;
    }
  }
  if(printHelp){
    std::cout << " SysPercentVariations: make Sys % variations!"  << std::endl;
    std::cout << "                Options: "                      << std::endl;
    std::cout << "                 --useBjet   [Enable b-jet veto:"
	      << " default is 'false' "                           << std::endl;
    std::cout << "                 --isBlind   [Enable Blind analysis:"
	      << " default is 'false' "                           << std::endl;
    std::cout << "                 --lfvType   [Choose lfv channel: "
	      << " options are '1,2,3'] "                         << std::endl;
    std::cout << "                 --Htype     [Choose MC channel: "
	      << " default is 'BkgTot'] "                         << std::endl;
    std::cout << "                 --isttCR    [Enable ttbar CR:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                 --isRevDphi [Enable revDphi analysis:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                 --isSherpa  [Enable Sherpa ttbar:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                 --isSignal  [Enable Signal shapes: "
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                 --rmAbs     [Remove abs(Var-Nom):"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                 --debug     [Enable debug]"    << std::endl;
    std::cout << "                 --help      [Print this help]" << std::endl;
    exit(0);
  }

  if(lfvType==-1){
    std::cout << "< SysPercentVariations() >:: lfvType not set!"
	      << " Possible options: 1,2,3" << std::endl;
    exit(0);
  }
  
  std::cout << " SysPercentVariations Options set: "              << std::endl;
  std::cout << "                       useBjet   = " << useBjet   << std::endl;
  std::cout << "                       isBlind   = " << isBlind   << std::endl;
  std::cout << "                       lfvType   = " << lfvType   << std::endl;
  std::cout << "                       isttCR    = " << isttCR    << std::endl;
  std::cout << "                       isRevDphi = " << isRevDphi << std::endl;
  std::cout << "                       isSherpa  = " << isSherpa  << std::endl;
  std::cout << "                       isSignal  = " << isSignal  << std::endl;
  std::cout << "                       Htype     = " << Htype     << std::endl;
  std::cout << "                       rmAbs     = " << rmAbs     << std::endl;
  std::cout << "                       debug     = " << debug     << std::endl;

  m_debug = debug;

  if(Htype.find("Zprime")!=std::string::npos ||
     Htype.find("QBH")!=std::string::npos ||
     Htype.find("SVT")!=std::string::npos  )
    isSignal=true;

  if(lfvType==1 && Htype=="Multijet")
    SysPercentVariations(useBjet,isBlind,isttCR,isSherpa);
  else
    SysPercentVariations(lfvType,Htype,useBjet,isBlind,isttCR,
			 isRevDphi,isSherpa,isSignal,rmAbs);
  
  return 0;
}

void SysPercentVariations(int LFVtype,   std::string Htype, bool useBjet,
			  bool isBlind,  bool isttCR,       bool isRevDphi,
			  bool isSherpa, bool isSignal,     bool rmAbs){
  
  SetATLASStyle();
  TH1::SetDefaultSumw2(kTRUE);

  std::string lfvType = "";
  if(LFVtype==1)      { lfvType="emu";   }
  else if(LFVtype==2) { lfvType="etau";  }
  else if(LFVtype==3) { lfvType="mutau"; }

  std::cout << " < SysPercentVariation() > :: making sys % variation for "
	    << lfvType << " Channel and " << Htype
	    << " Background" << std::endl;
  
  std::string Dir = "";
  if(useBjet){  Dir += "Bjet/";   }
  else{         Dir += "NoBjet/"; }

  bool noPtRw = false;
  if(isttCR){
    Dir += "ttbarCR";
    if(isSherpa) Dir += "_Sherpa";
    Dir += "/";
    noPtRw = true;
  }
  if(isRevDphi){
    Dir += "revDphi/";
    noPtRw = true;
  }

  /* define files */
  std::string NomName = Dir+"Plots_Nominal_"+lfvType;
  std::string OutName = Dir+"PercentVariations_"+lfvType;
  if(isSignal){
    NomName += "_Signals"; OutName += "_Signal";
  }
  if(isBlind){
    NomName += "_Blind"; OutName += "_Blind";
  }
  if(Htype!="BkgTot"){ OutName += "_"+Htype; }
  if(rmAbs) OutName += "_noAbs";
  
  TFile *Nom = new TFile( (NomName+".root").c_str() );
  TFile *out = new TFile( (OutName+".root").c_str(), "RECREATE" );
  TFile *Var = NULL;

  /* define systematics */
  std::vector<std::string> sysVar;
  if(isSignal)
    sysVar = GetSysList(LFVtype,useBjet,true,true,false,false,true,noPtRw);
  else
    sysVar = GetSysList(LFVtype,useBjet,true,true,false,false,false,noPtRw);

  /* define vectors */
  std::vector<TH1F*> Nominal;
  std::vector<TH1F*> Varied;
  std::vector<std::string> names;
  
  /* Define nominal plots */
  TH1F *mllCor_Nom  = (TH1F*)Nom->Get( ("hmllCorr_"+Htype).c_str()  );
  TH1F *mll_Nom     = (TH1F*)Nom->Get( ("hmll_"+Htype).c_str()      );
  TH1F *ptllCor_Nom = (TH1F*)Nom->Get( ("hptllCorr_"+Htype).c_str() );
  TH1F *ptll_Nom    = (TH1F*)Nom->Get( ("hptll_"+Htype).c_str()     );
  TH1F *etall_Nom   = (TH1F*)Nom->Get( ("hetall_"+Htype).c_str()    );
  TH1F *phill_Nom   = (TH1F*)Nom->Get( ("hphill_"+Htype).c_str()    );
  TH1F *njet_Nom    = (TH1F*)Nom->Get( ("hnjet_"+Htype).c_str()     );
  TH1F *met_Nom     = (TH1F*)Nom->Get( ("hmet_"+Htype).c_str()      );
  TH1F *mupt_Nom    = (TH1F*)Nom->Get( ("hmu_pt_"+Htype).c_str()    );
  TH1F *mueta_Nom   = (TH1F*)Nom->Get( ("hmu_eta_"+Htype).c_str()   );
  TH1F *muphi_Nom   = (TH1F*)Nom->Get( ("hmu_phi_"+Htype).c_str()   );
  TH1F *elpt_Nom    = (TH1F*)Nom->Get( ("hel_pt_"+Htype).c_str()    );
  TH1F *eleta_Nom   = (TH1F*)Nom->Get( ("hel_eta_"+Htype).c_str()   );
  TH1F *elphi_Nom   = (TH1F*)Nom->Get( ("hel_phi_"+Htype).c_str()   );
  TH1F *tapt_Nom    = (TH1F*)Nom->Get( ("hta_pt_"+Htype).c_str()    );
  TH1F *taeta_Nom   = (TH1F*)Nom->Get( ("hta_eta_"+Htype).c_str()   );
  TH1F *taphi_Nom   = (TH1F*)Nom->Get( ("hta_phi_"+Htype).c_str()   );
  TH1F *mt_Nom      = (TH1F*)Nom->Get( ("hmt_"+Htype).c_str()       );
  TH1F *mllCor_Nom_Orig = NULL;
  if(LFVtype==2 && (Htype=="BkgTot" || Htype=="Multijet") )
    mllCor_Nom_Orig = (TH1F*)Nom->Get( ("hmllCorr_"+Htype+"_Orig").c_str()   );

  Nominal.push_back( mllCor_Nom  );  Nominal.push_back( mll_Nom   );
  Nominal.push_back( ptllCor_Nom );  Nominal.push_back( ptll_Nom  );
  Nominal.push_back( etall_Nom   );  Nominal.push_back( phill_Nom );
  Nominal.push_back( njet_Nom    );  Nominal.push_back( met_Nom   );   
  Nominal.push_back( mupt_Nom    );  Nominal.push_back( mueta_Nom );
  Nominal.push_back( muphi_Nom   );  Nominal.push_back( elpt_Nom  );
  Nominal.push_back( eleta_Nom   );  Nominal.push_back( elphi_Nom );
  Nominal.push_back( tapt_Nom    );  Nominal.push_back( taeta_Nom );
  Nominal.push_back( taphi_Nom   );  Nominal.push_back( mt_Nom    );
  if(LFVtype==2 && (Htype=="BkgTot" || Htype=="Multijet") )
    Nominal.push_back( mllCor_Nom_Orig );
  
  /* Define varied plots */
  TH1F *mllCor_Var = NULL, *mll_Var   = NULL, *ptllCor_Var = NULL;
  TH1F *ptll_Var   = NULL, *etall_Var = NULL, *phill_Var   = NULL;
  TH1F *njet_Var   = NULL, *met_Var   = NULL, *mt_Var      = NULL;
  TH1F *mupt_Var   = NULL, *mueta_Var = NULL, *muphi_Var   = NULL;
  TH1F *elpt_Var   = NULL, *eleta_Var = NULL, *elphi_Var   = NULL;
  TH1F *tapt_Var   = NULL, *taeta_Var = NULL, *taphi_Var   = NULL;
  TH1F *mllCor_Var_Orig = NULL;

  names.push_back( "mllCorr"  );  names.push_back( "mll"    );
  names.push_back( "ptllCorr" );  names.push_back( "ptll"   );
  names.push_back( "etall"    );  names.push_back( "phill"  );
  names.push_back( "njet"     );  names.push_back( "met"    );
  names.push_back( "mu_pt"    );  names.push_back( "mu_eta" );
  names.push_back( "mu_phi"   );  names.push_back( "el_pt"  );
  names.push_back( "el_eta"   );  names.push_back( "el_phi" );
  names.push_back( "ta_pt"    );  names.push_back( "ta_eta" );
  names.push_back( "ta_phi"   );  names.push_back( "mt"     );
  if(LFVtype==2 && (Htype=="BkgTot" || Htype=="Multijet") )
    names.push_back( "mllCorr_Orig" );

  for(uint i=0; i<sysVar.size(); i++){
    
    std::cout << "< SysPercentVariations() >:: Processing Sys "
	      << sysVar.at(i) << std::endl;

    std::string VarName = Dir+"Plots_"+sysVar.at(i)+"_"+lfvType;
    if(isSignal){ VarName += "_Signals"; }
    if(isBlind) { VarName += "_Blind";   }
    
    Var = new TFile( (VarName+".root").c_str() );
  
    mllCor_Var  = (TH1F*)Var->Get( ("hmllCorr_"+Htype).c_str()  );
    mll_Var     = (TH1F*)Var->Get( ("hmll_"+Htype).c_str()      );
    ptllCor_Var = (TH1F*)Var->Get( ("hptllCorr_"+Htype).c_str() );
    ptll_Var    = (TH1F*)Var->Get( ("hptll_"+Htype).c_str()     );
    etall_Var   = (TH1F*)Var->Get( ("hetall_"+Htype).c_str()    );
    phill_Var   = (TH1F*)Var->Get( ("hphill_"+Htype).c_str()    );
    njet_Var    = (TH1F*)Var->Get( ("hnjet_"+Htype).c_str()     );
    met_Var     = (TH1F*)Var->Get( ("hmet_"+Htype).c_str()      );
    mupt_Var    = (TH1F*)Var->Get( ("hmu_pt_"+Htype).c_str()    );
    mueta_Var   = (TH1F*)Var->Get( ("hmu_eta_"+Htype).c_str()   );
    muphi_Var   = (TH1F*)Var->Get( ("hmu_phi_"+Htype).c_str()   );
    elpt_Var    = (TH1F*)Var->Get( ("hel_pt_"+Htype).c_str()    );
    eleta_Var   = (TH1F*)Var->Get( ("hel_eta_"+Htype).c_str()   );
    elphi_Var   = (TH1F*)Var->Get( ("hel_phi_"+Htype).c_str()   );
    tapt_Var    = (TH1F*)Var->Get( ("hta_pt_"+Htype).c_str()    );
    taeta_Var   = (TH1F*)Var->Get( ("hta_eta_"+Htype).c_str()   );
    taphi_Var   = (TH1F*)Var->Get( ("hta_phi_"+Htype).c_str()   );
    mt_Var      = (TH1F*)Var->Get( ("hmt_"+Htype).c_str()       );
    if(LFVtype==2 && (Htype=="BkgTot" || Htype=="Multijet") )
      mllCor_Var_Orig = (TH1F*)Var->Get( ("hmllCorr_"+Htype+"_Orig").c_str() );

    Varied.push_back( mllCor_Var  );  Varied.push_back( mll_Var   );
    Varied.push_back( ptllCor_Var );  Varied.push_back( ptll_Var  );
    Varied.push_back( etall_Var   );  Varied.push_back( phill_Var );
    Varied.push_back( njet_Var    );  Varied.push_back( met_Var   );   
    Varied.push_back( mupt_Var    );  Varied.push_back( mueta_Var );
    Varied.push_back( muphi_Var   );  Varied.push_back( elpt_Var  );
    Varied.push_back( eleta_Var   );  Varied.push_back( elphi_Var );
    Varied.push_back( tapt_Var    );  Varied.push_back( taeta_Var );
    Varied.push_back( taphi_Var   );  Varied.push_back( mt_Var    );
    if(LFVtype==2 && (Htype=="BkgTot" || Htype=="Multijet") )
      Varied.push_back( mllCor_Var_Orig );
		       
    for(int h=0; h<(int)Nominal.size(); h++){
      std::cout << "< SysPercentVariations > :: making % Variation for"
		<< " distribution = " << names.at(h) << std::endl;

      if(m_debug)
	std::cout << "< SysPercentVariations > :: Distribution = " <<names.at(h)
		  << " -> Bins (Nom,Var) = " <<  Nominal.at(h)->GetNbinsX()
		  << " , " <<  Varied.at(h)->GetNbinsX() << std::endl;
      
      TH1F *ratio = new TH1F();
      ratio = (TH1F*)Nominal.at(h)->Clone( (names.at(h)+"_PercVar_"+sysVar.at(i)).c_str() );
      ratio->Reset();
      ratio->GetXaxis()->SetTitle( Nominal.at(h)->GetXaxis()->GetTitle() );
      for(int b=1; b<Nominal.at(h)->GetNbinsX()+1; b++){
	double diff  = Varied.at(h)->GetBinContent(b)-Nominal.at(h)->GetBinContent(b);
	double den   = Nominal.at(h)->GetBinContent(b);
	double value = 0;
	if(den==0){ value = 0; }
	else{
	  if(rmAbs) value = diff/den;
	  else      value = fabs(diff/den);
	}

	if( sysVar.at(i)=="PDF_Sys" && (LFVtype==2 || LFVtype==3) )
	  if(value!=0) value = value+0.05;

	if(m_debug)
	  std::cout << "< SysPercentVariations > ::       "
		    << " Bin = "<< b << " , Denom = " << den << " , Diff = "
		    << diff << "  -> Value (%) = " << value << std::endl;

	ratio->SetBinContent( b, value*100 );
      }
      ratio->GetYaxis()->SetTitle("Systematic Uncertanty [%]");
      out->cd();
      if(LFVtype==1 && names.at(h).find("ptll")!=std::string::npos)
	ratio->Smooth(2);
      else	
	ratio->Smooth(100);
      ratio->Write( (names.at(h)+"_PercVar_"+sysVar.at(i)).c_str() );
    }
    if(m_debug)
      std::cout << "< SysPercentVariations > :: "
		<< "deleting histograms ... " << std::endl;
    mllCor_Var  -> Delete();
    mll_Var     -> Delete();
    ptllCor_Var -> Delete();
    ptll_Var    -> Delete();
    etall_Var   -> Delete();
    phill_Var   -> Delete();
    njet_Var    -> Delete();
    met_Var     -> Delete();
    mupt_Var    -> Delete();
    mueta_Var   -> Delete();
    muphi_Var   -> Delete();
    elpt_Var    -> Delete();
    eleta_Var   -> Delete();
    elphi_Var   -> Delete();
    tapt_Var    -> Delete();
    taeta_Var   -> Delete();
    taphi_Var   -> Delete();
    mt_Var      -> Delete();
    if(LFVtype==2 && (Htype=="BkgTot" || Htype=="Multijet") )
      mllCor_Var_Orig -> Delete();
    if(m_debug)
      std::cout << "< SysPercentVariations > :: "
		<< "clearing Varied vector ... " << std::endl;
    Varied.clear();
    if(m_debug)
      std::cout << "< SysPercentVariations > :: "
		<< "closing Varied file ... " << std::endl;
    Var->Close();
  }
  mllCor_Nom  -> Delete();
  mll_Nom     -> Delete();
  ptllCor_Nom -> Delete();
  ptll_Nom    -> Delete();
  etall_Nom   -> Delete();
  phill_Nom   -> Delete();
  njet_Nom    -> Delete();
  met_Nom     -> Delete();
  mupt_Nom    -> Delete();
  mueta_Nom   -> Delete();
  muphi_Nom   -> Delete();
  elpt_Nom    -> Delete();
  eleta_Nom   -> Delete();
  elphi_Nom   -> Delete();
  tapt_Nom    -> Delete();
  taeta_Nom   -> Delete();
  taphi_Nom   -> Delete();
  mt_Nom      -> Delete();
  if(LFVtype==2 && (Htype=="BkgTot" || Htype=="Multijet") )
    mllCor_Nom_Orig -> Delete();

  /* Clear Vectors */
  Nominal.clear();
  Varied.clear();
  names.clear();
  sysVar.clear();
  
  /* Closing Files */
  out->Close();
  Nom->Close();

  if(LFVtype>1 && !isSignal){

    std::vector<std::string> addSys;
    addSys.push_back( "SysUp"   );
    addSys.push_back( "SysDown" );
    std::string nPre = "mllCorr_PercVar_TauFake_";

    TFile *outN = new TFile( (OutName+".root").c_str(), "UPDATE" );
    TH1F *Comp = NULL, *BDT = NULL, *Merge = NULL;
    for(uint i=0; i<addSys.size(); i++){
      Comp  = (TH1F*)outN->Get( (nPre+"Comp_"+addSys.at(i)).c_str() );
      BDT   = (TH1F*)outN->Get( (nPre+"BDT_"+addSys.at(i)).c_str()  );
      Merge = (TH1F*)Comp->Clone( (addSys.at(i)+"_tmp").c_str() );
      Merge->Reset();
      
      int Nbins = Comp->GetNbinsX();
      for(int b=1; b<Nbins+1; b++){
	double val_a = BDT->GetBinContent(b);
	double val_b = Comp->GetBinContent(b);
	
	if(val_a>val_b) Merge->SetBinContent(b,val_a);
	else            Merge->SetBinContent(b,val_b);
      }
      outN->cd();
      Merge->Write( (nPre+addSys.at(i)).c_str() );

      /* clean */
      Comp->Delete();
      BDT->Delete();
      Merge->Delete();
    }
    outN->Close();
    addSys.clear();
  }
  
}

void SysPercentVariations(bool useBjet, bool isBlind, bool isttCR,
			  bool isSherpa){
  
  SetATLASStyle();
  TH1::SetDefaultSumw2(kTRUE);

  std::string lfvType = "emu";

  std::cout << " < SysPercentVariation() > :: making sys % variation for "
	    << lfvType << " Channel and Multijet Background"
	    << std::endl;
  
  std::string Dir = "";
  if(useBjet){  Dir += "Bjet/";   }
  else{         Dir += "NoBjet/"; }

  if(isttCR)    {
    Dir += "ttbarCR";
    if(isSherpa) Dir += "_Sherpa";
    Dir += "/";
  }
  
  /* define files */
  std::string NomName = "VarInputs/QCDemu";
  std::string OutName = Dir+"PercentVariations_"+lfvType;
  if(useBjet){ NomName += "_bjetVeto"; }
  if(isBlind){ NomName += "_Blind"; OutName += "_Blind"; }
  if(isttCR){  NomName += "_ttbarCR"; }
  OutName += "_Multijet";

  TFile *Nom = new TFile( (NomName+"_sys.root").c_str() );
  TFile *out = new TFile( (OutName+".root").c_str(), "RECREATE" );
  
  /* define systematics */
  std::vector<std::string> sysVar = GetMultijetSysList();

  /* Define nominal plots */
  TH1F *mll_Nom  = (TH1F*)Nom->Get( "hmllqcd" );

  /* Define varied plots */
  TH1F *mll_Var = NULL;

  for(uint i=0; i<sysVar.size(); i++){
    
    std::cout << "< SysPercentVariations() >:: Processing Sys "
	      << sysVar.at(i) << std::endl;

    mll_Var  = (TH1F*)Nom->Get( ("hmllqcd"+sysVar.at(i)).c_str()  );

    if(m_debug)
      std::cout << "< SysPercentVariations > :: Distribution = mll"
		<< " -> Bins (Nom,Var) = " <<  mll_Nom->GetNbinsX()
		<< " , " <<  mll_Var->GetNbinsX() << std::endl;

    TH1F *ratio = new TH1F();
    ratio = (TH1F*)mll_Nom->Clone( ("mllCorr_PercVar_"+sysVar.at(i)).c_str() );
    ratio->Reset();
    ratio->GetXaxis()->SetTitle( mll_Nom->GetXaxis()->GetTitle() );
    for(int b=1; b<mll_Nom->GetNbinsX()+1; b++){
      double diff  = mll_Var->GetBinContent(b)-mll_Nom->GetBinContent(b);
      double den   = mll_Nom->GetBinContent(b);
      double value = 0;
      if(den==0){ value=0; }
      else{ value = fabs(diff/den); }
      
      if(m_debug)
	std::cout << "< SysPercentVariations > ::       "
		  << " Denom = " << den << " , Diff = " << diff
		  << "  -> Value (%) = " << value << std::endl;
      
      ratio->SetBinContent( b, value*100 );
    }
    ratio->GetYaxis()->SetTitle("Systematic Uncertanty [%]");
    out->cd();
    ratio->Smooth(100);
    ratio->Write( ("mllCorr_PercVar_"+sysVar.at(i)).c_str() );
    
    mll_Var  -> Delete();
  }
  mll_Nom  -> Delete();

  /* Closing Files */
  out->Close();
  Nom->Close();
  
}
