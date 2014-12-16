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

void leading_bkgPhoton(){

    TH1::SetDefaultSumw2();
    TFile* dataF = new TFile("/home/goyeonju/recent2013/jetAnalysis/forestFiles/pA/pA_photonSkimForest_v85.root");
    TTree* dataPhoTree = (TTree*) dataF -> Get("multiPhotonAnalyzer/photon");
    TTree* dataPFTree = (TTree*) dataF -> Get("pfcandAnalyzer/pfTree");
    TTree* dataSkimTree = (TTree*) dataF -> Get("skimanalysis/HltTree");
    TTree* dataHltTree = (TTree*) dataF -> Get("hltanalysis/HltTree");
    TTree* dataHiTree = (TTree*) dataF -> Get("hiEvtAnalyzer/HiTree");
    dataPhoTree -> AddFriend(dataSkimTree);
    dataPhoTree -> AddFriend(dataHltTree);
    dataPhoTree -> AddFriend(dataHiTree);
    dataPhoTree -> AddFriend(dataPFTree);
   // dataPFTree -> AddFriend(dataSkimTree);
   // dataPFTree -> AddFriend(dataHltTree);
   // dataPFTree -> AddFriend(dataHiTree);

    const int nfile = 5;
    bool isMC = true;
    /*    
    HiForest *c[nfile];
    c[0] = new HiForest("/home/goyeonju/recent2013/jetAnalysis/files/forest/pA/pt15_HP05_prod24_v84_merged_forest_0.root", "forest", cPPb, isMC );
    c[1] = new HiForest("/home/goyeonju/recent2013/jetAnalysis/files/forest/pA/pt30_HP05_prod24_v84_merged_forest_0.root", "forest", cPPb, isMC );
    c[2] = new HiForest("/home/goyeonju/recent2013/jetAnalysis/files/forest/pA/pt50_HP05_prod24_v84_merged_forest_0.root", "forest", cPPb, isMC );
    c[3] = new HiForest("/home/goyeonju/recent2013/jetAnalysis/files/forest/pA/pt80_HP05_prod24_v84_merged_forest_0.root", "forest", cPPb, isMC );
    c[4] = new HiForest("/home/goyeonju/recent2013/jetAnalysis/files/forest/pA/pt120_HP05_prod24_v84_merged_forest_0.root", "forest", cPPb, isMC );
    for(int i=0; i<nfile; i++) c[i] -> InitTree();
    */ 
    TFile* MCF[nfile]; 
    TTree* MCPhoTree[nfile];
    TTree* MCPFTree[nfile]; 
    TTree* MCSkimTree[nfile]; 
    TTree* MCHltTree[nfile];
    TTree* MCHiTree[nfile];
    //photon tree
    int nPhotons[nfile];
    float pt[nfile][126], eta[nfile][126], sigmaIetaIeta[nfile][126], sigmaIphiIphi[nfile][126], seedTime[nfile][126];
    //skim tree
    int pPAcollisionEventSelectionPA[nfile], pHBHENoiseFilter[nfile], pprimaryvertexFilter[nfile]
    
    /*   int nPhotons0;
    int nPhotons1;
    int nPhotons2;
    int nPhotons3;
    int nPhotons4;
    float pt0[126], eta0[126], sigmaIetaIeta0[126], seedTime0[126], sigmaIphiIphi0[126];
    float pt1[126], eta1[126], sigmaIetaIeta1[126], seedTime1[126], sigmaIphiIphi1[126];
    float pt2[126], eta2[126], sigmaIetaIeta2[126], seedTime2[126], sigmaIphiIphi2[126];
    float pt3[126], eta3[126], sigmaIetaIeta3[126], seedTime3[126], sigmaIphiIphi3[126];
    float pt4[126], eta4[126], sigmaIetaIeta4[126], seedTime4[126], sigmaIphiIphi4[126];
 */ 
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
        MCPhoTree[i] -> AddFriend(MCHltTree[i]);
        MCPhoTree[i] -> AddFriend(MCHiTree[i]);
        MCPhoTree[i] -> AddFriend(MCPFTree[i]);

        MCPhoTree[i]-> SetBranchAddress("nPhotons", &nPhotons[i]);
        MCPhoTree[i]-> SetBranchAddress("pt", &pt[i]);
        MCPhoTree[i]-> SetBranchAddress("eta", &eta[i]);
        MCPhoTree[i]-> SetBranchAddress("sigmaIetaIeta", &sigmaIetaIeta[i]);
        MCPhoTree[i]-> SetBranchAddress("sigmaIphiIphi", &sigmaIphiIphi[i]);
        MCPhoTree[i]-> SetBranchAddress("seedTime", &seedTime[i]);
    }


