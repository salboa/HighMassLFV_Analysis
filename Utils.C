#include "Utils.h"

TCanvas *CreateCanvas(std::string name){

  TCanvas *cs = new TCanvas( ("cs_"+name).c_str(),
			     ("cs_"+name).c_str(),
			     0,0,600,600 );
  return cs;
  
}

TPad *CreateTopPad(std::string name, std::string Htype){

  TPad *p1 = new TPad( ("p1_"+name).c_str(),
		       ("p1_"+name).c_str(),
		       0.01,0.35,0.99,0.99 );

  p1->SetBottomMargin(0.00);
  p1->SetLogy();
  if(Htype.find("mll")!=std::string::npos)
    p1->SetLogx();
  
  return p1;
  
}

TPad *CreateBottomPad(std::string name, std::string Htype){

  TPad *p2 = new TPad( ("p2_"+name).c_str(),
		       ("p2_"+name).c_str(),
		       0.01,0.01,0.99,0.35 );

  p2->SetTopMargin(0.00);
  p2->SetBottomMargin(0.30);
  p2->SetGridy();
  if(Htype.find("mll")!=std::string::npos)
    p2->SetLogx();
  
  return p2;
  
}

TLegend *CreateLegend(Double_t v1=0.56, Double_t v2=0.59,
		      Double_t v3=0.91, Double_t v4=0.90){

  std::cout << "creating legend" << std::endl;
  TLegend *leg = new TLegend(v1,v2,v3,v4);
  std::cout << "legend created" << std::endl;
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);

  return leg;

}

void SetATLASStyle(bool useStat=false){
  
  TStyle *atlasStyle= new TStyle("ATLAS","Atlas style");
  
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
  if(useStat){
    atlasStyle->SetOptStat(1111);
    atlasStyle->SetOptFit(1111);
  }
  else{
    atlasStyle->SetOptStat(0);
    atlasStyle->SetOptFit(0);
  }

  /*put tick marks on top and RHS of plots*/
  atlasStyle->SetPadTickX(1);
  atlasStyle->SetPadTickY(1);

  gROOT->SetStyle("ATLAS");
  gROOT->ForceStyle();

}

void DrawLabels(bool hasRatio=false, bool isMC=false,
		bool isConf=false,   bool isPaper=false,
		bool is2015=false,   bool is2016=false,
		bool noLumi=false){

  Double_t TextSize = 0.04;
  Double_t Pos = 0.31;
  if(hasRatio){
    TextSize = 0.05;
    Pos = 0.29;
  }
  
  TLatex lumi;
  lumi.SetNDC();
  lumi.SetTextFont(42);
  lumi.SetTextSize(TextSize);
  lumi.SetTextColor(kBlack);
  
  TLatex AT;
  AT.SetNDC();
  AT.SetTextFont(72);
  AT.SetTextSize(TextSize);
  AT.SetTextColor(kBlack);

  TLatex Lab;
  Lab.SetNDC();
  Lab.SetTextFont(42);
  Lab.SetTextSize(TextSize);
  Lab.SetTextColor(kBlack);

  std::string Lumi = "36.1";
  if(is2015)     { Lumi = "3.2";  }
  else if(is2016){ Lumi = "32.9"; }

  std::string ecm  = "#sqrt{s} = 13 TeV";
  if(!noLumi) ecm += ", "+Lumi+" fb^{-1}";
  
  lumi.DrawLatex(0.18,0.79, ecm.c_str() );
  
  AT.DrawLatex(0.18,0.86,"ATLAS");
  std::string lab = "";
  if(isMC){ lab += "Simulation"; }

  if(isConf){       lab += " Preliminary"; }
  else if(isPaper){ lab += "";             }
  else{             lab += " Internal";    }
  
  Lab.DrawLatex(Pos,0.86,lab.c_str());
  
}

void DrawChannel(std::string lfvType, bool hasRatio=false, bool useBjet=false){

  Double_t TextSize = 0.04;
  Double_t Pos = 0.72;
  if(hasRatio){
    TextSize = 0.05;
    Pos = 0.69;
  }

  TLatex Chan;
  Chan.SetNDC();
  Chan.SetTextFont(42);
  Chan.SetTextSize(TextSize);
  Chan.SetTextColor(kBlack);
  
  std::string chStr = "";
  if(lfvType=="emu") chStr="e#mu";
  else if(lfvType=="etau") chStr="e#tau";
  else if(lfvType=="mutau") chStr="#mu#tau";
  if(useBjet)
    Chan.DrawLatex(0.21,Pos, (chStr+" channel (b-veto)").c_str() );
  else
    Chan.DrawLatex(0.21,Pos, (chStr+" channel").c_str() );
  
}
