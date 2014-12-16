#include "../HiForestAnalysis/hiForest.h"
#include "../gammaJetAnalysis/CutAndBinCollection2012.h"
#include <TROOT.h>
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

void efficiency(int collision=1){
    gROOT -> Macro("yjStyle.C");
    TH1::SetDefaultSumw2();
    gStyle -> SetOptStat(0);

    const int nPtBin = 5; 
    double ptBin[nPtBin+1]={40, 50, 60, 80, 120, 300};
    double AvePtBin[nPtBin];
    const int CENTBINS[] = {0, 12, 40};
    
    TFile* ff;
    TFile* fdata;
    TCut centCut;
    TCut genCut = "genCalIsoDR04<5 && abs(genMomId)<=22 && abs(eta)<1.44 && hadronicOverEm<0.1";
    TCut isolationCut;
    if(collision==0){//pp
        ff = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pp/yskim_pp2760_pythia_allQCDPhoton_CMSSW538HIp2.root");
        centCut = "";
        isolationCut = "(ecalRecHitSumEtConeDR04 < 4.2 && hcalTowerSumEtConeDR04 < 2.2 && trkSumPtHollowConeDR04< 2)";
    } else if(collision==1){//pA
        ff = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pA/yj_yskim_pA_Pyquen_allQCDPhoton_hiForest2_53x_2013-18-14-1922.root");
        isolationCut = "(ecalRecHitSumEtConeDR04 < 4.2 && hcalTowerSumEtConeDR04 < 2.2 && trkSumPtHollowConeDR04< 2)";
    } else if(collision==2){//AA 0-30%
        ff = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pbpb/yskim_PbPb_pythiaHYDJET_forest_AllQCDPhotons.root");
        centCut = Form("((cBin) >= %i) && ((cBin) < %i)", CENTBINS[0], CENTBINS[1]);   
        isolationCut = "cc4+cr4+ct4PtCut20<1";
    } else if(collision==3){//AA 30-100%
        ff = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pbpb/yskim_PbPb_pythiaHYDJET_forest_AllQCDPhotons.root");
        centCut = Form("((cBin) >= %i) && ((cBin) < %i)", CENTBINS[1], CENTBINS[2]);   
        isolationCut = "cc4+cr4+ct4PtCut20<1";
    }
    TTree* tpho = (TTree*) ff -> Get("yPhotonTree");
    TTree* ttgj = (TTree*) ff -> Get("tgj"); 
    tpho -> AddFriend(ttgj);
    TH1D* hGen = new TH1D("hGen", "", nPtBin, ptBin);
    TH1D* hReco[3]; 
    for(int i=0; i<3; i++){ 
        hReco[i] = new TH1D(Form("hReco%d",i), "", nPtBin, ptBin);
    }
    if(collision==0 || collision==1){
        //tgen -> Draw("et >> hGen", "id==22 && abs(momId)<=22 && abs(eta) < 1.44 && status==1");
        tpho -> Draw("genMatchedPt >> hGen", "vtxCentWeight*(genCalIsoDR04<5 && abs(genMomId)<=22 && abs(eta)<1.44 && hadronicOverEm<0.1)");
        tpho -> Draw("genMatchedPt >> hReco0", "vtxCentWeight*(abs(genMomId)<=22 && abs(eta) < 1.44)");// test
        tpho -> Draw("genMatchedPt >> hReco1", "vtxCentWeight*(abs(genMomId)<=22 && abs(eta) < 1.44 && hadronicOverEm < 0.1)");
        tpho -> Draw("genMatchedPt >> hReco2", "vtxCentWeight*(ecalRecHitSumEtConeDR04 < 4.2 && hcalTowerSumEtConeDR04 < 2.2 && trkSumPtHollowConeDR04< 2)");
    } else if(collision==2) {
        tpho -> Draw("genMatchedPt >> hGen", "vtxCentWeight*(genCalIsoDR04<5 && abs(genMomId)<=22 && abs(eta)<1.44 && hadronicOverEm<0.1&&(cBin >= 0) && (cBin < 12))");
        tpho -> Draw("genMatchedPt >> hReco0", "vtxCentWeight*(abs(genMomId)<=22 && abs(eta) < 1.44 && (cBin >= 0) && (cBin < 12))");// test
        tpho -> Draw("genMatchedPt >> hReco1", "vtxCentWeight*(abs(genMomId)<=22 && abs(eta) < 1.44 && hadronicOverEm < 0.1&& (cBin >= 0) && (cBin < 12))");
        tpho -> Draw("genMatchedPt >> hReco2", "vtxCentWeight*(cc4+cr4+ct4PtCut20<1 && (cBin >= 0) && (cBin < 12) )");
    } else if(collision==3) {
        tpho -> Draw("genMatchedPt >> hGen", "vtxCentWeight*(genCalIsoDR04<5 && abs(genMomId)<=22 && abs(eta)<1.44 && hadronicOverEm<0.1&&(cBin >= 12) && (cBin < 40))");
        tpho -> Draw("genMatchedPt >> hReco0", "vtxCentWeight*(abs(genMomId)<=22 && abs(eta) < 1.44 && (cBin >= 12) && (cBin < 40))");// test
        tpho -> Draw("genMatchedPt >> hReco1", "vtxCentWeight*(abs(genMomId)<=22 && abs(eta) < 1.44 && hadronicOverEm < 0.1&& (cBin >= 12) && (cBin < 40))");
        tpho -> Draw("genMatchedPt >> hReco2", "vtxCentWeight*(cc4+cr4+ct4PtCut20<1 && (cBin >= 12) && (cBin < 40) )");
    }

    TCanvas* c1 = new TCanvas("c1", "", 400, 800);
    c1 -> Divide(1,2);
    c1 -> cd(1);
    hGen -> Draw("hist");
    hReco[0] -> SetLineColor(1);
    hReco[1] -> SetLineColor(2);
    hReco[2] -> SetLineColor(3);
    hReco[0] -> Draw("p same");
    hReco[1] -> Draw("p same");
    hReco[2] -> Draw("p same");
   
    TFile* wf = new TFile(Form("efficiency_%d.root", collision), "RECREATE");
// ratio 
    c1 -> cd(2);
    TH1D* hRatio[3];
    for(int i=0; i<3; i++){ 
        hRatio[i] = new TH1D(Form("hRatio%d",i), ";p_{T}^{#gamma} (GeV); Isolation Efficiency (reco/gen)", nPtBin, ptBin);
        hRatio[i] -> Divide(hReco[i], hGen, 1., 1.);
        hRatio[i] -> SetLineColor(i+1);
        if(i==0) {
            hRatio[i] -> Draw();
            hRatio[i] -> SetAxisRange(0,1,"Y");
        } else hRatio[i] -> Draw("same");
    }
    TLegend* l1 = new TLegend(0.6, 0.6, 0.9, 0.9);
    l1 -> SetFillColor(0);
    l1 -> AddEntry(hRatio[0], "reco/gen");
    l1 -> AddEntry(hRatio[1], "reco(including hovere cut)/gen");
    l1 -> AddEntry(hRatio[2], "reco(including isolation cut)/gen");
    l1 -> Draw();
    
    wf -> Write("hRatio2");
    TCanvas* c2 = new TCanvas("c2", "", 400, 400);
    c2 -> cd();
    hRatio[2] -> Draw();
    hRatio[2] -> SetLineColor(1);
    //hRatio[2] -> SetTitleOffset(1.3, "Y"); 
    hRatio[2] -> SetTitleSize(0.05, "Y");
    hRatio[2] -> SetTitleSize(0.05, "X");
    hRatio[2] -> SetMarkerStyle(20);
    hRatio[2] -> SetAxisRange(0.75, 0.9,  "Y");
    TLegend* l2 = new TLegend(0.3, 0.7, 0.85, 0.85);
    l2 -> SetFillColor(0);
    l2 -> SetBorderSize(0);
    //l2 -> AddEntry(hRatio[2], "isolation efficiency");
    if(collision == 1) l2 -> SetHeader("pPb #sqrt{s}_{_{NN}}=5.02 TeV");
    else if(collision == 2) l2 -> SetHeader("PbPb #sqrt{s}_{_{NN}}=2.76 TeV 0-30 %");
    else if(collision == 3) l2 -> SetHeader("PbPb #sqrt{s}_{_{NN}}=2.76 TeV 30-100 %");
    else if(collision == 0) l2 -> SetHeader("pp #sqrt{s}_{_{NN}}=2.76 TeV");
    l2 -> Draw();
}


