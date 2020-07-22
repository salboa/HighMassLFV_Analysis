/* program includes */
#include "DataPeriodPlot.h"
#include "Utils.C"

int main( int argc, char* argv[] ) {

  bool useBjet   = false;
  int lfvType    = -1;
  bool useGUI    = false;
  bool divLumi   = false;
  bool debug     = false;
  bool printHelp = false;
  for(int i = 1; i < argc; ++i){
    if( !strcmp(argv[i],"--useBjet")      ){ useBjet = true; }
    else if( !strcmp(argv[i],"--lfvType") ){ lfvType = std::stoi(argv[i+1]); }
    else if( !strcmp(argv[i],"--useGUI")  ){ useGUI    = true; }
    else if( !strcmp(argv[i],"--divLumi") ){ divLumi   = true; }
    else if( !strcmp(argv[i],"--debug")   ){ debug     = true; }
    else if( !strcmp(argv[i],"--help")    ){ printHelp = true; }
    else{
      if(std::string(argv[i]).find("--")!=std::string::npos)
	std::cout << "WARNING:: Option " << argv[i] << " not recognized: "
		  << "skipping!" << std::endl;
    }
  }
  if(printHelp){
    std::cout << " DataPeriodPlot: make data/MC period plot! "    << std::endl;
    std::cout << "                 Options: "                     << std::endl;
    std::cout << "                  --useBjet  [Enable b-jet veto:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                  --lfvType  [Choose lfv channel: "
	      << " options 1,2,3']"                               << std::endl;
    std::cout << "                  --useGUI   [Enable GUI mode:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                  --divLumi  [Divide by Luminosity: "
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                  --debug    [Enable debug]"    << std::endl;
    std::cout << "                  --help     [Print this help]" << std::endl;
    exit(0);
  }

  if(lfvType==-1){
    std::cout << "< DataPeriodPlot() >:: lfvType not set!"
	      << " Possible options: 1,2,3" << std::endl;
    exit(0);
  }

  std::cout << "< DataPeriodPlot() >:: Options set "          << std::endl;
  std::cout << "                       useBjet = " << useBjet << std::endl;
  std::cout << "                       lfvType = " << lfvType << std::endl;
  std::cout << "                       useGUI  = " << useGUI  << std::endl;
  std::cout << "                       divLumi = " << divLumi << std::endl;
  std::cout << "                       debug   = " << debug   << std::endl;
  
  m_debug = debug;
  
  TRint *myApp = new TRint("RootSession",&argc,argv,NULL,0);
  DataPeriodPlot(lfvType,useBjet,divLumi);
  
  if(useGUI){
    std::cout << "< DataPeriodPlot() >:: using Rint -> ROOT will remain "
	      << "opened ... " << std::endl;
    myApp->Run();
  }

  return 0;
    
}

void SetHistoStyle(TH1F *h, std::vector<std::string> PeriodsName){

  h->GetYaxis()->SetTitle("Events / fb^{-1}");
  h->GetYaxis()->CenterTitle(kTRUE);
  h->GetYaxis()->SetTitleOffset(1.50);
  h->GetYaxis()->SetNdivisions(509);
  h->GetYaxis()->SetRangeUser(200,800);

  for(int i=1; i<(int)PeriodsName.size()+1; i++){
    h->GetXaxis()->SetBinLabel( i, PeriodsName.at(i-1).c_str() );
  }
  
}

