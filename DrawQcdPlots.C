/* program includes */
#include "DrawQcdPlots.h"
#include "Utils.C"

int main( int argc, char* argv[] ) {

  int lfvType        = -1;
  std::string Htype  = "mllCorr";
  std::string charge = "";
  std::string region = "";
  bool useBjet       = false;
  bool isFFcat       = false;
  bool useGUI        = false;
  bool doCR          = false;
  bool doKfact       = false;
  bool useNoPtCut    = false;
  bool doProngs      = false;
  bool doShape       = false;
  bool doSys         = false;
  bool doCatComp     = false;
  bool doPrgComp     = false;
  bool useRatio      = false;
  bool isttCR        = false;
  bool isRevDphi     = false;
  bool printHelp     = false;
  bool debug         = false;
  for(int i = 1; i < argc; ++i){
    if( !strcmp(argv[i],"--lfvType")          ){ lfvType   = std::stoi(argv[i+1]); }
    else if( !strcmp(argv[i],"--charge")      ){ charge     = argv[i+1]; }
    else if( !strcmp(argv[i],"--region")      ){ region     = argv[i+1]; }
    else if( !strcmp(argv[i],"--Htype")       ){ Htype      = argv[i+1]; }
    else if( !strcmp(argv[i],"--isFFcat")     ){ isFFcat    = true; }
    else if( !strcmp(argv[i],"--useBjet")     ){ useBjet    = true; }
    else if( !strcmp(argv[i],"--isttCR")      ){ isttCR     = true; }
    else if( !strcmp(argv[i],"--isRevDphi")   ){ isRevDphi  = true; }
    else if( !strcmp(argv[i],"--useGUI")      ){ useGUI     = true; }
    else if( !strcmp(argv[i],"--doCR")        ){ doCR       = true; }
    else if( !strcmp(argv[i],"--doKfact")     ){ doKfact    = true; }
    else if( !strcmp(argv[i],"--doSys")       ){ doSys      = true; }
    else if( !strcmp(argv[i],"--useNoPtCut")  ){ useNoPtCut = true; }
    else if( !strcmp(argv[i],"--doProngs")    ){ doProngs   = true; }
    else if( !strcmp(argv[i],"--doShape")     ){ doShape    = true; }
    else if( !strcmp(argv[i],"--doCatComp")   ){ doCatComp  = true; }
    else if( !strcmp(argv[i],"--doPrgComp")   ){ doPrgComp  = true; }
    else if( !strcmp(argv[i],"--useRatio")    ){ useRatio   = true; }
    else if( !strcmp(argv[i],"--debug")       ){ debug      = true; }
    else if( !strcmp(argv[i],"--help")        ){ printHelp  = true; }
    else{
      if(std::string(argv[i]).find("--")!=std::string::npos)
	std::cout << "WARNING:: Option " << argv[i] << " not recognized: "
		  << "skipping!" << std::endl;
    }
  }

  if(printHelp){
    std::cout << " DrawQcdPlots: make qcd related plots!"         << std::endl;
    std::cout << "               Options: "                       << std::endl;
    std::cout << "                --useBjet    [Enable b-jet veto:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --charge     [Specificy pair charge:"
	      << " default is ''] "                               << std::endl;
    std::cout << "                --region     [Specificy Control Region:"
	      << " default is 'Reg3'] "                           << std::endl;
    std::cout << "                --useGUI     [Enable GUI mode:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --isttCR     [Enable ttbar CR:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --isRevDphi  [Enable revDphi analysis:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --isFFcat    [Enable Double-Fake catepory:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --Htype      [Choose distribution: "
	      << " default is 'mllCorr']"                         << std::endl;
    std::cout << "                --lfvType    [Choose lfv channel: "
	      << " options 1,2,3']"                               << std::endl;
    std::cout << "                --doCR       [Do CR plots:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --doKfact    [Do kFactor plots:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --useNoPtCut [Enable removing lep pT cut:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --doProngs   [Enable 1p-3p splitting:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --doShape    [Do Shape plot:"
      	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --doSys      [Do kMJ systematic:"
      	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --doCatComp  [Do FF vs LF comp: "
              << " default is 'false'] "                          << std::endl;
    std::cout << "                --doPrgComp  [Do 1p+3p vs all comp: "
              << " default is 'false'] "                          << std::endl;
    std::cout << "                --useRatio   [Enable ratio pad:"
              << " default is 'false'] "                          << std::endl;
    std::cout << "                --debug      [Enable debug]"    << std::endl;
    std::cout << "                --help       [Print this help]" << std::endl;
    exit(0);
  }

  std::cout << "< DrawQcdPlots() >:: Options set "           << std::endl;
  std::cout << "                useBjet    = " << useBjet    << std::endl;
  std::cout << "                lfvType    = " << lfvType    << std::endl;
  std::cout << "                Htype      = " << Htype      << std::endl;
  std::cout << "                charge     = " << charge     << std::endl;
  std::cout << "                region     = " << region     << std::endl;
  std::cout << "                isttCR     = " << isttCR     << std::endl;
  std::cout << "                isFFcat    = " << isFFcat    << std::endl;
  std::cout << "                isRevDphi  = " << isRevDphi  << std::endl;
  std::cout << "                doKfact    = " << doKfact    << std::endl;
  std::cout << "                doCR       = " << doCR       << std::endl;
  std::cout << "                useNoPtCut = " << useNoPtCut << std::endl;
  std::cout << "                doProngs   = " << doProngs   << std::endl;
  std::cout << "                doShape    = " << doShape    << std::endl;
  std::cout << "                doSys      = " << doSys      << std::endl;
  std::cout << "                doCatComp  = " << doCatComp  << std::endl;
  std::cout << "                doPrgComp  = " << doPrgComp  << std::endl;
  std::cout << "                useRatio   = " << useRatio   << std::endl;
  std::cout << "                useGUI     = " << useGUI     << std::endl;
  std::cout << "                debug      = " << debug      << std::endl;

  std::string chanName = "";
  if(lfvType==1)      { chanName="emu";   }
  else if(lfvType==2) { chanName="etau";  }
  else if(lfvType==3) { chanName="mutau"; }

  m_debug = debug;

  TRint *myApp = new TRint("RootSession",&argc,argv,NULL,0);
  if(doCR)
    CRplots(chanName,Htype,charge,region,isFFcat,useBjet,
	    isttCR,isRevDphi,useRatio);
  else if(doKfact)
    DeriveKfactor(chanName,Htype,isFFcat,useBjet,isttCR,isRevDphi,useNoPtCut,doProngs);
  else if(doShape)
    DrawShape(chanName,Htype,useBjet,isttCR,isRevDphi);
  else if(doSys)
    DeriveSys(chanName,Htype,useBjet,isttCR,isRevDphi);
  else if(doCatComp)
    CompareFakeCategories(chanName,useBjet,isttCR,isRevDphi);
  else if(doPrgComp)
    CompareProngs(chanName,useBjet);
						  
  if(useGUI){
    std::cout << "< DrawQcdPlots() >:: using Rint -> ROOT will remain "
	      << "opened ... " << std::endl;
    myApp->Run();
  }

  return 0;
  
}

void CRplots(std::string lfvType, std::string Htype, std::string charge,
	     std::string Reg, bool isFFcat, bool useBjet, bool isttCR,
	     bool isRevDphi, bool useRatio){
  
  SetATLASStyle();
  TH1::SetDefaultSumw2(kTRUE);
  
  std::string Dir = "";
  if(useBjet){ Dir += "Bjet/";   }
  else{        Dir += "NoBjet/"; }
  
  if(isttCR)   { Dir += "ttbarCR/"; }
  if(isRevDphi){ Dir += "revDphi/"; }

  Dir += "Qcd"+Reg;

  std::string Suff1="", Suff2="", Suff3="";
  if(charge==""){
    Suff1="_SS"; Suff2=""; Suff3="_SS";
  }
  else if(charge=="SS"){
    Suff1="_OS"; Suff2="_SS"; Suff3="_OS";
    //Suff1="_SS"; Suff2="_SS"; Suff3="_SS";
  }
  else if(charge=="OS"){
    Suff1="_SS"; Suff2="_OS"; Suff3="_SS";
    //Suff1="_OS"; Suff2="_OS"; Suff3="_OS";
  }

  if(isFFcat){
    if(Reg=="Reg1"){      Dir += Suff3+"/";}
    else if(Reg=="Reg2"){ Dir += Suff1+"/";}
    else if(Reg=="Reg3"){ Dir += Suff2+"/";}
  }
  else{
    if(Reg=="Reg1"){      Dir += Suff3+"/LepFake/"; }
    else if(Reg=="Reg2"){ Dir += Suff1+"/LepFake/"; }
    else if(Reg=="Reg3"){ Dir += Suff2+"/LepFake/"; }
  }
  
  TFile *In  = new TFile( (Dir+"Plots_Nominal_"+lfvType+".root").c_str() );
  TH1F *data = (TH1F*)In->Get( ("h"+Htype+"_data").c_str()    );
  TH1F *Top  = (TH1F*)In->Get( ("h"+Htype+"_Top").c_str()     );
  TH1F *DB   = (TH1F*)In->Get( ("h"+Htype+"_DiBoson").c_str() );
  TH1F *DY   = (TH1F*)In->Get( ("h"+Htype+"_DY").c_str()      );
  TH1F *Wjet = (TH1F*)In->Get( ("h"+Htype+"_Wjets").c_str()   );

  TH1F *Tot  = (TH1F*)Top->Clone("MCTot");
  Tot->Reset();
  TH1F *dummy  = (TH1F*)Top->Clone("dummy");
  dummy->Reset();
  
  THStack *hs = new THStack("hs","");

  /* Set Axis Title */
  std::ostringstream sstream;
  sstream << std::setprecision(2) << Top->GetBinWidth(2);
  std::string Bsize = sstream.str();
  if(Htype.find("pt")!=std::string::npos || Htype=="njet" ||
     Htype.find("mll")!=std::string::npos ){
    dummy->GetYaxis()->SetTitle( "Events" );
  }
  else if( (Htype.find("met")!=std::string::npos) ){
    dummy->GetYaxis()->SetTitle( ("Events / "+Bsize+" GeV").c_str() );
  }
  else{
    dummy->GetYaxis()->SetTitle( ("Events / "+Bsize).c_str() );
  }
  Double_t Xmin=120, Xmax = 3000;
  if(Reg=="Reg3"){ Xmax=5000; }
  if(isRevDphi || isttCR) { Xmin = 80; }
  
  dummy->GetXaxis()->SetRangeUser(Xmin,Xmax);
  dummy->GetYaxis()->SetRangeUser(0.005,90000000);
  if(useRatio){
    dummy->GetYaxis()->SetTitleSize(0.06);
    dummy->GetYaxis()->SetLabelSize(0.05);
    dummy->GetYaxis()->SetTitleOffset(1.00);
  }
  else{
    dummy->GetYaxis()->SetTitleSize(0.04);
    dummy->GetYaxis()->SetTitleOffset(1.20);
    dummy->GetYaxis()->SetLabelSize(0.04);
    dummy->GetXaxis()->SetTitleSize(0.04);
    dummy->GetXaxis()->SetTitleOffset(1.20);
    dummy->GetXaxis()->SetLabelSize(0.04);
  }
  dummy->GetXaxis()->SetMoreLogLabels(kTRUE);
  dummy->GetXaxis()->SetNoExponent(kTRUE);
  
  /* defining histograms */
  std::vector<TH1F*> Plots;
  Plots.push_back(data);
  Plots.push_back(Top);
  Plots.push_back(DB);
  Plots.push_back(DY);
  Plots.push_back(Wjet);
  
  Plots.at(1)->SetFillColor(kRed+1);
  Plots.at(2)->SetFillColor(kOrange);
  Plots.at(3)->SetFillColor(kAzure-9);
  Plots.at(4)->SetFillColor(kYellow-9);

  for(uint h=1; h<Plots.size(); h++){
    Plots.at(h)->GetYaxis()->CenterTitle(kTRUE);
    Plots.at(h)->GetYaxis()->SetTitleSize(0.05);
    Plots.at(h)->GetYaxis()->SetTitleOffset(1.20);
    Plots.at(h)->GetYaxis()->SetTitle("Events");
    Tot->Add( Plots.at(h) );
  }
  hs->Add( Plots.at(4) ); //QCD
  hs->Add( Plots.at(3) ); //DY
  hs->Add( Plots.at(2) ); //Db
  hs->Add( Plots.at(1) ); //Top
  std::cout << " Data    = " << Plots.at(0)->Integral()<<std::endl;
  std::cout << " Wj      = " << Plots.at(4)->Integral()<<std::endl;
  std::cout << " Top     = " << Plots.at(1)->Integral()<<std::endl;
  std::cout << " DY      = " << Plots.at(3)->Integral()<<std::endl;
  std::cout << " Db      = " << Plots.at(2)->Integral()<<std::endl;
  std::cout << " Data-MC = " << Plots.at(0)->Integral()-Tot->Integral()<<std::endl;
  
  TH1F *ratio   = (TH1F*)Plots.at(0)->Clone("ratio");
  ratio->Reset();
  ratio->GetXaxis()->SetTitle(Plots.at(1)->GetXaxis()->GetTitle());
  
  TH1F *ratioLine = (TH1F*)ratio->Clone("ratioLine");
  for (int k=-1; k<ratioLine->GetNbinsX()+1; k++){
    ratioLine->SetBinContent(k,1.);
  }
  ratio->Divide(Plots.at(0),Tot);
  ratio->GetYaxis()->SetTitle("Ratio");
  ratioLine->GetYaxis()->SetTitle("Ratio");
  ratio->GetXaxis()->SetLabelSize(0.08);
  ratio->GetXaxis()->SetTitleOffset(1.20);
  ratio->GetXaxis()->SetTitleSize(0.10);
  ratio->GetYaxis()->SetLabelSize(0.07);
  ratio->GetYaxis()->SetTitleOffset(0.55);
  ratio->GetYaxis()->SetTitleSize(0.08);
  ratio->GetYaxis()->CenterTitle(kTRUE);
  ratio->GetYaxis()->SetNdivisions(507);
  ratio->GetYaxis()->SetRangeUser(0.1,1.9);
  ratio->GetXaxis()->SetMoreLogLabels(kTRUE);
  ratio->GetXaxis()->SetNoExponent(kTRUE);

  ratioLine->GetXaxis()->SetLabelSize(0.08);
  ratioLine->GetXaxis()->SetTitleOffset(1.20);
  ratioLine->GetXaxis()->SetTitleSize(0.10);
  ratioLine->GetYaxis()->SetLabelSize(0.07);
  ratioLine->GetYaxis()->SetTitleOffset(0.55);
  ratioLine->GetYaxis()->SetTitleSize(0.08);
  ratioLine->GetYaxis()->CenterTitle(kTRUE);
  ratioLine->GetYaxis()->SetNdivisions(507);
  ratioLine->GetYaxis()->SetRangeUser(0.1,1.9);
  ratioLine->GetXaxis()->SetMoreLogLabels(kTRUE);
  ratioLine->GetXaxis()->SetNoExponent(kTRUE);
  
  ratioLine->SetLineColor(2);
  ratioLine->SetLineStyle(2);
  ratio->SetLineColor(1);
  ratio->SetMarkerColor(1);

  ratio->GetXaxis()->SetRangeUser(Xmin,Xmax);
  ratioLine->GetXaxis()->SetRangeUser(Xmin,Xmax);

  TCanvas *cs = new TCanvas("cs","cs",0,0,600,600);
  cs->cd();
  TPad* p1 = NULL, *p2 = NULL;
  if(useRatio){
    p1 = new TPad("p1","p1",0.01,0.35,0.99,0.99);
    p1->Draw();
    p1->SetBottomMargin(0.00);

    p2 = new TPad("p2","p2",0.01,0.01,0.99,0.35);
    p2->Draw();
    p2->SetTopMargin(0.00);
    p2->SetBottomMargin(0.30);
  
    p1->cd();
    p1->SetLogy();
    if(Htype.find("mll")!=std::string::npos)
      p1->SetLogx();
  }
  else{
    cs->SetLogy();
    if(Htype.find("mll")!=std::string::npos)
      cs->SetLogx();
  }
  
  dummy->Draw();
  hs->Draw("HISTsame");
  hs->GetYaxis()->CenterTitle(kTRUE);
  hs->GetYaxis()->SetTitleSize(0.05);
  hs->GetYaxis()->SetTitleOffset(1.20);
  hs->GetYaxis()->SetTitle( "Events" );
  Plots.at(0)->Draw("pEsame");
  gPad->RedrawAxis();
   
  TLegend *leg = NULL;
  if(useRatio) leg = new TLegend(0.59,0.60,0.99,0.91);
  else         leg = new TLegend(0.59,0.71,0.99,0.91);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->AddEntry(Plots.at(0),"data","p");
  leg->AddEntry(Plots.at(1),"Top","f");
  leg->AddEntry(Plots.at(2),"Diboson","f");
  if(lfvType!="emu")
    leg->AddEntry(Plots.at(4),"W+jets","f");
  leg->AddEntry(Plots.at(3),"Drell-Yan","f");
  leg->Draw();

  DrawLabels(useRatio);
  DrawChannel(lfvType,useRatio);

  if(useRatio){
    p2->cd();
    p2->SetGridy();
    p2->SetLogx();
    ratioLine->Draw("hist");
    ratio->Draw("pE0same");
  }
  
}

std::vector<TH1F*> RetrieveHistos(std::string lfvType, std::string Htype,
				  std::string Fname){
  m_vecH.clear();
  
  TFile *InF    = new TFile( (Fname+"Plots_Nominal_"+lfvType+".root").c_str() );
  TH1F *data = (TH1F*)InF->Get( ("h"+Htype+"_data").c_str()    );
  TH1F *Top  = (TH1F*)InF->Get( ("h"+Htype+"_Top").c_str()     );
  TH1F *Db   = (TH1F*)InF->Get( ("h"+Htype+"_DiBoson").c_str() );
  TH1F *Dy   = (TH1F*)InF->Get( ("h"+Htype+"_DY").c_str()      );
  TH1F *Wj   = (TH1F*)InF->Get( ("h"+Htype+"_Wjets").c_str()   );

  m_vecH.push_back( data );
  m_vecH.push_back( Top  );
  m_vecH.push_back( Db   );
  m_vecH.push_back( Dy   );
  m_vecH.push_back( Wj   );

  std::cout << Fname << " : " << std::endl;
  std::cout << "    Data    = " << data -> Integral() << std::endl;
  std::cout << "    Top     = " << Top  -> Integral() << std::endl;
  std::cout << "    Db      = " << Db   -> Integral() << std::endl;
  std::cout << "    DY      = " << Dy   -> Integral() << std::endl;
  std::cout << "    Wj      = " << Wj   -> Integral() << std::endl;
  std::cout << "    Data-MC = "
	    << data->Integral()-(Top-> Integral()+Db-> Integral()+
				 Dy-> Integral()+Wj-> Integral()) << std::endl;
  std::cout << "" << std::endl;

  return m_vecH;
}

void DeriveKfactor(std::string lfvType, std::string Htype,
		   bool isFFcat,        bool useBjet,
		   bool isttCR,         bool isRevDphi,
		   bool useNoPtCut,     bool doProngs){
  
  SetATLASStyle();
  TH1::SetDefaultSumw2(kTRUE);
  
  std::string Dir = "";
  if(useBjet){ Dir += "Bjet/";   }
  else{        Dir += "NoBjet/"; }

  if(isttCR)   { Dir += "ttbarCR/"; }
  if(isRevDphi){ Dir += "revDphi/"; }

  std::string nR1_SS = Dir+"QcdReg1_SS";
  std::string nR1_OS = Dir+"QcdReg1_OS";
  std::string nR2_SS = Dir+"QcdReg2_SS";
  std::string nR2_OS = Dir+"QcdReg2_OS";
  std::string nR3    = Dir+"QcdReg3";
  std::string nR3_SS = Dir+"QcdReg3_SS";
  std::string nR3_OS = Dir+"QcdReg3_OS";

  std::string nR1_SS_pt = Dir+"QcdReg1_SS_NoPtCut";
  std::string nR1_OS_pt = Dir+"QcdReg1_OS_NoPtCut";
  std::string nR2_SS_pt = Dir+"QcdReg2_SS_NoPtCut";
  std::string nR2_OS_pt = Dir+"QcdReg2_OS_NoPtCut";

  std::string nR1_SS_1p = Dir+"QcdReg1_SS_1p";
  std::string nR2_SS_1p = Dir+"QcdReg2_SS_1p";
  std::string nR3_1p    = Dir+"QcdReg3_1p";
  std::string nR1_SS_3p = Dir+"QcdReg1_SS_3p";
  std::string nR2_SS_3p = Dir+"QcdReg2_SS_3p";
  std::string nR3_3p    = Dir+"QcdReg3_3p";
  
  if(isFFcat){
    nR1_SS    += "/"; nR2_SS    += "/"; nR1_OS    += "/"; nR2_OS    += "/";
    nR3       += "/"; nR3_SS    += "/"; nR3_OS    += "/";
    nR1_SS_pt += "/"; nR1_OS_pt += "/"; nR2_SS_pt += "/"; nR2_OS_pt += "/";
    nR1_SS_1p += "/"; nR1_SS_3p += "/"; nR2_SS_1p += "/"; nR2_SS_3p += "/";
    nR3_1p    += "/"; nR3_3p    += "/";
  }
  else{
    nR1_SS    += "/LepFake/"; nR2_SS    += "/LepFake/"; nR3_SS += "/LepFake/";
    nR1_OS    += "/LepFake/"; nR2_OS    += "/LepFake/"; nR3_OS += "/LepFake/"; 
    nR3       += "/LepFake/";
    nR1_SS_pt += "/LepFake/"; nR1_OS_pt += "/LepFake/";
    nR2_SS_pt += "/LepFake/"; nR2_OS_pt += "/LepFake/";
    nR1_SS_1p += "/LepFake/"; nR1_SS_3p += "/LepFake/";
    nR2_SS_1p += "/LepFake/"; nR2_SS_3p += "/LepFake/";
    nR3_1p    += "/LepFake/"; nR3_3p    += "/LepFake/";
  }

  std::vector<TH1F*> vecR1_SS = RetrieveHistos(lfvType,Htype,nR1_SS);
  std::vector<TH1F*> vecR2_SS = RetrieveHistos(lfvType,Htype,nR2_SS);
  std::vector<TH1F*> vecR3    = RetrieveHistos(lfvType,Htype,nR3);

  std::vector<TH1F*> vecR1_OS, vecR2_OS, vecR3_SS, vecR3_OS;
  std::vector<TH1F*> vecR1_SS_pt, vecR2_SS_pt, vecR1_OS_pt, vecR2_OS_pt;
  std::vector<TH1F*> vecR1_SS_1p, vecR2_SS_1p, vecR1_SS_3p, vecR2_SS_3p;
  std::vector<TH1F*> vecR3_1p, vecR3_3p;
  if(!isttCR && !isRevDphi){
    vecR1_OS = RetrieveHistos(lfvType,Htype,nR1_OS);
    vecR2_OS = RetrieveHistos(lfvType,Htype,nR2_OS);
    vecR3_SS = RetrieveHistos(lfvType,Htype,nR3_SS);
    vecR3_OS = RetrieveHistos(lfvType,Htype,nR3_OS);
    if(useNoPtCut){
      vecR1_SS_pt = RetrieveHistos(lfvType,Htype,nR1_SS_pt);
      vecR2_SS_pt = RetrieveHistos(lfvType,Htype,nR2_SS_pt);
      vecR1_OS_pt = RetrieveHistos(lfvType,Htype,nR1_OS_pt);
      vecR2_OS_pt = RetrieveHistos(lfvType,Htype,nR2_OS_pt);
    }
    if(doProngs){
      vecR1_SS_1p = RetrieveHistos(lfvType,Htype,nR1_SS_1p);
      vecR2_SS_1p = RetrieveHistos(lfvType,Htype,nR2_SS_1p);
      vecR1_SS_3p = RetrieveHistos(lfvType,Htype,nR1_SS_3p);
      vecR2_SS_3p = RetrieveHistos(lfvType,Htype,nR2_SS_3p);
      vecR3_1p    = RetrieveHistos(lfvType,Htype,nR3_1p);
      vecR3_3p    = RetrieveHistos(lfvType,Htype,nR3_3p);
    }
  }
  
  TH1F *mjReg1_SS = GetMultijet(vecR1_SS,"Reg1_SS");
  TH1F *mjReg2_SS = GetMultijet(vecR2_SS,"Reg2_SS");
  TH1F *mjReg3    = GetMultijet(vecR3   ,"Reg3"   );

  TH1F *mjReg1_OS = NULL, *mjReg2_OS = NULL;
  TH1F *mjReg3_SS = NULL, *mjReg3_OS = NULL;
  TH1F *mjReg1_OS_Copy = NULL, *mjReg1_SS_Copy=NULL;
  TH1F *mjReg2_OS_Copy = NULL, *mjReg2_SS_Copy=NULL;
  TH1F *mjReg1_SS_pt = NULL, *mjReg1_OS_pt = NULL;
  TH1F *mjReg2_SS_pt = NULL, *mjReg2_OS_pt = NULL;
  TH1F *mjReg1_SS_1p = NULL, *mjReg1_SS_3p = NULL;
  TH1F *mjReg2_SS_1p = NULL, *mjReg2_SS_3p = NULL;
  TH1F *mjReg3_1p    = NULL, *mjReg3_3p    = NULL;
  TH1F *mjReg1_SS_pt_Copy = NULL, *mjReg1_OS_pt_Copy = NULL;
  TH1F *mjReg2_SS_pt_Copy = NULL, *mjReg2_OS_pt_Copy = NULL;
  TH1F *mjReg1_SS_1p_Copy = NULL, *mjReg1_SS_3p_Copy = NULL;
  TH1F *mjReg2_SS_1p_Copy = NULL, *mjReg2_SS_3p_Copy = NULL;
  TH1F *mjReg3_1p_Copy    = NULL, *mjReg3_3p_Copy    = NULL;
  if(!isttCR && !isRevDphi){
    std::cout << "if ttCR or Dphi this should not appear" << std::endl;
    mjReg1_OS      = GetMultijet(vecR1_OS,"Reg1_OS");
    mjReg2_OS      = GetMultijet(vecR2_OS,"Reg2_OS");
    mjReg3_SS      = GetMultijet(vecR3_SS,"Reg2_SS");
    mjReg3_OS      = GetMultijet(vecR3_OS,"Reg2_OS");
    mjReg1_OS_Copy = (TH1F*)mjReg1_OS->Clone( "mj_Reg1_OS_Copy" );
    mjReg1_SS_Copy = (TH1F*)mjReg1_SS->Clone( "mj_Reg1_SS_Copy" );
    mjReg2_OS_Copy = (TH1F*)mjReg2_OS->Clone( "mj_Reg2_OS_Copy" );
    mjReg2_SS_Copy = (TH1F*)mjReg2_SS->Clone( "mj_Reg2_SS_Copy" );
    mjReg1_OS_Copy -> Scale( 1. / mjReg1_OS_Copy->Integral() );
    mjReg1_SS_Copy -> Scale( 1. / mjReg1_SS_Copy->Integral() );
    mjReg2_OS_Copy -> Scale( 1. / mjReg2_OS_Copy->Integral() );
    mjReg2_SS_Copy -> Scale( 1. / mjReg2_SS_Copy->Integral() );
    mjReg3_SS      -> Scale( 1. / mjReg3_SS->Integral()      );
    mjReg3_OS      -> Scale( 1. / mjReg3_OS->Integral()      );
    if(useNoPtCut){
      mjReg1_SS_pt = GetMultijet(vecR1_SS_pt,"Reg1_SS_pt");
      mjReg2_SS_pt = GetMultijet(vecR2_SS_pt,"Reg2_SS_pt");
      mjReg1_OS_pt = GetMultijet(vecR1_OS_pt,"Reg1_OS_pt");
      mjReg2_OS_pt = GetMultijet(vecR2_OS_pt,"Reg2_OS_pt");

      mjReg1_SS_pt_Copy = (TH1F*)mjReg1_SS_pt->Clone( "Reg1_SS_pt_Copy" );
      mjReg2_SS_pt_Copy = (TH1F*)mjReg2_SS_pt->Clone( "Reg2_SS_pt_Copy" );
      mjReg1_OS_pt_Copy = (TH1F*)mjReg1_OS_pt->Clone( "Reg1_OS_pt_Copy" );
      mjReg2_OS_pt_Copy = (TH1F*)mjReg2_OS_pt->Clone( "Reg2_OS_pt_Copy" );
    }
    if(doProngs){
      mjReg1_SS_1p = GetMultijet(vecR1_SS_1p,"Reg1_SS_1p");
      mjReg2_SS_1p = GetMultijet(vecR2_SS_1p,"Reg2_SS_1p");
      mjReg1_SS_3p = GetMultijet(vecR1_SS_3p,"Reg1_SS_3p");
      mjReg2_SS_3p = GetMultijet(vecR2_SS_3p,"Reg2_SS_3p");
      mjReg3_1p    = GetMultijet(vecR3_1p   ,"Reg3_1p"   );
      mjReg3_3p    = GetMultijet(vecR3_3p   ,"Reg3_3p"   );

      mjReg1_SS_1p_Copy = (TH1F*)mjReg1_SS_1p->Clone( "Reg1_SS_1p_Copy" );
      mjReg2_SS_1p_Copy = (TH1F*)mjReg2_SS_1p->Clone( "Reg2_SS_1p_Copy" );
      mjReg1_SS_3p_Copy = (TH1F*)mjReg1_SS_3p->Clone( "Reg1_SS_3p_Copy" );
      mjReg2_SS_3p_Copy = (TH1F*)mjReg2_SS_3p->Clone( "Reg2_SS_3p_Copy" );
      mjReg3_1p_Copy    = (TH1F*)mjReg3_1p   ->Clone( "Reg3_1p_Copy" );
      mjReg3_3p_Copy    = (TH1F*)mjReg3_3p   ->Clone( "Reg3_3p_Copy" );
    }
  }
  mjReg3 -> Scale( 1. / mjReg3->Integral() );
  
  TH1F *dummy  = (TH1F*)mjReg1_SS->Clone("dummy");
  TH1F *dummy2 = (TH1F*)mjReg1_SS->Clone("dummy2");
  TH1F *dummy3 = (TH1F*)mjReg1_SS->Clone("dummy3");
  dummy->Reset(); dummy2->Reset(); dummy3->Reset();
  dummy3->GetYaxis()->SetTitle( "k_{Multijet}" );
    
  /* Set Axis Title */
  std::ostringstream sstream;
  sstream << std::setprecision(2) << mjReg1_SS->GetBinWidth(2);
  std::string Bsize = sstream.str();
  if(Htype.find("pt")!=std::string::npos || Htype=="njet" ||
     Htype.find("mll")!=std::string::npos ){
    dummy->GetYaxis()->SetTitle( "Events" );
    dummy2->GetYaxis()->SetTitle( "Events" );
  }
  else if( (Htype.find("met")!=std::string::npos) ){
    dummy->GetYaxis()->SetTitle( ("Events / "+Bsize+" GeV").c_str() );
    dummy2->GetYaxis()->SetTitle( ("Events / "+Bsize+" GeV").c_str() );
  }
  else{
    dummy->GetYaxis()->SetTitle( ("Events / "+Bsize).c_str() );
    dummy2->GetYaxis()->SetTitle( ("Events / "+Bsize).c_str() );
  }

  Double_t Xmin=120, Xmax = 3000;
  if(isRevDphi || isttCR) { Xmin = 80; }
  dummy->GetXaxis()->SetRangeUser(Xmin,Xmax);
  dummy->GetYaxis()->SetRangeUser(0.005,90000000);
  dummy->GetYaxis()->SetTitleSize(0.06);
  dummy->GetYaxis()->SetLabelSize(0.05);
  dummy->GetYaxis()->SetTitleOffset(1.00);
  dummy->GetXaxis()->SetMoreLogLabels(kTRUE);
  dummy->GetXaxis()->SetNoExponent(kTRUE);

  dummy2->GetXaxis()->SetRangeUser(Xmin,Xmax);
  dummy2->GetYaxis()->SetRangeUser(0.00005,5);
  dummy2->GetYaxis()->SetTitleSize(0.06);
  dummy2->GetYaxis()->SetLabelSize(0.05);
  dummy2->GetYaxis()->SetTitleOffset(1.00);
  dummy2->GetXaxis()->SetMoreLogLabels(kTRUE);
  dummy2->GetXaxis()->SetNoExponent(kTRUE);

  dummy3->GetXaxis()->SetRangeUser(Xmin,Xmax);
  dummy3->GetYaxis()->SetRangeUser(0.,1.);
  dummy3->GetYaxis()->SetTitleSize(0.06);
  dummy3->GetYaxis()->SetLabelSize(0.05);
  dummy3->GetYaxis()->SetTitleOffset(1.00);
  dummy3->GetXaxis()->SetMoreLogLabels(kTRUE);
  dummy3->GetXaxis()->SetNoExponent(kTRUE);
  
  mjReg2_SS -> SetLineColor(kBlack);
  mjReg2_SS -> SetMarkerSize(0);
  mjReg1_SS -> SetLineColor(kRed);
  mjReg1_SS -> SetMarkerSize(0);
  mjReg3    -> SetLineColor(kBlack);
  if(!isttCR && !isRevDphi){
    std::cout << "if ttCR or Dphi this should not appear" << std::endl;
    mjReg2_OS -> SetLineColor(kBlack);
    mjReg2_OS -> SetMarkerSize(0);
    mjReg1_OS -> SetLineColor(kRed);
    mjReg1_OS -> SetMarkerSize(0);
    mjReg3_SS -> SetLineColor(kRed);
    mjReg3_SS -> SetMarkerSize(0);
    mjReg3_OS -> SetLineColor(kBlue);
    mjReg3_OS -> SetMarkerSize(0);
    
    mjReg1_SS_Copy -> SetLineColor( kBlack   );
    mjReg1_SS_Copy -> SetMarkerSize(0);
    mjReg1_OS_Copy -> SetLineColor( kRed     );
    mjReg1_OS_Copy -> SetMarkerSize(0);
    mjReg2_SS_Copy -> SetLineColor( kBlack   );
    mjReg2_SS_Copy -> SetMarkerSize(0);
    mjReg2_OS_Copy -> SetLineColor( kRed     );
    mjReg2_OS_Copy -> SetMarkerSize(0);
    mjReg3_SS      -> SetLineColor( kGreen+2 );
    mjReg3_SS      -> SetMarkerSize(0);
    mjReg3_OS      -> SetLineColor( kRed     );
    mjReg3_OS      -> SetMarkerSize(0);
    if(useNoPtCut){
      mjReg1_SS_pt -> SetMarkerSize(0);
      mjReg1_SS_pt -> SetLineColor( kRed );
      mjReg1_OS_pt -> SetMarkerSize(0);
      mjReg1_OS_pt -> SetLineColor( kRed );
      mjReg2_SS_pt -> SetMarkerSize(0);
      mjReg2_OS_pt -> SetMarkerSize(0);

      mjReg1_SS_pt_Copy -> SetMarkerSize(0);
      mjReg1_SS_pt_Copy -> SetLineColor(kGreen+2);
      mjReg2_SS_pt_Copy -> SetMarkerSize(0);
      mjReg2_SS_pt_Copy -> SetLineColor(kBlue);
      mjReg1_OS_pt_Copy -> SetMarkerSize(0);
      mjReg1_OS_pt_Copy -> SetLineColor(kGreen+2);
      mjReg2_OS_pt_Copy -> SetMarkerSize(0);
      mjReg2_OS_pt_Copy -> SetLineColor(kBlue);
    }
    if(doProngs){
      mjReg1_SS_1p -> SetMarkerSize(0);
      mjReg1_SS_1p -> SetLineColor( kRed );
      mjReg1_SS_3p -> SetMarkerSize(0);
      mjReg1_SS_3p -> SetLineColor( kRed );
      mjReg2_SS_1p -> SetMarkerSize(0);
      mjReg2_SS_3p -> SetMarkerSize(0);
      mjReg3_1p    -> SetMarkerSize(0);
      mjReg3_1p    -> SetMarkerColor(kRed);
      mjReg3_1p    -> SetLineColor(kRed);
      mjReg3_3p    -> SetMarkerSize(0);
      mjReg3_3p    -> SetMarkerColor(kBlack);
      mjReg3_3p    -> SetLineColor(kBlack);

      mjReg1_SS_1p_Copy -> SetMarkerSize(0);
      mjReg1_SS_1p_Copy -> SetLineColor(kGreen+2);
      mjReg2_SS_1p_Copy -> SetMarkerSize(0);
      mjReg2_SS_1p_Copy -> SetLineColor(kBlue);
      mjReg1_SS_3p_Copy -> SetMarkerSize(0);
      mjReg1_SS_3p_Copy -> SetLineColor(kGreen+2);
      mjReg2_SS_3p_Copy -> SetMarkerSize(0);
      mjReg2_SS_3p_Copy -> SetLineColor(kBlue);
      mjReg3_1p_Copy    -> SetMarkerSize(0);
      mjReg3_1p_Copy    -> SetMarkerColor(kRed);
      mjReg3_3p_Copy    -> SetMarkerSize(0);
      mjReg3_3p_Copy    -> SetMarkerColor(kBlack);
    }
  }
  mjReg3 -> SetLineColor( kBlack );
  
  TH1F *ratio_SS = (TH1F*)mjReg1_SS->Clone("ratio_SS");
  ratio_SS->Reset();
  ratio_SS->GetXaxis()->SetTitle(mjReg1_SS->GetXaxis()->GetTitle());
  ratio_SS->Divide(mjReg2_SS,mjReg1_SS);
  SetRatioPlot(ratio_SS);
  ratio_SS->GetXaxis()->SetRangeUser(Xmin,Xmax);

  TH1F *ratio_OS = NULL, *ratio_R1 = NULL, *ratio_R2 = NULL;
  TH1F *ratio_R3_NomSS = NULL, *ratio_R3_NomOS = NULL, *ratio_R3_OSSS = NULL;
  TH1F *ratio_SS_pt = NULL, *ratio_OS_pt = NULL;
  TH1F *ratio_SS_1p = NULL, *ratio_SS_3p = NULL;
  TH1F *ratio_SS_pt_copy = NULL, *ratio_OS_pt_copy = NULL;
  TH1F *ratio_SS_1p_copy = NULL, *ratio_SS_3p_copy = NULL;
  if(!isttCR && !isRevDphi){
    std::cout << "if ttCR or Dphi this should not appear" << std::endl;
    ratio_OS       = (TH1F*)mjReg1_OS->Clone( "ratio_OS"       );
    ratio_R1       = (TH1F*)mjReg1_SS->Clone( "ratio_R1"       );
    ratio_R2       = (TH1F*)mjReg2_SS->Clone( "ratio_R2"       );
    ratio_R3_NomSS = (TH1F*)mjReg3   ->Clone( "ratio_R3_NomSS" );
    ratio_R3_NomOS = (TH1F*)mjReg3   ->Clone( "ratio_R3_NomOS" );
    ratio_R3_OSSS  = (TH1F*)mjReg3   ->Clone( "ratio_R3_OSSS"  );
    ratio_OS       -> Reset();
    ratio_R1       -> Reset();
    ratio_R2       -> Reset();
    ratio_R3_NomSS -> Reset();
    ratio_R3_NomOS -> Reset();
    ratio_R3_OSSS  -> Reset();
    ratio_OS       -> GetXaxis()->SetTitle( mjReg1_OS->GetXaxis()->GetTitle() );
    ratio_R1       -> GetXaxis()->SetTitle( mjReg1_OS->GetXaxis()->GetTitle() );
    ratio_R2       -> GetXaxis()->SetTitle( mjReg2_OS->GetXaxis()->GetTitle() );
    ratio_R3_NomSS -> GetXaxis()->SetTitle( mjReg1_OS->GetXaxis()->GetTitle() );
    ratio_R3_NomOS -> GetXaxis()->SetTitle( mjReg1_OS->GetXaxis()->GetTitle() );
    ratio_R3_OSSS  -> GetXaxis()->SetTitle( mjReg1_OS->GetXaxis()->GetTitle() );
    std::cout << "dividing" << std::endl;
    ratio_OS       -> Divide(mjReg2_OS,mjReg1_OS);
    std::cout << "dividing news" << std::endl;
    ratio_R1 -> Divide( mjReg1_SS_Copy,mjReg1_OS_Copy );
    std::cout << "1 done" << std::endl;
    ratio_R2  -> Divide( mjReg2_SS_Copy,mjReg2_OS_Copy );
    std::cout << "2 done" << std::endl;
    ratio_R3_NomSS -> Divide( mjReg3_SS,mjReg3              );
    std::cout << "3 done" << std::endl;
    ratio_R3_NomOS -> Divide( mjReg3_OS,mjReg3              );
    std::cout << "4 done" << std::endl;
    ratio_R3_OSSS  -> Divide( mjReg3_OS,mjReg3_SS           );
    std::cout << "5 done" << std::endl;

    std::cout <<"setting ratios"<<std::endl;
    SetRatioPlot( ratio_OS );
    SetRatioPlot( ratio_R1 );
    SetRatioPlot( ratio_R2 );
    SetRatioPlot( ratio_R3_NomSS,kOrange+1,23 );
    SetRatioPlot( ratio_R3_NomOS,kGreen+2,21  );
    SetRatioPlot( ratio_R3_OSSS,kBlue         );
    ratio_OS       -> GetXaxis()->SetRangeUser(Xmin,Xmax);
    ratio_R1       -> GetXaxis()->SetRangeUser(Xmin,Xmax);
    ratio_R2       -> GetXaxis()->SetRangeUser(Xmin,Xmax);
    ratio_R3_NomSS -> GetXaxis()->SetRangeUser(Xmin,Xmax);
    ratio_R3_NomOS -> GetXaxis()->SetRangeUser(Xmin,Xmax);
    ratio_R3_OSSS  -> GetXaxis()->SetRangeUser(Xmin,Xmax);
    std::cout << "if ttCR or Dphi this should not appear" << std::endl;
    if(useNoPtCut){
      ratio_OS_pt  = (TH1F*)mjReg1_OS->Clone( "ratio_OS_pt" );
      ratio_SS_pt  = (TH1F*)mjReg1_OS->Clone( "ratio_SS_pt" );
      ratio_OS_pt -> Reset();
      ratio_SS_pt -> Reset();
      ratio_OS_pt -> Divide( mjReg2_OS_pt, mjReg1_OS_pt );
      ratio_SS_pt -> Divide( mjReg2_SS_pt, mjReg1_SS_pt );
      ratio_OS_pt -> GetXaxis()->SetTitle( mjReg1_OS_pt->GetXaxis()->GetTitle() );
      ratio_SS_pt -> GetXaxis()->SetTitle( mjReg1_OS_pt->GetXaxis()->GetTitle() );
      SetRatioPlot( ratio_OS_pt );
      SetRatioPlot( ratio_SS_pt );
      ratio_OS_pt -> GetXaxis()->SetRangeUser(Xmin,Xmax);
      ratio_SS_pt -> GetXaxis()->SetRangeUser(Xmin,Xmax);

      ratio_OS_pt_copy = (TH1F*)ratio_OS_pt->Clone( "ratio_OS_pt_copy" );
      ratio_SS_pt_copy = (TH1F*)ratio_SS_pt->Clone( "ratio_SS_pt_copy" );
      SetRatioPlot( ratio_OS_pt_copy,kRed,21 );
      SetRatioPlot( ratio_SS_pt_copy,kRed,21 );
    }
    if(doProngs){
      ratio_SS_3p  = (TH1F*)mjReg1_OS->Clone( "ratio_SS_3p" );
      ratio_SS_1p  = (TH1F*)mjReg1_OS->Clone( "ratio_SS_1p" );
      ratio_SS_3p -> Reset();
      ratio_SS_1p -> Reset();
      ratio_SS_3p -> Divide( mjReg2_SS_3p, mjReg1_SS_3p );
      ratio_SS_1p -> Divide( mjReg2_SS_1p, mjReg1_SS_1p );
      ratio_SS_3p -> GetXaxis()->SetTitle( mjReg1_SS_3p->GetXaxis()->GetTitle() );
      ratio_SS_1p -> GetXaxis()->SetTitle( mjReg1_SS_1p->GetXaxis()->GetTitle() );
      SetRatioPlot( ratio_SS_3p );
      SetRatioPlot( ratio_SS_1p );
      ratio_SS_3p -> GetXaxis()->SetRangeUser(Xmin,Xmax);
      ratio_SS_1p -> GetXaxis()->SetRangeUser(Xmin,Xmax);

      ratio_SS_3p_copy = (TH1F*)ratio_SS_3p->Clone( "ratio_SS_3p_copy" );
      ratio_SS_1p_copy = (TH1F*)ratio_SS_1p->Clone( "ratio_SS_1p_copy" );
      SetRatioPlot( ratio_SS_3p_copy,kGreen+2,21 );
      SetRatioPlot( ratio_SS_1p_copy,kRed,21 );
    }
  }
  //done up to here

  Double_t Ymin=0, Ymax=2.;
  if(lfvType=="etau") { Ymin=-0.15; Ymax=0.35; }
  if(lfvType=="mutau"){ Ymin=-0.15; Ymax=0.85; }
  ratio_SS->GetYaxis()->SetRangeUser(Ymin,Ymax);
  if(!isttCR && !isRevDphi){
    ratio_OS->GetYaxis()->SetRangeUser(Ymin,Ymax);
    ratio_R1->GetYaxis()->SetRangeUser(0.55,1.55);
    ratio_R2->GetYaxis()->SetRangeUser(0.55,1.55);
    ratio_R3_NomOS->GetYaxis()->SetRangeUser(0.55,1.55);
    ratio_R3_NomSS->GetYaxis()->SetRangeUser(0.55,1.55);
    ratio_R3_OSSS->GetYaxis()->SetRangeUser(0.55,1.55);
    if(useNoPtCut){
      ratio_SS_pt->GetYaxis()->SetRangeUser(Ymin,Ymax);
      ratio_OS_pt->GetYaxis()->SetRangeUser(Ymin,Ymax);
    }
  }

  TCanvas *cs_SS = CreateCanvas("SS");
  TPad *p1_SS    = CreateTopPad("SS",Htype);
  TPad *p2_SS    = CreateBottomPad("SS",Htype);

  TCanvas *cs_OS = NULL, *cs_R1 = NULL, *cs_R2 = NULL, *cs_R3 = NULL;
  TPad *p1_OS = NULL, *p2_OS = NULL, *p1_R1 = NULL, *p2_R1 = NULL;
  TPad* p1_R2 = NULL, *p2_R2 = NULL, *p1_R3 = NULL, *p2_R3 = NULL;

  TCanvas *cs_OS_pt = NULL, *cs_SS_pt = NULL,  *cs_SS_1p = NULL, *cs_SS_3p = NULL;
  TCanvas *cs_OS_cp = NULL, *cs_SS_cp = NULL, *cs_SS_kcp = NULL, *cs_R3_p  = NULL;
  TPad *p1_OS_pt = NULL, *p2_OS_pt = NULL, *p1_SS_pt = NULL, *p2_SS_pt = NULL;
  TPad *p1_SS_1p = NULL, *p2_SS_1p = NULL, *p1_SS_3p = NULL, *p2_SS_3p = NULL;
  TPad *p1_OS_cp = NULL, *p2_OS_cp = NULL, *p1_SS_cp = NULL, *p2_SS_cp = NULL;
  
  if(!isRevDphi && !isttCR){
    cs_OS = CreateCanvas("OS");
    p1_OS = CreateTopPad("OS",Htype);
    p2_OS = CreateBottomPad("OS",Htype);
    
    cs_R1 = CreateCanvas("R1");
    p1_R1 = CreateTopPad("R1",Htype);
    p2_R1 = CreateBottomPad("R1",Htype);
    
    cs_R2 = CreateCanvas("R2");
    p1_R2 = CreateTopPad("R2",Htype);
    p2_R2 = CreateBottomPad("R2",Htype);
    
    cs_R3 = CreateCanvas("R3");
    p1_R3 = CreateTopPad("R3",Htype);
    p2_R3 = CreateBottomPad("R3",Htype);
    if(useNoPtCut){
      cs_OS_pt = CreateCanvas("OS_NoPtCut");
      cs_SS_pt = CreateCanvas("SS_NoPtCut");
      p1_OS_pt = CreateTopPad("OS_NoPtCut",Htype);
      p2_OS_pt = CreateBottomPad("OS_NoPtCut",Htype);
      p1_SS_pt = CreateTopPad("SS_NoPtCut",Htype);
      p2_SS_pt = CreateBottomPad("SS_NoPtCut",Htype);
      cs_OS_cp = CreateCanvas("OS_Compare");
      p1_OS_cp = CreateTopPad("OS_Compare",Htype);
      p2_OS_cp = CreateBottomPad("OS_Compare",Htype);
      cs_SS_cp = CreateCanvas("SS_Compare");
      p1_SS_cp = CreateTopPad("SS_Compare",Htype);
      p2_SS_cp = CreateBottomPad("SS_Compare",Htype);
    }
    if(doProngs){
      cs_SS_1p  = CreateCanvas("SS_1p");
      cs_SS_3p  = CreateCanvas("SS_3p");
      p1_SS_1p  = CreateTopPad("SS_1p",Htype);
      p2_SS_1p  = CreateBottomPad("SS_1p",Htype);
      p1_SS_3p  = CreateTopPad("SS_3p",Htype);
      p2_SS_3p  = CreateBottomPad("SS_3p",Htype);
      cs_SS_kcp = CreateCanvas("SS_kmj_Compare");
      cs_R3_p   = CreateCanvas("R3_prongComp");
    }
      
  }

  std::cout << "all created and now drawing" << std::endl;
  /* Draw SS */
  cs_SS->cd();
  p1_SS->Draw();
  p2_SS->Draw();

  p1_SS->cd();
  dummy->Draw();
  mjReg2_SS->Draw("histsameE");
  mjReg1_SS->Draw("histsameE");
  gPad->RedrawAxis();
   
  TLegend *leg_SS = CreateLegend();
  leg_SS->AddEntry(mjReg2_SS,"Multijet - Reg2 (SS)","l");
  leg_SS->AddEntry(mjReg1_SS,"Multijet - Reg1 (SS)","l");
  leg_SS->AddEntry(ratio_SS,"k_{Multijet}","lpe");
  leg_SS->Draw();

  DrawLabels(true);
  DrawChannel(lfvType,true);

  p2_SS->cd();
  ratio_SS->Draw("pE");

  TFile *out = new TFile( (Dir+lfvType+"_"+Htype+"_kfact.root").c_str(),"RECREATE" );
  out->cd();
  ratio_SS->Write("SS_kfact");

  if(!isRevDphi && !isttCR){
    
    /* Draw OS */
    cs_OS->cd();
    p1_OS->Draw();
    p2_OS->Draw();
    
    p1_OS->cd();
    dummy->Draw();
    mjReg2_OS->Draw("histsameE");
    mjReg1_OS->Draw("histsameE");
    gPad->RedrawAxis();
    
    TLegend *leg_OS = CreateLegend();
    leg_OS->AddEntry(mjReg2_OS,"Multijet - Reg2 (OS)","l");
    leg_OS->AddEntry(mjReg1_OS,"Multijet - Reg1 (OS)","l");
    leg_OS->AddEntry(ratio_OS,"k_{Multijet}","lpe");
    leg_OS->Draw();
    
    DrawLabels(true);
    DrawChannel(lfvType,true);
    
    p2_OS->cd();
    ratio_OS->Draw("pE");
    ratio_OS->Write("OS_kfact");
    
    /* Draw Reg1 */
    cs_R1->cd();
    p1_R1->Draw();
    p2_R1->Draw();
    
    p1_R1->cd();
    dummy2->Draw();
    mjReg1_OS_Copy->Draw("histsameE");
    mjReg1_SS_Copy->Draw("histsameE");
    
    TLegend *leg_R1 = CreateLegend();
    leg_R1->AddEntry(mjReg1_OS_Copy,"Multijet - Reg1 (OS)","l");
    leg_R1->AddEntry(mjReg1_SS_Copy,"Multijet - Reg1 (SS)","l");
    leg_R1->AddEntry(ratio_R1,"Reg1 (OS) / Reg1 (SS)","pE");
    leg_R1->Draw();
    
    DrawLabels(true);
    DrawChannel(lfvType,true);
    
    p2_R1->cd();
    ratio_R1->Draw("pE");
    
    /* Draw Reg2 */
    cs_R2->cd();
    p1_R2->Draw();
    p2_R2->Draw();

    p1_R2->cd();
    dummy2->Draw();
    mjReg2_OS_Copy->Draw("histsameE");
    mjReg2_SS_Copy->Draw("histsameE");
    
    TLegend *leg_R2 = CreateLegend();
    leg_R2->AddEntry(mjReg2_OS_Copy,"Multijet - Reg2 (OS)","l");
    leg_R2->AddEntry(mjReg2_SS_Copy,"Multijet - Reg2 (SS)","l");
    leg_R2->AddEntry(ratio_R2,"Reg2 (OS) / Reg2 (SS)","pE");
    leg_R2->Draw();
    
    DrawLabels(true);
    DrawChannel(lfvType,true);
    
    p2_R2->cd();
    ratio_R2->Draw("pE");
    
    /* Draw Reg3 */
    cs_R3->cd();
    p1_R3->Draw();
    p2_R3->Draw();
    
    p1_R3->cd();
    dummy2->Draw();
    mjReg3   ->Draw("histsame");
    mjReg3_OS->Draw("histsameE");
    mjReg3_SS->Draw("histsameE");
    
    TLegend *leg_R3 = CreateLegend();
    leg_R3->AddEntry(mjReg3,"Multijet - Reg3 (OS+SS)","l");
    leg_R3->AddEntry(mjReg3_OS,"Multijet - Reg3 (OS)","l");
    leg_R3->AddEntry(mjReg3_SS,"Multijet - Reg3 (SS)","l");
    leg_R3->AddEntry(ratio_R3_NomSS,"Reg3 (SS) / Reg3 (OS+SS)","pE");
    leg_R3->AddEntry(ratio_R3_NomOS,"Reg3 (OS) / Reg3 (OS+SS)","pE");
    leg_R3->AddEntry(ratio_R3_OSSS ,"Reg3 (OS) / Reg3 (SS)","pE");
    leg_R3->Draw();
    
    DrawLabels(true);
    DrawChannel(lfvType,true);
    
    p2_R3->cd();
    ratio_R3_NomSS->Draw("pE");
    ratio_R3_NomOS->Draw("pEsame");
    ratio_R3_OSSS->Draw("pEsame");

    if(useNoPtCut){
      /* Draw SS No pT cut */
      cs_SS_pt->cd();
      p1_SS_pt->Draw();
      p2_SS_pt->Draw();
      
      p1_SS_pt->cd();
      dummy->Draw();
      mjReg2_SS_pt->Draw("histsameE");
      mjReg1_SS_pt->Draw("histsameE");
      gPad->RedrawAxis();
      
      TLegend *leg_SS_pt = CreateLegend();
      leg_SS_pt->AddEntry(mjReg2_SS_pt,"Multijet - Reg2 (SS - No p_{T}^{l} cut)","l");
      leg_SS_pt->AddEntry(mjReg1_SS_pt,"Multijet - Reg1 (SS - No p_{T}^{l} cut)","l");
      leg_SS_pt->AddEntry(ratio_SS_pt,"k_{Multijet}","lpe");
      leg_SS_pt->Draw();
      
      DrawLabels(true);
      DrawChannel(lfvType,true);
      
      p2_SS_pt->cd();
      ratio_SS_pt->Draw("pE");
      ratio_SS_pt->Write("SS_kfact_NoPtCut");

      /* Draw OS No pT cut */
      cs_OS_pt->cd();
      p1_OS_pt->Draw();
      p2_OS_pt->Draw();
      
      p1_OS_pt->cd();
      dummy->Draw();
      mjReg2_OS_pt->Draw("histsameE");
      mjReg1_OS_pt->Draw("histsameE");
      gPad->RedrawAxis();
      
      TLegend *leg_OS_pt = CreateLegend();
      leg_OS_pt->AddEntry(mjReg2_OS_pt,"Multijet - Reg2 (OS - No p_{T}^{lep} cut)","l");
      leg_OS_pt->AddEntry(mjReg1_OS_pt,"Multijet - Reg1 (OS - No p_{T}^{lep} cut)","l");
      leg_OS_pt->AddEntry(ratio_OS_pt,"k_{Multijet}","lpe");
      leg_OS_pt->Draw();
      
      DrawLabels(true);
      DrawChannel(lfvType,true);
      
      p2_OS_pt->cd();
      ratio_OS_pt->Draw("pE");
      ratio_OS_pt->Write("OS_kfact_NoPtCut");

      /* Draw SS compare */
      cs_SS_cp->cd();
      p1_SS_cp->Draw();
      p2_SS_cp->Draw();
      
      p1_SS_cp->cd();
      dummy->Draw();
      mjReg2_SS->Draw("histsameE");
      mjReg1_SS->Draw("histsameE");
      mjReg2_SS_pt_Copy->Draw("histsameE");
      mjReg1_SS_pt_Copy->Draw("histsameE");
      gPad->RedrawAxis();
      
      TLegend *leg_SS_cp = CreateLegend();
      leg_SS_cp->AddEntry(mjReg2_SS,"Multijet - Reg2 (SS)","l");
      leg_SS_cp->AddEntry(mjReg1_SS,"Multijet - Reg1 (SS)","l");
      leg_SS_cp->AddEntry(mjReg2_SS_pt_Copy,"Multijet - Reg2 (SS - No p_{T}^{lep} cut)","l");
      leg_SS_cp->AddEntry(mjReg1_SS_pt_Copy,"Multijet - Reg1 (SS - No p_{T}^{lep} cut)","l");
      leg_SS_cp->AddEntry(ratio_SS,"k_{Multijet} (SS)","lpe");
      leg_SS_cp->AddEntry(ratio_SS_pt_copy,"k_{Multijet} (SS - No p_{T}^{lep} cut)","lpe");
      leg_SS_cp->Draw();
      
      DrawLabels(true);
      DrawChannel(lfvType,true);

      p2_SS_cp->cd();
      ratio_SS->Draw("pE");
      ratio_SS_pt_copy->Draw("pEsame");
      
      /* Draw OS compare */
      cs_OS_cp->cd();
      p1_OS_cp->Draw();
      p2_OS_cp->Draw();
      
      p1_OS_cp->cd();
      dummy->Draw();
      mjReg2_OS->Draw("histsameE");
      mjReg1_OS->Draw("histsameE");
      mjReg2_OS_pt_Copy->Draw("histsameE");
      mjReg1_OS_pt_Copy->Draw("histsameE");
      gPad->RedrawAxis();
      
      TLegend *leg_OS_cp = CreateLegend();
      leg_OS_cp->AddEntry(mjReg2_OS,"Multijet - Reg2 (OS)","l");
      leg_OS_cp->AddEntry(mjReg1_OS,"Multijet - Reg1 (OS)","l");
      leg_OS_cp->AddEntry(mjReg2_OS_pt_Copy,"Multijet - Reg2 (OS - No p_{T}^{lep} cut)","l");
      leg_OS_cp->AddEntry(mjReg1_OS_pt_Copy,"Multijet - Reg1 (OS - No p_{T}^{lep} cut)","l");
      leg_OS_cp->AddEntry(ratio_OS,"k_{Multijet} (OS)","lpe");
      leg_OS_cp->AddEntry(ratio_OS_pt_copy,"k_{Multijet} (OS - No p_{T}^{lep} cut)","lpe");
      leg_OS_cp->Draw();
      
      DrawLabels(true);
      DrawChannel(lfvType,true);

      p2_OS_cp->cd();
      ratio_OS->Draw("pE");
      ratio_OS_pt_copy->Draw("pEsame");
      
    }

    if(doProngs){
      /* Draw SS 1p */
      cs_SS_1p->cd();
      p1_SS_1p->Draw();
      p2_SS_1p->Draw();
      
      p1_SS_1p->cd();
      dummy->Draw();
      mjReg2_SS_1p->Draw("histsameE");
      mjReg1_SS_1p->Draw("histsameE");
      gPad->RedrawAxis();
      
      TLegend *leg_SS_1p = CreateLegend();
      leg_SS_1p->AddEntry(mjReg2_SS_1p,"Multijet - Reg2 (SS - 1-prong)","l");
      leg_SS_1p->AddEntry(mjReg1_SS_1p,"Multijet - Reg1 (SS - 1-prong)","l");
      leg_SS_1p->AddEntry(ratio_SS_1p,"k_{Multijet}","lpe");
      leg_SS_1p->Draw();
      
      DrawLabels(true);
      DrawChannel(lfvType,true);
      
      p2_SS_1p->cd();
      ratio_SS_1p->Draw("pE");
      ratio_SS_1p->Write("SS_kfact_1prong");

      /* Draw SS 3p */
      cs_SS_3p->cd();
      p1_SS_3p->Draw();
      p2_SS_3p->Draw();
      
      p1_SS_3p->cd();
      dummy->Draw();
      mjReg2_SS_3p->Draw("histsameE");
      mjReg1_SS_3p->Draw("histsameE");
      gPad->RedrawAxis();
      
      TLegend *leg_SS_3p = CreateLegend();
      leg_SS_3p->AddEntry(mjReg2_SS_3p,"Multijet - Reg2 (SS - 3-prongs)","l");
      leg_SS_3p->AddEntry(mjReg1_SS_3p,"Multijet - Reg1 (SS - 3-prongs)","l");
      leg_SS_3p->AddEntry(ratio_SS_3p,"k_{Multijet}","lpe");
      leg_SS_3p->Draw();
      
      DrawLabels(true);
      DrawChannel(lfvType,true);
      
      p2_SS_3p->cd();
      ratio_SS_3p->Draw("pE");
      ratio_SS_3p->Write("SS_kfact_3prongs");

      /* Draw SS kmj compare */
      cs_SS_kcp->cd();
      dummy3->Draw();
      ratio_SS->Draw("pEsame");
      ratio_SS_1p_copy->Draw("pEsame");
      ratio_SS_3p_copy->Draw("pEsame");
      gPad->RedrawAxis();

      TLegend *leg_SS_kcp = CreateLegend();
      leg_SS_kcp->AddEntry(ratio_SS,"k_{Multijet} (SS)","lpe");
      leg_SS_kcp->AddEntry(ratio_SS_1p_copy,"k_{Multijet} (SS - 1-prong)","lpe");
      leg_SS_kcp->AddEntry(ratio_SS_3p_copy,"k_{Multijet} (SS - 3-prongs)","lpe");
      leg_SS_kcp->Draw();
      
      DrawLabels(false);
      DrawChannel(lfvType,false);

      /* Draw R3 prong comp */
      cs_R3_p->cd();
      dummy->Draw();
      mjReg3_1p -> Draw("pEsame");
      mjReg3_3p -> Draw("pEsame");
      gPad->RedrawAxis();

      TLegend *leg_R3_p = CreateLegend();
      leg_R3_p->AddEntry(mjReg3_1p,"Multijet - Reg3 (1-prong)","l");
      leg_R3_p->AddEntry(mjReg3_3p,"Multijet - Reg3 (3-prongs)","l");
      leg_R3_p->Draw();
      
      DrawLabels(false);
      DrawChannel(lfvType,false);
      
    }
  }
  out->Close();

}

void DrawShape(std::string lfvType, std::string Htype, bool useBjet,
	       bool isttCR, bool isRevDphi){

  SetATLASStyle();
  TH1::SetDefaultSumw2(kTRUE);
  
  std::string Dir = "";
  if(useBjet){ Dir += "Bjet/";   }
  else{        Dir += "NoBjet/"; }
  
  if(isttCR)   { Dir += "ttbarCR/"; }
  if(isRevDphi){ Dir += "revDphi/"; }

  TFile *In = new TFile( (Dir+"Plots_Nominal_"+lfvType+".root").c_str() );
  TH1F *hmj = (TH1F*)In->Get( ("h"+Htype+"_qcd").c_str()   );

  /* to be update for each histo */
  Double_t Xmin=130  ,  Xmax = 3000;
  Double_t Ymin=0.005,  Ymax = 9000000;
  if(lfvType=="mutau"){
    Xmax = 2000;  Ymax = 900000;
  }
  
  hmj->GetXaxis()->SetRangeUser(Xmin,Xmax);
  hmj->GetYaxis()->SetRangeUser(Ymin,Ymax);
  hmj->GetYaxis()->SetTitleSize(0.04);
  hmj->GetYaxis()->SetLabelSize(0.04);
  hmj->GetYaxis()->SetTitleOffset(1.50);
  hmj->GetXaxis()->SetMoreLogLabels(kTRUE);
  hmj->GetXaxis()->SetNoExponent(kTRUE);
  hmj->GetYaxis()->SetTitle("Events"); /* to be update for each histo */
  
  TCanvas *cs = new TCanvas("cs","cs",0,0,600,600);
  cs->cd();
  cs->SetLogy(true);
 
  if(Htype.find("mll")!=std::string::npos) cs->SetLogx(true);

  hmj->Draw("hist");
  DrawLabels();
  DrawChannel(lfvType);

  std::cout << " Multijet = " << hmj->Integral() << std::endl; 
  
}

void DeriveSys(std::string lfvType, std::string Htype, bool useBjet,
	       bool isttCR, bool isRevDphi){

  SetATLASStyle();
  TH1::SetDefaultSumw2(kTRUE);
  
  std::string Dir = "";
  if(useBjet){ Dir += "Bjet/";   }
  else{        Dir += "NoBjet/"; }
  
  if(isttCR)   { Dir += "ttbarCR/"; }
  if(isRevDphi){ Dir += "revDphi/"; }

  if(lfvType=="emu") SysElecMuon(useBjet);
  else               SysLepTau(lfvType, Htype, Dir);

}

void SysElecMuon(bool useBjet){

  std::string name = "QCDemu";
  if(useBjet) name += "_bjetVeto";
  
  TFile *Nom = new TFile( ("VarInputs/"+name+".root").c_str()     );
  TFile *Sys = new TFile( ("VarInputs/"+name+"_sys.root").c_str() );
  
  TH1F *nom = (TH1F*)Nom->Get( "hmllqcd"         );
  TH1F *mt  = (TH1F*)Sys->Get( "hmllqcdmT"       );
  TH1F *met = (TH1F*)Sys->Get( "hmllqcdmet"      );
  TH1F *mcU = (TH1F*)Sys->Get( "hmllqcdMCplus"   );
  TH1F *mcD = (TH1F*)Sys->Get( "hmllqcdMCminus"  );
  TH1F *lmU = (TH1F*)Sys->Get( "hmllqcdLumiup"   );
  TH1F *lmD = (TH1F*)Sys->Get( "hmllqcdLumidown" );
  TH1F *jet = (TH1F*)Sys->Get( "hmllqcdjetsys"   );

  nom->SetLineColor(kBlack);
  mt ->SetLineColor(kRed);
  met->SetLineColor(kGreen);
  mcU->SetLineColor(kBlue);
  mcD->SetLineColor(kYellow);
  lmU->SetLineColor(kMagenta);
  lmD->SetLineColor(kCyan);
  jet->SetLineColor(kGreen+2);

  TCanvas *cs = new TCanvas("cs","cs",0,0,600,600);
  cs->cd();
  cs->SetLogy(true);
  cs->SetLogx(true);

  nom->GetYaxis()->SetTitle("Events");
  nom->GetXaxis()->SetRangeUser(120,2000);
  nom->GetYaxis()->SetRangeUser(0.005,10000);
  nom->GetXaxis()->SetMoreLogLabels(kTRUE);
  nom->GetXaxis()->SetNoExponent(kTRUE);
  
  nom->Draw("hist");
  
  DrawLabels();
  DrawChannel("emu",false);

  TCanvas *cs2 = new TCanvas("cs2","cs2",0,0,600,600);
  cs2->cd();
  cs2->SetLogy(true);
  cs2->SetLogx(true);

  nom->Draw("hist");
  mt ->Draw("histsame");
  met->Draw("histsame");
  mcU->Draw("histsame");
  mcD->Draw("histsame");
  lmU->Draw("histsame");
  lmD->Draw("histsame");
  jet->Draw("histsame");
  
  TLegend *leg = new TLegend(0.55,0.62,0.92,0.92);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->AddEntry(nom,"Central Value", "l");
  leg->AddEntry(mt,"m_{T}<40 GeV & MET<25 GeV", "l");
  leg->AddEntry(met,"m_{T}<50 GeV & MET<15 GeV", "l");
  leg->AddEntry(mcU,"MC plus 10%", "l");
  leg->AddEntry(mcD,"MC minus 10%", "l");
  leg->AddEntry(lmU,"Lumi Up 3.2%", "l");
  leg->AddEntry(lmD,"Lumi Down 3.2%", "l");
  leg->AddEntry(jet,"Jet systematic", "l");
  leg->Draw();

  DrawLabels();
  DrawChannel("emu",false);
  
}

void SysLepTau(std::string lfvType, std::string Htype, std::string Dir){
    
  TFile *Nom  = new TFile( (Dir+"Plots_Nominal_"+lfvType+".root").c_str() );
  TFile *Sys  = new TFile( (Dir+"Plots_Multijet_kMJ_Sys_"+lfvType+".root").c_str() );
  TFile *Stat = new TFile( (Dir+"Plots_Multijet_kMJ_Stat_"+lfvType+".root").c_str() );
  TH1F *hmjNom  = (TH1F*)Nom->Get(  ("h"+Htype+"_qcd").c_str()   );
  TH1F *hmjStat = (TH1F*)Stat->Get( ("h"+Htype+"_qcd").c_str()   );
  TH1F *hmjSys  = NULL;
  if(lfvType=="etau")
    hmjSys = (TH1F*)Sys->Get(  ("h"+Htype+"_qcd").c_str() );
  
  /* to be update for each histo */
  Double_t Xmin=130  ,  Xmax = 3000;
  Double_t Ymin=0.005,  Ymax = 9000000;
  if(lfvType=="mutau"){
    Xmax = 2000;  Ymax = 900000;
  }
  
  hmjNom->GetXaxis()->SetRangeUser(Xmin,Xmax);
  hmjNom->GetYaxis()->SetRangeUser(Ymin,Ymax);
  hmjNom->GetYaxis()->SetTitleSize(0.04);
  hmjNom->GetYaxis()->SetLabelSize(0.04);
  hmjNom->GetYaxis()->SetTitleOffset(1.50);
  hmjNom->GetXaxis()->SetMoreLogLabels(kTRUE);
  hmjNom->GetXaxis()->SetNoExponent(kTRUE);
  hmjNom->GetYaxis()->SetTitle("Events"); /* to be update for each histo */
  if(lfvType=="etau"){
    hmjSys->GetXaxis()->SetRangeUser(Xmin,Xmax);
    hmjSys->GetYaxis()->SetRangeUser(Ymin,Ymax);
    hmjSys->GetYaxis()->SetTitleSize(0.04);
    hmjSys->GetYaxis()->SetLabelSize(0.04);
    hmjSys->GetYaxis()->SetTitleOffset(1.50);
    hmjSys->GetXaxis()->SetMoreLogLabels(kTRUE);
    hmjSys->GetXaxis()->SetNoExponent(kTRUE);
    hmjSys->GetYaxis()->SetTitle("Events"); /* to be update for each histo */
  }
  hmjStat->GetXaxis()->SetRangeUser(Xmin,Xmax);
  hmjStat->GetYaxis()->SetRangeUser(Ymin,Ymax);
  hmjStat->GetYaxis()->SetTitleSize(0.04);
  hmjStat->GetYaxis()->SetLabelSize(0.04);
  hmjStat->GetYaxis()->SetTitleOffset(1.50);
  hmjStat->GetXaxis()->SetMoreLogLabels(kTRUE);
  hmjStat->GetXaxis()->SetNoExponent(kTRUE);
  hmjStat->GetYaxis()->SetTitle("Events"); /* to be update for each histo */
  
  TH1F *ratio = (TH1F*)hmjNom->Clone("ratio_Stat");
  ratio->Reset();
  ratio->GetXaxis()->SetTitle(hmjNom->GetXaxis()->GetTitle());
  ratio->Divide(hmjStat,hmjNom);
  SetRatioPlot(ratio,kBlack);
  ratio->GetXaxis()->SetRangeUser(Xmin,Xmax);
  ratio->GetYaxis()->SetRangeUser(0.42,2.08);
  
  TH1F *ratio1 = NULL;
  if(lfvType=="etau"){
    ratio1 = (TH1F*)hmjNom->Clone("ratio_Sys");
    ratio1->Reset();
    ratio1->GetXaxis()->SetTitle(hmjNom->GetXaxis()->GetTitle());
    ratio1->Divide(hmjSys,hmjNom);
    SetRatioPlot(ratio1,kGreen+1,21);
    ratio1->GetXaxis()->SetRangeUser(Xmin,Xmax);
  }
  
  TCanvas *cs  = CreateCanvas("sys");
  TPad *p1     = CreateTopPad("sys",Htype);
  TPad *p2     = CreateBottomPad("sys",Htype);

  cs->cd();
  p1->Draw();
  p2->Draw();

  p1->cd();
  hmjNom->Draw("hist");
  hmjStat->SetLineColor(kRed);
  hmjStat->Draw("histsame");
  if(lfvType=="etau"){
    hmjSys->SetLineColor(kGreen+1);
    hmjSys->Draw("histsame");
  }
  gPad->RedrawAxis();

  TLegend *leg = CreateLegend();
  leg->AddEntry(hmjNom,"Nominal","l");
  leg->AddEntry(hmjStat,"k_{Multijet} Stat","l");
  if(lfvType=="etau")
    leg->AddEntry(hmjSys,"k_{Multijet} Sys","l");
  leg->AddEntry(ratio,"k_{Multijet} Stat / Nominal","lpe");
  if(lfvType=="etau")
    leg->AddEntry(ratio1,"k_{Multijet} Sys / Nominal","lpe");
  leg->Draw();
  
  DrawLabels(true);
  DrawChannel(lfvType,true);
  
  p2->cd();
  ratio->Draw("pE");
  if(lfvType=="etau")
    ratio1->Draw("pEsame");
  
  std::cout << " Multijet : Nom = " << hmjNom->Integral()
	    << " Stat = " << hmjStat->Integral();
  
  if(lfvType=="etau")
    std::cout << " Sys = " << hmjSys->Integral() << std::endl;
  else
    std::cout << "" << std::endl;
  
}

void CompareFakeCategories(std::string lfvType, bool useBjet,
			   bool isttCR, bool isRevDphi){

  SetATLASStyle();
  TH1::SetDefaultSumw2(kTRUE);

  std::string Dir = "";
  if(useBjet){ Dir += "Bjet/";   }
  else{        Dir += "NoBjet/"; }
  
  if(isttCR)   { Dir += "ttbarCR/"; }
  if(isRevDphi){ Dir += "revDphi/"; }

  TFile *Nom    = new TFile( (Dir+"Plots_Nominal_"+lfvType+"_OSSS_FFcat.root").c_str() );
  TFile *OSonly = new TFile( (Dir+"Plots_Nominal_"+lfvType+"_OS_FFcat.root").c_str()   );
  TFile *SSonly = new TFile( (Dir+"Plots_Nominal_"+lfvType+"_SS_FFcat.root").c_str()   );
  TFile *LFcat  = new TFile( (Dir+"Plots_Nominal_"+lfvType+"_OSSS_LFcat.root").c_str() );

  std::string name = "hmllCorr_qcd";
  TH1F *nom    = (TH1F*)Nom->Get(    name.c_str() );
  TH1F *osOnly = (TH1F*)OSonly->Get( name.c_str() );
  TH1F *ssOnly = (TH1F*)SSonly->Get( name.c_str() );
  TH1F *lfCat  = (TH1F*)LFcat->Get(  name.c_str() );

  nom->SetLineColor(kBlack);
  osOnly->SetLineColor(kRed);
  ssOnly->SetLineColor(kBlue);
  lfCat->SetLineColor(kGreen+2);

  std::cout << " Nom = " << nom->Integral() << " OSonly = "
	    << osOnly->Integral() << " SSonly = " << ssOnly->Integral()
	    << " LFcat = " << lfCat->Integral() << std::endl;


  nom->Scale( 1./nom->Integral() );
  osOnly->Scale( 1./osOnly->Integral() );
  ssOnly->Scale( 1./ssOnly->Integral() );
  lfCat->Scale( 1./lfCat->Integral() );
  
  TH1F *ratio1 = (TH1F*)nom->Clone("ratio");
  ratio1->Reset();
  TH1F *ratio2 = (TH1F*)nom->Clone("ratio");
  ratio2->Reset();
  TH1F *ratio3 = (TH1F*)nom->Clone("ratio");
  ratio3->Reset();
  ratio1->GetXaxis()->SetTitle(nom->GetXaxis()->GetTitle());
  ratio2->GetXaxis()->SetTitle(nom->GetXaxis()->GetTitle());
  ratio3->GetXaxis()->SetTitle(nom->GetXaxis()->GetTitle());
  
  TH1F *ratioLine = (TH1F*)ratio1->Clone("ratioLine");
  for (int k=-1; k<ratioLine->GetNbinsX()+1; k++){
    ratioLine->SetBinContent(k,1.);
  }
  ratioLine->GetYaxis()->SetTitle("Ratio");

  ratio1->Divide(osOnly,nom);
  ratio2->Divide(ssOnly,nom);
  ratio3->Divide(lfCat,nom);
  SetRatioPlot(ratio1,kRed);
  SetRatioPlot(ratio2,kBlue);
  SetRatioPlot(ratio3,kGreen+2);
  ratioLine->GetXaxis()->SetLabelSize(0.08);
  ratioLine->GetXaxis()->SetTitleOffset(1.20);
  ratioLine->GetXaxis()->SetTitleSize(0.10);
  ratioLine->GetYaxis()->SetLabelSize(0.07);
  ratioLine->GetYaxis()->SetTitleOffset(0.55);
  ratioLine->GetYaxis()->SetTitleSize(0.08);
  ratioLine->GetYaxis()->CenterTitle(kTRUE);
  ratioLine->GetYaxis()->SetNdivisions(507);
  ratioLine->GetYaxis()->SetRangeUser(0.1,1.9);
  ratioLine->GetXaxis()->SetMoreLogLabels(kTRUE);
  ratioLine->GetXaxis()->SetNoExponent(kTRUE);
  ratioLine->SetLineColor(2);
  ratioLine->SetLineStyle(2);

  /* Create Canvas and Pads*/
  TCanvas *c_charge = CreateCanvas("ChargeComp");
  TPad *p1_charge   = CreateTopPad("ChargeComp","mllCorr");
  TPad *p2_charge   = CreateBottomPad("ChargeComp","mllCorr");

  TCanvas *c_categ = CreateCanvas("CategoryComp");
  TPad *p1_categ   = CreateTopPad("CategoryComp","mllCorr");
  TPad *p2_categ   = CreateBottomPad("CategoryComp","mllCorr");

  /* Draw Charge Comp */
  c_charge->cd();
  p1_charge->Draw();
  p2_charge->Draw();

  p1_charge->cd();
  nom->GetYaxis()->SetTitle("Events");
  nom->GetXaxis()->SetRangeUser(130,5000);
  nom->GetYaxis()->SetRangeUser(0.00005,10);
  nom->Draw("hist");
  osOnly->Draw("histsame");
  ssOnly->Draw("histsame");

  TLegend *leg = CreateLegend();
  /* shapes */
  leg->AddEntry(nom,"Nominal (OS+SS FFcat)", "l");
  leg->AddEntry(osOnly,"OS Only FFcat", "l");
  leg->AddEntry(ssOnly,"SS Onlt FFcat", "l");
  /* ratios */
  leg->AddEntry(ratio1,"OS Only / Nominal","pel");
  leg->AddEntry(ratio2,"SS Only / Nominal","pel");
  leg->Draw();

  DrawLabels(true);
  DrawChannel(lfvType,true);
  
  p2_charge->cd();
  ratioLine->GetXaxis()->SetRangeUser(130,3000);
  ratioLine->Draw("hist");
  ratio1->Draw("pE0same");
  ratio2->Draw("pE0same");

  /* Draw category comp */
  c_categ->cd();
  p1_categ->Draw();
  p2_categ->Draw();
  
  p1_categ->cd();
  nom->GetYaxis()->SetTitle("Events");
  nom->GetXaxis()->SetRangeUser(130,3000);
  nom->GetYaxis()->SetRangeUser(0.00005,10);
  nom->Draw("hist");
  lfCat->Draw("histsame");

  TLegend *leg2 = CreateLegend();
  /* shapes */
  leg2->AddEntry(nom,"Nominal (OS+SS FFcat)", "l");
  leg2->AddEntry(lfCat,"OS+SS LFcat", "l");
  /* ratios */
  leg2->AddEntry(ratio3,"LFcat / Nominal","pel");
  leg2->Draw();

  DrawLabels(true);
  DrawChannel(lfvType,true);
  
  p2_categ->cd();
  ratioLine->GetXaxis()->SetRangeUser(130,3000);
  ratioLine->Draw("hist");
  ratio3->Draw("pE0same");
  
}

void CompareProngs(std::string lfvType, bool useBjet){

  SetATLASStyle();
  TH1::SetDefaultSumw2(kTRUE);

  std::string Dir = "";
  if(useBjet){ Dir += "Bjet/";   }
  else{        Dir += "NoBjet/"; }

  
  TFile *Nom    = new TFile( (Dir+"Plots_Nominal_"+lfvType+".root").c_str() );
  TFile *P1only = new TFile( (Dir+"Plots_Nominal_"+lfvType+"_1p.root").c_str()   );
  TFile *P3only = new TFile( (Dir+"Plots_Nominal_"+lfvType+"_3p.root").c_str()   );

  std::string name = "hmllCorr_qcd";
  TH1F *nom    = (TH1F*)Nom->Get(    name.c_str() );
  TH1F *p1Only = (TH1F*)P1only->Get( name.c_str() );
  TH1F *p3Only = (TH1F*)P3only->Get( name.c_str() );
  TH1F *merged = (TH1F*)p1Only->Clone( "merged" );
  merged->Add(p3Only);

  nom->SetLineColor(kBlack);
  nom->SetMarkerColor(kBlack);
  nom->SetMarkerSize(0);
  p1Only->SetLineColor(kGreen+2);
  p3Only->SetLineColor(kBlue);
  merged->SetLineColor(kRed);
  merged->SetMarkerColor(kRed);
  merged->SetMarkerSize(0);
  
  std::cout << " Nom = " << nom->Integral() << " p1only = "
	    << p1Only->Integral() << " p3only = " << p3Only->Integral()
	    << " p1+p3 = " << merged->Integral() << std::endl;


  TH1F *ratio = (TH1F*)nom->Clone("ratio");
  ratio->Reset();
  ratio->GetXaxis()->SetTitle(nom->GetXaxis()->GetTitle());
    
  TH1F *ratioLine = (TH1F*)ratio->Clone("ratioLine");
  for (int k=-1; k<ratioLine->GetNbinsX()+1; k++){
    ratioLine->SetBinContent(k,1.);
  }
  ratioLine->GetYaxis()->SetTitle("Ratio");

  ratio->Divide(nom,merged);
  SetRatioPlot(ratio,kBlack);
  ratioLine->GetXaxis()->SetLabelSize(0.08);
  ratioLine->GetXaxis()->SetTitleOffset(1.20);
  ratioLine->GetXaxis()->SetTitleSize(0.10);
  ratioLine->GetYaxis()->SetLabelSize(0.07);
  ratioLine->GetYaxis()->SetTitleOffset(0.55);
  ratioLine->GetYaxis()->SetTitleSize(0.08);
  ratioLine->GetYaxis()->CenterTitle(kTRUE);
  ratioLine->GetYaxis()->SetNdivisions(507);
  ratioLine->GetYaxis()->SetRangeUser(0.1,1.9);
  ratioLine->GetXaxis()->SetMoreLogLabels(kTRUE);
  ratioLine->GetXaxis()->SetNoExponent(kTRUE);
  ratioLine->SetLineColor(2);
  ratioLine->SetLineStyle(2);

  /* Create Canvas and Pads*/
  TCanvas *c = CreateCanvas("ProngsComp");
  TPad *p1   = CreateTopPad("ProngsComp","mllCorr");
  TPad *p2   = CreateBottomPad("ProngsComp","mllCorr");

  /* Draw Prings compareCharge Comp */
  c->cd();
  p1->Draw();
  p2->Draw();

  p1->cd();
  nom->GetYaxis()->SetTitle("Events");
  nom->GetXaxis()->SetRangeUser(130,3000);
  nom->GetYaxis()->SetRangeUser(0.00005,90000000);
  nom->Draw("pe");
  //p1Only->Draw("histsame");
  //p3Only->Draw("histsame");
  merged->Draw("pesame");

  TLegend *leg = CreateLegend();
  /* shapes */
  leg->AddEntry(nom,"Nominal ", "le");
  //leg->AddEntry(p1Only,"1p Only", "l");
  //leg->AddEntry(p3Only,"3p Only", "l");
  leg->AddEntry(merged,"1p + 3p", "le");
  /* ratios */
  leg->AddEntry(ratio,"Nominal / 1p + 3p ","pel");
  leg->Draw();

  DrawLabels(true);
  DrawChannel(lfvType,true);
  
  p2->cd();
  ratioLine->GetXaxis()->SetRangeUser(130,3000);
  ratioLine->Draw("hist");
  ratio->Draw("pE0same");

}

TH1F* GetMultijet(std::vector<TH1F*> vecH, std::string RegName){

  TH1F *mj  = (TH1F*)vecH.at(1)->Clone( ("mj_"+RegName).c_str() );
  mj->Reset();
  mj->Add( vecH.at(0)     );
  mj->Add( vecH.at(1), -1 );
  mj->Add( vecH.at(2), -1 );
  mj->Add( vecH.at(3), -1 );
  mj->Add( vecH.at(4), -1 );

  std::cout << " Multijet " << RegName << " ... " << std::endl;
  for(int b=1; b<mj->GetNbinsX()+1; b++){
    double c = mj->GetBinContent(b);
    double e = mj->GetBinError(b);
    //if(c<=0){
    //  c = (mj->GetBinContent(b-1)+mj->GetBinContent(b+1)) / 2.;
    //  mj->SetBinContent(b, c);
    //  mj->SetBinError(b, e);
    //}
    if(m_debug)
      std::cout << " Bin = " << b << " -> Content = " << c
		<< " Error = " << e << std::endl;
  }
  if(m_debug)
    std::cout << "" << std::endl;
  
  return mj;
  
}

void SetRatioPlot(TH1F *ratio, Int_t color, Int_t marker, bool isRatio){

  ratio->GetYaxis()->SetTitle("Ratio");
  ratio->GetXaxis()->SetTitleOffset(1.20);
  ratio->GetYaxis()->CenterTitle(kTRUE);
  ratio->GetYaxis()->SetNdivisions(507);
  ratio->GetXaxis()->SetMoreLogLabels(kTRUE);
  ratio->GetXaxis()->SetNoExponent(kTRUE);
  ratio->SetLineColor(color);
  ratio->SetMarkerColor(color);
  ratio->SetMarkerStyle(marker);
  if(isRatio){
    ratio->GetXaxis()->SetLabelSize(0.08);
    ratio->GetYaxis()->SetLabelSize(0.07);
    ratio->GetXaxis()->SetTitleSize(0.10);
    ratio->GetYaxis()->SetTitleSize(0.08);
    ratio->GetYaxis()->SetTitleOffset(0.55);
    ratio->SetMarkerSize(1.0);
  }
  else{
    ratio->GetXaxis()->SetLabelSize(0.04);
    ratio->GetYaxis()->SetLabelSize(0.04);
    ratio->GetXaxis()->SetTitleSize(0.05);
    ratio->GetYaxis()->SetTitleSize(0.05);
    ratio->GetYaxis()->SetTitleOffset(1.35);
    ratio->SetMarkerSize(1.2);
  }
  
}
