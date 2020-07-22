/* Program includes */
#include "DrawWjetsPlots.h"
#include "Utils.C"

int main( int argc, char* argv[] ) {

  int lfvType        = -1;
  std::string Htype  = "mllCorr";
  bool useBjet       = false;
  bool useGUI        = false;
  bool doShape       = false;
  bool doSys         = false;
  bool doMCcomp      = false;
  bool printHelp     = false;
  bool debug         = false;
  for(int i = 1; i < argc; ++i){
    if( !strcmp(argv[i],"--lfvType")         ){ lfvType   = std::stoi(argv[i+1]); }
    else if( !strcmp(argv[i],"--Htype")      ){ Htype     = argv[i+1]; }
    else if( !strcmp(argv[i],"--useBjet")    ){ useBjet   = true; }
    else if( !strcmp(argv[i],"--useGUI")     ){ useGUI    = true; }
    else if( !strcmp(argv[i],"--doSys")      ){ doSys     = true; }
    else if( !strcmp(argv[i],"--doShape")    ){ doShape   = true; }
    else if( !strcmp(argv[i],"--doMCcomp")   ){ doMCcomp  = true; }
    else if( !strcmp(argv[i],"--debug")      ){ debug     = true; }
    else if( !strcmp(argv[i],"--help")       ){ printHelp = true; }
    else{
      if(std::string(argv[i]).find("--")!=std::string::npos)
	std::cout << "WARNING:: Option " << argv[i] << " not recognized: "
		  << "skipping!" << std::endl;
    }
  }

  if(printHelp){
    std::cout << " DrawWjetsPlots: make W+jets related plots!"    << std::endl;
    std::cout << "               Options: "                       << std::endl;
    std::cout << "                --useBjet    [Enable b-jet veto:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --useGUI     [Enable GUI mode:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --Htype      [Choose distribution: "
	      << " default is 'mllCorr']"                         << std::endl;
    std::cout << "                --lfvType    [Choose lfv channel: "
	      << " options 1,2,3']"                               << std::endl;
    std::cout << "                --doShape    [Do Shape plot:"
      	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --doSys      [Do kMJ systematic:"
      	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --doMCcomp   [Do MC comparisons:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --debug      [Enable debug]"    << std::endl;
    std::cout << "                --help       [Print this help]" << std::endl;
    exit(0);
  }

  std::cout << "< DrawWjetsPlots() >:: Options set "         << std::endl;
  std::cout << "                useBjet    = " << useBjet    << std::endl;
  std::cout << "                lfvType    = " << lfvType    << std::endl;
  std::cout << "                Htype      = " << Htype      << std::endl;
  std::cout << "                doShape    = " << doShape    << std::endl;
  std::cout << "                doSys      = " << doSys      << std::endl;
  std::cout << "                doMCcomp   = " << doMCcomp   << std::endl;
  std::cout << "                useGUI     = " << useGUI     << std::endl;
  std::cout << "                debug      = " << debug      << std::endl;

  std::string chanName = "";
  if(lfvType==1)      { chanName="emu";   }
  else if(lfvType==2) { chanName="etau";  }
  else if(lfvType==3) { chanName="mutau"; }

  m_debug = debug;
  m_xMin=130;
  m_xMax=3000;
  if(lfvType==3) m_xMax=2700;
  
  TRint *myApp = new TRint("RootSession",&argc,argv,NULL,0);
  if(doShape)
    DrawShape(chanName,Htype,useBjet);
  else if(doSys)
    DeriveSys(chanName,Htype,useBjet);
  else if(doMCcomp)
    DrawMCcomp(chanName,Htype,useBjet);
  else{
    DrawShape(chanName,Htype,useBjet);
    DeriveSys(chanName,Htype,useBjet);
    DrawMCcomp(chanName,Htype,useBjet);
  }
								
  if(useGUI){
    std::cout << "< DrawWjetsPlots() >:: using Rint -> ROOT will remain "
	      << "opened ... " << std::endl;
    myApp->Run();
  }

  return 0;
  
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

void DrawShape(std::string lfvType, std::string Htype, bool useBjet){
  
  SetATLASStyle();
  TH1::SetDefaultSumw2(kTRUE);

  std::string Dir = "";
  if(useBjet){ Dir += "Bjet/";   }
  else{        Dir += "NoBjet/"; }

  Dir += "WjetNoTauId/";

  TFile *Nom = new TFile( (Dir+"Plots_Nominal_"+lfvType+".root").c_str()     );
  
  TH1F *nom = (TH1F*)Nom -> Get( ("h"+Htype+"_Wjets").c_str() );
  
  nom->SetLineColor(1);
  
  if(lfvType=="mutau"){
    for(int i=0; i<nom->GetNbinsX(); i++){
      double bin38 = nom->GetBinContent(38);
      double bin40 = nom->GetBinContent(40);
      nom->SetBinContent( 39, (bin38+bin40)/2. );
      nom->SetBinError( 39, nom->GetBinError(39) );
    }
  }
  
  std::cout << " Nom = " << nom->Integral() << std::endl;

  TCanvas *cs = CreateCanvas("Shape");
  cs->SetLogy(true);
  cs->SetLogx(true);
    
  nom->GetYaxis()->SetTitle("Events");
  nom->GetXaxis()->SetRangeUser(m_xMin,m_xMax);
  nom->GetYaxis()->SetRangeUser(0.005,500000);

  nom->Draw("hist");
  
  DrawLabels();
  DrawChannel(lfvType);

}

void DrawMCcomp(std::string lfvType, std::string Htype, bool useBjet){

  SetATLASStyle();
  TH1::SetDefaultSumw2(kTRUE);

  std::string Dir = "", mcDir = "";
  if(useBjet){ Dir += "Bjet/";   }
  else{        Dir += "NoBjet/"; }

  mcDir = Dir;
  Dir  += "WjetNoTauId/";
  
  TFile *Nom = new TFile( (Dir+"Plots_Nominal_"+lfvType+".root").c_str()     );
  TFile *MC  = new TFile( (mcDir+"Plots_Nominal_"+lfvType+"_WjetsMC.root").c_str() );

  TH1F *nom = (TH1F*)Nom -> Get( ("h"+Htype+"_Wjets").c_str() );
  TH1F *mc  = (TH1F*)MC  -> Get( ("h"+Htype+"_Wjets").c_str() );

  nom->SetLineColor(1);
  mc->SetLineColor(kRed);
  mc->SetLineStyle(9);
  
  if(lfvType=="mutau"){
    for(int i=0; i<nom->GetNbinsX(); i++){
      double bin38 = nom->GetBinContent(38);
      double bin40 = nom->GetBinContent(40);
      nom->SetBinContent( 39, (bin38+bin40)/2. );
      nom->SetBinError( 39, nom->GetBinError(39) );
    }
  }
  
  std::cout << " Nom = " << nom->Integral() << " MC = " << mc->Integral()
    	    << std::endl;

  TCanvas *cs = CreateCanvas("MCcomp");
  cs->SetLogy(true);
  cs->SetLogx(true);
    
  nom->GetYaxis()->SetTitle("Events");
  nom->GetXaxis()->SetRangeUser(m_xMin,m_xMax);
  nom->GetYaxis()->SetRangeUser(0.005,500000);

  nom->Draw("hist");
  mc->Draw("histsame");

  TLegend *leg = CreateLegend();
  leg->AddEntry(nom,"Nominal (BDT>0.4)", "l");
  leg->AddEntry(mc ,"MC with SR cuts", "l");
  leg->Draw();
    
  DrawLabels();
  DrawChannel(lfvType);
  
}

void DeriveSys(std::string lfvType, std::string Htype, bool useBjet){

  SetATLASStyle();
  TH1::SetDefaultSumw2(kTRUE);
  
  std::string Dir = "";
  if(useBjet){ Dir += "Bjet/";   }
  else{        Dir += "NoBjet/"; }

  Dir  += "WjetNoTauId/";
  
  TFile *Nom    = new TFile( (Dir+"Plots_Nominal_"+lfvType+".root").c_str()              );
  TFile *StatUp = new TFile( (Dir+"Plots_TauFake_StatUp_"+lfvType+".root").c_str()       );
  TFile *StatDw = new TFile( (Dir+"Plots_TauFake_StatDown_"+lfvType+".root").c_str()     );
  TFile *BdtUp  = new TFile( (Dir+"Plots_TauFake_BDT_SysUp_"+lfvType+".root").c_str()    );
  TFile *BdtDw  = new TFile( (Dir+"Plots_TauFake_BDT_SysDown_"+lfvType+".root").c_str()  );
  TFile *CR     = new TFile( (Dir+"Plots_TauFake_CR_Sys_"+lfvType+".root").c_str()       );
  TFile *NoBDT  = new TFile( (Dir+"Plots_TauFake_NoBDT_"+lfvType+".root").c_str()        );
  TFile *CompUp = new TFile( (Dir+"Plots_TauFake_Comp_SysUp_"+lfvType+".root").c_str()   );
  TFile *CompDw = new TFile( (Dir+"Plots_TauFake_Comp_SysDown_"+lfvType+".root").c_str() );
  
  TH1F *nom    = (TH1F*)Nom    -> Get( "hmllCorr_Wjets" );
  TH1F *bdtUp  = (TH1F*)BdtUp  -> Get( "hmllCorr_Wjets" );
  TH1F *bdtDw  = (TH1F*)BdtDw  -> Get( "hmllCorr_Wjets" );
  TH1F *statUp = (TH1F*)StatUp -> Get( "hmllCorr_Wjets" );
  TH1F *statDw = (TH1F*)StatDw -> Get( "hmllCorr_Wjets" );
  TH1F *cr     = (TH1F*)CR     -> Get( "hmllCorr_Wjets" );
  TH1F *noBDT  = (TH1F*)NoBDT  -> Get( "hmllCorr_Wjets" );
  TH1F *compUp = (TH1F*)CompUp -> Get( "hmllCorr_Wjets" );
  TH1F *compDw = (TH1F*)CompDw -> Get( "hmllCorr_Wjets" );
  
  nom->SetLineColor(1);
  bdtUp->SetLineColor(kRed);
  bdtDw->SetLineColor(kBlue);
  statUp->SetLineColor(kMagenta);
  statDw->SetLineColor(kOrange);
  cr->SetLineColor(kGreen+2);
  noBDT->SetLineColor(kRed);
  compUp->SetLineColor(kYellow-5);
  compDw->SetLineColor(kCyan+1);
  
  if(lfvType=="mutau"){
    
    std::vector<TH1F*> plots;
    plots.push_back( nom    );  plots.push_back( cr     );
    plots.push_back( bdtUp  );  plots.push_back( bdtDw  );
    plots.push_back( statUp );  plots.push_back( statDw );
    plots.push_back( noBDT  );  plots.push_back( compUp );
    plots.push_back( compDw );

    for(int i=0; i<(int)plots.size(); i++){
      double bin38 = plots.at(i)->GetBinContent(38);
      double bin40 = plots.at(i)->GetBinContent(40);
      plots.at(i)->SetBinContent( 39, (bin38+bin40)/2. );
      plots.at(i)->SetBinError( 39, plots.at(i)->GetBinError(39) );
    }
  }
  
  std::cout << " Nom = "    << nom->Integral()
	    << " BdtUp = "  << bdtUp->Integral()
	    << " BdtDw = "  << bdtDw->Integral()
	    << " StatUp = " << statUp->Integral()
	    << " StatDw = " << statDw->Integral()
	    << " CR = "     << cr->Integral()
	    << " CompUp = " << compUp->Integral()
	    << " CompDw = " << compDw->Integral()
	    << std::endl;
  
  TH1F *ratio1 = (TH1F*)nom->Clone("ratio1");
  ratio1->Reset();
  TH1F *ratio2 = (TH1F*)nom->Clone("ratio2");
  ratio2->Reset();
  TH1F *ratio3 = (TH1F*)nom->Clone("ratio3");
  ratio3->Reset();
  TH1F *ratio4 = (TH1F*)nom->Clone("ratio4");
  ratio4->Reset();
  TH1F *ratio5 = (TH1F*)nom->Clone("ratio5");
  ratio5->Reset();
  TH1F *ratio6 = (TH1F*)nom->Clone("ratio6");
  ratio6->Reset();
  TH1F *ratio7 = (TH1F*)nom->Clone("ratio7");
  ratio7->Reset();
  TH1F *ratio8 = (TH1F*)nom->Clone("ratio8");
  ratio8->Reset();
  ratio1->GetXaxis()->SetTitle(nom->GetXaxis()->GetTitle());
  ratio2->GetXaxis()->SetTitle(nom->GetXaxis()->GetTitle());
  ratio3->GetXaxis()->SetTitle(nom->GetXaxis()->GetTitle());
  ratio4->GetXaxis()->SetTitle(nom->GetXaxis()->GetTitle());
  ratio5->GetXaxis()->SetTitle(nom->GetXaxis()->GetTitle());
  ratio6->GetXaxis()->SetTitle(nom->GetXaxis()->GetTitle());
  ratio7->GetXaxis()->SetTitle(nom->GetXaxis()->GetTitle());
  ratio8->GetXaxis()->SetTitle(nom->GetXaxis()->GetTitle());
  
  TH1F *ratioLine = (TH1F*)ratio1->Clone("ratioLine");
  for (int k=-1; k<ratioLine->GetNbinsX()+1; k++){
    ratioLine->SetBinContent(k,1.);
  }
  ratioLine->GetYaxis()->SetTitle("Ratio");

  ratio1->Divide(bdtUp,nom);
  ratio2->Divide(bdtDw,nom);
  ratio3->Divide(statUp,nom);
  ratio4->Divide(statDw,nom);
  ratio5->Divide(cr,nom);
  ratio6->Divide(noBDT,nom);
  ratio7->Divide(compUp,nom);
  ratio8->Divide(compDw,nom);
  SetRatio(ratio1,kRed);
  SetRatio(ratio2,kBlue);
  SetRatio(ratio3,kMagenta);
  SetRatio(ratio4,kOrange);
  SetRatio(ratio5,kGreen+2);
  SetRatio(ratio6,kGreen+2);
  SetRatio(ratio7,kYellow-5);
  SetRatio(ratio8,kCyan+1);
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

  
  /* Create Canvas and Pads */
  TCanvas *c_UncSys = CreateCanvas("UncSys");
  TPad* p1_UncSys   = CreateTopPad("UncSys",Htype);
  TPad* p2_UncSys   = CreateBottomPad("UncSys",Htype);

  TCanvas *c_UncStat = CreateCanvas("UncStat");
  TPad* p1_UncStat   = CreateTopPad("UncStat",Htype);
  TPad* p2_UncStat   = CreateBottomPad("UncStat",Htype);

  TCanvas *c_NoBdt = CreateCanvas("NoBdt");
  TPad* p1_NoBdt   = CreateTopPad("NoBdt",Htype);
  TPad* p2_NoBdt   = CreateBottomPad("NoBdt",Htype);

  TCanvas *c_CpBD  = CreateCanvas("CompBDT");
  TPad* p1_CpBD    = CreateTopPad("CompBDT",Htype);
  TPad* p2_CpBD    = CreateBottomPad("CompBDT",Htype);

  TCanvas *c_Comp  = CreateCanvas("Comp");
  TPad* p1_Comp    = CreateTopPad("Comp",Htype);
  TPad* p2_Comp    = CreateBottomPad("Comp",Htype);

  /* Draw Sys Unc */
  c_UncSys->cd();
  p1_UncSys->Draw();
  p2_UncSys->Draw();
  
  p1_UncSys->cd();
  nom->GetYaxis()->SetTitle("Events");
  nom->GetXaxis()->SetRangeUser(m_xMin,m_xMax);
  nom->GetYaxis()->SetRangeUser(0.005,500000);
  nom->Draw("hist");
  bdtUp->Draw("histsame");
  bdtDw->Draw("histsame");
  cr->Draw("histsame");
  
  TLegend *leg1 = CreateLegend();
  /* shapes */
  leg1->AddEntry(nom,"Nominal (BDT>0.4)", "l");
  leg1->AddEntry(bdtUp,"BDT_SysUp (BDT>0.5)", "l");
  leg1->AddEntry(bdtDw,"BDT_SysDown (BDT>0.3)", "l");
  leg1->AddEntry(cr,"Sys CR (BDT>0.40 & No m_{T} cut)", "l");
  /* ratios */
  leg1->AddEntry(ratio1,"BDT_SysUp / Nominal","pel");
  leg1->AddEntry(ratio2,"BDT_SysDown / Nominal","pel");
  leg1->AddEntry(ratio5,"Sys CR / Nominal","pel");
  leg1->Draw();

  DrawLabels(true);
  DrawChannel(lfvType,true);
  
  p2_UncSys->cd();
  ratioLine->GetXaxis()->SetRangeUser(m_xMin,m_xMax);
  ratioLine->Draw("hist");
  ratio1->Draw("pE0same");
  ratio2->Draw("pE0same");
  ratio5->Draw("pE0same");


  /* Draw Stat Unc */
  c_UncStat->cd();
  p1_UncStat->Draw();
  p2_UncStat->Draw();

  p1_UncStat->cd();
  nom->GetYaxis()->SetTitle("Events");
  nom->GetXaxis()->SetRangeUser(m_xMin,m_xMax);
  nom->GetYaxis()->SetRangeUser(0.005,500000);
  nom->GetXaxis()->SetMoreLogLabels(kTRUE);
  nom->GetXaxis()->SetNoExponent(kTRUE);
  nom->Draw("hist");
  statUp->Draw("histsame");
  statDw->Draw("histsame");
  
  TLegend *leg2 = CreateLegend();
  /* shapes */
  leg2->AddEntry(nom,"Nominal (BDT>0.4)", "l");
  leg2->AddEntry(StatUp,"StatUp (BDT>0.4)", "l");
  leg2->AddEntry(StatDw,"StatDown (BDT>0.4)", "l");
  /* ratios */
  leg2->AddEntry(ratio3,"StatUp / Nominal","pel");
  leg2->AddEntry(ratio4,"StatDown / Nominal","pel");
  leg2->Draw();

  DrawLabels(true);
  DrawChannel(lfvType,true);
  
  p2_UncStat->cd();
  ratioLine->GetXaxis()->SetRangeUser(m_xMin,m_xMax);
  ratioLine->Draw("hist");
  ratio3->Draw("pE0same");
  ratio4->Draw("pE0same");

  /* Draw No Bdt */
  c_NoBdt->cd();
  p1_NoBdt->Draw();
  p2_NoBdt->Draw();

  p1_NoBdt->cd();
  nom->GetYaxis()->SetTitle("Events");
  nom->GetXaxis()->SetRangeUser(m_xMin,m_xMax);
  nom->GetYaxis()->SetRangeUser(0.005,500000);
  nom->GetXaxis()->SetMoreLogLabels(kTRUE);
  nom->GetXaxis()->SetNoExponent(kTRUE);
  nom->Draw("hist");
  noBDT->Draw("histsame");
  
  TLegend *leg3 = CreateLegend();
  /* shapes */
  leg3->AddEntry(nom,"Nominal (BDT>0.4)", "l");
  leg3->AddEntry(noBDT,"No BDT cut", "l");
  /* ratios */
  leg3->AddEntry(ratio6,"No BDT / Nominal","pel");
  leg3->Draw();

  DrawLabels(true);
  DrawChannel(lfvType,true);
  
  p2_NoBdt->cd();
  ratioLine->GetXaxis()->SetRangeUser(m_xMin,m_xMax);
  ratioLine->Draw("hist");
  ratio6->Draw("pE0same");

  
  /* Draw Comp vs BDT Sys Unc */
  c_CpBD->cd();
  p1_CpBD->Draw();
  p2_CpBD->Draw();
  
  p1_CpBD->cd();
  nom->GetYaxis()->SetTitle("Events");
  nom->GetXaxis()->SetRangeUser(m_xMin,m_xMax);
  nom->GetYaxis()->SetRangeUser(0.005,500000);
  nom->Draw("hist");
  bdtUp->Draw("histsame");
  bdtDw->Draw("histsame");
  compUp->Draw("histsame");
  compDw->Draw("histsame");
  
  TLegend *leg4 = CreateLegend();
  /* shapes */
  leg4->AddEntry(nom,"Nominal (BDT>0.4)", "l");
  leg4->AddEntry(bdtUp,"BDT_SysUp (BDT>0.5)", "l");
  leg4->AddEntry(bdtDw,"BDT_SysDown (BDT>0.3)", "l");
  leg4->AddEntry(compUp,"Comp_SysUp", "l");
  leg4->AddEntry(compDw,"Comp_SysDown", "l");
  /* ratios */
  leg4->AddEntry(ratio1,"BDT_SysUp / Nominal","pel");
  leg4->AddEntry(ratio2,"BDT_SysDown / Nominal","pel");
  leg4->AddEntry(ratio7,"Comp_SysUp / Nominal","pel");
  leg4->AddEntry(ratio8,"Comp_SysDown / Nominal","pel");
  leg4->Draw();

  DrawLabels(true);
  DrawChannel(lfvType,true);
  
  p2_CpBD->cd();
  ratioLine->GetXaxis()->SetRangeUser(m_xMin,m_xMax);
  ratioLine->Draw("hist");
  ratio1->Draw("pE0same");
  ratio2->Draw("pE0same");
  ratio7->Draw("pE0same");
  ratio8->Draw("pE0same");

  
  /* Draw Comp Sys Unc */
  c_Comp->cd();
  p1_Comp->Draw();
  p2_Comp->Draw();
  
  p1_Comp->cd();
  nom->GetYaxis()->SetTitle("Events");
  nom->GetXaxis()->SetRangeUser(m_xMin,m_xMax);
  nom->GetYaxis()->SetRangeUser(0.005,500000);
  nom->Draw("hist");
  compUp->Draw("histsame");
  compDw->Draw("histsame");
  
  TLegend *leg5 = CreateLegend();
  /* shapes */
  leg5->AddEntry(nom,"Nominal (BDT>0.4)", "l");
  leg5->AddEntry(compUp,"Comp_SysUp", "l");
  leg5->AddEntry(compDw,"Comp_SysDown", "l");
  /* ratios */
  leg5->AddEntry(ratio7,"Comp_SysUp / Nominal","pel");
  leg5->AddEntry(ratio8,"Comp_SysDown / Nominal","pel");
  leg5->Draw();

  DrawLabels(true);
  DrawChannel(lfvType,true);
  
  p2_Comp->cd();
  ratioLine->GetXaxis()->SetRangeUser(m_xMin,m_xMax);
  ratioLine->Draw("hist");
  ratio7->Draw("pE0same");
  ratio8->Draw("pE0same");
  
}
