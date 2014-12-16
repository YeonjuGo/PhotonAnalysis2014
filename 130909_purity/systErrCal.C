#include "../HiForestAnalysis/hiForest.h"
#include "../gammaJetAnalysis/CutAndBinCollection2012.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include <iostream>
#include "TStyle.h"
//#include "T.h"
//#include "T.h"

void systErrCal(){
    //    gStyle -> SetOptStat(0);
    const int nPt = 4;
    const int nPurity = 3; // 
    double purity[nPurity] = {0.9, 1., 1.1} ;// purity*0.9 and so on.. 
    double AvePtBin[nPt+1] = {45.0, 55.0, 70.0, 100.0};
    double ptBin[nPt+1] = {40,50,60,80,9999};
    double ptBinPaDraw[nPt+1] = { 40.5 ,49.5, 58.5,  76.5,  123. } ;

    const int nCentBinHI = 2;
    const int centBinHI[nCentBinHI +1] = {-1, 10030, 13099}; 

    TH1D* hxjg[7][1000][20][nPurity+10]; // [species][centrality][pt_dependence][purity]
    TH1D* hJetPt[7][1000][20][nPurity+10];
    TH1D* meanXjg[7][10][nPurity+10];      // [Collision][centrality][purity]
    TH1D* meanJetPt[7][10][nPurity+10];      // [Collision][centrality]
    TH1D* rjg[7][5][nPurity+10];     //  [Collision][centrality]

    for (int icoll=0 ; icoll<6  ; icoll++) {
        for (int icent=1 ; icent<= 10 ; icent++) {
            for(int ipu=0 ; ipu<nPurity ; ipu++) {
                meanXjg[icoll][icent][ipu] = new TH1D( Form("meanXjg_icoll%d_icent%d_ipu%d",icoll,icent,ipu), ";p_{T}^{#gamma} (GeV); <X_{J#gamma}>",nPt,ptBinPaDraw);
                meanJetPt[icoll][icent][ipu] = new TH1D( Form("meanJetPt_icoll%d_icent%d_ipu%d",icoll,icent,ipu), ";p_{T}^{#gamma} (GeV); <p_{T}^{Jet}>",nPt,ptBinPaDraw);
                rjg[icoll][icent][ipu]= new TH1D( Form("rjg_icoll%d_icent%d_ipu%d",icoll,icent,ipu), ";p_{T}^{#gamma} (GeV); R_{J#gamma}",nPt,ptBinPaDraw);
                for (int ipt=1 ; ipt<=nPt ; ipt++) {
                    hxjg[icoll][icent][ipt][ipu] = NULL;
                    hJetPt[icoll][icent][ipt][ipu] = NULL;
                }
            }
        }
    }

    TFile* histFile[7][6][nPurity];  // [Collision][pt]                                                                                          
    for (int ipt=1 ; ipt<=nPt ; ipt++) {
        for (int icoll=0 ; icoll<6 ; icoll++) {
            for (int ipu=0 ; ipu < nPurity ; ipu++) {
                TString sampleName = getSampleName( icoll ) ;
                char* fname;
                if (ipu==0) {fname =  Form("../gammaJetAnalysis/histogramProducer/ffFiles/photonTrackCorr_%s_output_photonPtThr%d_to_%d_jetPtThr30_20130909_purity09.root",sampleName.Data(), (int)ptBin[ipt-1], (int)ptBin[ipt]);
                } else if (ipu==1) {fname =  Form("../gammaJetAnalysis/histogramProducer/ffFiles/photonTrackCorr_%s_output_photonPtThr%d_to_%d_jetPtThr30_20130909.root",sampleName.Data(), (int)ptBin[ipt-1], (int)ptBin[ipt]);
                } else {fname =  Form("../gammaJetAnalysis/histogramProducer/ffFiles/photonTrackCorr_%s_output_photonPtThr%d_to_%d_jetPtThr30_20130909_purity1.1.root",sampleName.Data(), (int)ptBin[ipt-1], (int)ptBin[ipt]);
                }
                histFile[icoll][ipt][ipu] = new TFile(fname) ;
                //   cout << " Reading file : " << fname << endl;

                if ( histFile[icoll][ipt][ipu]->IsZombie()  == false ) {
                    //   cout << " Success." << endl;
                    if ( (icoll == kPPDATA) || (icoll == kPPMC) )   {  //  PP
                        int icent = 7 ; 
                        hxjg[icoll][icent][ipt][ipu] = (TH1D*)histFile[icoll][ipt][ipu]->Get(Form("xjg_icent%d_final", icent)) ;
                        //cout << " Getting histogram : " << Form("xjg_icent%d_final", icent) << endl;
                        hJetPt[icoll][icent][ipt][ipu] = (TH1D*)histFile[icoll][ipt][ipu]->Get(Form("jetPt_icent%d_final", icent)) ;
                        //cout << " Getting histogram : " << Form("jetPt_icent%d_final", icent) << endl;
                    }

                    if ( ( icoll == kHIDATA) ||  (icoll == kHIMC) ) { // PbPb
                        for ( int icent = 1; icent <= nCentBinHI ; icent++ ) {
                            hxjg[icoll][icent][ipt][ipu] = (TH1D*)histFile[icoll][ipt][ipu]->Get(Form("xjg_icent%d_final", centBinHI[icent] )) ;
                            //  cout << " Getting histogram : " << Form("xjg_icent%d_final", centBinHI[icent] ) << endl;
                            hJetPt[icoll][icent][ipt][ipu] = (TH1D*)histFile[icoll][ipt][ipu]->Get(Form("jetPt_icent%d_final", centBinHI[icent] ) );
                            //  cout << " Getting histogram : " << Form("jetPt_icent%d_final", centBinHI[icent] ) << endl;
                        }
                    }
                }
                else  
                    cout << " no such file " << endl;

            }
        }
    }

    for (int ipt=1 ; ipt<=nPt ; ipt++) {
        for (int icoll=0 ; icoll<6 ; icoll++) {
            for (int icent=1 ; icent<= 10 ; icent++ ) { 
                for (int ipu=0 ; ipu< nPurity ; ipu++ ) { 
                    if ( hxjg[icoll][icent][ipt][ipu] == NULL ) 
                        continue;   // emtpy histogram 
                    double rVal, rErr;

                    rVal = hxjg[icoll][icent][ipt][ipu]->IntegralAndError(1, hxjg[icoll][icent][ipt][ipu]->GetNbinsX(), rErr, "width");
                    rjg[icoll][icent][ipu]->SetBinContent( ipt, rVal );
                    rjg[icoll][icent][ipu]->SetBinError  ( ipt, rErr );

                    meanXjg[icoll][icent][ipu]->SetBinContent( ipt, hxjg[icoll][icent][ipt][ipu]->GetMean() );
                    meanXjg[icoll][icent][ipu]->SetBinError  ( ipt, hxjg[icoll][icent][ipt][ipu]->GetMeanError() );

                    meanJetPt[icoll][icent][ipu]->SetBinContent( ipt, hJetPt[icoll][icent][ipt][ipu]->GetMean() );
                    meanJetPt[icoll][icent][ipu]->SetBinError  ( ipt, hJetPt[icoll][icent][ipt][ipu]->GetMeanError() );
                }
            }
        }
    }
    
    TLegend *ly = new TLegend(0.4913112,0.6561548,0.9997611,0.9431145,NULL,"brNDC");
    easyLeg(ly,"2.76TeV");
    ly->AddEntry(meanJetPt[kPPDATA][7][1],"pp ","p");
    ly->AddEntry(meanJetPt[kHIDATA][2][1],"PbPb 0-30%","p");

    TLegend *l1 = new TLegend(0.4913112,0.6561548,0.9997611,0.9431145,NULL,"brNDC");
    easyLeg(l1,"2.76TeV");
    l1->AddEntry(meanJetPt[kPPDATA][7][1],"pp ","p");
    l1->AddEntry(meanJetPt[kHIDATA][1][1],"PbPb 30-100%","p");
    l1->AddEntry(meanJetPt[kHIDATA][2][1],"PbPb 0-30%","p");


    TCanvas* cJetpt = new TCanvas("c21","",500,500);
    for(int ipu=0; ipu<nPurity; ipu++){
        handsomeTH1(meanJetPt[kPPDATA][7][ipu]);
        if (ipu==0){
            meanJetPt[kPPDATA][7][ipu]->SetYTitle("<p_{T}^{Jet}>  (>30GeV)");
            //  meanJetPt[kPPDATA][7][ipu]->SetAxisRange(-2,2,"X");
            meanJetPt[kPPDATA][7][ipu]->SetAxisRange(30,95,"Y");
            meanJetPt[kPPDATA][7][ipu]->Draw();
        } else { 
            meanJetPt[kPPDATA][7][ipu]->Draw("same");
        }

    //    meanJetPt[kPPDATA][7][ipu]->SetMarkerStyle(24);
        meanJetPt[kPPDATA][7][ipu]->SetMarkerColor(kTeal+ipu);
        for ( int icent = 1; icent <= nCentBinHI ; icent++ ) {
            handsomeTH1(meanJetPt[kHIDATA][icent][ipu]);
            if ( icent == 2 ) meanJetPt[kHIDATA][icent][ipu]->SetMarkerStyle(24);
            //if ( icent != 2 ) meanJetPt[kHIDATA][icent]->Draw("same");
            meanJetPt[kHIDATA][icent][ipu]->Draw("same");
        }
    }

    l1 ->Draw();

    TCanvas* cXjg = new TCanvas("c31","",500,500);
    for(int ipu=0; ipu<nPurity; ipu++){
        handsomeTH1(meanXjg[kPPDATA][7][ipu], 1);
        meanXjg[kPPDATA][7][ipu]->SetYTitle("<x_{J#gamma}>  (>30GeV)");
        meanXjg[kPPDATA][7][ipu]->SetMarkerStyle(24);
        //  meanXjg[kPPDATA][7]->SetAxisRange(-2,2,"X");
        meanXjg[kPPDATA][7][ipu]->SetAxisRange(0.6,1.2,"Y");
        meanXjg[kPPDATA][7][ipu]->Draw();

        for ( int icent = 1; icent <= nCentBinHI ; icent++ ) {
            handsomeTH1(meanXjg[kHIDATA][icent][ipu],kRed);
            if ( icent == 2 ) meanXjg[kHIDATA][icent][ipu]->SetMarkerStyle(24);
            //if ( icent != 2 ) meanXjg[kHIDATA][icent]->Draw("same");
            meanXjg[kHIDATA][icent][ipu]->Draw("same");
        }
    }
    l1->Draw();

    TCanvas* cRjg = new TCanvas("c_rjg","",500,500);

    for(int ipu=0; ipu<nPurity; ipu++){
        handsomeTH1(rjg[kPPDATA][7][ipu], 1);
        rjg[kPPDATA][7][ipu]->SetYTitle("r_{J#gamma}");
        rjg[kPPDATA][7][ipu]->SetMarkerStyle(24);
        //  rjg[kPPDATA][7]->SetAxisRange(-2,2,"X");
        rjg[kPPDATA][7][ipu]->SetAxisRange(0.0,1.1,"Y");
        rjg[kPPDATA][7][ipu]->Draw();

        for ( int icent = 1; icent <= nCentBinHI ; icent++ ) {
            handsomeTH1(rjg[kHIDATA][icent][ipu],kRed);
            if ( icent == 2 ) rjg[kHIDATA][icent][ipu]->SetMarkerStyle(24);
            //       if ( icent != 2 ) rjg[kHIDATA][icent]->Draw("same");
            rjg[kHIDATA][icent][ipu]->Draw("same");
        }
    }
    ly->Draw();
}
