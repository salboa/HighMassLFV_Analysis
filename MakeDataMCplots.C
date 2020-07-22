/* program includes */
#include "MakeDataMCplots.h"
#include "Utils.C"

int main( int argc, char* argv[] ) {

  int lfvType        = -1;
  std::string Htype  = "mllCorr";
  bool useSysBand    = false;
  bool addStatInBand = false;
  bool useData       = false;
  bool isBlindData   = false;
  bool isBlind       = false;
  bool isttCR        = false;
  bool isRevDphi     = false;
  bool isSherpa      = false;
  bool useBjet       = false;
  bool useErrOnBkg   = false;
  bool usePtRw       = false;
  bool useSignal     = false;
  bool useGUI        = false;
  bool showQCD       = false;
  bool useSmooth     = false;
  bool printHelp     = false;
  std::string inDir = "";
  std::string sigMp = "1500";
  for(int i = 1; i < argc; ++i){
    if( !strcmp(argv[i],"--lfvType")            ){ lfvType       = std::stoi(argv[i+1]); }
    else if( !strcmp(argv[i],"--Htype")         ){ Htype         = argv[i+1]; }
    else if( !strcmp(argv[i],"--inDir")         ){ inDir         = argv[i+1]; }
    else if( !strcmp(argv[i],"--sigMp")         ){ sigMp         = argv[i+1]; }
    else if( !strcmp(argv[i],"--useSysBand")    ){ useSysBand    = true;      }
    else if( !strcmp(argv[i],"--addStatInBand") ){ addStatInBand = true;      }
    else if( !strcmp(argv[i],"--useData")       ){ useData       = true;      }
    else if( !strcmp(argv[i],"--isBlindData")   ){ isBlindData   = true;      }
    else if( !strcmp(argv[i],"--isBlind")       ){ isBlind       = true;      }
    else if( !strcmp(argv[i],"--isttCR")        ){ isttCR        = true;      }
    else if( !strcmp(argv[i],"--isRevDphi")     ){ isRevDphi     = true;      }
    else if( !strcmp(argv[i],"--isSherpa")      ){ isSherpa      = true;      }
    else if( !strcmp(argv[i],"--useBjet")       ){ useBjet       = true;      }
    else if( !strcmp(argv[i],"--useErrOnBkg")   ){ useErrOnBkg   = true;      }
    else if( !strcmp(argv[i],"--usePtRw")       ){ usePtRw       = true;      }
    else if( !strcmp(argv[i],"--useSignal")     ){ useSignal     = true;      }
    else if( !strcmp(argv[i],"--useGUI")        ){ useGUI        = true;      }
    else if( !strcmp(argv[i],"--showQCD")       ){ showQCD       = true;      }
    else if( !strcmp(argv[i],"--useSmooth")     ){ useSmooth     = true;      }
    else if( !strcmp(argv[i],"--help")          ){ printHelp     = true;      }
    else{
      if(std::string(argv[i]).find("--")!=std::string::npos)
	std::cout << "WARNING:: Option " << argv[i] << " not recognized: "
		  << "skipping!" << std::endl;
    }
  }
  if(printHelp){
    std::cout << " MakeSystPlots: make syst. uncert. plots!"  << std::endl;
    std::cout << "                 Options: "                 << std::endl;
    std::cout << "                  --lfvType       [Choose lfv channel: "
	      << " options 1,2,3']"                           << std::endl;
    std::cout << "                  --Htype         [Choose distribution: "
	      << " default is 'mllCorr']"                     << std::endl;
    std::cout << "                  --inDir         [Choose input Directory: "
	      << " default is '']"                            << std::endl;
    std::cout << "                  --sigMp         [Choose signal Mass point: "
	      << " default is '1500']"                        << std::endl;
    std::cout << "                  --useSysBand    [Enable drawing Sys Band: "
	      << " default is 'false'] "                      << std::endl;
    std::cout << "                  --addStatInBand [Enable StatErr in Sys Band: "
	      << " default is 'false'] "                      << std::endl;
    std::cout << "                  --useData       [Enable drawing data: "
	      << " default is 'false'] "                      << std::endl;
    std::cout << "                  --isBlindData   [Enable Blind mode for data:"
      	      << " default is 'false'] "                      << std::endl;
    std::cout << "                  --isBlind       [Enable Blind analysis: "
	      << " default is 'false'] "                      << std::endl;
    std::cout << "                  --isttCR        [Enable ttbar CR mode: "
	      << " default is 'false'] "                      << std::endl;
    std::cout << "                  --isRevDphi     [Enable revDphi mode: "
	      << " default is 'false'] "                      << std::endl;
    std::cout << "                  --isSherpa      [Enable Sherpa MC: "
	      << " default is 'false'] "                      << std::endl;
    std::cout << "                  --useBjet       [Enable b-jet veto:"
	      << " default is 'false'] "                      << std::endl;
    std::cout << "                  --useErrOnBkg   [Enable errors on Bkg: "
	      << " default is 'false'] "                      << std::endl;
    std::cout << "                  --usePtRw       [Enable pT_ll reweighting: "
	      << " default is 'false'] "                      << std::endl;
    std::cout << "                  --useSignal     [Enable drawing signals: "
	      << " default is 'false'] "                      << std::endl;
    std::cout << "                  --useGUI        [Enable GUI mode:"
	      << " default is 'false'] "                      << std::endl;
    std::cout << "                  --showQCD       [Enable Multijet splitting:"
      	      << " default is 'false'] "                      << std::endl;
    std::cout << "                  --useSmooth     [Enable smoothed qcd mll:"
	      << " default is 'false'] "                      << std::endl;
    std::cout << "                  --help          [Print this help]"
	      << std::endl;
    exit(0);
  }
  
  if(lfvType==-1){
    std::cout << "< MakeDataMCPlots() >:: lfvType not set!"
	      << " Possible options: 1,2,3" << std::endl;
    exit(0);
  }

  std::cout << " MakeDataMCplots Options set: "                      << std::endl;
  std::cout << "                  lfvType       = " << lfvType       << std::endl;
  std::cout << "                  Htype         = " << Htype         << std::endl;
  std::cout << "                  inDir         = " << inDir         << std::endl;
  std::cout << "                  sigMp         = " << sigMp         << std::endl;
  std::cout << "                  useSysBand    = " << useSysBand    << std::endl;
  std::cout << "                  addStatInBand = " << addStatInBand << std::endl;
  std::cout << "                  useData       = " << useData       << std::endl;
  std::cout << "                  isBlindData   = " << isBlindData   << std::endl;
  std::cout << "                  isBlind       = " << isBlind       << std::endl;
  std::cout << "                  isttCR        = " << isttCR        << std::endl;
  std::cout << "                  isRevDphi     = " << isRevDphi     << std::endl;
  std::cout << "                  isSherpa      = " << isSherpa      << std::endl;
  std::cout << "                  useBjet       = " << useBjet       << std::endl;
  std::cout << "                  useErrOnBkg   = " << useErrOnBkg   << std::endl;
  std::cout << "                  usePtRw       = " << usePtRw       << std::endl;
  std::cout << "                  useSignal     = " << useSignal     << std::endl;
  std::cout << "                  useGUI        = " << useGUI        << std::endl;
  std::cout << "                  showQCD       = " << showQCD       << std::endl;
  std::cout << "                  useSmooth     = " << useSmooth     << std::endl;
  
  m_useSysBand    = useSysBand;
  m_addStatInBand = addStatInBand;
  m_useData       = useData;
  m_showQCD       = showQCD;
  m_isBlindData   = isBlindData;
  m_isBlind       = isBlind;
  m_isttCR        = isttCR;
  m_isRevDphi     = isRevDphi;
  m_isSherpa      = isSherpa;
  m_useBjet       = useBjet;
  m_useErrOnBkg   = useErrOnBkg;
  m_usePtRw       = usePtRw;
  m_useSignal     = useSignal;
  m_useSmooth     = useSmooth;

  TRint *myApp = new TRint("RootSession",&argc,argv,NULL,0);
  MakePlots(lfvType, Htype, inDir, sigMp);
  
  if(useGUI){
    std::cout << "< MakeDataMCplots() >:: using Rint -> ROOT will remain "
	      << "opened ... " << std::endl;
    myApp->Run();
  }

  return 0;
  
}

