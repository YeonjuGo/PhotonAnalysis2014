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

void weightFactorCal(){
    float ptHat;
    TFile* openFile = new TFile("../130822/files/PA2013_pyquen_allQCDPhoton30_forestv78.root", "READ");
    TDirectory* photonDir = (TDirectory*) openFile -> Get("multiPhotonAnalyzer");
    photonDir -> cd();
    TTree* photonTree = (TTree*) photonDir -> Get("photon");
    photonTree -> SetBranchAddress("ptHat", &ptHat);
    cout << "photonTree" << endl;
    //the number of ptHat 30-50, 50-80, 80-120, 120-
    
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
    
    double weight30 = Nof30/Nof30;
    double weight50 = Nof50/Nof30;
    double weight80 = Nof80/Nof30;
    double weight120 = Nof120/Nof30;

    cout << "===== weighting factor ====" << endl;
    cout << "ptHat 30-50 : " << weight30 << endl;
    cout << "ptHat 50-80 : " << weight50 << endl;
    cout << "ptHat 80-120 : " << weight80 << endl;
    cout << "ptHat more than 120 : " << weight120 << endl;

    TFile* f30 = new TFile("../130822/PA2013_pyquen_allQCDPhoton30to50_forestv78.root", "READ");
    TFile* f50 = new TFile("../130822/PA2013_pyquen_allQCDPhoton50to80_forestv78.root", "READ");
    TFile* f80 = new TFile("../130822/PA2013_pyquen_allQCDPhoton80to120_forestv78.root", "READ");
    TFile* f120 = new TFile("../130822/PA2013_pyquen_allQCDPhoton120to9999_forestv78.root", "READ");

    TDirectory* pDir30 = (TDirectory*) f30 -> Get("multiPhotonAnalyzer");
    TDirectory* pDir50 = (TDirectory*) f50 -> Get("multiPhotonAnalyzer");
    TDirectory* pDir80 = (TDirectory*) f80 -> Get("multiPhotonAnalyzer");
    TDirectory* pDir120 = (TDirectory*) f120 -> Get("multiPhotonAnalyzer");
    
    pDir30 -> cd();
    TTree* pTree30 = (TTree*) pDir30 -> Get("photon");
    pDir50 -> cd();
    TTree* pTree50 = (TTree*) pDir50 -> Get("photon");
    pDir80 -> cd();
    TTree* pTree80 = (TTree*) pDir80 -> Get("photon");
    pDir120 -> cd();
    TTree* pTree120 = (TTree*) pDir120 -> Get("photon");

    int ptHat30Entries = pTree30 -> GetEntries();
    int ptHat50Entries = pTree50 -> GetEntries();
    int ptHat80Entries = pTree80 -> GetEntries();
    int ptHat120Entries = pTree120 -> GetEntries();

    cout << "===== Tree Entries ====" << endl;
    cout << "ptHat 30-50 : " << ptHat30Entries << endl;
    cout << "ptHat 50-80 : " << ptHat50Entries << endl;
    cout << "ptHat 80-120 : " << ptHat80Entries << endl;
    cout << "ptHat more than 120 : " << ptHat120Entries << endl;
    
    
 //   cout << "30 Entries : " << ptHat30Entries << ",  50 Entries : " << ptHat50Entries << ", 80 Entries : " << ptHat80Entries << ", 120 Entries : " << ptHat120Entries << endl;

    double weight_fac_30 = weight30/ptHat30Entries;
    double weight_fac_50 = weight50/ptHat50Entries;
    double weight_fac_80 = weight80/ptHat80Entries;
    double weight_fac_120 = weight120/ptHat120Entries;

    cout << "===== Weighting Factor =====" << endl;
    cout << "ptHat 30-50 : " << weight_fac_30 << endl;
    cout << "ptHat 50-80 : " << weight_fac_50 << endl;
    cout << "ptHat 80-120 : " << weight_fac_80 << endl;
    cout << "ptHat more than 120 : " << weight_fac_120 << endl;
    
    cout << "===== Weighting Factor base on 30to50=1 =====" << endl;
    cout << "ptHat 30-50 : " << weight_fac_30/weight_fac_30 << endl;
    cout << "ptHat 50-80 : " << weight_fac_50/weight_fac_30 << endl;
    cout << "ptHat 80-120 : " << weight_fac_80/weight_fac_30 << endl;
    cout << "ptHat more than 120 : " << weight_fac_120/weight_fac_30 << endl;
   
}

