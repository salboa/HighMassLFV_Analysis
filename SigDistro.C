/* program includes */
#include "SigDistro.h"
#include "Utils.C"

int main( int argc, char* argv[] ) {

  int lfvType       = -1   ;
  std::string model = ""   ;
  bool useGUI       = false;
  bool useBjet      = false;
  bool normalize    = false;
  bool sysComp      = false;
  bool debug        = false;
  bool printHelp    = false;
  for(int i = 1; i < argc; ++i){
    if( !strcmp(argv[i],"--lfvType")     ){ lfvType   = std::stoi(argv[i+1]); }
    else if( !strcmp(argv[i],"--useGUI")    ){ useGUI    = true; }
    else if( !strcmp(argv[i],"--normalize") ){ normalize = true; }
    else if( !strcmp(argv[i],"--sysComp")   ){ sysComp   = true; }
    else if( !strcmp(argv[i],"--model")     ){ model     = argv[i+1]; }
    else if( !strcmp(argv[i],"--useBjet")   ){ useBjet   = true; }
    else if( !strcmp(argv[i],"--debug")     ){ debug     = true; }
    else if( !strcmp(argv[i],"--help")      ){ printHelp = true; }
    else{
      if(std::string(argv[i]).find("--")!=std::string::npos)
	std::cout << "WARNING:: Option " << argv[i] << " not recognized: "
		  << "skipping!" << std::endl;
    }
  }
  if(printHelp){
    std::cout << " SigDistro: make signal distribution plots! "   << std::endl;
    std::cout << "                 Options: "                     << std::endl;
    std::cout << "                 --lfvType   [Choose lfv channel: "
	      << " options are '1,2,3'] "                         << std::endl;
    std::cout << "                 --useBjet   [Enable b-jet Veto:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                 --useGUI    [Enable GUI mode:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                 --sysComp   [Compare Nom vs sys:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                 --model     [Choose signal model:"
	      << " default is ''] "                               << std::endl;
    std::cout << "                 --normalize [Enable normalization to 1:"
              << " default is 'false'] "                          << std::endl;
    std::cout << "                 --debug     [Enable debug]"    << std::endl;
    std::cout << "                 --help      [Print this help]" << std::endl;
    exit(0);
  }

  if(lfvType==-1){
    std::cout << "< SigDistro() >:: lfvType not set!"
	      << " Possible options: 1,2,3" << std::endl;
    exit(0);
  }

  std::cout << "< SigDistro() >:: Options set "              << std::endl;
  std::cout << "                  lfvType   = " << lfvType   << std::endl;
  std::cout << "                  useBjet   = " << useBjet   << std::endl;
  std::cout << "                  normalize = " << normalize << std::endl;
  std::cout << "                  useGUI    = " << useGUI    << std::endl;
  std::cout << "                  sysComp   = " << sysComp   << std::endl;
  std::cout << "                  model     = " << model     << std::endl;
  std::cout << "                  debug     = " << debug     << std::endl;

  m_debug = debug;

  TRint *myApp = new TRint("RootSession",&argc,argv,NULL,0);
  DefineGlobals(lfvType);
  if(sysComp){
    if(model==""){
      std::cout << "< SigDistro() >:: sys comparison but no model set!" << std::endl;
      exit(0);
    }
    SigSysDistro(lfvType,useBjet,normalize,model);
  }
  else
    SigDistro(lfvType,useBjet,normalize);

  if(useGUI){
    std::cout << "< SigDistro() >:: using Rint -> ROOT will remain "
	      << "opened ... " << std::endl;
    myApp->Run();
  }

  return 0;
  
}

