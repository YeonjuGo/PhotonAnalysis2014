// modified by Yeonju 20140109 Wed.
// photonPurity.C
// Author: Alex Barbieri
// Cobbled together from code written by Yongsun Kim

// Calculates and plots the photon purity using a sideband estimation
// of the background and a MC calculation of the signal. This info is
// used to do a template fit in the sigmaIetaIeta variable.

#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TH1D.h"
#include "TCut.h"
#include "TProfile.h"
#include "TGraphAsymmErrors.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TROOT.h"
#include "TString.h"
#include "TLatex.h"
#include "TStyle.h"
#include "stdio.h"
#include <iostream>
#include "../gammaJetAnalysis/commonUtility.h"
#include "../gammaJetAnalysis/yj_fitResult.h"
//#include "uniqueEvents.C"

using namespace std;
//last forward run is 211256
/*
// //pp
 const TString DATA_FILE = "/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pp/yskim_pp_photonSKimForest_v85.root";
 const TString MC_FILE = "/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pp/yskim_pp2760_pythia_allQCDPhoton_CMSSW538HIp2.root";
 const TString LABEL = "pp #sqrt{s}_{_{NN}}=2.76 TeV";
 const TCut sampleIsolation = "ecalRecHitSumEtConeDR04 < 4.2  &&  hcalTowerSumEtConeDR04 < 2.2  &&  trkSumPtHollowConeDR04 < 2 && hadronicOverEm<0.1";
// const int collision = 0;

 //PbPb
const TString DATA_FILE = "/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pbpb/yskim_HiForestPhoton-v7-noDuplicate.root";
const TString MC_FILE = "/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pbpb/yskim_PbPb_pythiaHYDJET_forest_AllQCDPhotons.root";
const TString LABEL = "PbPb #sqrt{s}_{_{NN}}=2.76 TeV";
const TCut sampleIsolation = "(cc4+cr4+ct4PtCut20<1) && hadronicOverEm<0.1";
//const int collision = 2;

 //pPb
 const TString DATA_FILE = "/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pA/yskim_pA_photonSkimForest_v85_HLT_PAPhoton30_NoCaloIdVL_v1_highPtPhoton40.root";
 const TString MC_FILE = "/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pA/yskim_pA_Pyquen_allQCDPhoton_hiForest2_53x_2013-18-14-1922.root ";
 const TString LABEL = "pPb #sqrt{s}_{_{NN}}=5.02 TeV";
 const TCut sampleIsolation = "ecalRecHitSumEtConeDR04 < 4.2  &&  hcalTowerSumEtConeDR04 < 2.2  &&  trkSumPtHollowConeDR04 < 2 && hadronicOverEm<0.1";
 //const int collision = 1;
*/
//const Double_t sigShifts[] = {-0.0000989, -0.000131273, -0.00016207, -0.000170555};
const Double_t sigShifts[] = {0, 0, 0, 0};
//const Double_t sigShifts[] = {-0.00015,-0.00015,-0.00015,-0.00015};
const TString SAVENAME = "yj_photonPurity_pA_example";

// last entry is upper bound on last bin
const Int_t CENTBINS[] = {0, 12, 40};//, 40};
//const Int_t CENTBINS[] = {0, 100};
const Int_t nCENTBINS = sizeof(CENTBINS)/sizeof(Int_t) -1;

const Double_t PTBINS[] = {40, 50, 60, 80, 120, 300};
//const Double_t PTBINS[] = {60, 80};
const Int_t nPTBINS = sizeof(PTBINS)/sizeof(Double_t) -1;

const Double_t ETABINS[] = {-1.44, 1.44};
//const Double_t ETABINS[] = {-1.44, -1, -0.5, 0, 0.5, 1, 1.44};
const Int_t nETABINS = sizeof(ETABINS)/sizeof(Double_t) -1;

// the bin which holds this value is considered the largest bin when
// computing the purity
//const Double_t PURITY_BIN_VAL = 0.00999;
const Double_t PURITY_BIN_VAL = 0.02699;

