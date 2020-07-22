/* C++ includes */
#include "iostream"
/* program includes */
#include "CheckTopFits.h"
#include "SysHandler.C"
#include "Utils.C"

int main( int argc, char* argv[] ){

  int lfvType    = -1;
  bool useBjet   = false;
  bool printHelp = false;
  bool addSys    = false;
  for(int i = 1; i < argc; ++i){
    if( !strcmp(argv[i],"--useBjet")        ){ useBjet   = true; }
    else if( !strcmp(argv[i],"--lfvType")   ){ lfvType   = std::stoi(argv[i+1]); }
    else if( !strcmp(argv[i],"--addSys")    ){ addSys    = true; }
    else if( !strcmp(argv[i],"--help")      ){ printHelp = true; }
    else{
      if(std::string(argv[i]).find("--")!=std::string::npos)
	std::cout << "WARNING:: Option " << argv[i] << " not recognized: "
		  << "skipping!" << std::endl;
    }
  }
  if(printHelp){
    std::cout << " CheckTopFit: check top fits versus input! "     << std::endl;
    std::cout << "                 Options: "                      << std::endl;
    std::cout << "                  --useBjet   [Enable b-jet veto:"
	      << " default is 'false'] "                           << std::endl;
    std::cout << "                  --lfvType   [Choose lfv channel: "
	      << " options 1,2,3']"                                << std::endl;
    std::cout << "                  --addSys    [Enable systematics: "
	      << " default is 'false'] "                           << std::endl;
    std::cout << "                  --help      [Print this help]" << std::endl;
    exit(0);
  }
   
  if(lfvType==-1){
    std::cout << "< CheckTopFit() >:: lfvType not set!"
	      << " Possible options: 1,2,3" << std::endl;
    exit(0);
  }
  std::cout << "< CheckTopFit() >:: OPTIONS: " <<std::endl;
  std::cout << "                    lfvType   = " << lfvType << std::endl;
  std::cout << "                    useBjet   = " << useBjet << std::endl;
  std::cout << "                    addSys    = " << addSys  << std::endl;
  
  CheckTopFits(lfvType,useBjet,addSys);
  
  return 0;

}

void CheckTopFits(int LFVtype, bool useBjet, bool addSys){

  SetATLASStyle();
  TH1::SetDefaultSumw2(kTRUE);
  
  std::string lfvType = "";
  if(LFVtype==1)      { lfvType="emu";   }
  else if(LFVtype==2) { lfvType="etau";  }
  else if(LFVtype==3) { lfvType="mutau"; }
  
  std::cout << "< TopScale() >:: making top scale ratios for Channel "
	    << lfvType << " in a single file "<< std:: endl;
  
  TFile *inF = NULL, *fitF= NULL, *out = NULL;

  std::string Dir = "TopFits/";

  std::string OutDir = "TopFits/";
  CheckOutDir(OutDir);

  std::string outname = "TopFitCheck";
  if( useBjet ) outname += "_BjetVeto";

  outname += "_"+lfvType;

  if(LFVtype==1)
    out = new TFile( (OutDir+outname+".root").c_str(),"RECREATE");
  else
    out = new TFile( (OutDir+outname+".root").c_str(),"UPDATE");

  if(useBjet){
    inF  = new TFile( (Dir+"ExtraInputs/TopExtraInputs_bjet_"+lfvType+".root").c_str() );
    fitF = new TFile( (Dir+"Top_"+lfvType+"BjetFits.root").c_str() );
  }
  else{
    inF  = new TFile( (Dir+"ExtraInputs/TopExtraInputs_"+lfvType+".root").c_str() );
    fitF = new TFile( (Dir+"Top_"+lfvType+"Fits.root").c_str() );
  }

  std::vector<std::string> sysVar = GetSysList(LFVtype, useBjet, addSys,
					       false, true);

  for(uint i=0; i<sysVar.size(); i++){
    std::cout << "< CheckTopFit() >:: Processing Sys "
	      << sysVar.at(i) << std::endl;
    
    Input = (TH1F*)inF->Get( ("hmllCorr_Top_"+sysVar.at(i)).c_str() );
    Fit   = (TH1F*)fitF->Get( ("hmllCorr_Top_"+sysVar.at(i)+"_FIT").c_str() );
    ratio = (TH1F*)Input->Clone( ("ratio_"+sysVar.at(i)).c_str() );

    ratioLine = (TH1F*)ratio->Clone("ratioLine");
    for (int k=-1; k<ratioLine->GetNbinsX()+1; k++){
      ratioLine->SetBinContent(k,1.);
    }
    
    ratio->Divide(Input,Fit);

    out->cd();
    ratio->Write( ("ratio_"+sysVar.at(i)).c_str() );

    DrawDistro(sysVar.at(i),lfvType,useBjet);
    
    cs->Write( ("cs_ratio_"+sysVar.at(i)).c_str() );
    if(useBjet)
      cs->SaveAs( (Dir+"plots/FitChek_bjetVeto_"+lfvType+"_"+sysVar.at(i)+".pdf").c_str() );
    else
      cs->SaveAs( (Dir+"plots/FitChek_"+lfvType+"_"+sysVar.at(i)+".pdf").c_str() );  
    /* cleaning */
    Input->Delete();
    Fit->Delete();
    ratio->Delete();
    cs->Delete();
    p1->Delete();
    p2->Delete();
  }
  inF->Close();
  fitF->Close();
  out->Close();
  
}

