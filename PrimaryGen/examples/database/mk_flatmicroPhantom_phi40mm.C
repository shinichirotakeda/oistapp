

void mk_flatmicroPhantom_phi40mm(){

  gROOT->Reset();
  int nbinx = 900;
  int nbiny = 900;

  TH2D *hout = new TH2D("phantom","phantom",nbinx,-2.0,2.0,nbiny,-2.0,2.0);

  for(int i=1;i<=nbinx;i++){
    for(int j=1;j<=nbiny;j++){
      double x = hout->GetXaxis()->GetBinCenter(i);
      double y = hout->GetYaxis()->GetBinCenter(j);
      double r = TMath::Sqrt(x*x+y*y);
      if(r<=2.0){
	hout->SetBinContent(i,j,1.0);
      }
    }
  }


  TFile *fout = new TFile("microFlatPhantom_phi4.0cm.root","recreate");
  fout->cd();
  hout->Write();
  fout->Close();


}