void yj_photonPurity(int collision = 1)
{
//    gROOT -> Macro("./yjStyle.C");
    gStyle -> SetOptStat(0);
    TString DATA_FILE;
    TString MC_FILE;
    TString LABEL;
    TString centCut;
    TCut sampleIsolation;

    if (collision ==0){
        // //pp
        DATA_FILE = "/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pp/yskim_pp_photonSKimForest_v85.root";
        MC_FILE = "/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pp/yskim_pp2760_pythia_allQCDPhoton_CMSSW538HIp2.root";
        LABEL = "pp #sqrt{s}_{_{NN}}=2.76 TeV";
        sampleIsolation = "ecalRecHitSumEtConeDR04 < 4.2  &&  hcalTowerSumEtConeDR04 < 2.2  &&  trkSumPtHollowConeDR04 < 2 && hadronicOverEm<0.1";
        centCut =""; 
    }else if(collision ==2 || collision ==3){
        //PbPb
        DATA_FILE = "/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pbpb/yskim_HiForestPhoton-v7-noDuplicate.root";
        MC_FILE = "/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pbpb/yskim_PbPb_pythiaHYDJET_forest_AllQCDPhotons.root";
        if(collision ==2 ) {
            LABEL = "PbPb #sqrt{s}_{_{NN}}=2.76 TeV 0-30 %";
            centCut = Form("((cBin) >= %i) && ((cBin) < %i)", CENTBINS[0], CENTBINS[1]);
        } else if(collision ==3 ) { 
            LABEL = "PbPb #sqrt{s}_{_{NN}}=2.76 TeV 30-100 %";
            centCut = Form("((cBin) >= %i) && ((cBin) < %i)", CENTBINS[1], CENTBINS[2]);   
        } sampleIsolation = "(cc4+cr4+ct4PtCut20<1) && hadronicOverEm<0.1";
        
    } else if(collision ==1){
        //pPb
        DATA_FILE ="/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pA/yskim_pA_photonSkimForest_v85.root";
        MC_FILE = "/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pA/yskim_pA_Pyquen_allQCDPhoton_hiForest2_53x_2013-18-14-1922.root ";
        LABEL = "pPb #sqrt{s}_{_{NN}}=5.02 TeV";
        sampleIsolation = "ecalRecHitSumEtConeDR04 < 4.2  &&  hcalTowerSumEtConeDR04 < 2.2  &&  trkSumPtHollowConeDR04 < 2 && hadronicOverEm<0.1";
        centCut = "";
    }

    TH1::SetDefaultSumw2();

    TFile *dataFile = TFile::Open(DATA_FILE);
    TTree *dataTree = (TTree*)dataFile->Get("yPhotonTree");
    TTree *datatgjTree = (TTree*)dataFile->Get("tgj");
    dataTree -> AddFriend(datatgjTree);

    TFile *mcFile = TFile::Open(MC_FILE);
    TTree *mcTree = (TTree*)mcFile->Get("yPhotonTree");
    TTree *mctgjTree = (TTree*)mcFile->Get("tgj");
    mcTree -> AddFriend(mctgjTree);

    const TCut sidebandIsolation = "(cc4+cr4+ct4PtCut20>10) && (cc4+cr4+ct4PtCut20<20) && hadronicOverEm<0.1";
    //const TCut sidebandIsolation = "(cc4+cr4+ct4PtCut20>5) && (cc4+cr4+ct4PtCut20<10) && hadronicOverEm<0.1";
    const TCut mcIsolation = "genCalIsoDR04<5 && abs(genMomId)<=22";
    const TCut weight = "ptHatWeight*vtxCentWeight";

    // yeonju
    //
    Float_t pur[nPTBINS] = {0, 0, 0, 0};
    //TCanvas *cPurity[nPTBINS];
    //TCanvas *cPurity = new TCanvas("c1","c1",337*nPTBINS,300*nCENTBINS/**2*/);
    TCanvas *cPurity = new TCanvas("c1","c1",400*nPTBINS,400);
    //cPurity->Divide(nPTBINS,2*nCENTBINS,0,0);
    //cPurity->Divide(nPTBINS,nCENTBINS,0,0);
    makeMultiPanelCanvas(cPurity, nPTBINS, 1, 0.0, 0.0 , 0.2, 0.15, 0.005);
    //makeMultiPanelCanvas(cPurity, nPTBINS, nCENTBINS, 0.0, 0.0 , 0.2, 0.15, 0.005);
    for(Int_t i = 0; i < nPTBINS; ++i) {
        //cPurity[i] = new TCanvas(Form("c1_%d",i),"",1920,1000);
        //cPurity[i]->Divide(nETABINS,2,0,0);
        for(Int_t j = 0; j < nCENTBINS; ++j) {
            for(Int_t k = 0; k< nETABINS; ++k) {
                TString ptCut = Form("(corrPt >= %f) && (corrPt < %f)",
                        PTBINS[i], PTBINS[i+1]);
               TString etaCut = Form("(eta >= %f) && (eta < %f)",
                        ETABINS[k], ETABINS[k+1]);

                //TString pPbflipetaCut = Form("(eta*((run>211257)*-1+(run<211257)) >=%f) && (eta*((run>211257)*-1+(run<211257)) <%f)",
                //			     ETABINS[k], ETABINS[k+1]);

                TCut dataCandidateCut =weight*( sampleIsolation && etaCut && ptCut && centCut);
                TCut sidebandCut = weight*( sidebandIsolation && etaCut && ptCut && centCut);
                TCut mcSignalCut = weight*(dataCandidateCut && mcIsolation);

                // if(nETABINS != 1)
                // {
                //   dataCandidateCut = sampleIsolation && pPbflipetaCut && ptCut && centCut;
                //   sidebandCut =  sidebandIsolation && pPbflipetaCut && ptCut && centCut;
                //   mcSignalCut =  sampleIsolation && etaCut && ptCut && centCut && mcIsolation;
                // }

                fitResult fitr = getPurity(dataTree, mcTree,
                        dataCandidateCut, sidebandCut,
                        mcSignalCut, sigShifts[i],
                        0.0, PURITY_BIN_VAL);

                //cPurity[i*nCENTBINS+j] = new TCanvas(Form("cpurity%d",i*nCENTBINS+j),
                // 					 "",500,500);
                cPurity->cd(2*(k+j)*nPTBINS+i+1);
                //cPurity->cd((k+j)*nPTBINS+i+1);
                //cPurity[i]->cd(k+1);

                TH1F *hSigPdf = fitr.sigPdf;
                TH1F *hBckPdf = fitr.bckPdf;
                TH1D *hData1  = fitr.data;

                // plot stacked histos
                hSigPdf->Add(hBckPdf);
                handsomeTH1(hSigPdf);
                mcStyle(hSigPdf);
                sbStyle(hBckPdf);
                cleverRange(hSigPdf,1.5);
                hSigPdf->SetAxisRange(0.001,0.024,"X");
                hSigPdf->SetNdivisions(505);
                hSigPdf->GetYaxis()->SetTitleOffset(1.75);
                hSigPdf->SetYTitle("Entries");
                hSigPdf->SetXTitle("#sigma_{#eta #eta}");
                hSigPdf->DrawCopy("hist");
                hBckPdf->DrawCopy("same hist");
                hData1->DrawCopy("same");

                Float_t xpos = 0.42;
                if(2*(k+j)*nPTBINS+i+1 == 1)
                    xpos = 0.52;

                TLegend *t3=new TLegend(xpos, 0.60, 0.92, 0.79);
                t3->AddEntry(hData1,LABEL,"pl");
                t3->AddEntry(hSigPdf,"Signal","lf");
                t3->AddEntry(hBckPdf,"Background","lf");
                t3->SetFillColor(0);
                t3->SetBorderSize(0);
                t3->SetFillStyle(0);
                t3->SetTextFont(43);
                t3->SetTextSize(20);
                //if(i == 0)
                t3->Draw();

                //if(i == 0)
                drawText("CMS Preliminary", xpos, 0.90,1,20);

                //drawText("|#eta_{#gamma}| < 1.479",0.5680963,0.9);
                //drawText(Form("%f shift",fitr.sigMeanShift),0.57,0.82);
                //drawText("Background Correction",0.57,0.82);
                //drawText("bkg Tighter",0.57,0.82);
                //if(nPTBINS != 1)
                drawText(Form("%.0f GeV < p_{T}^{#gamma} < %.0f GeV",
                            PTBINS[i], PTBINS[i+1]),
                        xpos, 0.82,1,20);
                // if(/*nCENTBINS != 1 && */i ==0)
                //   drawText(Form("%.0f - %.0f%c",
                // 		CENTBINS[j]*100./40., CENTBINS[j+1]*100./40.,'%'),
                // 	   0.27, 0.82);
                if(nETABINS != 1)
                    drawText(Form("%.3f < #eta_{#gamma} < %.3f",
                                ETABINS[k], ETABINS[k+1]),
                            xpos, 0.82,1,20);
                drawText(Form("Purity : %.2f", (Float_t)fitr.purity),
                        xpos, 0.53,1,20);

                pur[i]=(Float_t)fitr.purity;
                // drawText(Form("#chi^{2}/ndf : %.2f", (Float_t)fitr.chisq),
                // 	 xpos, 0.45);

                // //plot ratio
                // cPurity->cd((2*(j+k)+1)*nPTBINS+i+1);
                // //cPurity[i]->cd(nETABINS + k+ 1);
                // TH1D* ratio = (TH1D*)hData1->Clone("ratio");
                // ratio->Divide(hData1, hSigPdf, 1, 1);
                // ratio->SetMinimum(0);
                // ratio->SetMaximum(3);
                // ratio->SetXTitle("#sigma_{#eta #eta}");
                // ratio->GetXaxis()->CenterTitle();
                // ratio->SetYTitle("Data/Fit");
                // ratio->GetYaxis()->CenterTitle();
                // ratio->DrawCopy("E");
                // TLine *line = new TLine(0,1,maxSIGMA,1);
                // line->SetLineStyle(2);
                // line->Draw("same");

                // TString savename = Form("purity_pA_barrel_pt%.0f_hf%.0f_plot",
                // 			PTBINS[i], CENTBINS[j]);
                // cPurity[i*nCENTBINS+j]->SaveAs(savename+".C");
                // cPurity[i*nCENTBINS+j]->SaveAs(savename+".pdf");
                // cPurity[i*nCENTBINS+j]->SaveAs(savename+".png");

            }
        }
        //cPurity[i]->SaveAs(Form("pPb_purity_etadep_wshift_ptbin%.0f.png",PTBINS[i]));
        //cPurity[i]->SaveAs(Form("pPb_purity_etadep_noshift_inclusive.png"));
    }
    //cPurity->SaveAs(SAVENAME+".C");
    //cPurity->SaveAs(SAVENAME+".png");
    cPurity->SaveAs(SAVENAME+".pdf");
    
    
    TFile* writeF = new TFile(Form("purity_%d.root",collision), "RECREATE");
    TCanvas* can = new TCanvas("can", "", 400, 400);
    TH1D* purityH = new TH1D("purityH", "purity; p_{T}^{#gamma} (GeV); purity", nPTBINS, PTBINS);
    purityH -> SetAxisRange(0.45, 1.0, "Y");
    for(int i=0; i<nPTBINS; i++){
        purityH -> Fill(PTBINS[i], pur[i]);
        purityH -> SetBinError(i+1, 0.00001);
    }
    purityH -> SetTitleSize(0.05, "Y");
    purityH -> SetTitleSize(0.05, "X");
   // purityH -> SetTitleOffset(1.3, "Y");
    purityH -> SetMarkerStyle(20);
    purityH -> Draw("P");
    TLegend* leg = new TLegend(0.3, 0.7, 0.89, 0.89);
    leg -> SetFillColor(0); 
    leg -> SetBorderSize(0);
    leg -> SetHeader(LABEL);
    leg -> Draw();
    writeF -> Write();

}
/*
   int main()
   {
   photonPurity();
   return 0;
   }*/
