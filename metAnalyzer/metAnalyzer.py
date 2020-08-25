import FWCore.ParameterSet.Config as cms

process = cms.Process("metAnalyzer")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.MessageLogger.cerr.FwkReport.reportEvery = 1

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(5) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
    #'file:/lustre/cms/store/user/mmaggi/HH_signal_2017_new/HH_signal_2017_new_desh/histos4mu_25ns_FR_step1_2017_questions_PU_new_new/output_GluGluToContinToZZTo4e_13TeV_MCFM701_pythia8.root',
    'root://eoscms.cern.ch//eos/cms/store/data/Run2017B/DoubleMuon/MINIAOD/31Mar2018-v1/90000/FEA296CB-1737-E811-9CBF-90B11C0BD35F.root',
    #'root://eoscms.cern.ch//eos/cms/store/data/Run2018B/MET/MINIAOD/17Sep2018-v1/270000/FA6FE75E-BED4-D240-B41D-E4D9134A88B5.root',
     #   'file:myfile.root'
    )
)

#process.demo = cms.EDAnalyzer("metAnalyzer"
#)
process.demo = cms.EDAnalyzer('metAnalyzer',
                              mets = cms.InputTag("slimmedMETs"),
#                              metSrc = cms.untracked.InputTag("slimmedMETs")
)

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('mymet.root')
                                   )
                                   
process.p = cms.Path(process.demo)
