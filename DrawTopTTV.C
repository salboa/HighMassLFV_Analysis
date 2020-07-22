/* Program includes */
#include "DrawTopTTV.h"
#include "Utils.C"

int main( int argc, char* argv[] ) {

  int lfvType        = -1;
  bool useBjet       = false;
  bool useGUI        = false;
  bool doTTV         = false;
  bool doTop         = false;
  bool printHelp     = false;
  for(int i = 1; i < argc; ++i){
    if( !strcmp(argv[i],"--lfvType")      ){ lfvType   = std::stoi(argv[i+1]); }
    else if( !strcmp(argv[i],"--useBjet") ){ useBjet   = true; }
    else if( !strcmp(argv[i],"--useGUI")  ){ useGUI    = true; }
    else if( !strcmp(argv[i],"--doTTV")   ){ doTTV     = true; }
    else if( !strcmp(argv[i],"--doTop")   ){ doTop     = true; }
    else if( !strcmp(argv[i],"--help")    ){ printHelp = true; }
    else{
      if(std::string(argv[i]).find("--")!=std::string::npos)
	std::cout << "WARNING:: Option " << argv[i] << " not recognized: "
		  << "skipping!" << std::endl;
    }
  }

  if(printHelp){
    std::cout << " DrawTopTTV: make ttV and Top MC comp plots!"   << std::endl;
    std::cout << "               Options: "                       << std::endl;
    std::cout << "                --useBjet    [Enable b-jet veto:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --useGUI     [Enable GUI mode:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --lfvType    [Choose lfv channel: "
	      << " options 1,2,3']"                               << std::endl;
    std::cout << "                --doTTV      [Do ttV plots:"
      	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --doTop      [Do Top MC comp plots:"
      	      << " default is 'false'] "                          << std::endl;
    std::cout << "                --help       [Print this help]" << std::endl;
    exit(0);
  }

  std::cout << "< DrawTopTTV() >:: Options set "           << std::endl;
  std::cout << "                useBjet    = " << useBjet  << std::endl;
  std::cout << "                lfvType    = " << lfvType  << std::endl;
  std::cout << "                doTTV      = " << doTTV    << std::endl;
  std::cout << "                doTop      = " << doTop    << std::endl;
  std::cout << "                useGUI     = " << useGUI   << std::endl;
  
  std::string chanName = "";
  if(lfvType==1)      { chanName="emu";   }
  else if(lfvType==2) { chanName="etau";  }
  else if(lfvType==3) { chanName="mutau"; }

  TRint *myApp = new TRint("RootSession",&argc,argv,NULL,0);
  if(doTTV)
    DrawTTV(chanName,useBjet);
  else if(doTop)
    DrawTopMCgens(chanName);
  
  if(useGUI){
    std::cout << "< DrawTopTTV() >:: using Rint -> ROOT will remain "
	      << "opened ... " << std::endl;
    myApp->Run();
  }

  return 0;
  
}

void DrawTTV(std::string lfvType, bool useBjet){

  SetATLASStyle();
  TH1::SetDefaultSumw2(kTRUE);

  std::string Dir = "";
  if(useBjet){ Dir += "Bjet/";   }
  else       { Dir += "NoBjet/"; }
  TFile *Nom = new TFile( (Dir+"Plots_Nominal_"+lfvType+".root").c_str() );
  TH1F *nom  = (TH1F*)Nom->Get( "hmllCorr_ttV" );
  
  nom->SetLineColor(1);

  TCanvas *cs = CreateCanvas("ttV");
  cs->cd();
  cs->SetLogy(true);
  cs->SetLogx(true);

  nom->GetYaxis()->SetTitle("Events");
  nom->GetXaxis()->SetRangeUser(130,3000);
  nom->GetYaxis()->SetRangeUser(0.005,1000);

  nom->Draw("hist");
  DrawLabels();
  DrawChannel(lfvType,false,useBjet);

  std::cout << "ttV = " << nom->Integral() << std::endl;
  
}

void DrawTopMCgens(std::string lfvType){
  
  SetATLASStyle();
  TH1::SetDefaultSumw2(kTRUE);

  std::string Dir = "NoBjet/ttbarCR";
  
  TFile *Pow = new TFile( (Dir+"/Plots_Nominal_"+lfvType+".root").c_str() );
  TFile *She = new TFile( (Dir+"_Sherpa/Plots_Nominal_"+lfvType+".root").c_str() );

  TH1F *hPow = (TH1F*)Pow->Get( "hmllCorr_Top" );
  TH1F *hShe = (TH1F*)She->Get( "hmllCorr_Top" );

  hPow->SetLineColor(1);
  hPow->SetMarkerColor(1);
  hPow->SetMarkerSize(0.3);
  hShe->SetLineColor(2);
  hShe->SetMarkerColor(2);
  hShe->SetMarkerSize(0.3);
  
  std::cout << " Powheg = " << hPow->Integral()
	    << " Sherpa = " << hShe->Integral() << std::endl;
  
  TH1F *ratio = (TH1F*)hPow->Clone("ratio");
  ratio->Reset();
  ratio->GetXaxis()->SetTitle(hPow->GetXaxis()->GetTitle());
    
  TH1F *ratioLine = (TH1F*)ratio->Clone("ratioLine");
  for (int k=-1; k<ratioLine->GetNbinsX()+1; k++){
    ratioLine->SetBinContent(k,1.);
  }
  ratioLine->GetYaxis()->SetTitle("Ratio");

  ratio->Divide(hShe,hPow);
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

  ratio->GetXaxis()->SetRange(130,2900);

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

  ratio->SetLineColor(kGreen+2);
  ratio->SetMarkerColor(kGreen+2);
  ratio->SetMarkerSize(1.2);
  ratio->GetXaxis()->SetRangeUser(80,2100);
  ratioLine->SetLineColor(2);
  ratioLine->SetLineStyle(2);
  ratioLine->GetXaxis()->SetRangeUser(80,2100);

  TCanvas *cs = CreateCanvas("PowShe");
  TPad *p1    = CreateTopPad("PowShe","mllCorr");
  TPad *p2    = CreateBottomPad("PowShe","mllCorr");

  cs->cd();
  p1->Draw();
  p2->Draw();

  p1->cd();
  hPow->GetYaxis()->SetTitle("Events");
  hPow->GetXaxis()->SetRangeUser(80,2100);
  hPow->GetYaxis()->SetRangeUser(0.005,500000);
  hShe->GetYaxis()->SetTitle("Events");
  hShe->GetXaxis()->SetRangeUser(80,2100);
  hShe->GetYaxis()->SetRangeUser(0.005,500000);
  
  hPow->Draw("histe");
  hShe->Draw("histesame");
  
  TLegend *leg = CreateLegend();
  leg->AddEntry(hPow,"Powheg", "l");
  leg->AddEntry(hShe,"Sherpa", "l");
  leg->AddEntry(ratio,"Sherpa / Powheg","pel");
  leg->Draw();

  DrawLabels(true);
  DrawChannel(lfvType,true);
  
  p2->cd();
  ratioLine->Draw("hist");
  ratio->Draw("pE0same");
  p2->Update();

}
