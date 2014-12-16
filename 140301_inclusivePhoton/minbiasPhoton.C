// Author : Yeonju Go
// 2014.03.04

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

void minbiasPhoton(){
    TH1::SetDefaultSumw2();
    TFile* dataF = new TFile("/home/goyeonju/recent2013/jetAnalysis/forestFiles/pA/MergedForest_withCones_MinBiasUPC_v71_1.root");
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
    TFile* MCF = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/forest/pA/H02_merged_hiforest_v68_prod12_yj_minbiasjetMC.root");
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


    TCut basicCut = "pt>=0 && pt<40 && hadronicOverEm<0.2";
    TCut EtaCut = "abs(eta) < 0.8";
    TCut pfCut = "abs(pfEta) < 0.8 && pfId==4 && pfPt>=0 && pfPt<40";
    // because of min-bias event.
    
    //=================== divide procedure ===================
    TCut triggerCut = "1";
    //TCut triggerCut = "HLT_PAZeroBiasPixel_SingleTrack_v1==1";
    TCut eventCut = "1";
    TCut eventCutMC = "1";
    //TCut eventCut = "pHBHENoiseFilter > 0 && pprimaryvertexFilter > 0 && pPAcollisionEventSelectionPA>0 && pVertexFilterCutGplus>0 && abs(vz)<15"; 
    //TCut eventCutMC = "pHBHENoiseFilter > 0 && pprimaryvertexFilter > 0 && pPAcollisionEventSelectionPA>0 && abs(vz)<15"; 
    TCut spikeCut = "1";
    //TCut spikeCut = "(1-(eRight+eLeft+eTop+eBottom)/eMax)<=0.9 && abs(seedTime)<=3 && sigmaIetaIeta>=0.002 && sigmaIphiIphi>=0.002";

    TLegend* ll = new TLegend(0.3,0.68, 0.85, 0.85);
    ll -> SetHeader("MinBias,|#eta|<0.8,trigger selection");
    //ll -> SetHeader("MinBias,|#eta|<0.8, trigger&event selection");
    //ll -> SetHeader("MinBias,|#eta|<0.8, total selection");
    //=======================================================
    
    TCut totalCut = triggerCut && eventCut && EtaCut && basicCut && spikeCut;
    TCut totalCutMC = triggerCut && eventCutMC && EtaCut && basicCut && spikeCut;
    TCut pftotalCut = triggerCut && eventCut && pfCut;
    TCut pftotalCutMC = triggerCut && eventCutMC && pfCut;
    
    const char* tempTitle = totalCut.GetTitle();
    const char* tempTitleMC = totalCutMC.GetTitle();
    const char* pftempTitle = pftotalCut.GetTitle();
    const char* pftempTitleMC = pftotalCutMC.GetTitle();
    TString totalCutTitle = tempTitle;
    TString pftotalCutTitle = pftempTitle;
    TString totalCutTitleMC = tempTitleMC;
    TString pftotalCutTitleMC = pftempTitleMC;
   // cout << totalCutTitle << endl;
   // cout << pftotalCutTitle << endl;

    TH1D* dataPhoH = new TH1D("dataPhoH", "photon;p_{T}^{#gamma} (GeV);d#sigma/dp_{T} (mb/GeV)", 8, 0, 40);
    TH1D* dataPFH = new TH1D("dataPFH", "PF photon;p_{T}^{#gamma} (GeV);d#sigma/dp_{T} (mb/GeV)", 8, 0, 40);
    TH1D* MCPhoH = (TH1D*) dataPhoH -> Clone("MCPhoH");
    TH1D* MCPFH = (TH1D*) dataPFH -> Clone("MCPFH");

    dataPhoTree -> Draw("pt >> dataPhoH", totalCutTitle);
    dataPFTree -> Draw("pfPt >> dataPFH", pftotalCutTitle);
    int dataPhoEntries = dataPhoTree -> GetEntries(totalCutTitle);
    int dataPFEntries = dataPFTree -> GetEntries(pftotalCutTitle);
    MCPhoTree -> Draw("pt >> MCPhoH", totalCutTitleMC);
    MCPFTree -> Draw("pfPt >> MCPFH", pftotalCutTitleMC);
    int MCPhoEntries = MCPhoTree -> GetEntries(totalCutTitleMC);
    int MCPFEntries = MCPFTree -> GetEntries(pftotalCutTitleMC);
   
    //double pPbLumi =3.05e-36; //30.4 nb-1

    dataPhoH -> Scale(1., "width");
    dataPhoH -> Scale(1./dataPhoEntries);
    dataPhoH -> SetMarkerStyle(20); 
    dataPhoH -> SetMarkerColor(2); 
    dataPFH -> Scale(1., "width");
    dataPFH -> Scale(1./dataPFEntries);
    dataPFH -> SetMarkerStyle(20); 
    dataPFH -> SetMarkerColor(2); 
    
    MCPhoH -> Scale(1., "width");
    MCPhoH -> Scale(1./MCPhoEntries);
    MCPFH -> Scale(1., "width");
    MCPFH -> Scale(1./MCPFEntries);

    ll -> AddEntry(dataPhoH, "data");
    ll -> AddEntry(MCPhoH, "MC");

    TH1D* PhoRatio = (TH1D*) dataPhoH -> Clone("PhoRatio");
    PhoRatio -> SetTitle(";p_{T}^{#gamma};data/MC ratio"); 
    TH1D* PFRatio = (TH1D*) dataPFH -> Clone("PFRatio");
    PFRatio -> SetTitle(";p_{T}^{#gamma};data/MC ratio"); 
    
    PhoRatio -> Divide(dataPhoH, MCPhoH);
    PFRatio -> Divide(dataPFH, MCPFH);
    TCanvas* can1 = new TCanvas("can1", "can1", 400, 800);
    can1 -> Divide(1,2);
    can1 -> cd(1);
    dataPhoH -> Draw("p");
  //  MCPhoH -> Draw();
    MCPhoH -> Draw("same hist");
        ll -> Draw();
    
    can1 -> cd(2);
    PhoRatio -> SetMarkerColor(1); 
    PhoRatio -> Draw("p");

    TCanvas* can2 = new TCanvas("can2", "can2", 400, 800);
    can2 -> Divide(1,2);
    can2 -> cd(1);
    dataPFH -> Draw("p");
   // MCPFH -> Draw();
    MCPFH -> Draw("same hist");
        ll -> Draw();
    can2 -> cd(2);
    PFRatio -> SetMarkerColor(1); 
    PFRatio -> Draw("p");
}