void DefineGlobals(int lfvType){

  /* Color and Line Style */
  Cols.push_back(kBlack);    Lin.push_back(1);
  Cols.push_back(kRed);	     Lin.push_back(2);
  Cols.push_back(kBlue);     Lin.push_back(5);
  Cols.push_back(kMagenta);  Lin.push_back(7);
  Cols.push_back(kGreen+1);  Lin.push_back(8);

  Cols.push_back(kOrange);   Lin.push_back(3);
  Cols.push_back(kCyan);     Lin.push_back(4);
  Cols.push_back(kGray);     Lin.push_back(6);
  Cols.push_back(kOrange-7); Lin.push_back(9);

  /* Systematics */
  sysVar.push_back( "Nominal" );
  name.push_back( "Nominal" );
  if(lfvType==1){
    sysVar.push_back( "MuSmeID_SysUp"  );
    sysVar.push_back( "MuSmeMS_SysUp"  );
    sysVar.push_back( "MuScale_SysUp"  );
    sysVar.push_back( "MuSagRho_SysUp" );
    sysVar.push_back( "MuSagRes_SysUp" );
    sysVar.push_back( "ElSme_SysUp"    );
    sysVar.push_back( "ElScale_SysUp"  );

    name.push_back( "MuSmeID"  );
    name.push_back( "MuSmeMS"  );
    name.push_back( "MuScale"  );
    name.push_back( "MuSagRho" );
    name.push_back( "MuSagRes" );
    name.push_back( "ElSme"    );
    name.push_back( "ElScale"  );
  }
  else if(lfvType==2){
    //sysVar.push_back( "ElSme_SysUp"    );
    //sysVar.push_back( "ElScale_SysUp"  );
    //sysVar.push_back( "TaSme_SysUp"    );
    //sysVar.push_back( "TaSmeDet_SysUp" );
    //sysVar.push_back( "TaSmeMod_SysUp" );
    sysVar.push_back( "MetResPara"     );
    sysVar.push_back( "MetResPer"      );
    sysVar.push_back( "MetScl_SysUp"   );
    //sysVar.push_back( "MetScl_SysDown" );

    //name.push_back( "ElSme"      );
    //name.push_back( "ElScale"    );
    //name.push_back(  "TaSme"      );
    //name.push_back(  "TaSmeDet"   );
    //name.push_back(  "TaSmeMod"   );
    name.push_back(  "MetResPara" );
    name.push_back(  "MetResPer"  );
    name.push_back(  "MetScl"     );
  }
  else if(lfvType==3){
    //sysVar.push_back( "MuSmeID_SysUp"  );
    //sysVar.push_back( "MuSmeMS_SysUp"  );
    //sysVar.push_back( "MuScale_SysUp"  );
    //sysVar.push_back( "MuSagRho_SysUp" );
    //sysVar.push_back( "MuSagRes_SysUp" );
    //sysVar.push_back( "TaSme_SysUp"    );
    //sysVar.push_back( "TaSmeDet_SysUp" );
    //sysVar.push_back( "TaSmeMod_SysUp" );
    sysVar.push_back( "MetResPara"     );
    sysVar.push_back( "MetResPer"      );
    sysVar.push_back( "MetScl_SysUp"   );

    //name.push_back( "MuSmeID"    );
    //name.push_back( "MuSmeMS"    );
    //name.push_back( "MuScale"    );
    //name.push_back( "MuSagRho"   );
    //name.push_back( "MuSagRes"   );
    //name.push_back(  "TaSme"      );
    //name.push_back(  "TaSmeDet"   );
    //name.push_back(  "TaSmeMod"   );
    name.push_back(  "MetResPara" );
    name.push_back(  "MetResPer"  );
    name.push_back(  "MetScl"     );
  }
  
}

