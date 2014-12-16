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

//
// old skim 
//
/*
    if(collision==0){//pp
        ff = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pp/yskim_pp2760_pythia_allQCDPhoton_CMSSW538HIp2.root");
        centCut = "";
        isolationCut = "(ecalRecHitSumEtConeDR04 < 4.2 && hcalTowerSumEtConeDR04 < 2.2 && trkSumPtHollowConeDR04< 2)";
    } else if(collision==1){//pA
        ff = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pA/backup/yskim_pA_Pyquen_allQCDPhoton_hiForest2_53x_2013-18-14-1922.root");
        isolationCut = "(ecalRecHitSumEtConeDR04 < 4.2 && hcalTowerSumEtConeDR04 < 2.2 && trkSumPtHollowConeDR04< 2)";
    } else if(collision==2){//AA 0-30%
        ff = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pbpb/backup/yskim_PbPb_pythiaHYDJET_forest_AllQCDPhotons.root");
        centCut = Form("((cBin) >= %i) && ((cBin) < %i)", CENTBINS[0], CENTBINS[1]);   
        isolationCut = "cc4+cr4+ct4PtCut20<1";
    } else if(collision==3){//AA 30-100%
        ff = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pbpb/backup/yskim_PbPb_pythiaHYDJET_forest_AllQCDPhotons.root");
        centCut = Form("((cBin) >= %i) && ((cBin) < %i)", CENTBINS[1], CENTBINS[2]);   
        isolationCut = "cc4+cr4+ct4PtCut20<1";
    }
*/

