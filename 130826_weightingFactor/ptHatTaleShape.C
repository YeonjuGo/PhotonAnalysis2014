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

void ptHatTaleShape(){
    
    TCanvas* c_notScale = new TCanvas("c_notScale", "c_notScale", 500, 400);
    TCanvas* c_Scale = new TCanvas("c_Scale", "c_Scale", 500, 400);
    c_notScale -> cd();
    
    TFile* f30 = new TFile("../130822/files/pA_Pyquen_allQCDPhoton30_hiForest2_53x_2013-18-14-1922.root", "READ");
    TTree* pTree30 = (TTree*) f30 -> Get("multiPhotonAnalyzer/photon");
    
    TFile* f50 = new TFile("../130822/files/pA_Pyquen_allQCDPhoton50_hiForest2_53x_2013-18-14-1922.root", "READ");
    TTree* pTree50 = (TTree*) f50 -> Get("multiPhotonAnalyzer/photon");
    
    TFile* f80 = new TFile("../130822/files/pA_Pyquen_allQCDPhoton80_hiForest2_53x_2013-18-14-1922.root", "READ");
    TTree* pTree80 = (TTree*) f80 -> Get("multiPhotonAnalyzer/photon");
    
    TH1D* h30 = new TH1D("h30", "h30", 600, 20, 300);
    TH1D* h50 = new TH1D("h50", "h50", 600, 20, 300);
    TH1D* h80 = new TH1D("h80", "h80", 600, 20, 300);

    pTree30->Draw("pt >> h30","abs(eta)<1.44");
    pTree50->Draw("pt >> h50","abs(eta)<1.44");
    pTree80->Draw("pt >> h80","abs(eta)<1.44");

    c_notScale -> cd();
    h30->DrawCopy();
    h50->DrawCopy("same");
    h80->DrawCopy("same");

    
    int entries30 = pTree30 -> GetEntries("pt>100&&abs(eta)<1.44"); 
    int entries50 = pTree50 -> GetEntries("pt>100&&abs(eta)<1.44"); 
    int entries80 = pTree80 -> GetEntries("pt>100&&abs(eta)<1.44"); 
    
    cout << "30 : " << entries30 << endl;    
    cout << "50 : " << entries50 << endl;    
    cout << "80 : " << entries80 << endl;    
    h30->Scale(1.0/(double)entries30);
    h50->Scale(1.0/(double)entries50);
    h80->Scale(1.0/(double)entries80);

    c_Scale -> cd();
    h30->Draw();
    h50->Draw("same");
    h80->Draw("same");

}
