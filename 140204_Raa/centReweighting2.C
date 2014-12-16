#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TH1D.h"
#include "TCut.h"
#include "TProfile.h"
#include "TGraphAsymmErrors.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TROOT.h"
#include "TString.h"
#include "TLatex.h"
#include "TStyle.h"
#include "stdio.h"
#include <iostream>
#include "../gammaJetAnalysis/commonUtility.h"
#include "../gammaJetAnalysis/yj_fitResult.h"

void centReweighting(int collision=1){
const Int_t CENTBINS[] = {0, 12, 40};//, 40};
    TString DATA_FILE;
    TString MC_FILE;
    TString LABEL;
    TString centCut;
    TCut sampleIsolation;
    if (collision ==0){
        // //pp
        DATA_FILE = "/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pp/yskim_pp_photonSKimForest_v85.root";
        MC_FILE = "/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pp/yskim_pp2760_pythia_allQCDPhoton_CMSSW538HIp2.root";
        LABEL = "pp #sqrt{s}_{_{NN}}=2.76 TeV";
        sampleIsolation = "ecalRecHitSumEtConeDR04 < 4.2  &&  hcalTowerSumEtConeDR04 < 2.2  &&  trkSumPtHollowConeDR04 < 2 && hadronicOverEm<0.1";
        centCut =""; 
    }else if(collision ==2 || collision ==3){
        //PbPb
        DATA_FILE = "/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pbpb/yskim_HiForestPhoton-v7-noDuplicate.root";
        MC_FILE = "/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pbpb/yskim_PbPb_pythiaHYDJET_forest_AllQCDPhotons.root";
        if(collision ==2 ) {
            LABEL = "PbPb #sqrt{s}_{_{NN}}=2.76 TeV 0-30 %";
            centCut = Form("((cBin) >= %i) && ((cBin) < %i)", CENTBINS[0], CENTBINS[1]);
        } else if(collision ==3 ) { 
            LABEL = "PbPb #sqrt{s}_{_{NN}}=2.76 TeV 30-100 %";
            centCut = Form("((cBin) >= %i) && ((cBin) < %i)", CENTBINS[1], CENTBINS[2]);   
        } sampleIsolation = "(cc4+cr4+ct4PtCut20<1) && hadronicOverEm<0.1";

    } else if(collision ==1){
        //pPb
        DATA_FILE = "/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pA/yskim_pA_photonSkimForest_v85_HLT_PAPhoton30_NoCaloIdVL_v1_highPtPhoton40.root";
        MC_FILE = "/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pA/yskim_pA_Pyquen_allQCDPhoton_hiForest2_53x_2013-18-14-1922.root ";
        LABEL = "pPb #sqrt{s}_{_{NN}}=5.02 TeV";
        sampleIsolation = "ecalRecHitSumEtConeDR04 < 4.2  &&  hcalTowerSumEtConeDR04 < 2.2  &&  trkSumPtHollowConeDR04 < 2 && hadronicOverEm<0.1";
        centCut = "";
    }

    TH1::SetDefaultSumw2();

    TFile* dataFile = TFile::Open(DATA_FILE);
    TTree* dataTree = (TTree*)dataFile -> Get("tgj"); 
    
    TFile* mcFile = TFile::Open(MC_FILE);
    TTree* mcTree = (TTree*)mcFile -> Get("tgj"); 

    int dcBin, mcBin;
    float dvtx, mvtx;
    dataTree -> SetBranchAddress("cBin", &dcBin);
    dataTree -> SetBranchAddress("vtxCentWeight", &dvtx);
    mcTree -> SetBranchAddress("cBin", &mcBin);
    mcTree -> SetBranchAddress("vtxCentWeight", &mvtx);
    
    for(int i=0; i< mcTree -> GetEntries(); i++){
        


    }

 