void DrawDistro(std::string sysVar, std::string lfvType, bool useBjet){

  cs = new TCanvas( ("cs_ratio_"+sysVar).c_str(),
		    ("cs_ratio_"+sysVar).c_str(),
		    0,0,600,600 );
  cs->cd();
  p1 = new TPad( ("p1_ratio_"+sysVar).c_str(),
		 ("p1_ratio_"+sysVar).c_str(),
		 0.01,0.345,0.99,0.99 );
  p1->Draw();
  p1->SetBottomMargin(0.00);
  
  p2 = new TPad( ("p2_ratio_"+sysVar).c_str(),
		 ("p2_ratio_"+sysVar).c_str(),
		 0.01,0.01,0.99,0.35 );
  p2->Draw();
  p2->SetTopMargin(0.00);
  p2->SetBottomMargin(0.30);
  
  p1->cd();
  p1->SetLogy();
  p1->SetLogx();
  
  Input->SetLineColor(1);
  Input->SetMarkerColor(1);
  Input->GetXaxis()->SetRangeUser(120,2000);
  Input->GetYaxis()->SetTitleSize(0.06);
  Input->GetYaxis()->SetTitleOffset(1.00);
  Input->GetYaxis()->SetTitle("Events");
  Input->GetYaxis()->SetLabelSize(0.05);
  
  Fit->SetLineColor(2);
  Fit->SetMarkerColor(2);
  Fit->SetFillColor(kWhite);
  Fit->GetYaxis()->SetRangeUser(0.005,500000);
  Fit->GetXaxis()->SetRangeUser(120,2000);
  Fit->GetYaxis()->SetTitleSize(0.06);
  Fit->GetYaxis()->SetTitleOffset(1.00);
  Fit->GetYaxis()->SetTitle("Events");
  Fit->GetYaxis()->SetLabelSize(0.05);
  
  p1->cd();
  Fit->Draw("hist");
  Input->Draw("histpsame");

  TLegend *leg = CreateLegend();
  leg->AddEntry(Input,"MC simulation","p");
  leg->AddEntry(Fit,"Fit Extrapolation","l");
  leg->Draw();

  DrawLabels(true);
  DrawChannel(lfvType,true,useBjet);
  
  p2->cd();
  p2->SetLogx();
  
  ratio->GetXaxis()->SetRangeUser(120,2000);
  ratio->GetXaxis()->SetTitle(Input->GetXaxis()->GetTitle());
  ratio->GetXaxis()->SetLabelSize(0.08);
  ratio->GetXaxis()->SetTitleOffset(1.20);
  ratio->GetXaxis()->SetTitleSize(0.12);
  ratio->GetXaxis()->SetMoreLogLabels(kTRUE);
  ratio->GetXaxis()->SetNoExponent(kTRUE);
  ratio->GetXaxis()->SetLabelSize(0.09);
  ratio->GetYaxis()->SetRangeUser(0.55,1.45);
  ratio->GetYaxis()->SetTitle("ratio");
  ratio->GetYaxis()->SetLabelSize(0.09);
  ratio->GetYaxis()->SetTitleOffset(0.55);
  ratio->GetYaxis()->SetTitleSize(0.10);
  ratio->GetYaxis()->CenterTitle(kTRUE);
  ratio->GetYaxis()->SetNdivisions(507);
  ratio->SetMarkerSize(0.9);
  ratio->SetMarkerStyle(21);
  ratio->SetLineStyle(1);
  ratio->SetLineWidth(1);
  ratio->SetLineColor(1);
  ratio->SetMarkerColor(1);

  ratioLine->GetXaxis()->SetRangeUser(120,2000);
  ratioLine->GetXaxis()->SetTitle(Input->GetXaxis()->GetTitle());
  ratioLine->GetXaxis()->SetLabelSize(0.08);
  ratioLine->GetXaxis()->SetTitleOffset(1.20);
  ratioLine->GetXaxis()->SetTitleSize(0.10);
  ratioLine->GetYaxis()->SetTitle("ratio");
  ratioLine->GetYaxis()->SetLabelSize(0.07);
  ratioLine->GetYaxis()->SetTitleOffset(0.55);
  ratioLine->GetYaxis()->SetTitleSize(0.08);
  ratioLine->GetYaxis()->CenterTitle(kTRUE);
  ratioLine->GetYaxis()->SetNdivisions(507);
  ratioLine->GetYaxis()->SetRangeUser(0.55,1.45);
  ratioLine->GetXaxis()->SetMoreLogLabels(kTRUE);
  ratioLine->GetXaxis()->SetNoExponent(kTRUE);
  ratioLine->SetLineColor(2);
  ratioLine->SetLineStyle(2);

  ratioLine->Draw("hist");
  ratio->Draw("pE0same");

}

