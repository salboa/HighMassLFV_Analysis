/* program includes */
#include "DerivePtRw.h"
#include "Utils.C"

int main( int argc, char* argv[] ) {

  int lfvType    = -1;
  bool useBjet   = false;
  bool useRwted  = false;
  bool useSignal = false;
  bool useGUI    = false;
  bool isBlind   = false;
  bool isttCR    = false;
  bool applyWgt  = false;
  bool useSherpa = false;
  bool doCompare = false;
  bool printHelp = false;
  bool debug     = false;
  bool verbose   = false;
  for(int i = 1; i < argc; ++i){
    if( !strcmp(argv[i],"--lfvType")         ){ lfvType   = std::stoi(argv[i+1]); }
    else if( !strcmp(argv[i],"--useBjet")    ){ useBjet    = true; }
    else if( !strcmp(argv[i],"--useRwted")   ){ useRwted   = true; }
    else if( !strcmp(argv[i],"--useGUI")     ){ useGUI     = true; }
    else if( !strcmp(argv[i],"--useSignal")  ){ useSignal  = true; }
    else if( !strcmp(argv[i],"--doCompare")  ){ doCompare  = true; }
    else if( !strcmp(argv[i],"--isBlind")    ){ isBlind    = true; }
    else if( !strcmp(argv[i],"--isttCR")     ){ isttCR     = true; }
    else if( !strcmp(argv[i],"--applyWgt")   ){ applyWgt   = true; }
    else if( !strcmp(argv[i],"--useSherpa")  ){ useSherpa  = true; }
    else if( !strcmp(argv[i],"--debug")      ){ debug      = true; }
    else if( !strcmp(argv[i],"--verbose")    ){ verbose    = true; }
    else if( !strcmp(argv[i],"--help")       ){ printHelp  = true; }
    else{
      if(std::string(argv[i]).find("--")!=std::string::npos)
	std::cout << "WARNING:: Option " << argv[i] << " not recognized: "
		  << "skipping!" << std::endl;
    }
  }

  if(printHelp){
    std::cout << " DerivePtRw: derive pT reweighting weights!"    << std::endl;
    std::cout << "               Options: "                       << std::endl;
    std::cout << "                --useBjet    [Enable b-jet veto:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --useRwted   [Enable using reweighted file:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --useSignal  [Enable drawing signals: "
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --useGUI     [Enable GUI mode:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --lfvType    [Choose lfv channel: "
	      << " options 1,2,3']"                               << std::endl;
    std::cout << "                --doCompare  [Enable PtRw vs Nom: "
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --isBlind    [Enable blind mode:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --isttCR     [Enable ttbar CR:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --useSherpa  [Enable using Sherpa ttbar:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --applyWgt   [Enable weights:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --debug      [Enable debug]"    << std::endl;
    std::cout << "                --verbose    [Enable verbose]"  << std::endl;
    std::cout << "                --help       [Print this help]" << std::endl;
    exit(0);
  }

  std::cout << "< DerivePtRw() >:: Options set "             << std::endl;
  std::cout << "                useBjet    = " << useBjet    << std::endl;
  std::cout << "                useRwted   = " << useRwted   << std::endl;
  std::cout << "                lfvType    = " << lfvType    << std::endl;
  std::cout << "                useSignal  = " << useSignal  << std::endl;
  std::cout << "                useGUI     = " << useGUI     << std::endl;
  std::cout << "                doCompare  = " << doCompare  << std::endl;
  std::cout << "                isBlind    = " << isBlind    << std::endl;
  std::cout << "                isttCR     = " << isttCR     << std::endl;
  std::cout << "                useSherpa  = " << useSherpa  << std::endl;
  std::cout << "                applyWgt   = " << applyWgt   << std::endl;
  std::cout << "                debug      = " << debug      << std::endl;
  std::cout << "                verbsoe    = " << verbose    << std::endl;

  std::string chanName = "";
  if(lfvType==1)      { chanName="emu";   }
  else if(lfvType==2) { chanName="etau";  }
  else if(lfvType==3) { chanName="mutau"; }

  m_debug   = debug;
  m_verbose = verbose;

  TRint *myApp = new TRint("RootSession",&argc,argv,NULL,0);
  if(doCompare)
    CompareMass(chanName,useBjet);
  else
    DerivePtRw(lfvType,useBjet,isBlind,isttCR,useSherpa,
	       useRwted,useSignal,applyWgt);

  if(useGUI){
    std::cout << "< DerivePtRw() >:: using Rint -> ROOT will remain "
	      << "opened ... " << std::endl;
    myApp->Run();
  }
  
  return 0;
  
}

void DerivePtRw(int lfvType, bool useBjet, bool isBlind, bool isttCR,
		bool useSherpa, bool useRwted, bool useSignal, bool applyWgt){

  SetATLASStyle();

  std::string chanName = "";
  if(lfvType==1)      { chanName="emu";   }
  else if(lfvType==2) { chanName="etau";  }
  else if(lfvType==3) { chanName="mutau"; }
  
  std::string Dir = "";
  if(useBjet){ Dir += "Bjet/";   }
  else{        Dir += "NoBjet/"; }

  if(isttCR){
    Dir += "ttbarCR";
    if(useSherpa) Dir += "_Sherpa";
    Dir += "/";
  }

  std::string fName = Dir+"Plots_Nominal_"+chanName;
  if(isBlind) fName += "_Blind";
  TFile *In = new TFile( (fName+".root").c_str() );
  TFile *In2 = NULL, *Sig=NULL;
  TFile *Bd = new TFile( (Dir+"SystematicsBands_"+chanName+".root").c_str() );
  if(useRwted)  In2 = new TFile( (fName+"_PtRw.root").c_str()    );
  if(useSignal) Sig = new TFile( (fName+"_Signals.root").c_str() );
  
  TH1F *Data = (TH1F*)In->Get( "hptllCorr_data"     );
  TH1F *Db   = (TH1F*)In->Get( "hptllCorr_DiBoson"  );
  TH1F *Dy   = (TH1F*)In->Get( "hptllCorr_DY"       );
  TH1F *Mjet = (TH1F*)In->Get( "hptllCorr_Multijet" );
  TH1F *Top = NULL, *Zprime = NULL, *RPV = NULL, *QBH = NULL;
  if(useRwted) Top = (TH1F*)In2->Get( "hptllCorr_Top" );
  else         Top = (TH1F*)In ->Get( "hptllCorr_Top" );
  if(useSignal){
    Zprime = (TH1F*)Sig->Get( "hptllCorr_Zprime1500" );
    QBH    = (TH1F*)Sig->Get( "hptllCorr_QBH1500_n1" );
    RPV    = (TH1F*)Sig->Get( "hptllCorr_SVT1500"    );
  }
  if(applyWgt){
    if(lfvType==1){
      //if(useBjet){
      //  double ct  = Top->GetBinContent(5);
      //  double err = Top->GetBinError(5);
      //  //Top->SetBinContent(5,ct*1.3);
      //  //Top->SetBinError(5,err);
      //}
      //else{
      double ct  = Top->GetBinContent(5);
      double err = Top->GetBinError(5);
      Top->SetBinContent(5,ct*1.35);
      Top->SetBinError(5,err);
      //}
    }
    else if(lfvType==2){
      Top->SetBinContent(2,Top->GetBinContent(2)*0.59);
      Top->SetBinContent(3,Top->GetBinContent(3)*0.56);
      Top->SetBinContent(4,Top->GetBinContent(4)*0.61);
      Top->SetBinContent(6,Top->GetBinContent(6)*0.69);
      Top->SetBinContent(7,Top->GetBinContent(7)*0.07);
    }
    else if(lfvType==3){
      Top->SetBinContent(7,Top->GetBinContent(7)*1.75);
    }
  }
  
  TH1F *BkgTot = (TH1F*)Top->Clone ( "hptllCorr_BkgTot"   );
  BkgTot->Add(Dy);
  BkgTot->Add(Db);
  BkgTot->Add(Mjet);
  TH1F *dummy  = (TH1F*)BkgTot->Clone( "dummy" );
  dummy->Reset();
  TH1F *ratio  = (TH1F*)BkgTot->Clone( "ratio" );
  ratio->Reset();

  
  TGraphAsymmErrors *Band = (TGraphAsymmErrors*)Bd->Get( "hptllCorr_SystBand" );
  

  Double_t Ymin = 0.005, Ymax = 10000000;
  if(lfvType==1)
    dummy->GetYaxis()->SetRangeUser(Ymin,Ymax);
  else
    dummy->GetYaxis()->SetRangeUser(Ymin,90000000);
  dummy->GetXaxis()->SetRangeUser(0.,900);
  dummy->GetYaxis()->SetTitleSize(0.06);
  dummy->GetYaxis()->SetLabelSize(0.05);
  dummy->GetYaxis()->SetTitleOffset(1.00);
  dummy->GetYaxis()->SetTitle("Events");

  Dy->SetFillColor(kAzure-9);
  Mjet->SetFillColor(kYellow-9);
  Db->SetFillColor(kOrange);
  Top->SetFillColor(kRed+1);
  
  TCanvas *c = CreateCanvas("ptll");
  TPad* p1   = CreateTopPad("ptrw","ptll");
  TPad* p2   = CreateBottomPad("ptrw","ptll");

  THStack *hs = new THStack("hs","");
  if(lfvType==1){
    hs->Add( Dy   ); //DY
    hs->Add( Mjet ); //QCD
    hs->Add( Db   ); //Db
    hs->Add( Top  ); //Top
  }
  else{
    hs->Add( Db   ); //Db
    hs->Add( Dy   ); //DY
    if(isttCR){
      hs->Add( Mjet ); //QCD
      hs->Add( Top  ); //Top
    }
    else{
      hs->Add( Top  ); //Top
      hs->Add( Mjet ); //QCD
    }
  }

  c->cd();
  p1->Draw();
  p2->Draw();
  
  p1->cd();
  p1->SetLogy();
  
  dummy->Draw();
  hs->Draw("HISTsame");
  if(useSignal){
    Zprime->SetLineColor(kGreen);
    Zprime->SetLineStyle(1);
    QBH->SetLineColor(kBlue);
    QBH->SetLineStyle(7);
    RPV->SetLineColor(kMagenta);
    RPV->SetLineStyle(6);
    Zprime->Draw("histsame");
    QBH->Draw("histsame");
    RPV->Draw("histsame");
  }
  Data->Draw("pEsame");
  gPad->RedrawAxis();

  TLegend *leg = NULL;
  if(useSignal) leg = new TLegend(0.59,0.49,0.99,0.91);
  else          leg = new TLegend(0.59,0.60,0.99,0.91);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->AddEntry(Data,"Data","pE");
  if(lfvType==1){
    leg->AddEntry(Top,"Top Quarks","f");
    leg->AddEntry(Db,"Diboson","f");
    leg->AddEntry(Mjet,"Multi-Jet & W+jets","f");
    leg->AddEntry(Dy,"Drell-Yan","f");
  }
  else{
    leg->AddEntry(Mjet,"Multi-Jet & W+jets","f");
    leg->AddEntry(Top,"Top Quarks","f");
    leg->AddEntry(Dy,"Drell-Yan","f");
    leg->AddEntry(Db,"Diboson","f");
  }
  if(useSignal){
    std::string mass = "1.5 TeV";
    leg->AddEntry(Zprime,("Z' "+mass).c_str(), "l");
    leg->AddEntry(RPV,("RPV #tilde{#nu}_{#tau} "+mass).c_str(), "l");
    leg->AddEntry(QBH,("QBH RS "+mass).c_str(), "l");
  }
  leg->AddEntry(Band,"Uncertainty","f");
  leg->Draw();
  
  DrawLabels(true);
  DrawChannel(chanName,true,useBjet);
  
  p2->cd();
  ratio->Divide(Data,BkgTot);
  ratio->SetMarkerSize(0.9);
  ratio->SetLineStyle(1);
  ratio->SetLineWidth(1);
  ratio->SetLineColor(1);
  ratio->SetMarkerColor(1);
  ratio->GetXaxis()->SetLabelSize(0.08);
  ratio->GetXaxis()->SetTitleOffset(1.20);
  ratio->GetXaxis()->SetTitleSize(0.12);
  ratio->GetYaxis()->SetTitle("Data/SM Bkg");
  ratio->GetYaxis()->SetLabelSize(0.09);
  ratio->GetYaxis()->SetTitleOffset(0.55);
  ratio->GetYaxis()->SetTitleSize(0.10);
  ratio->GetYaxis()->CenterTitle(kTRUE);
  ratio->GetYaxis()->SetNdivisions(507);
  ratio->GetXaxis()->SetLabelSize(0.09);
  ratio->GetXaxis()->SetRangeUser(0.,900);
  ratio->GetYaxis()->SetRangeUser(0.1,1.9);

  Band->SetFillColor(kGray);
  Band->SetFillStyle(1111);

  TLine* ratioLine = new TLine(0.,1.,1000.,1.);
  ratioLine->SetLineColor(kRed);
  ratioLine->SetLineStyle(1);
  ratioLine->SetLineWidth(2);

  ratio->Draw("pE");
  Band->Draw("same2");
  ratioLine->Draw("same");
  ratio->Draw("pEsame");
  gPad->RedrawAxis();
  
  Int_t Nbins = Data->GetNbinsX();
  for(Int_t b=1; b<Nbins+1; b++){
    m_data.push_back( Data->GetBinContent(b) );
    m_top.push_back(  Top->GetBinContent(b)  );
    m_dy.push_back(   Dy->GetBinContent(b)   );
    m_db.push_back(   Db->GetBinContent(b)   );
    m_mjet.push_back( Mjet->GetBinContent(b) );
    m_edge.push_back( Data->GetBinLowEdge(b) );
    if(b==Nbins)
      m_edge.push_back( Data->GetBinLowEdge(b+1) );
  }

  if(m_verbose)
    std::cout << " Nbins = " << Nbins << std::endl;
  
  for(uint b=0; b<m_data.size(); b++){

    if(m_data.at(b)==0) continue;

    double NonTop = m_dy.at(b)+ m_db.at(b)+m_mjet.at(b);
    
    std::cout.width(5);  std::cout << " Bin = ";
    std::cout.width(3);  std::cout << std::left << b;
    std::cout.width(8);  std::cout << " Range = ";
    std::cout.width(4);  std::cout << m_edge.at(b) << "- ";
    std::cout.width(4);  std::cout << m_edge.at(b+1);
    std::cout.width(8);  std::cout << " Data = ";
    std::cout.width(12); std::cout << std::left << m_data.at(b);
    std::cout.width(8);  std::cout << " Top  = ";
    std::cout.width(12); std::cout << std::left << m_top.at(b);
    if(m_verbose){
      std::cout.width(8);  std::cout << " DY   = ";
      std::cout.width(12); std::cout << std::left << m_dy.at(b);
      std::cout.width(8);  std::cout << " Dib  = ";
      std::cout.width(12); std::cout << std::left << m_db.at(b);
      std::cout.width(8);  std::cout << " Mjet = ";
      std::cout.width(12); std::cout << std::left << m_mjet.at(b);
    }
    std::cout.width(8);  std::cout << " !Top = ";
    std::cout.width(12); std::cout << std::left << NonTop;
    std::cout.width(8);  std::cout << " wgt  = ";
    std::cout.width(12); std::cout << (m_data.at(b)-NonTop)/m_top.at(b);
    std::cout << std::endl;
  }
  
}

void CompareMass(std::string lfvType, bool useBjet){

  SetATLASStyle();
  TH1::SetDefaultSumw2(kTRUE);
  
  std::string Dir = "";
  if(useBjet){ Dir += "Bjet/";   }
  else{        Dir += "NoBjet/"; }

  TFile *Nom  = new TFile( (Dir+"Plots_Nominal_"+lfvType+".root").c_str()      );
  TFile *PtRw = new TFile( (Dir+"Plots_PtRw_Sys_"+lfvType+".root").c_str() );

  TH1F *nom  = (TH1F*)Nom  -> Get( "hmllCorr_BkgTot" );
  TH1F *ptrw = (TH1F*)PtRw -> Get( "hmllCorr_BkgTot" );

  nom  -> SetLineColor( kBlack );
  ptrw -> SetLineColor( kRed   );

  std::cout << " Nom = " << nom->Integral() << " PtRw = " << ptrw->Integral()
	    << std::endl;

  TH1F *ratio = (TH1F*)nom->Clone("ratio");
  ratio->Reset();
  ratio->GetXaxis()->SetTitle(nom->GetXaxis()->GetTitle());

  TH1F *ratioLine = (TH1F*)ratio->Clone("ratioLine");
  for (int k=-1; k<ratioLine->GetNbinsX()+1; k++){
    ratioLine->SetBinContent(k,1.);
  }
  ratioLine->GetYaxis()->SetTitle("Ratio");

  ratio->Divide(ptrw,nom);
  SetRatio(ratio,kBlack);
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

  Double_t Xmin = 130., Xmax = 2600;

  TCanvas *cs = CreateCanvas("mll");
  TPad* p1    = CreateTopPad("ptrw","mll");
  TPad* p2    = CreateBottomPad("ptrw","mll");

  cs->cd();
  p1->Draw();
  p2->Draw();
    
  p1->cd();
  nom->GetYaxis()->SetTitle("Events");
  nom->GetXaxis()->SetRangeUser(Xmin,Xmax);
  nom->GetYaxis()->SetRangeUser(0.005,500000);
  
  nom->Draw("hist");
  ptrw->Draw("histsame");

  TLegend *leg = new TLegend(0.57,0.63,0.92,0.89);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  /* shapes */
  leg->AddEntry(nom,"Nominal", "l");
  leg->AddEntry(ptrw,"After pTrw", "l");
  /* ratios */
  leg->AddEntry(ratio,"pTrw / Nominal","pel");
  leg->Draw();

  DrawLabels(true);
  DrawChannel(lfvType,true,useBjet);
  
  p2->cd();
  p2->SetGridy();
  p2->SetLogx(true);

  ratioLine->GetXaxis()->SetRangeUser(Xmin,Xmax);
  ratioLine->GetYaxis()->SetRangeUser(0.77,1.23);
  ratioLine->Draw("hist");
  ratio->Draw("pE0same");
  
}

void SetRatio(TH1F* ratio, int color){

  ratio->GetYaxis()->SetTitle("Ratio");
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
  ratio->SetLineColor(color);
  ratio->SetMarkerColor(color);
  
}
