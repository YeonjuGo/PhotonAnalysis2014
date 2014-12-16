#include "../HiForestAnalysis/hiForest.h"
#include "../gammaJetAnalysis/CutAndBinCollection2012.h"
#include <TStyle.h>
#include <TH1D.h>
#include <TH1F.h>
#include <TTree.h>
#include <TBranch.h>
#include <TFile.h>
#include <iostream>
#include <TCanvas.h>
#include <TF1.h>
#include <TGraphAsymmErrors.h>
#include <TLegend.h>
#include <TCut.h>
#include <TPad.h>
//collision = 0, 1, 2, 3 for pp, pPb, PbPb 0-30 %, PbPb 30-100 % 
void calculCrossSection(int collision=1){
    TH1::SetDefaultSumw2();
    gStyle -> SetOptStat(0);
//    gStyle -> SetTitleSize(0.05, "xy");
   // gStyle -> SetTitleYOffset(1.2);
 //   gStyle -> SetPadBottomMargin(0.12);
  //  gStyle -> SetPadLeftMargin(0.11);
  //  gStyle -> SetLegendBorderSize(0);
 // gStyle->SetFillColor(-1);
    //  gStyle -> SetLegendFillColor(0);
  //  gStyle -> SetFrameFillColor(0);
  //  gStyle -> SetFrameBorderSize(0);

    const int nPtBin = 5; 
    double ptBin[nPtBin+1]={40, 50, 60, 80, 120, 300};
    double AvePtBin[nPtBin];
    double Luminosity_pp = 5.3 * 1e12;
    double nMB;
    double TA;
    TCut centCut, dataCut, weight;
    weight = "ptHatWeight*vtxCentWeight";
    if (collision==1) { //pPb
        nMB = 2.11 * 35 * 1e9;
        TA = 6.9/(7e7);
        centCut = "";
        dataCut = "abs(eta) < 1.44 && hadronicOverEm < 0.1 && (ecalRecHitSumEtConeDR04 < 4.2 && hcalTowerSumEtConeDR04 < 2.2 && trkSumPtHollowConeDR04 < 2)";
    } else if (collision==2) { //PbPb 0-30 %
        nMB = 7.6 * 150.0 * 1e6 * 0.3;
        TA = 15.5 * 1e3;// 1008/(65e-3) 
        centCut = "cBin >= 0 && cBin < 12";
        dataCut = "(cc4+cr4+ct4PtCut20<1) && hadronicOverEm<0.1"; 
    } else if (collision==3) { //PbPb 30-100 %
        nMB = 7.6 * 150.0 * 1e6 * 0.7;
        TA = 1.44 * 1e3;// 93.4/(65e-3) 
        centCut = "cBin >= 12 && cBin < 40";
        dataCut = "(cc4+cr4+ct4PtCut20<1) && hadronicOverEm<0.1"; 
    } else cout << "you have wrong number" << endl;

    TFile* fpp = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pp/yskim_pp_photonSKimForest_v85.root");

    TFile* ff;
    if(collision==1){//pA data
       // ff = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pA/yskim_pA_photonSkimForest_v85.root");
      ff = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pA/backup/yskim_pA_photonSkimForest_v85_HLT_PAPhoton30_NoCaloIdVL_v1_highPtPhoton40.root");
    } else if(collision==2 || collision==3){//AA data and pp data
        ff = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pbpb/yskim_HiForestPhoton-v7-noDuplicate.root");
    }   
//
// Get the trees from files
//
    TTree* tpho = (TTree*) ff -> Get("yPhotonTree");
    TTree* ttgj = (TTree*) ff -> Get("tgj");
    tpho -> AddFriend(ttgj);

    TTree* tphopp = (TTree*) fpp -> Get("yPhotonTree");
    TTree* ttgjpp = (TTree*) fpp -> Get("tgj");
    tphopp -> AddFriend(ttgjpp);

//
// Get purity and efficiency histogram from each file. 
//
    TFile* purityF = new TFile(Form("purity_%d.root", collision));
    TH1D* purityH = (TH1D*) purityF -> Get("purityH");
    TFile* effiF = new TFile(Form("efficiency_%d.root", collision));
    TH1D* effiH = (TH1D*) effiF -> Get("hRatio");
    
    TFile* purityFpp = new TFile("purity_0.root");
    TH1D* purityHpp = (TH1D*) purityFpp -> Get("purityH");
    TFile* effiFpp = new TFile("efficiency_0.root");
    TH1D* effiHpp = (TH1D*) effiFpp -> Get("hRatio");

//
// Define the histograms
//
    TH1D* hdata = new TH1D("hdata", ";p_{T}^{#gamma} (GeV); dN/dp_{T} (GeV^{-1})", nPtBin, ptBin);
    TH1D* hpucorr = new TH1D("hpucorr", "", nPtBin, ptBin);
    TH1D* hefficorr = new TH1D("hefficorr", ";p_{T}^{#gamma} (GeV); dN/dp_{T} (GeV^{-1})", nPtBin, ptBin);
    TH1D* hfinalcorr = new TH1D("hfinalcorr", ";p_{T}^{#gamma} (GeV); dN/dp_{T} (GeV^{-1})", nPtBin, ptBin);
    //TH1D* hffinalcorr = new TH1D("hffinalcorr", "", nPtBin, ptBin);
    TH1D* hdata_pp = new TH1D("hdata_pp", ";p_{T}^{#gamma} (GeV); dN/dp_{T} (GeV^{-1})", nPtBin, ptBin);
    TH1D* hpucorr_pp = new TH1D("hpucorr_pp", "", nPtBin, ptBin);
    TH1D* hefficorr_pp = new TH1D("hefficorr_pp",";p_{T}^{#gamma} (GeV); dN/dp_{T} (GeV^{-1})", nPtBin, ptBin);
    TH1D* hfinalcorr_pp = new TH1D("hfinalcorr_pp", ";p_{T}^{#gamma} (GeV); dN/dp_{T} (GeV^{-1})", nPtBin, ptBin);
    //TH1D* hffinalcorr_pp = new TH1D("hffinalcorr_pp", "", nPtBin, ptBin);

//
// Fill the Data in the histogram
//
    tpho -> Draw("corrPt >> hdata", weight*(centCut && dataCut));
    tphopp -> Draw("corrPt >> hdata_pp","ptHatWeight*vtxCentWeight*(abs(eta) < 1.44 && hadronicOverEm < 0.1 && (ecalRecHitSumEtConeDR04 < 4.2 && hcalTowerSumEtConeDR04 < 2.2 && trkSumPtHollowConeDR04 < 2) )" );
    
    hdata -> Scale(1., "width"); // divided by pt bin
    hdata_pp -> Scale(1., "width"); // divided by pt bin
    hpucorr -> Multiply(hdata, purityH);// modified by purity
    hpucorr_pp -> Multiply(hdata_pp, purityHpp);// modified by purity
    hefficorr -> Divide(hpucorr, effiH, 1., 1.);// modified by efficiency
    hefficorr_pp -> Divide(hpucorr_pp, effiHpp, 1., 1.);// modified by efficiency
    hfinalcorr = (TH1D*)hefficorr -> Clone();
    
    hdata -> SetMarkerColor(1);
    hdata_pp -> SetMarkerColor(1);
    hpucorr -> SetMarkerColor(2);
    hpucorr_pp -> SetMarkerColor(2);
    hefficorr -> SetMarkerColor(3);
    hefficorr_pp -> SetMarkerColor(3);
    
    TLegend* l1 = new TLegend(0.4, 0.6, 0.89, 0.80);
//    l1 -> SetFillColor(0);
//    l1 -> SetBorderSize(0);
    l1 -> AddEntry(hdata, "raw data");
    l1 -> AddEntry(hpucorr, "modified by purity");
    l1 -> AddEntry(hefficorr, "modified by efficiency");
    
    TLegend* lpp = new TLegend(0.4, 0.79, 0.89, 0.89);
    TLegend* ldata = new TLegend(0.4, 0.79, 0.89, 0.89);
    lpp -> SetHeader("pp #sqrt{s}_{_{NN}}=2.76 TeV");
    if(collision==1) ldata -> SetHeader("pPb #sqrt{s}_{_{NN}}=5.02 TeV");
    else if(collision==2) ldata -> SetHeader("PbPb #sqrt{s}_{_{NN}}=2.76 TeV 0-30 %"); 
    else if(collision==3) ldata -> SetHeader("PbPb #sqrt{s}_{_{NN}}=2.76 TeV 30-100 %"); 

    TH1D* hjetphox;
    if (collision == 1){    
        hjetphox = new TH1D("hjetphox", "", nPtBin, ptBin);
        hjetphox -> SetBinContent(1, 0.0715079*2.88);
        hjetphox -> SetBinContent(2, 0.0289211*2.88);
        hjetphox -> SetBinContent(3, 0.0100936*2.88);
        hjetphox -> SetBinContent(4, 0.00207405*2.88);
        hjetphox -> SetBinContent(5, 0.000113533*2.88);
        hfinalcorr -> Divide(hjetphox);
        hfinalcorr -> SetYTitle("R_{pPb}"); 
        hfinalcorr -> Scale(1./(TA*nMB)); 
     } else if(collision == 2 || collision == 3){
        hfinalcorr -> Divide(hefficorr_pp); 
        hfinalcorr -> SetYTitle("R_{PbPb}"); 
        hfinalcorr -> Scale(Luminosity_pp/(TA*nMB)); 
    }
    hfinalcorr -> SetMarkerStyle(20); 
    hfinalcorr -> SetTitleSize(0.05, "Y"); 
    hfinalcorr -> SetTitleSize(0.05, "X"); 
   
    TCanvas* c1 = new TCanvas("c1", "", 400, 400);
    c1 -> cd();
    hfinalcorr -> Draw();//Raa or Rpa
    ldata -> Draw();

    TCanvas* c2 = new TCanvas("c2", "", 800, 400);
    c2 -> Divide(2,1);
    TPad* p1 = (TPad*)c2 -> cd(1);
    c2 -> cd(1);
    p1 -> SetLogy();
    hdata -> Draw();
    hpucorr -> Draw("same");
    hefficorr -> Draw("same");
    l1 -> Draw();
    ldata -> Draw();

    TPad* p2 = (TPad*)c2 -> cd(2);
    c2 -> cd(2);
    p2 -> SetLogy();
    hdata_pp -> Draw();
    hpucorr_pp -> Draw("same");
    hefficorr_pp -> Draw("same");
    l1 -> Draw();
    lpp -> Draw();
}


