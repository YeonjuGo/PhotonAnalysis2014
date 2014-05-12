# -*- coding: utf-8 -*-
# Auto generated configuration file
# using: 
# Revision: 1.381.2.28 
# Source: /local/reps/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: Configuration/GenProduction/Pyquen_AllQCDPhotons_PtHat30_PhotonFilter_pt35GeV_eta3_TuneZ2_Unquenched_2760GeV_cfi -n 10 -s GEN,SIM,DIGI,L1,DIGI2RAW,HLT:HIon --conditions STARTHI53_LV1::All --scenario HeavyIons --himix --datatier GEN-SIM-RAW --eventcontent=RAW --filein file:/mnt/hadoop/cms/store/user/yetkin/MC_Production/HydjetDrum03/HydjetDrum03_HiForest_v05_merged_test02.root --processName HISIGNAL ? --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('HISIGNAL')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')
process.load('SimGeneral.MixingModule.HiEventMixing_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.GeometrySimDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic8TeVCollision_cfi')
process.load('SimGeneral.MixingModule.himixGEN_cff')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('SimGeneral.MixingModule.himixSIMIdeal_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.DigiHiMix_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('HLTrigger.Configuration.HLT_HIon_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10)
)

# Input source
process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
    fileNames = cms.untracked.vstring('/store/himc/HiFall13/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM/STARTHI53_V28-v2/00000/02B3F103-995E-E311-BD92-003048C9AC48.root'),
#fileNames = cms.untracked.vstring('/store/user/rkunnawa/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/HIMinBias2011_Hydjet_2760GeV_STARTHI53_LV1_20Feb2014_1211EST_Track8_Jet14/f800faea92f26219290cf07bacf415bf/'),
#fileNames = cms.untracked.vstring('file:merged_hydjet_53X_test02.root'),
#fileNames = cms.untracked.vstring('file:/mnt/hadoop/cms/store/user/yetkin/MC_Production/HydjetDrum03/HydjetDrum03_HiForest_v05_merged_test02.root'),
    inputCommands = cms.untracked.vstring('drop *', 
        'keep *_generator_*_*', 
        'keep *_g4SimHits_*_*'),
    dropDescendantsOfDroppedBranches = cms.untracked.bool(False)
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.381.2.28 $'),
    annotation = cms.untracked.string('Configuration/GenProduction/Pyquen_AllQCDPhotons_PtHat30_PhotonFilter_pt35GeV_eta3_TuneZ2_Unquenched_2760GeV_cfi nevts:10'),
    name = cms.untracked.string('PyReleaseValidation')
)

# Output definition

process.RAWoutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    outputCommands = process.RAWEventContent.outputCommands,
    fileName = cms.untracked.string('Pyquen_AllQCDPhotons_PtHat30_PhotonFilter_pt35GeV_eta3_TuneZ2_Unquenched_2760GeV_cfi_GEN_SIM_DIGI_L1_DIGI2RAW_HLT.root'),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('GEN-SIM-RAW')
    ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    )
)

# Additional output definition

# Other statements
process.genstepfilter.triggerConditions=cms.vstring("generation_step")
from HLTrigger.Configuration.CustomConfigs import ProcessName
process = ProcessName(process)

from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'STARTHI53_LV1::All', '')

