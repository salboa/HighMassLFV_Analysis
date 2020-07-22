/* program includes */
#include "MakeQCD.h"
#include "SysHandler.C"
#include "ATLASstyle.C"

int main( int argc, char* argv[] ) {

  bool useBjet        = false;
  bool printHelp      = false;
  bool isttCR         = false;
  bool isFFcat        = false;
  bool addSys         = false;
  bool isBlind        = false;
  bool isRevDphi      = false;
  bool usePtRw        = false;
  bool scaleWjet      = false;
  bool isSherpa       = false;
  bool useSmooth      = false;
  bool debug          = false;
  int lfvType         = -1;
  std::string nProngs = "";
  std::string charge  = "";
  for(int i = 1; i < argc; ++i){
    if( !strcmp(argv[i],"--useBjet")        ){ useBjet   = true; }
    else if( !strcmp(argv[i],"--lfvType")   ){ lfvType   = std::stoi(argv[i+1]); }
    else if( !strcmp(argv[i],"--nProngs")   ){ nProngs   = argv[i+1]; }  
    else if( !strcmp(argv[i],"--charge")    ){ charge    = argv[i+1]; }
    else if( !strcmp(argv[i],"--addSys")    ){ addSys    = true; }
    else if( !strcmp(argv[i],"--isttCR")    ){ isttCR    = true; }
    else if( !strcmp(argv[i],"--isFFcat")   ){ isFFcat   = true; }
    else if( !strcmp(argv[i],"--isBlind")   ){ isBlind   = true; }
    else if( !strcmp(argv[i],"--isRevDphi") ){ isRevDphi = true; }
    else if( !strcmp(argv[i],"--usePtRw")   ){ usePtRw   = true; }
    else if( !strcmp(argv[i],"--scaleWjet") ){ scaleWjet = true; }
    else if( !strcmp(argv[i],"--isSherpa")  ){ isSherpa  = true; }
    else if( !strcmp(argv[i],"--useSmooth") ){ useSmooth = true; }
    else if( !strcmp(argv[i],"--debug")     ){ debug     = true; }
    else if( !strcmp(argv[i],"--help")      ){ printHelp = true; }
    else{
      if(std::string(argv[i]).find("--")!=std::string::npos)
	std::cout << "WARNING:: Option " << argv[i] << " not recognized: "
		  << "skipping!" << std::endl;
    }
  }
  if(printHelp){
    std::cout << " MakeQCD: make qcd estimation! "               << std::endl;
    std::cout << "               Options: "                      << std::endl;
    std::cout << "                --useBjet   [Enable b-jet veto:"
	      << " default is 'false'] "                         << std::endl;
    std::cout << "                --lfvType   [Choose lfv channel:"
	      << " options 1,2,3']"                              << std::endl;
    std::cout << "                --nProngs   [Choose n-prongs taus:"
	      << " default is '' (no division in 1p or 3p]"      << std::endl;
    std::cout << "                --charge    [Choose ll-charge:"
	      << " default is '' (OS+SS)] "                      << std::endl;
    std::cout << "                --addSys    [Add sytematics:"
	      << " default is 'false'] "                         << std::endl;
    std::cout << "                --isttCR    [Enable ttbar CR:"
	      << " default is 'false'] "                         << std::endl;
    std::cout << "                --isFFcat   [Enable double fake category:"
	      << " default is 'false'] "                         << std::endl;
    std::cout << "                --isBlind   [Enable Blind analysis:"
	      << " default is 'false'] "                         << std::endl;
    std::cout << "                --isRevDphi [Enable revDphi analysis:"
	      << " default is 'false'] "                         << std::endl;
    std::cout << "                --usePtRw   [Enable pT_ll reweighting:"
    	      << " default is 'false'] "                         << std::endl;
    std::cout << "                --scaleWjet [Enable W+jets scaling:"
      	      << " default is 'false'] "                         << std::endl;
    std::cout << "                --isSherpa  [Enable Sherpa ttbar:"
	      << " default is 'false'] "                         << std::endl;
    std::cout << "                --useSmooth [Enable mll smoothing:"
              << " default is 'false'] "                         << std::endl;
    std::cout << "                --debug     [Enable debug]"    << std::endl;
    std::cout << "                --help      [Print this help]" << std::endl;
    exit(0);
  }

  if(lfvType==-1){
    std::cout << "< MakeQCD() >:: lfvType not set!"
	      << " Possible options: 1,2,3" << std::endl;
    exit(0);
  }

  std::cout << "< MakeQCD() >:: Options set " << std::endl;
  std::cout << "                useBjet   = " << useBjet   << std::endl;
  std::cout << "                lfvType   = " << lfvType   << std::endl;
  std::cout << "                nProngs   = " << nProngs   << std::endl;
  std::cout << "                charge    = " << charge    << std::endl;
  std::cout << "                addSys    = " << addSys    << std::endl;
  std::cout << "                isttCR    = " << isttCR    << std::endl;
  std::cout << "                isFFcat   = " << isFFcat   << std::endl;
  std::cout << "                isBlind   = " << isBlind   << std::endl;
  std::cout << "                isRevDphi = " << isRevDphi << std::endl;
  std::cout << "                usePtRw   = " << usePtRw   << std::endl;
  std::cout << "                scaleWjet = " << scaleWjet << std::endl;
  std::cout << "                isSherpa  = " << isSherpa  << std::endl;
  std::cout << "                useSmooth = " << useSmooth << std::endl;
  std::cout << "                debug     = " << debug     << std::endl;

  m_debug = debug;
  
  MakeQCD(lfvType,charge,addSys,useBjet,isttCR,useSmooth,isFFcat,isBlind,
	  isRevDphi,usePtRw,scaleWjet,isSherpa,nProngs);
  
  return 0;
  
}

