#include "../../HiForestAnalysis/hiForest.h"
#include "../CutAndBinCollection2012.h"
#include <TRandom3.h>
#include <time.h>

void drawPtDependence(bool drawPbPb=1, int xNorm = 0) {
  
  const int nPtBin = 4;
  double ptBin[nPtBin+1] = {40, 50,60,80,9999}; 
  double ptBinPaDraw[nPtBin+1] = { 40.5 ,49.5, 58.5,  76.5,  123. } ;
  // double AvePtBin[nPtBin+1] = { 45, 54.1479, 67.4204, 99.6956, 9999};
  
  const int nCentBinHI = 2;
  const int centBinHI[nCentBinHI +1] = {-1, 10030, 13099}; 

  TH1D* hxjg[7][10][6]; // [Collision][centrality][pt]
  TH1D* hJetPt[7][10][6]; // [Collision][centrality][pt]
  TH1D* hDphi[7][10][6]; // [Collision][centrality][pt]
  TH1D* meanXjg[7][10];      // [Collision][centrality]
  TH1D* meanJetPt[7][10];      // [Collisi on][centrality]

  TH1D* rjg[7][5];     //  [Collision][centrality]
  for (int icoll=0 ; icoll<6  ; icoll++) {
    for (int icent=1 ; icent<= 10 ; icent++) {
      meanXjg[icoll][icent] = new TH1D( Form("meanXjg_icoll%d_icent%d",icoll,icent), ";p_{T}^{#gamma}; <X_{J#gamma}>",nPtBin,ptBinPaDraw);
      meanJetPt[icoll][icent] = new TH1D( Form("meanJetPt_icoll%d_icent%d",icoll,icent), ";p_{T}^{#gamma}; <p_{T}^{Jet}>",nPtBin,ptBinPaDraw);
      rjg[icoll][icent] = new TH1D( Form("rjg_icoll%d_icent%d",icoll,icent), ";p_{T}^{#gamma}; R_{J#gamma}",nPtBin,ptBinPaDraw);

      for (int ipt=1 ; ipt<=nPtBin ; ipt++) {
	hxjg[icoll][icent][ipt] = NULL;
	hJetPt[icoll][icent][ipt] = NULL;
	hDphi[icoll][icent][ipt] = NULL;
      }
      
    }
  }
  
  TFile* histFile[7][6];  // [Collision][pt]                                                                                          
  for (int ipt=1 ; ipt<=nPtBin ; ipt++) {
    for (int icoll=0 ; icoll<6 ; icoll++) {
      TString sampleName = getSampleName( icoll ) ;
      char* fname =  Form("../histogramProducer/ffFiles/photonTrackCorr_%s_output_photonPtThr%d_to_%d_jetPtThr30_20130828.root",sampleName.Data(), (int)ptBin[ipt-1], (int)ptBin[ipt]);
      histFile[icoll][ipt] = new TFile(fname) ;
      cout << " Reading file : " << fname << endl;
      
      if ( histFile[icoll][ipt]->IsZombie()  == false ) {
	cout << " Success." << endl;
	if ( (icoll == kPPDATA) || (icoll == kPPMC) )   {  //  PP
	  int icent = 7 ; 
	  hxjg[icoll][icent][ipt] = (TH1D*)histFile[icoll][ipt]->Get(Form("xjg_icent%d_final", icent)) ;
	  cout << " Getting histogram : " << Form("xjg_icent%d_final", icent) << endl;
	  hJetPt[icoll][icent][ipt] = (TH1D*)histFile[icoll][ipt]->Get(Form("jetPt_icent%d_final", icent)) ;
	  cout << " Getting histogram : " << Form("jetPt_icent%d_final", icent) << endl;
	  hDphi[icoll][icent][ipt]  = (TH1D*)histFile[icoll][ipt]->Get(Form("jetDphi_icent%d_final", icent)) ;
	  cout << " Getting histogram : " << Form("jetDphi_icent%d_final", icent) << endl;
	}
	
	if ( ( icoll == kHIDATA) ||  (icoll == kHIMC) ) { // PbPb
	  for ( int icent = 1; icent <= nCentBinHI ; icent++ ) {
	    hxjg[icoll][icent][ipt] = (TH1D*)histFile[icoll][ipt]->Get(Form("xjg_icent%d_final", centBinHI[icent] )) ;
	    cout << " Getting histogram : " << Form("xjg_icent%d_final", centBinHI[icent] ) << endl;
	    hJetPt[icoll][icent][ipt] = (TH1D*)histFile[icoll][ipt]->Get(Form("jetPt_icent%d_final", centBinHI[icent] ) );
	    cout << " Getting histogram : " << Form("jetPt_icent%d_final", centBinHI[icent] ) << endl;
	    hDphi[icoll][icent][ipt]  = (TH1D*)histFile[icoll][ipt]->Get(Form("jetDphi_icent%d_final", centBinHI[icent] ) ) ;
	    cout << " Getting histogram : " << Form("jetDphi_icent%d_final", icent)<< endl;
	  }
	}
      }
      else  
	cout << " no such file " << endl;
    }
  }
  
  for (int ipt=1 ; ipt<=nPtBin ; ipt++) {
    for (int icoll=0 ; icoll<6 ; icoll++) {
      for (int icent=1 ; icent<= 10 ; icent++ ) { 
	if ( hxjg[icoll][icent][ipt] == NULL ) 
	  continue;   // emtpy histogram 
	double rVal, rErr;
	
	rVal = hxjg[icoll][icent][ipt]->IntegralAndError(1, hxjg[icoll][icent][ipt]->GetNbinsX(), rErr, "width");
	rjg[icoll][icent]->SetBinContent( ipt, rVal );
	rjg[icoll][icent]->SetBinError  ( ipt, rErr );
 	
	meanXjg[icoll][icent]->SetBinContent( ipt, hxjg[icoll][icent][ipt]->GetMean() );
	meanXjg[icoll][icent]->SetBinError  ( ipt, hxjg[icoll][icent][ipt]->GetMeanError() );
	
	meanJetPt[icoll][icent]->SetBinContent( ipt, hJetPt[icoll][icent][ipt]->GetMean() );
	meanJetPt[icoll][icent]->SetBinError  ( ipt, hJetPt[icoll][icent][ipt]->GetMeanError() );


	hJetPt[icoll][icent][ipt]->Rebin(2);
	hJetPt[icoll][icent][ipt]->Scale(1./2);
      }
    }
  }
  
  TCanvas* c1 = new TCanvas("c1","",1200,350);
  makeMultiPanelCanvas(c1,nPtBin,1,0.0,0.0,0.2,0.15,0.02);
  for ( int ipt = 1 ; ipt<=nPtBin  ; ipt++) {
    
    c1->cd(ipt);
    
    // draw pp
    handsomeTH1(hDphi[kPPDATA][7][ipt], 1);
    hDphi[kPPDATA][7][ipt]->SetXTitle("#Delta#phi_{J#gamma}");
    hDphi[kPPDATA][7][ipt]->SetYTitle("Normalized entries");
    hDphi[kPPDATA][7][ipt]->SetAxisRange(0,3.141592,"X");
    hDphi[kPPDATA][7][ipt]->SetAxisRange(0.01,100,"Y");
    hDphi[kPPDATA][7][ipt]->SetMarkerStyle(24);
    hDphi[kPPDATA][7][ipt]->Scale(1./hDphi[kPPDATA][7][ipt]->Integral("width"));       
    hDphi[kPPDATA][7][ipt]->Draw();
    // draw pbpb 
    for ( int icent = 1; icent <= nCentBinHI ; icent++ ) {
      handsomeTH1(hDphi[kHIDATA][icent][ipt],kRed);
      if ( icent == 2 ) hDphi[kHIDATA][icent][ipt]->SetMarkerStyle(24);
      hDphi[kHIDATA][icent][ipt]->Scale(1./hDphi[kHIDATA][icent][ipt]->Integral("width"));
      hDphi[kHIDATA][icent][ipt]->Draw("same");
      
    }
      
    gPad->SetLogy();
    //    onSun(30,0,200,0);
  }


  TCanvas* c2 = new TCanvas("c2","",1200,350);
  makeMultiPanelCanvas(c2,nPtBin,1,0.0,0.0,0.2,0.15,0.02);
  for ( int ipt = 1 ; ipt<=nPtBin  ; ipt++) {
    
    c2->cd(ipt);
    
    // draw pp
    handsomeTH1(hJetPt[kPPDATA][7][ipt], 1);
    hJetPt[kPPDATA][7][ipt]->SetXTitle("p_{T}^{Jet}");
    hJetPt[kPPDATA][7][ipt]->SetYTitle("#frac{dN}{dp_{T}} #frac{1}{N}");
    hJetPt[kPPDATA][7][ipt]->SetAxisRange(30,150,"X");
    hJetPt[kPPDATA][7][ipt]->SetAxisRange(0,0.025,"Y");
    hJetPt[kPPDATA][7][ipt]->SetMarkerStyle(24);
    hJetPt[kPPDATA][7][ipt]->Draw();

    // draw pbpb 
    for ( int icent = 1; icent <= nCentBinHI ; icent++ ) {
      handsomeTH1(hJetPt[kHIDATA][icent][ipt],kRed);
      if ( icent == 2 ) hJetPt[kHIDATA][icent][ipt]->SetMarkerStyle(24);
      //      if ( icent == 1 )       hJetPt[kHIDATA][icent][ipt]->Draw("same");
      hJetPt[kHIDATA][icent][ipt]->Draw("same");
      
    }
      
    onSun(30,0,200,0);
  }


}


