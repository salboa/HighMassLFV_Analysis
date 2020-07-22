{
  //                etau       mutau
  double dataSRSS = 18882;   //11077;
  double DYSRSS   = 2762.9;  //1300.25;
  double TopSRSS  = 3285.19; //2199.19;
  double DibSRSS  = 625.835; //430.708;
  double wjSRSS   = 7695.04; //5394.39;
  double NqcdSR   = 4513.03; //1752.46;
  

  double dataCRSS = 35888;   //6360;
  double DYCRSS   = 460.37;  //89.0968;
  double TopCRSS  = 529.833; //47.2738;
  double DibCRSS  = 51.1199; //13.8027;
  double wjCRSS   = 2298.1;  //453.649;
  double NqcdCR   = 32548.6; //5714;
  
  double NumErr2 = ( pow( sqrt(dataSRSS),2 ) +
		     pow( sqrt(DYSRSS),2 )   +
		     pow( sqrt(TopSRSS),2 )  +
		     pow( sqrt(DibSRSS),2 )  +
		     pow( sqrt(wjSRSS),2  )  )/pow(NqcdCR,2) ;
  
  double DenErr2 = ( pow( sqrt(dataCRSS),2 )+
		     pow( sqrt(DYCRSS),2 )  +
		     pow( sqrt(TopCRSS),2 ) +
		     pow( sqrt(DibCRSS),2 ) +
		     pow( sqrt(wjCRSS),2 )  )*
    (NqcdSR/pow( NqcdCR,4 ));
  
  double ErrSF = sqrt( NumErr2+DenErr2 );

  cout << "err = "<< ErrSF << endl;

}