TLine* DefineHorizLine(Double_t Yval,
		       Double_t Xmin,
		       Double_t Xmax){

  TLine *lin = new TLine(Xmin,Yval,Xmax,Yval);
  return lin;
  
}

void PrintYieldRegions(std::vector<TH1F*> Plots,
		       std::vector<TH1F*> Systs){
  
  Double_t StatErr;
  int B600  = Plots.at(4)->FindBin(600);
  int BEnd  = Plots.at(4)->GetNbinsX()+1;
  
  std::vector<TH1F*> OrdPlots;         std::vector<std::string> Names;
  OrdPlots.push_back( Plots.at(4) );   Names.push_back( "Top" );
  OrdPlots.push_back( Plots.at(3) );   Names.push_back( "DiBoson" );
  OrdPlots.push_back( Plots.at(2) );   Names.push_back( "QCD-Wjets" );
  OrdPlots.push_back( Plots.at(1) );   Names.push_back( "Drell-Yan" );
  OrdPlots.push_back( Plots.at(5) );   Names.push_back( "MC Total" );
  OrdPlots.push_back( Plots.at(0) );   Names.push_back( "data" );

  TH1F *TopUp = (TH1F*)Plots.at(4)->Clone("Top_Up");
  TopUp->Reset();
  TH1F *DbUp  = (TH1F*)Plots.at(3)->Clone("Db_Up");
  DbUp->Reset();
  TH1F *DYUp  = (TH1F*)Plots.at(1)->Clone("DY_Up");
  DYUp->Reset();
  TH1F *QCDUp = (TH1F*)Plots.at(2)->Clone("QCD_Up");
  QCDUp->Reset();
  TH1F *BkgUp = (TH1F*)Plots.at(5)->Clone("Bkg_Up");
  BkgUp->Reset();

  for(int b=1; b<BEnd; b++){
    TopUp->SetBinContent( b, Plots.at(4)->GetBinContent(b)+
			  (Plots.at(4)->GetBinContent(b)*
			   Systs.at(1)->GetBinContent(b)/100) ); //at(0)
    DbUp->SetBinContent(  b, Plots.at(3)->GetBinContent(b)+
			  (Plots.at(3)->GetBinContent(b)*
			   Systs.at(2)->GetBinContent(b)/100) );
    DYUp->SetBinContent(  b, Plots.at(1)->GetBinContent(b)+
			  (Plots.at(1)->GetBinContent(b)*
			   Systs.at(3)->GetBinContent(b)/100) );
    QCDUp->SetBinContent( b, Plots.at(2)->GetBinContent(b)+
			  (Plots.at(2)->GetBinContent(b)*
			   Systs.at(4)->GetBinContent(b)/100) );
    BkgUp->SetBinContent( b, Plots.at(5)->GetBinContent(b)+
			  (Plots.at(5)->GetBinContent(b)*
			   Systs.at(0)->GetBinContent(b)/100) );
  }
  std::cout<<"Bkgup integral "<<BkgUp->Integral()<<std::endl;

  std::vector<TH1F*> SystVar;
  SystVar.push_back(TopUp);
  SystVar.push_back(DbUp); 
  SystVar.push_back(QCDUp);
  SystVar.push_back(DYUp); 
  SystVar.push_back(BkgUp);

  std::vector<double> Y1, Y2;
  std::vector<double> Sta1, Sta2;
  std::vector<double> Sys1, Sys2;
  std::vector<double> CbE1, CbE2;
  std::vector<std::vector<double> > Yie, Sta, Sys, CbEr;
  Yie.push_back(Y1);  Sta.push_back(Sta1);  Sys.push_back(Sys1);  CbEr.push_back(CbE1);
  Yie.push_back(Y2);  Sta.push_back(Sta2);  Sys.push_back(Sys2);  CbEr.push_back(CbE2);
  std::vector<int> Bins;    std::vector<std::string> RegName;
  Bins.push_back(-1);       RegName.push_back( "mll < 600 GeV" );
  Bins.push_back(B600);	    RegName.push_back( "mll > 600 GeV" );
  Bins.push_back(BEnd);
  
  Plots.at(4)->IntegralAndError(0,0,StatErr);

  /* Fill Yield, Stat and Syst Errors */
  for(uint b=1; b<Bins.size(); b++){
    for(uint h=0; h<OrdPlots.size(); h++){
      if(h==OrdPlots.size()-1){
	Yie.at(b-1).push_back( OrdPlots.at(h)->Integral(Bins.at(b-1)+1,Bins.at(b)) );
	Sta.at(b-1).push_back( 0 );
	Sys.at(b-1).push_back( 0 );
      }
      else{
	Yie.at(b-1).push_back( OrdPlots.at(h)->IntegralAndError(Bins.at(b-1)+1,
								Bins.at(b),
								StatErr) );
	//if(h==2)
	//Sta.at(b-1).push_back( sqrt(OrdPlots.at(h)->Integral(Bins.at(b-1)+1,
	//Bins.at(b) ) ) );
	//else
	Sta.at(b-1).push_back( StatErr );
	Sys.at(b-1).push_back( SystVar.at(h)->Integral( Bins.at(b-1)+1,
							Bins.at(b) )
			       -OrdPlots.at(h)->Integral( Bins.at(b-1)+1,
							  Bins.at(b) ) );
	CbEr.at(b-1).push_back( sqrt( pow(StatErr,2) +
				      pow(SystVar.at(h)->Integral( Bins.at(b-1)+1,
								   Bins.at(b) )
					  -OrdPlots.at(h)->Integral( Bins.at(b-1)+1,
								     Bins.at(b) ), 2) ) );
	
      }
    }
  }
  std::cout<<" "<<std::endl;
  //std::cout<<" Yields  :"<<std::endl;
  std::cout<<" Yields   :             Value              StatErr"
	   <<"           SystErr            CombErr"<<std::endl;
  std::cout<<" "<<std::endl;
  for(uint b=1; b<Bins.size(); b++){
    std::cout << "        " << RegName.at(b-1) << std::endl;
    for(uint h=0; h<Names.size(); h++){
    
      if(h!=Names.size()-1){
	std::cout.width(15); std::cout << Names.at(h);
	std::cout.width(15); std::cout << Yie.at(b-1).at(h)  << " +- ";
	std::cout.width(15); std::cout << Sta.at(b-1).at(h)  << " +- ";
	std::cout.width(15); std::cout << Sys.at(b-1).at(h)  << " +- ";
	std::cout.width(15); std::cout << CbEr.at(b-1).at(h) << std::endl;
      }
      else{
	std::cout.width(15); std::cout << Names.at(h);
	std::cout.width(15); std::cout << Yie.at(b-1).at(h) << std::endl;
      }
    }
    std::cout << "        " << std::endl;
  }
  
}

