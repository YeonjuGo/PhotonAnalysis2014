// Author : Yeonju Go 
// checking on cross section calculation of Jet sample MCs
// add pt15, pt30, pt50 MC files
// 2014.03.17 Mon.

#include "../HiForestAnalysis/hiForest.h"
#include "../gammaJetAnalysis/CutAndBinCollection2012.h"
#include <TROOT.h>
#include <TStyle.h>
#include <TH1D.h>
#include <TH1F.h>
#include <TTree.h>
#include <TBranch.h>
#include <TFile.h>
#include <TChain.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <TCanvas.h>
#include <TString.h>
#include <TF1.h>
#include <TGraphAsymmErrors.h>
#include <TLegend.h>
#include <TCut.h>
#include <TPad.h>

void CScal(){

    TH1::SetDefaultSumw2();
 
    const int nfile = 5;
    TFile* MCF[nfile]; 
    TTree* MCPhoTree[nfile];
    TTree* MCPFTree[nfile]; 
    TTree* MCSkimTree[nfile]; 
    TTree* MCHltTree[nfile];
    TTree* MCHiTree[nfile];
    for(int i=0; i<nfile;i++){
        if(i==0) MCF[i] = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/forest/pA/pt15_HP05_prod24_v84_merged_forest_0.root");
        else if(i==1) MCF[i] = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/forest/pA/pt30_HP05_prod24_v84_merged_forest_0.root");
        else if(i==2) MCF[i] = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/forest/pA/pt50_HP05_prod24_v84_merged_forest_0.root");
        else if(i==3) MCF[i] = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/forest/pA/pt80_HP05_prod24_v84_merged_forest_0.root");
        else if(i==4) MCF[i] = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/forest/pA/pt120_HP05_prod24_v84_merged_forest_0.root");
        MCPhoTree[i] = (TTree*) MCF[i] -> Get("multiPhotonAnalyzer/photon");
        MCPFTree[i] = (TTree*) MCF[i] -> Get("pfcandAnalyzer/pfTree");
        MCSkimTree[i] = (TTree*) MCF[i] -> Get("skimanalysis/HltTree");
        MCHltTree[i] = (TTree*) MCF[i] -> Get("hltanalysis/HltTree");
        MCHiTree[i] = (TTree*) MCF[i] -> Get("hiEvtAnalyzer/HiTree");
        MCPhoTree[i] -> AddFriend(MCSkimTree[i]);
        MCPFTree[i] -> AddFriend(MCSkimTree[i]);
        MCPhoTree[i] -> AddFriend(MCHltTree[i]);
        MCPFTree[i] -> AddFriend(MCHltTree[i]);
        MCPhoTree[i] -> AddFriend(MCHiTree[i]);
        MCPFTree[i] -> AddFriend(MCHiTree[i]);
    }
//
//======================= ptHat Cut : combining the different ptHat MC files  =================================
//

    TCanvas* cpre = new TCanvas("cpre", "", 400,800);
    cpre -> Clear();
    
    cpre -> Divide(1,2);
    cpre -> cd(1);
    TH1D* hpt0 = new TH1D("hpt0", ";p_{T}Hat (GeV);Normalized Cross Section(mb)", 40, 0, 200);
    TH1D* hpt1 = (TH1D*) hpt0 -> Clone("hpt1");
    TH1D* hpt2 = (TH1D*) hpt0 -> Clone("hpt2");
    TH1D* hpt3 = (TH1D*) hpt0 -> Clone("hpt3");
    TH1D* hpt4 = (TH1D*) hpt0 -> Clone("hpt4");
   // TH1D* hpt5 = (TH1D*) hpt0 -> Clone("hpt5");

    MCPhoTree[0] -> Draw("ptHat >> hpt0", "(5.335e-01/172400.0)*(1)");
    MCPhoTree[1] -> Draw("ptHat >> hpt1", "(3.378e-02/403200.0)*(1)");
    MCPhoTree[2] -> Draw("ptHat >> hpt2", "(3.778E-03/362400.0)*(1)");
    MCPhoTree[3] -> Draw("ptHat >> hpt3", "(4.412e-04/358000.0)*(1)");
    MCPhoTree[4] -> Draw("ptHat >> hpt4", "(6.147E-05/306400.0)*(1)");
  
    hpt0 -> Draw();
    hpt1 -> Draw("same");
    hpt2 -> Draw("same");
    hpt3 -> Draw("same");
    hpt4 -> Draw("same");
    hpt1 -> SetMarkerColor(2);
    hpt2 -> SetMarkerColor(3);
    hpt3 -> SetMarkerColor(4);
    hpt4 -> SetMarkerColor(5);

    TLegend* l1 = new TLegend(0.6, 0.6, 0.85, 0.85);
    l1 -> AddEntry(hpt0, "ptHat15");
    l1 -> AddEntry(hpt1, "ptHat30");
    l1 -> AddEntry(hpt2, "ptHat50");
    l1 -> AddEntry(hpt3, "ptHat80");
    l1 -> AddEntry(hpt4, "ptHat120");
    l1 -> Draw();
}

