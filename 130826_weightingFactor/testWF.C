#include <TFile.h>
#include <TString.h>
#include <TDirectory.h>
#include <TTree.h>
#include <TH2D.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <iostream>
#include "../HiForestAnalysis/hiForest.h"
#include "../gammaJetAnalysis/CutAndBinCollection2012.h"
#include <iomanip>

using namespace std;
void testWF(){

    TCanvas* p_pt = new TCanvas("p_pt", "p_pt", 400, 300);
    p_pt -> cd();

    TH1D* h_pt = new TH1D("h_pt", "h_pt", 600, 0, 300);

    TString f30 = "../130822/PA2013_pyquen_allQCDPhoton30to50_forestv85.root";
    HiForest *t30 = new HiForest(f30.Data(),"", cPPb);
    int nentries = t30->GetEntries();
    for(Long64_t jentry = 0 ; jentry < nentries; jentry++) {
        t30->GetEntry(jentry);
        for (int jpho=0;jpho< t30->photon.nPhotons;jpho++) {
            h_pt -> Fill(t30->photon.pt[jpho],1);
        }
    }

    TString f50 = "../130822/PA2013_pyquen_allQCDPhoton50to80_forestv85.root";
    HiForest *t50 = new HiForest(f50.Data(),"",cPPb);
    nentries = t50->GetEntries();
    for(Long64_t jentry = 0 ; jentry < nentries; jentry++) {
        t50->GetEntry(jentry);
        for (int jpho=0;jpho< t50->photon.nPhotons;jpho++) {
            h_pt -> Fill(t50->photon.pt[jpho],0.0890448);
        }
    }

    TString f80 = "../130822/PA2013_pyquen_allQCDPhoton80to120_forestv85.root";
    HiForest *t80 = new HiForest(f80.Data(),"",cPPb);
    nentries = t80->GetEntries();
    for(Long64_t jentry = 0 ; jentry < nentries; jentry++) {
        t80->GetEntry(jentry);
        for (int jpho=0;jpho< t80->photon.nPhotons;jpho++) {
            h_pt -> Fill(t80->photon.pt[jpho],0.0228245);
        }
    }
    TString f120 = "../130822/PA2013_pyquen_allQCDPhoton120to9999_forestv85.root";
    HiForest *t120 = new HiForest(f120.Data(),"",cPPb);
    nentries = t120->GetEntries();
    for(Long64_t jentry = 0 ; jentry < nentries; jentry++) {
        t120->GetEntry(jentry);
        for (int jpho=0;jpho< t120->photon.nPhotons;jpho++) {
            h_pt -> Fill(t120->photon.pt[jpho],0.00493548);
        }
    }

    h_pt -> Draw();
}
          
                /*
    float pt30[100], pt50[100], pt80[100], pt120[100];
    int nPhotons30, nPhotons50, nPhotons80, nPhotons120;

    TFile* f30 = new TFile("../130822/PA2013_pyquen_allQCDPhoton30to50_forestv85.root", "READ");
    TTree* pTree30 = (TTree*) f30 -> Get("multiPhotonAnalyzer/photon");
    pTree30 -> SetBranchAddress("pt", &pt30[100]);
    pTree30 -> SetBranchAddress("nPhotons", &nPhotons30);

    cout << "f30"<< endl;
    TFile* f50 = new TFile("../130822/PA2013_pyquen_allQCDPhoton50to80_forestv85.root", "READ");
    TTree* pTree50 = (TTree*) f50 -> Get("multiPhotonAnalyzer/photon");
//    pTree50 -> SetBranchAddress("pt", &pt50);
    
    TFile* f80 = new TFile("../130822/PA2013_pyquen_allQCDPhoton80to120_forestv85.root", "READ");
    TTree* pTree80 = (TTree*) f80 -> Get("multiPhotonAnalyzer/photon");
//    pTree80 -> SetBranchAddress("pt", &pt80);
    
    TFile* f120 = new TFile("../130822/PA2013_pyquen_allQCDPhoton120to9999_forestv85.root", "READ");
    TTree* pTree120 = (TTree*) f120 -> Get("multiPhotonAnalyzer/photon");
//    pTree120 -> SetBranchAddress("pt", &pt120);

    TH1D* h_pt = new TH1D("h_pt", "h_pt", 600, 0, 300);
cout<< "h_pt"<<endl;

    int entries30 = pTree30 -> GetEntries();
    for(int i = 0 ; i< entries30; i++){
        pTree30 -> GetEntry(i);
        for(int jpho=0; jpho< nPhotons30; jpho++){
            h_pt -> Fill(pt30[jpho], 1);
        }
    }

    TH1D* h30 = new TH1D("h30", "h30", 600, 20, 300);
    TH1D* h50 = new TH1D("h50", "h50", 600, 20, 300);
    TH1D* h80 = new TH1D("h80", "h80", 600, 20, 300);
    TH1D* h120 = new TH1D("h120", "h120", 600, 20, 300);
  pTree30->Fill("pt >> h_pt", 1);
    pTree50->Draw("pt >> h50");
    pTree80->Draw("pt >> h80");
    pTree120->Draw("pt >> h120");
    
    h30->Scale(1);
    h50->Scale(0.0890448);
    h80->Scale(0.0228245);
    h120->Scale(0.00493548);
    
cout << "Draw"<< endl;
    h_pt->Draw();
    h50->Draw("same");
    h80->Draw("same");
    h120->Draw("same");
    */

