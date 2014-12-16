#include "../HiForestAnalysis/hiForest.h"
#include "../gammaJetAnalysis/CutAndBinCollection2012.h"
#include <TCut.h>
#include <TTree.h>
#include <TH1D.h>
#include <TH1.h>
#include <TStyle.h>
#include <iostream>
#include <TLegend.h>
#include <TFile.h>

void lowPtVariables(int jetLow=30, int jetHigh=40, int phoLow=80, int phoHigh=9999){
    TH1::SetDefaultSumw2();
    gStyle -> SetOptStat(0);
    
    TLegend* l1 = new TLegend(0.193674,0.5364219,0.9915464,0.7877331,NULL,"brNDC");
    easyLeg(l1, Form("%d < p_{T}^{Jet} < %d  ,  %d < p_{T}^{#gamma} < %d", jetLow, jetHigh, phoLow, phoHigh));

    TCut ptCut = Form("jtpt > %d && jtpt < %d && photonEt > %d && photonEt < %d",jetLow, jetHigh, phoLow, phoHigh);
    //TCut ptCut = Form("jtpt > %d && jtpt < %d", jetLow, jetHigh);
    TCut caloIso = "ecalIso < 4.2  &&  hcalIso < 2.2  &&  trackIso < 2 && hovere<0.1";
    TCut MCCut = "genIso<5 && abs(genMomId)<=22";
    TCut jetCut = "abs(jteta) < 1.6 && acos(cos(photonPhi-jtphi)) > 7.*3.141592/8.0"; //dphi> 0.5
    TCut evtCut = ptCut && caloIso && jetCut;
 
    multiTreeUtil* fullJetMC = new multiTreeUtil();
    fullJetMC -> addFile("/home/jazzitup/analysis/photonJetAnalysis2013/photonSkimProducer/yskimmedFiles/yskim_PA2013_pyquen_allQCDPhoton30to50_forestv85.root", "fullJet", "",56669./50385.);
    fullJetMC -> addFile("/home/jazzitup/analysis/photonJetAnalysis2013/photonSkimProducer/yskimmedFiles/yskim_PA2013_pyquen_allQCDPhoton50to80_forestv85.root", "fullJet", "",41906./114136.);
    fullJetMC -> addFile("/home/jazzitup/analysis/photonJetAnalysis2013/photonSkimProducer/yskimmedFiles/yskim_PA2013_pyquen_allQCDPhoton80to120_forestv85.root", "fullJet", "",12044./103562.);
    fullJetMC -> addFile("/home/jazzitup/analysis/photonJetAnalysis2013/photonSkimProducer/yskimmedFiles/yskim_PA2013_pyquen_allQCDPhoton120to9999_forestv85.root", "fullJet","", 4481./151511.);
    fullJetMC -> AddFriend("tgj");
    fullJetMC -> AddFriend("yPhotonTree");
   /* 
    TCanvas* ctest=  new TCanvas("ctest", "", 500,500);
    TH1D* hptHat = new TH1D("hptHat",";pt hat;Entries",200,0,200);
    fullJetMC->Draw3( hptHat, "yPhotonTree.ptHat"," photonEt>40 && genPhotonEt> 30 && abs(genMomId)<=22",""); 
*/
    multiTreeUtil* fullJetDATA = new multiTreeUtil();
    fullJetDATA -> addFile("/home/jazzitup/analysis/photonJetAnalysis2013/photonSkimProducer/yskimmedFiles/yskim_pA_photonSkimForest_v85_HLT_PAPhoton30_NoCaloIdVL_v1_highPtPhoton40.root", "fullJet", evtCut, 1);
    fullJetDATA -> AddFriend("tgj");   

    TH1D* htrackMax[2];//data or MC
    TH1D* htrackSum[2];
    TH1D* hphotonMax[2];
    TH1D* hphotonSum[2];
    TH1D* hneutralMax[2];
    TH1D* hneutralSum[2];

    for(int itype=0; itype<2; itype++){
        //=============initialize the histograms=============
        htrackMax[itype] = new TH1D(Form("trackMax_%d", itype), ";trackMax/jetpt ; Normalized Entires ", 15, 0, 2.5);
        htrackSum[itype] = new TH1D(Form("trackSum_%d", itype), ";trackSum/jetpt ; Normalized Entires ", 15, 0, 2.5);
        hphotonMax[itype] = new TH1D(Form("photonMax_%d", itype), ";photonMax/jetpt ; Normalized Entries ", 15, 0, 2.5); 
        hphotonSum[itype] = new TH1D(Form("photonSum_%d", itype), ";photonSum/jetpt ; Normalized Entries ", 15, 0, 2.5); 
        hneutralMax[itype] = new TH1D(Form("neutralMax_%d", itype), ";neutralMax/jetpt ; Normalized Entries ", 15, 0, 2.5); 
        hneutralSum[itype] = new TH1D(Form("neutralSum_%d", itype), ";neutralSum/jetpt ; Normalized Entries ", 15, 0, 2.5); 
    }   
/*
    for(int itype=0; itype<2; itype++){
        //=============initialize the histograms=============
        htrackMax[itype] = new TH1D(Form("trackMax_%d", itype), ";trackMax ; Normalized Entires ", 25, 0, 80);
        htrackSum[itype] = new TH1D(Form("trackSum_%d", itype), ";trackSum ; Normalized Entires ", 25, 0, 80);
        hphotonMax[itype] = new TH1D(Form("photonMax_%d", itype), ";photonMax ; Normalized Entries ", 20, 0, 60); 
        hphotonSum[itype] = new TH1D(Form("photonSum_%d", itype), ";photonSum ; Normalized Entries ", 20, 0, 60); 
        hneutralMax[itype] = new TH1D(Form("neutralMax_%d", itype), ";neutralMax ; Normalized Entries ", 20, 0, 30); 
        hneutralSum[itype] = new TH1D(Form("neutralSum_%d", itype), ";neutralSum ; Normalized Entries ", 20, 0, 30); 
    }   
*/
    for(int itype=0; itype<2; itype++){
        if (itype==0) {
            //fullJetDATA -> Draw("trackMax/jtpt >> trackMax_0", evtCut, "");
            fullJetDATA -> Draw2(htrackMax[itype], "trackMax/jtpt", evtCut, "");
            fullJetDATA -> Draw2(htrackSum[itype], "trackSum/jtpt",  evtCut, "");
            fullJetDATA -> Draw2(hphotonMax[itype], "photonMax/jtpt", evtCut, "");
            fullJetDATA -> Draw2(hphotonSum[itype], "photonSum/jtpt", evtCut, "");
            fullJetDATA -> Draw2(hneutralMax[itype], "neutralMax/jtpt", evtCut, "");
            fullJetDATA -> Draw2(hneutralSum[itype], "neutralSum/jtpt", evtCut, "");
        } else {
            fullJetMC -> Draw2(htrackMax[itype], "trackMax/jtpt", evtCut&&MCCut, "");
            fullJetMC -> Draw2(htrackSum[itype], "trackSum/jtpt", evtCut&&MCCut, "");
            fullJetMC -> Draw2(hphotonMax[itype], "photonMax/jtpt", evtCut&&MCCut, "");
            fullJetMC -> Draw2(hphotonSum[itype], "photonSum/jtpt", evtCut&&MCCut, "");
            fullJetMC -> Draw2(hneutralMax[itype], "neutralMax/jtpt", evtCut&&MCCut, "");
            fullJetMC -> Draw2(hneutralSum[itype], "neutralSum/jtpt", evtCut&&MCCut, "");
        }   

    } 

    for(int itype=0; itype<2; itype++){
        hphotonMax[itype]->SetTitleOffset(1.19, "Y");
        hphotonSum[itype]->SetTitleOffset(1.19, "Y");
        hneutralMax[itype]->SetTitleOffset(1.19, "Y");
        hneutralSum[itype]->SetTitleOffset(1.19, "Y");
        htrackMax[itype]->SetTitleOffset(1.19, "Y");
        htrackSum[itype]->SetTitleOffset(1.19, "Y");
        
        hphotonMax[itype]->SetTitleSize(0.065, "X");
        hphotonSum[itype]->SetTitleSize(0.065, "X");
        hneutralMax[itype]->SetTitleSize(0.065, "X");
        hneutralSum[itype]->SetTitleSize(0.065, "X");
        htrackMax[itype]->SetTitleSize(0.065, "X");
        htrackSum[itype]->SetTitleSize(0.065, "X");
        

        hphotonMax[itype]->SetTitleSize(0.05, "Y");
        hphotonSum[itype]->SetTitleSize(0.05, "Y");
        hneutralMax[itype]->SetTitleSize(0.05, "Y");
        hneutralSum[itype]->SetTitleSize(0.05, "Y");
        htrackMax[itype]->SetTitleSize(0.05, "Y");
        htrackSum[itype]->SetTitleSize(0.05, "Y");
        
        hphotonMax[itype]->SetTitleOffset(0.85, "X");
        hphotonSum[itype]->SetTitleOffset(0.85, "X");
        hneutralMax[itype]->SetTitleOffset(0.85, "X");
        hneutralSum[itype]->SetTitleOffset(0.85, "X");
        htrackMax[itype]->SetTitleOffset(0.85, "X");
        htrackSum[itype]->SetTitleOffset(0.85, "X");
        
        hphotonMax[itype]->SetTitleOffset(0.85, "Y");
        hphotonSum[itype]->SetTitleOffset(0.85, "Y");
        hneutralMax[itype]->SetTitleOffset(0.85, "Y");
        hneutralSum[itype]->SetTitleOffset(0.85, "Y");
        htrackMax[itype]->SetTitleOffset(0.85, "Y");
        htrackSum[itype]->SetTitleOffset(0.85, "Y");
        


        hphotonMax[itype]->GetXaxis()->CenterTitle();
        hphotonSum[itype]->GetXaxis()->CenterTitle();
        hneutralMax[itype]->GetXaxis()->CenterTitle();
        hneutralSum[itype]->GetXaxis()->CenterTitle();
        htrackMax[itype]->GetXaxis()->CenterTitle();
        htrackSum[itype]->GetXaxis()->CenterTitle();
        
        if(itype==0){
            hphotonMax[itype]->SetLineColor(2);
            hphotonSum[itype]->SetLineColor(2);
            hneutralMax[itype]->SetLineColor(2);
            hneutralSum[itype]->SetLineColor(2);
            htrackMax[itype]->SetLineColor(2);
            htrackSum[itype]->SetLineColor(2);
        }

        htrackMax[itype] ->Scale(1./htrackMax[itype]->Integral("width"));
        htrackSum[itype] -> Scale(1./htrackSum[itype]->Integral("width"));
        hphotonMax[itype] -> Scale(1./hphotonMax[itype]->Integral("width"));
        hphotonSum[itype] -> Scale(1./hphotonSum[itype]->Integral("width"));
        hneutralMax[itype] -> Scale(1./hneutralMax[itype]->Integral("width"));
        hneutralSum[itype] -> Scale(1./hneutralSum[itype]->Integral("width"));
    }

    TLegend* l2 = new TLegend(0.5103716,0.4935144,0.832632,0.6967312,NULL,"brNDC");
    l2 -> AddEntry(htrackMax[0], "DATA");
    l2 -> AddEntry(htrackSum[1], "MC");
    l2 -> SetFillStyle(0);
    l2 -> SetBorderSize(0);

    TCanvas* c1 = new TCanvas("c1", "c1", 900, 600);
    c1 -> Divide(3,2);
/*    
    TCanvas* c2 = new TCanvas("c2", "c2", 800, 400);
    c2 -> Divide(2,1);
    
    TCanvas* c3 = new TCanvas("c3", "c3", 800, 400);
    c3 -> Divide(2,1);
*/
    c1 -> cd(1);
    htrackMax[0] -> Draw("e");
    htrackMax[1] -> Draw("same hist");
    l2 -> Draw();
    
    c1 -> cd(4);
    htrackSum[0] -> Draw("e");
    htrackSum[1] -> Draw("same hist");
   // l1 -> Draw();

    c1 -> cd(2);
    hphotonMax[0] -> Draw("e");
    hphotonMax[1] -> Draw("same hist");
    l1 -> Draw();
    
    c1 -> cd(5);
    hphotonSum[0] -> Draw("e");
    hphotonSum[1] -> Draw("same hist");
   // l1 -> Draw();
    
    c1 -> cd(3);
    hneutralMax[0] -> Draw("e");
    hneutralMax[1] -> Draw("same hist");
//    l2 -> Draw();
    
    c1 -> cd(6);
    hneutralSum[0] -> Draw("e");
    hneutralSum[1] -> Draw("same hist");
 //   l1 -> Draw();

    c1 -> SaveAs(Form("variables_jet%dto%d_photon%dto%d.gif", jetLow, jetHigh, phoLow, phoHigh));    
   // c2 -> SaveAs(Form("photon_jet%dto%d_photon%dto%d.gif", jetLow, jetHigh, phoLow, phoHigh));    
   // c3 -> SaveAs(Form("neutral_jet%dto%d_photon%dto%d.gif", jetLow, jetHigh, phoLow, phoHigh));    
    
}