std::vector<TGraphErrors*> FillHistAndUnc(Int_t Bins, double SystErr,
					  std::vector<std::string> PeriodsName,
					  std::map<std::string, double> DataN,
					  std::map<std::string, double> MCExp,
					  TH1F *hdata){
  
  Int_t N=Bins;
  Double_t xVal[N] , yVal[N] , xErr[N] , yErr[N] ;
  Double_t DxVal[N], DyVal[N], DxErr[N], DyErr[N];
  Double_t SxVal[N], SyVal[N], SxErr[N], SyErr[N];
  for(int i=1; i<Bins+1; i++){
    if(m_debug)
      std::cout << "Bin = " << i << " Data = "<<  DataN[PeriodsName.at(i-1)]
		<< " MC = " << MCExp[PeriodsName.at(i-1)] << std::endl;
    
    DxVal[i-1] = 0.5+1*(i-1);
    DyVal[i-1] = DataN[PeriodsName.at(i-1)];
    DxErr[i-1] = 0.4;
    DyErr[i-1] = hdata->GetBinError(i); //sqrt(DataN[PeriodsName.at(i-1)]);
    
    SxVal[i-1] = 0.5+1*(i-1);
    SyVal[i-1] = MCExp[PeriodsName.at(i-1)];
    SxErr[i-1] = 0.4;
    SyErr[i-1] = 0.0; //sqrt(MCExp[ PeriodsName.at(i-1) ]);
    
    xVal[i-1] = 0.5+1*(i-1);
    yVal[i-1] = MCExp[PeriodsName.at(i-1)];
    xErr[i-1] = 0.4;
    yErr[i-1] = MCExp[PeriodsName.at(i-1)]*SystErr;
  }
  if(m_debug)
    std::cout << "" << std::endl;

  TGraphErrors *Data = new TGraphErrors(N,DxVal,DyVal,DxErr,DyErr);
  Data->SetLineColor(kBlack);
  Data->SetMarkerColor(kBlack);
  
  TGraphErrors *MC = new TGraphErrors(N,SxVal,SyVal,SxErr,SyErr);
  MC->SetLineColor(kRed);
  MC->SetMarkerColor(kRed);
  MC->SetMarkerStyle(21);
  
  TGraphErrors *Syst = new TGraphErrors(N,xVal,yVal,xErr,yErr);
  Syst->SetFillColor(kRed-10);
  Syst->SetLineColor(kRed-10);
  Syst->SetFillStyle(1001);

  std::vector<TGraphErrors*> m_vec;
  m_vec.push_back(Data);
  m_vec.push_back(MC);
  m_vec.push_back(Syst);
  
  return m_vec;
  
}

TLegend* MakeLegend(std::vector<TGraphErrors*> Histos){

  TLegend *leg = new TLegend(0.59,0.74,0.99,0.91);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->AddEntry(Histos.at(0),"Data","pE");
  leg->AddEntry(Histos.at(1),"Simulation","pE");
  leg->AddEntry(Histos.at(2),"Uncertainty","f");
  return leg;
  
}

