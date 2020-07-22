/* program includes */
#include "DrawLFVxsec.h"
#include "ATLASstyle.C"

int main( int argc, char* argv[] ) {

  bool useGUI    = false;
  bool debug     = false;
  bool printHelp = false;
  for(int i = 1; i < argc; ++i){
    if( !strcmp(argv[i],"--useGUI")     ){ useGUI    = true; }
    else if( !strcmp(argv[i],"--debug") ){ debug     = true; }
    else if( !strcmp(argv[i],"--help")  ){ printHelp = true; }
    else{
      if(std::string(argv[i]).find("--")!=std::string::npos)
	std::cout << "WARNING:: Option " << argv[i] << " not recognized: "
		  << "skipping!" << std::endl;
    }
  }
  if(printHelp){
    std::cout << " DrawLFVxsec: make xsec plots! "    << std::endl;
    std::cout << "                 Options: "                     << std::endl;
    std::cout << "                  --useGUI   [Enable GUI mode:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                  --debug    [Enable debug]"    << std::endl;
    std::cout << "                  --help     [Print this help]" << std::endl;
    exit(0);
  }

  std::cout << "< DrawLFVxsec() >:: Options set " << std::endl;
  std::cout << "                       useGUI  = " << useGUI    << std::endl;
  std::cout << "                       debug   = " << debug     << std::endl;

  m_debug = debug;

  TRint *myApp = new TRint("RootSession",&argc,argv,NULL,0);
  DrawLFVxsec();

  if(useGUI){
    std::cout << "< DrawLFVxsec() >:: using Rint -> ROOT will remain "
	      << "opened ... " << std::endl;
    myApp->Run();
  }

  return 0;
  
}

