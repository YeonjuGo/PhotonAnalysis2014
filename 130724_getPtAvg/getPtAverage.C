#include <TH1D.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <iostream>
void getPtAverageFunc(int lowPt =50, int highPt =60);

void getPtAverage () { 
  getPtAverageFunc(50,60);
  getPtAverageFunc(60,80);
  getPtAverageFunc(80,1000);
}

void getPtAverageFunc(int lowPt, int highPt ){
    TFile* readFile = new TFile("skimmedFiles/skim_ak3PF_ppData2013_promptSkim_photon40GeV.root", "READ");
   
    Double_t photonEt, photonEta, hovere, sigmaletaleta;

    TTree* tgjTree = (TTree*) readFile -> Get("tgj");
    
    TH1D* hPhotonEt = new TH1D("histPhotonEt",";photon E_{T} (GeV) ; Entries",1000,0,1000);
    tgjTree->Draw( "photonEt >> histPhotonEt",Form("photonEt>%d && photonEt<%d && abs(photonEta)<1.44 && hovere<0.1 && genMomId<=22", lowPt, highPt));
    hPhotonEt->Draw();
    double mean = hPhotonEt -> GetMean();
    double mean_error = hPhotonEt -> GetMeanError();
    cout << "range from " << lowPt << " to " << highPt << " ,  Mean : " << mean << ",  Error : " << mean_error << endl;  
    /*tgjTree -> SetBranchAddress("photonEt", &photonEt);
    tgjTree -> SetBranchAddress("photonEta", &photonEta);
    tgjTree -> SetBranchAddress("hovere", &hovere);
    tgjTree -> SetBranchAddress("sigmaletaleta", &sigmaletaleta);
   
    TTree skimTree = tgjTree -> CopyTree(Form("abs(photonEta)<1.44 && hovere<0.1 && genMomId<=22 && sigmaIetaIeta< 0.01"));

    TH1D* rawHist = (TH1D*)skimTree -> Get("photonEt");
    */    

}

