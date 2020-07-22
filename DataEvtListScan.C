/* program includes */
#include "DataEvtListScan.h"
#include "Utils.C"

int main( int argc, char* argv[] ) {

  int lfvType        = -1;
  bool debug         = false;
  bool useBjet       = false;
  bool useGUI        = false;
  bool doPlot        = false;
  bool printHelp     = false;
  std::string list1  = "";
  std::string list2  = "";
  for(int i = 1; i < argc; ++i){
    if( !strcmp(argv[i],"--lfvType")      ){ lfvType   = std::stoi(argv[i+1]); }
    else if( !strcmp(argv[i],"--useBjet") ){ useBjet   = true;      }
    else if( !strcmp(argv[i],"--list1")   ){ list1     = argv[i+1]; }
    else if( !strcmp(argv[i],"--list2")   ){ list2     = argv[i+1]; }
    else if( !strcmp(argv[i],"--useGUI")  ){ useGUI    = true;      }
    else if( !strcmp(argv[i],"--doPlot")  ){ doPlot    = true;      }
    else if( !strcmp(argv[i],"--debug")   ){ debug     = true;      }
    else if( !strcmp(argv[i],"--help")    ){ printHelp = true;      }
    else{
      if(std::string(argv[i]).find("--")!=std::string::npos)
	std::cout << "WARNING:: Option " << argv[i] << " not recognized: "
		  << "skipping!" << std::endl;
    }
  }
  
  if(printHelp){
    std::cout << " DataEvtListScan: detect differences between"
	      << " two data list files!"                        << std::endl;
    std::cout << "               Options: "                     << std::endl;
    std::cout << "                --lfvType  [Choose lfv channel: "
	      << " options 1,2,3']"                             << std::endl;
    std::cout << "                --useBjet  [Enable b-jet veto:"
	      << " default is 'false'] "                        << std::endl;
    std::cout << "                --list1    [Specify data list 1:"
	      << " default is ''] "                             << std::endl;
    std::cout << "                --list2    [Specify data list 2:"
	      << " default is ''] "                             << std::endl;
    std::cout << "                --useGUI   [Enable GUI mode:"
	      << " default is 'false'] "                        << std::endl;
    std::cout << "                --doPlot   [Do comparison plot:"
	      << " default is 'false'] "                        << std::endl;
    std::cout << "                --debug    [Enable debug]"    << std::endl;
    std::cout << "                --help     [Print this help]" << std::endl;
    exit(0);
  }

  std::cout << "< DataEvtListScan() >:: Options set: "          << std::endl;
  std::cout << "                         lfvType = " << lfvType << std::endl;
  std::cout << "                         useBjet = " << useBjet << std::endl;
  std::cout << "                         list1   = " << list1   << std::endl;
  std::cout << "                         list2   = " << list2   << std::endl;
  std::cout << "                         useGUI  = " << useGUI  << std::endl;
  std::cout << "                         doPlot  = " << doPlot  << std::endl;
  std::cout << "                         debug   = " << debug   << std::endl;

  std::string chanName = "";
  if(lfvType==1)      { chanName="emu";   }
  else if(lfvType==2) { chanName="etau";  }
  else if(lfvType==3) { chanName="mutau"; }

  m_debug = debug;

  TRint *myApp = new TRint("RootSession",&argc,argv,NULL,0);
  if(doPlot)
    DrawPlot(chanName,useBjet);
  else
    DataEvtListScan(chanName,useBjet,list1,list2);

  if(useGUI){
    std::cout << "DataEvtListScan() >:: using Rint -> ROOT will remain "
	      << "opened ... " << std::endl;
    myApp->Run();
  }
  return 0;
  
}

void DataEvtListScan(std::string lfvType, bool useBjet,
		     std::string file1,   std::string file2){

  SetATLASStyle();

  std::string Dir = "";
  if(useBjet){ Dir += "Bjet/";   }
  else{        Dir += "NoBjet/"; }

  std::ifstream m_list1;
  m_list1.open( file1.c_str() );
  std::ifstream m_list2;
  m_list2.open( file2.c_str() );

  std::vector<int> RunList1, RunList2;
  std::vector<unsigned long long> EvtList1, EvtList2;
  
  int tmpRun = 0;
  unsigned long long tmpEvt = 0;
  std::string tmp = "";
  int counter = 0;
  while(m_list1.good()){
    counter++;
    tmpRun=0;
    tmpEvt=0;
    m_list1>>tmp;
    m_list1>>tmp;
    m_list1>>tmpRun;
    RunList1.push_back(tmpRun);
    m_list1>>tmp;
    m_list1>>tmp;
    m_list1>>tmp;
    m_list1>>tmpEvt;
    EvtList1.push_back(tmpEvt);
  }
  std::cout << "< DataEvtListScan() >:: Events List1 = " << counter
	    << " " << RunList1.size() << std::endl;
  
  counter = 0;
  while(m_list2.good()){
    counter++;
    tmpRun=0;
    tmpEvt=0;
    m_list2>>tmp;
    m_list2>>tmp;
    m_list2>>tmpRun;
    RunList2.push_back(tmpRun);
    m_list2>>tmp;
    m_list2>>tmp;
    m_list2>>tmp;
    m_list2>>tmpEvt;
    EvtList2.push_back(tmpEvt);
  }
  std::cout << "< DataEvtListScan() >:: Events List2 = " << counter
	    << " " << RunList2.size() << std::endl;

  /* check douplicates */
  std::set< std::pair<Int_t,ULong64_t> > m_EvtProcessed;
  for(uint j=0; j<RunList2.size(); j++){
    int run = RunList2.at(j);
    unsigned long long evt = EvtList2.at(j);
    const std::pair<Int_t,ULong64_t> RunEvt = std::make_pair(run,evt);
    if( m_EvtProcessed.insert(RunEvt).second == false ){
      std::cout << "< DataEvtListScan() >:: Found Duplicate In List2 "
	<< "-> Skipping! (Run = " << run << " Event = " << evt << ")"
	<< std::endl;
      continue;
    }
  }

  std::cout << "" << std::endl;
  
  for(uint i=0; i<RunList1.size(); i++){
    int run = RunList1.at(i);
    unsigned long long evt = EvtList1.at(i);
    bool evtfound=false;
    for(uint j=0; j<RunList2.size(); j++){
      if( run==RunList2.at(j) && evt==EvtList2.at(j) )
	evtfound=true;
    }
    if(!evtfound){
      std::cout << "< DataEvtListScan() >:: Event NOT Found in List2: "
		<< " Run " << run << " Event " << evt << std::endl;
    }
  }

  std::cout << "" << std::endl;

  for(uint i=0; i<RunList2.size(); i++){
    int run = RunList2.at(i);
    unsigned long long evt = EvtList2.at(i);
    bool evtfound=false;
    for(uint j=0; j<RunList1.size(); j++){
      if( run==RunList1.at(j) && evt==EvtList1.at(j) )
	evtfound=true;
    }
    if(!evtfound){
      std::cout << "< DataEvtListScan() >:: Event NOT Found in List1: "
		<< " Run " << run << " Event " << evt << std::endl;
    }
  }
  
}