//
// new skim after vtxCentWeight and ptHatWeight
//

    if(collision==0){//pp
        ff = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pp/yskim_pp2760_pythia_allQCDPhoton_CMSSW538HIp2.root");
        centCut = "";
        isolationCut = "(ecalRecHitSumEtConeDR04 < 4.2 && hcalTowerSumEtConeDR04 < 2.2 && trkSumPtHollowConeDR04< 2)";
    } else if(collision==1){//pA
        ff = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pA/yskim_pA_Pyquen_allQCDPhoton_hiForest2_53x_2013-18-14-1922.root");
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


//
// get Tree
//
    TTree* tpho = (TTree*) ff -> Get("yPhotonTree");
    TTree* ttgj = (TTree*) ff -> Get("tgj"); 
    tpho -> AddFriend(ttgj);
    TH1D* hGen = new TH1D("hGen", ";p_{T}^{#gamma} (GeV); Entries", nPtBin, ptBin);
    TH1D* hReco = new TH1D("hReco", "p_{T}^{#gamma} (GeV); Entries", nPtBin, ptBin); 

    
//
//old skim
//
  /*
    if(collision==0 || collision==1){
        tpho -> Draw("genMatchedPt >> hGen", "1.0*1.0*(genCalIsoDR04<5 && abs(genMomId)<=22 && abs(eta)<1.44 && hadronicOverEm<0.1)");
        tpho -> Draw("genMatchedPt >> hReco", "1.0*1.0*( (genCalIsoDR04<5 && abs(genMomId)<=22 && abs(eta)<1.44 && hadronicOverEm<0.1)     &&    ecalRecHitSumEtConeDR04 < 4.2 && hcalTowerSumEtConeDR04 < 2.2 && trkSumPtHollowConeDR04< 2)");
    } else if(collision==2) {
        tpho -> Draw("genMatchedPt >> hGen", "1.0*1.0*(genCalIsoDR04<5 && abs(genMomId)<=22 && abs(eta)<1.44 && hadronicOverEm<0.1 && (cBin >= 0) && (cBin < 12))");
        tpho -> Draw("genMatchedPt >> hReco", "1.0*1.0*((genCalIsoDR04<5 && abs(genMomId)<=22 && abs(eta)<1.44 && hadronicOverEm<0.1 && (cBin >= 0) && (cBin < 12))   &&    cc4+cr4+ct4PtCut20<1 )");
    } else if(collision==3) {
        tpho -> Draw("genMatchedPt >> hGen", "1.0*1.0*(genCalIsoDR04<5 && abs(genMomId)<=22 && abs(eta)<1.44 && hadronicOverEm<0.1&&(cBin >= 12) && (cBin < 40))");
        tpho -> Draw("genMatchedPt >> hReco", "1.0*1.0*((genCalIsoDR04<5 && abs(genMomId)<=22 && abs(eta)<1.44 && hadronicOverEm<0.1&&(cBin >= 12) && (cBin < 40))    &&  cc4+cr4+ct4PtCut20<1  )");
    }
*/
    
//
//new skim
//

    if(collision==0 || collision==1){
        tpho -> Draw("genMatchedPt >> hGen", "ptHatWeight*vtxCentWeight*(genCalIsoDR04<5 && abs(genMomId)<=22 && abs(eta)<1.44 && hadronicOverEm<0.1)");
        tpho -> Draw("genMatchedPt >> hReco", "ptHatWeight*vtxCentWeight*( (genCalIsoDR04<5 && abs(genMomId)<=22 && abs(eta)<1.44 && hadronicOverEm<0.1) && ecalRecHitSumEtConeDR04 < 4.2 && hcalTowerSumEtConeDR04 < 2.2 && trkSumPtHollowConeDR04< 2)");
    } else if(collision==2) {
        tpho -> Draw("genMatchedPt >> hGen", "ptHatWeight*vtxCentWeight*(genCalIsoDR04<5 && abs(genMomId)<=22 && abs(eta)<1.44 && hadronicOverEm<0.1 && (cBin >= 0) && (cBin < 12))");
        tpho -> Draw("genMatchedPt >> hReco", "ptHatWeight*vtxCentWeight*((genCalIsoDR04<5 && abs(genMomId)<=22 && abs(eta)<1.44 && hadronicOverEm<0.1 && (cBin >= 0) && (cBin < 12))   &&    cc4+cr4+ct4PtCut20<1 )");
    } else if(collision==3) {
        tpho -> Draw("genMatchedPt >> hGen", "ptHatWeight*vtxCentWeight*(genCalIsoDR04<5 && abs(genMomId)<=22 && abs(eta)<1.44 && hadronicOverEm<0.1&&(cBin >= 12) && (cBin < 40))");
        tpho -> Draw("genMatchedPt >> hReco", "ptHatWeight*vtxCentWeight*((genCalIsoDR04<5 && abs(genMomId)<=22 && abs(eta)<1.44 && hadronicOverEm<0.1&&(cBin >= 12) && (cBin < 40))    &&  cc4+cr4+ct4PtCut20<1  )");
    }

    TFile* wf = new TFile(Form("efficiency_%d.root", collision), "RECREATE");
    
    TCanvas* c1 = new TCanvas("c1", "", 400, 400);
   // c1 -> Divide(1,2);
   // c1 -> cd(1);
    hGen -> Draw("hist"); 
    hReco -> SetLineColor(2);
    hReco -> Draw("p same");
   
// ratio 
   // c1 -> cd(2);
   
    TCanvas* c2 = new TCanvas("c2", "", 400, 400);
    TH1D* hRatio;
    hRatio = new TH1D("hRatio", ";p_{T}^{#gamma} (GeV); Isolation Efficiency (reco/gen)", nPtBin, ptBin);
    hRatio -> Divide(hReco, hGen, 1., 1.);
    hRatio -> SetLineColor(1);
    hRatio -> Draw();
    hRatio -> SetAxisRange(0.6,1,"Y");
    //hRatio -> SetTitleOffset(1.3, "Y"); 
    hRatio -> SetTitleSize(0.05, "Y");
    hRatio -> SetTitleSize(0.05, "X");
    hRatio -> SetMarkerStyle(20);
  
    TLegend* l2 = new TLegend(0.2, 0.7, 0.82, 0.82);
  //  l2 -> SetFillColor(0);
  //  l2 -> SetBorderSize(0);
    if(collision == 1) l2 -> SetHeader("pPb #sqrt{s}_{_{NN}}=5.02 TeV");
    else if(collision == 2) l2 -> SetHeader("PbPb #sqrt{s}_{_{NN}}=2.76 TeV 0-30 %");
    else if(collision == 3) l2 -> SetHeader("PbPb #sqrt{s}_{_{NN}}=2.76 TeV 30-100 %");
    else if(collision == 0) l2 -> SetHeader("pp #sqrt{s}_{_{NN}}=2.76 TeV");
    l2 -> Draw();

    c1 -> cd();
    l2 -> Draw();
    wf -> Write();
//    wf -> Write("hRatio");
  
        /*    
    TLegend* l1 = new TLegend(0.6, 0.6, 0.9, 0.9);
    l1 -> SetFillColor(0);
    l1 -> AddEntry(hRatio, "reco/gen");
  //  l1 -> AddEntry(hRatio[1], "reco(including hovere cut)/gen");
  //  l1 -> AddEntry(hRatio[2], "reco(including isolation cut)/gen");
    l1 -> Draw();
  */  
 
}


