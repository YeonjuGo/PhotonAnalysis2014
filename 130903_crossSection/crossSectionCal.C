#include "../HiForestAnalysis/hiForest.h"
#include "../gammaJetAnalysis/CutAndBinCollection2012.h"
#include <TStyle.h>
#include <TH1D.h>
#include <TTree.h>
#include <TBranch.h>
#include <TFile.h>
#include <iostream>
#include <TCanvas.h>

void crossSectionCal(){
    gStyle -> SetOptStat(0);
    gStyle -> SetOptLogy();
    gStyle -> SetTitleYSize(0.05);
    gStyle -> SetTitleXSize(0.05);
    const int nPt = 5;
    const double eventNum = 5000.0;
    const double eventNumNoFilter = 100000.0;
    int ptHat[nPt] = {30, 50, 80, 120, 170};
    int ptCut[nPt] = {15, 35, 35, 60, 60};
    double noFilterCS[nPt] = {0.01078, 0.001022, 0.00009943, 0.00001124, 0.000001472};
    int drawCut[nPt] = {15, 35, 35, 60, 60};
    double realCS[nPt];
    int entries[nPt];
    int entriesNoFilter[nPt];
    TFile* fNoFilter[nPt];
    TFile* f[nPt];
    TTree* tNoFilter[nPt];
    TTree* t[nPt];
    TH1D* hNoFilter[nPt];
    TH1D* hFinal[nPt];
    TH1D* h[nPt];

    TCanvas* c1 = new TCanvas("c1", "c1", 2000, 300);
    c1 -> Divide(5,1);

    for(int i=0; i<nPt; i++){
        c1->cd(i+1);
        fNoFilter[i] = new TFile(Form("genParticleTree_Configuration.GenProduction.Pyquen_AllQCDPhotons_PtHat%d_No_PhotonFilter_TuneZ2_Unquenched_2760GeV_cfi.root",ptHat[i]), "READ");
        tNoFilter[i] = (TTree*) fNoFilter[i] -> Get("genpana/photon");
        hNoFilter[i] = new TH1D(Form("hNoFilter_%d",i), Form("hNoFilter_%d",i), 35, 0, 350);
        tNoFilter[i] -> Draw(Form("pt >> hNoFilter_%d", i), "id==22 && abs(eta)<3 && status==1 && abs(momId)<=22");
        entriesNoFilter[i] = tNoFilter[i] -> GetEntries(Form("id==22 && abs(eta)<3 && status==1 && abs(momId)<=22 && pt>%d",drawCut[i]));
        cout << Form("NoFilter entries (pt more than %d) : ", drawCut[i]) << entriesNoFilter[i] << endl;
        
        hFinal[i] = new TH1D(Form("hFinal_%d",i), Form("hFinal_%d",i), 35, 0, 350);
        hFinal[i] -> Sumw2();   
        tNoFilter[i] -> Draw(Form("pt >> hFinal_%d", i), "id==22 && abs(eta)<3 && status==1 && abs(momId)<=22");

        f[i] = new TFile(Form("genParticleTree_Configuration.GenProduction.Pyquen_AllQCDPhotons_PtHat%d_PhotonFilter_pt%dGeV_eta3_TuneZ2_Unquenched_2760GeV_cfi.root",ptHat[i],ptCut[i]), "READ");
        t[i] = (TTree*) f[i] -> Get("genpana/photon");
        h[i] = new TH1D(Form("h%d",i), Form("AllQCDPhotons PtHat > %d",ptHat[i]), 35, 0, 350); 
        t[i] -> Draw(Form("pt >> h%d",i), "id==22 && abs(eta)<3 && status==1 && abs(momId)<=22");
        entries[i] = t[i] -> GetEntries(Form("id==22 && abs(eta)<3 && status==1 && abs(momId)<=22 && pt>%d",drawCut[i]));
        cout << Form("Filter entries (pt more than %d) : ", drawCut[i]) << entries[i] << endl;

        h[i] -> SetXTitle("p_{T}^{#gamma} (GeV)");
        h[i] -> SetYTitle("Entries/event");
//        h[i] -> SetTitleSize(0.035, "X");
//        h[i] -> SetTitleSize(0.035, "Y");
        h[i] -> Draw();
        hNoFilter[i] -> SetLineColor(2);
        hFinal[i] -> SetLineColor(3);
        hNoFilter[i] -> Draw("same");
        hFinal[i] -> Draw("same");
        realCS[i] = noFilterCS[i]*(double)entries[i]*eventNumNoFilter/(double)entriesNoFilter[i]/eventNum;
        cout << Form("cross section %d : ",ptHat[i]) << realCS[i] << endl;

        h[i] -> Scale(1/eventNum);
        hNoFilter[i] -> Scale(1/eventNumNoFilter);
        hFinal[i] -> Scale(1/eventNumNoFilter*realCS[i]/noFilterCS[i]);
        c1 -> Update();
    }
    c1 -> cd(1);
    TLegend *l1 = new TLegend(0.4365615,0.5445304,0.9577623,0.846736,NULL,"brNDC");
    easyLeg(l1,"p+p 2.76TeV");
    l1 -> Draw();
    
    c1 -> cd(2);
    TLegend *l2 = new TLegend(0.3365615,0.6445304,0.9977623,0.846736,NULL,"brNDC");
    l2 -> AddEntry(h[1], "Filter");
    l2 -> AddEntry(hNoFilter[1], "No Filter");
    l2 -> AddEntry(hFinal[1], "No Filter * Cross Section");
    l2 -> SetFillStyle(0);
    l2 -> SetBorderSize(0);
    l2 -> Draw();
}