void SetHistoStyle(TH1F* hV, int i, double Xmin, bool normalize, bool forceStyle){

  Double_t yMin = 0.000005, yMax= 9000000;
  if(normalize) yMax= 1000;

  hV->SetLineWidth(2);
  if(forceStyle)
    hV->SetLineStyle(1);
  else
    hV->SetLineStyle(Lin.at(i));
  hV->SetLineColor(Cols.at(i));
  hV->GetYaxis()->SetTitleOffset(1.50);
  hV->GetYaxis()->SetTitle("Events");
  //hV->GetYaxis()->CenterTitle(kTRUE);
  hV->GetYaxis()->SetRangeUser(yMin,yMax);
  hV->GetXaxis()->SetMoreLogLabels(kTRUE);
  hV->GetXaxis()->SetNoExponent(kTRUE);
  hV->GetXaxis()->SetRangeUser(Xmin,10000);
  
}

void SetRatioPlot(TH1F *ratio, int i, double Xmin){

  ratio->GetYaxis()->SetTitle("Ratio");
  ratio->GetXaxis()->SetTitleOffset(1.20);
  ratio->GetYaxis()->CenterTitle(kTRUE);
  ratio->GetYaxis()->SetNdivisions(507);
  ratio->GetXaxis()->SetMoreLogLabels(kTRUE);
  ratio->GetXaxis()->SetNoExponent(kTRUE);
  ratio->SetLineColor(Cols.at(i));
  ratio->GetXaxis()->SetLabelSize(0.08);
  ratio->GetYaxis()->SetLabelSize(0.07);
  ratio->GetXaxis()->SetTitleSize(0.10);
  ratio->GetYaxis()->SetTitleSize(0.08);
  ratio->GetYaxis()->SetTitleOffset(0.55);
  ratio->GetYaxis()->SetRangeUser(0.5,1.5);
  ratio->GetXaxis()->SetRangeUser(Xmin,10000);
  
}


