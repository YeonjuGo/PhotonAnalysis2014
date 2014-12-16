//the first draft 
//2013.10.21 am 10:10
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
#include <TRandom3.h>

void smearing(int collision = 2, int fixOpt = 0){//if fixOpt=0 (yes, it fixed) fixOpt=1(No, it isn't fixed)
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
    gStyle -> SetTitleYOffset(1.0);
    gStyle -> SetTitleXOffset(1.0);
    gStyle -> SetTitleYSize(0.045);
    gStyle -> SetTitleXSize(0.04);

    TLegend *l1 = new TLegend(0.4365615,0.6445304,0.9577623,0.846736,NULL,"brNDC");
    //
    //to calculate sigma
    //
    double sigma=0.0; 
    double cc=0.0;
    double ss=0.0;
    double nn=0.0; 

    //
    // cuts!!!
    // 
    TCut centCut = "";
    if ( (collision ==0) )   { // HI 0-30 %
        centCut = "cBin > 0 && cBin< 12";
        easyLeg(l1,"Pb+Pb 0-30%");
    }
    else if (  (collision ==1) ){  // HI 30-100 %
        centCut = "cBin >=12";
        easyLeg(l1,"Pb+Pb 30-100%");
    }
    else if (collision == 2 || collision == 3){ // pPb or pp
        centCut = "";
        if(collision == 2) {
            easyLeg(l1,"p+p");
            cc =0.056762;    
            ss =0.808114;    
            nn =0.000244992;
        } else easyLeg(l1, "p+Pb");
    }
    else if (  (collision ==4) ){  //HI 0-10
        centCut = "cBin > 0 && cBin < 4";
        easyLeg(l1,"Pb+Pb 0-10%"); 
        if(fixOpt==0) {
            cc =0.056762;    
            ss =0.808114;    
            nn =9.6876;
        } else if(fixOpt==1){
            cc =0.0560882;   
            ss =1.47838; 
            nn =0.115188;
        }

    } else if (  (collision ==5) ){  //HI 10-30
        centCut = "cBin >= 4 && cBin < 12";
        easyLeg(l1,"Pb+Pb 10-30%"); 
        if(fixOpt==0) {
            cc =0.056762;    
            ss =0.808114;    
            nn =8.21968;
        } else if(fixOpt==1){
            cc =0.0256674;   
            ss =1.40659;
            nn =-0.0341018;
        }

    } else if (  (collision ==6) ){  //HI 30-50
        centCut = "cBin >= 12 && cBin < 20";
        easyLeg(l1,"Pb+Pb 30-50%"); 
        if(fixOpt==0) {
            cc =0.056762;    
            ss =0.808114;    
            nn =7.02911;
        } else if(fixOpt==1){
            cc =0.00644361; 
            ss = 1.31446;
            nn = -0.0721935;
        }

    } else if (  (collision ==7) ){  //HI 50-100
        centCut = "cBin >= 20";
        easyLeg(l1,"Pb+Pb 50-100%");
        if(fixOpt==0) {
            cc =0.056762;    
            ss =0.808114;    
            nn =6.10214;
        } else if(fixOpt==1){
            cc =0.0170442;
            ss = 1.22837; 
            nn = 0.0511498;
        }
    }
    /*
       TCut partonCut = "";
    if (flvOpt ==0 ) partonCut = "";
    else if (flvOpt == 1 ) partonCut = "refPartonFlv == 21";
    else if (flvOpt == 2 ) partonCut = "abs(refPartonFlv) < 21";
    else partonCut = "refPartonFlv < -200";
*/
    TCut totalCut = centCut && "photonEt>40 && abs(genMomId)<=22 && (abs(eta) < 1.6) && (dphi > 7*3.141592/8.0)"; 

    multiTreeUtil* yJet = new multiTreeUtil();
    if(collision ==1 || collision == 0  || collision == 4 || collision == 5 || collision == 6|| collision == 7){// PbPb
        yJet -> addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_qcdAllPhoton30to50_genPhotonPtCut40_allCent.root", "yJet", totalCut, 32796./32796);
        yJet -> addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_qcdAllPhoton50to80_genPhotonPtCut40_allCent.root", "yJet", totalCut, 21470./53876);
        yJet -> addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_qcdAllPhoton80to9999_genPhotonPtCut40_allCent.root", "yJet", totalCut, 6462./58781);
    } else if (collision ==3){ //pA
        yJet->addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_PA2013_pyquen_allQCDPhoton30to50_forestv85.root", "yJet",totalCut, 56669./50385);
        yJet->addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_PA2013_pyquen_allQCDPhoton50to80_forestv85.root", "yJet",totalCut, 41906./114136);
        yJet->addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_PA2013_pyquen_allQCDPhoton80to120_forestv85.root", "yJet",totalCut, 12044./103562);
        yJet->addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_PA2013_pyquen_allQCDPhoton120to9999_forestv85.root", "yJet",totalCut, 4481./151511);
    } else if (collision ==2){ //pp
        yJet->addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_merged_allQCDPhoton30to50_genPhotonPtCut30_CMSSW538HIp2.root", "yJet", totalCut, 29329. / 29329.);
        yJet->addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_merged_allQCDPhoton50to80_genPhotonPtCut30_CMSSW538HIp2.root", "yJet", totalCut, 8098. / 87988.);
        yJet->addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_merged_allQCDPhoton80to120_genPhotonPtCut30_CMSSW538HIp2.root", "yJet", totalCut, 1680. / 96756.);
        yJet->addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_merged_allQCDPhoton120to9999_genPhotonPtCut30_CMSSW538HIp2.root", "yJet", totalCut, 438.   / 90972.);
    }

    yJet -> AddFriend("tgj");
    yJet->AddFriend("yPhotonTree");

    TCanvas* cGenPt = new TCanvas("cGenPt", "", 400, 400);
    TH1D* hGenPt = new TH1D("hGenPt", "; p_{T}^{GenJet} (GeV) ; Entries", 150, 0, 200);
    yJet -> Draw2(hGenPt, "refPt", "", "");
    hGenPt -> Scale(1./hGenPt->Integral());
    hGenPt -> Draw();

    TCanvas* cRecoPt = new TCanvas("cRecoPt", "", 400, 400);
    TH1D* hRecoPt = new TH1D("hRecoPt", "; p_{T}^{RecoJet} (GeV) ; Entries", 150, 0, 200);
    yJet -> Draw2(hRecoPt, "pt", "refPt>0", "");
    hRecoPt -> Scale(1./hRecoPt->Integral());
    hRecoPt -> Draw();

    TCanvas* cSmear = new TCanvas("cSmear", "", 400, 800);
    cSmear -> Divide(1,2);
    cSmear -> cd(1);

    TH1D* hSmear = new TH1D("hSmear", "; p_{T}^{Smeared} (GeV) ; Entries", 150, 0, 200); 
    for(int i=0; i<1000000; i++){
        double pt = hGenPt -> GetRandom();
        sigma = sqrt(cc*cc + ss*ss/pt + nn*nn/(pt*pt));
        TRandom3 rand(111); 
        double factor = rand.Gaus(1,sigma); 
        double newPt = pt*factor;
        hSmear -> Fill(newPt);
    }
    
    hSmear -> Scale(1./hSmear->Integral());
    hSmear -> Draw();
   
    cSmear -> cd(2);
    TH1D* hRatio = (TH1D*) hSmear -> Clone("hRatio");
    hRatio -> Divide(hRecoPt);
    hRatio -> SetYTitle("p_{T}^{smeared}/p_{T}^{Reco}");
    hRatio -> SetTitleOffset(0.8, "Y");
    hRatio -> Draw();

    cSmear -> SaveAs(Form("smeared_coll%d_fixOpt%d.pdf",collision,fixOpt));
}

