void dr(){
  double eta1 = 0.294023; double phi1 = 0.392597;
  double eta2 = 0.185144; double phi2 = 0.241317;

  double deltaR=0;
  double Dphi=phi1-phi2;
  double Deta=eta1-eta2;
  double pi = TMath::Pi();

  if( fabs(Dphi)>pi ) {
    if( Dphi>0 ){
      Dphi = 2*pi-Dphi;
    }
    else{
      Dphi = 2*pi+Dphi;
    }
  }

  deltaR=sqrt( pow(Deta,2)+pow(Dphi,2) );

  cout << "deltaR = "<<deltaR<<endl;

}