void DrawPlot(std::string lfvType, bool useBjet){
  
  SetATLASStyle();
  
  std::string Dir = "";
  if(useBjet){ Dir += "Bjet/";   }
  else{        Dir += "NoBjet/"; }

  TFile *m_F1 = new TFile( (Dir+"Plots_Nominal_"+lfvType+".root").c_str() );
  TFile *m_F2 = new TFile( ("Save_36p2/"+Dir+"Plots_Nominal_"+lfvType+".root").c_str() );

  TH1F *h1 = (TH1F*)m_F1->Get( "hmllCorr_data" );
  TH1F *h2 = (TH1F*)m_F2->Get( "hmllCorr_data" );

  TH1F *ratio = (TH1F*)h1->Clone("ratio");
  ratio->Reset();
  ratio->GetXaxis()->SetTitle(h1->GetXaxis()->GetTitle());
  ratio->Divide(h1,h2);
  SetRatioPlot(ratio,kBlack);
  ratio->GetXaxis()->SetRangeUser(130,2400);
  ratio->GetYaxis()->SetRangeUser(0.95,1.05);

  /* Draw */
  TCanvas *c = CreateCanvas(lfvType);
  TPad *p1   = CreateTopPad(lfvType,"mll");
  TPad *p2   = CreateBottomPad(lfvType,"mll");

  c->cd();
  p1->Draw();
  p2->Draw();

  p1->cd();

  h1->SetMarkerColor(kBlack);
  h1->SetLineColor(kBlack);
  h2->SetMarkerStyle(25);
  h2->SetMarkerColor(kRed);
  h2->SetLineColor(kRed);
  h1->GetXaxis()->SetRangeUser(130,2400);
  h1->GetYaxis()->SetRangeUser(0.1,100000);

  h1->Draw("pE");
  h2->Draw("pEsame");

  TLegend *leg = CreateLegend();
  leg->AddEntry(h1,"Data - v88 (36.1 fb^{-1})","lpe");
  leg->AddEntry(h2,"Data - v89 (36.2 fb^{-1})","lpe");
  leg->AddEntry(ratio,"v88/v89","lpe");
  leg->Draw();

  DrawLabels(true);
  DrawChannel(lfvType,true);

  p2->cd();
  ratio->Draw("pE");
  
}

void SetRatioPlot(TH1F *ratio, Int_t color, Int_t marker, bool isRatio){

  ratio->GetYaxis()->SetTitle("Ratio");
  ratio->GetXaxis()->SetTitleOffset(1.20);
  ratio->GetYaxis()->CenterTitle(kTRUE);
  ratio->GetYaxis()->SetNdivisions(507);
  ratio->GetXaxis()->SetMoreLogLabels(kTRUE);
  ratio->GetXaxis()->SetNoExponent(kTRUE);
  ratio->SetLineColor(color);
  ratio->SetMarkerColor(color);
  ratio->SetMarkerStyle(marker);
  if(isRatio){
    ratio->GetXaxis()->SetLabelSize(0.08);
    ratio->GetYaxis()->SetLabelSize(0.07);
    ratio->GetXaxis()->SetTitleSize(0.10);
    ratio->GetYaxis()->SetTitleSize(0.08);
    ratio->GetYaxis()->SetTitleOffset(0.55);
    ratio->SetMarkerSize(1.0);
  }
  else{
    ratio->GetXaxis()->SetLabelSize(0.04);
    ratio->GetYaxis()->SetLabelSize(0.04);
    ratio->GetXaxis()->SetTitleSize(0.05);
    ratio->GetYaxis()->SetTitleSize(0.05);
    ratio->GetYaxis()->SetTitleOffset(1.35);
    ratio->SetMarkerSize(1.2);
  }
  
}
