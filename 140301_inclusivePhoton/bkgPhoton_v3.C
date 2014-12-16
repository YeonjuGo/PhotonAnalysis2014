// Author : Yeonju Go 
// modified by yeonju according to the Yetkin's comments
// 2014.03.05

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
#include <TCanvas.h>
#include <TString.h>
#include <TF1.h>
#include <TGraphAsymmErrors.h>
#include <TLegend.h>
#include <TCut.h>
#include <TPad.h>

void bkgPhoton_v3(){

    TH1::SetDefaultSumw2();
    TFile* dataF = new TFile("/home/goyeonju/recent2013/jetAnalysis/forestFiles/pA/pA_photonSkimForest_v85.root");
    TTree* dataPhoTree = (TTree*) dataF -> Get("multiPhotonAnalyzer/photon");
    TTree* dataPFTree = (TTree*) dataF -> Get("pfcandAnalyzer/pfTree");
    TTree* dataSkimTree = (TTree*) dataF -> Get("skimanalysis/HltTree");
    TTree* dataHltTree = (TTree*) dataF -> Get("hltanalysis/HltTree");
    TTree* dataHiTree = (TTree*) dataF -> Get("hiEvtAnalyzer/HiTree");
    dataPhoTree -> AddFriend(dataSkimTree);
    dataPFTree -> AddFriend(dataSkimTree);
    dataPhoTree -> AddFriend(dataHltTree);
    dataPFTree -> AddFriend(dataHltTree);
    dataPhoTree -> AddFriend(dataHiTree);
    dataPFTree -> AddFriend(dataHiTree);

//    TFile* MCF = new TFile("/mnt/hadoop/cms/store/user/dgulhan/Pbp/HP05/prod24/Hijing_Pythia_pt15/HiForest_v84_merged02/pt15_HP05_prod24_v84_merged_forest_0.root");
    TFile* MCF = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/forest/pA/pt15_HP05_prod24_v84_merged_forest_0.root");
    //TFile* MCF = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/forest/pA/pt30_HP05_prod24_v84_merged_forest_0.root");
    TTree* MCPhoTree = (TTree*) MCF -> Get("multiPhotonAnalyzer/photon");
    TTree* MCPFTree = (TTree*) MCF -> Get("pfcandAnalyzer/pfTree");
    TTree* MCSkimTree = (TTree*) MCF -> Get("skimanalysis/HltTree");
    TTree* MCHltTree = (TTree*) MCF -> Get("hltanalysis/HltTree");
    TTree* MCHiTree = (TTree*) MCF -> Get("hiEvtAnalyzer/HiTree");
    MCPhoTree -> AddFriend(MCSkimTree);
    MCPFTree -> AddFriend(MCSkimTree);
    MCPhoTree -> AddFriend(MCHltTree);
    MCPFTree -> AddFriend(MCHltTree);
    MCPhoTree -> AddFriend(MCHiTree);
    MCPFTree -> AddFriend(MCHiTree);
//
//======================= trigger prescale test =================================
//
/*
    TCanvas* cpre = new TCanvas("cpre", "", 400,800);
    cpre -> Clear();
    
    cpre -> Divide(1,2);
    cpre -> cd(1);
    TH1D* hpt0 = new TH1D("hpt0", ";p_{T}^{#gamma} (GeV);Entries", 20, 0, 200);
    TH1D* hpt1 = (TH1D*) hpt0 -> Clone("hpt1");
    TH1D* hpt2 = (TH1D*) hpt0 -> Clone("hpt2");
    TH1D* hpt3 = (TH1D*) hpt0 -> Clone("hpt3");
    
    dataPhoTree -> Draw("pt >> hpt0", "27.2*(HLT_PAPhoton10_NoCaloIdVL_v1==1)");
    dataPhoTree -> Draw("pt >> hpt1", "1.3*(HLT_PAPhoton15_NoCaloIdVL_v1==1)");
    hpt0 -> Draw("hist");
    //cpre -> cd(2);
    hpt1 -> Draw("same p");
*/
    // removed h/e 
    //TCut runCut ="1";
    //TCut ptHatCut = "ptHat>30";
    TCut runCut = "HiTree.run >= 210676 && HiTree.run <= 211256";
    //TCut basicCut = "pt>0 && pt<100 && sigmaIetaIeta>0.011";
    TCut basicCut = "pt>0 && pt<100 && sigmaIetaIeta>0.011 && hadronicOverEm<0.2";
    //TCut basicCut = "pt>0 && pt<100 && hadronicOverEm<0.2";
    TCut EtaCut = "abs(eta) < 0.8";
    TCut pfCut = "abs(pfEta) < 0.8 && pfId==4";
  
    //=================== divide procedure ===================
    //TCut triggerCut = "1";
    TCut triggerCut = "HLT_PAPhoton10_NoCaloIdVL_v1==1";
    //TCut eventCut = "1";
    //TCut eventCutMC = "1";
    //TCut eventCut = "pHBHENoiseFilter > 0 && pprimaryvertexFilter > 0 && pPAcollisionEventSelectionPA>0 && pVertexFilterCutGplus>0 && abs(vz)<15";
    TCut eventCut = "pHBHENoiseFilter > 0 && pprimaryvertexFilter > 0 && pPAcollisionEventSelectionPA>0 && abs(vz)<15";
    TCut eventCutMC = "pHBHENoiseFilter > 0 && pprimaryvertexFilter > 0 && pPAcollisionEventSelectionPA>0 && abs(vz)<15";
    //TCut spikeCut = "1";
    TCut spikeCut = "(1-(eRight+eLeft+eTop+eBottom)/eMax)<=0.9 && abs(seedTime)<=3 && sigmaIphiIphi>=0.002";
    //TCut spikeCut = "(1-(eRight+eLeft+eTop+eBottom)/eMax)<=0.9 && abs(seedTime)<=3 && sigmaIetaIeta>=0.002 && sigmaIphiIphi>=0.002";
    TLegend* ll = new TLegend(0.3,0.68, 0.85, 0.85);
    //ll -> SetHeader("|#eta|<0.8 && no trigger weight");
    //ll -> SetHeader("|#eta|<0.8, trigger&event selection");
    ll -> SetHeader("|#eta|<0.8");
    //ll -> SetHeader("|#eta|<0.8, w/o h/e cut");
   
    //========================================================
    TCut totalCut = triggerCut && eventCut && EtaCut && basicCut && spikeCut && runCut;
    TCut totalCutMC = triggerCut && eventCutMC && EtaCut && basicCut && spikeCut;
    TCut pftotalCut = triggerCut && eventCut && pfCut && runCut;
    TCut pftotalCutMC = triggerCut && eventCutMC && pfCut;
    
    const char* tempTitle = totalCut.GetTitle();
    const char* tempTitleMC = totalCutMC.GetTitle();
    const char* pftempTitle = pftotalCut.GetTitle();
    const char* pftempTitleMC = pftotalCutMC.GetTitle();
    TString totalCutTitle = tempTitle;
    TString totalCutTitleMC = tempTitleMC;
    TString pftotalCutTitle = pftempTitle;
    TString pftotalCutTitleMC = pftempTitleMC;
    //cout << totalCutTitle << endl;
    //cout << pftotalCutTitle << endl;
    double ptbin[] = {0,2,4,6,8,10,12,14,16,18,20,30,60,100};
    const int nPtBin = 13;
    TH1D* dataPhoH = new TH1D("dataPhoH", "photon;p_{T}^{#gamma} (GeV);d#sigma/dp_{T} (mb/GeV)",nPtBin, ptbin);
    TH1D* dataPFH = new TH1D("dataPFH", "PF photon;p_{T}^{#gamma} (GeV);d#sigma/dp_{T} (mb/GeV)", nPtBin, ptbin);
    TH1D* MCPhoH = (TH1D*) dataPhoH -> Clone("MCPhoH");
    TH1D* MCPFH = (TH1D*) dataPFH -> Clone("MCPFH");

    //dataPhoTree -> Draw("pt >> dataPhoH", "HLT_PAPhoton10_NoCaloIdVL_v1_Prescl*"+totalCutTitle);
    dataPhoTree -> Draw("pt >> dataPhoH", totalCutTitle); //no weight
    dataPFTree -> Draw("pfPt >> dataPFH", pftotalCutTitle);

    //MCPhoTree -> Draw("pt >> MCPhoH", "HLT_PAPhoton10_NoCaloIdVL_v1_Prescl*"+totalCutTitleMC);
    MCPhoTree -> Draw("pt >> MCPhoH", totalCutTitleMC); //no weight
    MCPFTree -> Draw("pfPt >> MCPFH", pftotalCutTitleMC);

    //double pPbLumi =3.09e7; //3.05e7 mb-1 = 30.9 nb-1 
    double pPbLumi =5.8e5; //effective lumi 5.8e5 mb-1 = 580.252 ub-1 recorded lumi = 15.784 nb-1

    dataPhoH -> Scale(1., "width");
    dataPhoH -> Scale(1./pPbLumi);
    //dataPhoH -> Scale(1./dataPhoTree->GetEntries(triggerCut && eventCutMC && runCut));
    //dataPhoH -> Scale(27.0); //prescl
    dataPhoH -> SetMarkerStyle(20); 
    dataPhoH -> SetMarkerColor(2); 
    dataPFH -> Scale(1., "width");
    //dataPFH -> Scale(1./dataPFTree->GetEntries(triggerCut && eventCutMC && runCut));
    dataPFH -> Scale(1./pPbLumi);
    //dataPFH -> Scale(27.0); //prescl
    dataPFH -> SetMarkerStyle(20); 
    dataPFH -> SetMarkerColor(2); 
    
    //cout << "MCPhoTree->GetEntries(totalCut) : " << MCPhoTree->GetEntries(totalCutMC) << endl;
    //cout << "MCPFTree->GetEntries(pftotalCut) : " << MCPFTree->GetEntries(pftotalCutMC) << endl;
    MCPhoH -> Scale(1., "width");
    // MCPhoH -> Scale(5.335e-01/100.); 
   // MCPhoH -> Scale(3.378E-02/MCPhoTree->GetEntries(triggerCut && eventCutMC));
    MCPhoH -> Scale(5.335e-01/MCPhoTree->GetEntries(triggerCut && eventCutMC));
    //MCPhoH -> Scale(1./MCPhoTree->GetEntries(triggerCut && eventCutMC));
    // MCPhoH -> Scale(5.335e-01/MCPhoH->GetEntries());
    MCPFH -> Scale(1., "width");
    // MCPFH -> Scale(5.335e-01/100.);
    //MCPFH -> Scale(1./MCPFTree->GetEntries(triggerCut && eventCutMC));
    //MCPFH -> Scale(3.378E-02/MCPFTree->GetEntries(triggerCut && eventCutMC));
    MCPFH -> Scale(5.335e-01/MCPFTree->GetEntries(triggerCut && eventCutMC));
    // MCPFH -> Scale(5.335e-01/MCPFH->GetEntries());
    
    TH1D* PhoRatio = (TH1D*) dataPhoH -> Clone("PhoRatio");
    PhoRatio -> SetTitle(";p_{T}^{#gamma} (GeV);data/MC ratio"); 
    TH1D* PFRatio = (TH1D*) dataPFH -> Clone("PFRatio");
    PFRatio -> SetTitle(";p_{T}^{#gamma} (GeV);data/MC ratio"); 
    PhoRatio -> Divide(dataPhoH, MCPhoH);
    PFRatio -> Divide(dataPFH, MCPFH);

    ll -> AddEntry(dataPhoH, "data");
    ll -> AddEntry(MCPhoH, "MC");

    TCanvas* cc1 = new TCanvas("cc1", "cc1", 400, 800);
    cc1 -> Divide(1,2);
    cc1 -> cd(1);
    MCPhoH -> Draw("hist");
    dataPhoH -> Draw("p same");
    //cc1_1 -> Setlogy();
    ll -> Draw();

    cc1 -> cd(2);
    PhoRatio -> SetMarkerColor(1); 
    PhoRatio -> Draw("p");

    TCanvas* c2 = new TCanvas("c2", "c2", 400, 800);
    c2 -> Divide(1,2);
    c2 -> cd(1);
    MCPFH -> Draw("hist");
    dataPFH -> Draw("p same");
    //  c2_1 -> Setlogy();
    ll -> Draw();
    
    c2 -> cd(2);
    PFRatio -> SetMarkerColor(1); 
    PFRatio -> Draw("p");
}


