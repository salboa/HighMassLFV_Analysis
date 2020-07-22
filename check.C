#include "Utils.C"

void dr(){

  TFile *fp1  = new TFile("NoBjet/Plots_Nominal_etau_1p.root");
  TH1F  *hp1  = (TH1F*)fp1->Get("hmllCorr_qcd");
  TFile *fp3  = new TFile("NoBjet/Plots_Nominal_etau_3p.root");
  TH1F  *hp3  = (TH1F*)fp3->Get("hmllCorr_qcd");
  TFile *fall = new TFile("NoBjet/Plots_Nominal_etau.root");
  TH1F  *hall = (TH1F*)fall->Get("hmllCorr_qcd");
  
  TH1F *merge = (TH1F*)hp1->Clone("merged");
  merge->Add(hp3);

  merge->SetLineColor(kRed);
  hall->SetLineColor(kBlack);

  std::cout << merge->Integral() << std::endl;
  std::cout << hall->Integral() << std::endl;

  TH1F *ratio = (TH1F*)hp1->Clone("ratio");
  ratio->Reset();
  ratio->Divide(hall,merge);

  Double_t Xmin=120, Xmax = 3000;
  merge->GetXaxis()->SetRangeUser(Xmin,Xmax);
  merge->GetYaxis()->SetRangeUser(0.005,90000000);
  merge->GetYaxis()->SetTitleSize(0.06);
  merge->GetYaxis()->SetLabelSize(0.05);
  merge->GetYaxis()->SetTitleOffset(1.00);
  merge->GetXaxis()->SetMoreLogLabels(kTRUE);
  merge->GetXaxis()->SetNoExponent(kTRUE);

  ratio->GetXaxis()->SetRangeUser(Xmin,Xmax);
  ratio->GetYaxis()->SetRangeUser(0.45,1.55);
  
  TCanvas *cs = new TCanvas("cs","cs",0,0,600,600);
  cs->cd();
  TPad *p1 = new TPad("p1","p1",0.01,0.35,0.99,0.99);
  p1->Draw();
  p1->SetBottomMargin(0.00);
  
  TPad *p2 = new TPad("p2","p2",0.01,0.01,0.99,0.35);
  p2->Draw();
  p2->SetTopMargin(0.00);
  p2->SetBottomMargin(0.30);

  p1->cd();
  p1->SetLogy();
  p1->SetLogx();

  merge->Draw("hist");
  hall->Draw("histsame");

  p2->cd();
  ratio->Draw("Ep");
  
  
}
