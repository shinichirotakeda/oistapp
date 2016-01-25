


void fukuchiPhantom2microPhantom(){

  gROOT->Reset();
  TFile *fin = new TFile("fukuchiPhantom.root");
  TH2D *hin = (TH2D *)fin->Get("phantom");

  int nbinx = hin->GetXaxis()->GetNbins();
  int nbiny = hin->GetYaxis()->GetNbins();


  TH2D *hout = new TH2D("phantom","phantom",nbinx,-0.5,0.5,nbiny,-0.5,0.5);

  for(int i=1;i<=nbinx;i++){
    for(int j=1;j<=nbiny;j++){
      double v = hin->GetBinContent(i,j);
      hout->SetBinContent(i,j,v);
    }
  }


  TFile *fout = new TFile("microPhantom.root","recreate");
  fout->cd();
  hout->Write();
  fout->Close();

}

  
