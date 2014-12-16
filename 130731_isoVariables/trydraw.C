#include <TROOT.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <iostream>
#include <fstream>
#include <TFile.h>
#include <TTree.h>

void getDistHist(int low=0, int high=20, TH1D *h=NULL);

void trydraw()
{
    TCanvas* c1 = new TCanvas("c1", "c1", 1200, 400);
    c1 -> Divide(3,1);

    TFile* f = new TFile("yskim_PA2013_pyquen_allQCDPhoton50_forestv78.root");

    TTree *tgj = (TTree*) f -> Get ("tgj");

    c1 -> cd(1);
    tgj -> Draw("ecalIso.GetMean():hf4Sum", "(abs(vz) < 15) && (photonEt > 60 ) && ( hovere < 0.1 )  && ( abs(genMomId) <= 22 )");
 
 /*   Double_t ecalIso, hcalIso, trackIso, hf4Sum;

    tgj-> SetBranchAddress("ecalIso", &ecalIso);
    tgj-> SetBranchAddress("hcalIso", &hcalIso);
    tgj-> SetBranchAddress("trackIso", &trackIso);
    tgj-> SetBranchAddress("hf4Sum", &hf4Sum);
  */  
 //   TTree *cutTgj = tgj -> Copy(Form("(abs(tgj.vz) < 15) && (tgj.photonEt > 60 )   && ( hovere < 0.1 )  && ( abs(genMomId) <= 22 )"));

    c1 -> cd(2);
    TH1D* meanHist = new TH1D("meanHist","<ecalIso> vs. HF4Sum",10, 0, 100);
  //  TH1D* distHist = new TH1D("","",);

    double mean[10] = {0};
    double error[10] = {0};

    TH1D* hist[10];
    for(int i=0;i<10;i++){
        hist[i] = new TH1D(Form("hist%d",i),"",100,0,50);
        tgj -> Draw(Form("ecalIso>>hist%d",i), Form("(abs(tgj.vz) < 15) && (tgj.photonEt > 60 )   && ( hovere < 0.1 )  && ( abs(genMomId) <= 22 ) &&  (hf4Sum > %d*10 && hf4Sum < %d*10) ", i, i+1));
        hist[i] -> Draw();

        mean[i] = hist[i] -> GetMean();
        error[i] = hist[i] -> GetMeanError();
        
        cout <<" i , " << mean[i] << " ," << error[i] << endl; 
        meanHist -> Fill(10*i+5, mean[i]);
        meanHist -> SetBinError(10*i+5, error[i]);
    }
    c1 -> cd(2);
    meanHist -> SetMarkerStyle(20);
    meanHist -> Draw();

    TCanvas* c2 = new TCanvas("c2","c2", 100, 100);


    int low = 0;
    int high = 20;
    TH1D* h = new TH1D("h","",100,0,10);
    c2 -> cd();
    tgj -> Draw("ecalIso>>h", Form("(abs(tgj.vz) < 15) && (tgj.photonEt > 60 )   && ( hovere < 0.1 )  && ( abs(genMomId) <= 22 ) &&  (hf4Sum > %d && hf4Sum < %d) ", low, high));
    h -> SetLineColor(low + 1);
    c1-> cd(3);
    h -> Draw();

    low = 20;
    high = 25;
    TH1D* h2 = new TH1D("h2","",100,0,10);
    c2 -> cd();
    tgj -> Draw("ecalIso>>h2", Form("(abs(tgj.vz) < 15) && (tgj.photonEt > 60 )   && ( hovere < 0.1 )  && ( abs(genMomId) <= 22 ) &&  (hf4Sum > %d && hf4Sum < %d) ", low, high));
    h2 -> SetLineColor(low + 1);
    c1-> cd(3);
    h2 -> Draw("same");
    
    low = 25;
    high = 30;
    TH1D* h3 = new TH1D("h3","",100,0,10);
    c2 -> cd();
    tgj -> Draw("ecalIso>>h3", Form("(abs(tgj.vz) < 15) && (tgj.photonEt > 60 )   && ( hovere < 0.1 )  && ( abs(genMomId) <= 22 ) &&  (hf4Sum > %d && hf4Sum < %d) ", low, high));
    h3 -> SetLineColor(low + 1);
    c1-> cd(3);
    h3 -> Draw("same");
    
    low = 30;
    high = 40;
    TH1D* h4 = new TH1D("h4","",100,0,10);
    c2 -> cd();
    tgj -> Draw("ecalIso>>h4", Form("(abs(tgj.vz) < 15) && (tgj.photonEt > 60 )   && ( hovere < 0.1 )  && ( abs(genMomId) <= 22 ) &&  (hf4Sum > %d && hf4Sum < %d) ", low, high));
    h4 -> SetLineColor(low + 1);
    c1-> cd(3);
    h4 -> Draw("same");
    
    low = 40;
    high = 100;
    TH1D* h5 = new TH1D("h5","",100,0,10);
    c2 -> cd();
    tgj -> Draw("ecalIso>>h5", Form("(abs(tgj.vz) < 15) && (tgj.photonEt > 60 )   && ( hovere < 0.1 )  && ( abs(genMomId) <= 22 ) &&  (hf4Sum > %d && hf4Sum < %d) ", low, high));
    h5 -> SetLineColor(low + 1);
    c1-> cd(3);
    h5 -> Draw("same");
    
/*
    TH1D *h[5];
    for (Int_t i = 0; i < 5; i++)
        h[i] = new TH1D(Form("h%d",i),"",1000,0,50);

    c1 -> cd(3);
    getDistHist(0,20, h[0]);
    getDistHist(20,25, h[1]);
    getDistHist(25,30, h[2]);
    getDistHist(30,40, h[3]);
    getDistHist(40,100, h[4]);

    for (Int_t i = 0; i < 5; i++)
        h[i] -> Draw((i == 0 ? "" : "same"));
*/
    c1 -> Update();
    c1 -> SaveAs("ecalIso.jpg");
}

void getDistHist(int low, int high, TH1D *h){
    
    TFile* f = new TFile("yskim_PA2013_pyquen_allQCDPhoton50_forestv78.root");

    TTree *tgj = (TTree*) f -> Get ("tgj");

//    TH1D *h = new TH1D(Form("h%d",low),"",1000,0,50);
    tgj -> Draw(Form("ecalIso>>%s",h->GetName()), Form("(abs(tgj.vz) < 15) && (tgj.photonEt > 60 )   && ( hovere < 0.1 )  && ( abs(genMomId) <= 22 ) &&  (hf4Sum > %d && hf4Sum < %d) ", low, high));

    h -> SetLineColor(low+1);
}