/*  
    MCPhoTree[0]-> SetBranchAddress("nPhotons", &nPhotons0);
    MCPhoTree[0]-> SetBranchAddress("pt", &pt0);
    MCPhoTree[0]-> SetBranchAddress("eta", &eta0);
    MCPhoTree[0]-> SetBranchAddress("sigmaIetaIeta", &sigmaIetaIeta0);
    MCPhoTree[0]-> SetBranchAddress("sigmaIphiIphi", &sigmaIphiIphi0);
    MCPhoTree[0]-> SetBranchAddress("seedTime", &seedTime0);
    
    MCPhoTree[1]-> SetBranchAddress("nPhotons", &nPhotons1);
    MCPhoTree[1]-> SetBranchAddress("pt", &pt1);
    MCPhoTree[1]-> SetBranchAddress("eta", &eta1);
    MCPhoTree[1]-> SetBranchAddress("sigmaIetaIeta", &sigmaIetaIeta1);
    MCPhoTree[1]-> SetBranchAddress("sigmaIphiIphi", &sigmaIphiIphi1);
    MCPhoTree[1]-> SetBranchAddress("seedTime", &seedTime1);
    
    MCPhoTree[2]-> SetBranchAddress("nPhotons", &nPhotons2);
    MCPhoTree[2]-> SetBranchAddress("pt", &pt2);
    MCPhoTree[2]-> SetBranchAddress("eta", &eta2);
    MCPhoTree[2]-> SetBranchAddress("sigmaIetaIeta", &sigmaIetaIeta2);
    MCPhoTree[2]-> SetBranchAddress("sigmaIphiIphi", &sigmaIphiIphi2);
    MCPhoTree[2]-> SetBranchAddress("seedTime", &seedTime2);
    
    MCPhoTree[3]-> SetBranchAddress("nPhotons", &nPhotons3);
    MCPhoTree[3]-> SetBranchAddress("pt", &pt3);
    MCPhoTree[3]-> SetBranchAddress("eta", &eta3);
    MCPhoTree[3]-> SetBranchAddress("sigmaIetaIeta", &sigmaIetaIeta3);
    MCPhoTree[3]-> SetBranchAddress("sigmaIphiIphi", &sigmaIphiIphi3);
    MCPhoTree[3]-> SetBranchAddress("seedTime", &seedTime3);
    
    MCPhoTree[4]-> SetBranchAddress("nPhotons", &nPhotons4);
    MCPhoTree[4]-> SetBranchAddress("pt", &pt4);
    MCPhoTree[4]-> SetBranchAddress("eta", &eta4);
    MCPhoTree[4]-> SetBranchAddress("sigmaIetaIeta", &sigmaIetaIeta4);
    MCPhoTree[4]-> SetBranchAddress("sigmaIphiIphi", &sigmaIphiIphi4);
    MCPhoTree[4]-> SetBranchAddress("seedTime", &seedTime4);
    //   MCPhoTree[i]-> SetBranchAddress("", &pt);
    //   MCPhoTree[i]-> SetBranchAddress("pt", &pt);
    //   MCPhoTree[i]-> SetBranchAddress("pt", &pt);
    //   MCPhoTree[i]-> SetBranchAddress("pt", &pt);
    //   MCPhoTree[i]-> SetBranchAddress("pt", &pt);
     //   MCPhoTree[i]-> SetBranchAddress("pt", &pt);
    
  */      

//
//======================= ptHat Cut : combining the different ptHat MC files: =================================
//

    TCanvas* cpre = new TCanvas("cpre", "", 400,400);
    cpre -> Clear();
    //cpre -> Divide(1,2);
    //cpre -> cd();
    cpre -> cd();
    TH1D* hpt0 = new TH1D("hpt0", ";p_{T}^{#gamma} (GeV);Entries", 40, 0, 200);
    TH1D* hpt1 = (TH1D*) hpt0 -> Clone("hpt1");
    TH1D* hpt2 = (TH1D*) hpt0 -> Clone("hpt2");
    TH1D* hpt3 = (TH1D*) hpt0 -> Clone("hpt3");
    TH1D* hpt4 = (TH1D*) hpt0 -> Clone("hpt4");

    // method of using HiForest makes seg. fault
    // c[0] ->photonTree-> Draw("ptHat >> hpt0", "(5.335e-01/172400.0)*(1)");
    // c[1] ->photonTree-> Draw("ptHat >> hpt1", "(3.378e-02/403200.0)*(1)");
    // c[2] ->photonTree-> Draw("ptHat >> hpt2", "(3.778E-03/362400.0)*(1)");
    //  c[3] ->photonTree-> Draw("ptHat >> hpt3", "(4.412e-04/358000.0)*(1)");
    //  c[4] ->photonTree-> Draw("ptHat >> hpt4", "(6.147E-05/306400.0)*(1)");


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
  
 
//
//================== Cut Conditions ====================
//

    TCut ;





