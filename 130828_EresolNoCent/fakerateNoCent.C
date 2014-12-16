// yeonju find fake rate.
//
#include "../HiForestAnalysis/hiForest.h"
#include "../gammaJetAnalysis/CutAndBinCollection2012.h"
#include <TStyle.h>
#include <TH1D.h>
#include <TTree.h>
#include <TFile.h>
#include <iostream>
#include <TCanvas.h>
#include <TF1.h>
#include <TGraphAsymmErrors.h>
#include <TLegend.h>

using namespace std;
void fakerateNoCent(){
    gStyle->SetOptFit(1011);
    gStyle -> SetOptStat(0);
    gStyle -> SetTitleYOffset(1.35);
    gStyle -> SetTitleYSize(0.04);
    TFile* readFile = new TFile("yskim_merged_allQCDPhoton_CMSSW538HIp2.root" ,"READ");

    const int nPtBin = 4;
    double ptBin[nPtBin+1] = {30.0, 40.0, 50.0, 80.0, 9999.0}; 
    double AvePtBin[nPtBin+1] = { 35.0, 45.0, 65.0, 100.0};
    
    const int nEtaBin = 3;
    double EtaBinPa[nEtaBinPa+1] = {0,0.5,1.0,1.6};
   
    const int nCentBin = 3;
    double centBinPa[nCentBinPa+1] = {0,20,30,100};
    //
    // fake rate
    //
    int nJetmax = 10;
    float refPt[nJetmax], refPartonFlv[nJetmax], pt[nJetmax], dphi[nJetmax], eta[nJetmax];
    int nJet;
    TTree* yJet = (TTree*) readFile -> Get("yJet");
    yJet -> SetBranchAddress("refPt", refPt);
    yJet -> SetBranchAddress("nJet", &nJet);
    yJet -> SetBranchAddress("refPartonFlv", refPartonFlv);
    yJet -> SetBranchAddress("pt", pt);
    yJet -> SetBranchAddress("dphi", dphi);
    yJet -> SetBranchStyle(1);

//    TTree* tgj = (TTree*) readFile -> Get("tgj");
    yJet -> AddFriend("tgj");

    double realjet[nCentBin+5][nPtBin+5][nEtaBin+5];
    double totaljet[nCentBin+5][nPtBin+5][nEtaBin+5];
    double fakerate[nCentBin+5][nPtBin+5][nEtaBin+5];

    //    for (int icent = 1 ; icent <= nCentBinPa ; icent++){
    int icent = 1;    
    for (int i = 0; i<nPtBin ; i++){
        for(int jeta = 0; jeta<nEtaBin; jeta++){
            realjet[icent][i][jeta]=0.0;
            totaljet[icent][i][jeta]=0.0;
            fakerate[icent][i][jeta]=0.0;

            int entries = yJet -> GetEntries();
            for(int k=0; k<entries; k++){
                yJet -> GetEntry(k);
                if(Form("refPt > 0 && (pt > %d && pt < %d) && dphi > 7*3.141592/8.0 && (abs(eta) > %f abs(eta) < %f)", (int)ptBin[i], (int)ptBin[i+1]), (float)EtaBinPa[jeta], (float)EtaBinPa[jeta+1]){
                    for(int j=0; j<nJet; j++){
                        if(refPt[j] > 0.0) realjet[icent][i][jeta] += 1.0; 
                        totaljet[icent][i][jeta] += 1.0;
                    }
                }
            }
            fakerate[icent][i][jeta] = 1.0 - realjet[icent][i][jeta]/totaljet[icent][i][jeta];
        }
    }
    // }

    TCanvas* c_fake = new TCanvas("c_fake", "fake rate", 350, 300); 
    TH1D* h_fake = new TH1D("h_fake",";JetP_{T} (GeV); Fake Rate ",500,20,120);
    h_fake -> SetAxisRange(-0.02, 0.105, "Y");
    h_fake -> GetYaxis()->CenterTitle();
    c_fake -> cd();
    h_fake -> Draw();
    //  jumSun(20,1,120,1);

    TGraphAsymmErrors* gfake[nCentBin+5][nEtaBin+5];
    for(int icent=0; icent<nCentBin; icent++){
        for(int jeta=0; jeta<nEtaBin; jeta++){
            gfake[icent][jeta] = new TGraphAsymmErrors();
        }
    }

    TLegend *lfake=new TLegend(0.40,0.80,0.85,0.62);
    lfake->SetTextFont(42);
    lfake->SetTextSize(0.04);
    lfake->SetFillColor(0);
    lfake->SetLineColor(0);

    //    for(int icent=1; icent <= nCentBinPa ; icent++){
    for(int i=0; i < nPtBin ; i++){ 
        for(int jeta=0; jeta< nEtaBin; jeta++){
            gfake[icent][jeta] -> SetPoint(i+1, AvePtBin[i], fakerate[icent][i][jeta]);
            //  g[icent] -> SetPointError(i+1, 0.001,0.001, var[icent][i], var[icent][i]);
            gfake[icent][jeta] -> SetMarkerStyle(20);
            gfake[icent][jeta] -> SetMarkerSize(1);
            gfake[icent][jeta] -> SetMarkerColor(icent);
            gfake[icent][jeta] -> Draw("same p");
        }
        lfake->AddEntry(gfake[icent][jeta], "pp", "p"); 
    }
    //  }
    //    lfake-> Draw();
    //  c_fake -> Update();
/*
    TCanvas* c_Eresol = new TCanvas("c_Eresol", "Energy Scale with all pt", 400, 300); 
    c1 -> cd();

    TH1D* jetEscale = new TH1D("jetEscale" , ";recoPt/genPt", 100, 0, 2);
    yJet -> Draw("pt/refPt >> jetEscale" , "refPt>0 && refPartonFlv >-100");
    jetEscale -> Draw();

    cleverGaus(jetEscale);
    
       TF1* f1 = new TF1("f1", "gaus", 1.0, 1.06);
       jetEscale -> Fit("f1");
       f1 -> Draw("same");
       gStyle -> SetOptStat(0); 
    
    */
    
  /*  TCanvas* c2 = new TCanvas("c2", "pt/refPt distribution", 1200, 900); 
    c2 -> Divide(4,3);
*/

    TH1D* Escale[nCentBin+5][nPtBin+5][nEtaBin+5];
    double mean[nCentBin+5][nPtBin+5][nEtaBin+5], var[nCentBin+5][nPtBin+5][nEtaBin+5], resol[nCentBin+5][nPtBin+5][nEtaBin+5], resolVar[nCentBin+5][nPtBin+5][nEtaBin+5];
    // for(int icent=1; icent <= nCentBinPa ; icent++){
    for(int jeta=1;jeta <=nEtaBin;jeta++){
        for(int i=0; i < nPtBin ; i++){
         //   c2 -> cd((icent-1)*4+i+1);
            Escale[icent][i] = new TH1D(Form("Escale_cent%d_pt%d_eta%d",icent, i, jeta) , " ;  Energy Scale ", 100, 0, 2);
            yJet -> Draw(Form("pt/refPt >> Escale_cent%d_pt%d_eta%d",icent, i, jeta) , Form("((refPt>0 && (pt > %d && pt < %d) && (abs(eta) < %f && abs(eta) > %f)", (int)ptBin[i], (int)ptBin[i+1]), (float)EtaBin[jeta], (float)EtaBin[jeta]);
         //   Escale[icent][i][jeta] -> Draw(); 
         //   cleverGaus(Escale[icent][i][jeta]);

            mean[icent][i][jeta] = Escale[icent][i][jeta] -> GetMean();
            var[icent][i][jeta] = Escale[icent][i][jeta] -> GetMeanError();
            resol[icent][i][jeta] = Escale[icent][i][jeta] -> GetRMS();
            resolVar[icent][i][jeta] = Escale[icent][i][jeta] -> GetRMSError();
        }
    }
    //  }
    
    // c2 -> Update();
    
    //
    // Energy Scale
    //

    TCanvas* c_scale = new TCanvas("c_scale", "Energy Scale vs. jet pt", 350, 300); 
    TH1D* h = new TH1D("h",";JetP_{T} (GeV); Energy Scale ",500,20,120);
    h -> SetAxisRange(0.90, 1.08, "Y");
    h -> GetYaxis()->CenterTitle();
    c3 -> cd();
    h -> Draw();
    jumSun(20,1,120,1);

    TGraphAsymmErrors* g_scale[nCentBin+5][nEtaBin+5];
    for(int icent=0; icent<nCentBin; icent++){
        for(int jeta=0; jeta<nEtaBin; jeta++){
            g_scale[icent][jeta] = new TGraphAsymmErrors();
        }
    }
    
    TLegend *l3=new TLegend(0.40,0.20,0.85,0.42);
    l3->SetTextFont(42);
    l3->SetTextSize(0.04);
    l3->SetFillColor(0);
    l3->SetLineColor(0);


    //    for(int icent=1; icent <= nCentBin ; icent++){
    for(int jeta=1;jeta<=nEtaBin;jeta++){
        for(int i=0; i < nPtBin ; i++){ 
        g[icent][jeta] -> SetPoint(i+1, AvePtBin[i], mean[icent][i][jeta]);
        g[icent][jeta] -> SetPointError(i+1, 0.001,0.001, var[icent][i][jeta], var[icent][i][jeta]);
        g[icent][jeta] -> SetMarkerStyle(20);
        g[icent][jeta] -> SetMarkerSize(1);
        g[icent][jeta] -> SetMarkerColor(icent);
        g[icent][jeta] -> Draw("same p");
    }
    l3->AddEntry(g[icent][jeta], "pp", "p"); 
    }
    //  }
//    l3 -> Draw();
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

    //    for(int icent=1; icent <= nCentBinPa ; icent++){
    for(int i=0; i < nPtBin ; i++){ 
        cout << "resol : " << resol[icent][i] << ", resolVar : " << resolVar[icent][i]<< endl;
        gResol[icent] -> SetPoint(i+1, AvePtBin[i], resol[icent][i]);
        gResol[icent] -> SetPointError(i+1, 0.001,0.001, resolVar[icent][i], resolVar[icent][i]);
        gResol[icent] -> SetMarkerStyle(20);
        gResol[icent] -> SetMarkerSize(1);
        gResol[icent] -> SetMarkerColor(icent);
        gResol[icent] -> Draw("same p");
    }
    l_resol->AddEntry(gResol[icent], "pp", "p"); 
    //  }
//    l_resol->Draw();
    c_resol -> Update();

    c1 -> SaveAs(".gif");
    c2 -> SaveAs(".gif");
    c3 -> SaveAs(".gif");
    c_fake -> SaveAs(".gif");
    c_resol -> SaveAs(".gif");
}
