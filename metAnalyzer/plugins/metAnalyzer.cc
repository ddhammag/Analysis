// -*- C++ -*-
//
// Package:    resoDiHiggs/metAnalyzer
// Class:      metAnalyzer
// 
/**\class metAnalyzer metAnalyzer.cc resoDiHiggs/metAnalyzer/plugins/metAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Deshitha Dhammage
//         Created:  Tue, 25 Aug 2020 03:39:52 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/PatCandidates/interface/MET.h"
//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class metAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit metAnalyzer(const edm::ParameterSet&);
      ~metAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;
      
      // ----------member data ---------------------------
      edm::EDGetTokenT<edm::View<pat::MET>> metToken_;
      int nEvent;
};
//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
metAnalyzer::metAnalyzer(const edm::ParameterSet& iConfig)

{
  metToken_=(consumes<edm::View<pat::MET>>(iConfig.getParameter<edm::InputTag>("mets")));

  nEvent=0;
   //now do what ever initialization is needed
   usesResource("TFileService");

}


metAnalyzer::~metAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
metAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

  Handle<View<pat::MET> > mets;
  iEvent.getByToken(metToken_,mets);
  const pat::MET &met = mets->front();

  // Print event information
  std::cout << "run " << iEvent.id().run()
       << " lumi " << iEvent.id().luminosityBlock()
       << " event " << iEvent.id().event();
  // Print corr MET (default out-of-box)
  std::cout << " pt " <<  met.pt() 
       << " px " <<  met.px() 
       << " py " <<  met.py() 
       << " phi " <<  met.phi() 
       << std::endl;

  nEvent++;
}


// ------------ method called once each job just before starting event loop  ------------
void 
metAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
metAnalyzer::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
metAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(metAnalyzer);