void SigDistro(int LFVtype, bool useBjet, bool normalize){

  SetATLASStyle();
  TH1::SetDefaultSumw2(kTRUE);

  std::string lfvType = "";
  if(LFVtype==1)      { lfvType="emu";   }
  else if(LFVtype==2) { lfvType="etau";  }
  else if(LFVtype==3) { lfvType="mutau"; }
  
  std::cout << "< SigDistro() >:: Making Signal Distributions for Channel "
	    << lfvType << std::endl;

  std::cout << "useBjet" << useBjet << std::endl;
  std::string Dir = "";
  if(useBjet){ Dir += "Bjet/";   }
  else{        Dir += "NoBjet/"; }

  dist = new TFile( (Dir+"Plots_Nominal_"+lfvType+"_Signals.root").c_str() );
  
  /* Zprime */
  TH1F *Zp1tev = (TH1F*)dist->Get( "hmllCorr_Zprime1000" );
  TH1F *Zp2tev = (TH1F*)dist->Get( "hmllCorr_Zprime2000" );
  TH1F *Zp3tev = (TH1F*)dist->Get( "hmllCorr_Zprime3000" );
  TH1F *Zp4tev = (TH1F*)dist->Get( "hmllCorr_Zprime4000" );
  TH1F *Zp5tev = (TH1F*)dist->Get( "hmllCorr_Zprime5000" );
  /* QBH */
  TH1F *Qbh1tev = (TH1F*)dist->Get( "hmllCorr_QBH1000_n1" );
  TH1F *Qbh2tev = (TH1F*)dist->Get( "hmllCorr_QBH2000_n1" );
  TH1F *Qbh3tev = (TH1F*)dist->Get( "hmllCorr_QBH3000_n1" );
  TH1F *Qbh4tev = (TH1F*)dist->Get( "hmllCorr_QBH4000_n1" );
  TH1F *Qbh5tev = (TH1F*)dist->Get( "hmllCorr_QBH5000_n1" );
  /* SVT */
  TH1F *Svt1tev = (TH1F*)dist->Get( "hmllCorr_SVT1000" );
  TH1F *Svt2tev = (TH1F*)dist->Get( "hmllCorr_SVT2000" );
  TH1F *Svt3tev = (TH1F*)dist->Get( "hmllCorr_SVT3000" );
  TH1F *Svt4tev = (TH1F*)dist->Get( "hmllCorr_SVT4000" );
  TH1F *Svt5tev = (TH1F*)dist->Get( "hmllCorr_SVT5000" );

  std::vector<std::string> Mass;
  Mass.push_back( "1 TeV" );
  Mass.push_back( "2 TeV" );
  Mass.push_back( "3 TeV" );
  Mass.push_back( "4 TeV" );
  Mass.push_back( "5 TeV" );

  std::vector<TH1F*> Zp, Qbh, Svt;
  Zp.push_back(Zp1tev);  Qbh.push_back(Qbh1tev);  Svt.push_back(Svt1tev);
  Zp.push_back(Zp2tev);	 Qbh.push_back(Qbh2tev);  Svt.push_back(Svt2tev);
  Zp.push_back(Zp3tev);	 Qbh.push_back(Qbh3tev);  Svt.push_back(Svt3tev);
  Zp.push_back(Zp4tev);	 Qbh.push_back(Qbh4tev);  Svt.push_back(Svt4tev);
  Zp.push_back(Zp5tev);	 Qbh.push_back(Qbh5tev);  Svt.push_back(Svt5tev);

  /* Draw Zprime */
  TCanvas *Zprime = CreateCanvas("Zprime");
  Zprime->cd();
  Zprime->SetLogx();
  Zprime->SetLogy();

  TLegend *lZp = CreateLegend();//0.634,0.638,0.976,937);
  for(uint i=0; i<Zp.size(); i++){
    if(normalize) Zp.at(i)->Scale( 1/Zp.at(i)->Integral() );
    SetHistoStyle(Zp.at(i),i,200,normalize);
    if(i==0) Zp.at(i)->Draw("hist");
    else Zp.at(i)->Draw("histsame");
    lZp->AddEntry( Zp.at(i), ("LFV Z' "+Mass.at(i)).c_str(), "l" );
  }
  lZp->Draw();
  DrawLabels(false,true,false,true,false,false,normalize);
  DrawChannel(lfvType,false,useBjet);

  /* Draw QBH */
  TCanvas *QBH = CreateCanvas("QBH");
  QBH->cd();
  QBH->SetLogx();
  QBH->SetLogy();
  
  TLegend *lQbh = CreateLegend();//0.608,0.622,0.960,0.932);
  for(uint i=0; i<Qbh.size(); i++){
    if(normalize) Qbh.at(i)->Scale( 1/Qbh.at(i)->Integral() );
    SetHistoStyle(Qbh.at(i),i,750,normalize);
    if(i==0) Qbh.at(i)->Draw("hist");
    else Qbh.at(i)->Draw("histsame");
    lQbh->AddEntry( Qbh.at(i), ("QBH RS "+Mass.at(i)).c_str(), "l" );
  }
  lQbh->Draw();
  DrawLabels(false,true,false,true,false,false,normalize);
  DrawChannel(lfvType,false,useBjet);
  
  /* Draw SVT */
  TCanvas *SVT = CreateCanvas("SVT");
  SVT->cd();
  SVT->SetLogx();
  SVT->SetLogy();
  
  TLegend *lSvt = CreateLegend();//0.594,0.655,0.896,0.916);
  for(uint i=0; i<Svt.size(); i++){
    if(normalize) Svt.at(i)->Scale( 1/Svt.at(i)->Integral() );
    SetHistoStyle(Svt.at(i),i,450,normalize);
    if(i==0) Svt.at(i)->Draw("hist");
    else Svt.at(i)->Draw("histsame");
    lSvt->AddEntry( Svt.at(i), ("RPV #tilde{#nu_{#tau}} "+Mass.at(i)).c_str(), "l" );
  }
  lSvt->Draw();
  DrawLabels(false,true,false,true,false,false,normalize);
  DrawChannel(lfvType,false,useBjet);

}

