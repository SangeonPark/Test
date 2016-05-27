void ach_dist(){

    using namespace std;
    TFile *f = TFile::Open("trackData.root");
    TNtuple *T = (TNtuple*)f->Get("demo/track_Data");
    TH1F *h1 = new TH1F("h1","Distribution of Charge Asymmetry",25,-0.2,0.2);

    TCanvas *c1 = new TCanvas("c1","c1",50,50,800,600);

    Double_t charge;

    T->SetBranchAddress("charge",&charge);

    Int_t i,nentries;
    nentries = (Int_t) T->GetEntries();

    for(i=0;i<nentries;i++){
	T->GetEntry(i);
	