void PrintYields(std::vector<TH1F*> Plots,
		 std::vector<TH1F*> Systs){

  Double_t StatErr;
  int B300  = Plots.at(4)->FindBin(300);
  int B600  = Plots.at(4)->FindBin(600);
  int B1200 = Plots.at(4)->FindBin(1200);
  int B2000 = Plots.at(4)->FindBin(2000);
  int B3000 = Plots.at(4)->FindBin(3000);
  int BEnd  = Plots.at(4)->GetNbinsX()+1;
  
  std::vector<TH1F*> OrdPlots;         std::vector<std::string> Names;
  OrdPlots.push_back( Plots.at(4) );   Names.push_back( "Top" );
  OrdPlots.push_back( Plots.at(3) );   Names.push_back( "DiBoson" );
  OrdPlots.push_back( Plots.at(2) );   Names.push_back( "QCD-Wjets" );
  OrdPlots.push_back( Plots.at(1) );   Names.push_back( "Drell-Yan" );
  OrdPlots.push_back( Plots.at(5) );   Names.push_back( "MC Total" );
  OrdPlots.push_back( Plots.at(0) );   Names.push_back( "data" );
  
  TH1F *TopUp = (TH1F*)Plots.at(4)->Clone("Top_Up");
  TopUp->Reset();
  TH1F *DbUp  = (TH1F*)Plots.at(3)->Clone("Db_Up");
  DbUp->Reset();
  TH1F *DYUp  = (TH1F*)Plots.at(1)->Clone("DY_Up");
  DYUp->Reset();
  TH1F *QCDUp = (TH1F*)Plots.at(2)->Clone("QCD_Up");
  QCDUp->Reset();
  TH1F *BkgUp = (TH1F*)Plots.at(5)->Clone("Bkg_Up");
  BkgUp->Reset();
  
  for(int b=1; b<BEnd; b++){
    TopUp->SetBinContent( b, Plots.at(4)->GetBinContent(b)+
  			  (Plots.at(4)->GetBinContent(b)*
  			   Systs.at(1)->GetBinContent(b)/100) ); //at.(0)
    DbUp->SetBinContent(  b, Plots.at(3)->GetBinContent(b)+
			  (Plots.at(3)->GetBinContent(b)*
			   Systs.at(2)->GetBinContent(b)/100) );
    DYUp->SetBinContent(  b, Plots.at(1)->GetBinContent(b)+
			  (Plots.at(1)->GetBinContent(b)*
			   Systs.at(3)->GetBinContent(b)/100) );
    QCDUp->SetBinContent( b, Plots.at(2)->GetBinContent(b)+
  			  (Plots.at(2)->GetBinContent(b)*
  			   Systs.at(4)->GetBinContent(b)/100) );
    BkgUp->SetBinContent( b, Plots.at(5)->GetBinContent(b)+
  			  (Plots.at(5)->GetBinContent(b)*
  			   Systs.at(0)->GetBinContent(b)/100) );
  }
  
  std::vector<TH1F*> SystVar;
  SystVar.push_back(TopUp);
  SystVar.push_back(DbUp); 
  SystVar.push_back(QCDUp);
  SystVar.push_back(DYUp); 
  SystVar.push_back(BkgUp);
  
  std::vector<double> Y1, Y2, Y3, Y4, Y5, Y6;
  std::vector<double> Sta1, Sta2, Sta3, Sta4, Sta5, Sta6;
  std::vector<double> Sys1, Sys2, Sys3, Sys4, Sys5, Sys6;
  std::vector<double> CbE1, CbE2, CbE3, CbE4, CbE5, CbE6;
  std::vector<std::vector<double> > Yie, Sta, Sys, CbEr;
  Yie.push_back(Y1);  Sta.push_back(Sta1);  Sys.push_back(Sys1);  CbEr.push_back(CbE1);
  Yie.push_back(Y2);  Sta.push_back(Sta2);  Sys.push_back(Sys2);  CbEr.push_back(CbE2);
  Yie.push_back(Y3);  Sta.push_back(Sta3);  Sys.push_back(Sys3);  CbEr.push_back(CbE3);
  Yie.push_back(Y4);  Sta.push_back(Sta4);  Sys.push_back(Sys4);  CbEr.push_back(CbE4);
  Yie.push_back(Y5);  Sta.push_back(Sta5);  Sys.push_back(Sys5);  CbEr.push_back(CbE5);
  Yie.push_back(Y6);  Sta.push_back(Sta6);  Sys.push_back(Sys6);  CbEr.push_back(CbE6);
  
  std::vector<int> Bins;    std::vector<std::string> RegName;
  Bins.push_back(-1);       RegName.push_back( "mll < 300 GeV " );
  Bins.push_back(B300);	    RegName.push_back( "300 < mll < 600 GeV" );
  Bins.push_back(B600);	    RegName.push_back( "600 < mll< 1200 GeV" );
  Bins.push_back(B1200);    RegName.push_back( "1200 < mll < 2000 GeV" );
  Bins.push_back(B2000);    RegName.push_back( "2000 < mll < 3000 GeV" );
  Bins.push_back(B3000);    RegName.push_back( "mll > 3000 GeV" );
  Bins.push_back(BEnd);
  
  Plots.at(4)->IntegralAndError(0,0,StatErr);
  
  /* Fill Yield, Stat and Syst Errors */
  for(uint b=1; b<Bins.size(); b++){
    for(uint h=0; h<OrdPlots.size(); h++){
      if(h==OrdPlots.size()-1){
  	Yie.at(b-1).push_back( OrdPlots.at(h)->Integral(Bins.at(b-1)+1,Bins.at(b)) );
  	Sta.at(b-1).push_back( 0 );
  	Sys.at(b-1).push_back( 0 );
      }
      else{
  	Yie.at(b-1).push_back( OrdPlots.at(h)->IntegralAndError(Bins.at(b-1)+1,
  								Bins.at(b),
  								StatErr) );
  	//if(h==2)
  	//Sta.at(b-1).push_back( sqrt(OrdPlots.at(h)->Integral(Bins.at(b-1)+1,
  	//Bins.at(b) ) ) );
  	//else
  	Sta.at(b-1).push_back( StatErr );
  	Sys.at(b-1).push_back( SystVar.at(h)->Integral( Bins.at(b-1)+1,
  							Bins.at(b) )
  			       -OrdPlots.at(h)->Integral( Bins.at(b-1)+1,
  							  Bins.at(b) ) );
  	CbEr.at(b-1).push_back( sqrt( pow(StatErr,2) +
  				      pow(SystVar.at(h)->Integral( Bins.at(b-1)+1,
  								   Bins.at(b) )
  					  -OrdPlots.at(h)->Integral( Bins.at(b-1)+1,
  								     Bins.at(b) ), 2) ) );
  	
      }
    }
  }
  std::cout<<" "<<std::endl;
  std::cout<<" Yields   :             Value              StatErr"
  	   <<"           SystErr            CombErr"<<std::endl;
  std::cout<<" "<<std::endl;
  for(uint b=1; b<Bins.size(); b++){
    std::cout << "        " << RegName.at(b-1) << std::endl;
    for(uint h=0; h<Names.size(); h++){
    
      if(h!=Names.size()-1){
  	std::cout.width(15); std::cout << Names.at(h);
  	std::cout.width(15); std::cout << Yie.at(b-1).at(h)  << " +- ";
  	std::cout.width(15); std::cout << Sta.at(b-1).at(h)  << " +- ";
  	std::cout.width(15); std::cout << Sys.at(b-1).at(h)  << " +- ";
  	std::cout.width(15); std::cout << CbEr.at(b-1).at(h) << std::endl;
      }
      else{
  	std::cout.width(15); std::cout << Names.at(h);
  	std::cout.width(15); std::cout << Yie.at(b-1).at(h) << std::endl;
      }
    }
    std::cout << "        " << std::endl;
  }

  std::cout << "  -------------------------------------------  " << std::endl;

  Int_t S1 = Plots.at(5)->FindBin(900);
  Int_t E1 = Plots.at(5)->FindBin(1100);

  Int_t S2 = Plots.at(5)->FindBin(1800);
  Int_t E2 = Plots.at(5)->FindBin(2200);

  Int_t S3 = Plots.at(5)->FindBin(2700);
  Int_t E3 = Plots.at(5)->FindBin(3300);
  
  std::cout << " Bkg around Mass point 1 TeV "<<std::endl;
  std::cout << " Central = "<< Plots.at(5)->Integral(S1,E1)<<std::endl;
  std::cout << " Sys Up  = "<< BkgUp->Integral(S1,E1)<<std::endl;
  std::cout << " --> "<< Plots.at(5)->Integral(S1,E1)<<" +- "
	    << BkgUp->Integral(S1,E1)-Plots.at(5)->Integral(S1,E1)
	    <<std::endl;
  std::cout<<""<<std::endl;

  std::cout << " Bkg around Mass point 2 TeV "<<std::endl;
  std::cout << " Central = "<< Plots.at(5)->Integral(S2,E2)<<std::endl;
  std::cout << " Sys Up  = "<< BkgUp->Integral(S2,E2)<<std::endl;
  std::cout << " --> "<< Plots.at(5)->Integral(S2,E2)<<" +- "
	    << BkgUp->Integral(S2,E2)-Plots.at(5)->Integral(S2,E2)
	    <<std::endl;
  std::cout<<""<<std::endl;

  std::cout << " Bkg around Mass point 3 TeV "<<std::endl;
  std::cout << " Central = "<< Plots.at(5)->Integral(S3,E3)<<std::endl;
  std::cout << " Sys Up  = "<< BkgUp->Integral(S3,E3)<<std::endl;
  std::cout << " --> "<< Plots.at(5)->Integral(S3,E3)<<" +- "
	    << BkgUp->Integral(S3,E3)-Plots.at(5)->Integral(S3,E3)
	    <<std::endl;
  std::cout<<""<<std::endl;
 
}