void DataPeriodPlot(int lfvType, bool useBjet, bool divLumi){

  SetATLASStyle();
  TH1::SetDefaultSumw2(kTRUE);
  
  std::string treename = "lfv";
  std::string Dir = "";

  double MCInt   = 0, SystErr = 0;
  std::string lfvName = "";
  if(lfvType==1){      lfvName="emu"  ; MCInt=14318.3; SystErr=10.1/100.; }
  else if(lfvType==2){ lfvName="etau" ; MCInt=25424.9; SystErr=17.8/100.; }
  else if(lfvType==3){ lfvName="mutau"; MCInt=13956.8; SystErr=16.6/100.; }

  if(useBjet){
    if(lfvType==1){      lfvName="emu"  ; MCInt=4689.88; SystErr=10.9/100.; }
    else if(lfvType==2){ lfvName="etau" ; MCInt=26039.8; SystErr=11.0/100.; }
    else if(lfvType==3){ lfvName="mutau"; MCInt=13687.1; SystErr=12.5/100.; }
  }
  double Slumi = 36.1;
  
  std::vector<std::string> PeriodsName2015, PeriodsName2016;
  PeriodsName2015.push_back( "Period D" );
  PeriodsName2015.push_back( "Period E" );
  PeriodsName2015.push_back( "Period F" );
  PeriodsName2015.push_back( "Period G" );
  PeriodsName2015.push_back( "Period H" );
  PeriodsName2015.push_back( "Period J" );

  PeriodsName2016.push_back( "Period A" );
  PeriodsName2016.push_back( "Period B" );
  PeriodsName2016.push_back( "Period C" );
  PeriodsName2016.push_back( "Period D" );
  PeriodsName2016.push_back( "Period E" );
  PeriodsName2016.push_back( "Period F" );
  PeriodsName2016.push_back( "Period G" );
  PeriodsName2016.push_back( "Period I" );
  PeriodsName2016.push_back( "Period K" );
  PeriodsName2016.push_back( "Period L" );
  
  std::map<std::string, double> Periods2015, Periods2016;
  Periods2015["Period D"] = 0.051646125; //25ns from 276262 to 276954
  Periods2015["Period E"] = 0.435604977; //25ns from 278727 to 279928
  Periods2015["Period F"] = 0.370266155; //25ns from 279932 to 280422
  Periods2015["Period G"] = 0.655825479; //25ns from 280423 to 281075
  Periods2015["Period H"] = 0.264361534; //25ns from 281130 to 281411
  Periods2015["Period J"] = 1.435249385; //25ns from 282625 to 284484

  Periods2016["Period A"] = 0.546661326; //25ns from 297730 to 300279
  Periods2016["Period B"] = 1.953013170; //25ns from 300345 to 300908
  Periods2016["Period C"] = 2.870445808; //25ns from 301912 to 302393
  Periods2016["Period D"] = 4.631222048; //25ns from 302737 to 303560
  Periods2016["Period E"] = 1.485629645; //25ns from 303638 to 303892
  Periods2016["Period F"] = 3.405039737; //25ns from 303943 to 304494
  Periods2016["Period G"] = 3.834726882; //25ns from 305380 to 306451
  Periods2016["Period I"] = 5.803622108; //25ns from 307126 to 308084
  Periods2016["Period K"] = 2.209024435; //25ns from 309375 to 309759
  Periods2016["Period L"] = 6.145215909; //25ns from 310015 to 311481

  std::map<std::string, double> MCExp2015, MCExp2016;
  MCExp2015["Period D"] = MCInt/Slumi*Periods2015["Period D"];
  MCExp2015["Period E"] = MCInt/Slumi*Periods2015["Period E"];
  MCExp2015["Period F"] = MCInt/Slumi*Periods2015["Period F"];
  MCExp2015["Period G"] = MCInt/Slumi*Periods2015["Period G"];
  MCExp2015["Period H"] = MCInt/Slumi*Periods2015["Period H"];
  MCExp2015["Period J"] = MCInt/Slumi*Periods2015["Period J"];
			   
  MCExp2016["Period A"] = MCInt/Slumi*Periods2016["Period A"];
  MCExp2016["Period B"] = MCInt/Slumi*Periods2016["Period B"];
  MCExp2016["Period C"] = MCInt/Slumi*Periods2016["Period C"];
  MCExp2016["Period D"] = MCInt/Slumi*Periods2016["Period D"];
  MCExp2016["Period E"] = MCInt/Slumi*Periods2016["Period E"];
  MCExp2016["Period F"] = MCInt/Slumi*Periods2016["Period F"];
  MCExp2016["Period G"] = MCInt/Slumi*Periods2016["Period G"];
  MCExp2016["Period I"] = MCInt/Slumi*Periods2016["Period I"];
  MCExp2016["Period K"] = MCInt/Slumi*Periods2016["Period K"];
  MCExp2016["Period L"] = MCInt/Slumi*Periods2016["Period L"];

  std::map<std::string, double> DataN2015, DataN2016;
  DataN2015["Period D"] = 0;
  DataN2015["Period E"] = 0;
  DataN2015["Period F"] = 0;
  DataN2015["Period G"] = 0;
  DataN2015["Period H"] = 0;
  DataN2015["Period J"] = 0;

  DataN2016["Period A"] = 0;
  DataN2016["Period B"] = 0;
  DataN2016["Period C"] = 0;
  DataN2016["Period D"] = 0;
  DataN2016["Period E"] = 0;
  DataN2016["Period F"] = 0;
  DataN2016["Period G"] = 0;
  DataN2016["Period I"] = 0;
  DataN2016["Period K"] = 0;
  DataN2016["Period L"] = 0;
  
  TFile* input = new TFile( (Dir+"data.root").c_str() );

  /* duplicates */
  std::set< std::pair<Int_t,ULong64_t> > EvtProcessed;
  EvtProcessed.clear();
  
  ULong64_t       event;
  Int_t           run;
  Int_t           channel;
  Int_t           lbn;
  Double_t        dilepMass;
  Double_t        dilepPt;
  Double_t        dilepEta;
  Double_t        dilepPhi;
  Bool_t          isBTBGood;
  Bool_t          isBjetEvt;
  
  TBranch        *b_event;       //!
  TBranch        *b_run;         //!
  TBranch        *b_channel;     //!
  TBranch        *b_lbn;         //!
  TBranch        *b_dilepMass;   //!
  TBranch        *b_dilepPt;     //!
  TBranch        *b_dilepEta;    //!
  TBranch        *b_dilepPhi;    //!
  TBranch        *b_isBTBGood;   //!
  TBranch        *b_isBjetEvt;   //!
  
  TTree* InTree = (TTree*)input->Get( treename.c_str() );
  InTree->SetBranchStatus("*",1);

  dilepMass    = 0;
  dilepPt      = 0;
  dilepEta     = 0;
  dilepPhi     = 0;
  
  InTree->SetBranchAddress("event", &event, &b_event);
  InTree->SetBranchAddress("run", &run, &b_run);
  InTree->SetBranchAddress("channel", &channel, &b_channel);
  InTree->SetBranchAddress("lbn", &lbn, &b_lbn);
  InTree->SetBranchAddress("dilepCorrMass", &dilepMass, &b_dilepMass);
  InTree->SetBranchAddress("dilepCorrPt", &dilepPt, &b_dilepPt);
  InTree->SetBranchAddress("dilepEta", &dilepEta, &b_dilepEta);
  InTree->SetBranchAddress("dilepPhi", &dilepPhi, &b_dilepPhi);
  InTree->SetBranchAddress("isBTBGood", &isBTBGood, &b_isBTBGood);
  InTree->SetBranchAddress("isBjetEvt", &isBjetEvt, &b_isBjetEvt);

  /* data histograms */
  int Bins2015 = (int)PeriodsName2015.size();
  TH1F *h2015 = new TH1F( "data2015", "data2015", Bins2015, 0, Bins2015 );
  SetHistoStyle(h2015,PeriodsName2015);
  
  int Bins2016 = (int)PeriodsName2016.size();
  TH1F *h2016 = new TH1F( "data2016", "data2016", Bins2016, 0, Bins2016 );
  SetHistoStyle(h2016,PeriodsName2016);
  
  Int_t Nentries = (Int_t)InTree->GetEntries();
  for(Int_t en=0; en<Nentries; en++){
    InTree->GetEntry(en);

    if(channel!=lfvType) continue;
    if(!isBTBGood) continue;
    if(useBjet){ if(isBjetEvt) continue; }
    
    const std::pair<Int_t,ULong64_t> RunEvt = std::make_pair(run,event);
    if( EvtProcessed.insert(RunEvt).second == false ){
      std::cout<< "Found Duplicate in data -> Skipping! (Run "
	       << run << " Event "<< event << std::endl;
      continue;
    }
    if(m_debug){
      if(dilepMass>1000)
	std::cout << "Run Number " << run << " Event Number " << event
		  << " lbn " << lbn << std::endl;
    }
    
    /* 2015 data */
    if(run<276955){
      DataN2015["Period D"] +=1;
      if(divLumi) h2015->Fill(0.5,1/Periods2015["Period D"]);
      else        h2015->Fill(0.5,1);
    }
    else if(run<279929){
      DataN2015["Period E"] +=1;
      if(divLumi) h2015->Fill(1.5,1/Periods2015["Period E"]);
      else        h2015->Fill(1.5,1);
    }
    else if(run<280424){
      DataN2015["Period F"] +=1;
      if(divLumi) h2015->Fill(2.5,1/Periods2015["Period F"]);
      else        h2015->Fill(2.5,1);
    }
    else if(run<281076){
      DataN2015["Period G"] +=1;
      if(divLumi) h2015->Fill(3.5,1/Periods2015["Period G"]);
      else        h2015->Fill(3.5,1);
    }
    else if(run<281412){
      DataN2015["Period H"] +=1;
      if(divLumi) h2015->Fill(4.5,1/Periods2015["Period H"]);
      else        h2015->Fill(4.5,1);
    }
    else if(run<284485){
      DataN2015["Period J"] +=1;
      if(divLumi) h2015->Fill(5.5,1/Periods2015["Period J"]);
      else        h2015->Fill(5.5,1);
    }
    
    /* 2016 data */
    else if(run<300280){
      DataN2016["Period A"] +=1;
      if(divLumi) h2016->Fill(0.5,1/Periods2016["Period A"]);
      else        h2016->Fill(0.5,1);
    }
    else if(run<300909){
      DataN2016["Period B"] +=1;
      if(divLumi) h2016->Fill(1.5,1/Periods2016["Period B"]);
      else        h2016->Fill(1.5,1);
    }
    else if(run<302394){
      DataN2016["Period C"] +=1;
      if(divLumi) h2016->Fill(2.5,1/Periods2016["Period C"]);
      else        h2016->Fill(2.5,1);
    }
    else if(run<303561){
      DataN2016["Period D"] +=1;
      if(divLumi) h2016->Fill(3.5,1/Periods2016["Period D"]);
      else        h2016->Fill(3.5,1);
    }
    else if(run<303893){
      DataN2016["Period E"] +=1;
      if(divLumi) h2016->Fill(4.5,1/Periods2016["Period E"]);
      else        h2016->Fill(4.5,1);
    }
    else if(run<304495){
      DataN2016["Period F"] +=1;
      if(divLumi) h2016->Fill(5.5,1/Periods2016["Period F"]);
      else        h2016->Fill(5.5,1);
    }
    else if(run<306715){
      DataN2016["Period G"] +=1;
      if(divLumi) h2016->Fill(6.5,1/Periods2016["Period G"]);
      else        h2016->Fill(6.5,1);
    }
    else if(run<308085){
      DataN2016["Period I"] +=1;
      if(divLumi) h2016->Fill(7.5,1/Periods2016["Period I"]);
      else        h2016->Fill(7.5,1);
    }
    else if(run<309760){
      DataN2016["Period K"] +=1;
      if(divLumi) h2016->Fill(8.5,1/Periods2016["Period K"]);
      else        h2016->Fill(8.5,1);
    }
    else if(run<311482){
      DataN2016["Period L"] +=1;
      if(divLumi) h2016->Fill(9.5,1/Periods2016["Period L"]);
      else        h2016->Fill(9.5,1);
    }

  }
  if(divLumi){
    DataN2015["Period D"] = DataN2015["Period D"]/Periods2015["Period D"];
    DataN2015["Period E"] = DataN2015["Period E"]/Periods2015["Period E"];
    DataN2015["Period F"] = DataN2015["Period F"]/Periods2015["Period F"];
    DataN2015["Period G"] = DataN2015["Period G"]/Periods2015["Period G"];
    DataN2015["Period H"] = DataN2015["Period H"]/Periods2015["Period H"];
    DataN2015["Period J"] = DataN2015["Period J"]/Periods2015["Period J"];

    DataN2016["Period A"] = DataN2016["Period A"]/Periods2016["Period A"];
    DataN2016["Period B"] = DataN2016["Period B"]/Periods2016["Period B"];
    DataN2016["Period C"] = DataN2016["Period C"]/Periods2016["Period C"];
    DataN2016["Period D"] = DataN2016["Period D"]/Periods2016["Period D"];
    DataN2016["Period E"] = DataN2016["Period E"]/Periods2016["Period E"];
    DataN2016["Period F"] = DataN2016["Period F"]/Periods2016["Period F"];
    DataN2016["Period G"] = DataN2016["Period G"]/Periods2016["Period G"];
    DataN2016["Period I"] = DataN2016["Period I"]/Periods2016["Period I"];
    DataN2016["Period K"] = DataN2016["Period K"]/Periods2016["Period K"];
    DataN2016["Period L"] = DataN2016["Period L"]/Periods2016["Period L"];

    MCExp2015["Period D"] = MCExp2015["Period D"]/Periods2015["Period D"];
    MCExp2015["Period E"] = MCExp2015["Period E"]/Periods2015["Period E"];
    MCExp2015["Period F"] = MCExp2015["Period F"]/Periods2015["Period F"];
    MCExp2015["Period G"] = MCExp2015["Period G"]/Periods2015["Period G"];
    MCExp2015["Period H"] = MCExp2015["Period H"]/Periods2015["Period H"];
    MCExp2015["Period J"] = MCExp2015["Period J"]/Periods2015["Period J"];

    MCExp2016["Period A"] = MCExp2016["Period A"]/Periods2016["Period A"];
    MCExp2016["Period B"] = MCExp2016["Period B"]/Periods2016["Period B"];
    MCExp2016["Period C"] = MCExp2016["Period C"]/Periods2016["Period C"];
    MCExp2016["Period D"] = MCExp2016["Period D"]/Periods2016["Period D"];
    MCExp2016["Period E"] = MCExp2016["Period E"]/Periods2016["Period E"];
    MCExp2016["Period F"] = MCExp2016["Period F"]/Periods2016["Period F"];
    MCExp2016["Period G"] = MCExp2016["Period G"]/Periods2016["Period G"];
    MCExp2016["Period I"] = MCExp2016["Period I"]/Periods2016["Period I"];
    MCExp2016["Period K"] = MCExp2016["Period K"]/Periods2016["Period K"];
    MCExp2016["Period L"] = MCExp2016["Period L"]/Periods2016["Period L"];

  }
  
  /* 2015 plot */
  TH1F *dummy2015 = new TH1F( "dummy2015", "dummy2015", Bins2015, 0, Bins2015 );
  SetHistoStyle(dummy2015,PeriodsName2015);
  
  std::vector<TGraphErrors*> H2015 = FillHistAndUnc(Bins2015,SystErr,
						    PeriodsName2015,DataN2015,
						    MCExp2015,h2015);

  /* 2016 plot */
  TH1F *dummy2016 = new TH1F( "dummy2016", "dummy2016", Bins2016, 0, Bins2016 );
  SetHistoStyle(dummy2016,PeriodsName2016);
  
  std::vector<TGraphErrors*> H2016 = FillHistAndUnc(Bins2016,SystErr, 
						    PeriodsName2016,DataN2016,
						    MCExp2016,h2016);
  
  TCanvas *c15 = new TCanvas("c15","c15",0,0,600,600);
  c15->cd();
  dummy2015->Draw();
  H2015.at(1)->Draw("pez");
  H2015.at(2)->Draw("same2");
  H2015.at(1)->Draw("pEzsame");
  H2015.at(0)->Draw("pEzsame");
  DrawLabels(false,false,false,false,false,true,false);
  DrawChannel(lfvName,false,useBjet);
  TLegend *leg2015 = MakeLegend(H2015);
  leg2015->Draw();

  TCanvas *c16 = new TCanvas("c16","c16",0,0,600,600);
  c16->cd();
  dummy2016->Draw();
  H2016.at(1)->Draw("pEz");
  H2016.at(2)->Draw("same2");
  H2016.at(1)->Draw("pEzsame");
  H2016.at(0)->Draw("pEzsame");
  DrawLabels(false,false,false,false,false,false,true);
  DrawChannel(lfvName,false,useBjet);
  TLegend *leg2016 = MakeLegend(H2016);
  leg2016->Draw();
  
}
