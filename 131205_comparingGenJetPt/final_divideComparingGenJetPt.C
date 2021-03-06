// yeonju
// comparing genjetpt PbPb vs pp
// with respect to the same ptHat range.
//
#include "../HiForestAnalysis/hiForest.h"
#include "../gammaJetAnalysis/CutAndBinCollection2012.h"
#include <TStyle.h>
#include <TH1D.h>
#include <TTree.h>
#include <TBranch.h>
#include <TFile.h>
#include <iostream>
#include <TCanvas.h>
#include <TF1.h>
#include <TGraphAsymmErrors.h>
#include <TLegend.h>
#include <TCut.h>

TH1D* getHist(int collision, TH1D* hh);

void TestComparingGenJetPt(){

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
 
    TCanvas* c1 = new TCanvas("c1", "c1", 400, 400);

    TLegend *l1 = new TLegend(0.4365615,0.6445304,0.9577623,0.846736,NULL,"brNDC");
    l1 -> SetFillColor(0);
    l1 -> SetBorderSize(0);
    TH1D* hPbPb = new TH1D("hGenJetPt_pbpb", "Jet p_{T}^{Gen}", nPtBin, ptBin);
    TH1D* hpp = new TH1D("hGenJetPt_pp", "Jet p_{T}^{Gen}", nPtBin, ptBin);
    hPbPb = getHist(4, hPbPb);
    hPbPb -> Scale(1./hPbPb->Integral("width"),"width");
    hpp = getHist(2, hpp);
    hpp -> Scale(1./hpp->Integral("width"),"width");
    l1 -> AddEntry(hPbPb, "PbPb");
    l1 -> AddEntry(hpp, "pp");
    hPbPb -> Draw();
    hpp -> Draw("same p");
    l1 -> Draw("same");
}

TH1D* getHist(int collision, TH1D* hh){
/* 
    const int kHIcentral = 0; // 0-30%
    const int kHIperipheral = 1;//30-100%
    const int kPP = 2;
    const int kPA = 3;
    const int kHI010 = 4; //0-10%
    const int kHI1030 = 5; //10-30%
    const int kHI3050 = 6;//30-50%
    const int kHI50100 = 7;//50-100%
*/

    TH1::SetDefaultSumw2();

    gStyle -> SetOptFit(0);
    gStyle -> SetOptStat(0);
    gStyle -> SetTitleYOffset(2.35);
    gStyle -> SetTitleYSize(0.04);
   

    TLegend *l1 = new TLegend(0.4365615,0.6445304,0.9577623,0.846736,NULL,"brNDC");
    TCut centCut = "";
    if ( (collision ==0) )   {
        centCut = "cBin > 0 && cBin< 12";
        easyLeg(l1,"Pb+Pb 0-30%");
    }
    else if (  (collision ==1) ){  // if it's pp 
        centCut = "cBin >=12";
        easyLeg(l1,"Pb+Pb 30-100%");
    }
    else if (collision == 2 || collision == 3){ // pPb
        centCut = "";
        if (collision == 2) easyLeg(l1,"p+p");
        else easyLeg(l1, "p+Pb");
    }
    else if (  (collision ==4) ){  //HI
        centCut = "cBin > 0 && cBin < 4";
        easyLeg(l1,"Pb+Pb 0-10%");
    } else if (  (collision ==5) ){  //HI
        centCut = "cBin >= 4 && cBin < 12";
        easyLeg(l1,"Pb+Pb 10-30%");
    } else if (  (collision ==6) ){  //HI
        centCut = "cBin >= 12 && cBin < 20";
        easyLeg(l1,"Pb+Pb 30-50%");
    } else if (  (collision ==7) ){  //HI
        centCut = "cBin >= 20";
        easyLeg(l1,"Pb+Pb 50-100%");
    }
/*
    int nJetmax = 100;
    float refPt[nJetmax], pt[nJetmax], eta[nJetmax], dphi[nJetmax];
    int nJet, cBin, refPartonFlv[nJetmax];
    EvtSel evtImb;
    TBranch *b_evt;
    */
    if (collision !=2 && collision !=3){
        multiTreeUtil* yJetPbPb = new multiTreeUtil();
        //new forest PbPb
        if(pthat==1)
        yJetPbPb -> addFile("/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/yskim_PbPb_pythiaHYDJET_forest_AllQCDPhotons30.root", "yJet", "");
        yJetPbPb -> addFile("/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/yskim_PbPb_pythiaHYDJET_forest_AllQCDPhotons50.root", "yJet", "");
        yJetPbPb -> addFile("/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/yskim_PbPb_pythiaHYDJET_forest_AllQCDPhotons80.root", "yJet", "");
        yJetPbPb -> addFile("/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/yskim_PbPb_pythiaHYDJET_forest_AllQCDPhotons120.root", "yJet", "");
       // yJetPbPb -> addFile("/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/yskim_PbPb_pythiaHYDJET_forest_AllQCDPhotons170.root", "yJet", "");
        yJetPbPb->AddFriend("tgj");
        yJetPbPb->AddFriend("yPhotonTree");

       // TCanvas* c1 = new TCanvas("c1", "GenJetPt", 400, 400);

        yJetPbPb -> Draw2(hh, "refPt", centCut && "photonEt>40 && genPhotonEt> 30 && abs(genMomId)<=22 && (abs(eta) < 1.6) && (dphi > 7*3.141592/8.0)", "ptHatWeight");
        handsomeTH1(hh,1);
        //hh -> Draw();

        return hh;
    }

    // old pp
    if (collision == 2){
        multiTreeUtil* yJetpp = new multiTreeUtil();
        yJetpp->addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_merged_allQCDPhoton30to50_genPhotonPtCut30_CMSSW538HIp2.root", "yJet", "");
     //   yJetpp->addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_merged_allQCDPhoton50to80_genPhotonPtCut30_CMSSW538HIp2.root", "yJet", "");
     //   yJetpp->addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_merged_allQCDPhoton80to120_genPhotonPtCut30_CMSSW538HIp2.root", "yJet", "");
     //   yJetpp->addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_merged_allQCDPhoton120to9999_genPhotonPtCut30_CMSSW538HIp2.root", "yJet", "");
        yJetpp->AddFriend("tgj");
        yJetpp->AddFriend("yPhotonTree");

        //hh = new TH1D("hGenJetPt_pp", "", nPtBin, ptBin);
        //hGenJetPt_pp -> SetBinContent(10, 0.001);
        yJetpp -> Draw2(hh, "refPt","photonEt>40 && genPhotonEt> 30 && abs(genMomId)<=22 && (abs(eta) < 1.6) && (dphi > 7*3.141592/8.0)", "");
        //  yJetpp -> Draw2(hGenJetPt_pp, "nJet","");
        handsomeTH1(hh,2);
        //hGenJetPt_pp -> Draw();
        return hh;
    }
}
