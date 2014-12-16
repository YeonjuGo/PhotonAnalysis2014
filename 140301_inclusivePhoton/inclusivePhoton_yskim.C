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
#include <TF1.h>
#include <TGraphAsymmErrors.h>
#include <TLegend.h>
#include <TCut.h>
#include <TPad.h>

void inclusivePhoton_yskim(){
    TFile* dataF = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pA/yskim_pA_photonSkimForest_v85.root");
    TTree* dataPho = (TTree*) dataF -> Get("yPhotonTree");
   
    TFile* MCF = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pA/yskim_pA_Pyquen_allQCDPhoton_hiForest2_53x_2013-18-14-1922.root");
    TTree* MCPho = (TTree*) dataF -> Get("yPhotonTree");

    TCut etahCut = "abs(eta) < 0.8 && ( 1 - (eRight+eLeft+eTop+eBottom)/eMax ) <= 0.9 && abs(seedTime) <=3 && sigmaIetaIeta>=0.002 && sigmaIphiIphi>=0.002";
    TCut pfCut = "abs(pfEta) < 0.8 && pfId==4";

    TH1D* dataPhoH = new TH1D("dataPhoH", "photon;p_{T}^{#gamma};dN/dp_{T}",17, 30, 200);
    TH1D* dataPFH = new TH1D("dataPFH", "PF photon;p_{T}^{#gamma};dN/dp_{T}", 10, 0, 100);
    TH1D* MCPhoH = (TH1D*) dataPhoH -> Clone("MCPhoH");
    TH1D* MCPFH = (TH1D*) dataPFH -> Clone("MCPFH");

    // hlt & evt & spike rejection condition
    dataPho -> Draw("pt >> dataPhoH", etahCut);
    MCPho -> Draw("pt >> MCPhoH", "ptHatWeight*( abs(eta) < 0.8 && ( 1 - (eRight+eLeft+eTop+eBottom)/eMax ) <= 0.9 && abs(seedTime) <=3 && sigmaIetaIeta>=0.002 && sigmaIphiIphi>=0.002 )");
    
    //dataPhoH -> Scale(1., "width");
    dataPhoH -> Scale(1./dataPhoH -> Integral("width"));
    dataPhoH -> SetMarkerStyle(21); 
    dataPhoH -> SetMarkerColor(2); 
   // dataPFH -> Scale(1., "width");
   // dataPFH -> Scale(1./dataPFH -> Integral("width"));
    //dataPFH -> SetMarkerStyle(21); 
   // dataPFH -> SetMarkerColor(2); 
    //MCPhoH -> Scale(1., "width");
    MCPhoH -> Scale(1./MCPhoH -> Integral("width"));
    //MCPFH -> Scale(1., "width");
   // MCPFH -> Scale(1./MCPFH -> Integral("width"));
    cout << dataPhoH -> Integral("width") << endl; 
   // cout << dataPFH -> Integral("width") << endl; 
    cout << MCPhoH -> Integral("width") << endl; 
   // cout << MCPFH -> Integral("width") << endl; 
    TH1D* PhoRatio = (TH1D*) dataPhoH -> Clone("PhoRatio");
    PhoRatio -> SetTitle(";p_{T}^{#gamma};data/MC ratio"); 
  //  TH1D* PFRatio = (TH1D*) dataPFH -> Clone("PFRatio");
  //  PFRatio -> SetTitle(";p_{T}^{#gamma};data/MC ratio"); 
    
    PhoRatio -> Divide(dataPhoH, MCPhoH);
  //  PFRatio -> Divide(dataPFH, MCPFH);
    TCanvas* cc1 = new TCanvas("cc1", "cc1", 400, 800);
    cc1 -> Divide(1,2);
    cc1 -> cd(1);
    dataPhoH -> Draw("p");
  //  MCPhoH -> Draw();
    MCPhoH -> Draw("same");
    cc1 -> cd(2);
    PhoRatio -> Draw();

  /*  TCanvas* c2 = new TCanvas("c2", "c2", 400, 800);
    c2 -> Divide(1,2);
    c2 -> cd(1);
    dataPFH -> Draw("p");
   // MCPFH -> Draw();
    MCPFH -> Draw("same");
    c2 -> cd(2);
    PFRatio -> Draw();
*/
    }



