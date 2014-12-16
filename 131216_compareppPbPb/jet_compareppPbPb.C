// yeonju
// compare pp MC and PbPb MC to check on (confirm) the consistency of the gen information
// both files are new including phHatWeight
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


void jet_compareppPbPb(){
    gStyle -> SetOptStat(0);
    const int nPtBin = 12; 
    double ptBin[nPtBin+1];
    double AvePtBin[nPtBin];

    ptBin[0] = 30.0;
    ptBin[1] = 40.0;
    ptBin[2] = 50.0;
    ptBin[3] = 60.0;
    ptBin[4] = 70.0;
    ptBin[5] = 80.0;
    ptBin[6] = 90.0;
    ptBin[7] = 100.0;
    ptBin[8] = 120.0;
    ptBin[9] = 140.0;
    ptBin[10] = 160.0;
    ptBin[11] = 180.0;
    ptBin[12] = 200.0;

    for(int i=0;i<nPtBin;i++){
        AvePtBin[i] = (ptBin[i+1]+ptBin[i])/2.0;
    } 
 

    TLegend *l1 = new TLegend(0.5865615,0.7045304,0.8577623,0.846736,NULL,"brNDC");
    l1 -> SetFillColor(0);
    l1 -> SetBorderSize(0);
    
    TFile* fpbpb = new TFile("/home/jazzitup/analysis/photonJetAnalysis2013/photonSkimProducer/yskim_PbPb_pythiaHYDJET_forest_AllQCDPhotons305080.root");
    TTree* tpbpb = (TTree*) fpbpb -> Get("tgj");
    TTree* tpbpbJet = (TTree*) fpbpb -> Get("yJet");
    tpbpb -> AddFriend(tpbpbJet);
    TH1F* hpbpb = new TH1F("hpbpb", "refPt", nPtBin, ptBin);
   // tpbpb -> Draw("refPt >> hpbpb", "ptHatWeight");
   // tpbpb -> Draw("refPt >> hpbpb", "ptHatWeight*(photonEt>40 && genPhotonEt>30 && abs(genMomId)<=22)");
    tpbpb -> Draw("refPt >> hpbpb", "ptHatWeight*(photonEt>40 && genPhotonEt>30 && abs(genMomId)<=22 && abs(eta)<1.6 && abs(dphi)>7*3.141592/8.0)");
  //  tpbpb -> Draw("refPt >> hpbpb", "ptHatWeight*(photonEt>40 && genPhotonEt>30 && abs(genMomId)<=22 && abs(eta)<1.6)");
    hpbpb -> Scale(1., "width");
    //cout << 1./hpbpb -> Integral("width") << endl;
    hpbpb -> Scale(1./hpbpb -> Integral("width"));
    hpbpb -> SetLineColor(2);
    //cout << 1./hpbpb -> Integral("width") << endl;

    TFile* fpp = new TFile("/home/jazzitup/analysis/photonJetAnalysis2013/photonSkimProducer/yskim_merged_allQCDPhoton305080_CMSSW538HIp2.root");
    TTree* tpp = (TTree*) fpp -> Get("tgj");
    TTree* tppJet = (TTree*) fpp -> Get("yJet");
    tpp -> AddFriend(tppJet); 
    TH1F* hpp = new TH1F("hpp", "refPt", nPtBin, ptBin);
  //  tpp -> Draw("refPt >> hpp", "ptHatWeight");
   // tpp -> Draw("refPt >> hpp", "ptHatWeight*(photonEt>40 && genPhotonEt>30 && abs(genMomId)<=22)");
    tpp -> Draw("refPt >> hpp", "ptHatWeight*(photonEt>40 && genPhotonEt>30 && abs(genMomId)<=22 && abs(eta)<1.6 && abs(dphi)>7*3.141592/8.0)");
  //  tpp -> Draw("refPt >> hpp", "ptHatWeight*(photonEt>40 && genPhotonEt>30 && abs(genMomId)<=22 && abs(eta)<1.6)");
    hpp -> Scale(1.,"width");
    hpp -> Scale(1./hpp->Integral("width"));

    TCanvas* c1 = new TCanvas("c1", "c1", 400, 400);
    c1 -> cd();
    hpbpb -> Draw();
    hpp -> Draw("same");
    
    l1 -> AddEntry("hpp", "pp");
    l1 -> AddEntry("hpbpb", "PbPb");
    l1 -> Draw();
    gPad -> SetLogy();
}