TGraphAsymmErrors* PrepareRatio(TH1F *data, TH1F *MC, bool isData){

  TGraphAsymmErrors *Hratio = new TGraphAsymmErrors();
  double value = 0;
  double error_poisson_up   = 0;
  double error_poisson_down = 0;
  double y1 = 0;
  double y2 = 0;
  double d1 = 0;
  double d2 = 0;
  for(int i=1; i<data->GetNbinsX()+1; i++){
    value = data->GetBinContent(i);
    if(value!=0){
      y1 = value + 1.0;
      d1 = 1.0 - 1.0/(9.0*y1) + 1.0/(3*TMath::Sqrt(y1));
      error_poisson_up = y1*d1*d1*d1 - value;
      y2 = value;
      d2 = 1.0 - 1.0/(9.0*y2) - 1.0/(3.0*TMath::Sqrt(y2));
      error_poisson_down = value - y2*d2*d2*d2;
      if(isData){
	/* Set Data Ratio: 
	   save values of the data that will be used in ratio plot */
	Hratio->SetPoint(i-1, data->GetBinCenter(i), value);
	Hratio->SetPointError( i-1, data->GetBinWidth(i)/2,
			            data->GetBinWidth(i)/2,
			            error_poisson_down,
				    error_poisson_up );
      }
      else{
	/* Set Bkg Ratio: 
	   save values of the bkg that will be used in ratio plot */
	Hratio->SetPoint( i-1, MC->GetBinCenter(i),
			       MC->GetBinContent(i) );
	if(m_useErrOnBkg){
	  Hratio->SetPointError( i-1, MC->GetBinWidth(i)/2,
				      MC->GetBinWidth(i)/2,
				      MC->GetBinError(i),
				      MC->GetBinError(i) );
	}
	else{
	  Hratio->SetPointError( i-1,MC->GetBinWidth(i)/2,
				     MC->GetBinWidth(i)/2,
				     0, 0 );
	}
      }
    }
    else{
      /* if 0 enteries set so ratio = -999/1 and off the ratio plot and 
	 that h_Data on P1 are also off plot (1E32) used to work with -999, 
	 but could see data points as artifacts in Root6... */
      if(isData){
	Hratio->SetPoint(i-1, data->GetBinCenter(i), -999.0);
	Hratio->SetPointError(i-1, 0, 0, 0, 0);
      }
      else{
	Hratio->SetPoint(i-1, MC->GetBinCenter(i), 1.0);
	Hratio->SetPointError(i-1, 0, 0, 0, 0);
      }
    }
  }
  
  return Hratio;
  
}

TGraphAsymmErrors* myTGraphErrorsDivide(TGraphAsymmErrors* g1,
					TGraphAsymmErrors* g2){
  
  const Int_t debug=0; 
  
  TGraphAsymmErrors* g3= new TGraphAsymmErrors();
  Int_t n1=g1->GetN();
  Int_t n2=g2->GetN();
  
  if(n1!=n2){
    std::cout<<"vectors do not have same number of entries!"<<std::endl;
    return g3;
  }
  
  Double_t x1=0., y1=0., x2=0., y2=0.;
  Double_t dx1h=0., dx1l=0.;
  Double_t dy1h=0., dy1l=0.;
  Double_t dy2h=0., dy2l=0.;
  
  Double_t* EXhigh1 = g1->GetEXhigh();
  Double_t* EXlow1 =  g1->GetEXlow();
  Double_t* EYhigh1 = g1->GetEYhigh();
  Double_t* EYlow1 =  g1->GetEYlow();
  
  Double_t* EYhigh2 = g2->GetEYhigh();
  Double_t* EYlow2 =  g2->GetEYlow();
  
  for (Int_t i=0; i<g1->GetN(); i++) {
    g1->GetPoint(i,x1,y1);
    g2->GetPoint(i,x2,y2);
    dx1h  = EXhigh1[i];
    dx1l  = EXlow1[i];
    if (y1!=0.) dy1h = EYhigh1[i]/y1;
    else        dy1h = 0.;
    if (y2!=0.) dy2h = EYhigh2[i]/y2;
    else        dy2h = 0.;
    if (y1!=0.) dy1l = EYlow1 [i]/y1;
    else        dy1l = 0.;
    if (y2!=0.) dy2l = EYlow2 [i]/y2;
    else        dy2l = 0.;
   
    //if (debug)
    //printf("%d x1=%f x2=%f y1=%f y2=%f  \n",i,x1,x2,y1,y2);
    if (debug)
      printf("%d dy1=%f %f dy2=%f %f sqrt= %f %f \n",i,dy1l,dy1h,dy2l,dy2h,
	     std::sqrt(dy1l*dy1l+dy2l*dy2l), std::sqrt(dy1h*dy1h+dy2h*dy2h));
    
    if (y2!=0.) g3->SetPoint(i, x1,y1/y2);
    else       g3->SetPoint(i, x1,y2);
    Double_t el=0.; Double_t eh=0.;

    if (y1!=0. && y2!=0.) el=std::sqrt(dy1l*dy1l+dy2l*dy2l)*(y1/y2);
    if (y1!=0. && y2!=0.) eh=std::sqrt(dy1h*dy1h+dy2h*dy2h)*(y1/y2);
    
    if (debug) printf("dx1h=%f  dx1l=%f  el=%f  eh=%f \n",dx1h,dx1l,el,eh);
    g3->SetPointError(i,dx1h,dx1l,el,eh);
    if(debug)
      std::cout<<"Mass = "<<x1<<" Ratio = "<<y1/y2
	       <<" Err up = "<<eh<<" Err dw = "<<el<<std::endl;
    
  }  
  return g3;
  
}

