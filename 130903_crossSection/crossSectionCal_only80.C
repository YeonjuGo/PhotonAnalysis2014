#include "../HiForestAnalysis/hiForest.h"
#include "../gammaJetAnalysis/CutAndBinCollection2012.h"
#include <TStyle.h>
#include <TH1D.h>
#include <TTree.h>
#include <TBranch.h>
#include <TFile.h>
#include <iostream>
#include <TCanvas.h>

void crossSectionCal_only80(){
//
//case 80
//

    TFile* fNoFilter = new TFile("genParticleTree_Configuration.GenProduction.Pyquen_AllQCDPhotons_PtHat80_No_PhotonFilter_TuneZ2_Unquenched_2760GeV_cfi.root", "READ");
    TTree* tNoFilter = (TTree*) fNoFilter -> Get("genpana/photon");
    TH1D* hNoFilter = new TH1D("hNoFilter", "hNoFilter", 500, 80, 500);
    tNoFilter -> Draw("pt >> hNoFilter", "id==22 && abs(eta)<3 && pt>100");
    int entriesNoFilter = tNoFilter -> GetEntries("id==22 && abs(eta)<3 && pt>100");
    cout << " NoFilter entries (pt more than 100) : " << entriesNoFilter << endl;

    TFile* f = new TFile("genParticleTree_Configuration.GenProduction.Pyquen_AllQCDPhotons_PtHat80_PhotonFilter_pt35GeV_eta3_TuneZ2_Unquenched_2760GeV_cfi.root", "READ");
    TTree* t = (TTree*) f -> Get("genpana/photon");
    TH1D* h = new TH1D("h", "h", 500, 80, 500); 
    t -> Draw("pt >> h", Form("id==22 && abs(eta)<3 && pt>100"));
    int entries = t -> GetEntries("id==22 && abs(eta)<3 && pt>100");
    cout << " Filter entries (pt more than 100) : " << entries << endl;

    double noFilterCS =0.00009923;
    
    TCanvas* c1 = new TCanvas("c1", "c1", 400, 400);
    h -> Draw();
    hNoFilter -> SetLineColor(2);
    hNoFilter -> Draw("same");
    double realCS = noFilterCS*(double)entries/(double)entriesNoFilter;
    cout << "cross section 80 : " << realCS << endl;
}

