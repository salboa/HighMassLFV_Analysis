/* C++ includes */
#include "iostream"
/* program includes */
#include "TopExtra.h"
#include "SysHandler.C"

int main( int argc, char* argv[] ){

  int lfvType    = -1;
  bool useBjet   = false;
  bool exclScale = false;
  bool addSys    = false;
  bool addPtRw   = false;
  bool printHelp = false;
  for(int i = 1; i < argc; ++i){
    if( !strcmp(argv[i],"--useBjet")        ){ useBjet   = true; }
    else if( !strcmp(argv[i],"--exclScale") ){ exclScale = true; }
    else if( !strcmp(argv[i],"--lfvType")   ){ lfvType   = std::stoi(argv[i+1]); }
    else if( !strcmp(argv[i],"--addSys")    ){ addSys    = true; }
    else if( !strcmp(argv[i],"--addPtRw")   ){ addPtRw   = true; }
    else if( !strcmp(argv[i],"--help")      ){ printHelp = true; }
    else{
      if(std::string(argv[i]).find("--")!=std::string::npos)
	std::cout << "WARNING:: Option " << argv[i] << " not recognized: "
		  << "skipping!" << std::endl;
    }
  }
   if(printHelp){
    std::cout << " TopExtra: make top extrapolation inputs! "     << std::endl;
    std::cout << "                Options: "                      << std::endl;
    std::cout << "                 --useBjet   [Enable b-jet veto:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                 --lfvType   [Choose lfv channel: "
	      << " options 1,2,3']"                               << std::endl;
    std::cout << "                 --exclScale [exclude Top Scale:  "
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                 --addSys    [Add sytematics:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                 --addPtRw   [Add pT rw sys:"
	      << " default is 'false'] "                          << std::endl;
    std::cout << "                 --help      [Print this help]" << std::endl;
    exit(0);
  }
   
  if(lfvType==-1){
    std::cout << "< TopExtra() >:: lfvType not set!"
	      << " Possible options: 1,2,3" << std::endl;
    exit(0);
  }
  std::cout << "< TopExtra() >:: OPTIONS: " <<std::endl;
  std::cout << "                  lfvType   = " << lfvType   << std::endl;
  std::cout << "                  useBjet   = " << useBjet   << std::endl;
  std::cout << "                  esclScale = " << exclScale << std::endl;
  std::cout << "                  addSys    = " << addSys    << std::endl;
  std::cout << "                  addPtRw   = " << addPtRw   << std::endl;

  TopExtra(lfvType,useBjet,exclScale,addSys,addPtRw);
  
  return 0;

}

void TopExtra(int LFVtype, bool useBjet, bool exclScale,
	      bool addSys, bool addPtRw){

  TH1::SetDefaultSumw2(kTRUE);

  std::string lfvType = "";
  if(LFVtype==1)      { lfvType="emu";   }
  else if(LFVtype==2) { lfvType="etau";  }
  else if(LFVtype==3) { lfvType="mutau"; }
  
  std::cout << "< TopExtra() >:: Merging top mass plots for Channel "
	    << lfvType << " in a single file "<< std:: endl;
  
  std::vector<std::string> sysVar = GetSysList(LFVtype,useBjet,addSys,
					       false,true,false,false,true);

  if(addPtRw) sysVar.push_back( "PtRw_Sys" );
  
  TFile *inF = NULL, *out = NULL;
  std::string Dir = "";
  if( useBjet ){ Dir = "Bjet/";   }
  else{          Dir += "NoBjet/"; }

  std::string OutDir = "TopFits/ExtraInputs/";
  CheckOutDir(OutDir);

  std::string outname = "TopExtraInputs_";
  if( useBjet ) outname += "bjet_";
  outname += lfvType;
  
  out = new TFile( (OutDir+outname+".root").c_str(),"RECREATE");
  for(uint i=0; i<sysVar.size(); i++){

    std::cout << "Processing sysVar = " << sysVar.at(i) << std::endl;
    if(sysVar.at(i)=="PtRw_Sys")
      inF = new TFile( (Dir+"/Plots_Nominal_"+lfvType+"_PtRw.root").c_str() );
    else
      inF = new TFile( (Dir+"topExtraInput/Plots_"+sysVar.at(i)+"_"+lfvType+".root").c_str() );
    
    TH1F *h = (TH1F*)inF->Get( "hmllCorr_Top" );
    out->cd();
    h->Write( ("hmllCorr_Top_"+sysVar.at(i)).c_str() );
    /* cleaning */
    h->Delete();
    inF->Close();
  }
  out->Close();
  
}

void CheckOutDir(std::string m_OutDir){

  std::string tmp_s = m_OutDir;
  std::string delim = "/";
  size_t pos = 0;
  while( (pos = tmp_s.find(delim)) != std::string::npos ){
    m_dirs.push_back( tmp_s.substr(0, pos) );
    tmp_s.erase(0, pos + delim.length());
  }

  m_tmpOutDir = "";
  for(uint i=0; i<m_dirs.size(); i++){
    struct stat st;
    m_tmpOutDir+=m_dirs.at(i)+"/";
    if(stat(m_tmpOutDir.c_str(),&st) == 0){
      std::cout << "< RunOnMiniTree :: CheckOutDir() > :: "
		<< "\033[1;32m Out Directory " << m_tmpOutDir
		<< " already present!\033[0m" << std::endl;
    }
    else{
      std::cout << "< RunOnMiniTree :: CheckOutDir() > :: "
		<< "\033[1;34m Creating Directory " << m_tmpOutDir
		<< " ... \033[0m" << std::endl;
      int outD = system( ("mkdir "+m_tmpOutDir).c_str() );
      if(outD!=0)
	std::cout << "< RunOnMiniTree :: CheckOutDir() > :: "
		  << "\033[1;31m Directory " << m_tmpOutDir
		  << " could not be created!\033[0m" << std::endl;
    }
  }
  m_dirs.clear();
  
}