std::pair<double,double> FindPlotRange(int LFVtype, std::string Htype, TH1F *h){
  
  std::pair<double,double> vals;
  
  if(Htype=="mllCorr" || Htype=="mll"){
    /* lower value */
    if(m_isttCR || m_isRevDphi){
      vals.first=80.;
    }
    else{
      if(Htype=="mll" && LFVtype>1)
	vals.first=120.;
      else
	vals.first=130.;
    }
    /* upper value */
    if(m_isRevDphi){
      vals.second=2000.;
    }
    else if(m_isttCR){
      if(LFVtype==3 || LFVtype==1)
	vals.second=1400.;
      else
	vals.second=2000.;
    }
    else{
      if(LFVtype==1)
	vals.second=2200.;
      else if(LFVtype==2)
	vals.second=2800.;
      else
	vals.second=2600.;
    }
  }
  else if(Htype=="ptllCorr" || Htype=="ptll"){
    vals.first=0.; vals.second=900.;
  }
  else if(Htype=="etall"){
     vals.first=-4.2; vals.second=4.2;
  }
  else if(Htype=="met"){
    vals.first=0.; vals.second=500.;
  }
  else if(Htype=="njet"){
    vals.first=0.;
    if(m_isttCR) vals.first=1.;
    if(LFVtype==2){ vals.second=8.9; }
    else          { vals.second=9.9; }
  }
  if(Htype=="mu_pt" || Htype=="el_pt" || Htype=="ta_pt"){
    vals.first=50.; vals.second=1100.;
  }
  else if(Htype=="mu_eta" || Htype=="el_eta" || Htype=="ta_eta" ||
	  Htype=="mu_phi" || Htype=="el_phi" || Htype=="ta_phi" ||
	  Htype=="phill"  ){
    vals.first  = h->GetXaxis()->GetXmin();
    vals.second = h->GetXaxis()->GetXmax()-0.1;
  }
  else if(Htype=="mt"){
    vals.first  = h->GetXaxis()->GetXmin();
    vals.second = 490.;
  }
  return vals;
  
}

double FindMaxValue(TH1F* h, double Val){

  int Bin = h->FindBin(Val);
  double Ext = h->GetBinLowEdge(Bin+1);
  return Ext;
}

double FindMinValue(TH1F* h, double Val){

  int Bin = h->FindBin(Val);
  double Ext = h->GetBinLowEdge(Bin);
  return Ext;
  
}

void SetPlotRange(TH1F* h, double Xmin, double Xmax){

  h->GetXaxis()->SetRangeUser(Xmin,Xmax);
  
}

std::string GetOutName(std::string Htype){

  std::string m_name = "";
  if(Htype=="mllCorr")      { m_name = "invmass";    }
  else if(Htype=="mll")     { m_name = "invmassVis"; }
  else if(Htype=="ptllCorr"){ m_name = "ptll";       }
  else if(Htype=="ptll")    { m_name = "ptllVis";    }
  else if(Htype=="mu_pt")   { m_name = "muPt";       }
  else if(Htype=="el_pt")   { m_name = "elPt";       }
  else if(Htype=="ta_pt")   { m_name = "taPt";       }
  else if(Htype=="mu_eta")  { m_name = "muEta";      }
  else if(Htype=="el_eta")  { m_name = "elEta";      }
  else if(Htype=="ta_eta")  { m_name = "taEta";      }
  else if(Htype=="mu_phi")  { m_name = "muPhi";      }
  else if(Htype=="el_phi")  { m_name = "elPhi";      }
  else if(Htype=="ta_phi")  { m_name = "taPhi";      }
  else{
    m_name = Htype;
  }

  if(m_isBlind)  { m_name += "_Blind";    }
  if(m_usePtRw)  { m_name += "_PtRw";     }
  if(m_isttCR)   { m_name += "_ttbarCR";  }
  if(m_isSherpa) { m_name += "_Sherpa";   }
  if(m_isRevDphi){ m_name += "_revDphi";  }
  if(!m_useData) { m_name += "_MC";       }
  if(m_useBjet)  { m_name += "_bjetVeto"; }

  return m_name;
  
}

