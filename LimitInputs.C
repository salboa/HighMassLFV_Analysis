/* program includes */
#include "LimitInputs.h"
#include "SysHandler.C"
#include "ATLASstyle.C"

int main( int argc, char* argv[] ) {

  bool useBjet         = false;
  std::string process  = "Background";
  bool useSmooth       = false;
  bool sigShapes       = false;
  bool useVisMass      = false;
  bool rmAbs           = false;
  bool printHelp       = false;
  int lfvType = -1;
  for(int i = 1; i < argc; ++i){
    if( !strcmp(argv[i],"--useBjet")         ){ useBjet    = true; }
    else if( !strcmp(argv[i],"--process")    ){ process    = argv[i+1]; }
    else if( !strcmp(argv[i],"--lfvType")    ){ lfvType    = std::stoi(argv[i+1]); }
    else if( !strcmp(argv[i],"--useSmooth")  ){ useSmooth  = true; }
    else if( !strcmp(argv[i],"--sigShapes")  ){ sigShapes  = true; }
    else if( !strcmp(argv[i],"--rmAbs")      ){ rmAbs      = true; }
    else if( !strcmp(argv[i],"--useVisMass") ){ useVisMass = true; }
    else if( !strcmp(argv[i],"--help")       ){ printHelp  = true; }
    else{
      if(std::string(argv[i]).find("--")!=std::string::npos)
	std::cout << "WARNING:: Option " << argv[i] << " not recognized: "
		  << "skipping!" << std::endl;
    }
  }
  if(printHelp){
    std::cout << " LimitInputs: making limit inputs!"              << std::endl;
    std::cout << "                Options: "                       << std::endl;
    std::cout << "                 --useBjet    [Enable b-jet veto:"
	      << " default is 'false' "                            << std::endl;
    std::cout << "                 --process    [Define process to run:"
	      << " default is 'Background "                        << std::endl;
    std::cout << "                 --lfvType    [Choose lfv channel: "
	      << " options are '1,2,3'] "                          << std::endl;
    std::cout << "                 --useSmooth  [Enable smoothed qcd mll:"
	      << " default is 'false'] "                           << std::endl;
    std::cout << "                 --sigShapes  [Save signals shapes:"
	      << " defualt is 'false'] "                           << std::endl;
    std::cout << "                 --rmAbs      [Enable using no abs version:"
	      << " defualt is 'false'] "                           << std::endl;
    std::cout << "                 --useVisMass [Enable using visible mass:"
	      << " default is 'false'] "                           << std::endl;
    std::cout << "                 --help       [Print this help]" << std::endl;
    exit(0);
  }

  if(lfvType==-1){
    std::cout << "< LimitInputs() >:: lfvType not set!"
	      << " Possible options: 1,2,3" << std::endl;
    exit(0);
  }
  
  std::cout << " LimitInputs Options set: "           << std::endl;
  std::cout << "         useBjet    = " << useBjet    << std::endl;
  std::cout << "         process    = " << process    << std::endl;
  std::cout << "         lfvType    = " << lfvType    << std::endl;
  std::cout << "         useSmooth  = " << useSmooth  << std::endl;
  std::cout << "         sigShapes  = " << sigShapes  << std::endl;
  std::cout << "         rmAbs      = " << rmAbs      << std::endl;
  std::cout << "         useVisMass = " << useVisMass << std::endl;
  
  LimitInputs(lfvType,useBjet,process,useSmooth,sigShapes,rmAbs,useVisMass);
  
  return 0;
}

