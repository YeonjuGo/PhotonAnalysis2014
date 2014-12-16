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

void inclusivePhoton(){
    TFile* dataF = new TFile("/home/goyeonju/recent2013/jetAnalysis/forestFiles/pA/pA_photonSkimForest_v85_HLT_PAPhoton30_NoCaloIdVL_v1_highPtPhoton40.root");
    TTree* dataPho = (TTree*) dataF -> Get("multiPhotonAnalyzer/photon");
    TTree* dataPF = (TTree*) dataF -> Get("pfcandAnalyzer/pfTree");
   
    TFile* MCPhoF[4];
    TTree* MCPhoT[4];
    TTree* MCPFT[4];

    //MCPhoF[0] = new TFile("/home/goyeonju/recent2013/jetAnalysis/forestFiles/pA/pA_Pyquen_allQCDPhoton30_hiForest2_53x_2013-18-14-1922.root");
    MCPhoF[0] = new TFile("/home/goyeonju/recent2013/jetAnalysis/forestFiles/pA/PA2013_pyquen_allQCDPhoton30to50_forestv85.root");
    MCPhoT[0] = (TTree*) MCPhoF[0] -> Get("multiPhotonAnalyzer/photon");
    MCPFT[0] = (TTree*) MCPhoF[0] -> Get("pfcandAnalyzer/pfTree");
    //MCPhoF[1] = new TFile("/home/goyeonju/recent2013/jetAnalysis/forestFiles/pA/pA_Pyquen_allQCDPhoton50_hiForest2_53x_2013-18-14-1922.root");
    MCPhoF[1] = new TFile("/home/goyeonju/recent2013/jetAnalysis/forestFiles/pA/PA2013_pyquen_allQCDPhoton50to80_forestv85.root");
    MCPhoT[1] = (TTree*) MCPhoF[1] -> Get("multiPhotonAnalyzer/photon");
    MCPFT[1] = (TTree*) MCPhoF[1] -> Get("pfcandAnalyzer/pfTree");
    //MCPhoF[2] = new TFile("/home/goyeonju/recent2013/jetAnalysis/forestFiles/pA/pA_Pyquen_allQCDPhoton80_hiForest2_53x_2013-18-14-1922.root");
    MCPhoF[2] = new TFile("/home/goyeonju/recent2013/jetAnalysis/forestFiles/pA/PA2013_pyquen_allQCDPhoton80to120_forestv85.root");
    MCPhoT[2] = (TTree*) MCPhoF[2] -> Get("multiPhotonAnalyzer/photon");
    MCPFT[2] = (TTree*) MCPhoF[2] -> Get("pfcandAnalyzer/pfTree");
    //MCPhoF[3] = new TFile("/home/goyeonju/recent2013/jetAnalysis/forestFiles/pA/pA_Pyquen_allQCDPhoton120_hiForest2_53x_2013-18-14-1922.root");
    MCPhoF[3] = new TFile("/home/goyeonju/recent2013/jetAnalysis/forestFiles/pA/PA2013_pyquen_allQCDPhoton120to9999_forestv85.root");
    MCPhoT[3] = (TTree*) MCPhoF[3] -> Get("multiPhotonAnalyzer/photon");
    MCPFT[3] = (TTree*) MCPhoF[3] -> Get("pfcandAnalyzer/pfTree");


/*
    TChain* MCPho = new TChain();
    multiTreeUtil* MCPho = new multiTreeUtil();
    MCPho -> addFile("/home/goyeonju/recent2013/jetAnalysis/forestFiles/pA/pA_Pyquen_allQCDPhoton30_hiForest2_53x_2013-18-14-1922.root", "photon", "", 27.2595);
    MCPho -> addFile("/home/goyeonju/recent2013/jetAnalysis/forestFiles/pA/pA_Pyquen_allQCDPhoton50_hiForest2_53x_2013-18-14-1922.root", "photon", "",3.50696);
    MCPho -> addFile("/home/goyeonju/recent2013/jetAnalysis/forestFiles/pA/pA_Pyquen_allQCDPhoton80_hiForest2_53x_2013-18-14-1922.root", "photon", "",0.186099);
    MCPho -> addFile("/home/goyeonju/recent2013/jetAnalysis/forestFiles/pA/pA_Pyquen_allQCDPhoton120_hiForest2_53x_2013-18-14-1922.root", "photon", "",0.0245596);
    MCPho -> addFile("/home/goyeonju/recent2013/jetAnalysis/forestFiles/pA/pA_Pyquen_allQCDPhoton30_hiForest2_53x_2013-18-14-1922.root", "multiPhotonAnalyzer/photon", "", 27.2595);
    MCPho -> addFile("/home/goyeonju/recent2013/jetAnalysis/forestFiles/pA/pA_Pyquen_allQCDPhoton50_hiForest2_53x_2013-18-14-1922.root", "multiPhotonAnalyzer/photon", "",3.50696);
    MCPho -> addFile("/home/goyeonju/recent2013/jetAnalysis/forestFiles/pA/pA_Pyquen_allQCDPhoton80_hiForest2_53x_2013-18-14-1922.root", "multiPhotonAnalyzer/photon", "",0.186099);
    MCPho -> addFile("/home/goyeonju/recent2013/jetAnalysis/forestFiles/pA/pA_Pyquen_allQCDPhoton120_hiForest2_53x_2013-18-14-1922.root", "multiPhotonAnalyzer/photon", "",0.0245596);
    //MCPho -> addFile("/home/goyeonju/recent2013/jetAnalysis/forestFiles/pA/pA_Pyquen_allQCDPhoton170_hiForest2_53x_2013-18-14-1922.root", "multiPhotonAnalyzer/photon", "",0.00243838);

   multiTreeUtil* MCPF = new multiTreeUtil();
    MCPF -> addFile("/home/goyeonju/recent2013/jetAnalysis/forestFiles/pA/pA_Pyquen_allQCDPhoton30_hiForest2_53x_2013-18-14-1922.root", "pfTree", "", 27.2595);
    MCPF -> addFile("/home/goyeonju/recent2013/jetAnalysis/forestFiles/pA/pA_Pyquen_allQCDPhoton50_hiForest2_53x_2013-18-14-1922.root", "pfTree", "",3.50696);
    MCPF -> addFile("/home/goyeonju/recent2013/jetAnalysis/forestFiles/pA/pA_Pyquen_allQCDPhoton80_hiForest2_53x_2013-18-14-1922.root", "pfTree", "",0.186099);
    MCPF -> addFile("/home/goyeonju/recent2013/jetAnalysis/forestFiles/pA/pA_Pyquen_allQCDPhoton120_hiForest2_53x_2013-18-14-1922.root", "pfTree", "",0.0245596);
    MCPF -> addFile("/home/goyeonju/recent2013/jetAnalysis/forestFiles/pA/pA_Pyquen_allQCDPhoton30_hiForest2_53x_2013-18-14-1922.root", "pfcandAnalyzer/pfTree", "", 27.2595);
    MCPF -> addFile("/home/goyeonju/recent2013/jetAnalysis/forestFiles/pA/pA_Pyquen_allQCDPhoton50_hiForest2_53x_2013-18-14-1922.root", "pfcandAnalyzer/pfTree", "",3.50696);
    MCPF -> addFile("/home/goyeonju/recent2013/jetAnalysis/forestFiles/pA/pA_Pyquen_allQCDPhoton80_hiForest2_53x_2013-18-14-1922.root", "pfcandAnalyzer/pfTree", "",0.186099);
    MCPF -> addFile("/home/goyeonju/recent2013/jetAnalysis/forestFiles/pA/pA_Pyquen_allQCDPhoton120_hiForest2_53x_2013-18-14-1922.root", "pfcandAnalyzer/pfTree", "",0.0245596);
    //MCPF -> addFile("/home/goyeonju/recent2013/jetAnalysis/forestFiles/pA/pA_Pyquen_allQCDPhoton170_hiForest2_53x_2013-18-14-1922.root", "pfcandAnalyzer/pfTree", "",0.00243838);
*/
    TCut etahCut = "abs(eta) < 0.8 && ( 1 - (eRight+eLeft+eTop+eBottom)/eMax ) <= 0.9 && abs(seedTime) <=3 && sigmaIetaIeta>=0.002 && sigmaIphiIphi>=0.002";
    TCut pfCut = "abs(pfEta) < 0.8 && pfId==4";
    //TCut pfCut = "abs(pfEta) < 0.8 && pfId==4 && ( 1 - (eRight+eLeft+eTop+eBottom)/eMax ) <= 0.9 && abs(seedTime) <=3 && sigmaIetaIeta>=0.002 && sigmaIphiIphi>=0.002";
    TCut w1 = "27.2595";
   // TCut genCut = "abs(pfEta) < 1.44 && pfId==22";

    TH1D* dataPhoH = new TH1D("dataPhoH", "photon;p_{T}^{#gamma};dN/dp_{T}",19, 10, 200);
    TH1D* dataPFH = new TH1D("dataPFH", "PF photon;p_{T}^{#gamma};dN/dp_{T}", 10, 0, 100);
    TH1D* MCPhoH = (TH1D*) dataPhoH -> Clone("MCPhoH");
    TH1D* MCPFH = (TH1D*) dataPFH -> Clone("MCPFH");

    dataPho -> Draw("pt >> dataPhoH", etahCut);
    dataPF -> Draw("pfPt >> dataPFH", pfCut);

   // MCPhoT[0] -> Draw("pt >> MCPhoH", (27.2595)*etahCut);
   // MCPhoT[1] -> Draw("pt >> MCPhoH", (3.50696)*etahCut);
   // MCPhoT[0] -> Draw("pt >> MCPhoH", w1*etahCut);

    //// for the not 30to50 ... and so on
/*  MCPhoT[0] -> Draw("pt >> MCPhoH", "27.2595*( abs(eta) < 0.8 )");
    MCPhoT[1] -> Draw("pt >> MCPhoH", "3.50696*( abs(eta) < 0.8 )");
    MCPhoT[2] -> Draw("pt >> MCPhoH", "0.186099*( abs(eta) < 0.8 )");
    MCPhoT[3] -> Draw("pt >> MCPhoH", "0.0245596*( abs(eta) < 0.8 )");
    MCPFT[0] -> Draw("pfPt >> MCPFH", "27.2595*(abs(pfEta) < 0.8 && pfId==4)");
    MCPFT[1] -> Draw("pfPt >> MCPFH", "3.50696*(abs(pfEta) < 0.8 && pfId==4)");
    MCPFT[2] -> Draw("pfPt >> MCPFH", "0.186099*(abs(pfEta) < 0.8 && pfId==4)");
    MCPFT[3] -> Draw("pfPt >> MCPFH", "0.0245596*(abs(pfEta) < 0.8 && pfId==4)");
*/
    //// for the spike rejection
  MCPhoT[0] -> Draw("pt >> MCPhoH", "(56669./50385)*( abs(eta) < 0.8 && ( 1 - (eRight+eLeft+eTop+eBottom)/eMax ) <= 0.9 && abs(seedTime) <=3 && sigmaIetaIeta>=0.002 && sigmaIphiIphi>=0.002 )");
    MCPhoT[1] -> Draw("pt >> MCPhoH", "(41906./114136)*( abs(eta) < 0.8 && ( 1 - (eRight+eLeft+eTop+eBottom)/eMax ) <= 0.9 && abs(seedTime) <=3 && sigmaIetaIeta>=0.002 && sigmaIphiIphi>=0.002)");
    MCPhoT[2] -> Draw("pt >> MCPhoH", "(12044./103562)*( abs(eta) < 0.8 && ( 1 - (eRight+eLeft+eTop+eBottom)/eMax ) <= 0.9 && abs(seedTime) <=3 && sigmaIetaIeta>=0.002 && sigmaIphiIphi>=0.002 )");
    MCPhoT[3] -> Draw("pt >> MCPhoH", "(4481./151511)*( abs(eta) < 0.8 && ( 1 - (eRight+eLeft+eTop+eBottom)/eMax ) <= 0.9 && abs(seedTime) <=3 && sigmaIetaIeta>=0.002 && sigmaIphiIphi>=0.002)");
    MCPFT[0] -> Draw("pfPt >> MCPFH", "(56669./50385)*(abs(pfEta) < 0.8 && pfId==4)");
    MCPFT[1] -> Draw("pfPt >> MCPFH", "(41906./114136)*(abs(pfEta) < 0.8 && pfId==4)");
    MCPFT[2] -> Draw("pfPt >> MCPFH", "(12044./103562)*(abs(pfEta) < 0.8 && pfId==4)");
    MCPFT[3] -> Draw("pfPt >> MCPFH", "(4481./151511)*(abs(pfEta) < 0.8 && pfId==4)"); 

    //// for the hlt trigger + event selction
/*    MCPhoT[0] -> Draw("pt >> MCPhoH", "(56669./50385)*( abs(eta) < 0.8 )");
    MCPhoT[1] -> Draw("pt >> MCPhoH", "(41906./114136)*( abs(eta) < 0.8 )");
    MCPhoT[2] -> Draw("pt >> MCPhoH", "(12044./103562)*( abs(eta) < 0.8  )");
    MCPhoT[3] -> Draw("pt >> MCPhoH", "(4481./151511)*( abs(eta) < 0.8  )");
   MCPFT[0] -> Draw("pfPt >> MCPFH", "(56669./50385)*(abs(pfEta) < 0.8 && pfId==4)"); 
    MCPFT[1] -> Draw("pfPt >> MCPFH", "(41906./114136)*(abs(pfEta) < 0.8 && pfId==4)");
    MCPFT[2] -> Draw("pfPt >> MCPFH", "(12044./103562)*(abs(pfEta) < 0.8 && pfId==4)");
    MCPFT[3] -> Draw("pfPt >> MCPFH", "(4481./151511)*(abs(pfEta) < 0.8 && pfId==4)");
*/
 //// for the hlt trigger selction
/*    MCPhoT[0] -> Draw("pt >> MCPhoH", "(56669./50385)*( abs(eta) < 0.8)");
    MCPhoT[1] -> Draw("pt >> MCPhoH", "(41906./114136)*( abs(eta) < 0.8)");
    MCPhoT[2] -> Draw("pt >> MCPhoH", "(12044./103562)*( abs(eta) < 0.8 )");
    MCPhoT[3] -> Draw("pt >> MCPhoH", "(4481./151511)*( abs(eta) < 0.8)");
   MCPFT[0] -> Draw("pfPt >> MCPFH", "(56669./50385)*(abs(pfEta) < 0.8 && pfId==4)"); 
    MCPFT[1] -> Draw("pfPt >> MCPFH", "(41906./114136)*(abs(pfEta) < 0.8 && pfId==4)");
    MCPFT[2] -> Draw("pfPt >> MCPFH", "(12044./103562)*(abs(pfEta) < 0.8 && pfId==4)");
    MCPFT[3] -> Draw("pfPt >> MCPFH", "(4481./151511)*(abs(pfEta) < 0.8 && pfId==4)");
*/
    //dataPhoH -> Scale(1., "width");
    dataPhoH -> Scale(1./dataPhoH -> Integral("width"));
    dataPhoH -> SetMarkerStyle(21); 
    dataPhoH -> SetMarkerColor(2); 
   // dataPFH -> Scale(1., "width");
    dataPFH -> Scale(1./dataPFH -> Integral("width"));
    dataPFH -> SetMarkerStyle(21); 
    dataPFH -> SetMarkerColor(2); 
    //MCPhoH -> Scale(1., "width");
    MCPhoH -> Scale(1./MCPhoH -> Integral("width"));
    //MCPFH -> Scale(1., "width");
    MCPFH -> Scale(1./MCPFH -> Integral("width"));
    cout << dataPhoH -> Integral("width") << endl; 
    cout << dataPFH -> Integral("width") << endl; 
    cout << MCPhoH -> Integral("width") << endl; 
    cout << MCPFH -> Integral("width") << endl; 
    TH1D* PhoRatio = (TH1D*) dataPhoH -> Clone("PhoRatio");
    PhoRatio -> SetTitle(";p_{T}^{#gamma};data/MC ratio"); 
    TH1D* PFRatio = (TH1D*) dataPFH -> Clone("PFRatio");
    PFRatio -> SetTitle(";p_{T}^{#gamma};data/MC ratio"); 
    
    PhoRatio -> Divide(dataPhoH, MCPhoH);
    PFRatio -> Divide(dataPFH, MCPFH);
    TCanvas* cc1 = new TCanvas("cc1", "cc1", 400, 800);
    cc1 -> Divide(1,2);
    cc1 -> cd(1);
    dataPhoH -> Draw("p");
  //  MCPhoH -> Draw();
    MCPhoH -> Draw("same");
    cc1 -> cd(2);
    PhoRatio -> Draw();

    TCanvas* c2 = new TCanvas("c2", "c2", 400, 800);
    c2 -> Divide(1,2);
    c2 -> cd(1);
    dataPFH -> Draw("p");
   // MCPFH -> Draw();
    MCPFH -> Draw("same");
    c2 -> cd(2);
    PFRatio -> Draw();
}


