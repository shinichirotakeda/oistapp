

void mk_flatmicroPhantom_phi15mm(){

  gROOT->Reset();
  int nbinx = 675;
  int nbiny = 675;

  TH2D *hout = new TH2D("phantom","phantom",nbinx,-0.75,0.75,nbiny,-0.75,0.75);

  for(int i=1;i<=nbinx;i++){
    for(int j=1;j<=nbiny;j++){
      double x = hout->GetXaxis()->GetBinCenter(i);
      double y = hout->GetYaxis()->GetBinCenter(j);
      double r = TMath::Sqrt(x*x+y*y);
      if(r<=0.75){
	hout->SetBinContent(i,j,1.0);
      }
    }
  }


  TFile *fout = new TFile("microFlatPhantom_phi1.5cm.root","recreate");
  fout->cd();
  hout->Write();
  fout->Close();


}
