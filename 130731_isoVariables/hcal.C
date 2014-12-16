#include <TROOT.h>
#include <TF1.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <iostream>
#include <fstream>
#include <TFile.h>
#include <TTree.h>

void hcal()
{
    TCanvas* c1 = new TCanvas("c1", "c1", 1200, 400);
    c1 -> Divide(3,1);
    TFile* f = new TFile("./yskim_pA_Pyquen_allQCDPhoton_hiForest2_v85.root");
    TTree *tgj = (TTree*) f -> Get ("tgj");

    c1 -> cd(1);
    gStyle->SetPadRightMargin(0.08);
    gStyle->SetLabelFont(42,"Z");
    TH2D* hh = new TH2D("hh", "", 65, 0, 110, 65, 0, 110);
    tgj -> Draw("hcalIso:hf4Sum>>hh", "(abs(vz) < 15) && (photonEt > 60 ) && ( hovere < 0.1 )  && ( abs(genMomId) <= 22 )","colz");
    hh -> GetXaxis() -> SetTitle("E_{T}^{HF|#eta|>4} (GeV)");
    hh -> GetYaxis() -> SetTitle("hcalIso (GeV)");
    hh->GetYaxis()->CenterTitle(true);
    hh->GetYaxis()->SetTitleSize(0.05);
    //    hh -> GetZaxis() -> SetLabelSize(0.03);
//    hh -> GetZaxis() -> SetLabelOffset(0.1);
    hh -> Draw("colz");

    c1 -> cd(2);
    TH1D* meanHist = new TH1D("meanHist","",10, 0, 100);

    meanHist -> GetYaxis() -> SetTitle("<hcalIso> (GeV)");
    meanHist -> GetXaxis() -> SetTitle("E_{T}^{HF|#eta|>4} (GeV)");
    meanHist->GetYaxis()->CenterTitle(true);
    meanHist->GetYaxis()->SetTitleSize(0.05);
    meanHist->GetXaxis()->SetLabelSize(0.035);

    double mean[10] = {0};
    double error[10] = {0};

    TH1D* hist[10];
    for(int i=0;i<10;i++){
        hist[i] = new TH1D(Form("hist%d",i),"",100,0,100);
        tgj -> Draw(Form("hcalIso>>hist%d",i), Form("(abs(tgj.vz) < 15) && (tgj.photonEt > 60 )   && ( hovere < 0.1 )  && ( abs(genMomId) <= 22 ) &&  (hf4Sum > %d*10 && hf4Sum < %d*10) ", i, i+1));
        hist[i] -> Draw();

        mean[i] = hist[i] -> GetMean();
        error[i] = hist[i] -> GetMeanError();
    
    //important!! not Fill, but SetBinContent!!!     
        meanHist -> SetBinContent(i+1, mean[i]);
        meanHist -> SetBinError(i+1, error[i]);
    }
    c1 -> cd(2);
    meanHist -> SetMarkerStyle(20);
    meanHist -> Draw();

    TF1* f1 = new TF1("f1", "pol1", 0, 100);
    meanHist -> Fit("f1", "QN");
    f1 -> Draw("same");
    f1 -> SetLineColor(2);
    f1 -> SetLineStyle(7);
    gStyle -> SetOptStat(0);
    
    TCanvas* c2 = new TCanvas("c2","c2", 100, 100);

    int low = 0;
    int high = 20;
    TH1D* h = new TH1D("h","",100,0,10);
    c2 -> cd();
    tgj -> Draw("hcalIso>>h", Form("(abs(tgj.vz) < 15) && (tgj.photonEt > 60 )   && ( hovere < 0.1 )  && ( abs(genMomId) <= 22 ) &&  (hf4Sum > %d && hf4Sum < %d) ", low, high));
    c1-> cd(3);
    h -> GetXaxis() -> SetTitle("hcalIso (GeV)");
    gPad-> SetLogy();
    h -> Draw();
    h -> Scale( 1./( h -> Integral() ));

    low = 20;
    high = 25;
    TH1D* h2 = new TH1D("h2","",100,0,10);
    c2 -> cd();
    tgj -> Draw("hcalIso>>h2", Form("(abs(tgj.vz) < 15) && (tgj.photonEt > 60 )   && ( hovere < 0.1 )  && ( abs(genMomId) <= 22 ) &&  (hf4Sum > %d && hf4Sum < %d) ", low, high));
    h2 -> SetLineColor(2);
    c1-> cd(3);
    h2 -> Draw("same");
    h2 -> Scale( 1./( h2 -> Integral() ));
    
    low = 25;
    high = 30;
    TH1D* h3 = new TH1D("h3","",100,0,10);
    c2 -> cd();
    tgj -> Draw("hcalIso>>h3", Form("(abs(tgj.vz) < 15) && (tgj.photonEt > 60 )   && ( hovere < 0.1 )  && ( abs(genMomId) <= 22 ) &&  (hf4Sum > %d && hf4Sum < %d) ", low, high));
    h3 -> SetLineColor(3);
    c1-> cd(3);
    h3 -> Draw("same");
    h3 -> Scale( 1./( h3 -> Integral() ));
    
    low = 30;
    high = 40;
    TH1D* h4 = new TH1D("h4","",100,0,10);
    c2 -> cd();
    tgj -> Draw("hcalIso>>h4", Form("(abs(tgj.vz) < 15) && (tgj.photonEt > 60 )   && ( hovere < 0.1 )  && ( abs(genMomId) <= 22 ) &&  (hf4Sum > %d && hf4Sum < %d) ", low, high));
    h4 -> SetLineColor(4);
    c1-> cd(3);
    h4 -> Draw("same");
    h4 -> Scale( 1./( h4 -> Integral() ));
    
    low = 40;
    high = 100;
    TH1D* h5 = new TH1D("h5","",100,0,10);
    c2 -> cd();
    tgj -> Draw("hcalIso>>h5", Form("(abs(tgj.vz) < 15) && (tgj.photonEt > 60 )   && ( hovere < 0.1 )  && ( abs(genMomId) <= 22 ) &&  (hf4Sum > %d && hf4Sum < %d) ", low, high));
    h5 -> SetLineColor(5);
    c1-> cd(3);
    h5 -> Draw("same");
    h5 -> Scale( 1./( h5 -> Integral() ));

    c1 -> cd(3);
    TLegend *legend=new TLegend(0.458194,0.5768049,0.8771437,0.8730524,NULL,"brNDC");
    legend->SetLineColor(0);
    legend->SetFillStyle(1001);
    legend->SetTextFont(42);
    legend->SetTextSize(0.04);
    legend->SetFillColor(0);
    legend->AddEntry("h1","0 < E_{T}^{HF|#eta|>4} < 20", "l");
    legend->AddEntry("h2","20 < E_{T}^{HF|#eta|>4} < 25", "l");
    legend->AddEntry("h3","25 < E_{T}^{HF|#eta|>4} < 30", "l");
    legend->AddEntry("h4","30 < E_{T}^{HF|#eta|>4} < 40", "l");
    legend->AddEntry("h5","40 < E_{T}^{HF|#eta|>4} < 100", "l");
    legend->Draw();
    gStyle->SetPadBorderMode(0);

    c1 -> Update();
    c1 -> SaveAs("hcalIso_pPbMC_forestv85.gif");
}

