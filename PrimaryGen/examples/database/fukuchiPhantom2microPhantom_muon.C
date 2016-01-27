


void fukuchiPhantom2microPhantom_muon(){

  gROOT->Reset();
  TFile *fin = new TFile("fukuchiPhantom.root");
  TH2D *hin = (TH2D *)fin->Get("phantom");

  int nbinx = hin->GetXaxis()->GetNbins();
  int nbiny = hin->GetYaxis()->GetNbins();


  TH2D *hout = new TH2D("phantom","phantom",nbinx,-1.0,1.0,nbiny,-1.0,1.0);

  for(int i=1;i<=nbinx;i++){
    for(int j=1;j<=nbiny;j++){
      double v = hin->GetBinContent(i,j);
      hout->SetBinContent(i,j,v);
    }
  }


  TFile *fout = new TFile("microPhantom_muon.root","recreate");
  fout->cd();
  hout->Write();
  fout->Close();

}

  
