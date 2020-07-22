/* C++ includes */
#include "iostream"
#include "set"
/* program includes */
#include "AdjustFakeRate.h"

int main( int argc, char* argv[] ) {

  bool useBjet   = false;
  bool printHelp = false;
  for(int i = 1; i < argc; ++i){
    if( !strcmp(argv[i],"--useBjet") ){ useBjet   = true; }
    if( !strcmp(argv[i],"--help")    ){ printHelp = true; }
    else{
      if(std::string(argv[i]).find("--")!=std::string::npos)
	std::cout << "WARNING:: Option " << argv[i] << " not recognized: "
		  << "skipping!" << std::endl;
    }
  }
  if(printHelp){
    std::cout << " AdjustFakeRate: make tau fake rate plots! "   << std::endl;
    std::cout << "                 Options: "                    << std::endl;
    std::cout << "                  --useBjet [Enable b-jet veto:"
	      << " default is 'false'] "                         << std::endl;
    std::cout << "                  --help    [Print this help]" << std::endl;
    exit(0);
  }

  if(useBjet)
    std::cout << "< AdjustFakeRate() >:: using B-jet veto!" << std::endl;
  else
    std::cout << "< AdjustFakeRate() >:: NOT using B-jet veto!" << std::endl;
  
  AdjustFakeRate(useBjet);
  
  return 0;
  
}
  
void SetATLASStyle(){
  
  TStyle *atlasStyle = new TStyle("ATLAS","Atlas style");
  
  /*use plain black on white colors*/
  Int_t icol=0; // WHITE
  atlasStyle->SetFrameBorderMode(icol);
  atlasStyle->SetFrameFillColor(icol);
  atlasStyle->SetCanvasBorderMode(icol);
  atlasStyle->SetCanvasColor(icol);
  atlasStyle->SetPadBorderMode(icol);
  atlasStyle->SetPadColor(icol);
  atlasStyle->SetStatColor(icol);
  /*don't use: white fill color for *all* objects*/
  //atlasStyle->SetFillColor(icol); 

  /*set the paper & margin sizes*/
  atlasStyle->SetPaperSize(20,26);

  /*set margin sizes*/
  atlasStyle->SetPadTopMargin(0.05);
  atlasStyle->SetPadRightMargin(0.05);
  atlasStyle->SetPadBottomMargin(0.16);
  atlasStyle->SetPadLeftMargin(0.14);

  /*set title offsets (for axis label)*/
  atlasStyle->SetTitleXOffset(1.4);
  atlasStyle->SetTitleYOffset(1.4);

  /*use large fonts*/
  //Int_t font=72; // Helvetica italics
  Int_t font=42; // Helvetica
  Double_t tsize=0.04; //io=0.04
  atlasStyle->SetTextFont(font);

  atlasStyle->SetTextSize(tsize);
  atlasStyle->SetLabelFont(font,"x");
  atlasStyle->SetTitleFont(font,"x");
  atlasStyle->SetLabelFont(font,"y");
  atlasStyle->SetTitleFont(font,"y");
  atlasStyle->SetLabelFont(font,"z");
  atlasStyle->SetTitleFont(font,"z");

  atlasStyle->SetLabelSize(tsize,"x");
  atlasStyle->SetTitleSize(tsize,"x");
  atlasStyle->SetLabelSize(tsize,"y");
  atlasStyle->SetTitleSize(tsize,"y");
  atlasStyle->SetLabelSize(tsize,"z");
  atlasStyle->SetTitleSize(tsize,"z");

  /*use bold lines and markers*/
  atlasStyle->SetMarkerStyle(20);
  atlasStyle->SetMarkerSize(1.2);
  atlasStyle->SetHistLineWidth(2.);
  atlasStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

  /*get rid of X error bars*/
  //atlasStyle->SetErrorX(0.001);
  /*get rid of error bar caps*/
  atlasStyle->SetEndErrorSize(0.);

  /*do not display any of the standard histogram decorations*/
  atlasStyle->SetOptTitle(0);
  //atlasStyle->SetOptStat(1111);
  atlasStyle->SetOptStat(0);
  //atlasStyle->SetOptFit(1111);
  atlasStyle->SetOptFit(0);

  /*put tick marks on top and RHS of plots*/
  atlasStyle->SetPadTickX(1);
  atlasStyle->SetPadTickY(1);

  gROOT->SetStyle("ATLAS");
  gROOT->ForceStyle();

}

