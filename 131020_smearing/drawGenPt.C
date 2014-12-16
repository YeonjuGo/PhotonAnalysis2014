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

void drawGenPt(int fixOpt=0){
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
//    gStyle -> SetOptLogy(); 
    gStyle -> SetTitleYSize(0.065);
    gStyle -> SetTitleXSize(0.065);

    TLegend *l2 = new TLegend(0.111127,0.7241099,0.8205091,0.8773607,NULL,"brNDC");
    if(fixOpt==0) easyLeg(l2,"fixed");
    else easyLeg(l2," NOT fixed");
//
// cuts!!!
//  
    TCut centCut0 = "";//pp
    TCut centCut1 = "cBin > 0 && cBin < 4";//HI 0-10 %
    TCut centCut2 = "cBin >= 4 && cBin < 12"; // HI 10-30 %
    TCut centCut3 = "cBin >= 12 && cBin < 20";// HI 30-50 %
    TCut centCut4 = "cBin >= 20";// HI 50-100 %

    TCut totalCut = "photonEt>40 && abs(genMomId)<=22 && (abs(eta) < 1.6) && (dphi > 7*3.141592/8.0)"; 

    multiTreeUtil* yJetpp = new multiTreeUtil();
    multiTreeUtil* yJetpb = new multiTreeUtil();
    // PbPb
    yJetpb -> addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_qcdAllPhoton30to50_genPhotonPtCut40_allCent.root", "yJet", totalCut, 32796./32796);
    yJetpb -> addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_qcdAllPhoton50to80_genPhotonPtCut40_allCent.root", "yJet", totalCut, 21470./53876);
    yJetpb -> addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_qcdAllPhoton80to9999_genPhotonPtCut40_allCent.root", "yJet",totalCut, 6462./58781);
    //pp
    yJetpp -> addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_merged_allQCDPhoton30to50_genPhotonPtCut30_CMSSW538HIp2.root", "yJet",totalCut, 29329. / 29329.);
    yJetpp -> addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_merged_allQCDPhoton50to80_genPhotonPtCut30_CMSSW538HIp2.root", "yJet",totalCut, 8098. / 87988.);
    yJetpp -> addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_merged_allQCDPhoton80to120_genPhotonPtCut30_CMSSW538HIp2.root", "yJet",totalCut, 1680. / 96756.);
    yJetpp -> addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_merged_allQCDPhoton120to9999_genPhotonPtCut30_CMSSW538HIp2.root", "yJet",totalCut, 438.   / 90972.);

    yJetpb -> AddFriend("tgj");
    yJetpp -> AddFriend("tgj");

    TCanvas* cGenPt = new TCanvas("cGenPt", "", 900, 300);
    makeMultiPanelCanvas(cGenPt, 4, 1);
    //makeMultiPanelCanvas(cGenPt, 1, 2);
    //cGenPt -> Divide(1,2);

    TH1D* hGenPt[5];
    TH1D* hGenPt_ratio[5];
    for(int icoll=0; icoll<5; icoll++){
        hGenPt[icoll]= new TH1D(Form("hGenPt%d",icoll), "; p_{T}^{GenJet} (GeV) ; Entries", 20, 0, 200);
    }

    yJetpp -> Draw2(hGenPt[0], "refPt", "", "");
    yJetpb -> Draw2(hGenPt[1], "refPt", centCut1, "");
    yJetpb -> Draw2(hGenPt[2], "refPt", centCut2, "");
    yJetpb -> Draw2(hGenPt[3], "refPt", centCut3, "");
    yJetpb -> Draw2(hGenPt[4], "refPt", centCut4, "");

    TLegend* l1 = new TLegend(0.3014874,0.5593653,0.6951945,0.9195046,NULL,"brNDC");
    l1 -> SetFillColor(0);
    l1 -> SetBorderSize(0);    
    cGenPt -> cd(1);
    double norm[5];
    for(int icoll=0; icoll<5; icoll++){
      norm[icoll] = hGenPt[icoll]->Integral(); 
      hGenPt[icoll] -> Scale(1./norm[icoll]);
        
        handsomeTH1(hGenPt[icoll], icoll+1, 0.5);
        if(icoll==0) {
            hGenPt[icoll] -> Draw();
        } else {
            hGenPt[icoll] -> Draw("same");  
            hGenPt_ratio[icoll] = (TH1D*) hGenPt[icoll] -> Clone(Form("hGenPt_ratio%d",icoll));
        }
    }

    l1 -> AddEntry(hGenPt[0], "pp");
    l1 -> AddEntry(hGenPt[1], "PbPb 0-10%");
    l1 -> AddEntry(hGenPt[2], "PbPb 10-30%");
    l1 -> AddEntry(hGenPt[3], "PbPb 30-50%");
    l1 -> AddEntry(hGenPt[4], "PbPb 50-100%");
    l1 -> Draw();

    for(int icoll=1; icoll<5; icoll++){    
        cGenPt -> cd(icoll);
        hGenPt_ratio[icoll] -> Divide(hGenPt[0]);
     //   if(icoll==1) {
            hGenPt_ratio[icoll] -> Draw();
            hGenPt_ratio[icoll] -> SetYTitle("p_{T}^{PbPb}/p_{T}^{pp}");
            hGenPt_ratio[icoll] -> SetAxisRange(0.4,1.4,"Y"); 
            jumSun(0,1,200,1,2);
     //   } else{ 
     //       hGenPt_ratio[icoll] -> Draw("same");
     //       jumSun(0,1,200,1,2);
     //   }
    }
    
    TCanvas* cRecoPt = new TCanvas("cRecoPt", "", 400, 800);
  //  makeMultiPanelCanvas(cRecoPt, 1, 2);
    cRecoPt -> Divide(1,2);
  
    TH1D* hRecoPt[5];
    TH1D* hRecoPt_ratio[5];
    for(int icoll=0; icoll<5; icoll++){
        hRecoPt[icoll]= new TH1D(Form("hRecoPt%d",icoll), "; p_{T}^{RecoJet} (GeV) ; Normalized Entries", 20, 0, 200);
    }

    yJetpp -> Draw2(hRecoPt[0], "pt","refPt>0", "");
    yJetpb -> Draw2(hRecoPt[1], "pt","refPt>0" && centCut1, "");
    yJetpb -> Draw2(hRecoPt[2], "pt","refPt>0" && centCut2, "");
    yJetpb -> Draw2(hRecoPt[3], "pt","refPt>0" && centCut3, "");
    yJetpb -> Draw2(hRecoPt[4], "pt","refPt>0" && centCut4, "");

    cRecoPt -> cd(1);
    for(int icoll=0; icoll<5; icoll++){
        handsomeTH1(hRecoPt[icoll], icoll+1, 0.5);
        hRecoPt[icoll] -> Scale(1./norm[icoll]); //hRecoPt[icoll]->Integral());
        hRecoPt[icoll] -> SetLineColor(icoll+1);
        if(icoll==0) {
            hRecoPt[icoll] -> Draw();
        } else {
            hRecoPt[icoll] -> Draw("same");
            hRecoPt_ratio[icoll] = (TH1D*) hRecoPt[icoll] -> Clone(Form("hRecoPt_ratio%d",icoll));
        }
    }
    l1 -> Draw();

    cRecoPt -> cd(2);
    for(int icoll=1; icoll<5; icoll++){
        hRecoPt_ratio[icoll] -> Divide(hRecoPt[0]);
        if(icoll==1){ 
            hRecoPt_ratio[icoll] -> Draw();
            hRecoPt_ratio[icoll] -> SetYTitle("p_{T}^{PbPb}/p_{T}^{pp}");
        //    hRecoPt_ratio[icoll] -> SetTitleOffset(0.52, "Y");
        //    hRecoPt[icoll] -> SetTitleOffset(0.52, "Y");
        } else hRecoPt_ratio[icoll] -> Draw("same");
    }
    jumSun(0,1,200,1,2);
//
// reco/gen ratio
//
    TCanvas* crg = new TCanvas("crg", "", 1200, 300);
    makeMultiPanelCanvas(crg, 5, 1);
    TH1D* hrg[5];
    for(int icoll=0; icoll<5; icoll++){
        hrg[icoll]= (TH1D*) hRecoPt[icoll] -> Clone(Form("hrg%d",icoll));
       // hrg[icoll]= new TH1D(Form("hrg%d", icoll),"; p_{T} (GeV) ; p_{T}^{Reco}/p_{T}^{Gen}", 20, 0, 200);
    }
     
    for(int icoll=0; icoll<5; icoll++){
        crg -> cd(icoll+1);
        hrg[icoll] -> Divide(hGenPt[icoll]);
     //   hrg[icoll] -> Scale(1./hrg[icoll]->Integral());
        hrg[icoll] -> SetYTitle("p_{T}^{Reco}/p_{T}^{Gen}");
        hrg[icoll] -> SetAxisRange(0.7,1.8,"Y"); 
        hrg[icoll] -> Draw(); 
        jumSun(0,1,200,1,2);
    }
    crg -> cd(1);
    l1 -> Draw();
    crg -> cd(2);
    l2 -> Draw();
    double sigma[5]; 
    double cc[5]; 
    double ss[5]; 
    double nn[5]; 

    cc[0] =0.056762;
    ss[0] =0.808114;
    nn[0] =0.000244992;
    if(fixOpt==0) {
        cc[1] =0.056762;
        ss[1] =0.808114;
        nn[1] =9.6876;
        cc[2] =0.056762;
        ss[2] =0.808114;
        nn[2] =8.21968;
        cc[3] =0.056762;
        ss[3] =0.808114;
        nn[3] =7.02911;
        cc[4] =0.056762;
        ss[4] =0.808114;
        nn[4] =6.10214;
    } else if(fixOpt==1){
        cc[1] =0.0560882;
        ss[1] =1.47838;
        nn[1] =0.115188;
        cc[2] =0.0256674;
        ss[2] =1.40659;
        nn[2] =-0.0341018;
        cc[3] =0.00644361;
        ss[3] = 1.31446;
        nn[3] = -0.0721935;
        cc[4] =0.0170442;
        ss[4] = 1.22837;
        nn[4] = 0.0511498;
    }

    TCanvas* cSmear = new TCanvas("cSmear", "", 350, 900);
  //  makeMultiPanelCanvas(cSmear, 1, 3);
    cSmear -> Divide(1,3); 
    cSmear -> SetLeftMargin(0.5);

    TH1D* hSmear[5]; 
    TH1D* hRatio[5]; 
    TH1D* hRatioGen[5]; 
    for(int icoll=0; icoll<5; icoll++){    
        hSmear[icoll] = new TH1D(Form("hSmear%d",icoll), "; p_{T}^{Smeared} (GeV) ; Entries", 20, 0, 200);
    }

    TRandom3 rand(111);
    
    for(int icoll=0; icoll<5; icoll++){    
        cSmear -> cd(1);
        for(int i=0; i<10000; i++){
	  double pt = hGenPt[icoll] -> GetRandom();
	  sigma[icoll] = sqrt(cc[icoll]*cc[icoll] + ss[icoll]*ss[icoll]/pt + nn[icoll]*nn[icoll]/(pt*pt));
	  double factor = rand.Gaus(1,sigma[icoll]);
	  double newPt = pt*factor;
	  hSmear[icoll] -> Fill(newPt);
        }

        handsomeTH1(hSmear[icoll], icoll+1, 0.5);
        hSmear[icoll] -> Scale(1./10000);
        if(icoll==0) hSmear[icoll] -> Draw();
        else hSmear[icoll] -> Draw("same");
        
        cSmear -> cd(2);
        hRatioGen[icoll] = (TH1D*) hSmear[icoll] -> Clone(Form("hRatioGen%d",icoll));
        hRatioGen[icoll] -> Divide(hRecoPt[icoll]);
        hRatioGen[icoll] -> SetYTitle("p_{T}^{smeared}/p_{T}^{Gen}");
	//        hRatioGen[icoll] -> Scale(1./hRatioGen[icoll]->Integral());
      //  hRatioGen[icoll] -> SetTitleOffset(0.52, "Y");
        handsomeTH1(hRatioGen[icoll], icoll+1, 0.5);
        if(icoll==0) hRatioGen[icoll] -> Draw();
        else hRatioGen[icoll] -> Draw("same");
        jumSun(0,1,200,1,2);
        
        cSmear -> cd(3);
        hRatio[icoll] = (TH1D*) hSmear[icoll] -> Clone(Form("hRatio%d",icoll));
        hRatio[icoll] -> Divide(hRecoPt[icoll]);
        hRatio[icoll] -> SetYTitle("p_{T}^{smeared}/p_{T}^{Reco}");
      //  hRatio[icoll] -> SetTitleOffset(0.52, "Y");
        handsomeTH1(hRatio[icoll], icoll+1, 0.5);
        if(icoll==0) hRatio[icoll] -> Draw();
        else hRatio[icoll] -> Draw("same");
        jumSun(0,1,200,1,2);
        
    }
    cSmear -> cd(1);
    l1 -> Draw();
    l2 -> Draw();
//
// reco/smear ratio
//
    TCanvas* crs = new TCanvas("crs", "", 1200, 300);
    makeMultiPanelCanvas(crs, 5, 1);
    TH1D* hrs[5];//histogram reco/smear
    for(int icoll=0; icoll<5; icoll++){
        hrs[icoll]= (TH1D*) hRecoPt[icoll] -> Clone(Form("hrs%d",icoll));
    }
     
    for(int icoll=0; icoll<5; icoll++){
        crs -> cd(icoll+1);
        hrs[icoll] -> Divide(hSmear[icoll]);
        hrs[icoll] -> SetYTitle("p_{T}^{Reco}/p_{T}^{Smear}");
     //   hrs[icoll] -> SetTitleOffset(0.52, "Y");
        hrs[icoll] -> SetAxisRange(0.5,2.5,"Y"); 
        hrs[icoll] -> Draw(); 
        jumSun(0,1,200,1,2);
        
    }
    crs -> cd(1);
    l1 -> Draw();
    crs -> cd(2);
    l2 -> Draw();

    cSmear -> SaveAs(Form("smeared_fixOpt%d.pdf",fixOpt));
}

