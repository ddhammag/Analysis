// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"

class jetAnalyzer : public edm::EDAnalyzer {

public:
   explicit jetAnalyzer(const edm::ParameterSet&);
   ~jetAnalyzer();
  
private:

   virtual void beginJob() ;
   virtual void analyze(const edm::Event&, const edm::EventSetup&);
   virtual void endJob() ;
  
   // simple map to contain all histograms; 
   // histograms are booked in the beginJob() 
   // method
   std::map<std::string,TH1F*> histContainer_; 
   // ----------member data ---------------------------     
   //edm::EDGetTokenT<pat::MuonCollection> muonCollToken;
   //edm::EDGetTokenT<pat::ElectronCollection> elecCollToken;
   //edm::EDGetTokenT<pat::JetCollection> jetCollToken;
 edm::EDGetTokenT jetCollToken;
};


jetAnalyzer::jetAnalyzer(const edm::ParameterSet& iConfig):

   histContainer_(),
   jetCollToken(consumes(iConfig.getParameter("slimmedJets")))
   {

  //edm::InputTag muonTag("slimmedMuons");
  //edm::InputTag genPartTag("slimmedElectrons");
 // edm::InputTag jetTag("slimmedJets");

  // muonCollToken = consumes<pat::MuonCollection>(muonTag);
 // elecCollToken = consumes<pat::ElectronCollection>(genPartTag);
 // jetCollToken = consumes<pat::JetCollection>(jetTag);

}

jetAnalyzer::~jetAnalyzer(){
}

void
jetAnalyzer::analyze(const edm::Event& iEvent, 
                         const edm::EventSetup& iSetup){

   // get pat jet collection 
   edm::Handle< std::vector<pat::Jet>> jet;
   iEvent.getByToken(jetCollToken, jet);
  int ijet = 0;
   // fill pat muon histograms
   for (auto j = jet->cbegin(); j != jet->cend(); ++j) {
      histContainer_["muonPt"] ->Fill(j->pt());
      histContainer_["muonEta"]->Fill(j->eta());
      histContainer_["muonPhi"]->Fill(j->phi());

      if( j->pt()>20){
      printf("jet  with pt %5.1f (raw pt %5.1f), eta %+4.2f, btag CSV %.3f, CISV %.3f, pileup mva disc %+.2f\n",
            j->pt(), j->pt()*j->jecFactor("Uncorrected"), j->eta(), std::max(0.f,j->bDiscriminator("combinedSecondaryVertexBJetTags")), std::max(0.f,j->bDiscriminator("combinedInclusiveSecondaryVertexBJetTags")), j->userFloat("pileupJetId:fullDiscriminant"));
 
      /*   if ((++ijet) == 1) { // for the first jet, let's print the leading constituents
            std::vector daus(j->daughterPtrVector());
            std::sort(daus.begin(), daus.end(), [](const reco::CandidatePtr &p1, const reco::CandidatePtr &p2) { return p1->pt() > p2->pt(); }); // the joys of C++11
            for (unsigned int i2 = 0, n = daus.size(); i2 < n && i2 <= 3; ++i2) {
                const pat::PackedCandidate &cand = dynamic_cast<const pat::PackedCandidate &>(*daus[i2]);
                printf("         constituent %3d: pt %6.2f,  pdgId %+3d\n", i2,cand.pt(),cand.pdgId());
            }
        }*/
      }
   }
 
   
}

void 
jetAnalyzer::beginJob()
{
   // register to the TFileService
   edm::Service<TFileService> fs;


   histContainer_["mumuMass"]=fs->make<TH1F>("mumuMass", "mass",    90,   30., 120.);
  
   // book histograms for Multiplicity:

   histContainer_["eleMult"]=fs->make<TH1F>("eleMult",   "electron multiplicity", 100, 0,  50);
   histContainer_["muonMult"]=fs->make<TH1F>("muonMult",   "muon multiplicity",     100, 0,  50);

   // book histograms for Pt:

   histContainer_["elePt"]=fs->make<TH1F>("elePt",   "electron Pt", 100, 0,  200);
   histContainer_["muonPt"]=fs->make<TH1F>("muonPt",   "muon Pt", 100, 0, 200);

   // book histograms for Eta:
   histContainer_["eleEta"]=fs->make<TH1F>("eleEta",   "electron Eta",100, -5,  5);
   histContainer_["muonEta"]=fs->make<TH1F>("muonEta",   "muon Eta",  100, -5,  5);


   // book histograms for Phi:
   histContainer_["elePhi"]=fs->make<TH1F>("elePhi",   "electron Phi", 100, -3.5, 3.5);
   histContainer_["muonPhi"]=fs->make<TH1F>("muonPhi",   "muon Phi",     100, -3.5, 3.5);
    
}

void 
jetAnalyzer::endJob() 
{
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(jetAnalyzer);
 