//
//=============== leading photon selection : Loop starts =================
//

    int nentries[nfile];
    // for(int i=0; i< nfile; i++){
    int i=1;
    nentries[i] = MCPhoTree[i] -> GetEntries();
    cout << i << "th number of entries = " << nentries[i] << endl;

    int order[126];
    for(Long64_t jentry=0; jentry < nentries[i]; jentry++){
        if(jentry%2000 ==0) 
            cout << jentry << " / " << nentries[i] << "  " << (double)jentry/nentries[i]*100 << " %" << endl;
        
        MCPhoTree[i] -> GetEntry(jentry);
        
        if(HLT_PAPhoton10_NoCaloIdVL_v1[i]==0) continue; // trigger selection 
        if(pHBHENoiseFilter[i]==0 || pprimaryvertexFilter[i]==0 || pPAcollisionEventSelectionPA[i]==0 || abs(vz[i])>=15) continue; //event selection
        
        for ( int g=0 ; g< nPhotons1 ; g++) {
            if(sigmaIeatIeta[i][g]<0.011) continue; // prompt photon rejection.
            if(hadronicOverEm[i][g]>0.2) continue; // this is neither pi0 nor prompt photon 
            if( (1-(eRight[i][g]+eLeft[i][g]+eTop[i][g]+eBottom[i][g])/eMax[i][g])>0.9 || abs(seedTime[i][g])>3 || sigmaIphiIphi[i][g]<0.002 ) continue; //spike rejection
            if( abs(eta[i][g])>=0.8 || pt<=0 || pt>=100) continue; // eta and pt condition
 
 
 
            cout << g << "th pt : " << pt1[g] << ", and sigmaIetaIeta : " << sigmaIetaIeta1[g] << endl;
        }
        TMath::Sort(nPhotons1, pt1, order);

        for (int g=0; g<nPhotons1; g++){
            cout << "sorted "<< g << "th pt : " << pt1[order[g]] << ", and sigmaIetaIeta : " << sigmaIetaIeta1[order[g]] << endl;
        }
    }
}
//}*/
/*

            if ( )
                    continue;
                if ( fabs( c->genp.momId[g] ) > 22 )
                    continue;
                if ( fabs( c->genp.status[g] ) != 1 ) 
                    continue;
                if ( fabs( c->genp.eta[g] ) > cutphotonEta ) 
                    continue;
                if ( c->genp.et[g] < 35 )
                    continue;
                genPhotonFlag = true;
            }   
         c->photon.nPhotons

    }










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
    TCut totalCutMC = eventCutMC && EtaCut && basicCut && spikeCut;
    TCut pftotalCut = triggerCut && eventCut && pfCut && runCut;
    TCut pftotalCutMC = eventCutMC && pfCut;
    
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
      //  PhoTotEntries[0] = MCPhoTree[0]->GetEntries(triggerCut && eventCutMC);
      //  PhoTotEntries[1] = MCPhoTree[1]->GetEntries(triggerCut && eventCutMC);
     //   PhoTotEntries[2] = MCPhoTree[2]->GetEntries(triggerCut && eventCutMC);
     //   PFTotEntries[0] = MCPFTree[0]->GetEntries(triggerCut && eventCutMC);
      //  PFTotEntries[1] = MCPFTree[1]->GetEntries(triggerCut && eventCutMC);
     //   PFTotEntries[2] = MCPFTree[2]->GetEntries(triggerCut && eventCutMC);
      //  strPhoEntries[0] = to_string(PhoTotEntries[0]);
      //  strPhoEntries[1] = to_string(PhoTotEntries[1]);
      //  strPhoEntries[2] = to_string(PhoTotEntries[2]);
      //  strPFEntries[0] = to_string(PFTotEntries[0]);
       // strPFEntries[1] = to_string(PFTotEntries[1]);
       // strPFEntries[2] = to_string(PFTotEntries[2]);
        
    }
    PhoWeight[0] = "0.00012108*0.3592*(";//5.335e-01-1.743e-01
    PhoWeight[1] = "9.31289e-06*0.14052*(";//1.743e-01-3.378e-02
    PhoWeight[2] = "4.88384e-06*0.03378*(";
    PFWeight[0] = "0.00012108*0.3592*(";//5.335e-01-1.743e-01
    PFWeight[1] = "9.31289e-06*0.14052*(";//1.743e-01-3.378e-02
    PFWeight[2] = "4.88384e-06*0.03378*(";
    
  
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
 //  MCPhoTree[0] -> Draw("pt >> MCPhoH", PhoWeight[0]+totalCutTitleMC+ptHatCut[0]); //no weight
 //   MCPhoTree[1] -> Draw("pt >> MCPhoH", PhoWeight[1]+totalCutTitleMC+ptHatCut[1]); //no weight
 //   MCPhoTree[2] -> Draw("pt >> MCPhoH", PhoWeight[2]+totalCutTitleMC+ptHatCut[2]); //no weight
 //   MCPFTree[0] -> Draw("pfPt >> MCPFH", PFWeight[0]+pftotalCutTitleMC);
 //   MCPFTree[1] -> Draw("pfPt >> MCPFH", PFWeight[1]+pftotalCutTitleMC);
 //   MCPFTree[2] -> Draw("pfPt >> MCPFH", PFWeight[2]+pftotalCutTitleMC);

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

*/
