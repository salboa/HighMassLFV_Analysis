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

void DrawLabels(bool hasRatio=false, bool isMC=false,   bool isConf=false,
		bool isPaper=false,  bool is2015=false, bool is2016=false){

  Double_t TextSize = 0.04;
  Double_t Pos = 0.30;
  if(hasRatio){
    TextSize = 0.05;
    Pos = 0.28;
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

  std::string Lumi = "36.2";
  if(is2015)     { Lumi = "3.2";  }
  else if(is2016){ Lumi = "33.0"; }

  lumi.DrawLatex(0.17,0.79, ("#sqrt{s} = 13 TeV, "+Lumi+" fb^{-1}").c_str() );
  AT.DrawLatex(0.17,0.86,"ATLAS");
  std::string lab = "";
  if(isMC){ lab += "Simulation"; }

  if(isConf){       lab += "Preliminary"; }
  else if(isPaper){ lab += "";            }
  else{             lab += "Internal";    }
  
  Lab.DrawLatex(Pos,0.86,lab.c_str());
  
}

void DrawChannel(std::string lfvType, bool hasRatio=false){

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
  Chan.DrawLatex(0.20,Pos, (chStr+" channel").c_str() );
  
}