/*  
  //    onSun(meanX[iSpecies][iglb].val - meanX[iSpecies][iglb].err, 0, meanX[iSpecies][iglb].val+meanX[iSpecies][iglb].err,0,ycolor[ipt+1],2);
    
    float dx1;    
    (ipt==0)? dx1=0.15 : dx1=0 ;
    
    if ( ipt == nPtBin-1 ) 
      drawText(Form("p_{T}^{#gamma} > %dGeV,   p_{T}^{jet}>30GeV", (int)ptBin[ipt]), 0.12+dx1+0.25,0.889118,1,15);
    else 
      drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV,   p_{T}^{jet}>30GeV", (int)ptBin[ipt], (int)ptBin[ipt+1]), 0.12+dx1,0.889118,1,15);

      
    TLegend *l1 = new TLegend(0.6365615,0.6445304,0.9577623,0.846736,NULL,"brNDC");
    easyLeg(l1,"2.76TeV");
    l1->AddEntry(hdptNorm[kPPDATA][ipt + kPPDATA*50],"pp ","p");
    if (drawPbPb)    l1->AddEntry(hdptNorm[kHIDATA][iglb],"PbPb 50-100%","p");
    if ( ipt==0 )   l1->Draw();
    

  }
  c1->SaveAs(Form("gifs/dpt_ptDependence_drawPbPb%d_norm%d.pdf",drawPbPb,xNorm));

  TCanvas* cDphi = new TCanvas("cDphi","",900,350);
  makeMultiPanelCanvas(cDphi,nPtBin,1,0.0,0.0,0.2,0.15,0.02);
  for ( int ipt = 0 ; ipt<nPtBin  ; ipt++) {
    cDphi->cd(ipt+1);
    
    int iSpecies = kPPDATA;
    int iglb = ipt + iSpecies*50.;
    handsomeTH1(hdphi[iSpecies][iglb],1);
    hdphi[iSpecies][iglb]->SetYTitle("x_{J,#gamma}");
    hdphi[iSpecies][iglb]->SetXTitle("#Delta#phi_{J,#gamma}");
    hdphi[iSpecies][iglb]->Scale(1./hdphi[iSpecies][iglb]->Integral("width"));
    hdphi[iSpecies][iglb]->SetAxisRange(0.01,30,"Y");
    hdphi[iSpecies][iglb]->SetMarkerStyle(24);
    hdphi[iSpecies][iglb]->Draw();

    iSpecies = kHIDATA;
    iglb = ipt + iSpecies*50.;
    hdphi[iSpecies][iglb]->Scale(1./hdphi[iSpecies][iglb]->Integral("width"));
    handsomeTH1(hdphi[iSpecies][iglb],2);
    if (drawPbPb)     hdphi[iSpecies][iglb]->Draw("same");
    gPad->SetLogy();
    float dx1;    
    (ipt==0)? dx1=0.15 : dx1=0 ;
    
    if ( ipt == nPtBin-1 ) 
      drawText(Form("%dGeV<p_{T}^{#gamma},   p_{T}^{jet}>30GeV", (int)ptBin[ipt]), 0.15+dx1+0.25,0.889118,1,15);
    else 
      drawText(Form("%dGeV<p_{T}^{#gamma}<%dGeV,   p_{T}^{jet}>30GeV", (int)ptBin[ipt], (int)ptBin[ipt+1]), 0.15+dx1,0.889118,1,15);
    
      
    TLegend *l1 = new TLegend(0.6365615,0.6445304,0.9577623,0.846736,NULL,"brNDC");
    easyLeg(l1,"2.76TeV");
    l1->AddEntry(hdphi[kPPDATA][ipt + kPPDATA*50],"pp ","p");
    if (drawPbPb)    l1->AddEntry(hdphi[kHIDATA][iglb],"PbPb 0-30%","p");
    if ( ipt==0 )   l1->Draw();

  }

  
  //  cDphi->SaveAs(Form("gifs/dphi_ptDependence_drawPbPb%d_norm%d.pdf",drawPbPb,xNorm));
  
  TCanvas* c2 = new TCanvas("c2","",800,400);
  c2->Divide(2,1);
  c2->cd(2);
  TH1D* hr = new TH1D("hr",";p_{T}^{#gamma};r_{J,#gamma}",200,20,120);
  handsomeTH1(hr,0);
  hr->SetAxisRange(0.0,1.3,"Y");
  //  hr->SetNdivisions(5);
  hr->Draw();
  handsomeTGraph(gr[kPPDATA],1);
  handsomeTGraph(gr[kHIDATA],2);
  gr[kPPDATA]->SetMarkerStyle(24);
  gr[kPPDATA]->Draw("same p");
  if (drawPbPb)   gr[kHIDATA]->Draw("same p");
  jumSun(20,1,120,1);


  
  c2->cd(1);
  TH1D* hx = (TH1D*)hr->Clone("hx");
  handsomeTH1(hx,0);
  hx->SetYTitle("<#Deltap_{T}^{J,#gamma}>");
  //  hx->SetAxisRange(-60,10,"Y");
  hx->SetAxisRange(30,100,"Y");
  //  hx->SetNdivisions(5);
  hx->Draw();
  handsomeTGraph(gdpt[kPPDATA],1);
  handsomeTGraph(gdpt[kHIDATA],2);
  gdpt[kPPDATA]->SetMarkerStyle(24);
  gdpt[kPPDATA]->Draw("same p");
  if (drawPbPb)   gdpt[kHIDATA]->Draw("same p");
  jumSun(20,1,120,1);

  TLegend *l1=   new TLegend(0.5226071,0.6300415,0.9597724,0.8332584,NULL,"brNDC");
  easyLeg(l1,"2.76TeV");
  l1->AddEntry(gr[kPPDATA],"pp ","p");
  if (drawPbPb)     l1->AddEntry(gr[kHIDATA],"PbPb 30-100%","p");
  l1->Draw();

  //  c2->SaveAs(Form("gifs/summaryPlot_ptDependence_drawPbPb%d_norm%d.pdf",drawPbPb,xNorm));

}

*/