void DrawLFVxsec(){

  SetATLASStyle();

  std::string OutDir = "Plots/Theory/";
  TFile *kfac_F = new TFile( "VarInputs/kFactor_RPV_SUSY_svt.root" );
  TF1   *kfac   = (TF1*)kfac_F->Get( "kfactor_RPV" );
  
  double fb = 1000.;

  std::vector<double> Zp_mass;
  Zp_mass.push_back( 500 );
  Zp_mass.push_back( 600 );
  Zp_mass.push_back( 700 );
  Zp_mass.push_back( 800 );
  Zp_mass.push_back( 900 );
  Zp_mass.push_back( 1000 );
  Zp_mass.push_back( 1100 );
  Zp_mass.push_back( 1200 );
  Zp_mass.push_back( 1300 );
  Zp_mass.push_back( 1400 );
  Zp_mass.push_back( 1500 );
  Zp_mass.push_back( 1600 );
  Zp_mass.push_back( 1700 );
  Zp_mass.push_back( 1800 );
  Zp_mass.push_back( 1900 );
  Zp_mass.push_back( 2000 );
  Zp_mass.push_back( 2200 );
  Zp_mass.push_back( 2400 );
  Zp_mass.push_back( 2600 );
  Zp_mass.push_back( 2800 );
  Zp_mass.push_back( 3000 );
  Zp_mass.push_back( 3500 );
  Zp_mass.push_back( 4000 );
  Zp_mass.push_back( 4500 );
  Zp_mass.push_back( 5000 );
  
  std::vector<double> Zp_xsec;
  Zp_xsec.push_back( 11.428     * fb * 1.3595  );
  Zp_xsec.push_back( 5.8245     * fb * 1.3708  );
  Zp_xsec.push_back( 3.2385     * fb * 1.38144 );
  Zp_xsec.push_back( 1.9063     * fb * 1.39284 );
  Zp_xsec.push_back( 1.1865     * fb * 1.40227 );
  Zp_xsec.push_back( 0.77863    * fb * 1.41101 );
  Zp_xsec.push_back( 0.51843    * fb * 1.41884 );
  Zp_xsec.push_back( 0.35695    * fb * 1.42543 );
  Zp_xsec.push_back( 0.25045    * fb * 1.43061 );
  Zp_xsec.push_back( 0.17783    * fb * 1.43428 );
  Zp_xsec.push_back( 0.12975    * fb * 1.43644 );
  Zp_xsec.push_back( 0.095508   * fb * 1.43711 );
  Zp_xsec.push_back( 0.071173   * fb * 1.43656 );
  Zp_xsec.push_back( 0.054205   * fb * 1.43508 );
  Zp_xsec.push_back( 0.040973   * fb * 1.43272 );
  Zp_xsec.push_back( 0.031493   * fb * 1.4293  );
  Zp_xsec.push_back( 0.018915   * fb * 1.41906 );
  Zp_xsec.push_back( 0.011765   * fb * 1.40535 );
  Zp_xsec.push_back( 0.00752    * fb * 1.38819 );
  Zp_xsec.push_back( 0.004826   * fb * 1.36835 );
  Zp_xsec.push_back( 0.0031915  * fb * 1.347   );
  Zp_xsec.push_back( 0.0011935  * fb * 1.28844 );
  Zp_xsec.push_back( 0.00049213 * fb * 1.22345 );
  Zp_xsec.push_back( 0.00022248 * fb * 1.15531 );
  Zp_xsec.push_back( 0.00011163 * fb * 1.08168 );

  std::vector<double> QBH_ADD_m, QBH_RS_m;
  QBH_ADD_m.push_back( 3000 );
  QBH_ADD_m.push_back( 3500 );
  QBH_ADD_m.push_back( 4000 );
  QBH_ADD_m.push_back( 4500 );
  QBH_ADD_m.push_back( 5000 );
  QBH_ADD_m.push_back( 5500 );
  QBH_ADD_m.push_back( 6000 );
  QBH_ADD_m.push_back( 6500 );
  QBH_ADD_m.push_back( 7000 );
  QBH_ADD_m.push_back( 7500 );
  QBH_ADD_m.push_back( 8000 );
  
  QBH_RS_m.push_back( 1000 );
  QBH_RS_m.push_back( 1500 );
  QBH_RS_m.push_back( 2000 );
  QBH_RS_m.push_back( 2500 );
  QBH_RS_m.push_back( 3000 );
  QBH_RS_m.push_back( 3500 );
  QBH_RS_m.push_back( 4000 );
  QBH_RS_m.push_back( 4500 );
  QBH_RS_m.push_back( 5000 );
  QBH_RS_m.push_back( 5500 );
  QBH_RS_m.push_back( 6000 );

  std::vector<double> QBH_ADD_xsec, QBH_RS_xsec;
  QBH_ADD_xsec.push_back( 0.109*fb );
  QBH_ADD_xsec.push_back( 0.0297*fb );
  QBH_ADD_xsec.push_back( 0.00839*fb );
  QBH_ADD_xsec.push_back( 0.00244*fb );
  QBH_ADD_xsec.push_back( 0.000708*fb );
  QBH_ADD_xsec.push_back( 0.000205*fb );
  QBH_ADD_xsec.push_back( 5.74e-05*fb );
  QBH_ADD_xsec.push_back( 1.59e-05*fb );
  QBH_ADD_xsec.push_back( 4.17e-06*fb );
  QBH_ADD_xsec.push_back( 1.04e-06*fb );
  QBH_ADD_xsec.push_back( 2.47e-07*fb );
  
  QBH_RS_xsec.push_back( 0.543*fb );
  QBH_RS_xsec.push_back( 0.0566*fb );
  QBH_RS_xsec.push_back( 0.00927*fb );
  QBH_RS_xsec.push_back( 0.00192*fb );
  QBH_RS_xsec.push_back( 0.000451*fb );
  QBH_RS_xsec.push_back( 0.000118*fb );
  QBH_RS_xsec.push_back( 3.17e-05*fb );
  QBH_RS_xsec.push_back( 8.71e-06*fb );
  QBH_RS_xsec.push_back( 2.44e-06*fb );
  QBH_RS_xsec.push_back( 6.84e-07*fb );
  QBH_RS_xsec.push_back( 1.87e-07*fb );


  std::vector<double> Svt_mass;
  Svt_mass.push_back(  500 );
  Svt_mass.push_back(  600 );
  Svt_mass.push_back(  700 );
  Svt_mass.push_back(  800 );
  Svt_mass.push_back(  900 );
  Svt_mass.push_back( 1000 );
  Svt_mass.push_back( 1100 );
  Svt_mass.push_back( 1200 );
  Svt_mass.push_back( 1300 );
  Svt_mass.push_back( 1400 );
  Svt_mass.push_back( 1500 );
  Svt_mass.push_back( 1600 );
  Svt_mass.push_back( 1700 );
  Svt_mass.push_back( 1800 );
  Svt_mass.push_back( 1900 );
  Svt_mass.push_back( 2000 );
  Svt_mass.push_back( 2200 );
  Svt_mass.push_back( 2400 );
  Svt_mass.push_back( 2600 );
  Svt_mass.push_back( 2800 );
  Svt_mass.push_back( 3000 );
  Svt_mass.push_back( 3500 );
  Svt_mass.push_back( 4000 );
  Svt_mass.push_back( 4500 );
  Svt_mass.push_back( 5000 );
  
  std::vector<double> Svt_xsec;
  Svt_xsec.push_back( 1.8933     * fb * kfac->Eval(500)  );
  Svt_xsec.push_back( 0.96525    * fb * kfac->Eval(600)  );
  Svt_xsec.push_back( 0.53705    * fb * kfac->Eval(700)  );
  Svt_xsec.push_back( 0.3181     * fb * kfac->Eval(800)  );
  Svt_xsec.push_back( 0.19793    * fb * kfac->Eval(900)  );
  Svt_xsec.push_back( 0.12785    * fb * kfac->Eval(1000) );
  Svt_xsec.push_back( 0.08512    * fb * kfac->Eval(1100) );
  Svt_xsec.push_back( 0.058123   * fb * kfac->Eval(1200) );
  Svt_xsec.push_back( 0.040528   * fb * kfac->Eval(1300) );
  Svt_xsec.push_back( 0.02875    * fb * kfac->Eval(1400) );
  Svt_xsec.push_back( 0.02072    * fb * kfac->Eval(1500) );
  Svt_xsec.push_back( 0.01513    * fb * kfac->Eval(1600) );
  Svt_xsec.push_back( 0.011168   * fb * kfac->Eval(1700) );
  Svt_xsec.push_back( 0.0083273  * fb * kfac->Eval(1800) );
  Svt_xsec.push_back( 0.006263   * fb * kfac->Eval(1900) );
  Svt_xsec.push_back( 0.0047488  * fb * kfac->Eval(2000) );
  Svt_xsec.push_back( 0.0027918  * fb * kfac->Eval(2200) );
  Svt_xsec.push_back( 0.0016763  * fb * kfac->Eval(2400) );
  Svt_xsec.push_back( 0.001023   * fb * kfac->Eval(2600) );
  Svt_xsec.push_back( 0.0006332  * fb * kfac->Eval(2800) );
  Svt_xsec.push_back( 0.0003961  * fb * kfac->Eval(3000) );
  Svt_xsec.push_back( 0.00012675 * fb * kfac->Eval(3500) );
  Svt_xsec.push_back( 4.1785e-05 * fb * kfac->Eval(4000) );
  Svt_xsec.push_back( 1.3953e-05 * fb * kfac->Eval(4500) );
  Svt_xsec.push_back( 4.6825e-06 * fb * kfac->Eval(5000) );

  int NZp  = Zp_mass.size();
  int NQAp = QBH_ADD_m.size();
  int NQRp = QBH_RS_m.size();
  int NSvt = Svt_mass.size();
  Float_t Zpx[NZp]  , Zpy[NZp];
  Float_t QAx[NQAp] , QAy[NQAp];
  Float_t QRx[NQRp] , QRy[NQRp];
  Float_t Svtx[NSvt], Svty[NSvt];
  for(uint i=0; i<Zp_mass.size(); i++){
    Zpx[i] = Zp_mass.at(i)/1000.;
    Zpy[i] = Zp_xsec.at(i);
  }
  for(uint i=0; i<QBH_ADD_m.size(); i++){
    QAx[i] = QBH_ADD_m.at(i)/1000.;
    QAy[i] = QBH_ADD_xsec.at(i);
  }
  for(uint i=0; i<QBH_RS_m.size(); i++){
    QRx[i] = QBH_RS_m.at(i)/1000.;
    QRy[i] = QBH_RS_xsec.at(i);
  }
  for(uint i=0; i<Svt_mass.size(); i++){
    Svtx[i] = Svt_mass.at(i)/1000.;
    Svty[i] = Svt_xsec.at(i);
  }
  TH1F *Qbh      = new TH1F("Qbh","Qbh",10,0,10);
  TGraph *Zp     = new TGraph(NZp , Zpx , Zpy );
  TGraph *QbhADD = new TGraph(NQAp, QAx , QAy );
  TGraph *QbhRS  = new TGraph(NQRp, QRx , QRy );
  TGraph *Svt    = new TGraph(NSvt, Svtx, Svty);

  TCanvas *Czp = new TCanvas("Czp","Czp",0,0,600,600);
  Czp->cd();
  Czp->SetLogy(true);
  
  Zp->SetLineWidth(3);
  Zp->SetMarkerSize(1.0);
  Zp->SetLineColor(kRed);
  Zp->SetMarkerColor(kBlack);
  Zp->GetYaxis()->SetRangeUser(0.01,30000);
  Zp->GetYaxis()->SetTitleOffset(1.5 );
  Zp->GetYaxis()->SetTitle("#sigma#timesBR [fb]");
  Zp->GetXaxis()->SetTitle("Z' polemass [TeV]");
  Zp->Draw("ACp");

  TLegend *legzp = new TLegend(0.57,0.76,0.97,0.91);
  legzp->SetFillStyle(0);
  legzp->SetBorderSize(0);
  legzp->SetTextFont(42);
  legzp->AddEntry(Zp,"Z' #sqrt{s} = 13 TeV","pl");
  legzp->Draw();
  
  TLatex zp;
  zp.SetNDC();
  zp.SetTextFont(42);
  zp.SetTextColor(kBlack);
  zp.DrawLatex(0.63,0.75,"pp #rightarrow Z' #rightarrow l^{ #pm} l'^{ #mp}");

  Czp->SaveAs( (OutDir+"Zprime_xsec.pdf").c_str() );

  TCanvas *Cqbh = new TCanvas("Cqbh","Cqbh",0,0,600,600);
  Cqbh->cd();
  Cqbh->SetLogy(true);
  
  QbhADD->SetLineColor(kRed);
  QbhADD->SetLineWidth(3);
  QbhADD->SetMarkerSize(1.0);
  QbhADD->SetMarkerColor(kBlack);
  QbhRS->SetLineColor(kBlack);
  QbhRS->SetLineWidth(3);
  QbhRS->SetLineStyle(3);
  QbhRS->SetMarkerSize(1.0);
  QbhRS->SetMarkerStyle(22);
  QbhRS->SetMarkerColor(kBlack);
  QbhADD->GetYaxis()->SetTitle("#sigma#timesBR [fb]");
  QbhRS->GetYaxis()->SetTitle("#sigma#timesBR [fb]");
  QbhADD->GetXaxis()->SetTitle("M_{th} [TeV]");
  QbhRS->GetXaxis()->SetTitle("M_{th} [TeV]");
  QbhADD->GetYaxis()->SetRangeUser(0.0001,3500);
  QbhRS->GetYaxis()->SetRangeUser(0.0001,3500);
  Qbh->GetYaxis()->SetRangeUser(0.0001,3500);
  Qbh->GetXaxis()->SetTitle("M_{th} [TeV]");
  Qbh->GetYaxis()->SetTitle("#sigma#timesBR [fb]");
  Qbh->Draw();
  QbhRS->Draw("Cpsame");
  QbhADD->Draw("Cpsame");
  
  TLegend *legqbh = new TLegend(0.56,0.79,0.96,0.90);
  legqbh->SetFillStyle(0);
  legqbh->SetBorderSize(0);
  legqbh->SetTextFont(42);
  legqbh->AddEntry(QbhADD,"ADD #sqrt{s} = 13 TeV","pl");
  legqbh->AddEntry(QbhRS,"RS #sqrt{s} = 13 TeV","pl");
  legqbh->Draw();
  
  TLatex qb;
  qb.SetNDC();
  qb.SetTextFont(42);
  qb.SetTextColor(kBlack);
  qb.DrawLatex(0.60,0.70,"pp #rightarrow QBH #rightarrow l^{ #pm} l'^{ #mp}");

  Cqbh->SaveAs( (OutDir+"QBH_xsec.pdf").c_str() );

  TCanvas *Csvt = new TCanvas("Csvt","Csvt",0,0,600,600);
  Csvt->cd();
  Csvt->SetLogy(true);
  
  Svt->SetLineWidth(3);
  Svt->SetMarkerSize(1.0);
  Svt->SetLineColor(kRed);
  Svt->SetMarkerColor(kBlack);
  Svt->GetYaxis()->SetRangeUser(0.01,30000);
  Svt->GetYaxis()->SetTitleOffset(1.5 );
  Svt->GetYaxis()->SetTitle("#sigma#timesBR [fb]");
  Svt->GetXaxis()->SetTitle("#tilde{#nu}_{#tau} polemass [TeV]");
  Svt->Draw("ACp");

  TLegend *legsvt = new TLegend(0.57,0.76,0.97,0.91);
  legsvt->SetFillStyle(0);
  legsvt->SetBorderSize(0);
  legsvt->SetTextFont(42);
  legsvt->AddEntry(Zp,"RPV #sqrt{s} = 13 TeV","pl");
  legsvt->Draw();
  
  TLatex svt;
  svt.SetNDC();
  svt.SetTextFont(42);
  svt.SetTextColor(kBlack);
  svt.DrawLatex(0.63,0.75,"pp #rightarrow #tilde{#nu}_{#tau} #rightarrow l^{ #pm} l'^{ #mp}");

  Csvt->SaveAs( (OutDir+"RPV_xsec.pdf").c_str() );
  
}
