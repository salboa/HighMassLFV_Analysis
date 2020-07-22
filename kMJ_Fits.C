/* program includes */
#include "kMJ_Fits.h"
#include "Utils.C"

int main( int argc, char* argv[] ) {

  int lfvType        = -1;
  bool debug         = false;
  bool useBjet       = false;
  bool useGUI        = false;
  bool printHelp     = false;
  for(int i = 1; i < argc; ++i){
    if( !strcmp(argv[i],"--lfvType")         ){ lfvType   = std::stoi(argv[i+1]); }
    else if( !strcmp(argv[i],"--useBjet")    ){ useBjet    = true; }
    else if( !strcmp(argv[i],"--useGUI")     ){ useGUI     = true; }
    else if( !strcmp(argv[i],"--debug")      ){ debug      = true; }
    else if( !strcmp(argv[i],"--help")       ){ printHelp  = true; }
    else{
      if(std::string(argv[i]).find("--")!=std::string::npos)
	std::cout << "WARNING:: Option " << argv[i] << " not recognized: "
		  << "skipping!" << std::endl;
    }
  }
  
  if(printHelp){
    std::cout << " kMJ_Fits: draw k_MJ fit functions!"            << std::endl;
    std::cout << "               Options: "                       << std::endl;
    std::cout << "                --lfvType    [Choose lfv channel: "
	      << " options 1,2,3']"                               << std::endl;
    std::cout << "                --useBjet    [[Enable b-jet veto:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --useGUI     [Enable GUI mode:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --debug      [Enable debug]"    << std::endl;
    std::cout << "                --help       [Print this help]" << std::endl;
    exit(0);
  }

  std::cout << "< kMJ_Fits() >:: Options set "            << std::endl;
  std::cout << "                lfvType    = " << lfvType << std::endl;
  std::cout << "                useBjet    = " << useBjet << std::endl;
  std::cout << "                useGUI     = " << useGUI  << std::endl;
  std::cout << "                debug      = " << debug   << std::endl;

  std::string chanName = "";
  if(lfvType==1)      { chanName="emu";   }
  else if(lfvType==2) { chanName="etau";  }
  else if(lfvType==3) { chanName="mutau"; }

  m_debug = debug;

  TRint *myApp = new TRint("RootSession",&argc,argv,NULL,0);
  kMJ_Fits(chanName,useBjet);
  
  if(useGUI){
    std::cout << "< kMJ_Fits() >:: using Rint -> ROOT will remain "
	      << "opened ... " << std::endl;
    myApp->Run();
  }
  
  return 0;
  
}