void AdjustFakeRate(bool useBjet){

  SetATLASStyle();
  TH1::SetDefaultSumw2(kTRUE);

  std::string Dir = "TaFrRaw/";
  
  TFile *input_Nom = NULL, *input_StatUp = NULL, *input_StatDw = NULL;
  TFile *input_BDT_SysUp = NULL, *input_BDT_SysDw = NULL, *input_CR_Sys = NULL;
  TFile *input_NoBDT = NULL, *input_Comp_Sys = NULL;
  if(useBjet){
    //to be updated
    input_Nom       = new TFile( (Dir+"TauFakeRate_NoBDTCut_bjetveto.root").c_str()    );
    input_StatUp    = new TFile( (Dir+"TauFakeRate_WithBDTCut_bjeteveto.root").c_str() );
    input_StatDw    = new TFile( (Dir+"TauFakeRate_WithBDTCut_bjeteveto.root").c_str() );
    input_BDT_SysUp = new TFile( (Dir+"TauFakeRate_WithBDTCut_bjeteveto.root").c_str() );
    input_BDT_SysDw = new TFile( (Dir+"TauFakeRate_WithBDTCut_bjeteveto.root").c_str() );
    input_CR_Sys    = new TFile( (Dir+"TauFakeRate_NoMTDPhiCut_bjetveto.root").c_str() );
    input_NoBDT     = new TFile( (Dir+"TauFakeResults_NoBDT_bjetveto.root").c_str()    );
    input_Comp_Sys  = new TFile( (Dir+"TauFakeResults_Comp.root").c_str()              );
  }
  else{
    input_Nom       = new TFile( (Dir+"TauFakeResults_BDT04.root").c_str()          );
    input_StatUp    = new TFile( (Dir+"TauFakeResults_BDT04_STATUP.root").c_str()   );
    input_StatDw    = new TFile( (Dir+"TauFakeResults_BDT04_STATDOWN.root").c_str() );
    input_BDT_SysUp = new TFile( (Dir+"TauFakeResults_BDT05.root").c_str()          );
    input_BDT_SysDw = new TFile( (Dir+"TauFakeResults_BDT03.root").c_str()          );
    input_CR_Sys    = new TFile( (Dir+"TauFakeResults_BDT04_noMT.root").c_str()     );
    input_NoBDT     = new TFile( (Dir+"TauFakeResults_NoBDT.root").c_str()          );
    input_Comp_Sys  = new TFile( (Dir+"TauFakeResults_Comp.root").c_str()           );
  }

  /* Original Histos */
  TH1F* pT_1p        = (TH1F*)input_Nom->Get( "TaupT_1prongFraction"    );
  TH1F* pT_3p        = (TH1F*)input_Nom->Get( "TaupT_3prongFraction"    );
  TH1F* Eta_1p       = (TH1F*)input_Nom->Get( "TauEta_1prongFraction"   );
  TH1F* Eta_3p       = (TH1F*)input_Nom->Get( "TauEta_3prongFraction"   );
  TH2F* pTeta_1p     = (TH2F*)input_Nom->Get( "TaupTEta_1prongFraction" );
  TH2F* pTeta_3p     = (TH2F*)input_Nom->Get( "TaupTEta_3prongFraction" );

  TH1F* pT_1p_StatUp    = (TH1F*)input_StatUp->Get( "TaupT_1prongFraction"    );
  TH1F* pT_3p_StatUp    = (TH1F*)input_StatUp->Get( "TaupT_3prongFraction"    );
  TH1F* Eta_1p_StatUp   = (TH1F*)input_StatUp->Get( "TauEta_1prongFraction"   );
  TH1F* Eta_3p_StatUp   = (TH1F*)input_StatUp->Get( "TauEta_3prongFraction"   );
  TH2F* pTeta_1p_StatUp = (TH2F*)input_StatUp->Get( "TaupTEta_1prongFraction" );
  TH2F* pTeta_3p_StatUp = (TH2F*)input_StatUp->Get( "TaupTEta_3prongFraction" );

  TH1F* pT_1p_StatDw    = (TH1F*)input_StatDw->Get( "TaupT_1prongFraction"    );
  TH1F* pT_3p_StatDw    = (TH1F*)input_StatDw->Get( "TaupT_3prongFraction"    );
  TH1F* Eta_1p_StatDw   = (TH1F*)input_StatDw->Get( "TauEta_1prongFraction"   );
  TH1F* Eta_3p_StatDw   = (TH1F*)input_StatDw->Get( "TauEta_3prongFraction"   );
  TH2F* pTeta_1p_StatDw = (TH2F*)input_StatDw->Get( "TaupTEta_1prongFraction" );
  TH2F* pTeta_3p_StatDw = (TH2F*)input_StatDw->Get( "TaupTEta_3prongFraction" );

  TH1F* pT_1p_bdtUp    = (TH1F*)input_BDT_SysUp->Get( "TaupT_1prongFraction"    );
  TH1F* pT_3p_bdtUp    = (TH1F*)input_BDT_SysUp->Get( "TaupT_3prongFraction"    );
  TH1F* Eta_1p_bdtUp   = (TH1F*)input_BDT_SysUp->Get( "TauEta_1prongFraction"   );
  TH1F* Eta_3p_bdtUp   = (TH1F*)input_BDT_SysUp->Get( "TauEta_3prongFraction"   );
  TH2F* pTeta_1p_bdtUp = (TH2F*)input_BDT_SysUp->Get( "TaupTEta_1prongFraction" );
  TH2F* pTeta_3p_bdtUp = (TH2F*)input_BDT_SysUp->Get( "TaupTEta_3prongFraction" );

  TH1F* pT_1p_bdtDw    = (TH1F*)input_BDT_SysDw->Get( "TaupT_1prongFraction"    );
  TH1F* pT_3p_bdtDw    = (TH1F*)input_BDT_SysDw->Get( "TaupT_3prongFraction"    );
  TH1F* Eta_1p_bdtDw   = (TH1F*)input_BDT_SysDw->Get( "TauEta_1prongFraction"   );
  TH1F* Eta_3p_bdtDw   = (TH1F*)input_BDT_SysDw->Get( "TauEta_3prongFraction"   );
  TH2F* pTeta_1p_bdtDw = (TH2F*)input_BDT_SysDw->Get( "TaupTEta_1prongFraction" );
  TH2F* pTeta_3p_bdtDw = (TH2F*)input_BDT_SysDw->Get( "TaupTEta_3prongFraction" );

  TH1F* pT_1p_CR     = (TH1F*)input_CR_Sys->Get( "TaupT_1prongFraction"    );
  TH1F* pT_3p_CR     = (TH1F*)input_CR_Sys->Get( "TaupT_3prongFraction"    );
  TH1F* Eta_1p_CR    = (TH1F*)input_CR_Sys->Get( "TauEta_1prongFraction"   );
  TH1F* Eta_3p_CR    = (TH1F*)input_CR_Sys->Get( "TauEta_3prongFraction"   );
  TH2F* pTeta_1p_CR  = (TH2F*)input_CR_Sys->Get( "TaupTEta_1prongFraction" );
  TH2F* pTeta_3p_CR  = (TH2F*)input_CR_Sys->Get( "TaupTEta_3prongFraction" );

  TH1F* pT_1p_NoBDT    = (TH1F*)input_NoBDT->Get( "TaupT_1prongFraction"    );
  TH1F* pT_3p_NoBDT    = (TH1F*)input_NoBDT->Get( "TaupT_3prongFraction"    );
  TH1F* Eta_1p_NoBDT   = (TH1F*)input_NoBDT->Get( "TauEta_1prongFraction"   );
  TH1F* Eta_3p_NoBDT   = (TH1F*)input_NoBDT->Get( "TauEta_3prongFraction"   );
  TH2F* pTeta_1p_NoBDT = (TH2F*)input_NoBDT->Get( "TaupTEta_1prongFraction" );
  TH2F* pTeta_3p_NoBDT = (TH2F*)input_NoBDT->Get( "TaupTEta_3prongFraction" );

  TH1F* pT_1p_Comp_SysUp = (TH1F*)pT_1p->Clone( "TaupT_1prongFraction_tmpUp" );
  TH1F* pT_1p_Comp_SysDw = (TH1F*)pT_1p->Clone( "TaupT_1prongFraction_tmpDw" );
  TH1F* pT_3p_Comp_SysUp = (TH1F*)pT_3p->Clone( "TaupT_3prongFraction_tmpUp" );
  TH1F* pT_3p_Comp_SysDw = (TH1F*)pT_3p->Clone( "TaupT_3prongFraction_tmpDw" );
  TH1F* var_1p           = (TH1F*)input_Comp_Sys->Get( "TaupT_1prongRATIOMC" );
  TH1F* var_3p           = (TH1F*)input_Comp_Sys->Get( "TaupT_3prongRATIOMC" );
 
  std::string OutName = "VarInputs/TauFakeFactors";
  if(useBjet){ OutName += "_BjetVeto"; }

  TFile* output = new TFile( (OutName+".root").c_str(),"RECREATE" );
  output->cd();
  
  pT_1p           -> Write( "Tau_pT_Fraction_1prong_Nom"    );
  pT_3p           -> Write( "Tau_pT_Fraction_3prong_Nom"    );
  Eta_1p          -> Write( "Tau_Eta_Fraction_1prong_Nom"   );
  Eta_3p          -> Write( "Tau_Eta_Fraction_3prong_Nom"   );
  pTeta_1p        -> Write( "Tau_pTeta_Fraction_1prong_Nom" );
  pTeta_3p        -> Write( "Tau_pTeta_Fraction_3prong_Nom" );

  pT_1p_StatUp    -> Write( "Tau_pT_Fraction_1prong_StatUp"    );
  pT_3p_StatUp    -> Write( "Tau_pT_Fraction_3prong_StatUp"    );
  Eta_1p_StatUp   -> Write( "Tau_Eta_Fraction_1prong_StatUp"   );
  Eta_3p_StatUp   -> Write( "Tau_Eta_Fraction_3prong_StatUp"   );
  pTeta_1p_StatUp -> Write( "Tau_pTeta_Fraction_1prong_StatUp" );
  pTeta_3p_StatUp -> Write( "Tau_pTeta_Fraction_3prong_StatUp" );

  pT_1p_StatDw    -> Write( "Tau_pT_Fraction_1prong_StatDown"    );
  pT_3p_StatDw    -> Write( "Tau_pT_Fraction_3prong_StatDown"    );
  Eta_1p_StatDw   -> Write( "Tau_Eta_Fraction_1prong_StatDown"   );
  Eta_3p_StatDw   -> Write( "Tau_Eta_Fraction_3prong_StatDown"   );
  pTeta_1p_StatDw -> Write( "Tau_pTeta_Fraction_1prong_StatDown" );
  pTeta_3p_StatDw -> Write( "Tau_pTeta_Fraction_3prong_StatDown" );
  
  pT_1p_bdtUp     -> Write( "Tau_pT_Fraction_1prong_BDT_SysUp"    );
  pT_3p_bdtUp     -> Write( "Tau_pT_Fraction_3prong_BDT_SysUp"    );
  Eta_1p_bdtUp    -> Write( "Tau_Eta_Fraction_1prong_BDT_SysUp"   );
  Eta_3p_bdtUp    -> Write( "Tau_Eta_Fraction_3prong_BDT_SysUp"   );
  pTeta_1p_bdtUp  -> Write( "Tau_pTeta_Fraction_1prong_BDT_SysUp" );
  pTeta_3p_bdtUp  -> Write( "Tau_pTeta_Fraction_3prong_BDT_SysUp" );

  pT_1p_bdtDw     -> Write( "Tau_pT_Fraction_1prong_BDT_SysDown"    );
  pT_3p_bdtDw     -> Write( "Tau_pT_Fraction_3prong_BDT_SysDown"    );
  Eta_1p_bdtDw    -> Write( "Tau_Eta_Fraction_1prong_BDT_SysDown"   );
  Eta_3p_bdtDw    -> Write( "Tau_Eta_Fraction_3prong_BDT_SysDown"   );
  pTeta_1p_bdtDw  -> Write( "Tau_pTeta_Fraction_1prong_BDT_SysDown" );
  pTeta_3p_bdtDw  -> Write( "Tau_pTeta_Fraction_3prong_BDT_SysDown" );

  pT_1p_CR        -> Write( "Tau_pT_Fraction_1prong_SysCR"    );
  pT_3p_CR        -> Write( "Tau_pT_Fraction_3prong_SysCR"    );
  Eta_1p_CR       -> Write( "Tau_Eta_Fraction_1prong_SysCR"   );
  Eta_3p_CR       -> Write( "Tau_Eta_Fraction_3prong_SysCR"   );
  pTeta_1p_CR     -> Write( "Tau_pTeta_Fraction_1prong_SysCR" );
  pTeta_3p_CR     -> Write( "Tau_pTeta_Fraction_3prong_SysCR" );

  pT_1p_NoBDT     -> Write( "Tau_pT_Fraction_1prong_NoBDT"    );
  pT_3p_NoBDT     -> Write( "Tau_pT_Fraction_3prong_NoBDT"    );
  Eta_1p_NoBDT    -> Write( "Tau_Eta_Fraction_1prong_NoBDT"   );
  Eta_3p_NoBDT    -> Write( "Tau_Eta_Fraction_3prong_NoBDT"   );
  pTeta_1p_NoBDT  -> Write( "Tau_pTeta_Fraction_1prong_NoBDT" );
  pTeta_3p_NoBDT  -> Write( "Tau_pTeta_Fraction_3prong_NoBDT" );

  int Bins1p = pT_1p_Comp_SysUp->GetNbinsX();
  int Bins3p = pT_3p_Comp_SysUp->GetNbinsX();
  for(int b=1; b<Bins1p+1; b++){
    double value = pT_1p_Comp_SysUp->GetBinContent(b);
    double err   = pT_1p_Comp_SysUp->GetBinError(b);
    double var   = fabs(1-var_1p->GetBinContent(b));
    pT_1p_Comp_SysUp -> SetBinContent( b, value+value*var);
    pT_1p_Comp_SysDw -> SetBinContent( b, value-value*var);
    pT_1p_Comp_SysUp -> SetBinError( b, err );
    pT_1p_Comp_SysDw -> SetBinError( b, err );
  }
  for(int b=1; b<Bins3p+1; b++){
    double value = pT_3p_Comp_SysUp->GetBinContent(b);
    double err   = pT_3p_Comp_SysUp->GetBinError(b);
    double var   = fabs(1-var_3p->GetBinContent(b));
    pT_3p_Comp_SysUp -> SetBinContent( b, value+value*var);
    pT_3p_Comp_SysDw -> SetBinContent( b, value-value*var);
    pT_3p_Comp_SysUp -> SetBinError( b, err );
    pT_3p_Comp_SysDw -> SetBinError( b, err );
  }
  
  pT_1p_Comp_SysUp -> Write( "Tau_pT_Fraction_1prong_Comp_SysUp"   );
  pT_1p_Comp_SysDw -> Write( "Tau_pT_Fraction_1prong_Comp_SysDown" );
  pT_3p_Comp_SysUp -> Write( "Tau_pT_Fraction_3prong_Comp_SysUp"   );
  pT_3p_Comp_SysDw -> Write( "Tau_pT_Fraction_3prong_Comp_SysDown" );

  /* close out file */
  output->Close();
  
  /* Delete histos */
  pT_1p           -> Delete();
  pT_3p           -> Delete();
  Eta_1p          -> Delete();
  Eta_3p          -> Delete();
  pTeta_1p        -> Delete();
  pTeta_3p        -> Delete();

  pT_1p_StatUp    -> Delete();
  pT_3p_StatUp    -> Delete();
  Eta_1p_StatUp   -> Delete();
  Eta_3p_StatUp   -> Delete();
  pTeta_1p_StatUp -> Delete();
  pTeta_3p_StatUp -> Delete();

  pT_1p_StatDw    -> Delete();
  pT_3p_StatDw    -> Delete();
  Eta_1p_StatDw   -> Delete();
  Eta_3p_StatDw   -> Delete();
  pTeta_1p_StatDw -> Delete();
  pTeta_3p_StatDw -> Delete();
  
  pT_1p_bdtUp     -> Delete();
  pT_3p_bdtUp     -> Delete();
  Eta_1p_bdtUp    -> Delete();
  Eta_3p_bdtUp    -> Delete();
  pTeta_1p_bdtUp  -> Delete();
  pTeta_3p_bdtUp  -> Delete();

  pT_1p_bdtDw     -> Delete();
  pT_3p_bdtDw     -> Delete();
  Eta_1p_bdtDw    -> Delete();
  Eta_3p_bdtDw    -> Delete();
  pTeta_1p_bdtDw  -> Delete();
  pTeta_3p_bdtDw  -> Delete();
  
  pT_1p_CR        -> Delete();
  pT_3p_CR        -> Delete();
  Eta_1p_CR       -> Delete();
  Eta_3p_CR       -> Delete();
  pTeta_1p_CR     -> Delete();
  pTeta_3p_CR     -> Delete();

  pT_1p_NoBDT     -> Delete();
  pT_3p_NoBDT     -> Delete();
  Eta_1p_NoBDT    -> Delete();
  Eta_3p_NoBDT    -> Delete();
  pTeta_1p_NoBDT  -> Delete();
  pTeta_3p_NoBDT  -> Delete();

  pT_1p_Comp_SysUp -> Delete();
  pT_1p_Comp_SysDw -> Delete();
  pT_3p_Comp_SysUp -> Delete();
  pT_3p_Comp_SysDw -> Delete();
  var_1p->Delete();
  var_3p->Delete();
    
  /* close input files */
  input_Nom       -> Close();
  input_StatUp    -> Close();
  input_StatDw    -> Close();
  input_BDT_SysUp -> Close();
  input_BDT_SysDw -> Close();
  input_CR_Sys    -> Close();
  input_NoBDT     -> Close();
  input_Comp_Sys  -> Close();

}
