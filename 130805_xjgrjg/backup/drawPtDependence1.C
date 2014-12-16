#include "CutAndBinCollection2012.h"
#include <TRandom3.h>
#include <time.h>


void drawPtDependence1() {
  
  const int nPtBin = 4;
  double ptBin[nPtBin+1] = {50,60,80,120,9999}; 
  
  TH1D* hxjg[7][1000]; // [species][centrality] 
  TH1D* hxjgNorm[7][1000];
  valPair meanX[7][1000];
  valPair rjg[7][1000];
  TGraphAsymmErrors* gr[7];
  TGraphAsymmErrors* gx[7];
  for (int i=0;i<7;i++) {  
    gr[i] = new TGraphAsymmErrors();
    gr[i]->SetName(Form("gr_%d",i));
    gx[i] = new TGraphAsymmErrors();
    gx[i]->SetName(Form("gx_%d",i));
  }
  TFile* fff[7][1000];
  
  for ( int ipt = 0 ; ipt<nPtBin  ; ipt++) { 
    int iSpecies = kPPDATA;
    int iglb = ipt + iSpecies*50.;
    int icent = 7;
    fff[iSpecies][iglb] = new TFile(Form("ffFiles/photonTrackCorr_ppDATA_output_photonPtThr%d_to_%d_jetPtThr30_20130723_genLevel0_qnch0.root",(int)ptBin[ipt],(int)ptBin[ipt+1]));
    cout << Form("ffFiles/photonTrackCorr_ppDATA_output_photonPtThr%d_to_%d_jetPtThr30_20130723_genLevel0_qnch0.root", (int)ptBin[ipt],(int)ptBin[ipt+1]) << endl;
    hxjg[iSpecies][iglb] = (TH1D*)fff[iSpecies][iglb]->Get(Form("jetXjg_icent%d_final",icent));
    hxjgNorm[iSpecies][iglb] = (TH1D*)hxjg[iSpecies][iglb]->Clone(Form("norm_%s",hxjg[iSpecies][iglb]->GetName()) );

    meanX[iSpecies][iglb].val = hxjg[iSpecies][iglb]->GetMean();
    meanX[iSpecies][iglb].err = hxjg[iSpecies][iglb]->GetMeanError();
    gx[iSpecies]->SetPoint     (ipt+1, ptBin[ipt], meanX[iSpecies][iglb].val);
    gx[iSpecies]->SetPointError(ipt+1, 0.001,0.001, meanX[iSpecies][iglb].err, meanX[iSpecies][iglb].err);
    
    double rError;
    rjg[iSpecies][iglb].val = hxjg[iSpecies][iglb]->IntegralAndError(1, hxjg[iSpecies][iglb]->GetNbinsX(), rError, "width");
    rjg[iSpecies][iglb].err = rError;
    gr[iSpecies]->SetPoint     (ipt+1, ptBin[ipt], rjg[iSpecies][iglb].val);
    gr[iSpecies]->SetPointError(ipt+1, 0.001,0.001, rjg[iSpecies][iglb].err, rjg[iSpecies][iglb].err);
    
  }
  
  TCanvas* c1 = new TCanvas("c1","",1200,350);
  makeMultiPanelCanvas(c1,nPtBin,1,0.0,0.0,0.2,0.15,0.02);
  for ( int ipt = 0 ; ipt<nPtBin  ; ipt++) {
    c1->cd(ipt+1);
    int iSpecies = kPPDATA;
    int iglb = ipt + iSpecies*50.;
    handsomeTH1(hxjgNorm[iSpecies][iglb],ycolor[ipt+1]);
    scaleInt(hxjgNorm[iSpecies][iglb]);
    hxjgNorm[iSpecies][iglb]->Rebin(10);
    hxjgNorm[iSpecies][iglb]->SetXTitle("x_{J,#gamma}");
    hxjgNorm[iSpecies][iglb]->SetAxisRange(-0.03,0.3,"Y");
    hxjgNorm[iSpecies][iglb]->Draw();
    jumSun(1,0,1,0.25);
    onSun(meanX[iSpecies][iglb].val - meanX[iSpecies][iglb].err, 0, meanX[iSpecies][iglb].val+meanX[iSpecies][iglb].err,0,ycolor[ipt+1],2);
  }
  
   
  TCanvas* c2 = new TCanvas("c2","",500,500);
  TH1D* hr = new TH1D("hr",";p_{T}^{#gamma};r_{J,#gamma}",200,35,140);
  handsomeTH1(hr,1);
  hr->SetAxisRange(0.37,1.1,"Y");
  //  hr->SetNdivisions(5);
  hr->Draw();
  if ( 1==1) 
    {
      int iSpecies = kPPDATA;
      gr[kHIDATA]->SetMarkerColor(1);
      gr[kHIDATA]->SetLineColor(1);
      gr[iSpecies]->Draw("same p");
      jumSun(35,1,140,1);
   }
  TCanvas* c3 = new TCanvas("c3","",500,500);
  TH1D* hx = (TH1D*)hr->Clone("hx");
  handsomeTH1(hx,1);
  hx->SetYTitle("<x_{J,#gamma}>");
  hx->SetAxisRange(0.6,1.1,"Y");
  //  hx->SetNdivisions(5);
  hx->Draw();
  if ( 1==1) 
    {
      int iSpecies = kPPDATA;
      gx[kHIDATA]->SetMarkerColor(1);
      gx[kHIDATA]->SetLineColor(1);
      gx[iSpecies]->Draw("same p");
      jumSun(35,1,140,1);
    }  
}
