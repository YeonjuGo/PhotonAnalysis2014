// Author : Yeonju Go
// modified according to the Yetkin's comments.
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

void minbiasPhoton_v3(){
	cout << "aaa" << endl;
    TH1::SetDefaultSumw2();
    //TFile* dataF = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/forest/pA/merged_hiForest_pPb_data_20140312_YJ.root");
    TFile* dataF = new TFile("/home/goyeonju/recent2013/jetAnalysis/forestFiles/pA/MergedForest_withCones_MinBiasUPC_v71_1.root");
    //   TFile* dataF = new TFile("/home/goyeonju/recent2013/jetAnalysis/forestFiles/pA/MergedForest_withCones_MinBiasUPC_v71_1.root");
    //TFile* dataF = new TFile("root://xrootd.ba.infn.it//store/group/phys_heavyions/yjlee/pPb2013/promptReco/PA2013_HiForest_PromptReco_KrisztianMB_JSonPPb_forestv84.root");
    //TFile* dataF = new TFile("root://eoscms//eos/cms/store/group/phys_heavyions/yjlee/pPb2013/promptReco/PA2013_HiForest_PromptReco_KrisztianMB_JSonPPb_forestv84.root");
  //  TFile* dataF = new TFile("/tmp/ygo/PA2013_HiForest_PromptReco_KrisztianMB_JSonPPb_forestv84.root");
    //TFile* dataF = TFile::Open("root://eoscms//eos/cms/store/group/phys_heavyions/yjlee/pPb2013/promptReco/PA2013_HiForest_PromptReco_KrisztianMB_JSonPPb_forestv84.root");
//    TFile* dataF = TFile::Open("root://xrootd.unl.edu//store/group/phys_heavyions/yjlee/pPb2013/promptReco/PA2013_HiForest_PromptReco_KrisztianMB_JSonPPb_forestv84.root");
	cout << "bbb" << endl;
    TTree* dataPhoTree = (TTree*) dataF -> Get("multiPhotonAnalyzer/photon");
    TTree* dataPFTree = (TTree*) dataF -> Get("pfcandAnalyzer/pfTree");
    TTree* dataSkimTree = (TTree*) dataF -> Get("skimanalysis/HltTree");
    TTree* dataHltTree = (TTree*) dataF -> Get("hltanalysis/HltTree");
    TTree* dataHiTree = (TTree*) dataF -> Get("hiEvtAnalyzer/HiTree");
	cout << "ccc" << endl;
	cout << dataPhoTree << endl;
	cout << dataPFTree << endl;
	cout << dataSkimTree << endl;
	cout << dataHltTree << endl;
	cout << dataHiTree << endl;
    dataPhoTree -> AddFriend(dataSkimTree);
	cout << "eee" << endl;
    dataPFTree -> AddFriend(dataSkimTree);
    dataPhoTree -> AddFriend(dataHltTree);
    dataPFTree -> AddFriend(dataHltTree);
    dataPhoTree -> AddFriend(dataHiTree);
    dataPFTree -> AddFriend(dataHiTree);

	cout << "ddd" << endl;
    
    TFile* MCF = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/forest/pA/H02_merged_hiforest_v68_prod12_yj_minbiasjetMC.root");
    //TFile* MCF = new TFile("root://eoscms//eos/cms/store/group/phys_heavyions/dgulhan/pPb_Hijing_MB02/prod12/HiForest_v68_merged01/H02_merged_hiforest_v68_prod12.root");
    //TFile* MCF = TFile::Open("/tmp/kimy/H02_merged_hiforest_v68_prod12.root");
    //TFile* MCF = TFile::Open("/tmp/ygo/H02_merged_hiforest_v68_prod12.root");
    //TFile* MCF = TFile::Open("root://eoscms//eos/cms/store/group/phys_heavyions/dgulhan/pPb_Hijing_MB02/prod12/HiForest_v68_merged01/H02_merged_hiforest_v68_prod12.root");
    //TFile* MCF = TFile::Open("root://xrootd.unl.edu//store/group/phys_heavyions/dgulhan/pPb_Hijing_MB02/prod12/HiForest_v68_merged01/H02_merged_hiforest_v68_prod12.root");
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


    //TCut basicCut = "pt>=0 && pt<60 && hadronicOverEm<0.2";
    //TCut runCut = "run >= 210676 && run <= 211256";
    //TCut basicCut = "pt>=0 && pt<60 && sigmaIetaIeta>0.011";
    //TCut basicCut = "pt>=0 && pt<60 && hadronicOverEm<0.2";
    TCut basicCut = "pt>=0 && pt<60 && hadronicOverEm<0.2 && sigmaIetaIeta>0.011";
    //TCut basicCut = "1"; 
    TCut EtaCut = "abs(eta) < 0.8";
    TCut pfCut = "abs(pfEta) < 0.8 && pfId==4 && pfPt>=0 && pfPt<40";
    // because of min-bias event.
    
    //=================== divide procedure ===================
    //TCut triggerCut = "1";
    TCut triggerCut = "HLT_PAZeroBiasPixel_SingleTrack_v1==1";
    //TCut eventCut = "1";
    //TCut eventCutMC = "1";
    //TCut eventCut = "pHBHENoiseFilter > 0 && pprimaryvertexFilter > 0 && pPAcollisionEventSelectionPA>0 && pVertexFilterCutGplus>0 && abs(vz)<15"; 
    TCut eventCut = "pHBHENoiseFilter > 0 && pprimaryvertexFilter > 0 && pPAcollisionEventSelectionPA>0 && abs(vz)<15"; 
    TCut eventCutMC = "pHBHENoiseFilter > 0 && pprimaryvertexFilter > 0 && pPAcollisionEventSelectionPA>0 && abs(vz)<15"; 
    TCut spikeCut = "1";
    //TCut spikeCut = "(1-(eRight+eLeft+eTop+eBottom)/eMax)<=0.9 && abs(seedTime)<=3 && sigmaIphiIphi>=0.002";
    //TCut spikeCut = "(1-(eRight+eLeft+eTop+eBottom)/eMax)<=0.9 && abs(seedTime)<=3 && sigmaIphiIphi>=0.002";

    TLegend* ll = new TLegend(0.3,0.68, 0.85, 0.85);
    ll -> SetHeader("MinBias,|#eta|<0.8");
    //ll -> SetHeader("MinBias,|#eta|<0.8, trigger&event selection");
    //ll -> SetHeader("MinBias,|#eta|<0.8, total selection");
    //=======================================================
    
    TCut totalCut = triggerCut && eventCut && EtaCut && basicCut && spikeCut;
    //TCut totalCut = triggerCut && eventCut && EtaCut && basicCut && spikeCut && runCut;
    TCut totalCutMC = triggerCut && eventCutMC && EtaCut && basicCut && spikeCut;
    TCut pftotalCut = triggerCut && eventCut && pfCut;
    //TCut pftotalCut = triggerCut && eventCut && pfCut && runCut;
    TCut pftotalCutMC = triggerCut && eventCutMC && pfCut;
    
    const char* tempTitle = totalCut.GetTitle();
    const char* tempTitleMC = totalCutMC.GetTitle();
    const char* pftempTitle = pftotalCut.GetTitle();
    const char* pftempTitleMC = pftotalCutMC.GetTitle();
    TString totalCutTitle = tempTitle;
    TString pftotalCutTitle = pftempTitle;
    TString totalCutTitleMC = tempTitleMC;
    TString pftotalCutTitleMC = pftempTitleMC;
 
    double ptbin[] = {0,2,4,6,8,10,12,14,16,18,20,30,60};
    const int nPtBin = 12;
    //TH1D* dataPhoH = new TH1D("dataPhoH", "multiPhotonAnalyzer photon;p_{T}^{#gamma} (GeV);d#sigma/dp_{T} (mb/GeV)", 8, 0, 40);
    //TH1D* dataPFH = new TH1D("dataPFH", "PF photon;p_{T}^{#gamma} (GeV);d#sigma/dp_{T} (mb/GeV)", 8, 0, 40);
    TH1D* dataPhoH = new TH1D("dataPhoH", "multiPhotonAnalyzer photon;p_{T}^{#gamma} (GeV);d#sigma/dp_{T} (mb/GeV)", nPtBin, ptbin);
    TH1D* dataPFH = new TH1D("dataPFH", "PF photon;p_{T}^{#gamma} (GeV);d#sigma/dp_{T} (mb/GeV)", nPtBin, ptbin);
    TH1D* MCPhoH = (TH1D*) dataPhoH -> Clone("MCPhoH");
    TH1D* MCPFH = (TH1D*) dataPFH -> Clone("MCPFH");

    dataPhoTree -> Draw("pt >> dataPhoH", totalCutTitle);
    dataPFTree -> Draw("pfPt >> dataPFH", pftotalCutTitle);
    //int dataPhoEntries = dataPhoTree -> GetEntries(triggerCut && eventCut && runCut);
    //int dataPFEntries = dataPFTree -> GetEntries(triggerCut && eventCut && runCut);
    int dataPhoEntries = dataPhoTree -> GetEntries(triggerCut && eventCut);
    int dataPFEntries = dataPFTree -> GetEntries(triggerCut && eventCut);
    MCPhoTree -> Draw("pt >> MCPhoH", totalCutTitleMC);
    MCPFTree -> Draw("pfPt >> MCPFH", pftotalCutTitleMC);
    int MCPhoEntries = MCPhoTree -> GetEntries(triggerCut && eventCutMC);
    int MCPFEntries = MCPFTree -> GetEntries(triggerCut && eventCutMC);
   cout << " dataPhoEntries : " << dataPhoEntries << endl; 
   cout << " dataPFEntries : " << dataPFEntries << endl; 
   cout << " MCPhoEntries : " << MCPhoEntries << endl; 
   cout << " MCPFEntries : " << MCPFEntries << endl; 
    //double pPbLumi =3.05e-36; //30.4 nb-1

    dataPhoH -> Scale(1., "width");
    dataPhoH -> Scale(1./dataPhoEntries);
    //dataPhoH -> Scale(3029);
    dataPhoH -> SetMarkerStyle(20); 
    dataPhoH -> SetMarkerColor(2); 
    dataPFH -> Scale(1., "width");
    dataPFH -> Scale(1./dataPFEntries);
    //dataPFH -> Scale(3029);
    dataPFH -> SetMarkerStyle(20); 
    dataPFH -> SetMarkerColor(2); 
    
    MCPhoH -> Scale(1., "width");
    MCPhoH -> Scale(1./MCPhoEntries);
    MCPFH -> Scale(1., "width");
    MCPFH -> Scale(1./MCPFEntries);

    ll -> AddEntry(dataPhoH, "data");
    ll -> AddEntry(MCPhoH, "MC");

    TH1D* PhoRatio = (TH1D*) dataPhoH -> Clone("PhoRatio");
    PhoRatio -> SetTitle(";p_{T}^{#gamma} (GeV);data/MC ratio"); 
    TH1D* PFRatio = (TH1D*) dataPFH -> Clone("PFRatio");
    PFRatio -> SetTitle(";p_{T}^{#gamma} (GeV);data/MC ratio"); 
    
    PhoRatio -> Divide(dataPhoH, MCPhoH);
    PFRatio -> Divide(dataPFH, MCPFH);
    TCanvas* can1 = new TCanvas("can1", "can1", 400, 800);
    can1 -> Divide(1,2);
    can1 -> cd(1);
    dataPhoH -> Draw("p");
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