void LimitInputs(int LFVtype,    bool useBjet,   std::string process,
		 bool useSmooth, bool sigShapes, bool rmAbs,
		 bool useVisMass){

  SetATLASStyle();
  TH1::SetDefaultSumw2(kTRUE);

  std::string lfvType = "";
  if(LFVtype==1)      { lfvType="emu";   }
  else if(LFVtype==2) { lfvType="etau";  }
  else if(LFVtype==3) { lfvType="mutau"; }
  
  std::cout << " < LimitInputs >:: Making Limit inputs for Channel "
	    << lfvType << std::endl;
  
  std::string Dir = "";
  if(useBjet){ Dir += "Bjet/";   }
  else{        Dir += "NoBjet/"; }

  bool isSignal = false;
  if(process.find("Zprime")!=std::string::npos ||
     process.find("QBH")!=std::string::npos    ||
     process.find("SVT")!=std::string::npos     )
    isSignal = true;
     
  /* Loading files */
  std::string DistName = "Plots_Nominal_"+lfvType;
  std::string PercName = "PercentVariations_"+lfvType;
  std::string OutName  = "LimitsInputs_"+lfvType;
  if(isSignal){
    DistName += "_Signals";
    PercName += "_Signal_"+process;
    OutName  += "_Signal_"+process;
  }
  if(useSmooth){
    DistName += "_Smooth";
    OutName  += "_Smooth";
  }
  if(rmAbs){
    PercName += "_noAbs";
    OutName  += "_noAbs";
  }
  if(useVisMass) OutName += "_VisMass";
  
  /* making syst list */
  std::vector<std::string> sysVar;
  if(isSignal){
    if(sigShapes)
      sysVar = GetSysList(LFVtype,useBjet,true,false,false,false,true);
    else
      sysVar = GetSysList(LFVtype,useBjet,true,true,false,false,true);
  }
  else{
    sysVar = GetSysList(LFVtype,useBjet,true);
    if(LFVtype>1){
      sysVar.push_back( "TauFake_SysUp"   );
      sysVar.push_back( "TauFake_SysDown" );
    }
  }

  if(sigShapes){
    SignalShapes(Dir,lfvType,process,sysVar);
    sysVar.clear();
    return;
  }

  TFile *dist = new TFile( (Dir+DistName+".root").c_str() );
  TFile *perc = NULL, *out = NULL;
  perc = new TFile( (Dir+PercName+".root").c_str() );
  out  = new TFile( (Dir+OutName+".root").c_str(), "RECREATE" );

  /* define Histograms */
  TH1F *data=NULL, *mllCor=NULL;

  for(uint i=0; i<sysVar.size(); i++){
    std::cout << "< LimitInputs() >:: Processing Sys = " << sysVar.at(i)
	      << std::endl;
  
    if(sysVar.at(i)=="Nominal"){
      data   = (TH1F*)dist->Get( "hmllCorr_data" );
      mllCor = (TH1F*)dist->Get( "hmllCorr_BkgTot" );
    }
    else{
      if(useVisMass){
	if(sysVar.at(i).find("Top")!=std::string::npos)
	  mllCor = (TH1F*)perc->Get( ("mllCorr_PercVar_"+sysVar.at(i)).c_str() );
	else
	  mllCor = (TH1F*)perc->Get( ("mll_PercVar_"+sysVar.at(i)).c_str() );
      }
      else{
	mllCor = (TH1F*)perc->Get( ("mllCorr_PercVar_"+sysVar.at(i)).c_str() );
      }
    }
    
    out->cd();
    if(sysVar.at(i)=="Nominal"){
      data->Write("hmll_data");
      std::cout << "Num. of bins = " << data->GetNbinsX() << std::endl;
      mllCor->Write("hmll_Nominal");
      std::cout << "Num. of bins = " << mllCor->GetNbinsX() << std::endl;
    }
    else{
      TH1F *mllV = (TH1F*)mllCor->Clone( ("PercVar_"+sysVar.at(i)).c_str() );
      mllV->Reset();
      for(int b=1; b<mllCor->GetNbinsX()+1; b++){
	double val = mllCor->GetBinContent(b);
	mllV->SetBinContent(b, val/100 );
      }
      
      mllV->Write( ("PercVar_"+sysVar.at(i)).c_str() );
      std::cout << "Num. of bins = " << mllV->GetNbinsX() << std::endl;
      mllV->Delete();
    }
    
    /* cleaning */
    if(sysVar.at(i)=="Nominal")
      data->Delete();
    mllCor->Delete();
  }
  
  /* close file */
  out->Close();
  perc->Close();
  dist->Close();
  
}


void SignalShapes(std::string Dir,     std::string lfvType,
		  std::string process, std::vector<std::string> sysVar){

  TFile *out = NULL;
  if(process=="Zprime0500")
    out = new TFile( (Dir+"SignalShapes_"+lfvType+".root").c_str(), "RECREATE" );
  else
    out = new TFile( (Dir+"SignalShapes_"+lfvType+".root").c_str(), "UPDATE" );

  TFile *in = NULL; TH1F *mll = NULL;
  
  for(uint i=0; i<sysVar.size(); i++){
    std::cout << "< LimitInputs() >:: Processing Sys = " << sysVar.at(i)
	      << std::endl;
    in = new TFile( (Dir+"Plots_"+sysVar.at(i)+"_"+lfvType+"_Signals.root").c_str() );
    mll=(TH1F*)in->Get( ("hmllCorr_"+process).c_str() );
    out->cd();
    mll->Write( (process+"_"+sysVar.at(i)).c_str() );
    mll->Delete();
    in->Close();
  }
  out->Close();
  std::cout << "exiting SignaShapes"<<std::endl;
}
