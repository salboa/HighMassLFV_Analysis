/* program includes */
#include "FakeBkgSmooth.h"
#include "Utils.C"

int main( int argc, char* argv[] ) {

  int lfvType        = -1;
  bool useBjet       = false;
  bool useGUI        = false;
  bool printHelp     = false;
  bool debug         = false;
  for(int i = 1; i < argc; ++i){
    if( !strcmp(argv[i],"--lfvType")          ){ lfvType   = std::stoi(argv[i+1]); }
    else if( !strcmp(argv[i],"--useBjet")     ){ useBjet    = true; }
    else if( !strcmp(argv[i],"--useGUI")      ){ useGUI     = true; }
    else if( !strcmp(argv[i],"--debug")       ){ debug      = true; }
    else if( !strcmp(argv[i],"--help")        ){ printHelp  = true; }
    else{
      if(std::string(argv[i]).find("--")!=std::string::npos)
	std::cout << "WARNING:: Option " << argv[i] << " not recognized: "
		  << "skipping!" << std::endl;
    }
  }

  if(printHelp){
    std::cout << " FakeBkgSmooth: smooth qcd mll distribution!"   << std::endl;
    std::cout << "                Options: "                      << std::endl;
    std::cout << "                --useBjet    [Enable b-jet veto:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --useGUI     [Enable GUI mode:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --lfvType    [Choose lfv channel: "
	      << " options 1,2,3']"                               << std::endl;
    std::cout << "                --debug      [Enable debug]"    << std::endl;
    std::cout << "                --help       [Print this help]" << std::endl;
    exit(0);
  }

  std::cout << "< FakeBkgSmooth() >:: Options set "          << std::endl;
  std::cout << "                useBjet    = " << useBjet    << std::endl;
  std::cout << "                lfvType    = " << lfvType    << std::endl;
  std::cout << "                useGUI     = " << useGUI     << std::endl;
  std::cout << "                debug      = " << debug      << std::endl;

  std::string chanName = "";
  if(lfvType==1)      { chanName="emu";   }
  else if(lfvType==2) { chanName="etau";  }
  else if(lfvType==3) { chanName="mutau"; }

  m_debug = debug;

  TRint *myApp = new TRint("RootSession",&argc,argv,NULL,0);
  FakeBkgSmooth(chanName,useBjet);
  
  if(useGUI){
    std::cout << "< FakeBkgSmooth() >:: using Rint -> ROOT will remain "
	      << "opened ... " << std::endl;
    myApp->Run();
  }

  return 0;
  
}

void FakeBkgSmooth(std::string chanName, bool useBjet){

  SetATLASStyle();
  TH1::SetDefaultSumw2(kTRUE);

  std::string fName = "VarInputs/QCDemu";
  if(useBjet) fName += "_bjetVeto";
  TFile *QCDemu = new TFile( (fName+".root").c_str() );
  
  TH1F *mll    = (TH1F*)QCDemu->Get( "hmllqcd" );
  TH1F *mllSm  = (TH1F*)mll->Clone("hmllqcd_Smooth" );
  mll->GetXaxis()->SetRangeUser(80.,2000.);
  mllSm->GetXaxis()->SetRangeUser(175.,2500.);
  mllSm->Smooth(5000,"R");
  mllSm->Scale(mll->Integral()/mllSm->Integral() );

  std::cout << "Integrals -> mll = " << mll->Integral()
	    <<" mllSm = " << mllSm->Integral() << std::endl;

  for(int b=1; b<mllSm->GetNbinsX()+1; b++){
    if(b<37) continue;
    if(b==37)
      mllSm->SetBinContent(b, (mllSm->GetBinContent(36)+ mllSm->GetBinContent(38))/2.);
    else
      mllSm->SetBinContent(b,0);
  }
  
  TCanvas *c = new TCanvas("c","c",0,0,600,600);
  c->cd();
  c->SetLogy();
  c->SetLogx();
  
  mll->SetLineColor(kBlack);
  mll->GetXaxis()->SetMoreLogLabels(kTRUE);
  mll->GetXaxis()->SetNoExponent(kTRUE);
  mllSm->SetLineColor(kRed);
  mll->GetYaxis()->SetTitle("Events");
  mll->GetXaxis()->SetRangeUser(120,1800);
  mll->GetYaxis()->SetRangeUser(0.005,5000);
  mllSm->GetXaxis()->SetRange(120,2000);
  mll->Draw("hist");
  mllSm->Draw("histsame");
  TLegend *leg  = new TLegend(0.66,0.79,0.99,0.91);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->AddEntry(mll  ,"Raw"     ,"l");
  leg->AddEntry(mllSm,"Smoothed","l");
  leg->Draw();

  DrawLabels();
  DrawChannel(chanName,false,useBjet);
  
}
