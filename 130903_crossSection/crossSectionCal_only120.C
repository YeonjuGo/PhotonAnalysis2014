#include "../HiForestAnalysis/hiForest.h"
#include "../gammaJetAnalysis/CutAndBinCollection2012.h"
#include <TStyle.h>
#include <TH1D.h>
#include <TTree.h>
#include <TBranch.h>
#include <TFile.h>
#include <iostream>
#include <TCanvas.h>

void crossSectionCal_only120(){
//
//case 120 
//

    TFile* fNoFilter = new TFile("genParticleTree_Configuration.GenProduction.Pyquen_AllQCDPhotons_PtHat120_No_PhotonFilter_TuneZ2_Unquenched_2760GeV_cfi.root", "READ");
    TTree* tNoFilter = (TTree*) fNoFilter -> Get("genpana/photon");
    TH1D* hNoFilter = new TH1D("hNoFilter", "hNoFilter", 500, 120, 500);
    tNoFilter -> Draw("pt >> hNoFilter", "id==22 && abs(eta)<3 && pt>130");
    int entriesNoFilter = tNoFilter -> GetEntries("id==22 && abs(eta)<3 && pt>130");
    cout << " NoFilter entries (pt more than 130) : " << entriesNoFilter << endl;

    TFile* f = new TFile("genParticleTree_Configuration.GenProduction.Pyquen_AllQCDPhotons_PtHat120_PhotonFilter_pt60GeV_eta3_TuneZ2_Unquenched_2760GeV_cfi.root", "READ");
    TTree* t = (TTree*) f -> Get("genpana/photon");
    TH1D* h = new TH1D("h", "h", 500, 120, 500); 
    t -> Draw("pt >> h", Form("id==22 && abs(eta)<3 && pt>130"));
    int entries = t -> GetEntries("id==22 && abs(eta)<3 && pt>130");
    cout << " Filter entries (pt more than 130) : " << entries << endl;

    double noFilterCS = 0.00001119;
    
    TCanvas* c1 = new TCanvas("c1", "c1", 400, 400);
    h -> Draw();
    hNoFilter -> SetLineColor(2);
    hNoFilter -> Draw("same");
    double realCS = noFilterCS*(double)entries/(double)entriesNoFilter;
    cout << "cross section 120 : " << realCS << endl;
}