void SigSysDistro(int LFVtype, bool useBjet, bool normalize, std::string model){

  SetATLASStyle();
  TH1::SetDefaultSumw2(kTRUE);

  std::string lfvType = "";
  if(LFVtype==1)      { lfvType="emu";   }
  else if(LFVtype==2) { lfvType="etau";  }
  else if(LFVtype==3) { lfvType="mutau"; }
  
  std::cout << "< SigDistro() >:: Making Nominal vs SysVar Signal Distributions"
	    << " for Channel " << lfvType << std::endl;
  
  std::string Dir = "";
  if(useBjet){ Dir += "Bjet/";   }
  else{        Dir += "NoBjet/"; }

  if(m_debug)
    std::cout << "< SigDistro::SigSysDistro() > :: Dir = "<< Dir << std::endl;

  dist = new TFile( (Dir+"SignalShapes_"+lfvType+".root").c_str() );
  std::vector<TH1F*> Histos = GetHistos(model,LFVtype);
  std::vector<TH1F*> Ratios;
  for(uint i=1; i<Histos.size(); i++){
    Ratios.push_back( MakeRatio(Histos.at(0),Histos.at(i)) );
  }
  
  TCanvas *cs = CreateCanvas(model);
  TPad *p1 = CreateTopPad(model,"mll");
  TPad *p2 = CreateBottomPad(model,"mll");

  cs->cd();
  p1->Draw();  
  p2->Draw();

  p1->cd();

  Double_t Xmin = 0;
  if(model.find("Zprime")!=std::string::npos)   Xmin = 200;
  else if(model.find("QBH")!=std::string::npos) Xmin = 750;
  else if(model.find("SVT")!=std::string::npos) Xmin = 450;

  TLegend *leg = NULL;
  if(LFVtype==1)      leg = CreateLegend(0.56,0.55,0.91,0.91);
  else if(LFVtype==2) leg = CreateLegend(0.56,0.55,0.91,0.91);
  else if(LFVtype==3) leg = CreateLegend(0.56,0.55,0.91,0.91);
  for(uint i=0; i<Histos.size(); i++){
    if(normalize) Histos.at(i)->Scale( 1/Histos.at(i)->Integral() );
    SetHistoStyle(Histos.at(i),i,Xmin,normalize,true);
    if(i==0) Histos.at(i)->Draw("hist");
    else Histos.at(i)->Draw("histsame");
    leg->AddEntry( Histos.at(i), name.at(i).c_str(), "l" );
  }
  leg->Draw();
  DrawLabels(true,true,false,false,false,false,normalize);
  DrawChannel(lfvType,true,useBjet);

  p2->cd();
  for(uint i=1; i<Ratios.size(); i++){
    SetRatioPlot(Ratios.at(i),i,Xmin);
    if(i==1) Ratios.at(i)->Draw("hist");
    else Ratios.at(i)->Draw("histsame");
  }
  
  //cs->SaveAs( ("Plots/SigDistro/"+lfvType+"_"+model+"_Sys.pdf").c_str() );
  
}

std::vector<TH1F*> GetHistos(std::string Mp, int lfvType){

  if(m_debug)
    std::cout << "< SigDistro::GetHisto() >:: retrieving histograms" << std::endl;
  TH1F* h = NULL;
  std::vector<TH1F*> plots;
  for(uint i=0; i<sysVar.size(); i++){
    h = (TH1F*)dist->Get( (Mp+"_"+sysVar.at(i)).c_str() );
    plots.push_back(h);
  }
  return plots;
  
}

TH1F* MakeRatio(TH1F *Nom, TH1F* Var){

  if(m_debug)
    std::cout << "< SigDistro::MakeRatio() >:: making sysVar/Nom ratio" << std::endl;
  TH1F* ratio = (TH1F*)Nom->Clone("ratio");
  ratio->Reset();
  ratio->Divide(Var,Nom);

  return ratio;
  
}
