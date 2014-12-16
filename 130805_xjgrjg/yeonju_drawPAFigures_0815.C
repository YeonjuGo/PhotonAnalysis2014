// cent dep.
//

#include "CutAndBinCollection2012.h"
#include <TRandom3.h>
#include <time.h>
#include <TStyle.h>

void yeonju_drawPAFigures_0815(int xNorm = 1) { 
  gStyle -> SetOptStat(0); 
    //yeonju
  const int nCentBinPa = 3;
  double centBinPa[nCentBinPa+1] = {0,20,30,100};
  double AvePtBin[nCentBinPa+1] = {10, 25.0, 65.0, 9999};
  const int nPt = 5;
  const int nFile = 10;
  
  double PtBinPa[nPt+1] = {40,50,60,80,120,9999};

/*  const int nCentBinPa = 5;
  double centBinPa[nCentBinPa+1] = {0,20,25,30,40,100};
  double AvePtBin[nCentBinPa+1] = { 10, 22.5, 27.5, 35, 70, 9999};
  */
  TH1D* hxjg[7][1000][20]; // [species][centrality][pt_dependence]
  TH1D* hxjgNorm[7][1000][20];
  TH1D* hdphi[7][1000][20];
  
  valPair meanX[7][1000][20];
  valPair rjg[7][1000][20];
  TGraphAsymmErrors* gr[7][20];
  TGraphAsymmErrors* gx[7][20];
  for (int j=1;j<=nFile;j++){
      for (int i=1;i<=7;i++) {  
          gr[i][j] = new TGraphAsymmErrors();
          gr[i][j]->SetName(Form("gr_%d_%d",i,j));
          gx[i][j] = new TGraphAsymmErrors();
          gx[i][j]->SetName(Form("gx_%d_%d",i,j));
      }
  }
  TFile* fff[7][1000][20];
  double rError[20];
// cout << "ok!"<< endl;
  for ( int icent = 1 ; icent<=nCentBinPa  ; icent++) { 
    int iSpecies =kPADATA ; 
    
    int iglb = icent + iSpecies*50.;
    
    fff[iSpecies][iglb][1] = new TFile("ffFiles/photonTrackCorr_ppbDATA_output_photonPtThr40_to_50_jetPtThr30_20130815.root");
    fff[iSpecies][iglb][2] = new TFile("ffFiles/photonTrackCorr_ppbDATA_output_photonPtThr50_to_60_jetPtThr30_20130815.root");
    fff[iSpecies][iglb][3] = new TFile("ffFiles/photonTrackCorr_ppbDATA_output_photonPtThr60_to_80_jetPtThr30_20130815.root");
    fff[iSpecies][iglb][4] = new TFile("ffFiles/photonTrackCorr_ppbDATA_output_photonPtThr80_to_120_jetPtThr30_20130815.root");
    fff[iSpecies][iglb][5] = new TFile("ffFiles/photonTrackCorr_ppbDATA_output_photonPtThr120_to_9999_jetPtThr30_20130815.root");
    fff[iSpecies][iglb][6] = new TFile("ffFiles/photonTrackCorr_ppbMC_output_photonPtThr40_to_50_jetPtThr30_20130815.root");
    fff[iSpecies][iglb][7] = new TFile("ffFiles/photonTrackCorr_ppbMC_output_photonPtThr50_to_60_jetPtThr30_20130815.root");
    fff[iSpecies][iglb][8] = new TFile("ffFiles/photonTrackCorr_ppbMC_output_photonPtThr60_to_80_jetPtThr30_20130815.root");
    fff[iSpecies][iglb][9] = new TFile("ffFiles/photonTrackCorr_ppbMC_output_photonPtThr80_to_120_jetPtThr30_20130815.root");
    fff[iSpecies][iglb][10] = new TFile("ffFiles/photonTrackCorr_ppbMC_output_photonPtThr120_to_9999_jetPtThr30_20130815.root");
  //          cout << "fffff" << endl;
    for(int j = 1; j <= nFile ; j++){
        hdphi[iSpecies][iglb][j] = (TH1D*)fff[iSpecies][iglb][j]->Get(Form("jetDphi_icent%d_final",icent));
//cout << "hdphi" <<endl;
        hxjg[iSpecies][iglb][j] = (TH1D*)fff[iSpecies][iglb][j]->Get(Form("xjg_icent%d_final",icent));
        hxjgNorm[iSpecies][iglb][j] = (TH1D*)hxjg[iSpecies][iglb][j]->Clone(Form("norm_%s",hxjg[iSpecies][iglb][j]->GetName()) );

//cout << "meanX" <<endl;
        meanX[iSpecies][iglb][j].val = hxjg[iSpecies][iglb][j]->GetMean();
        meanX[iSpecies][iglb][j].err = hxjg[iSpecies][iglb][j]->GetMeanError();
        gx[iSpecies][j]->SetPoint     (icent, AvePtBin[icent-1], meanX[iSpecies][iglb][j].val);
        gx[iSpecies][j]->SetPointError(icent, AvePtBin[icent-1] - centBinPa[icent-1], centBinPa[icent] - AvePtBin[icent-1], meanX[iSpecies][iglb][j].err, meanX[iSpecies][iglb][j].err);

//cout << "rjg" <<endl;
        rjg[iSpecies][iglb][j].val = hxjg[iSpecies][iglb][j]->IntegralAndError(1, hxjg[iSpecies][iglb][j]->GetNbinsX(), rError[j], "width");
        rjg[iSpecies][iglb][j].err = rError[j];
        gr[iSpecies][j]->SetPoint     (icent, AvePtBin[icent-1], rjg[iSpecies][iglb][j].val);
        gr[iSpecies][j]->SetPointError(icent,  AvePtBin[icent-1] - centBinPa[icent-1], centBinPa[icent] - AvePtBin[icent-1], rjg[iSpecies][iglb][j].err, rjg[iSpecies][iglb][j].err);
    }

  }

  cout << "Tcanvas c1 " << endl;
  TCanvas* c1 = new TCanvas("c1","xjg_distribution",900,1750);
  makeMultiPanelCanvas(c1,3,5,0.0,0.0,0.2,0.15,0.02);
  for ( int j = 1 ; j <= nPt ; j++){//pt
      for ( int icent = 1 ; icent<=nCentBinPa  ; icent++) {
          c1->cd(icent+3*(j-1));

          int iSpecies = kPADATA;
          int iglb = icent + iSpecies*50.;
          handsomeTH1(hxjgNorm[iSpecies][iglb][j],icent);
          hxjgNorm[iSpecies][iglb][j]->Scale(0.1);
          if (xNorm==1) scaleInt(hxjgNorm[iSpecies][iglb][j]);
          hxjgNorm[iSpecies][iglb][j]->SetXTitle("x_{J,#gamma}");
          hxjgNorm[iSpecies][iglb][j]->SetYTitle("#frac{dN}{dx} #frac{1}{N}");
          if (xNorm==1)     hxjgNorm[iSpecies][iglb][j]->SetAxisRange(-0.015,0.35,"Y");
          else              hxjgNorm[iSpecies][iglb][j]->SetAxisRange(-0.06,1.5,"Y");
          hxjgNorm[iSpecies][iglb][j]->SetMarkerStyle(19+j);
          hxjgNorm[iSpecies][iglb][j]->Draw();


          float dx1;    
          ((icent==1)||(icent==4))? dx1=0.15 : dx1=0 ;

          if ( icent == nCentBinPa )
              drawText(Form("E_{T}^{HF|#eta|>4} > %dGeV, ", (int)centBinPa[icent-1]), 0.12+dx1+0.25,0.889118,1,15);//yeonju 130805
          else
              drawText(Form("%dGeV < E_{T}^{HF|#eta|>4} < %dGeV, ", (int)centBinPa[icent-1], (int)centBinPa[icent]), 0.12+dx1,0.889118,1,15);
          
          if ( j == nPt ) 
              drawText(Form("p_{T}^{#gamma} < %dGeV, ", (int)PtBinPa[j-1]), 0.12+dx1+0.25,0.79,1,15);//yeonju 130823
          else
              drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV, ", (int)PtBinPa[j-1], (int)PtBinPa[j]), 0.12+dx1,0.79,1,15);//yeonju 130823
          
              TLegend *l1 = new TLegend(0.6365615,0.6445304,0.9577623,0.846736,NULL,"brNDC");
              easyLeg(l1,"p+Pb 5.02TeV");
          //    l1->AddEntry(hxjgNorm[kPADATA][icent + kPADATA*50][j],"pPb ","p");
              if ( icent==1 && j==1)   l1->Draw();
              onSun(0,0,2,0);
              jumSun(1,0,1,1);
      }
  }

  c1 -> SaveAs("pPbData_xjgDistribution_pt_cent_dep.gif");
//cout<< "c11" << endl;
/*  TCanvas* c11 = new TCanvas("c11","xjgDist_onePanel_pt_cent_dep",500,500);
  for ( int j = 1 ; j <=nPt ; j++){
      for ( int icent = 1 ; icent<=nCentBinPa  ; icent++) {
          int iSpecies = kPADATA;
          int iglb = icent + iSpecies*50.;
          handsomeTH1(hxjgNorm[iSpecies][iglb][j],icent+3*(j-1));

          if ( icent == 1 && j == 1) hxjgNorm[iSpecies][iglb][j]->Draw();
          else     hxjgNorm[iSpecies][iglb][j]->Draw("same");
          onSun(0,0,2,0);
      }
  }

  c11 -> SaveAs("xjgDist_onePanel_by_pt_cent_dep.gif");
*/
  TCanvas* cDphi = new TCanvas("cDphi","",1200,350);
  makeMultiPanelCanvas(cDphi,5,1,0.0,0.0,0.2,0.15,0.02);

  TH1D* meanDphi[7][10];      // [iSpecies][pt]
  for (int j=1 ; j<=nPt  ; j++) {

          int iSpecies = kPADATA;
          meanDphi[iSpecies][j] = new TH1D(Form("meanDphi_iSpecies%d_pt%d",iSpecies,j), ";p_{T}^{#gamma} (GeV); <Dphi_{J#phi}>",nPt,AvePtBin);
  }

  for (int ipt=1 ; ipt<=nPt ; ipt++) {
      for (int icent=1 ; icent<= nCentBinPa ; icent++ ) { 
          int iSpecies = kPADATA;
          int iglb = icent + iSpecies*50.;

          if ( hdphi[iSpecies][iglb][ipt] == NULL ) 
              continue;   // emtpy histogram 

          meanDphi[iSpecies][ipt]->SetBinContent( ipt, hdphi[iSpecies][iglb][ipt]->GetMean() );
          meanDphi[iSpecies][ipt]->SetBinError  ( ipt, hdphi[iSpecies][iglb][ipt]->GetMeanError() );
      }
  }

  for ( int j = 1 ; j<=nPt ; j++){
      int icent=1;
      // for ( int icent = 1 ; icent<=nCentBinPa  ; icent++) {
      cDphi->cd(j-1);
      int iSpecies = kPADATA;
      int iglb = icent + iSpecies*50.;
      handsomeTH1(meanDphi[iSpecies][j]);
      meanDphi[iSpecies][j]->SetXTitle("#Delta#phi_{J,#gamma}");
      meanDphi[iSpecies][j]->Scale(1./meanDphi[iSpecies][j]->Integral("width"));
      meanDphi[iSpecies][j]->SetAxisRange(0.01,30,"Y");
      //    meanDphi[iSpecies][j]->SetMarkerStyle(24);
      //    handsomeTH1(meanDphi[iSpecies][j],icent+3*(j-1));
      meanDphi[iSpecies][j]->Draw();

      gPad->SetLogy();
      float dx1=0;    
 //     ((icent==1)||(icent==4))? dx1=0.15 : dx1=0 ;

      /*   if ( icent == nCentBinPa )
           drawText(Form("E_{T}^{HF|#eta|>4} > %dGeV", (int)centBinPa[icent-1]), 0.12+dx1+0.25,0.889118,1,15);//yeonju 130805
           else
           drawText(Form("%dGeV < E_{T}^{HF|#eta|>4} < %dGeV", (int)centBinPa[icent-1], (int)centBinPa[icent]), 0.12+dx1,0.889118,1,15);
           */   if ( j == nPt ) 
      drawText(Form("p_{T}^{#gamma} < %dGeV, ", (int)PtBinPa[j-1]), 0.12+dx1+0.25,0.79,1,15);//yeonju 130823
      else
          drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV, ", (int)PtBinPa[j-1], (int)PtBinPa[j]), 0.12+dx1,0.79,1,15);//yeonju 130823

      TLegend *l1 = new TLegend(0.6365615,0.6445304,0.9577623,0.846736,NULL,"brNDC");
      easyLeg(l1,"p+Pb 5.02TeV");
          if ( icent==1 && j==1)   l1->Draw();
     // }
  }
  cDphi -> SaveAs("pPbData_Dphi_distribution_by_pt_dep.pdf");
  
  TCanvas* c2 = new TCanvas("c2","xjg_rjg_vs_pt",800,400);
  c2->Divide(2,1);
  
  TH1D* hr[15];
  TH1D* hx[15];

  for(int j=1; j<=nFile ; j++){
      c2->cd(2);
      hr[j] = new TH1D(Form("hr%d",j),";E_{T}^{HF|#eta|>4} (GeV);r_{J,#gamma}",200,0,100);
      handsomeTH1(hr[j],j+1);
      hr[j]->SetAxisRange(0.01,1.1,"Y");
      //  hr->SetNdivisions(5);
      if (j ==1 ) {hr[j]->Draw();}
      else  { hr[j]->Draw("same");}
      
      if (j < 4) { 
      handsomeTGraph(gr[kPADATA][j],j+1);
          gr[kPADATA][j]->SetMarkerStyle(20);
          gr[kPADATA][j]->SetMarkerSize(1);
          gr[kPADATA][j]->Draw("same p");
      } else {  
      handsomeTGraph(gr[kPADATA][j],j-2);
          gr[kPADATA][j]->SetMarkerStyle(24);
          gr[kPADATA][j]->SetMarkerSize(1.5);
          gr[kPADATA][j]->Draw("same p");
      }

      jumSun(0,1,100,1);

      c2->cd(1);
      hx[j] = (TH1D*)hr[j]->Clone(Form("hx%d",j));
      handsomeTH1(hx[j],j+1);
      hx[j]->SetYTitle("<x_{J,#gamma}>");
      hx[j]->SetAxisRange(0.6,1.05,"Y");
      //  hx->SetNdivisions(5);
      if (j==1) {hx[j]->Draw();}
      else {hx[j]->Draw("same");}
      if (j < 4) { 
      handsomeTGraph(gx[kPADATA][j],j+1);
          gx[kPADATA][j]->SetMarkerStyle(20);
          gx[kPADATA][j]->SetMarkerSize(1);
          gx[kPADATA][j]->Draw("same p");
      } else {  
      handsomeTGraph(gx[kPADATA][j],j-2);
          gx[kPADATA][j]->SetMarkerStyle(24);
          gx[kPADATA][j]->SetMarkerSize(0.2);
          gx[kPADATA][j]->Draw("same p");
      }
      jumSun(0,1,100,1);
  
      TLegend *l1 = new TLegend(0.5226071,0.6300415,0.9597724,0.8332584,NULL,"brNDC");
      easyLeg(l1,"5.02TeV");
      l1->AddEntry(gr[kPADATA][j],"pPb ","p");
      l1->Draw();  }
  

      c2 -> SaveAs("pPbMC_and_Data_comparison_xjg_rjg.gif");
  /* 
  for(int j=1; j<=nPt ; j++){
      c2->cd(2*j);
      hr[j] = new TH1D(Form("hr%d",j),";E_{T}^{HF|#eta|>4} (GeV);r_{J,#gamma}",200,0,100);
      handsomeTH1(hr[j],1);
      hr[j]->SetAxisRange(0.01,1.1,"Y");
      //  hr->SetNdivisions(5);
      hr[j]->Draw();
      handsomeTGraph(gr[kPADATA][j],1);
      gr[kPADATA][j]->SetMarkerStyle(20+j);
      gr[kPADATA][j]->Draw("same p");
      jumSun(0,1,100,1);

      c2->cd(2*j-1);
      hx[j] = (TH1D*)hr[j]->Clone(Form("hx%d",j));
      handsomeTH1(hx[j],1);
      hx[j]->SetYTitle("<x_{J,#gamma}>");
      hx[j]->SetAxisRange(0.6,1.05,"Y");
      //  hx->SetNdivisions(5);
      hx[j]->Draw();
      handsomeTGraph(gx[kPADATA][j],1);
      gx[kPADATA][j]->SetMarkerStyle(20+j);
      gx[kPADATA][j]->Draw("same p");
      jumSun(0,1,100,1);

      TLegend *l1 = new TLegend(0.5226071,0.6300415,0.9597724,0.8332584,NULL,"brNDC");
      easyLeg(l1,"5.02TeV");
      l1->AddEntry(gr[kPADATA][j],"pPb ","p");
      l1->Draw();

      c2 -> SaveAs("x_Jgamma.gif");
  }*/
}

