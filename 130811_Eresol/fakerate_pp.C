// yeonju find fake rate.
//
#include "CutAndBinCollection2012.h"
#include <TStyle.h>
#include <TH1D.h>
#include <TTree.h>
#include <TFile.h>
#include <iostream>
#include <TCanvas.h>
#include <TF1.h>
#include <TGraphAsymmErrors.h>
#include <TLegend.h>

void fakerate(){
    gStyle->SetOptFit(1011);
    gStyle -> SetOptStat(0);
    gStyle -> SetTitleYOffset(1.35);
    gStyle -> SetTitleYSize(0.04);
    TFile* readFile = new TFile("output.root" ,"READ");
    
    const int nPtBin = 4;
    double ptBin[nPtBin+1] = {30.0, 40.0, 50.0, 80.0, 9999.0}; 
    double AvePtBin[nPtBin+1] = { 35.0, 45.0, 65.0, 100.0};

    const int nCentBinPa = 3;
    double centBinPa[nCentBinPa+1] = {0,20,30,100};
//
// fake rate
//
    int nJetmax = 10;
    float refPt[nJetmax];
    int nJet;
    TTree* yJet = (TTree*) readFile -> Get("yJet");
    yJet -> SetBranchAddress("refPt", &refPt);
    yJet -> SetBranchAddress("nJet", &nJet);
    yJet -> SetBranchStyle(1);

    TTree* tgj = (TTree*) readFile -> Get("tgj");
    yJet -> AddFriend("tgj");

    double realjet[nCentBinPa+5][nPtBin];
    double totaljet[nCentBinPa+5][nPtBin];
    double fakerate[nCentBinPa+5][nPtBin];

    for (int icent = 1 ; icent <= nCentBinPa ; icent++){
        for (int i = 0; i<nPtBin ; i++){
            realjet[icent][i]=0.0;
            totaljet[icent][i]=0.0;
            fakerate[icent][i]=0.0;
            TTree* tempTree = yJet -> CopyTree(Form("refPartonFlv >-100 && (pt >= %d && pt < %d) && (hf4Sum > %f && hf4Sum <= %f)", (int)ptBin[i], (int)ptBin[i+1], (float)centBinPa[icent-1], (float)centBinPa[icent]));
            int entries = tempTree -> GetEntries();
            for(int k=0; k<entries; k++){
                tempTree -> GetEntry(k);
                for(int j=0; j<nJet; j++){
                    if(refPt[j] > 0.0) realjet[icent][i] += 1.0; 
                    totaljet[icent][i] += 1.0;
                }
            }
            delete tempTree;
            fakerate[icent][i] = 1.0 - realjet[icent][i]/totaljet[icent][i];
        }
    }

    TCanvas* c_fake = new TCanvas("c_fake", "fake rate", 400, 300); 
    TH1D* h_fake = new TH1D("h_fake",";JetP_{T} (GeV); Fake Rate ",500,20,120);
    h_fake -> SetAxisRange(-0.02, 0.105, "Y");
    c_fake -> cd();
    h_fake -> Draw();
  //  jumSun(20,1,120,1);

    TGraphAsymmErrors* gfake[nCentBinPa+5];
    gfake[1] = new TGraphAsymmErrors();
    gfake[2] = new TGraphAsymmErrors();
    gfake[3] = new TGraphAsymmErrors();
    TLegend *lfake=new TLegend(0.40,0.80,0.85,0.62);
    lfake->SetTextFont(42);
    lfake->SetTextSize(0.04);
    lfake->SetFillColor(0);
    lfake->SetLineColor(0);

    for(int icent=1; icent <= nCentBinPa ; icent++){
        for(int i=0; i < nPtBin ; i++){ 
            gfake[icent] -> SetPoint(i+1, AvePtBin[i], fakerate[icent][i]);
            //  g[icent] -> SetPointError(i+1, 0.001,0.001, var[icent][i], var[icent][i]);
            gfake[icent] -> SetMarkerStyle(24);
            gfake[icent] -> SetMarkerSize(1);
            gfake[icent] -> SetMarkerColor(icent);
            gfake[icent] -> Draw("same p");
        }
        lfake->AddEntry(gfake[icent], Form("%d GeV < E_{T}^{HF|#eta|>4} < %d GeV", (int)centBinPa[icent-1], (int)centBinPa[icent]), "p"); 
    }
    lfake-> Draw();
    c_fake -> Update();

    TCanvas* c1 = new TCanvas("c1", "Energy Scale with all pt", 400, 300); 
    c1 -> cd();

    TH1D* jetEscale = new TH1D("jetEscale" , ";recoPt/genPt", 100, 0, 2);
    yJet -> Draw("pt/refPt >> jetEscale" , "refPt>0 && refPartonFlv >-100");
    jetEscale -> Draw();

    cleverGaus(jetEscale);
    /*
       TF1* f1 = new TF1("f1", "gaus", 1.0, 1.06);
       jetEscale -> Fit("f1");
       f1 -> Draw("same");
       gStyle -> SetOptStat(0); 
       */
    TCanvas* c2 = new TCanvas("c2", "pt/refPt distribution", 1200, 900); 
    c2 -> Divide(4,3);


    TH1D* Escale[nCentBinPa+5][nPtBin];
    double mean[nCentBinPa+5][nPtBin], var[nCentBinPa+5][nPtBin], resol[nCentBinPa+5][nPtBin], resolVar[nCentBinPa+5][nPtBin];
    for(int icent=1; icent <= nCentBinPa ; icent++){
        for(int i=0; i < nPtBin ; i++){
            c2 -> cd((icent-1)*4+i+1);
            Escale[icent][i] = new TH1D(Form("Escale%d_%d",icent, i) , " ;  Energy Scale ", 100, 0, 2);
            yJet -> Draw(Form("pt/refPt >> Escale%d_%d",icent,i) , Form("refPartonFlv >-100 && (pt >= %d && pt < %d) && (hf4Sum > %f && hf4Sum <= %f) ", (int)ptBin[i], (int)ptBin[i+1], (float)centBinPa[icent-1], (float)centBinPa[icent]));
            Escale[icent][i] -> Draw(); 
            cleverGaus(Escale[icent][i]);

            mean[icent][i] = Escale[icent][i] -> GetMean();
            var[icent][i] = Escale[icent][i] -> GetMeanError();
            resol[icent][i] = Escale[icent][i] -> GetRMS();
            resolVar[icent][i] = Escale[icent][i] -> GetRMSError();
        }
    }
    c2 -> Update();
    //
    // Energy Scale
    //

    TCanvas* c3 = new TCanvas("c3", "Energy Scale vs. jet pt", 400, 300); 
    TH1D* h = new TH1D("h",";JetP_{T} (GeV); Energy Scale ",500,20,120);
    h -> SetAxisRange(0.94, 1.05, "Y");
    c3 -> cd();
    h -> Draw();
    jumSun(20,1,120,1);

    TGraphAsymmErrors* g[nCentBinPa+5];
    g[1] = new TGraphAsymmErrors();
    g[2] = new TGraphAsymmErrors();
    g[3] = new TGraphAsymmErrors();
    TLegend *l3=new TLegend(0.40,0.20,0.85,0.42);
    l3->SetTextFont(42);
    l3->SetTextSize(0.04);
    l3->SetFillColor(0);
    l3->SetLineColor(0);


    for(int icent=1; icent <= nCentBinPa ; icent++){
        for(int i=0; i < nPtBin ; i++){ 
            g[icent] -> SetPoint(i+1, AvePtBin[i], mean[icent][i]);
            g[icent] -> SetPointError(i+1, 0.001,0.001, var[icent][i], var[icent][i]);
            g[icent] -> SetMarkerStyle(24);
            g[icent] -> SetMarkerSize(1);
            g[icent] -> SetMarkerColor(icent);
            g[icent] -> Draw("same p");
        }
        l3->AddEntry(g[icent], Form("%d GeV < E_{T}^{HF|#eta|>4} < %d GeV", (int)centBinPa[icent-1], (int)centBinPa[icent]), "p"); 
    }
    l3 -> Draw();
    c3 -> Update();

    //
    // Energy Resolution
    //

    TCanvas* c_resol = new TCanvas("c_resol", "Energy Resolution vs. jet pt", 400, 300); 
    TH1D* h_resol = new TH1D("h_resol",";JetP_{T} (GeV); Energy Resolution (GeV) ",500,20,120);
    h_resol -> SetAxisRange(0.0, 0.2, "Y");
    h_resol->GetYaxis()->CenterTitle();
    c_resol -> cd();
    h_resol -> Draw();
    jumSun(0,1,120,1);
    TGraphAsymmErrors* gResol[nCentBinPa+5];
    gResol[1] = new TGraphAsymmErrors();
    gResol[2] = new TGraphAsymmErrors();
    gResol[3] = new TGraphAsymmErrors();

    TLegend *l_resol=new TLegend(0.40,0.20,0.85,0.42);
    l_resol->SetTextFont(42);
    l_resol->SetTextSize(0.04);
    l_resol->SetFillColor(0);
    l_resol->SetLineColor(0);

    for(int icent=1; icent <= nCentBinPa ; icent++){
        for(int i=0; i < nPtBin ; i++){ 
            cout << "resol : " << resol[icent][i] << ", resolVar : " << resolVar[icent][i]<< endl;
            gResol[icent] -> SetPoint(i+1, AvePtBin[i], resol[icent][i]);
            gResol[icent] -> SetPointError(i+1, 0.001,0.001, resolVar[icent][i], resolVar[icent][i]);
            gResol[icent] -> SetMarkerStyle(24);
            gResol[icent] -> SetMarkerSize(1);
            gResol[icent] -> SetMarkerColor(icent);
            gResol[icent] -> Draw("same p");
        }
        l_resol->AddEntry(gResol[icent], Form("%d GeV < E_{T}^{HF|#eta|>4} < %d GeV", (int)centBinPa[icent-1], (int)centBinPa[icent]), "p"); 
    }
    l_resol->Draw();
    c_resol -> Update();

    c1 -> SaveAs(".gif");
    c2 -> SaveAs(".gif");
    c3 -> SaveAs(".gif");
    c_fake -> SaveAs(".gif");
    c_resol -> SaveAs(".gif");
}