void MakePlots(int LFVtype, std::string Htype, std::string Dir,
	       std::string SigMp){

  SetATLASStyle();

  std::string lfvType = "";
  if(LFVtype==1)      { lfvType="emu";   }
  else if(LFVtype==2) { lfvType="etau";  }
  else if(LFVtype==3) { lfvType="mutau"; }
  
  if(Dir==""){
    if(m_useBjet){ Dir += "Bjet/";   }
    else         { Dir += "NoBjet/"; }
  }
  if(m_isttCR)   {
    Dir += "ttbarCR";
    if(m_isSherpa) Dir += "_Sherpa";
    Dir += "/";
  }
  if(m_isRevDphi){ Dir += "revDphi/"; }

  std::cout << " < MakeDataMCplots() >:: inputDir = " << Dir << std::endl;
  
  TFile *In = NULL, *InD = NULL, *Sig=NULL;
  std::string fName = Dir+"Plots_Nominal_"+lfvType;
  if(m_isBlind)  { fName += "_Blind";  }
  if(m_usePtRw)  { fName += "_PtRw";   }
  if(m_useSmooth){ fName += "_Smooth"; }
  
  In = new TFile( (fName+".root").c_str() );

  std::string BdName = Dir+"SystematicsBands_"+lfvType;
  if(m_isBlind){ BdName += "_Blind"; }

  TFile *Bd=NULL, *BdStat=NULL, *Bd_Top=NULL, *Bd_DY=NULL, *Bd_Db=NULL, *Bd_Mj=NULL;
  if(m_useSysBand){
    Bd = new TFile( (BdName+".root").c_str() );
    if(m_addStatInBand)
      BdStat = new TFile( (Dir+"SystematicsBands_"+lfvType+"_WithStatUnc.root").c_str() );
    if(!m_isRevDphi && !m_isttCR){
      Bd_Top = new TFile( (BdName+"_Top.root").c_str()      );
      Bd_DY  = new TFile( (BdName+"_DY.root").c_str()       );
      Bd_Db  = new TFile( (BdName+"_DiBoson.root").c_str()  );
      Bd_Mj  = new TFile( (BdName+"_Multijet.root").c_str() );
    }
  }
  
  if(m_useSignal)
    Sig = new TFile( (Dir+"Plots_Nominal_"+lfvType+"_Signals.root").c_str() );
  
  TH1F *data = NULL;
  if(m_isBlindData){
    InD = new TFile( (Dir+"Plots_Nominal_"+lfvType+"_BlindData.root").c_str() );
    data = (TH1F*)InD->Get( ("h"+Htype+"_data").c_str() );
  }
  else{
    data = (TH1F*)In->Get( ("h"+Htype+"_data").c_str() );
  }
  
  TH1F *QcdWjets = (TH1F*)In->Get( ("h"+Htype+"_Multijet").c_str() );
  TH1F *DY       = (TH1F*)In->Get( ("h"+Htype+"_DY").c_str()       );
  TH1F *DiBoson  = (TH1F*)In->Get( ("h"+Htype+"_DiBoson").c_str()  );
  TH1F *Top      = (TH1F*)In->Get( ("h"+Htype+"_Top").c_str()      );
  Top->GetXaxis()->SetRange(0,10000);

  TH1F * Wjets = NULL, *qcd = NULL;
  if(m_showQCD){
    Wjets = (TH1F*)In->Get( ("h"+Htype+"_Wjets").c_str() );
    qcd   = (TH1F*)In->Get( ("h"+Htype+"_qcd").c_str()   );
  }
  
  TH1F *BkgTot   = (TH1F*)In->Get( ("h"+Htype+"_BkgTot").c_str() );
  TH1F *dummy    = (TH1F*)BkgTot->Clone("dummy");
  dummy->Reset();

  TH1F *Zprime = NULL, *QBH = NULL, *SVT=NULL;
  if(m_useSignal){
    Zprime = (TH1F*)Sig->Get( ("h"+Htype+"_Zprime"+SigMp).c_str() );
    QBH    = (TH1F*)Sig->Get( ("h"+Htype+"_QBH"+SigMp+"_n1").c_str() );
    SVT    = (TH1F*)Sig->Get( ("h"+Htype+"_SVT"+SigMp).c_str() );
  }

  TGraphAsymmErrors *Band = NULL;
  TH1F *mllSys_Tot = NULL, *mllSys_Top = NULL;
  TH1F *mllSys_DY  = NULL, *mllSys_Db  = NULL, *mllSys_Mj = NULL;
  if(m_useSysBand){
    if(m_addStatInBand)
      Band = (TGraphAsymmErrors*)BdStat->Get( ("h"+Htype+"_SystBand").c_str() );
    else
      Band = (TGraphAsymmErrors*)Bd->Get( ("h"+Htype+"_SystBand").c_str() );
    if(!m_isRevDphi && !m_isttCR){
      mllSys_Tot = (TH1F*)Bd->Get    ( (Htype+"_SysUp").c_str() );
      mllSys_Top = (TH1F*)Bd_Top->Get( (Htype+"_SysUp").c_str() );
      mllSys_DY  = (TH1F*)Bd_DY->Get ( (Htype+"_SysUp").c_str() );
      mllSys_Db  = (TH1F*)Bd_Db->Get ( (Htype+"_SysUp").c_str() );
      mllSys_Mj  = (TH1F*)Bd_Mj->Get ( (Htype+"_SysUp").c_str() );
    }
  }
  
  THStack *hs = new THStack("hs","");

  /* defining histograms */
  std::vector<TH1F*> Plots;
  Plots.push_back( data     );
  Plots.push_back( DY       );
  if(m_showQCD){
    Plots.push_back( Wjets );
    Plots.push_back( qcd   );
  }
  else
    Plots.push_back( QcdWjets );
  Plots.push_back( DiBoson  );
  Plots.push_back( Top      );
  Plots.push_back( BkgTot   );
  if(m_useSignal){
    Plots.push_back( Zprime );
    Plots.push_back( QBH    );
    Plots.push_back( SVT    );
  }

  std::vector<TH1F*> Systs;
  Systs.push_back( mllSys_Tot );
  Systs.push_back( mllSys_Top );
  Systs.push_back( mllSys_Db  );
  Systs.push_back( mllSys_DY  );
  Systs.push_back( mllSys_Mj  );
  
  Double_t Xmin = FindPlotRange( LFVtype,Htype,Plots.at(0) ).first;
  Double_t Xmax = FindPlotRange( LFVtype,Htype,Plots.at(0) ).second;

  /* Set Axis title */
  std::ostringstream sstream;
  sstream << std::setprecision(2) << Plots.at(1)->GetBinWidth(2);
  std::string Bsize = sstream.str();
  if(Htype.find("pt")!=std::string::npos || Htype=="njet" ||
     Htype.find("mll")!=std::string::npos )
    dummy->GetYaxis()->SetTitle( "Events" );
  else if( Htype=="met" ||  Htype=="mt" ){
    dummy->GetYaxis()->SetTitle( ("Events / "+Bsize+" GeV").c_str() );
  }
  else
    dummy->GetYaxis()->SetTitle( ("Events / "+Bsize).c_str() );
  
  double Integral = 0;
  /* Set Colors */
  if(m_showQCD){
    Plots.at(1)->SetFillColor(kAzure-9);
    Plots.at(2)->SetFillColor(kYellow-9);
    Plots.at(3)->SetFillColor(kViolet+1);
    Plots.at(4)->SetFillColor(kOrange);
    Plots.at(5)->SetFillColor(kRed+1);
  }
  else{
    Plots.at(1)->SetFillColor(kAzure-9);
    Plots.at(2)->SetFillColor(kYellow-9);
    Plots.at(3)->SetFillColor(kOrange);
    Plots.at(4)->SetFillColor(kRed+1);
  }
  if(m_useSysBand){
    Band->SetFillColor(kGray);
    Band->SetFillStyle(1111);
    Band->SetLineColor(kGray);
  }
  
  /* Integrals */
  if(m_showQCD){
    std::cout<<"Integral Top       = "<<Plots.at(5)->Integral()<<std::endl;
    Integral += Plots.at(5)->Integral();
    std::cout<<"Integral DiBoson   = "<<Plots.at(4)->Integral()<<std::endl;
    Integral += Plots.at(4)->Integral();
    std::cout<<"Integral QCD       = "<<Plots.at(3)->Integral()<<std::endl;
    Integral += Plots.at(3)->Integral();
    std::cout<<"Integral W+jets    = "<<Plots.at(2)->Integral()<<std::endl;
    Integral += Plots.at(2)->Integral();
    std::cout<<"Integral DY        = "<<Plots.at(1)->Integral()<<std::endl;
    Integral += Plots.at(1)->Integral();
    std::cout<<"Integral Total MC  = "<<Integral<<std::endl;
  }
  else{
    std::cout<<"Integral Top       = "<<Plots.at(4)->Integral()<<std::endl;
    Integral += Plots.at(4)->Integral();
    std::cout<<"Integral DiBoson   = "<<Plots.at(3)->Integral()<<std::endl;
    Integral += Plots.at(3)->Integral();
    std::cout<<"Integral QCD-Wjets = "<<Plots.at(2)->Integral()<<std::endl;
    Integral += Plots.at(2)->Integral();
    std::cout<<"Integral DY        = "<<Plots.at(1)->Integral()<<std::endl;
    Integral += Plots.at(1)->Integral();
    std::cout<<"Integral Total MC  = "<<Integral<<std::endl;
  }
  std::cout<<"Integral Data      = "<<Plots.at(0)->Integral()<<std::endl;
  
  /* Making Stack */
  if(LFVtype==1){
    hs->Add( Plots.at(1) ); //DY
    hs->Add( Plots.at(2) ); //QCD
    hs->Add( Plots.at(3) ); //Db
    hs->Add( Plots.at(4) ); //Top
  }
  else{
    if(m_showQCD){
      hs->Add( Plots.at(4) ); //Db
      hs->Add( Plots.at(1) ); //DY
      if(m_isttCR){
	hs->Add( Plots.at(3) ); //QCD
	hs->Add( Plots.at(2) ); //Wjets
	hs->Add( Plots.at(5) ); //Top
      }
      else if(m_isRevDphi){
      	hs->Add( Plots.at(3) ); //QCD
	hs->Add( Plots.at(5) ); //Top
	hs->Add( Plots.at(2) ); //wjets
      }
      else{
	hs->Add( Plots.at(5) ); //Top
	hs->Add( Plots.at(3) ); //QCD
	hs->Add( Plots.at(2) ); //wjets
      }
    }
    else{
      hs->Add( Plots.at(3) ); //Db
      hs->Add( Plots.at(1) ); //DY
      if(m_isttCR){
	hs->Add( Plots.at(2) ); //QCD
	hs->Add( Plots.at(4) ); //Top
      }
      else{
	hs->Add( Plots.at(4) ); //Top
	hs->Add( Plots.at(2) ); //QCD
      }
    }
  }
  
  TCanvas *cs = new TCanvas("cs","cs",0,0,600,600);
  cs->cd();
  TPad* p1 = new TPad("p1","p1",0.01,0.345,0.99,0.99);
  p1->Draw();
  //p1->SetBottomMargin(0.035);
  p1->SetBottomMargin(0.00);

  TPad* p2 = new TPad("p2","p2",0.01,0.01,0.99,0.35);
  p2->Draw();
  p2->SetTopMargin(0.00);
  p2->SetBottomMargin(0.30);
  
  p1->cd();
  p1->SetLogy();

  /* Setting plot range */
  SetPlotRange(dummy,Xmin,Xmax);
  Double_t Ymin = 0.002, Ymax = 10000000;
  if(LFVtype==1){
    if(m_useSignal){ Ymax = 500000000; }
    dummy->GetYaxis()->SetRangeUser(Ymin,Ymax);
  }
  else{
    Ymax = 90000000;
    if(m_isRevDphi){ Ymin = 0.5; Ymax = 100000; }
    if(m_useSignal){ Ymax = 5000000000; }
    dummy->GetYaxis()->SetRangeUser(Ymin,Ymax);
  }
  dummy->GetYaxis()->SetTitleSize(0.06);
  dummy->GetYaxis()->SetLabelSize(0.06);
  dummy->GetYaxis()->SetTitleOffset(1.00);
  dummy->GetXaxis()->SetTickLength(0.06);
  dummy->Draw();
  if(Htype=="mllCorr" || (Htype=="mll") ){
    p1->SetLogx();
    hs->Draw("HISTsame");
    hs->GetXaxis()->SetRangeUser(Xmin,Xmax);
  }
  else{
    hs->Draw("HISTsame");
    hs->GetXaxis()->SetRangeUser(Xmin,Xmax);
  }
  if(m_useSignal){
    if(m_showQCD){
      Plots.at(7)->SetLineColor(kGreen+2);
      Plots.at(7)->SetLineStyle(1);
      Plots.at(7)->GetYaxis()->SetTitleSize(0.06);
      Plots.at(7)->GetYaxis()->SetTitleOffset(1.00);
      Plots.at(7)->GetYaxis()->SetTitle("Events");
      Plots.at(7)->GetYaxis()->SetLabelSize(0.05);
      SetPlotRange(Plots.at(7),Xmin,Xmax);
      Plots.at(7)->Draw("histsame");
      Plots.at(8)->SetLineColor(kBlue);
      Plots.at(8)->SetLineStyle(7);
      SetPlotRange(Plots.at(8),Xmin,Xmax);
      Plots.at(8)->Draw("histsame");
      Plots.at(9)->SetLineColor(kMagenta);
      Plots.at(9)->SetLineStyle(6);
      SetPlotRange(Plots.at(9),Xmin,Xmax);
      Plots.at(9)->Draw("histsame");
    }
    else{
      Plots.at(6)->SetLineColor(kGreen+2);
      Plots.at(6)->SetLineStyle(1);
      Plots.at(6)->GetYaxis()->SetTitleSize(0.06);
      Plots.at(6)->GetYaxis()->SetTitleOffset(1.00);
      Plots.at(6)->GetYaxis()->SetTitle("Events");
      Plots.at(6)->GetYaxis()->SetLabelSize(0.05);
      SetPlotRange(Plots.at(6),Xmin,Xmax);
      Plots.at(6)->Draw("histsame");
      Plots.at(7)->SetLineColor(kBlue);
      Plots.at(7)->SetLineStyle(7);
      SetPlotRange(Plots.at(7),Xmin,Xmax);
      Plots.at(7)->Draw("histsame");
      Plots.at(8)->SetLineColor(kMagenta);
      Plots.at(8)->SetLineStyle(6);
      SetPlotRange(Plots.at(8),Xmin,Xmax);
      Plots.at(8)->Draw("histsame");
    }
  }
  
  /* cover signal */
  if(m_useData)
    Plots.at(0)->Draw("pEsame");
  gPad->RedrawAxis();

  if(Htype=="mllCorr" && m_useSysBand && !m_isRevDphi && !m_isttCR){
    PrintYields(Plots,Systs);
    std::cout<<"  -------------------------------------------  "<<std::endl;
    PrintYieldRegions(Plots,Systs);
  }

  TLegend *leg = CreateFillLegend(LFVtype,Plots,Band);
  leg->Draw();

  DrawLabels(true,false,false,true);
  DrawChannel(lfvType,true,m_useBjet);

  p2->cd();
  if(Htype=="mllCorr" || (Htype=="mll") )
    p2->SetLogx();
  p2->SetGridy();
  
  TH1F* ratio = (TH1F*)Plots.at(0)->Clone("ratio");
  ratio->Reset();
  ratio->GetXaxis()->SetTitle(Plots.at(0)->GetXaxis()->GetTitle());
  ratio->GetXaxis()->SetTitleOffset(1.20);
  ratio->GetXaxis()->SetTitleSize(0.12);
  ratio->GetXaxis()->SetLabelSize(0.11);
  ratio->GetYaxis()->SetTitle("Data/SM Bkg");
  ratio->GetYaxis()->SetLabelSize(0.11);
  ratio->GetYaxis()->SetTitleOffset(0.55);
  ratio->GetYaxis()->SetTitleSize(0.11);
  ratio->GetYaxis()->CenterTitle(kTRUE);
  ratio->GetYaxis()->SetNdivisions(507);
  ratio->GetXaxis()->SetMoreLogLabels(kTRUE);
  ratio->GetXaxis()->SetNoExponent(kTRUE);

  ratio->GetXaxis()->SetTickLength(0.09);
  ratio->SetMarkerSize(0.9);
  ratio->SetMarkerStyle(21);
  ratio->SetLineStyle(1);
  ratio->SetLineWidth(1);
  ratio->SetLineColor(1);
  ratio->SetMarkerColor(1);
  
  TLine* ratioLine = DefineHorizLine( 1,
				      FindMinValue(ratio,Xmin),
				      FindMaxValue(ratio,Xmax) );
  ratioLine->SetLineColor(kRed);
  ratioLine->SetLineStyle(1);
  ratioLine->SetLineWidth(2);

  TGraphAsymmErrors *HData_ratio = PrepareRatio(Plots.at(0),BkgTot,true);
  TGraphAsymmErrors *HBkg_ratio  = PrepareRatio(Plots.at(0),BkgTot,false);
  
  TGraphAsymmErrors* Hratio = myTGraphErrorsDivide(HData_ratio,HBkg_ratio);
  Hratio->GetXaxis()->SetTitle(Plots.at(0)->GetXaxis()->GetTitle());
  Hratio->GetXaxis()->SetLabelSize(0.08);
  Hratio->GetXaxis()->SetTitleOffset(1.20);
  Hratio->GetXaxis()->SetTitleSize(0.12);
  Hratio->GetYaxis()->SetTitle("Data/MC");
  Hratio->GetYaxis()->SetLabelSize(0.09);
  Hratio->GetYaxis()->SetTitleOffset(0.55);
  Hratio->GetYaxis()->SetTitleSize(0.10);
  Hratio->GetYaxis()->CenterTitle(kTRUE);
  Hratio->GetYaxis()->SetNdivisions(507);
  Hratio->GetXaxis()->SetMoreLogLabels(kTRUE);
  Hratio->GetXaxis()->SetNoExponent(kTRUE);
  Hratio->GetXaxis()->SetLabelSize(0.09);
  Hratio->SetMarkerSize(0.9);
  Hratio->SetMarkerStyle(21);
  Hratio->SetLineStyle(1);
  Hratio->SetLineWidth(2);
  Hratio->SetLineColor(1);
  Hratio->SetMarkerColor(1);
  Hratio->GetXaxis()->SetRangeUser(Xmin,Xmax);

  ratio->GetYaxis()->SetRangeUser(0.1,1.9);
  ratio->GetXaxis()->SetRangeUser(Xmin,Xmax);
  if(m_useSysBand){
    Band->GetYaxis()->SetRangeUser(0.1,1.9);
    Band->GetXaxis()->SetLabelSize(0.08);
    Band->GetXaxis()->SetTitleOffset(1.20);
    Band->GetXaxis()->SetTitleSize(0.12);
    Band->GetYaxis()->SetTitle("Data/MC");
    Band->GetYaxis()->SetLabelSize(0.09);
    Band->GetYaxis()->SetTitleOffset(0.55);
    Band->GetYaxis()->SetTitleSize(0.10);
    Band->GetYaxis()->CenterTitle(kTRUE);
    Band->GetYaxis()->SetNdivisions(507);
    Band->GetXaxis()->SetMoreLogLabels(kTRUE);
    Band->GetXaxis()->SetNoExponent(kTRUE);
    Band->GetXaxis()->SetLabelSize(0.09);
  }
  
  ratio->Draw();
  if(m_useSysBand)
    Band->Draw("same2"); //do not draw axis
  ratioLine->Draw("same");
  if(m_useData)
    Hratio->Draw("samepE0");
  gPad->RedrawAxis();
  cs->Update();

  std::string oDir = "Plots/";
  if(m_isttCR)        { oDir += "ttbarCR/"; }
  else if(m_isRevDphi){ oDir += "revDphi/"; }
  else                { oDir += "DataMC/";  }

  if(m_useSmooth)
    cs->SaveAs( (oDir+lfvType+"_"+GetOutName(Htype)+"_Smooth.pdf").c_str() );
  else
    cs->SaveAs( (oDir+lfvType+"_"+GetOutName(Htype)+".pdf").c_str() );
  
}