process.hiSignal = cms.EDFilter("PyquenGeneratorFilter",
    comEnergy = cms.double(2760.0),
    partonStatus = cms.vint32(2, 2, 2, 2, 2, 
        2, 2, 1),
    etaMax = cms.double(3.0),
    maxTries = cms.untracked.int32(5000),
    doCollisionalEnLoss = cms.bool(False),
    doQuench = cms.bool(False),
    qgpInitialTemperature = cms.double(1.0),
    cFlag = cms.int32(0),
    backgroundLabel = cms.InputTag("generator"),
    bMax = cms.double(0.0),
    angularSpectrumSelector = cms.int32(0),
    particles = cms.vint32(22),
    particlePt = cms.vdouble(35),
    hadronFreezoutTemperature = cms.double(0.14),
    particleStatus = cms.vint32(1),
    qgpNumQuarkFlavor = cms.int32(0),
    partons = cms.vint32(1, 2, 3, 4, 5, 
        6, 21, 22),
    doRadiativeEnLoss = cms.bool(True),
    bFixed = cms.double(0.0),
    doIsospin = cms.bool(True),
    filterType = cms.untracked.string('EcalGenEvtSelectorFrag'),
    bMin = cms.double(0.0),
    numQuarkFlavor = cms.int32(0),
    aBeamTarget = cms.double(208.0),
    PythiaParameters = cms.PSet(
        myParameters = cms.vstring(),
        pythiaZtoElectrons = cms.vstring('MDME(174,1)=0', 
            'MDME(175,1)=0', 
            'MDME(176,1)=0', 
            'MDME(177,1)=0', 
            'MDME(178,1)=0', 
            'MDME(179,1)=0', 
            'MDME(182,1)=1', 
            'MDME(183,1)=0', 
            'MDME(184,1)=0', 
            'MDME(185,1)=0', 
            'MDME(186,1)=0', 
            'MDME(187,1)=0'),
        pythiaWeakBosons = cms.vstring('MSUB(1)=1', 
            'MSUB(2)=1'),
        pythiaZtoMuons = cms.vstring('MDME(174,1)=0', 
            'MDME(175,1)=0', 
            'MDME(176,1)=0', 
            'MDME(177,1)=0', 
            'MDME(178,1)=0', 
            'MDME(179,1)=0', 
            'MDME(182,1)=0', 
            'MDME(183,1)=0', 
            'MDME(184,1)=1', 
            'MDME(185,1)=0', 
            'MDME(186,1)=0', 
            'MDME(187,1)=0'),
        ppJets = cms.vstring('MSEL=1   ! QCD hight pT processes'),
        pythiaUpsilonToMuons = cms.vstring('BRAT(1034) = 0 ', 
            'BRAT(1035) = 1 ', 
            'BRAT(1036) = 0 ', 
            'BRAT(1037) = 0 ', 
            'BRAT(1038) = 0 ', 
            'BRAT(1039) = 0 ', 
            'BRAT(1040) = 0 ', 
            'BRAT(1041) = 0 ', 
            'BRAT(1042) = 0 ', 
            'MDME(1034,1) = 0 ', 
            'MDME(1035,1) = 1 ', 
            'MDME(1036,1) = 0 ', 
            'MDME(1037,1) = 0 ', 
            'MDME(1038,1) = 0 ', 
            'MDME(1039,1) = 0 ', 
            'MDME(1040,1) = 0 ', 
            'MDME(1041,1) = 0 ', 
            'MDME(1042,1) = 0 '),
        ppDefault = cms.vstring('MSEL=1   ! QCD hight pT processes (only jets)', 
            'CKIN(3)=6.', 
            'MSTP(81)=0'),
        pythiaZjets = cms.vstring('MSUB(15)=1', 
            'MSUB(30)=1'),
        allQCDPhotonChannel = cms.vstring('MSUB(11)=1', 
            'MSUB(12)=1', 
            'MSUB(13)=1', 
            'MSUB(28)=1', 
            'MSUB(53)=1', 
            'MSUB(68)=1', 
            'MSUB(14)=1', 
            'MSUB(18)=1', 
            'MSUB(29)=1', 
            'MSUB(114)=1', 
            'MSUB(115)=1'),
        pythiaMuonCandidates = cms.vstring('CKIN(3)=20', 
            'MSTJ(22)=2', 
            'PARJ(71)=40.'),
        pythiaQuarkoniaSettings = cms.vstring('PARP(141)=1.16', 
            'PARP(142)=0.0119', 
            'PARP(143)=0.01', 
            'PARP(144)=0.01', 
            'PARP(145)=0.05', 
            'PARP(146)=9.28', 
            'PARP(147)=0.15', 
            'PARP(148)=0.02', 
            'PARP(149)=0.02', 
            'PARP(150)=0.085', 
            'PARJ(13)=0.60', 
            'PARJ(14)=0.162', 
            'PARJ(15)=0.018', 
            'PARJ(16)=0.054', 
            'MSTP(145)=0', 
            'MSTP(146)=0', 
            'MSTP(147)=0', 
            'MSTP(148)=1', 
            'MSTP(149)=1', 
            'BRAT(861)=0.202', 
            'BRAT(862)=0.798', 
            'BRAT(1501)=0.013', 
            'BRAT(1502)=0.987', 
            'BRAT(1555)=0.356', 
            'BRAT(1556)=0.644'),
        kinematics = cms.vstring('CKIN(3)=30', 
            'CKIN(4)=9999'),
        pythiaJpsiToMuons = cms.vstring('BRAT(858) = 0 ', 
            'BRAT(859) = 1 ', 
            'BRAT(860) = 0 ', 
            'MDME(858,1) = 0 ', 
            'MDME(859,1) = 1 ', 
            'MDME(860,1) = 0 '),
        pythiaBottomoniumNRQCD = cms.vstring('MSUB(461) = 1', 
            'MSUB(462) = 1', 
            'MSUB(463) = 1', 
            'MSUB(464) = 1', 
            'MSUB(465) = 1', 
            'MSUB(466) = 1', 
            'MSUB(467) = 1', 
            'MSUB(468) = 1', 
            'MSUB(469) = 1', 
            'MSUB(470) = 1', 
            'MSUB(471) = 1', 
            'MSUB(472) = 1', 
            'MSUB(473) = 1', 
            'MSUB(474) = 1', 
            'MSUB(475) = 1', 
            'MSUB(476) = 1', 
            'MSUB(477) = 1', 
            'MSUB(478) = 1', 
            'MSUB(479) = 1'),
        hydjetPythiaDefault = cms.vstring('MSEL=0   ! user processes', 
            'CKIN(3)=6.', 
            'MSTP(81)=0'),
        parameterSets = cms.vstring('pythiaUESettingsZ2Tune', 
            'customProcesses', 
            'allQCDPhotonChannel', 
            'kinematics'),
        pythiaPromptPhotons = cms.vstring('MSUB(14)=1', 
            'MSUB(18)=1', 
            'MSUB(29)=1', 
            'MSUB(114)=1', 
            'MSUB(115)=1'),
        customProcesses = cms.vstring('MSEL=0   ! User processes'),
        pythiaCharmoniumNRQCD = cms.vstring('MSUB(421) = 1', 
            'MSUB(422) = 1', 
            'MSUB(423) = 1', 
            'MSUB(424) = 1', 
            'MSUB(425) = 1', 
            'MSUB(426) = 1', 
            'MSUB(427) = 1', 
            'MSUB(428) = 1', 
            'MSUB(429) = 1', 
            'MSUB(430) = 1', 
            'MSUB(431) = 1', 
            'MSUB(432) = 1', 
            'MSUB(433) = 1', 
            'MSUB(434) = 1', 
            'MSUB(435) = 1', 
            'MSUB(436) = 1', 
            'MSUB(437) = 1', 
            'MSUB(438) = 1', 
            'MSUB(439) = 1'),
        pythiaZtoMuonsAndElectrons = cms.vstring('MDME(174,1)=0', 
            'MDME(175,1)=0', 
            'MDME(176,1)=0', 
            'MDME(177,1)=0', 
            'MDME(178,1)=0', 
            'MDME(179,1)=0', 
            'MDME(182,1)=1', 
            'MDME(183,1)=0', 
            'MDME(184,1)=1', 
            'MDME(185,1)=0', 
            'MDME(186,1)=0', 
            'MDME(187,1)=0'),
        pythiaJets = cms.vstring('MSUB(11)=1', 
            'MSUB(12)=1', 
            'MSUB(13)=1', 
            'MSUB(28)=1', 
            'MSUB(53)=1', 
            'MSUB(68)=1'),
        pythiaUESettingsZ2Tune = cms.vstring('MSTU(21)=1     ! Check on possible errors during program execution', 
            'MSTJ(22)=2     ! Decay those unstable particles', 
            'PARJ(71)=10 .  ! for which ctau  10 mm', 
            'MSTP(33)=0     ! no K factors in hard cross sections', 
            'MSTP(2)=1      ! which order running alphaS', 
            'MSTP(51)=10042 ! structure function chosen (external PDF CTEQ6L1)', 
            'MSTP(52)=2     ! work with LHAPDF', 
            'PARP(82)=1.832 ! pt cutoff for multiparton interactions', 
            'PARP(89)=1800. ! sqrts for which PARP82 is set', 
            'PARP(90)=0.275 ! Multiple interactions: rescaling power', 
            'MSTP(95)=6     ! CR (color reconnection parameters)', 
            'PARP(77)=1.016 ! CR', 
            'PARP(78)=0.538 ! CR', 
            'PARP(80)=0.1   ! Prob. colored parton from BBR', 
            'PARP(83)=0.356 ! Multiple interactions: matter distribution parameter', 
            'PARP(84)=0.651 ! Multiple interactions: matter distribution parameter', 
            'PARP(62)=1.025 ! ISR cutoff', 
            'MSTP(91)=1     ! Gaussian primordial kT', 
            'PARP(93)=10.0  ! primordial kT-max', 
            'MSTP(81)=21    ! multiple parton interactions 1 is Pythia default', 
            'MSTP(82)=4     ! Defines the multi-parton model'),
        pythiaHirootDefault = cms.vstring('MSEL=0', 
            'MSTU(21)=1', 
            'PARU(14)=1.', 
            'MSTP(81)=0', 
            'PMAS(5,1)=4.8', 
            'PMAS(6,1)=175.0', 
            'CKIN(3)=7.', 
            'MSTJ(22)=2', 
            'PARJ(71)=10.', 
            'PARP(67)=1.', 
            'PARP(82)=1.9', 
            'PARP(85)=0.33', 
            'PARP(86)=0.66', 
            'PARP(89)=1000.', 
            'PARP(91)=1.0', 
            'MSTJ(11)=3', 
            'MSTJ(22)=2')
    ),
    embeddingMode = cms.bool(True),
    partonPt = cms.vdouble(38.5, 38.5, 38.5, 38.5, 38.5, 
        38.5, 38.5, 38.5),
    qgpProperTimeFormation = cms.double(0.1)
)


# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen_hi)
process.simulation_step = cms.Path(process.psim)
process.digitisation_step = cms.Path(process.pdigi)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RAWoutput_step = cms.EndPath(process.RAWoutput)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.genfiltersummary_step,process.simulation_step,process.digitisation_step,process.L1simulation_step,process.digi2raw_step)
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.endjob_step,process.RAWoutput_step])

# customisation of the process.

# Automatic addition of the customisation function from HLTrigger.Configuration.customizeHLTforMC
from HLTrigger.Configuration.customizeHLTforMC import customizeHLTforMC 

#call to customisation function customizeHLTforMC imported from HLTrigger.Configuration.customizeHLTforMC
process = customizeHLTforMC(process)

# End of customisation functions
process.SimpleMemoryCheck=cms.Service("SimpleMemoryCheck",
                                              oncePerEventMode=cms.untracked.bool(False))

process.Timing=cms.Service("Timing",
                                useJobReport = cms.untracked.bool(True)
                                                          )
