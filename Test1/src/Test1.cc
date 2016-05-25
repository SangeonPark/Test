// -*- C++ -*-
//
// Package:    Test1
// Class:      Test1
// 
/**\class Test1 Test1.cc Test/Test1/src/Test1.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Sang Eon Park,,,
//         Created:  Tue May 24 11:20:11 CEST 2016
// $Id$
//
//


// system include files
#include "Test/Test1/interface/Test1.h"


//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
Test1::Test1(const edm::ParameterSet& iConfig)

{

    nHitCut_ = iConfig.getParameter<int>("nHitCut");
    dxySigCut_ = iConfig.getParameter<double>("dxySigCut");
    dzSigCut_ = iConfig.getParameter<double>("dzSigCut");
    etaCutMin_ = iConfig.getParameter<double>("etaCutMin");
    etaCutMax_ = iConfig.getParameter<double>("etaCutMax");

    
    trackSrc_ = iConfig.getParameter<edm::InputTag>("trackSrc");
    vertexSrc_ = iConfig.getParameter<std::string>("vertexSrc");
    
   //now do what ever initialization is needed

}


Test1::~Test1()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
Test1::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    using namespace edm;
    
    edm::Handle<reco::VertexCollection> vertices;
    iEvent.getByLabel(vertexSrc_,vertices);
    double bestvz=-999.9, bestvx=-999.9, bestvy=-999.9;
    double bestvzError=-999.9, bestvxError=-999.9, bestvyError=-999.9;
    const reco::Vertex & vtx = (*vertices)[0];
    bestvz = vtx.z(); bestvx = vtx.x(); bestvy = vtx.y();
    bestvzError = vtx.zError(); bestvxError = vtx.xError(); bestvyError = vtx.yError();
    if(bestvz < -15.0 || bestvz>15.0) return;

    cout << "test: " << bestvz << bestvx << bestvy << bestvzError << bestvxError << bestvyError;
    
    
    edm::Handle<reco::TrackCollection> tracks;
    iEvent.getByLabel(trackSrc_, tracks);

/*
    for( reco::TrackCollection::const_iterator cand = tracks->begin(); cand != tracks->end(); cand++){

	double eta = cand->eta();
	double charge = (double)cand->charge();
	double pt = cand->pt();
	double phi = cand->phi();

	//eta cut
	if(eta > etaCutMax_ || eta < etaCutMin_) continue;

	//trkNHits cut
	int nhit = tracks->numberOfValidHits();
	if(nhit <= nHitCut_) continue;

	//DCA
	math::XYZPoint bestvtx(bestvx,bestvy,bestvz);

	double dzbest = tracks->dz(bestvtx);
	double dxybest = tracks->dxy(bestvtx);
	double dzerror = sqrt(tracks->dzError()*tracks->dzError()+bestvzError*bestvzError);
	double dxyerror = sqrt(tracks->d0Error()*tracks->d0Error()+bestvxError*bestvyError);
	double dzos = dzbest/dzerror;
	double dxyos = dxybest/dxyerror;
	
	if( dzSigCut_ <= fabs(dzos) || dxySigCut_ <= fabs(dxyos) ) continue;

	double data[7]={pt,eta,phi,charge,dzos,dxyos,nhit};
	track_Data->Fill(data);
    }
*/
}


// ------------ method called once each job just before starting event loop  ------------
void 
Test1::beginJob()
{
    edm::Service<TFileService> fs;
    TH1D::SetDefaultSumw2();
    track_Data = fs->make<TNtuple>("track_Data","track_Data","pt:eta:phi:charge:dzos:dxyos:nhit");
    
}

// ------------ method called once each job just after ending the event loop  ------------
void 
Test1::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
Test1::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
Test1::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
Test1::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
Test1::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
Test1::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(Test1);
