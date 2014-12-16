// Author : Yeonju Go 
// modified by yeonju
// add pt15, pt30, pt50 MC files
// 2014.03.11

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

void bkgPhoton_v4(){

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
    TFile* MCF[3]; 
    TTree* MCPhoTree[3];
    TTree* MCPFTree[3]; 
    TTree* MCSkimTree[3]; 
    TTree* MCHltTree[3];
    TTree* MCHiTree[3];
    for(int i=0; i<3;i++){
        if(i==0) MCF[i] = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/forest/pA/pt15_HP05_prod24_v84_merged_forest_0.root");
        else if(i==1) MCF[i] = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/forest/pA/pt30_HP05_prod24_v84_merged_forest_0.root");
        else if(i==2) MCF[i] = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/forest/pA/pt50_HP05_prod24_v84_merged_forest_0.root");
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
//======================= trigger prescale test =================================
//

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
    cout << "87 line" << endl;
    // removed h/e 
    TCut runCut = "HiTree.run >= 210676 && HiTree.run <= 211256";
    TCut basicCut = "pt>0 && pt<100 && sigmaIetaIeta>0.011 && hadronicOverEm<0.2";
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
    ll -> SetHeader("|#eta|<0.8, total selection");
   
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

    dataPhoTree -> Draw("pt >> dataPhoH", totalCutTitle); //no weight
    dataPFTree -> Draw("pfPt >> dataPFH", pftotalCutTitle);

    TString ptHatCut[3];
    double PhoTotEntries[3];
    double PFTotEntries[3];
    stringstream strPhoEntries[3];
    stringstream strPFEntries[3];
    TString PhoWeight[3];
    TString PFWeight[3];
   
    ptHatCut[0] = "&& ptHat >=15 && ptHat <30)";
    ptHatCut[1] = "&& ptHat >=30 && ptHat <50)";
    ptHatCut[2] = "&& ptHat >=50)";
 
    cout << "line 148" << endl;   
    // EffectiveCrossSection/NumOfEvent
    for(int i=0;i<3;i++){
        PhoTotEntries[i] = 1./MCPhoTree[i]->GetEntries(triggerCut && eventCutMC);
        PFTotEntries[i] = 1./MCPFTree[i]->GetEntries(triggerCut && eventCutMC);
        cout << i << "th PhoEntries(triggerCut&&eventCut) : " <<  PhoTotEntries[i] << endl;
        cout << i << "th PFEntries(triggerCut&&eventCut) : " <<  PhoTotEntries[i] << endl;
        strPhoEntries[i] >> PhoTotEntries[i];
        strPFEntries[i] >> PFTotEntries[i];
        cout << "str (Pho) is ok? : " << strPhoEntries[i] << endl;
        cout << "str (PF) is ok? : " << strPFEntries[i] << endl;
      /*  PhoTotEntries[0] = MCPhoTree[0]->GetEntries(triggerCut && eventCutMC);
        PhoTotEntries[1] = MCPhoTree[1]->GetEntries(triggerCut && eventCutMC);
        PhoTotEntries[2] = MCPhoTree[2]->GetEntries(triggerCut && eventCutMC);
        PFTotEntries[0] = MCPFTree[0]->GetEntries(triggerCut && eventCutMC);
        PFTotEntries[1] = MCPFTree[1]->GetEntries(triggerCut && eventCutMC);
        PFTotEntries[2] = MCPFTree[2]->GetEntries(triggerCut && eventCutMC);
        strPhoEntries[0] = to_string(PhoTotEntries[0]);
        strPhoEntries[1] = to_string(PhoTotEntries[1]);
        strPhoEntries[2] = to_string(PhoTotEntries[2]);
        strPFEntries[0] = to_string(PFTotEntries[0]);
        strPFEntries[1] = to_string(PFTotEntries[1]);
        strPFEntries[2] = to_string(PFTotEntries[2]);
        */
    }
    PhoWeight[0] = "0.00012108*0.3592*(";//5.335e-01-1.743e-01
    PhoWeight[1] = "9.31289e-06*0.14052*(";//1.743e-01-3.378e-02
    PhoWeight[2] = "4.88384e-06*0.03378*(";
    PFWeight[0] = "0.00012108*0.3592*(";//5.335e-01-1.743e-01
    PFWeight[1] = "9.31289e-06*0.14052*(";//1.743e-01-3.378e-02
    PFWeight[2] = "4.88384e-06*0.03378*(";
    /*
    PhoWeight[0] = "0.00012108*0.3592*(";//5.335e-01-1.743e-01
    PhoWeight[1] = "9.31289e-06*0.14052*(";//1.743e-01-3.378e-02
    PhoWeight[2] = "4.88384e-06*0.03378*(";
    PFWeight[0] = "0.00012108*5.335e-01*(";//5.335e-01-1.743e-01
    PFWeight[1] = "9.31289e-06*1.743e-01*(";//1.743e-01-3.378e-02
    PFWeight[2] = "4.88384e-06*0.03378*(";
*/  /*PhoWeight[0] = strPhoEntries[0].str()+"*0.3592*(";//5.335e-01-1.743e-01
    PhoWeight[1] = strPhoEntries[1].str()+"*0.14052*(";//1.743e-01-3.378e-02
    PhoWeight[2] = strPhoEntries[2].str()+"*0.03378*(";
    PFWeight[0] = strPFEntries[0].str()+"*5.335e-01*(";//5.335e-01-1.743e-01
    PFWeight[1] = strPFEntries[1].str()+"*1.743e-01*(";//1.743e-01-3.378e-02
    PFWeight[2] = strPFEntries[2].str()+"*0.03378*(";
  */  
    TString PhoFinal[3];
    TString PFFinal[3];
    //PhoFinal[0]=PhoWeight[0]+totalCutTitleMC+ptHatCut[0];
    //PhoFinal[1]=PhoWeight[1]+totalCutTitleMC+ptHatCut[1];
    //PhoFinal[2]=PhoWeight[2]+totalCutTitleMC+ptHatCut[2];
    PhoFinal[0]=PhoWeight[0]+totalCutTitleMC+")";
    PhoFinal[1]=PhoWeight[1]+totalCutTitleMC+")";
    PhoFinal[2]=PhoWeight[2]+totalCutTitleMC+")";
    PFFinal[0]=PFWeight[0]+pftotalCutTitleMC+")";
    PFFinal[1]=PFWeight[1]+pftotalCutTitleMC+")";
    PFFinal[2]=PFWeight[2]+pftotalCutTitleMC+")";
    cout << PhoFinal[2] << endl;
    cout << PFFinal[2] << endl;
    cout << "line 184" << endl; 
    MCPhoTree[0] -> Draw("pt >> MCPhoH", PhoFinal[0]); //no weight
    MCPhoTree[1] -> Draw("pt >> MCPhoH", PhoFinal[1]); //no weight
    MCPhoTree[2] -> Draw("pt >> MCPhoH", PhoFinal[2]); //no weight
    MCPFTree[0] -> Draw("pfPt >> MCPFH", PFFinal[0]);
    MCPFTree[1] -> Draw("pfPt >> MCPFH", PFFinal[1]);
    MCPFTree[2] -> Draw("pfPt >> MCPFH", PFFinal[2]);
 /*  MCPhoTree[0] -> Draw("pt >> MCPhoH", PhoWeight[0]+totalCutTitleMC+ptHatCut[0]); //no weight
    MCPhoTree[1] -> Draw("pt >> MCPhoH", PhoWeight[1]+totalCutTitleMC+ptHatCut[1]); //no weight
    MCPhoTree[2] -> Draw("pt >> MCPhoH", PhoWeight[2]+totalCutTitleMC+ptHatCut[2]); //no weight
    MCPFTree[0] -> Draw("pfPt >> MCPFH", PFWeight[0]+pftotalCutTitleMC);
    MCPFTree[1] -> Draw("pfPt >> MCPFH", PFWeight[1]+pftotalCutTitleMC);
    MCPFTree[2] -> Draw("pfPt >> MCPFH", PFWeight[2]+pftotalCutTitleMC);
*/
    //double pPbLumi =3.09e7; //3.05e7 mb-1 = 30.9 nb-1 
    double pPbLumi =5.8e5; //effective lumi 5.8e5 mb-1 = 580.252 ub-1 
    // double pPbLumi =1.58e7; //recorded lumi 5.8e5 mb-1 = 580.252 ub-1 
cout << " 201 line" << endl;
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
    
    MCPhoH -> Scale(1., "width");
 //   MCPhoH -> Scale(5.335e-01); 
 //   MCPhoH -> Scale(1./MCPhoTree->GetEntries(triggerCut && eventCutMC));
    MCPFH -> Scale(1., "width");
 //   MCPFH -> Scale(5.335e-01);
 //   MCPFH -> Scale(1./MCPFTree->GetEntries(triggerCut && eventCutMC));
    cout << " 221 line" << endl; 
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
    ll -> Draw();

    cc1 -> cd(2);
    PhoRatio -> SetMarkerColor(1); 
    PhoRatio -> Draw("p");

    TCanvas* c2 = new TCanvas("c2", "c2", 400, 800);
    c2 -> Divide(1,2);
    c2 -> cd(1);
    MCPFH -> Draw("hist");
    dataPFH -> Draw("p same");
    ll -> Draw();
    
    c2 -> cd(2);
    PFRatio -> SetMarkerColor(1); 
    PFRatio -> Draw("p");
}


