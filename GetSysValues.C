/* program includes */
#include "GetSysValues.h"
#include "SysHandler.C"
#include "ATLASstyle.C"

int main( int argc, char* argv[] ) {

  bool useBjet   = false;
  bool useAllSys = false;    
  bool printHelp = false;
  bool debug     = false;
  int lfvType    = -1;
  for(int i = 1; i < argc; ++i){
    if( !strcmp(argv[i],"--useBjet")        ){ useBjet   = true; }
    else if( !strcmp(argv[i],"--lfvType")   ){ lfvType   = std::stoi(argv[i+1]); }
    else if( !strcmp(argv[i],"--useAllSys") ){ useAllSys = true; }
    else if( !strcmp(argv[i],"--debug")     ){ debug     = true; }
    
    else if( !strcmp(argv[i],"--help")      ){ printHelp = true; }
    else{
      if(std::string(argv[i]).find("--")!=std::string::npos)
	std::cout << "WARNING:: Option " << argv[i] << " not recognized: "
		  << "skipping!" << std::endl;
    }
  }
  if(printHelp){
    std::cout << " GetSysValues: get Sys % values!"  << std::endl;
    std::cout << "                Options: "                      << std::endl;
    std::cout << "                 --useBjet   [Enable b-jet veto:"
	      << " default is 'false' "                           << std::endl;
    std::cout << "                 --useAllSys [Enable BDT/Comp sys:"
	      << " default is 'false' "                           << std::endl;
    std::cout << "                 --lfvType   [Choose lfv channel: "
	      << " options are '1,2,3'] "                         << std::endl;
    std::cout << "                 --debug     [Enable debug]"      << std::endl;
    std::cout << "                 --help      [Print this help]"   << std::endl;
    exit(0);
  }

  if(lfvType==-1){
    std::cout << "< GetSysValues() >:: lfvType not set!"
	      << " Possible options: 1,2,3" << std::endl;
    exit(0);
  }
  
  std::cout << " GetSysValues Options set: "      << std::endl;
  std::cout << "       useBjet   = " << useBjet   << std::endl;
  std::cout << "       useAllSys = " << useAllSys << std::endl;
  std::cout << "       lfvType   = " << lfvType   << std::endl;
  std::cout << "       debug     = " << debug     << std::endl;

  m_debug = debug;

  GetSysValues(lfvType,useBjet,useAllSys);
  
  return 0;
}

void GetSysValues(int LFVtype, bool useBjet, bool useAllSys){
  
  SetATLASStyle();
  TH1::SetDefaultSumw2(kTRUE);

  std::string lfvType = "";
  if(LFVtype==1)      { lfvType="emu";   }
  else if(LFVtype==2) { lfvType="etau";  }
  else if(LFVtype==3) { lfvType="mutau"; }

  std::cout << " < GetSysValues() > :: retrieving sys % values for "
	    << lfvType << " Channel and BkgTot Background" << std::endl;
  
  std::string Dir = "";
  if(useBjet){  Dir += "Bjet/";   }
  else{         Dir += "NoBjet/"; }

  /* define files */
  std::string InName = Dir+"PercentVariations_"+lfvType;
  std::string ToName = Dir+"SystematicsBands_"+lfvType;
  
  TFile *InF = new TFile( (InName+".root").c_str() );
  TFile *InT = new TFile( (ToName+".root").c_str() );

  /* define systematics */
  std::vector<std::string> sysVar = GetSystematics(LFVtype,useBjet);
  if(LFVtype>1)
    sysVar.push_back( "TauFake_SysUp" );

  TH1F *sysH = NULL;
  for(uint i=0; i<sysVar.size(); i++){

    if(!useAllSys){
      if(sysVar.at(i).find("TauFake_BDT")!=std::string::npos  ||
	 sysVar.at(i).find("TauFake_Comp")!=std::string::npos  )
	continue;
    }

    if(sysVar.at(i)=="Total")
      sysH = (TH1F*)InT->Get( "mllCorr_SysUp" );
    else
      sysH = (TH1F*)InF->Get( ("mllCorr_PercVar_"+sysVar.at(i)).c_str() );
    
    Int_t bin1 = sysH->FindBin(1000.);
    Int_t bin2 = sysH->FindBin(2000.);
    Int_t bin3 = sysH->FindBin(3000.);

    std::cout << "     Syst = "; std::cout.width(20); std::cout << sysVar.at(i);
    std::cout.width(15); std::cout << sysH->GetBinContent(bin1); 
    std::cout.width(15); std::cout << sysH->GetBinContent(bin2);
    std::cout.width(15); std::cout << sysH->GetBinContent(bin3) << std::endl;
    sysH->Delete();
  }

  /* Closing Files */
  InF->Close();
  InT->Close();
}
