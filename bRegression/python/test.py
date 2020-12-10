import FWCore.ParameterSet.Config as cms

process = cms.Process("bRegression")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("Configuration.EventContent.EventContent_cff")
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')


process.MessageLogger.cerr.FwkReport.reportEvery = 250

### do not remove the line below!
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(5000) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )


process.source = cms.Source("PoolSource",
	skipEvents = cms.untracked.uint32(0),
    fileNames = cms.untracked.vstring(
    #'file:/lustre/cms/store/user/mmaggi/HH_signal_2017_new/HH_signal_2017_new_desh/histos4mu_25ns_FR_step1_2017_questions_PU_new_new/output_GluGluToContinToZZTo4e_13TeV_MCFM701_pythia8.root',
    'root://xrootd-cms.infn.it:1194//store/group/phys_higgs/cmshmm/amarini/ZbbZhadJJ_EWK_LO_SM_mjj100_pTj10_13TeV_madgraphMLM_pythia8/FullSim_94X-MINIAODSIM/191118_105306/0000/step4_1.root',
    #'root://eoscms.cern.ch//eos/cms/store/data/Run2017B/DoubleMuon/MINIAOD/31Mar2018-v1/90000/FEA296CB-1737-E811-9CBF-90B11C0BD35F.root',
    #'root://eoscms.cern.ch//eos/cms/store/data/Run2018B/MET/MINIAOD/17Sep2018-v1/270000/FA6FE75E-BED4-D240-B41D-E4D9134A88B5.root',
     #   'file:myfile.root'
    )    
)

# ---- define the output file -------------------------------------------
process.TFileService = cms.Service("TFileService",
    closeFileFast = cms.untracked.bool(True),
    fileName = cms.string("bRegressionNtuples.root"),
)


### BRegression
#process.load('bRegression.bRegression.bRegression')
#process.bRegression.JetTag = process.nero.NeroJets.jets

process.bRegressionProducer= cms.EDProducer('bRegression',
#                                               JetTag=coll,
                                           JetTag=cms.InputTag("slimmedJets"),#,"0"),
                                           svCollection=cms.InputTag("slimmedSecondaryVertices"),
                                           vtxCollection=cms.InputTag("offlineSlimmedPrimaryVertices"),
                                           rhoFixedGridCollection=cms.InputTag("fixedGridRhoFastjetAll"),
                                           #bRegressionWeightfile= cms.untracked.string("file:/afs/cern.ch/user/n/nchernya/public/breg_training/2017_JECv32/breg_training_2017_updated.pb"),
                                           #bRegressionWeightfile=cms.untracked.string("model_2017_JECv32.hdf5"), 
                                           bRegressionWeightfile=cms.untracked.string("./graph/model-51.pb"), 
                                           y_mean = cms.untracked.double(1.0454729795455933),
                                           y_std =cms.untracked.double( 0.31628304719924927)
                                           )
#------------------------------------------------------

## DEBUG -- dump the event content with all the value maps ..
process.output = cms.OutputModule("PoolOutputModule",
                      fileName = cms.untracked.string('output1.root'),
                      outputCommands = cms.untracked.vstring("drop *",
                      "keep *_bRegressionProducer_*_*")
                      )
                    
process.p = cms.Path(process.bRegressionProducer)
#process.output_step = cms.EndPath(process.output)

process.e = cms.EndPath(process.output)
#
process.schedule = cms.Schedule(
		process.p,
		process.e)

# Local Variables:
# mode:python
# indent-tabs-mode:nil
# tab-width:4
# c-basic-offset:4
# End:
# vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