TLegend* CreateFillLegend(int LFVtype, std::vector<TH1F*> Plots,
			  TGraphAsymmErrors *Band){

  TLegend *leg=NULL;

  if(m_useSignal){
    if(m_showQCD)
      leg = new TLegend(0.59,0.40,0.99,0.91);
    else
      leg = new TLegend(0.59,0.49,0.99,0.91);
  }
  else
    leg = new TLegend(0.59,0.60,0.99,0.91);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  if(m_useData)
    leg->AddEntry(Plots.at(0),"Data","pE");
  if(LFVtype==1){
    leg->AddEntry(Plots.at(4),"Top Quarks","f");
    leg->AddEntry(Plots.at(3),"Diboson","f");
    leg->AddEntry(Plots.at(2),"Multijet & W+jets","f");
    leg->AddEntry(Plots.at(1),"Z/#gamma*#rightarrow ll","f");
  }
  else{
    if(m_showQCD){
      if(m_isttCR){
	leg->AddEntry(Plots.at(5),"Top Quarks","f");
	leg->AddEntry(Plots.at(2),"W+jets","f");
	leg->AddEntry(Plots.at(3),"Multijet","f");
      }
      else if(m_isRevDphi){
	leg->AddEntry(Plots.at(2),"W+jets","f");
	leg->AddEntry(Plots.at(5),"Top Quarks","f");
	leg->AddEntry(Plots.at(3),"Multijet","f");
      }
      else{
	leg->AddEntry(Plots.at(2),"W+jets","f");
	leg->AddEntry(Plots.at(3),"Multijet","f");
	leg->AddEntry(Plots.at(5),"Top Quarks","f");
      }
      leg->AddEntry(Plots.at(1),"Z/#gamma*#rightarrow ll","f");
      leg->AddEntry(Plots.at(4),"Diboson","f");
    }
    else{
      if(m_isttCR){
	leg->AddEntry(Plots.at(4),"Top Quarks","f");
	leg->AddEntry(Plots.at(2),"Multijet & W+jets","f");
      }
      else{
	leg->AddEntry(Plots.at(2),"Multijet & W+jets","f");
	leg->AddEntry(Plots.at(4),"Top Quarks","f");
      }
      leg->AddEntry(Plots.at(1),"Z/#gamma*#rightarrow ll","f");
      leg->AddEntry(Plots.at(3),"Diboson","f");
    }
  }
  if(m_useSignal){
    std::string mass = "1.5 TeV";
    if(m_showQCD){
      leg->AddEntry(Plots.at(7),("LFV Z' "+mass).c_str(), "l");
      leg->AddEntry(Plots.at(9),("RPV #tilde{#nu}_{#tau} "+mass).c_str(), "l");
      leg->AddEntry(Plots.at(8),("QBH RS "+mass).c_str(), "l");
    }
    else{
      leg->AddEntry(Plots.at(6),("LFV Z' "+mass).c_str(), "l");
      leg->AddEntry(Plots.at(8),("RPV #tilde{#nu}_{#tau} "+mass).c_str(), "l");
      leg->AddEntry(Plots.at(7),("QBH RS "+mass).c_str(), "l");
    }
  }
  if(m_useSysBand){
    if(m_useErrOnBkg)
      leg->AddEntry(Band,"Systematics","f");
    else
      leg->AddEntry(Band,"Uncertainty","f");
  }

  return leg;
}
