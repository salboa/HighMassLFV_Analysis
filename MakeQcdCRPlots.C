#include <TH1F.h>
#include <THStack.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TROOT.h>
#include "iostream"
#include "sstream"
#include "iomanip"
#include "vector"
#include "ATLASstyle.C"

void MakeQcdCRPlots(std::string lfvType,
		    std::string Htype,
		    std::string charge,
		    std::string Reg,
		    bool isFFcat,
		    bool useBjet){
  
  SetATLASStyle();
  TH1::SetDefaultSumw2(kTRUE);
  
  std::string Dir = "";
  if(useBjet){ Dir += "Bjet/";   }
  else{        Dir += "NoBjet/"; }

  Dir += "Qcd"+Reg;

  std::string Suff1="", Suff2="", Suff3="";
  if(charge==""){
    Suff1="_SS"; Suff2=""; Suff3="_SS";
  }
  else if(charge=="SS"){
    Suff1="_OS"; Suff2="_SS"; Suff3="_OS";
  }
  else if(charge=="OS"){
    Suff1="_SS"; Suff2="_OS"; Suff3="_SS";
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
  TH1F *dummy    = (TH1F*)Top->Clone("dummy");
  dummy->Reset();

  THStack *hs = new THStack("hs","");

  /* Set Axis Title */
  std::ostringstream sstream;
  sstream << std::setprecision(2) << Top->GetBinWidth(2);
  std::string Bsize = sstream.str();
  if(Htype.find("pt")!=std::string::npos || Htype=="njet" ||
     Htype.find("mll")!=std::string::npos )
    dummy->GetYaxis()->SetTitle( "Events" );
  else if( (Htype.find("met")!=std::string::npos) ){
    dummy->GetYaxis()->SetTitle( ("Events / "+Bsize+" GeV").c_str() );
  }
  else
    dummy->GetYaxis()->SetTitle( ("Events / "+Bsize).c_str() );

  Double_t Xmin=120, Xmax = 3000;
  if(Reg=="Reg3")
    Xmax=5000;
  dummy->GetXaxis()->SetRangeUser(Xmin,Xmax);
  dummy->GetYaxis()->SetRangeUser(0.005,90000000);
  dummy->GetYaxis()->SetTitleSize(0.06);
  dummy->GetYaxis()->SetLabelSize(0.05);
  dummy->GetYaxis()->SetTitleOffset(1.00);
  
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
  std::cout << " Top     = " << Plots.at(1)->Integral()<<std::endl;
  std::cout << " Db      = " << Plots.at(2)->Integral()<<std::endl;
  std::cout << " DY      = " << Plots.at(3)->Integral()<<std::endl;
  std::cout << " Wj      = " << Plots.at(4)->Integral()<<std::endl;
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
  TPad* p1 = new TPad("p1","p1",0.01,0.35,0.99,0.99);
  p1->Draw();
  p1->SetBottomMargin(0.00);

  TPad* p2 = new TPad("p2","p2",0.01,0.01,0.99,0.35);
  p2->Draw();
  p2->SetTopMargin(0.00);
  p2->SetBottomMargin(0.30);
  
  p1->cd();
  p1->SetLogy();
  if(Htype.find("mll")!=std::string::npos)
    p1->SetLogx();
  
  dummy->Draw();
  hs->Draw("HISTsame");
  hs->GetYaxis()->CenterTitle(kTRUE);
  hs->GetYaxis()->SetTitleSize(0.05);
  hs->GetYaxis()->SetTitleOffset(1.20);
  hs->GetYaxis()->SetTitle( "Events" );
  Plots.at(0)->Draw("pEsame");
  gPad->RedrawAxis();
   
  TLegend *leg = new TLegend(0.59,0.60,0.99,0.91);
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

  DrawLabels(true);
  DrawChannel(lfvType,true);
  
  p2->cd();
  p2->SetGridy();
  p2->SetLogx();
  ratioLine->Draw("hist");
  ratio->Draw("pE0same");
  
}

std::vector<TH1F*> RetriveHistos(std::string lfvType, std::string Htype,
				 std::string Fname){

  TFile *InF    = new TFile( (Fname+"Plots_Nominal_"+lfvType+".root").c_str() );
  TH1F *data_r1 = (TH1F*)InF->Get( ("h"+Htype+"_data").c_str()    );
  TH1F *Top_r1  = (TH1F*)InF->Get( ("h"+Htype+"_Top").c_str()     );
  TH1F *DB_r1   = (TH1F*)InF->Get( ("h"+Htype+"_DiBoson").c_str() );
  TH1F *DY_r1   = (TH1F*)InF->Get( ("h"+Htype+"_DY").c_str()      );
  TH1F *Wj_r1   = (TH1F*)InF->Get( ("h"+Htype+"_Wjets").c_str()   );

  
}

void MakeQcdCKfactor(std::string lfvType,
		     std::string Htype,
		     bool isFFcat,
		     bool useBjet){
  
  SetATLASStyle();
  TH1::SetDefaultSumw2(kTRUE);
  
  std::string Dir = "";
  if(useBjet){ Dir += "Bjet/";   }
  else{        Dir += "NoBjet/"; }

  std::string nR1_SS = Dir+"QcdReg1_SS";
  std::string nR1_OS = Dir+"QcdReg1_OS";
  std::string nR2_SS = Dir+"QcdReg2_SS";
  std::string nR2_OS = Dir+"QcdReg2_OS";

  if(isFFcat){
    nR1_SS += "/";  nR2_SS += "/";
    nR1_OS += "/";  nR2_OS += "/";
  }
  else{
    nR1_SS += "/LepFake/";  nR2_SS += "/LepFake/";
    nR1_OS += "/LepFake/";  nR2_OS += "/LepFake/";
  }
  
  TFile *InReg1 = new TFile( (nR1_SS+"Plots_Nominal_"+lfvType+".root").c_str() );
  TH1F *data_r1 = (TH1F*)InReg1->Get( ("h"+Htype+"_data").c_str()    );
  TH1F *Top_r1  = (TH1F*)InReg1->Get( ("h"+Htype+"_Top").c_str()     );
  TH1F *DB_r1   = (TH1F*)InReg1->Get( ("h"+Htype+"_DiBoson").c_str() );
  TH1F *DY_r1   = (TH1F*)InReg1->Get( ("h"+Htype+"_DY").c_str()      );
  TH1F *Wjet_r1 = (TH1F*)InReg1->Get( ("h"+Htype+"_Wjets").c_str()   );

  TFile *InReg2 = new TFile( (nR2+"Plots_Nominal_"+lfvType+".root").c_str() );
  TH1F *data_r2 = (TH1F*)InReg2->Get( ("h"+Htype+"_data").c_str()    );
  TH1F *Top_r2  = (TH1F*)InReg2->Get( ("h"+Htype+"_Top").c_str()     );
  TH1F *DB_r2   = (TH1F*)InReg2->Get( ("h"+Htype+"_DiBoson").c_str() );
  TH1F *DY_r2   = (TH1F*)InReg2->Get( ("h"+Htype+"_DY").c_str()      );
  TH1F *Wjet_r2 = (TH1F*)InReg2->Get( ("h"+Htype+"_Wjets").c_str()   );

  TH1F *mjReg1  = (TH1F*)Top_r1->Clone("mjReg1");
  TH1F *mjReg2  = (TH1F*)Top_r2->Clone("mjReg2");
  mjReg1->Reset();  mjReg2->Reset();

  TH1F *dummy   = (TH1F*)Top_r1->Clone("dummy");
  dummy->Reset();
  
  mjReg1->Add(data_r1);
  mjReg1->Add(Top_r1,-1);
  mjReg1->Add(DB_r1,-1);
  mjReg1->Add(DY_r1,-1);
  mjReg1->Add(Wjet_r1,-1);

  mjReg2->Add(data_r2);
  mjReg2->Add(Top_r2,-1);
  mjReg2->Add(DB_r2,-1);
  mjReg2->Add(DY_r2,-1);
  mjReg2->Add(Wjet_r2,-1);

  std::cout << " Multijet Region 1 ... " << std::endl;
  for(int b=1; b<mjReg1->GetNbinsX()+1; b++){
    double c = mjReg1->GetBinContent(b);
    double e = mjReg1->GetBinError(b);
    std::cout << " Bin = " << b << " -> Content = " << c
	      << " Error = " << e << std::endl;
  }

  std::cout << "" << std::endl;
  std::cout << " Multijet Region 2 ... " << std::endl;
  for(int b=1; b<mjReg2->GetNbinsX()+1; b++){
    double c = mjReg2->GetBinContent(b);
    double e = mjReg2->GetBinError(b);
    std::cout << " Bin = " << b << " -> Content = " << c
	      << " Error = " << e << std::endl;
  }

  /* Set Axis Title */
  std::ostringstream sstream;
  sstream << std::setprecision(2) << Top_r1->GetBinWidth(2);
  std::string Bsize = sstream.str();
  if(Htype.find("pt")!=std::string::npos || Htype=="njet" ||
     Htype.find("mll")!=std::string::npos )
    dummy->GetYaxis()->SetTitle( "Events" );
  else if( (Htype.find("met")!=std::string::npos) ){
    dummy->GetYaxis()->SetTitle( ("Events / "+Bsize+" GeV").c_str() );
  }
  else
    dummy->GetYaxis()->SetTitle( ("Events / "+Bsize).c_str() );

  Double_t Xmin=120, Xmax = 3000;
  dummy->GetXaxis()->SetRangeUser(Xmin,Xmax);
  dummy->GetYaxis()->SetRangeUser(0.005,90000000);
  dummy->GetYaxis()->SetTitleSize(0.06);
  dummy->GetYaxis()->SetLabelSize(0.05);
  dummy->GetYaxis()->SetTitleOffset(1.00);
  
  mjReg2->SetLineColor(kBlack);
  mjReg1->SetLineColor(kRed);
  
  std::cout << " Region 1: " << std::endl;
  std::cout << "    Data    = " << data_r1 -> Integral() << std::endl;
  std::cout << "    Top     = " << Top_r1  -> Integral() << std::endl;
  std::cout << "    Db      = " << DB_r1   -> Integral() << std::endl;
  std::cout << "    DY      = " << DY_r1   -> Integral() << std::endl;
  std::cout << "    Wj      = " << Wjet_r1 -> Integral() << std::endl;
  std::cout << "    Data-MC = " << mjReg1  -> Integral() << std::endl;

  std::cout << " Region 2: " << std::endl;
  std::cout << "    Data    = " << data_r2 -> Integral() << std::endl;
  std::cout << "    Top     = " << Top_r2  -> Integral() << std::endl;
  std::cout << "    Db      = " << DB_r2   -> Integral() << std::endl;
  std::cout << "    DY      = " << DY_r2   -> Integral() << std::endl;
  std::cout << "    Wj      = " << Wjet_r2 -> Integral() << std::endl;
  std::cout << "    Data-MC = " << mjReg2  -> Integral() << std::endl;

  TH1F *ratio   = (TH1F*)Top_r1->Clone("ratio");
  ratio->Reset();
  ratio->GetXaxis()->SetTitle(Top_r1->GetXaxis()->GetTitle());
  
  TH1F *ratioLine = (TH1F*)ratio->Clone("ratioLine");
  for (int k=-1; k<ratioLine->GetNbinsX()+1; k++){
    ratioLine->SetBinContent(k,1.);
  }
  ratio->Divide(mjReg2,mjReg1);
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
  TPad* p1 = new TPad("p1","p1",0.01,0.35,0.99,0.99);
  p1->Draw();
  p1->SetBottomMargin(0.00);

  TPad* p2 = new TPad("p2","p2",0.01,0.01,0.99,0.35);
  p2->Draw();
  p2->SetTopMargin(0.00);
  p2->SetBottomMargin(0.30);
  
  p1->cd();
  p1->SetLogy();
  if(Htype.find("mll")!=std::string::npos)
    p1->SetLogx();
  
  dummy->Draw();
  mjReg2->Draw("histsame");
  mjReg1->Draw("histsame");
  gPad->RedrawAxis();
   
  TLegend *leg = new TLegend(0.56,0.59,0.91,0.90);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->AddEntry(mjReg2,("Multijet - Reg2 ("+charge+")").c_str(),"l");
  leg->AddEntry(mjReg1,("Multijet - Reg1("+charge+")").c_str(),"l");
  leg->AddEntry(ratio,"k_{Multijet}","lpe");
  leg->Draw();

  DrawLabels(true);
  DrawChannel(lfvType,true);
  
  p2->cd();
  p2->SetGridy();
  p2->SetLogx();
  ratioLine->Draw("hist");
  ratio->Draw("pEsame");
  
}
