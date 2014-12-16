// yeonju
// to compare between the old fitting and new fitting (comming from different file) 
// old file is red color, new file is black color
// old skim is open circle, new skim is closed circle
//
#include "../HiForestAnalysis/hiForest.h"
#include "../gammaJetAnalysis/CutAndBinCollection2012.h"
#include <TStyle.h>
#include <TH1D.h>
#include <TTree.h>
#include <TBranch.h>
#include <TFile.h>
#include <iostream>
#include <TCanvas.h>
#include <TF1.h>
#include <TGraphAsymmErrors.h>
#include <TLegend.h>
#include <TCut.h>

void CompareResolFit(){
//
// comparing resolutions 
//
    TH1::SetDefaultSumw2();
    TFile* oldFile[9];
    TFile* recentFile[9];
    TFile* OFNSFile[9];
    TFile* outFile = new TFile("comparedResol.root", "RECREATE");

    TH1D* oldH[9];//histogram // old file & old skim
    TH1D* recentH[9];         // new file & new skim 
    TH1D* OFNSH[9];         // Old File & New Skim 

    TF1 *oldF[9];//fitting // old file & old skim 
    TF1 *recentF[9];       // new file & new skim
    TF1 *OFNSF[9];       // new file & new skim

    TLegend *legend[9];
    for(int i=0;i<=7;i++){
        if(i!=2 && i!=3) 
            legend[i] = new TLegend(0.4913112,0.6561548,0.9997611,0.9431145,NULL,"brNDC");
    }
    easyLeg(legend[0], "PbPb 0-30 %");
    easyLeg(legend[1], "PbPb 30-100 %");
    easyLeg(legend[4], "PbPb 0-10 %");
    easyLeg(legend[5], "PbPb 10-30 %");
    easyLeg(legend[6], "PbPb 30-50 %");
    easyLeg(legend[7], "PbPb 50-100 %");
    
    TLegend *ly = new TLegend(0.4913112,0.6561548,0.9997611,0.9431145,NULL,"brNDC");
    
    TCanvas* c1 = new TCanvas("c1", "", 1200,600);
    c1 -> Divide(4,2);
    for(int i=0; i<=7; i++){
        if(i==2){
            c1 -> cd(i+1);
            ly -> SetBorderSize(0);
            ly -> SetFillColor(0);
            ly -> AddEntry(oldH[0],"old forest & old skim","p");        
            ly -> AddEntry(OFNSH[0],"old forest & new skim","p");        
            ly -> AddEntry(recentH[0],"new forest & new skim","p");        
            ly -> Draw();
        }
        if(i!=2 && i!=3){
            //       c[i] = new TCanvas(Form("c%d",i), "", 400,400);
     //       c[i] -> cd();
            c1 -> cd(i+1);

            TString aa = Form("resolutionHisto_old%d.root", i);
            oldFile[i] = new TFile(aa, "READ");
            oldH[i] = (TH1D*)oldFile[i] -> Get("hresol");
            oldH[i] -> SetMarkerColor(1); 
            oldF[i] = oldH[i] -> GetFunction("f");
            oldF[i] -> SetLineColor(1); 
            oldF[i] -> Draw();
            oldH[i] -> Draw("same");


            OFNSFile[i] = new TFile(Form("resolutionHisto_testOldForestWithNewSkim%d.root", i), "READ");
            OFNSH[i] = (TH1D*)OFNSFile[i] -> Get("hresol");
            //OFNSH[i] -> SetMarkerStyle(4);
            OFNSH[i] -> SetMarkerColor(2);
            OFNSF[i] = OFNSH[i] -> GetFunction("f");
            OFNSF[i] -> SetLineColor(2); 
            OFNSF[i] -> Draw("same");
            OFNSH[i] -> Draw("same");
            

            recentFile[i] = new TFile(Form("resolutionHisto_recent%d.root", i), "READ");
            recentH[i] = (TH1D*)recentFile[i] -> Get("hresol");
            recentH[i] -> SetMarkerColor(3);
            recentF[i] = recentH[i] -> GetFunction("f");
            recentF[i] -> SetLineColor(3); 
            recentF[i] -> Draw("same"); 
            recentH[i] -> Draw("same");
            
            legend[i] -> Draw("same");
           // outFile -> Write();
        }
    }
//
// comparing scales
//
    TH1D* oldH_scale[9];
    TH1D* recentH_scale[9];
    TH1D* OFNSH_scale[9];
    
    TCanvas* c2 = new TCanvas("c2", "", 1200,600);
    c2 -> Divide(4,2);
    for(int i=0; i<=7; i++){
        if(i==2){
            c2 -> cd(i+1);
            ly -> Draw();
        }
        if(i!=2 && i!=3){
            c2 -> cd(i+1);

            TString aa = Form("resolutionHisto_old%d.root", i);
            oldFile[i] = new TFile(aa, "READ");
            oldH_scale[i] = (TH1D*)oldFile[i] -> Get("hscale");
            oldH_scale[i] -> SetMarkerColor(1); 
            oldH_scale[i] -> Draw();


            OFNSFile[i] = new TFile(Form("resolutionHisto_testOldForestWithNewSkim%d.root", i), "READ");
            OFNSH_scale[i] = (TH1D*)OFNSFile[i] -> Get("hscale");
            OFNSH_scale[i] -> SetMarkerColor(2);
            OFNSH_scale[i] -> Draw("same");


            recentFile[i] = new TFile(Form("resolutionHisto_recent%d.root", i), "READ");
            recentH_scale[i] = (TH1D*)recentFile[i] -> Get("hscale");
            recentH_scale[i] -> SetMarkerColor(3);
            recentH_scale[i] -> Draw("same");

            legend[i] -> Draw("same");
            // outFile -> Write();
        }
    }
}
