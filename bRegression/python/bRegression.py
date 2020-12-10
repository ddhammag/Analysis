import FWCore.ParameterSet.Config as cms

#from flashgg.Taggers.flashggTags_cff import UnpackedJetCollectionVInputTag
#from flashgg.Taggers.flashggTags_cff import flashggUnpackedJets

#recoJetCollections = UnpackedJetCollectionVInputTag

#print recoJetCollections

#for icoll,coll in enumerate(recoJetCollections):
bRegression= cms.EDProducer('bRegression',
#                                               JetTag=coll,
                                           JetTag=cms.InputTag("slimmedJets"),#,"0"),
                                           svCollection=cms.InputTag("slimmedSecondaryVertices"),
                                           vtxCollection=cms.InputTag("offlineSlimmedPrimaryVertices"),
                                           rhoFixedGridCollection=cms.InputTag("fixedGridRhoFastjetAll"),
                                           bRegressionWeightfile= cms.untracked.string("/lustrehome/ddhammag/CMSSW_9_4_9/src/bRegression/bRegression/data/breg_training_2017"), 
                                           y_mean = cms.untracked.double(1.0454729795455933),
                                           y_std =cms.untracked.double( 0.31628304719924927)
                                           )