void CheckOutDir(std::string m_OutDir){

  std::string tmp_s = m_OutDir;
  std::string delim = "/";
  size_t pos = 0;
  while( (pos = tmp_s.find(delim)) != std::string::npos ){
    m_dirs.push_back( tmp_s.substr(0, pos) );
    tmp_s.erase(0, pos + delim.length());
  }

  m_tmpOutDir = "";
  for(uint i=0; i<m_dirs.size(); i++){
    struct stat st;
    m_tmpOutDir+=m_dirs.at(i)+"/";
    if(stat(m_tmpOutDir.c_str(),&st) == 0){
      std::cout << "< RunOnMiniTree :: CheckOutDir() > :: "
		<< "\033[1;32m Out Directory " << m_tmpOutDir
		<< " already present!\033[0m" << std::endl;
    }
    else{
      std::cout << "< RunOnMiniTree :: CheckOutDir() > :: "
		<< "\033[1;34m Creating Directory " << m_tmpOutDir
		<< " ... \033[0m" << std::endl;
      int outD = system( ("mkdir "+m_tmpOutDir).c_str() );
      if(outD!=0)
	std::cout << "< RunOnMiniTree :: CheckOutDir() > :: "
		  << "\033[1;31m Directory " << m_tmpOutDir
		  << " could not be created!\033[0m" << std::endl;
    }
  }
  m_dirs.clear();
  
}
