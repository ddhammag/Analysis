import FWCore.ParameterSet.Config as cms

process = cms.Process("jetAnalyzer")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.MessageLogger.cerr.FwkReport.reportEvery = 1

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(5) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
    #'file:/lustre/cms/store/user/mmaggi/HH_signal_2017_new/HH_signal_2017_new_desh/histos4mu_25ns_FR_step1_2017_questions_PU_new_new/output_GluGluToContinToZZTo4e_13TeV_MCFM701_pythia8.root',
    'root://eoscms.cern.ch//eos/cms/store/data/Run2017B/DoubleMuon/MINIAOD/31Mar2018-v1/90000/FEA296CB-1737-E811-9CBF-90B11C0BD35F.root',
     #   'file:myfile.root'
    )
)

process.demo = cms.EDAnalyzer("jetAnalyzer"
)

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('myjet.root')
                                   )
                                   
process.p = cms.Path(process.demo)
