#include <TFile.h>
#include <TString.h>
#include <TDirectory.h>
#include <TTree.h>
#include <TH2D.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <iostream>
//#include "../analysis/hiForestV3/hiForest.h"
//#include "../CutAndBinCollection2012.h"
#include <iomanip>

using namespace std;
void testWF_v2(){

    TCanvas* p_pt = new TCanvas("p_pt", "p_pt", 400, 300);
    p_pt -> cd();

    TH1D* h_pt = new TH1D("h_pt", "h_pt", 600, 0, 300);

    float pt30[100], pt50[100], pt80[100], pt120[100];
    int nPhotons30, nPhotons50, nPhotons80, nPhotons120;

    TFile* f30 = new TFile("../130822/PA2013_pyquen_allQCDPhoton30to50_forestv85.root", "READ");
    TTree* pTree30 = (TTree*) f30 -> Get("multiPhotonAnalyzer/photon");
    pTree30 -> SetBranchAddress("pt", pt30);
    pTree30 -> SetBranchAddress("nPhotons", &nPhotons30);

    cout << "f30"<< endl;
    TFile* f50 = new TFile("../130822/PA2013_pyquen_allQCDPhoton50to80_forestv85.root", "READ");
    TTree* pTree50 = (TTree*) f50 -> Get("multiPhotonAnalyzer/photon");
    pTree50 -> SetBranchAddress("pt", pt50);
    pTree50 -> SetBranchAddress("nPhotons", &nPhotons50);
    
    TFile* f80 = new TFile("../130822/PA2013_pyquen_allQCDPhoton80to120_forestv85.root", "READ");
    TTree* pTree80 = (TTree*) f80 -> Get("multiPhotonAnalyzer/photon");
    pTree80 -> SetBranchAddress("pt", pt80);
    pTree80 -> SetBranchAddress("nPhotons", &nPhotons80);
    
    TFile* f120 = new TFile("../130822/PA2013_pyquen_allQCDPhoton120to9999_forestv85.root", "READ");
    TTree* pTree120 = (TTree*) f120 -> Get("multiPhotonAnalyzer/photon");
    pTree120 -> SetBranchAddress("pt", pt120);
    pTree120 -> SetBranchAddress("nPhotons", &nPhotons120);

    int entries30 = pTree30 -> GetEntries();
    for(int i = 0 ; i< entries30; i++){
        pTree30 -> GetEntry(i);
        for(int jpho=0; jpho< nPhotons30; jpho++){
            h_pt -> Fill(pt30[jpho], 1);
        }
    }
    
    int entries50 = pTree50 -> GetEntries();
    for(int i = 0 ; i< entries50; i++){
        pTree50 -> GetEntry(i);
        for(int jpho=0; jpho< nPhotons50; jpho++){
            h_pt -> Fill(pt50[jpho], 0.0890448);
        }
    }

    int entries80 = pTree80 -> GetEntries();
    for(int i = 0 ; i< entries80; i++){
        pTree80 -> GetEntry(i);
        for(int jpho=0; jpho< nPhotons80; jpho++){
            h_pt -> Fill(pt80[jpho], 0.0228245);
        }
    }

    int entries120 = pTree120 -> GetEntries();
    for(int i = 0 ; i< entries120; i++){
        pTree120 -> GetEntry(i);
        for(int jpho=0; jpho< nPhotons120; jpho++){
            h_pt -> Fill(pt120[jpho], 0.00493548);
        }
    }
    /*
       h30->Scale(1);
       h50->Scale(0.0890448);
       h80->Scale(0.0228245);
       h120->Scale(0.00493548);
       */  
    h_pt->Draw();
}
