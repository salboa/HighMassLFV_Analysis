/* C++ includes */
#include "iostream"
/* program includes */
#include "TopScale.h"

int main( int argc, char* argv[] ){

  int lfvType    = -1;
  bool useBjet   = false;
  bool printHelp = false;
  for(int i = 1; i < argc; ++i){
    if( !strcmp(argv[i],"--useBjet")        ){ useBjet   = true; }
    else if( !strcmp(argv[i],"--lfvType")   ){ lfvType   = std::stoi(argv[i+1]); }
    else if( !strcmp(argv[i],"--help")      ){ printHelp = true; }
    else{
      if(std::string(argv[i]).find("--")!=std::string::npos)
	std::cout << "WARNING:: Option " << argv[i] << " not recognized: "
		  << "skipping!" << std::endl;
    }
  }
  if(printHelp){
    std::cout << " TopScale: make top scale sys ratio! "           << std::endl;
    std::cout << "                 Options: "                      << std::endl;
    std::cout << "                  --useBjet   [Enable b-jet veto:"
	      << " default is 'false'] "                           << std::endl;
    std::cout << "                  --lfvType   [Choose lfv channel: "
	      << " options 1,2,3']"                                << std::endl;
    std::cout << "                  --help      [Print this help]" << std::endl;
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
  
  TopScale(lfvType,useBjet);
  
  return 0;

}

void TopScale(int LFVtype, bool useBjet){

  TH1::SetDefaultSumw2(kTRUE);

  std::string lfvType = "";
  if(LFVtype==1)      { lfvType="emu";   }
  else if(LFVtype==2) { lfvType="etau";  }
  else if(LFVtype==3) { lfvType="mutau"; }
  
  std::cout << "< TopScale() >:: making top scale ratios for Channel "
	    << lfvType << " in a single file "<< std:: endl;
  
  TFile *input = NULL, *out = NULL;
  std::string Dir = "TopFits/";

  std::string OutDir = "VarInputs/";
  CheckOutDir(OutDir);

  std::string outname = "TopScaleVariation";
  if( useBjet ) outname += "_BjetVeto";

  if(LFVtype==1)
    out = new TFile( (OutDir+outname+".root").c_str(),"RECREATE");
  else
    out = new TFile( (OutDir+outname+".root").c_str(),"UPDATE");

  if(useBjet)
    input = new TFile( (Dir+"Top_"+lfvType+"Fits_bjet.root").c_str() );
  else
    input = new TFile( (Dir+"Top_"+lfvType+"Fits.root").c_str() );
  
  TH1F* Nom = (TH1F*)input->Get( "hmllCorr_Top_Nominal_FIT" );
  TH1F* UpV = (TH1F*)input->Get( "hmllCorr_Top_TopScale_SysUp_FIT" );
  TH1F* DwV = (TH1F*)input->Get( "hmllCorr_Top_TopScale_SysDown_FIT" );

  TH1F* ratioUp = (TH1F*)Nom->Clone( "hTopScaleUp" ); ratioUp->Reset();
  TH1F* ratioDw = (TH1F*)Nom->Clone( "hTopScaleDw" ); ratioDw->Reset();

  MakeRatio(Nom, UpV, ratioUp);
  MakeRatio(Nom, DwV, ratioDw);
  
  out->cd();
  ratioUp->Write( ("hTopScaleUp_"+lfvType).c_str()   );
  ratioDw->Write( ("hTopScaleDown_"+lfvType).c_str() );
  /* cleaning */
  Nom->Delete();
  UpV->Delete();
  DwV->Delete();
  input->Close();
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

void MakeRatio(TH1F* nominal, TH1F* varied, TH1F* &ratio){
  
  for(int b=1; b<nominal->GetNbinsX()+1; b++){
    double diff  = varied->GetBinContent(b)-nominal->GetBinContent(b);
    double den   = nominal->GetBinContent(b);
    double value = 0;
    if(den==0){ value=0; }
    else{ value = fabs(diff/den); }

    std::cout << "Bin = " << b << " Varied = " << varied->GetBinContent(b)
      	      << " Nominal = " << nominal->GetBinContent(b) << std::endl;
    std::cout<<"den "<< den<<"  diff "<<diff<<std::endl;
    std::cout<<"value "<<value<<std::endl;
    ratio->SetBinContent( b, value );
  }
  ratio->Smooth();
  ratio->SetFillColor(kWhite);
  ratio->SetLineStyle(1);
  ratio->SetLineColor(1);
  
}
