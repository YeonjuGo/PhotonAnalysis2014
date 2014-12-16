#include <TStyle.h>
#include <TH1D.h>
#include <TTree.h>
#include <TFile.h>
#include <iostream>
#include <TCanvas.h>
#include <TF1.h>
#include <TGraphAsymmErrors.h>
#include <TLegend.h>
#include <TDirectory.h>

void weightCal(){
    
    cout << "sljdf" << endl;
    float ptHat;
    TFile* openFile = new TFile("../130822/files/PA2013_pyquen_allQCDPhoton30_forestv78.root", "READ");
   // TDirectory* photonDir = (TDirectory*) openFile -> Get("multiPhotonAnalyzer");
   // photonDir -> cd();
    TTree* photonTree = (TTree*) openFile -> Get("multiPhotonAnalyzer.photon");
    cout << "dlskjaf" << endl;
    photonTree -> SetBranchAddress("ptHat", &ptHat);
    cout << "photonTree" << endl;
    // the number of ptHat 30-50, 50-80, 80-120, 120-
    double Nof30 = 0.0;
    double Nof50 = 0.0;
    double Nof80 = 0.0;
    double Nof120 = 0.0;

    int entries = photonTree -> GetEntries();
    for(int i=0;i<entries;i++){
        photonTree -> GetEntry(i);
        if(ptHat>30 && ptHat<50) Nof30 += 1.0;
        else if(ptHat>50 && ptHat<80) Nof50 += 1.0;
        else if(ptHat>80 && ptHat<120) Nof80 += 1.0;
        else Nof120 += 1.0;
    }
    int entries30 = photonTree -> GetEntries("ptHat>30 && ptHat<50");
    int entries50 = photonTree -> GetEntries("ptHat>50 && ptHat<80");
    int entries80 = photonTree -> GetEntries("ptHat>80 && ptHat<120");
    int entries120 = photonTree -> GetEntries("ptHat>120");

    cout << "comparision!! in case 30, GetEntiries = " << entries30 << ", if my loop = " << Nof30 << endl;
    cout << "comparision!! in case 50, GetEntiries = " << entries50 << ", if my loop = " << Nof50 << endl;
    cout << "comparision!! in case 80, GetEntiries = " << entries80 << ", if my loop = " << Nof80 << endl;
    cout << "comparision!! in case 120, GetEntiries = " << entries120 << ", if my loop = " << Nof120 << endl;

    cout << "===== weighting factor ====" << endl;
    cout << "ptHat 30-50 : " << Nof30/Nof30 << endl;
    cout << "ptHat 50-80 : " << Nof50/Nof30 << endl;
    cout << "ptHat 80-120 : " << Nof80/Nof30 << endl;
    cout << "ptHat more than 120 : " << Nof120/Nof30 << endl;

}

