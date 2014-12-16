#include "CutAndBinCollection2012.h"
#include <TRandom3.h>
#include <time.h>
#include <TStyle.h>
#include <iostream>

void onlyDataPtDependence(int xNorm = 1) { 
    gStyle -> SetOptStat(0); 
    //yeonju
    const int nCentBinPa = 3;
    double CentBinPa[nCentBinPa+1] = {0,20,30,100};
    double AveCentBin[nCentBinPa+1] = {10.0, 25.0, 65.0, 9999};

    const int nPt = 5;
    const int nFile = 5;
    double PtBinPa[nPt+1] = {40,50,60,80,120,9999};
    double AvePtBin[nPt+1] = {45.0, 55.0, 70.0, 100.0, 160.0};

    TH1D* hxjg[7][1000][20]; // [species][centrality][pt_dependence]
    TH1D* hxjgNorm[7][1000][20];
    TH1D* hdphi[7][1000][20];

    valPair totalmeanX[7][20];//not divided by centrality 
    valPair totalrjg[7][20];
    valPair meanX[7][1000][20];
    valPair rjg[7][1000][20];
    double temp_meanX[20];
    double temp_rjg[20];
    double temperr_meanX[20];
    double temperr_rjg[20];

    TGraphAsymmErrors* gr[7];
    TGraphAsymmErrors* gx[7];
    gr[1] = new TGraphAsymmErrors();
    gr[1]->SetName("gr_cent1");
    gr[2] = new TGraphAsymmErrors();
    gr[2]->SetName("gr_cent2");
    gr[3] = new TGraphAsymmErrors();
    gr[3]->SetName("gr_cent3");
    gx[1] = new TGraphAsymmErrors();
    gx[1]->SetName("gx_cent1");
    gx[2] = new TGraphAsymmErrors();
    gx[2]->SetName("gx_cent2");
    gx[3] = new TGraphAsymmErrors();
    gx[3]->SetName("gx_cent3");

    TFile* fff[7][1000][20];
    double rError[20];
    // cout << "ok!"<< endl;
    for ( int icent = 1 ; icent<=nCentBinPa  ; icent++) { 
        int iSpecies =kPADATA ; 

        int iglb = icent + iSpecies*50.;

        fff[iSpecies][iglb][1] = new TFile("forYeonJu/photonTrackCorr_ppbDATA_output_photonPtThr40_to_50_jetPtThr30_20130815.root");
        fff[iSpecies][iglb][2] = new TFile("forYeonJu/photonTrackCorr_ppbDATA_output_photonPtThr50_to_60_jetPtThr30_20130815.root");
        fff[iSpecies][iglb][3] = new TFile("forYeonJu/photonTrackCorr_ppbDATA_output_photonPtThr60_to_80_jetPtThr30_20130815.root");
        fff[iSpecies][iglb][4] = new TFile("forYeonJu/photonTrackCorr_ppbDATA_output_photonPtThr80_to_120_jetPtThr30_20130815.root");
        fff[iSpecies][iglb][5] = new TFile("forYeonJu/photonTrackCorr_ppbDATA_output_photonPtThr120_to_9999_jetPtThr30_20130815.root");
 /*       fff[iSpecies][iglb][6] = new TFile("forYeonJu/photonTrackCorr_ppbMC_output_photonPtThr40_to_50_jetPtThr30_20130815.root");
        fff[iSpecies][iglb][7] = new TFile("forYeonJu/photonTrackCorr_ppbMC_output_photonPtThr50_to_60_jetPtThr30_20130815.root");
        fff[iSpecies][iglb][8] = new TFile("forYeonJu/photonTrackCorr_ppbMC_output_photonPtThr60_to_80_jetPtThr30_20130815.root");
        fff[iSpecies][iglb][9] = new TFile("forYeonJu/photonTrackCorr_ppbMC_output_photonPtThr80_to_120_jetPtThr30_20130815.root");
        fff[iSpecies][iglb][10] = new TFile("forYeonJu/photonTrackCorr_ppbMC_output_photonPtThr120_to_9999_jetPtThr30_20130815.root");
   */             cout << "fffff" << endl;
        for(int j = 1; j <= nFile ; j++){
            hdphi[iSpecies][iglb][j] = (TH1D*)fff[iSpecies][iglb][j]->Get(Form("jetDphi_icent%d_final",icent));
            cout << "hdphi" <<endl;
            hxjg[iSpecies][iglb][j] = (TH1D*)fff[iSpecies][iglb][j]->Get(Form("xjg_icent%d_final",icent));
           // hxjgNorm[iSpecies][iglb][j] = (TH1D*)hxjg[iSpecies][iglb][j]->Clone(Form("norm_%s",hxjg[iSpecies][iglb][j]->GetName()) );

            cout << "meanX" <<endl;
            meanX[iSpecies][iglb][j].val = hxjg[iSpecies][iglb][j]->GetMean();
            meanX[iSpecies][iglb][j].err = hxjg[iSpecies][iglb][j]->GetMeanError();
            cout << "rjg" <<endl;
            rjg[iSpecies][iglb][j].val = hxjg[iSpecies][iglb][j]->IntegralAndError(1, hxjg[iSpecies][iglb][j]->GetNbinsX(), rError[j], "width");
            rjg[iSpecies][iglb][j].err = rError[j];
        }
    }

    int iSpecies =kPADATA ; 
    
    for(int icent =1 ; icent<=nCentBinPa ; icent++){
        
        int iglb = icent + iSpecies*50.;
        for(int ipt=1; ipt<=nPt; ipt++){
            gx[icent]->SetPoint     (ipt, AvePtBin[ipt-1], meanX[iSpecies][iglb][ipt].val);
            gx[icent]->SetPointError(ipt, 0.01, 0.01, meanX[iSpecies][iglb][ipt].err, meanX[iSpecies][iglb][ipt].err);
            gr[icent]->SetPoint     (ipt, AvePtBin[ipt-1], rjg[iSpecies][iglb][ipt].val);
            gr[icent]->SetPointError(ipt, 0.01, 0.01, rjg[iSpecies][iglb][ipt].err, rjg[iSpecies][iglb][ipt].err);
        }
    }


   
    //
   //for no central dependence.
   //
    /*
    for(int j=1; j<=nFile;j++){
        for(int icent =1 ; icent<=nCentBinPa ; icent++){
          //  cout << "loop!!" << endl;
            int iglb = icent + iSpecies*50.;
            if(icent==1) {
         //       cout << " icent loop " << endl;
                totalmeanX[iSpecies][j].val = 0.0;
                totalmeanX[iSpecies][j].err = 0.0;
                totalrjg[iSpecies][j].val = 0.0;
                totalrjg[iSpecies][j].err = 0.0;
                temp_meanX[j] = 0.0;
                temperr_meanX[j] = 0.0;
                temp_rjg[j] = 0.0;
                temperr_rjg[j] = 0.0;
            }
       //     cout << "icent loop calcul." << endl;
            temp_meanX[j] += meanX[iSpecies][iglb][j].val;
            temperr_meanX[j] += (meanX[iSpecies][iglb][j].err)*(meanX[iSpecies][iglb][j].err);
            temp_rjg[j] += rjg[iSpecies][iglb][j].val;
            temperr_rjg[j] += (rjg[iSpecies][iglb][j].err)*(rjg[iSpecies][iglb][j].err);
    
        cout << j << " th,  " << icent << " th : " <<meanX[iSpecies][iglb][j].val << "   , " << rjg[iSpecies][iglb][j].val << endl;
        }
     //   cout << "loop end " << endl;
        totalmeanX[iSpecies][j].err = sqrt(temperr_meanX[j]);
        totalmeanX[iSpecies][j].val = (temp_meanX[j])/3.0;
        totalrjg[iSpecies][j].err = sqrt(temperr_rjg[j]);
        totalrjg[iSpecies][j].val = (temp_rjg[j])/3.0;

        cout << "total!!! " <<j << " th  : " <<totalmeanX[iSpecies][j].val << "   , " << totalrjg[iSpecies][j].val << endl;
        cout << "temp!!! " << j << " th  : " << temp_meanX[j] << "   , " << temp_rjg[j] << endl;
        if(j<=5){ // data
   //         cout << "gx" << endl;
            gx[1]->SetPoint     (j, AvePtBin[j-1], totalmeanX[iSpecies][j].val);
            gx[1]->SetPointError(j, 0.01, 0.01, totalmeanX[iSpecies][j].err, totalmeanX[iSpecies][j].err);
            gr[1]->SetPoint     (j, AvePtBin[j-1], totalrjg[iSpecies][j].val);
            gr[1]->SetPointError(j, 0.01, 0.01, totalrjg[iSpecies][j].err, totalrjg[iSpecies][j].err);
        } else { // MC
            gx[2]->SetPoint     (j-5, AvePtBin[j-6], totalmeanX[iSpecies][j].val);
            gx[2]->SetPointError(j-5, 0.01, 0.01, totalmeanX[iSpecies][j].err, totalmeanX[iSpecies][j].err);
            gr[2]->SetPoint     (j-5, AvePtBin[j-6], totalrjg[iSpecies][j].val);
            gr[2]->SetPointError(j-5, 0.01, 0.01, totalrjg[iSpecies][j].err, totalrjg[iSpecies][j].err);
        }
    }
    */
    TCanvas* c2 = new TCanvas("c2","",800,400);
    c2->Divide(2,1);

    TH1D* hr[15];
    TH1D* hx[15];
    //  for(int j=1; j<=nFile ; j++){
    c2->cd(2);
    int j = 2;
    hr[j] = new TH1D(Form("hr%d",j),";pT of photon (GeV);r_{J,#gamma}",200,30,200);
    handsomeTH1(hr[j],j+1);
    hr[j]->SetAxisRange(0.01,1.1,"Y");
    hr[j]->Draw();

    handsomeTGraph(gr[1],2);
    gr[1]->SetMarkerStyle(25);
    gr[1]->SetMarkerSize(1);
    gr[1]->Draw("same p");
    handsomeTGraph(gr[2],2);
    gr[2]->SetMarkerStyle(24);
    gr[2]->SetMarkerSize(1);
    gr[2]->Draw("same p");
    handsomeTGraph(gr[3],2);
    gr[3]->SetMarkerStyle(20);
    gr[3]->SetMarkerSize(1);
    gr[3]->Draw("same p");
    jumSun(30,1,200,1);

    c2->cd(1);
    j=1;
    hx[j] = (TH1D*)hr[2]->Clone(Form("hx%d",j));
    handsomeTH1(hx[j],j+1);
    hx[j]->SetYTitle("<x_{J,#gamma}>");
    hx[j]->SetAxisRange(0.6,1.05,"Y");
    //  hx->SetNdivisions(5);
    hx[j]->Draw();
    handsomeTGraph(gx[1],2);
    gx[1]->SetMarkerStyle(25);
    gx[1]->SetMarkerSize(1);
    gx[1]->Draw("same p");
    handsomeTGraph(gx[2],2);
    gx[2]->SetMarkerStyle(24);
    gx[2]->SetMarkerSize(1);
    gx[2]->Draw("same p");
    handsomeTGraph(gx[3],2);
    gx[3]->SetMarkerStyle(20);
    gx[3]->SetMarkerSize(1);
    gx[3]->Draw("same p");
    jumSun(30,1,200,1);
    gStyle -> SetEndErrorSize(0);
    c2 -> SaveAs("x_Jgamma_0815.gif");
   
    TLegend *l1=   new TLegend(0.5226071,0.6300415,0.9597724,0.8332584,NULL,"brNDC");
    easyLeg(l1,"2.76TeV");
  //  l1->AddEntry(gr[kPPDATA],"pp ","p");
    l1->AddEntry(gx[1],"pPb 0 GeV < E_{T}^{HF|#eta|>4} < 20 GeV","p");
    l1->AddEntry(gx[2],"pPb 20 GeV < E_{T}^{HF|#eta|>4} < 30 GeV","p");
    l1->AddEntry(gx[3],"pPb 30 GeV < E_{T}^{HF|#eta|>4} < 100 GeV","p");
    l1->Draw();

}

