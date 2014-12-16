#include "CutAndBinCollection2012.h"
#include <TRandom3.h>
#include <time.h>

void drawDphi();

void drawThesisFigures() {
  
  drawDphi();
}

void drawDphi() { 
  
  TH1D* hdphi[5][5]; // [species][centrality] 
  TH1D* hxjg[5][5]; // [species][centrality] 
  TH1D* hxjgNorm[5][5];
  TFile* fff[5];
  
  fff[kHIDATA] = new TFile("ffFiles/photonTrackCorr_pbpbDATA_output_photonPtThr60_jetPtThr30_20130210_genLevel0.root");
  for ( int iSpecies =0 ; iSpecies<=5 ; iSpecies++) {
    if (iSpecies != kHIDATA)       continue;
    for ( int icent = 1 ; icent<=4 ; icent++) {
      hdphi[iSpecies][icent] = (TH1D*)fff[iSpecies]->Get(Form("jetDphi_icent%d_final",icent));
      hxjg[iSpecies][icent] = (TH1D*)fff[iSpecies]->Get(Form("jetXjg_icent%d_final",icent));
      hxjgNorm[iSpecies][icent] = (TH1D*)hxjg[iSpecies][icent]->Clone(Form("norm_%s",hxjg[iSpecies][icent]->GetName()));
      scaleInt(hxjgNorm[iSpecies][icent]);    
    }}
  
  fff[kHIMC]   = new TFile("ffFiles/photonTrackCorr_pbpbMC_output_photonPtThr60_jetPtThr30_20130210_genLevel0.root"); 
  for ( int iSpecies =0 ; iSpecies<=5 ; iSpecies++) {
    if (iSpecies != kHIMC)         continue;
    for ( int icent = 1 ; icent<=4 ; icent++) {
      hdphi[iSpecies][icent] = (TH1D*)fff[iSpecies]->Get(Form("jetDphi_icent%d_final",icent));
      hxjg[iSpecies][icent] = (TH1D*)fff[iSpecies]->Get(Form("jetXjg_icent%d_final",icent));
      hxjgNorm[iSpecies][icent] = (TH1D*)hxjg[iSpecies][icent]->Clone(Form("norm_%s",hxjg[iSpecies][icent]->GetName()));
      scaleInt(hxjgNorm[iSpecies][icent]);
    }}
  
  
  
  TCanvas* c1 = new TCanvas("c1","",1400,450);
  makeMultiPanelCanvas(c1,4,1,0.0,0.0,0.2,0.15,0.02);
  for ( int icent = 1 ; icent<=4 ; icent++) {
    c1->cd(5-icent);
    handsomeTH1(hdphi[kHIMC][icent],1);
    handsomeTH1(hdphi[kHIDATA][icent],2);
    hdphi[kHIMC][icent]->Scale(1./hdphi[kHIMC][icent]->Integral("width"));
    hdphi[kHIDATA][icent]->Scale(1./hdphi[kHIDATA][icent]->Integral("width"));
    hdphi[kHIMC][icent]->SetAxisRange(3.141592/3.,3.141592,"X");
    hdphi[kHIMC][icent]->SetAxisRange(0.01,5,"Y");
    hdphi[kHIMC][icent]->DrawCopy("hist");
    //  hdphi[kHIDATA][icent]->Draw("same");
    //    gPad->SetLogy();
    
    TF1 *fdphi = new TF1("fdphi","exp(-(TMath::Pi()-x)/[0]) / ([0]*(1-exp(-TMath::Pi()/[0]))) ",2.0*TMath::Pi()/3.0,TMath::Pi());
    fdphi->SetParName(0,"width");
    fdphi->SetParameter("width",0.22);
        
    float fitxmin=3.1415926*2./3;
    //    float fitxmin=2.5;
    hdphi[kHIMC][icent]->Fit("fdphi","0llm","",fitxmin,3.1415926);
    fdphi->SetLineWidth(1);
    fdphi->SetLineStyle(2);
    fdphi->SetLineColor(kBlue);
    float dphiWidth = fdphi->GetParameter("width");
    float dphiWidthErr = fdphi->GetParError(0);
    cout << " dphiWidth,dphiWidthErr = " << dphiWidth <<"   "<< dphiWidthErr << endl;
    fdphi->DrawCopy("same");
  }
  c1->SaveAs("pdfFiles/dPhi_MC_only.pdf");


  TCanvas* c2 = new TCanvas("c2","",1400,450);
  makeMultiPanelCanvas(c2,4,1,0.0,0.0,0.2,0.15,0.02);
  for ( int icent = 1 ; icent<=4 ; icent++) {
    c2->cd(5-icent);
    handsomeTH1(hxjgNorm[kHIMC][icent],1);
    handsomeTH1(hxjgNorm[kHIDATA][icent],2);
    hxjgNorm[kHIMC][icent]->SetAxisRange(-0.01,0.35,"Y");
    hxjgNorm[kHIMC][icent]->DrawCopy("");
    //    hxjgNorm[kHIDATA][5-icent]->Draw("same");
    int lowCent = centBin1[icent-1];    int highCent = centBin1[icent]-1;
    drawText(Form("%.0f%% - %.0f%%", float((float)lowCent*2.5), float((float)(highCent+1)*2.5)), 0.67,0.7,1);
  }
  TLegend *l12 = new TLegend(0.304355,0.755085,.8,0.9552542,NULL,"brNDC");
  easyLeg(l12,"p_{T}^{Jet}/p_{T}^{#gamma}");
  l12->AddEntry(hxjgNorm[kHIMC][1],"PYTHIA+HYDJET","pl");
  c2->cd(1);   l12->Draw();

  c2->SaveAs("pdfFiles/xgj_MC_only.pdf");

  TCanvas* c2MCover = new TCanvas("c2MCover","",500,500);
  bool drawn=false;
  for ( int icent = 1 ; icent<=4 ; icent++) {
    c2MCover->cd(icent);
    handsomeTH1(hxjgNorm[kHIMC][icent],ycolor[icent]);
    hxjgNorm[kHIMC][5-icent]->SetAxisRange(-0.01,0.38,"Y");
    if (drawn)  
      hxjgNorm[kHIMC][5-icent]->Draw("same");
    else       hxjgNorm[kHIMC][5-icent]->Draw("");
    
    
    drawn = true;
  }
  TLegend *l11 = new TLegend(0.1794355,0.7055085,1,0.9152542,NULL,"brNDC");
  easyLeg(l11,"p_{T}^{Jet}/p_{T}^{#gamma} of PYTHIA embedded in"); 
  l11->AddEntry(hxjgNorm[kHIMC][4],"HYDJET 50-100%","p");
  l11->AddEntry(hxjgNorm[kHIMC][3],"HYDJET 30-50%","p");
  l11->AddEntry(hxjgNorm[kHIMC][2],"HYDJET 10-30%","p");
  l11->AddEntry(hxjgNorm[kHIMC][1],"HYDJET 0 -10%","p");
  l11->Draw();
  c2MCover->SaveAs("pdfFiles/xgj_MC_OnePannel.pdf");


  
  TCanvas* c3 = new TCanvas("c3","",500,500);
  TH1D* npartTempHist = new TH1D("meanR",";N_{part}; R",100,0,400);
  
  double npart4[8] = { 43.6661-10, 43.6661+10, 116.36-10, 116.36+10, 235.769-10, 235.769+10, 359.22-10,359.22+10};
  double npart4_2[4] = { 43.6661, 116.36, 235.769, 359.22};
  TGraphAsymmErrors* gR[5];

  for ( int iSpec = 0 ; iSpec<5 ; iSpec++) {
    
    if ( (iSpec != kHIDATA) && (iSpec != kHIMC) )       continue;
    gR[iSpec] = new TGraphAsymmErrors();
    gR[iSpec]->SetName(Form("gR_%d",iSpec));
    for ( int icent =4 ; icent>=1 ; icent--) {
      double theRerror;
      double theR = hxjg[iSpec][icent]->IntegralAndError(1, hxjg[iSpec][5-icent]->GetNbinsX(), theRerror, "width");
      gR[iSpec]->SetPoint(icent, npart4_2[4 - icent], theR );
      gR[iSpec]->SetPointError(icent, 0.001,0.001, theRerror, theRerror);    
    }
  }
  handsomeTH1(npartTempHist,1);
  npartTempHist->SetAxisRange(0.3,1.0,"Y");
  npartTempHist->DrawCopy();
  gR[kHIDATA]->SetMarkerColor(2);
  gR[kHIDATA]->SetLineColor(2);
  gR[kHIMC]->Draw("same p");
  //  gR[kHIDATA]->Draw("same p");

  c3->SaveAs("pdfFiles/r_MC_only.pdf");

  TCanvas* c3a = new TCanvas("c3a","",500,500);
  npartTempHist->DrawCopy();
  gR[kHIMC]->Draw("same p");
  gR[kHIDATA]->Draw("same p");
  TLegend *l13 = new TLegend(0.1794355,0.7055085,1,0.9152542,NULL,"brNDC");
  easyLeg(l13,"R_{J,#gamma}");
  l13->AddEntry(gR[kHIDATA],"PbPb data","pl");
  l13->AddEntry(gR[kHIMC],"PYTHIA+HYDJET","pl");
  l13->Draw();
  c3a->SaveAs("pdfFiles/r_MC_Data.pdf");


  TCanvas* c4 = new TCanvas("c4","",500,500);
  
  TGraphAsymmErrors* gX[5];

  for ( int iSpec = 0 ; iSpec<5 ; iSpec++) {
    
    if ( (iSpec != kHIDATA) && (iSpec != kHIMC) )       continue;
    gX[iSpec] = new TGraphAsymmErrors();
    gX[iSpec]->SetName(Form("gX_%d",iSpec));
    for ( int icent =4 ; icent>=1 ; icent--) {
      double theX      = hxjg[iSpec][icent]->GetMean();
      double theXerror = hxjg[iSpec][icent]->GetMeanError();
      gX[iSpec]->SetPoint(icent, npart4_2[4 - icent], theX );
      gX[iSpec]->SetPointError(icent, 0.001,0.001, theXerror, theXerror);    
    }
  }
  handsomeTH1(npartTempHist,1);
  npartTempHist->SetYTitle("<X_{J,#gamma}>");
  npartTempHist->SetAxisRange(0.6,1.1,"Y");
  npartTempHist->DrawCopy();
  gX[kHIDATA]->SetMarkerColor(2);
  gX[kHIDATA]->SetLineColor(2);
  gX[kHIMC]->Draw("same p");
  //  gX[kHIDATA]->Draw("same p");

  c4->SaveAs("pdfFiles/meanX_MC_only.pdf");


 TCanvas* c4a = new TCanvas("c4a","",500,500);
  
 npartTempHist->DrawCopy();
 gX[kHIMC]->Draw("same p");
 gX[kHIDATA]->Draw("same p");
 TLegend *l14 = new TLegend(0.1794355,0.7055085,1,0.9152542,NULL,"brNDC");
 easyLeg(l14,"<X_{J,#gamma}>");
 l14->AddEntry(gX[kHIDATA],"PbPb data","pl");
 l14->AddEntry(gX[kHIMC],"PYTHIA+HYDJET","pl");
 l14->Draw();
 c4a->SaveAs("pdfFiles/meanX_MC_Data.pdf");




    
}