void MakeQCD(int LFVtype,    std::string charge, bool addSys,    bool useBjet,
	     bool isttCR,    bool useSmooth,     bool isFFcat,   bool isBlind,
	     bool isRevDphi, bool usePtRw,       bool scaleWjet, bool isSherpa,
	     std::string nProngs){

  SetATLASStyle();
  TH1::SetDefaultSumw2(kTRUE);

  std::string lfvType = "";
  if(LFVtype==1)      { lfvType="emu";   }
  else if(LFVtype==2) { lfvType="etau";  }
  else if(LFVtype==3) { lfvType="mutau"; }

  std::cout << "< MakeQCD() >:: Deriving QCD for Channel " << LFVtype << std::endl;
  
  std::string Dir = "";
  if(useBjet){ Dir += "Bjet/";   }
  else{        Dir += "NoBjet/"; }

  bool noPtRw = false;
  if(isttCR)   {
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
    
  for(uint i=0; i<sysVar.size(); i++){

    std::cout << "< MakeQCD() >:: Processing sysVar = " << sysVar.at(i) << std::endl;
    
    if(LFVtype>1)
      MakeQCD_tau(sysVar.at(i), lfvType, Dir, charge, useBjet, isFFcat,
		  isBlind, usePtRw, scaleWjet, nProngs);
    else
      MakeQCD_emu(sysVar.at(i), Dir, useBjet, useSmooth, isBlind, usePtRw);
  }
  
}

void MakeQCD_emu(std::string sysVar, std::string Dir,  bool useBjet,
		 bool useSmooth, bool isBlind, bool usePtRw){
  
  /* open out file */
  std::string fName = Dir+"Plots_"+sysVar+"_emu";
  if(isBlind)  { fName += "_Blind";  }
  if(usePtRw)  { fName += "_PtRw";   }
  if(useSmooth){ fName += "_Smooth"; }

  /* define input files */
  std::string InName = "QCDemu";
  if(useBjet){ InName += "_bjetVeto"; }
  if(isBlind){ InName += "_Blind";    }
  
  m_out = new TFile( (fName+".root").c_str(), "UPDATE");
  
  /* open input distro file */
  if(Dir.find("ttbar")!=std::string::npos)
    m_qcdemu = new TFile( "VarInputs/QCDemu_ttbarCR.root" );
  else
    m_qcdemu = new TFile( ("VarInputs/"+InName+".root").c_str() );
  
  /* Create Base Histograms */
  TH1F *mll    = (TH1F*)m_qcdemu->Get( "hmllqcd"    );
  TH1F *ptll   = (TH1F*)m_qcdemu->Get( "hptllqcd"   );
  TH1F *etall  = (TH1F*)m_qcdemu->Get( "hetallqcd"  ); 
  TH1F *phill  = (TH1F*)m_qcdemu->Get( "hphillqcd"  ); 
  TH1F *met    = (TH1F*)m_qcdemu->Get( "hmetqcd"    );   
  TH1F *njet   = (TH1F*)m_qcdemu->Get( "hnjetqcd"   );  
  TH1F *mu_pt  = (TH1F*)m_qcdemu->Get( "hmu_ptqcd"  ); 
  TH1F *mu_eta = (TH1F*)m_qcdemu->Get( "hmu_etaqcd" );
  TH1F *mu_phi = (TH1F*)m_qcdemu->Get( "hmu_phiqcd" );
  TH1F *el_pt  = (TH1F*)m_qcdemu->Get( "hel_ptqcd"  ); 
  TH1F *el_eta = (TH1F*)m_qcdemu->Get( "hel_etaqcd" );
  TH1F *el_phi = (TH1F*)m_qcdemu->Get( "hel_phiqcd" );
    
  TH1F *ta_pt  = (TH1F*)m_out->Get( "hta_pt_Top"  );  ta_pt->Reset(); 
  TH1F *ta_eta = (TH1F*)m_out->Get( "hta_eta_Top" );  ta_eta->Reset();
  TH1F *ta_phi = (TH1F*)m_out->Get( "hta_phi_Top" );  ta_phi->Reset();
  TH1F *mt     = (TH1F*)m_out->Get( "hmt_Top"     );  mt->Reset();

  if(useSmooth){
    mll->GetXaxis()->SetRangeUser(80.,1000.);
    double qcd=mll->Integral();
    mll->GetXaxis()->SetRangeUser(175.,2500.);
    mll->Smooth(5000,"R");
    mll->Scale(qcd/mll->Integral() );
    for(int b=1; b<mll->GetNbinsX()+1; b++){
      if(b<37) continue;
      if(b==37)
	mll->SetBinContent(b, (mll->GetBinContent(36)+mll->GetBinContent(38))/2.);
      else
	mll->SetBinContent(b,0);
    }
  }
  
  m_out->cd();
  
  /* Write Plots */
  mll    -> Write( "hmllCorr_qcd"  );
  mll    -> Write( "hmll_qcd"      ); 
  ptll   -> Write( "hptllCorr_qcd" );
  ptll   -> Write( "hptll_qcd"     );
  etall  -> Write( "hetall_qcd"    );
  phill  -> Write( "hphill_qcd"    );
  njet   -> Write( "hnjet_qcd"     );
  met    -> Write( "hmet_qcd"      );
  mu_pt  -> Write( "hmu_pt_qcd"    );
  mu_eta -> Write( "hmu_eta_qcd"   );
  mu_phi -> Write( "hmu_phi_qcd"   );
  el_pt  -> Write( "hel_pt_qcd"    );
  el_eta -> Write( "hel_eta_qcd"   );
  el_phi -> Write( "hel_phi_qcd"   );
  ta_pt  -> Write( "hta_pt_qcd"    );
  ta_eta -> Write( "hta_eta_qcd"   );
  ta_phi -> Write( "hta_phi_qcd"   );
  mt     -> Write( "hmt_qcd"       );
  
  if(m_debug){
    std::cout << "< MakeQCD() >:: Checking integrals ... " << std::endl;
    std::cout << "                mll    = " << mll->Integral()    << std::endl;
    std::cout << "                ptll   = " << ptll->Integral()   << std::endl;
    std::cout << "                etall  = " << etall->Integral()  << std::endl;
    std::cout << "                phill  = " << phill->Integral()  << std::endl;
    std::cout << "                met    = " << met->Integral()    << std::endl;
    std::cout << "                njet   = " << njet->Integral()   << std::endl;
    std::cout << "                met    = " << met->Integral()    << std::endl;
    std::cout << "                mu_pt  = " << mu_pt->Integral()  << std::endl;
    std::cout << "                mu_eta = " << mu_eta->Integral() << std::endl;
    std::cout << "                mu_phi = " << mu_phi->Integral() << std::endl;
    std::cout << "                el_pt  = " << el_pt->Integral()  << std::endl;
    std::cout << "                el_eta = " << el_eta->Integral() << std::endl;
    std::cout << "                el_phi = " << el_phi->Integral() << std::endl;
    std::cout << "                ta_pt  = " << ta_pt->Integral()  << std::endl;
    std::cout << "                ta_eta = " << ta_eta->Integral() << std::endl;
    std::cout << "                ta_phi = " << ta_phi->Integral() << std::endl;
    std::cout << "                mt     = " << mt->Integral()     << std::endl;
  }
  /* Cleaning */
  mll    -> Delete();
  ptll   -> Delete();
  etall  -> Delete();
  phill  -> Delete();
  njet   -> Delete();
  met    -> Delete();
  mu_pt  -> Delete();
  mu_eta -> Delete();
  mu_phi -> Delete();
  el_pt  -> Delete();
  el_eta -> Delete();
  el_phi -> Delete();
  ta_pt  -> Delete();
  ta_eta -> Delete();
  ta_phi -> Delete();
  mt     -> Delete();
  
  m_out->Close();
  m_qcdemu->Close();
  
}

double WjetTranFact(TFile *SR, TFile *CR){

  TH1F *wjCR   = (TH1F*)CR->Get( "hmllCorr_Wjets"   );
  TH1F *dataCR = (TH1F*)CR->Get( "hmllCorr_data"    );
  TH1F *DYCR   = (TH1F*)CR->Get( "hmllCorr_DY"      );
  TH1F *TopCR  = (TH1F*)CR->Get( "hmllCorr_Top"     );
  TH1F *DibCR  = (TH1F*)CR->Get( "hmllCorr_DiBoson" );
  TH1F *wjSR   = (TH1F*)SR->Get( "hmllCorr_Wjets"   );

  double SF = wjSR->Integral()/wjCR->Integral();
  double Nd = dataCR->Integral();
  double Nm = DYCR->Integral()+TopCR->Integral()+DibCR->Integral();

  double Nw   = (Nd-Nm)*SF;
  double NwSR = wjSR->Integral();
  double ScFc = Nw/NwSR;
  if(m_debug){
    std::cout << "               WjetTranFact() -->  " << std::endl;
    std::cout << "               Wjet SF = " << SF << " , Ndata (CR) = "
	      << Nd << " , Nmc (CR) = " << Nm << " , Nw (SR) = " << NwSR
	      << " , Exp. Nw = " << Nw << std::endl;
    std::cout << "               ---> ScaleFactor = " << ScFc << std::endl;
  }
  
  return ScFc;
  
}

void MakeQCD_tau(std::string sysVar, std::string lfvType, std::string Dir,
		 std::string charge, bool useBjet,        bool isFFcat,
		 bool isBlind,       bool usePtRw,        bool scaleWjet,
		 std::string nProngs){

  std::string fName = Dir+"Plots_"+sysVar+"_"+lfvType;
  if(nProngs!="") fName += "_"+nProngs;
  if(isBlind){ fName += "_Blind"; }
  if(usePtRw){ fName += "_PtRw";  }

  bool isRevDphi = false, isttCR = false;
  if(Dir.find("revDphi")!=std::string::npos){ isRevDphi = true; }
  if(Dir.find("ttbarCR")!=std::string::npos){ isttCR    = true; }
  
  m_out = new TFile( (fName+".root").c_str(), "UPDATE");
  
  if(sysVar.find("TauFake") != std::string::npos ||
     sysVar.find("Top")     != std::string::npos ||
     sysVar.find("PDF")     != std::string::npos ||
     sysVar.find("PtRw")    != std::string::npos  ){

    CopyFromNominal(Dir,lfvType,useBjet,isBlind);
    return;
    
  }
  
  std::string Suff1="", Suff2="", Suff3="", WjetSuff="";
  if(charge==""){
    Suff1="_SS"; Suff2=""; Suff3="_SS"; WjetSuff="_SS";
  }
  else if(charge=="SS"){
    Suff1="_OS"; Suff2="_SS"; Suff3="_OS"; WjetSuff="_OS";
  }
  else if(charge=="OS"){
    Suff1="_SS"; Suff2="_OS"; Suff3="_SS"; WjetSuff="_SS";
  }
  if(nProngs!=""){
    Suff1+="_"+nProngs; Suff2+="_"+nProngs; Suff3+="_"+nProngs; 
  }
  std::string m_sysVar = sysVar;
  if(sysVar.find("Multijet")!=std::string::npos) m_sysVar = "Nominal";
  
  std::string reg2_Name = Dir+"QcdReg2"+Suff1+"/Plots_"+m_sysVar+"_"+lfvType;
  std::string wjcr_Name = Dir+"WjetCR"+WjetSuff+"/Plots_"+m_sysVar+"_"+lfvType;
  std::string wjsr_Name = Dir+"WjetSR"+WjetSuff+"/Plots_"+m_sysVar+"_"+lfvType;
  std::string reg3_Name = Dir+"QcdReg3";
  std::string reg1_Name = Dir+"QcdReg1";
  if(isFFcat){
    reg3_Name += Suff2+"/Plots_"+m_sysVar+"_"+lfvType;
    reg1_Name += Suff3+"/Plots_"+m_sysVar+"_"+lfvType;
  }
  else{
    reg3_Name += "/LepFake/Plots_"+m_sysVar+"_"+lfvType;
    reg1_Name += "_SS/LepFake/Plots_"+m_sysVar+"_"+lfvType;
  }
  
  if(isBlind){
    reg2_Name += "_Blind";
    wjcr_Name += "_Blind";
    wjsr_Name += "_Blind";
    reg3_Name += "_Blind";
    reg1_Name += "_Blind";
  }
  
  TFile *Reg2 = new TFile( (reg2_Name+".root").c_str() );
  TFile *WjCR = new TFile( (wjcr_Name+".root").c_str() );
  TFile *WjSR = new TFile( (wjsr_Name+".root").c_str() );
  TFile *Reg3 = new TFile( (reg3_Name+".root").c_str() );
  TFile *Reg1 = new TFile( (reg1_Name+".root").c_str() );
  
  double WjTF = WjetTranFact(WjSR,WjCR);

  std::vector<std::string> Names;
  Names.push_back( "hmllCorr"  );
  Names.push_back( "hmll"      );
  Names.push_back( "hptll"     );
  Names.push_back( "hptllCorr" );
  Names.push_back( "hetall"    );
  Names.push_back( "hphill"    );
  Names.push_back( "hmet"      );
  Names.push_back( "hnjet"     );
  Names.push_back( "hmt"       );
  Names.push_back( "hmu_pt"    );
  Names.push_back( "hmu_eta"   );
  Names.push_back( "hmu_phi"   );
  Names.push_back( "hel_pt"    );
  Names.push_back( "hel_eta"   );
  Names.push_back( "hel_phi"   );
  Names.push_back( "hta_pt"    );
  Names.push_back( "hta_eta"   );
  Names.push_back( "hta_phi"   );

  double QcdInt = 0;
  for(uint h=0; h<Names.size(); h++){

    //if(m_debug)
    //std::cout<<" distro "<<Names.at(h)<<std::endl;
    
    TH1F *wjSRSS   = (TH1F*)Reg2->Get( (Names.at(h)+"_Wjets"  ).c_str() );
    TH1F *dataSRSS = (TH1F*)Reg2->Get( (Names.at(h)+"_data"   ).c_str() );
    TH1F *DYSRSS   = (TH1F*)Reg2->Get( (Names.at(h)+"_DY"     ).c_str() );
    TH1F *TopSRSS  = (TH1F*)Reg2->Get( (Names.at(h)+"_Top"    ).c_str() );
    TH1F *DibSRSS  = (TH1F*)Reg2->Get( (Names.at(h)+"_DiBoson").c_str() );

    TH1F *wjCRSS   = (TH1F*)Reg1->Get( (Names.at(h)+"_Wjets"  ).c_str() );
    TH1F *dataCRSS = (TH1F*)Reg1->Get( (Names.at(h)+"_data"   ).c_str() );
    TH1F *DYCRSS   = (TH1F*)Reg1->Get( (Names.at(h)+"_DY"     ).c_str() );
    TH1F *TopCRSS  = (TH1F*)Reg1->Get( (Names.at(h)+"_Top"    ).c_str() );
    TH1F *DibCRSS  = (TH1F*)Reg1->Get( (Names.at(h)+"_DiBoson").c_str() );

    TH1F *wjCR   = (TH1F*)Reg3->Get( (Names.at(h)+"_Wjets"  ).c_str() );
    TH1F *dataCR = (TH1F*)Reg3->Get( (Names.at(h)+"_data"   ).c_str() );
    TH1F *DYCR   = (TH1F*)Reg3->Get( (Names.at(h)+"_DY"     ).c_str() );
    TH1F *TopCR  = (TH1F*)Reg3->Get( (Names.at(h)+"_Top"    ).c_str() );
    TH1F *DibCR  = (TH1F*)Reg3->Get( (Names.at(h)+"_DiBoson").c_str() );

    if(scaleWjet){ wjSRSS->Scale(WjTF); }

    double NqcdSR = dataSRSS->Integral()-
      ( DYSRSS->Integral()+TopSRSS->Integral()+
	DibSRSS->Integral()+wjSRSS->Integral() );
    if(h==0 && m_debug){
      std::cout << "               Nqcd in SR (Reg2) = " << NqcdSR << std::endl;
    }
    TH1F *Reg2 = (TH1F*)dataSRSS->Clone( (Names.at(h)+"_Reg2").c_str() );
    Reg2->Add(wjSRSS, -1);
    Reg2->Add(DYSRSS, -1);
    Reg2->Add(TopSRSS, -1);
    Reg2->Add(DibSRSS, -1);
    
    double NqcdCR = dataCRSS->Integral()-
      ( DYCRSS->Integral()+TopCRSS->Integral()+
	DibCRSS->Integral()+wjCRSS->Integral() );

    TH1F *Reg1 = (TH1F*)dataCRSS->Clone( (Names.at(h)+"_Reg1").c_str() );
    Reg1->Add(wjCRSS, -1);
    Reg1->Add(DYCRSS, -1);
    Reg1->Add(TopCRSS, -1);
    Reg1->Add(DibCRSS, -1);
    
    double SF = NqcdSR/NqcdCR;

    TH1F *k_mj = (TH1F*)TopCRSS->Clone( (Names.at(h)+"_kMj").c_str() );
    k_mj->Reset();
    k_mj->Divide(Reg2,Reg1);
    
    double NumErr2 = ( pow( sqrt(dataSRSS->Integral()),2 ) +
		       pow( sqrt(DYSRSS->Integral()),2 )   +
		       pow( sqrt(TopSRSS->Integral()),2 )  +
		       pow( sqrt(DibSRSS->Integral()),2 )  +
		       pow( sqrt(wjSRSS->Integral()),2  )  )/pow(NqcdCR,2) ;
    
    double DenErr2 = ( pow( sqrt(dataCRSS->Integral()),2 )+
		       pow( sqrt(DYCRSS->Integral()),2 )  +
		       pow( sqrt(TopCRSS->Integral()),2 ) +
		       pow( sqrt(DibCRSS->Integral()),2 ) +
		       pow( sqrt(wjCRSS->Integral()),2 )  )*
      (NqcdSR/pow( NqcdCR,4 ));
    
    double ErrSF = sqrt( NumErr2+DenErr2 );
    
    if(h==0 && m_debug){
      std::cout << "               Nqcd in CR (Reg1) = " << NqcdCR << std::endl;
      std::cout << "               QCD SF = " << SF << " +- " << ErrSF << std::endl;
    }
    
    TH1F* TmpQcd = (TH1F*)dataCR->Clone( (Names.at(h)+"_tmpqcd").c_str() );
    TmpQcd->Add(wjCR, -1);
    TmpQcd->Add(DYCR, -1);
    TmpQcd->Add(TopCR, -1);
    TmpQcd->Add(DibCR, -1);

    if(h==0 && m_debug)
      std::cout << "               Nqcd before Scaling (Reg3) = "
		<< TmpQcd->Integral() << std::endl;

    /* Apply SF */
    if(Names.at(h).find("mll")!=std::string::npos){
      for(int b=1; b<TmpQcd->GetNbinsX()+1; b++){
	double c = TmpQcd->GetBinContent(b);
	double e = TmpQcd->GetBinError(b);
	double v = TmpQcd->GetBinCenter(b);
	double s = k_mj->GetBinContent( k_mj->FindBin(v) );
	/* etau channel */ 
	if(lfvType=="etau"){
	  if(isRevDphi){

	    if(b<7){
	      if(b==3) s=k_mj->GetBinContent( b+1);
	      else     s=k_mj->GetBinContent( b );
	    }
	    else if(b==7) {  s=k_mj->GetBinContent( b+1 ); }
	    else if(b<=25){  s=k_mj->GetBinContent( b );   }
	    else          {  s=k_mj->GetBinContent( 32 );  }
	    
	  }
	  else if(isttCR){

	    if(b<8){
	      if(b<3)     { s=SF*1.8; }
	      else if(b<5){ s=SF*4;   }
	      else        { s=SF*2;   }
	    }
	    else if(b<=25){ s=k_mj->GetBinContent( b );  }
	    else if(b==26){ s=k_mj->GetBinContent( 25 ); }
	    else if(b==27){ s=k_mj->GetBinContent( 25 ); }
	    else if(b==28){ s=k_mj->GetBinContent( 25 )*1.2; }
	    else if(b==29){ s=k_mj->GetBinContent( 25 ); }
	    else          { s=k_mj->GetBinContent( 29 ); }
	    
	  }
	  else{
	    if(sysVar=="Multijet_kMJ_Stat"){
	      
	      double k = 0;
	      //fit variation
	      //if(b==7)      { k=0.1;  s=k_mj->GetBinContent( b+1 ) + k; }
	      //else if(b==14){ k=0.07; s=k_mj->GetBinContent( b )   + k; }
	      //else if(b==20){ k=0.05; s=k_mj->GetBinContent( b )   + k; }
	      //else if(b==21){ k=0.04; s=k_mj->GetBinContent( b )   + k; }
	      //else if(b==22){ k=0.05; s=k_mj->GetBinContent( b )   + k; }
	      //else if(b==24){ k=0.05; s=k_mj->GetBinContent( b )   + k; }
	      //else if(b==25){ k=0.02; s=k_mj->GetBinContent( b )   + k; }
	      //else if(b==26){ k=0.06; s=k_mj->GetBinContent( b )   + k; }
	      //else if(b<27) { k=0.1;  s=k_mj->GetBinContent( b )   + k; }
	      //else if(b==27){ k=0.06; s=k_mj->GetBinContent( b )   + k; }
	      //else if(b==28){ k=0.08; s=k_mj->GetBinContent( b )   + k; }
	      //else if(b==29){ k=0.04; s=k_mj->GetBinContent( b )   + k; }
	      //else if(b==30){ k=0.08; s=k_mj->GetBinContent( b )   + k; }
	      //else if(b==31){ k=0.05; s=k_mj->GetBinContent( b )   + k; }
	      //else if(b<=32){ k=0.09;  s=k_mj->GetBinContent( 27 ) + k; }
	      //else          { k=0.08;  s=k_mj->GetBinContent( 27 ) + k; }

	      //fit confidence
	      if(b==7)      { k=0.04;   s=k_mj->GetBinContent(b+1) + k-0.2*k;  }
	      else if(b==13){ k=0.02;   s=k_mj->GetBinContent(b)   + k-0.2*k;  }
	      else if(b==14){ k=0.015;  s=k_mj->GetBinContent(b)   + k-0.2*k;  }
	      else if(b==20){ k=0.014;  s=k_mj->GetBinContent(b)   + k-0.2*k;  }
	      else if(b==21){ k=0.01;   s=k_mj->GetBinContent(b)   + k-0.2*k;  }
	      else if(b==22){ k=0.015;  s=k_mj->GetBinContent(b)   + k-0.2*k;  }
	      else if(b==24){ k=0.018;  s=k_mj->GetBinContent(b)   + k-0.2*k;  }
	      else if(b==25){ k=0.01;   s=k_mj->GetBinContent(b)   + k-0.2*k;  }
	      else if(b==26){ k=0.033;  s=k_mj->GetBinContent(b)   + k-0.2*k;  }
	      else if(b<27) { k=0.03;   s=k_mj->GetBinContent(b)   + k-0.2*k;  }
	      else if(b==27){ k=0.026;  s=k_mj->GetBinContent(b)   + k-0.2*k;  }
	      else if(b==28){ k=0.048;  s=k_mj->GetBinContent(b)   + k-0.2*k;  }
	      else if(b==29){ k=-0.018; s=k_mj->GetBinContent(b)   + k;        }
	      else if(b==30){ k=0.046;  s=k_mj->GetBinContent(b)   + k-0.2*k;  }
	      else if(b==31){ k=-0.003; s=k_mj->GetBinContent(b)   + k;        }
	      else if(b<=32){ k=0.04;   s=k_mj->GetBinContent(27)  + k-0.12*k; }
	      else          { k=0.04;   s=k_mj->GetBinContent(27)  + k-0.12*k; }
	      
	    }
	    else if(sysVar=="Multijet_kMJ_Sys"){
	      
	      double k = 0;
	      if(b==7)      { k=0.05;   s=k_mj->GetBinContent(b+1) + k+0.3*k; }
	      else if(b==13){ k=0.02;   s=k_mj->GetBinContent(b)   + k+0.3*k; }
	      else if(b==14){ k=0.015;  s=k_mj->GetBinContent(b)   + k+0.3*k; }
	      else if(b==20){ k=0.015;  s=k_mj->GetBinContent(b)   + k+0.3*k; }
	      else if(b==21){ k=0.01;   s=k_mj->GetBinContent(b)   + k+0.3*k; }
	      else if(b==22){ k=0.02;   s=k_mj->GetBinContent(b)   + k+0.3*k; }
	      else if(b==24){ k=0.017;  s=k_mj->GetBinContent(b)   + k+0.3*k; }
	      else if(b==25){ k=-0.018; s=k_mj->GetBinContent(27)  + k;       }
	      else if(b==26){ k=0.03;   s=k_mj->GetBinContent(27)  + k+0.3*k; }
	      else if(b<27) { k=0.03;   s=k_mj->GetBinContent(b)   + k+0.3*k; }
	      else if(b==27){ k=0.007;  s=k_mj->GetBinContent(27)  + k+0.3*k; }
	      else if(b==28){ k=0.0;    s=k_mj->GetBinContent(27)  + k;       }
	      else if(b==29){ k=-0.005; s=k_mj->GetBinContent(27)  + k;       }
	      else if(b==30){ k=-0.007; s=k_mj->GetBinContent(27)  + k;       }
	      else          { k=-0.009; s=k_mj->GetBinContent(27)  + k;       }
	      
	    }
	    else{
	      
	      if(nProngs=="1p"){
		if(b==7)      { s=k_mj->GetBinContent( b+1 ); }
		else if(b<=27){ s=k_mj->GetBinContent( b )  ; }
		else          { s=k_mj->GetBinContent( 27 ) ; }
		
	      }
	      else if(nProngs=="3p"){
		if(b==7)      { s=k_mj->GetBinContent( b+1 ); }
		else if(b<=27){ s=k_mj->GetBinContent( b );   }
		else          { s=k_mj->GetBinContent( 27 ) ; }
	      }
	      else{
		
		if(b==7)      { s=k_mj->GetBinContent( b+1 ); }
		else if(b<=27){ s=k_mj->GetBinContent( b )  ; }
		else          { s=k_mj->GetBinContent( 27 ) ; }
	      }
	      
	    }
	    
	  }
	}
	/* mutau channel */
	else{
	  if(isRevDphi){
	    
	    if(b<8)              { s=k_mj->GetBinContent( b ); }
	    else if(b>29 && b<34){ s=SF*0.4;                   }
	    else                 { s=SF;                       }
	    
	  }
	  else if(isttCR){
	    
	    if( b==18 )               { s=SF*1.8; }
	    else if( b==28 ||
		     (b>23 && b<26) ) { s=SF*1.4; }
	    else if( b>30 && b<33 )   { s=SF*0.4; }
	    else                      { s=SF;     }
	    
	  }
	  else{
	    if(sysVar=="Multijet_kMJ_Sys"){

	      if(b==7)     { s=0.0016;         }
	      else if(b==8){ s=0.23  + 0.4*SF; }
	      else if(b<20){ s=SF    + 0.3*SF; } //added now
	      else if(b<30){ s=SF    + 0.3*SF; } //added now
	      else         { s=SF    + 0.3*SF; }
	      
	    }
	    else if(sysVar=="Multijet_kMJ_Stat"){
	      double k=0;
	      
	      if(b==7)     { k=0.0004; s=0.001 + k;       }
	      else if(b==8){ k=0.02;   s=0.23  + k+0.2*k; }
	      else if(b<20){ k=0.015;  s=SF    + k+0.2*k; } //added now
	      else if(b<30){ k=0.017;  s=SF    + k+0.2*k; } //added now
	      else         { k=0.02;   s=SF    + k+0.2*k; }
	    }
	    else{
	      if(nProngs=="1p"){
		if(b==7)     { s=0.001; }
		else         { s=SF;    }
	      }
	      else if(nProngs=="3p"){
		if(b==7)     { s=0.001; }
		else         { s=SF;    }
	      }
	      else{
		if(b==7)     { s=0.001; }
		else if(b==8){ s=0.23;  }
		else         { s=SF;    }
	      }
	    }
	    
	  }
	}
	TmpQcd->SetBinContent( b, c*s );
	TmpQcd->SetBinError( b, e*s );
      }
      
    }
    else if(Names.at(h).find("el_pt")!=std::string::npos){
      if(lfvType=="etau"){
	for(int b=1; b<TmpQcd->GetNbinsX()+1; b++){
	  double c = TmpQcd->GetBinContent(b);
	  double e = TmpQcd->GetBinError(b);
	  double v = TmpQcd->GetBinCenter(b);
	  double s = k_mj->GetBinContent( k_mj->FindBin(v) );
	  if(isRevDphi){
	    if(b==4)       s = k_mj->GetBinContent(3)*0.53;
	    else if(b==5)  s = k_mj->GetBinContent(3)*0.58;
	    else if(b==6)  s = k_mj->GetBinContent(3)*0.55;
	    else if(b==7)  s = k_mj->GetBinContent(3)*0.4;
	    else if(b==8)  s = k_mj->GetBinContent(3)*0.28;
	    else if(b==9)  s = k_mj->GetBinContent(3)*0.3;
	    else if(b==10) s = k_mj->GetBinContent(3)*0.3;
	  }
	  else if(isttCR){
	    s=SF;
	  }
	  else{
	    if(b==4)       s = k_mj->GetBinContent(3)*0.5;
	    else if(b==5)  s = k_mj->GetBinContent(3)*0.5;
	    else if(b==6)  s = k_mj->GetBinContent(3)*0.2;
	    else if(b>6)   s = SF;
	  }
	  TmpQcd->SetBinContent( b, c*s );
	  TmpQcd->SetBinError( b, e*s );
	}
      }
    }
    else if(Names.at(h).find("ta_pt")!=std::string::npos){
      if(lfvType=="mutau"){
	for(int b=1; b<TmpQcd->GetNbinsX()+1; b++){
	  double c = TmpQcd->GetBinContent(b);
	  double e = TmpQcd->GetBinError(b);
	  double v = TmpQcd->GetBinCenter(b);
	  double s = k_mj->GetBinContent( k_mj->FindBin(v) );
	  if(isRevDphi){
	    if(b==4)       s = k_mj->GetBinContent(3)*0.53;
	    else if(b==5)  s = k_mj->GetBinContent(3)*0.58;
	    else if(b==6)  s = k_mj->GetBinContent(3)*0.55;
	    else if(b==7)  s = k_mj->GetBinContent(3)*0.4;
	    else if(b==8)  s = k_mj->GetBinContent(3)*0.28;
	    else if(b==9)  s = k_mj->GetBinContent(3)*0.3;
	    else if(b==10) s = k_mj->GetBinContent(3)*0.3;
	  }
	  else if(isttCR){
	    s=SF;
	  }
	  else{
	    if(b==4)       s = SF;
	    else if(b==5)  s = SF;
	    else if(b==6)  s = k_mj->GetBinContent(3)*0.4;
	    else if(b==7)  s = k_mj->GetBinContent(3)*2.5;
	    else if(b==8)  s = SF;
	    else if(b==9)  s = SF*1.5;
	    else if(b==10) s = SF;
	  }
	  TmpQcd->SetBinContent( b, c*s );
	  TmpQcd->SetBinError( b, e*s );
	}
      }
      else{
	if(isRevDphi || isttCR){
	  TmpQcd->Scale(SF);
	}
	else{
	  for(int b=1; b<TmpQcd->GetNbinsX()+1; b++){
	    double c = TmpQcd->GetBinContent(b);
	    double e = TmpQcd->GetBinError(b);
	    double v = TmpQcd->GetBinCenter(b);
	    double s = k_mj->GetBinContent( k_mj->FindBin(v) );
	    if(b==4)       s = k_mj->GetBinContent(3)*0.9;
	    else if(b==5)  s = k_mj->GetBinContent(3)*0.8;
	    else if(b==6)  s = SF;
	    else if(b==7)  s = SF*0.6;
	    else if(b>7)   s = SF;
	    TmpQcd->SetBinContent( b, c*s );
	    TmpQcd->SetBinError( b, e*s );
	  }
	}
      }
    }
    else if(Names.at(h).find("mu_pt")!=std::string::npos){
      if(lfvType=="mutau"){
	for(int b=1; b<TmpQcd->GetNbinsX()+1; b++){
	  double c = TmpQcd->GetBinContent(b);
	  double e = TmpQcd->GetBinError(b);
	  double v = TmpQcd->GetBinCenter(b);
	  double s = k_mj->GetBinContent( k_mj->FindBin(v) );
	  if(isRevDphi || isttCR){
	    s=SF;
	  }
	  else{
	    if(b==3)       s = SF;
	    if(b==4)       s = k_mj->GetBinContent(3)*0.8;
	    else if(b>4)   s = SF;
	  }
	  TmpQcd->SetBinContent( b, c*s );
	  TmpQcd->SetBinError( b, e*s );
	}
      }
    }
    else{
      TmpQcd->Scale(SF);
    }
    
    QcdInt = TmpQcd->Integral();
    if(h==0 && m_debug){
      std::cout << "               Nqcd from TH1F Subtraction = "
		<< QcdInt << std::endl;
    }
    TH1F* qcd = (TH1F*)TmpQcd->Clone( (Names.at(h)+"_qcd").c_str() );
    qcd->Reset();
        
    for(int b=1; b<TmpQcd->GetNbinsX()+1; b++){
      double x   = TmpQcd->GetBinContent(b);
      double err = TmpQcd->GetBinError(b);
      if(x<0) x=0;
      qcd->SetBinContent(b, x);
      qcd->SetBinError(b, err);
    }
    //qcd->Draw();
    if(h==0 && m_debug){
      std::cout << "               Nqcd after setting neg. bins to zero = "
		<< qcd->Integral() << std::endl;
    }
    if(qcd->Integral()!=0) qcd->Scale( fabs(QcdInt)/qcd->Integral() );
    if(h==0 && m_debug)
      std::cout << "               Nqcd final = " << qcd->Integral() << std::endl;

    TH1F *qcdNorm=qcd;//NULL;
    //if(Names.at(h)=="hmllCorr" || Names.at(h)=="hmll")
    //qcdNorm = ChangeShape(qcd);
    
    /* Writing */
    m_out->cd();
    if( lfvType=="etau" && (Names.at(h)=="hmllCorr" || Names.at(h)=="hmll") ){
      qcd->Write( (Names.at(h)+"_qcd_Orig").c_str() );
      qcdNorm->Write( (Names.at(h)+"_qcd").c_str() );
    }
    else
      qcd->Write();
    /* Cleaning */
    qcd->Delete();
    if(Names.at(h)=="mllCorr" || Names.at(h)=="mll")
      qcdNorm->Delete();
    Reg1->Delete();
    Reg2->Delete();
    TmpQcd->Delete();
    wjSRSS->Delete();
    dataSRSS->Delete();
    DYSRSS->Delete();
    TopSRSS->Delete();
    DibSRSS->Delete();
    wjCRSS->Delete();
    dataCRSS->Delete();
    DYCRSS->Delete();
    TopCRSS->Delete();
    DibCRSS->Delete();
    wjCR->Delete();
    dataCR->Delete();
    DYCR->Delete();
    TopCR->Delete();
    DibCR->Delete();
  }
  
  /* cleaning */
  m_out->Close();
  Reg2->Close();
  WjCR->Close();
  WjSR->Close();
  Reg3->Close();
  Reg1->Close();
  
  if(m_debug)
    std::cout<<""<<std::endl;
  
}

void CopyFromNominal(std::string Dir, std::string lfvType,
		     bool useBjet, bool isBlind){

  TFile *Nom = NULL;
  if(isBlind)
    Nom = new TFile( (Dir+"Plots_Nominal_"+lfvType+"_Blind.root").c_str() );
  else
    Nom = new TFile( (Dir+"Plots_Nominal_"+lfvType+".root").c_str() );

  TH1F *mllC   = (TH1F*)Nom->Get( "hmllCorr_qcd"  );
  TH1F *mll    = (TH1F*)Nom->Get( "hmll_qcd"      );
  TH1F *ptllC  = (TH1F*)Nom->Get( "hptllCorr_qcd" );
  TH1F *ptll   = (TH1F*)Nom->Get( "hptll_qcd"     );
  TH1F *etall  = (TH1F*)Nom->Get( "hetall_qcd"    ); 
  TH1F *phill  = (TH1F*)Nom->Get( "hphill_qcd"    ); 
  TH1F *met    = (TH1F*)Nom->Get( "hmet_qcd"      );   
  TH1F *njet   = (TH1F*)Nom->Get( "hnjet_qcd"     );
  TH1F *mt     = (TH1F*)Nom->Get( "hmt_qcd"       );  
  TH1F *mu_pt  = (TH1F*)Nom->Get( "hmu_pt_qcd"    ); 
  TH1F *mu_eta = (TH1F*)Nom->Get( "hmu_eta_qcd"   );
  TH1F *mu_phi = (TH1F*)Nom->Get( "hmu_phi_qcd"   );
  TH1F *el_pt  = (TH1F*)Nom->Get( "hel_pt_qcd"    ); 
  TH1F *el_eta = (TH1F*)Nom->Get( "hel_eta_qcd"   );
  TH1F *el_phi = (TH1F*)Nom->Get( "hel_phi_qcd"   );
  TH1F *ta_pt  = (TH1F*)Nom->Get( "hta_pt_qcd"    );
  TH1F *ta_eta = (TH1F*)Nom->Get( "hta_eta_qcd"   );
  TH1F *ta_phi = (TH1F*)Nom->Get( "hta_phi_qcd"   );
  TH1F *mllC_Or = NULL;
  if(lfvType=="etau")
    mllC_Or = (TH1F*)Nom->Get( "hmllCorr_qcd_Orig"  );

  m_out->cd();
  mllC   -> Write( "hmllCorr_qcd"  );
  mll    -> Write( "hmll_qcd"      );
  ptllC  -> Write( "hptllCorr_qcd" );
  ptll   -> Write( "hptll_qcd"     );
  etall  -> Write( "hetall_qcd"    ); 
  phill  -> Write( "hphill_qcd"    ); 
  met    -> Write( "hmet_qcd"      ); 
  njet   -> Write( "hnjet_qcd"     );
  mt     -> Write( "hmt_qcd"       );
  mu_pt  -> Write( "hmu_pt_qcd"    );
  mu_eta -> Write( "hmu_eta_qcd"   );
  mu_phi -> Write( "hmu_phi_qcd"   );
  el_pt  -> Write( "hel_pt_qcd"    );
  el_eta -> Write( "hel_eta_qcd"   );
  el_phi -> Write( "hel_phi_qcd"   );
  ta_pt  -> Write( "hta_pt_qcd"    );
  ta_eta -> Write( "hta_eta_qcd"   );
  ta_phi -> Write( "hta_phi_qcd"   );
  if(lfvType=="etau")
    mllC_Or -> Write( "hmllCorr_qcd_Orig" );

  mllC   -> Delete();
  mll    -> Delete();
  ptllC  -> Delete();
  ptll   -> Delete();
  etall  -> Delete();
  phill  -> Delete();
  met    -> Delete();
  njet   -> Delete();
  mt     -> Delete();
  mu_pt  -> Delete();
  mu_eta -> Delete();
  mu_phi -> Delete();
  el_pt  -> Delete();
  el_eta -> Delete();
  el_phi -> Delete();
  ta_pt  -> Delete();
  ta_eta -> Delete();
  ta_phi -> Delete();
  if(lfvType=="etau")
    mllC_Or -> Delete();
  
  m_out->Close();
  Nom->Close();
  
}

TH1F *ChangeShape(TH1F*qcd){

  int Bins = qcd->GetNbinsX();
  TH1F *qcdNew = (TH1F*)qcd->Clone("tmp");
  qcdNew->Reset();
  
  for(int i=1; i<Bins+1; i++){
    double c = qcd->GetBinContent(i);
    double e = qcd->GetBinError(i);
    /* 60 bins */
    if(i<=9){
      qcdNew->SetBinContent(i,c+c*1.40);//1.10
    }
    else if(i>=10 && i<=12)
      qcdNew->SetBinContent(i,c+c*0.80);
    else if(i>=21 && i<=24)
      qcdNew->SetBinContent(i,c-c*0.55);//0.55
    else if(i>=25){
      qcdNew->SetBinContent(i,c-c*0.65);//0.55
    }
    else
      qcdNew->SetBinContent(i,c);

    /* 80 bins -> 40 bins */
    //if(i<=11){
    //  qcdNew->SetBinContent(i,c+c*1.40);//1.10
    //}
    //else if(i>=12 && i<=17){//16
    //  qcdNew->SetBinContent(i,c+c*0.20);
    //  
    //}
    //else if(i>=28 && i<=31){
    //  qcdNew->SetBinContent(i,c-c*0.40);
    //}
    //else if(i>=32){
    //  qcdNew->SetBinContent(i,c-c*0.65);//0.55
    //}
    //else
    //  qcdNew->SetBinContent(i,c);
    qcdNew->SetBinError(i,e);
  }

  return qcdNew;
  
}
