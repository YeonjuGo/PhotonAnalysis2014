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


void gen_compareppPbPb(){
    TH1::SetDefaultSumw2();

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
    
    TFile* fpbpb = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/yskim_PbPb_pythiaHYDJET_forest_AllQCDPhotons30.root");
    //TFile* fpbpb = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/merged_yskim_PbPb_pythiaHYDJET_forest_AllQCDPhotons305080.root");
    TTree* tpbpb = (TTree*) fpbpb -> Get("tgj");
    TTree* tpbpbGen = (TTree*) fpbpb -> Get("genTree");
    tpbpb -> AddFriend(tpbpbGen);
    TH1F* hpbpb = new TH1F("hpbpb", "ptHat{only AllQCDPhotons30 file}", nPtBin, ptBin);
    //tpbpb -> Draw("ptHat >> hpbpb", "ptHatWeight");
    tpbpb -> Draw("ptHat >> hpbpb", "ptHatWeight*(et>40 && abs(momId)<=22 && id==22 && abs(eta)<1.44) ");
   // tpbpb -> Draw("photonRawEt >> hpbpb", "ptHatWeight*(photonEt>40 && abs(genMomId)<=22 && abs(photonEta)<1.44 && abs(lJetDphi)>7*3.141592/8.0)");
  //  tpbpb -> Draw("photonRawEt >> hpbpb", "ptHatWeight*(photonEt>40 && abs(genMomId)<=22 && abs(photonEta)<1.44)");
    hpbpb -> Scale(1., "width");
    //cout << 1./hpbpb -> Integral("width") << endl;
    hpbpb -> Scale(1./hpbpb -> Integral("width"));
    hpbpb -> SetLineColor(2);
    //cout << 1./hpbpb -> Integral("width") << endl;

    TFile* fpp = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/yskim_pp2760_pythia_allQCDPhoton30_CMSSW538HIp2.root");
    //TFile* fpp = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/merged_yskim_pp2760_pythia_allQCDPhoton305080.root");
    TTree* tpp = (TTree*) fpp -> Get("tgj");
    TTree* tppGen = (TTree*) fpp -> Get("genTree");
    tpp -> AddFriend(tppGen); 
    TH1F* hpp = new TH1F("hpp", "", nPtBin, ptBin);
    //tpp -> Draw("ptHat >> hpp", "ptHatWeight");
    tpp -> Draw("ptHat >> hpp", "ptHatWeight*(et>40 && abs(momId)<=22 && id==22 && abs(eta)<1.44)");
   // tpp -> Draw("photonRawEt >> hpp", "ptHatWeight*(photonEt>40 && abs(genMomId)<=22 && abs(photonEta)<1.44 && abs(lJetDphi)>7*3.141592/8.0)");
   // tpp -> Draw("photonRawEt >> hpp", "ptHatWeight*(photonEt>40 && abs(genMomId)<=22 && abs(photonEta)<1.44)");
    hpp -> Scale(1.,"width");
    hpp -> Scale(1./hpp->Integral("width"));

    TCanvas* c1 = new TCanvas("c1", "c1", 400, 400);
    c1 -> cd();
    hpbpb -> Draw("p e");
    hpp -> Draw("same hist");
    
    l1 -> AddEntry("hpp", "pp");
    l1 -> AddEntry("hpbpb", "PbPb");
    l1 -> Draw();
    gPad -> SetLogy();
}

