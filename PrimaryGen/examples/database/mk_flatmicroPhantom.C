

void mk_flatmicroPhantom(){

  gROOT->Reset();
  int nbinx = 450;
  int nbiny = 450;

  TH2D *hout = new TH2D("phantom","phantom",nbinx,-0.5,0.5,nbiny,-0.5,0.5);

  for(int i=1;i<=nbinx;i++){
    for(int j=1;j<=nbiny;j++){
      double x = hout->GetXaxis()->GetBinCenter(i);
      double y = hout->GetYaxis()->GetBinCenter(j);
      double r = TMath::Sqrt(x*x+y*y);
      if(r<=0.5){
	hout->SetBinContent(i,j,1.0);
      }
    }
  }


  TFile *fout = new TFile("microFlatPhantom_phi1cm.root","recreate");
  fout->cd();
  hout->Write();
  fout->Close();


}