void kMJ_Fits(std::string lfvType, bool useBjet){

  SetATLASStyle(true);

  std::string Dir = "";
  if(useBjet){ Dir += "Bjet/";   }
  else{        Dir += "NoBjet/"; }
  
  TFile *f = new TFile( (Dir+lfvType+"_mllCorr_kfact.root").c_str() );

  TH1F *Hss = (TH1F*)f->Get( "SS_kfact" );
  TH1F *Hos = (TH1F*)f->Get( "OS_kfact" );
  
  TF1 *SS = new TF1("ss","pol5",120,2000);
  SS->SetParameter( 0, 0.348302    );
  SS->SetParameter( 1,-0.00163441  );
  SS->SetParameter( 2, 3.25303e-06 );
  SS->SetParameter( 3,-2.95269e-09 );
  SS->SetParameter( 4, 1.23169e-12 );
  SS->SetParameter( 5,-1.93218e-16 );
  
  SS->SetParError( 0, 0.0749117   );
  SS->SetParError( 1, 0.000687638 ); 
  SS->SetParError( 2, 2.16688e-06 ); 
  SS->SetParError( 3, 2.96639e-09 ); 
  SS->SetParError( 4, 1.78656e-12 ); 
  SS->SetParError( 5, 3.84644e-16 );

  TF1 *OS = new TF1("os","pol5",120,2000);
  OS->SetParameter( 0,  0.426871    );
  OS->SetParameter( 1, -0.00172647  );
  OS->SetParameter( 2,  3.24979e-06 );
  OS->SetParameter( 3, -3.03347e-09 );
  OS->SetParameter( 4,  1.33983e-12 );
  OS->SetParameter( 5, -2.23464e-16 );
  
  OS->SetParError( 0, 0.0998207   );
  OS->SetParError( 1, 0.000705111 );
  OS->SetParError( 2, 1.653e-06   );
  OS->SetParError( 3, 1.65967e-09 );
  OS->SetParError( 4, 7.46777e-13 );
  OS->SetParError( 5, 1.24317e-16 );


  /* Draw SS */
  TCanvas *cs_SS = CreateCanvas("SS");
  cs_SS->cd();
  cs_SS->SetLogx();
  
  SS->SetLineColor(kRed);
  SS->SetMarkerColor(kRed);
  SS->SetMarkerSize(0);
  Hss->GetXaxis()->SetRangeUser(120,2000);
  Hss->GetYaxis()->SetTitle("k_{MJ}^{SS}");
  Hss->GetYaxis()->SetRangeUser(-0.08,0.45);
  Hss->Fit(SS,"R");
  TH1D *SSband = new TH1D("SSband","SSband", 35, 95, 2000);
  (TVirtualFitter::GetFitter())->GetConfidenceIntervals(SSband);
  SSband->SetStats(kFALSE);
  SSband->SetFillColor(kRed-10);
  SSband->SetMarkerSize(0);
  SSband->SetMarkerColor(kRed-10);
  SSband->Draw("E3same");
  //gPad->RedrawAxis();
  Hss->Draw("pesame");
  DrawLabels();
  DrawChannel(lfvType);
  

  /* Draw OS */
  TCanvas *cs_OS = CreateCanvas("OS");
  cs_OS->cd();
  cs_OS->SetLogx();
  
  OS->SetLineColor(kBlue);
  OS->SetMarkerColor(kBlue);
  OS->SetMarkerSize(0);
  Hos->GetXaxis()->SetRangeUser(120,2000);
  Hos->GetYaxis()->SetTitle("k_{MJ}^{OS}");
  Hos->GetYaxis()->SetRangeUser(-0.08,0.45);
  Hos->Fit(OS,"R");
  TH1D *OSband = new TH1D("OSband","OSband", 35, 95, 2000);
  (TVirtualFitter::GetFitter())->GetConfidenceIntervals(OSband);
  OSband->SetStats(kFALSE);
  OSband->SetFillColor(kBlue-10);
  OSband->SetMarkerSize(0);
  OSband->SetMarkerColor(kBlue-10);
  OSband->Draw("E3same");
  Hos->Draw("pesame");
  DrawLabels();
  DrawChannel(lfvType);
  //gPad->RedrawAxis();
  
  /* Draw functions */
  TH1F *dummy = (TH1F*)Hss->Clone("dummy");
  dummy->Reset();
  dummy->GetXaxis()->SetMoreLogLabels(kTRUE);
  dummy->GetXaxis()->SetNoExponent(kTRUE);
  dummy->GetYaxis()->SetTitle( "k_{MJ}^{SS}" );
  dummy->GetYaxis()->SetRangeUser(-0.08,0.45);
  dummy->SetStats(kFALSE);
  
  TF1 *SS_nom = new TF1("ss_nom","pol5",120,2000);
  SS_nom->SetParameter( 0, 0.348302    );
  SS_nom->SetParameter( 1,-0.00163441  );//+ 0.000687638);
  SS_nom->SetParameter( 2, 3.25303e-06 );//+ 2.16688e-06);
  SS_nom->SetParameter( 3,-2.95269e-09 );//+ 2.96639e-09);
  SS_nom->SetParameter( 4, 1.23169e-12 );//+ 1.78656e-12);
  SS_nom->SetParameter( 5,-1.93218e-16 );//+ 3.84644e-16);
  
  TF1 *SS_var1 = new TF1("ss_var1","pol5",120,2000);
  SS_var1->SetParameter( 0, 0.348302    + 0.0749117  );
  SS_var1->SetParameter( 1,-0.00163441  );//+ 0.000687638);
  SS_var1->SetParameter( 2, 3.25303e-06 );//+ 2.16688e-06);
  SS_var1->SetParameter( 3,-2.95269e-09 );//+ 2.96639e-09);
  SS_var1->SetParameter( 4, 1.23169e-12 );//+ 1.78656e-12);
  SS_var1->SetParameter( 5,-1.93218e-16 );//+ 3.84644e-16);
  
  TF1 *SS_var2 = new TF1("ss_var2","pol5",120,2000);
  SS_var2->SetParameter( 0, 0.348302    );
  SS_var2->SetParameter( 1,-0.00163441  + 0.000687638);
  SS_var2->SetParameter( 2, 3.25303e-06 );//+ 2.16688e-06);
  SS_var2->SetParameter( 3,-2.95269e-09 );//+ 2.96639e-09);
  SS_var2->SetParameter( 4, 1.23169e-12 );//+ 1.78656e-12);
  SS_var2->SetParameter( 5,-1.93218e-16 );//+ 3.84644e-16);

  TF1 *SS_var3 = new TF1("ss_var3","pol5",120,2000);
  SS_var3->SetParameter( 0, 0.348302    );
  SS_var3->SetParameter( 1,-0.00163441  );
  SS_var3->SetParameter( 2, 3.25303e-06 + 2.16688e-06);
  SS_var3->SetParameter( 3,-2.95269e-09 );//+ 2.96639e-09);
  SS_var3->SetParameter( 4, 1.23169e-12 );//+ 1.78656e-12);
  SS_var3->SetParameter( 5,-1.93218e-16 );//+ 3.84644e-16);

  TF1 *SS_var4 = new TF1("ss_var4","pol5",120,2000);
  SS_var4->SetParameter( 0, 0.348302    );
  SS_var4->SetParameter( 1,-0.00163441  );
  SS_var4->SetParameter( 2, 3.25303e-06 );
  SS_var4->SetParameter( 3,-2.95269e-09 + 2.96639e-09);
  SS_var4->SetParameter( 4, 1.23169e-12 );//+ 1.78656e-12);
  SS_var4->SetParameter( 5,-1.93218e-16 );//+ 3.84644e-16);

  TF1 *SS_var5 = new TF1("ss_var5","pol5",120,2000);
  SS_var5->SetParameter( 0, 0.348302    );
  SS_var5->SetParameter( 1,-0.00163441  );
  SS_var5->SetParameter( 2, 3.25303e-06 );
  SS_var5->SetParameter( 3,-2.95269e-09 );
  SS_var5->SetParameter( 4, 1.23169e-12 + 1.78656e-12);
  SS_var5->SetParameter( 5,-1.93218e-16 );//+ 3.84644e-16);

  TF1 *SS_var6 = new TF1("ss_var6","pol5",120,2000);
  SS_var6->SetParameter( 0, 0.348302    );
  SS_var6->SetParameter( 1,-0.00163441  );
  SS_var6->SetParameter( 2, 3.25303e-06 );
  SS_var6->SetParameter( 3,-2.95269e-09 );
  SS_var6->SetParameter( 4, 1.23169e-12 );
  SS_var6->SetParameter( 5,-1.93218e-16 + 3.84644e-16);
  
  TCanvas *c = CreateCanvas("funcs");
  c->cd();

  SS_nom  -> SetLineColor( kBlack   );
  SS_var1 -> SetLineColor( kGreen+1 );
  SS_var2 -> SetLineColor( kBlue    );
  SS_var3 -> SetLineColor( kRed     );
  SS_var4 -> SetLineColor( kOrange  );
  SS_var5 -> SetLineColor( kMagenta );
  SS_var6 -> SetLineColor( kCyan    );

  dummy   -> Draw();
  SS_nom  -> Draw("same");
  SS_var1 -> Draw("same");
  SS_var2 -> Draw("same");
  SS_var3 -> Draw("same");
  SS_var4 -> Draw("same");
  SS_var5 -> Draw("same");
  SS_var6 -> Draw("same");

  TLegend *leg = CreateLegend();
  leg->AddEntry(SS_nom,"Nominal","l");
  leg->AddEntry(SS_var1,"par_0 max var","l");
  leg->AddEntry(SS_var2,"par_1 max var","l");
  leg->AddEntry(SS_var3,"par_2 max var","l");
  leg->AddEntry(SS_var4,"par_3 max var","l");
  leg->AddEntry(SS_var5,"par_4 max var","l");
  leg->AddEntry(SS_var6,"par_5 max var","l");
  leg->Draw();

  DrawLabels();
  DrawChannel(lfvType);
  gPad->RedrawAxis();
  
  /* Draw OS and SS and fit var */
  TCanvas *cs_OSSS = CreateCanvas("OSSS");
  cs_OSSS->cd();
  cs_OSSS->SetLogx();

  dummy->Draw();
  SSband->Draw("E3same");
  OSband->Draw("E3same");
  SS->Draw("same");  
  OS->Draw("same");
  //SS_var1 -> Draw("same");
  
  DrawLabels();
  DrawChannel(lfvType);
  
  TLegend *leg2 = CreateLegend();
  leg2->AddEntry(SS,"SS function","l");
  leg2->AddEntry(OS,"OS function","l");
  //leg2->AddEntry(SS_var1,"par_0 max var","l");
  leg2->Draw();

  gPad->RedrawAxis();

  //Int_t bins = Hss->GetNbinsX();
  //for(int i=1; i<bins+1; i++){
  //
  //  if(Hss->GetBinContent(i)!=0){
  //    std::cout << "bin = " << i << " mass = " << Hss->GetBinCenter(i)
  //		<< " Value  = "  << Hss->GetBinContent(i) << " OS val = "
  //		<< OS->Eval(Hss->GetBinCenter(i)) << " Diff = "
  //		<< OS->Eval(Hss->GetBinCenter(i))-Hss->GetBinContent(i)
  //		<< std::endl;
  //  }
  //}
  
}
