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

void one_systErrCal(sampleType collision_=kPPDATA, int icent=7){
    gStyle -> SetOptStat(0);
//
// constant initialization   
    const int nPt = 4;
    double AvePtBin[nPt+1] = {45.0, 55.0, 70.0, 100.0};
    double ptBin[nPt+1] = {40,50,60,80,9999};
    double ptBinPaDraw[nPt+1] = { 40.5 ,49.5, 58.5,  76.5,  123. } ;
    
    const int nPurity = 2; // 
    double purity[nPurity] = {1., 999} ;// purity*0.9 and so on.. 
    
    const int nCentBinHI = 2;
    const int centBinHI[nCentBinHI +1] = {-1, 10030, 13099}; 

//
// histogram
    TH1D* hxjg[nPt+2][nPurity];  // [pt_dependence][purity]
    TH1D* hJetPt[nPt+2][nPurity];// [pt_dependence][purity]
    TH1D* meanXjg[nPurity];    // [purity]
    TH1D* meanJetPt[nPurity];  // [purity]
    TH1D* rjg[nPurity];        // [purity]

//
// error initialization
    double meanXjg_upErr[nPt+2]; // as percent
    double meanXjg_downErr[nPt+2];
    double rjg_upErr[nPt+2]; // as percent
    double rjg_downErr[nPt+2];
    double meanJetPt_upErr[nPt+2]; // as percent
    double meanJetPt_downErr[nPt+2];
    double xjg_Err[nPt][40];

    for(int ipu=0 ; ipu<nPurity ; ipu++) {
        meanXjg[ipu] = new TH1D( Form("meanXjg_icoll%d_icent%d_ipu%d",collision_,icent,ipu), ";p_{T}^{#gamma} (GeV); <X_{J#gamma}>",nPt,ptBinPaDraw);
        meanJetPt[ipu] = new TH1D( Form("meanJetPt_icoll%d_icent%d_ipu%d",collision_,icent,ipu), ";p_{T}^{#gamma} (GeV); <p_{T}^{Jet}>",nPt,ptBinPaDraw);
        rjg[ipu]= new TH1D( Form("rjg_icoll%d_icent%d_ipu%d",collision_,icent,ipu), ";p_{T}^{#gamma} (GeV); R_{J#gamma}",nPt,ptBinPaDraw);
        for (int ipt=1 ; ipt<=nPt ; ipt++) {
            hxjg[ipt][ipu] = NULL;
            hJetPt[ipt][ipu] = NULL;
        }
    }

    TFile* histFile[nPt][nPurity];  // [pt][purity]                                                                                      
    for (int ipt=1 ; ipt<=nPt ; ipt++) {
        for (int ipu=0 ; ipu < nPurity ; ipu++) {
            TString sampleName = getSampleName( collision_ ) ;
            char* fname = "";
            if (ipu==1) {fname =  Form("../gammaJetAnalysis/histogramProducer/ffFiles/photonTrackCorr_%s_output_photonPtThr%d_to_%d_jetPtThr30_20131002_purity999.root",sampleName.Data(), (int)ptBin[ipt-1], (int)ptBin[ipt]);
      //      } else if (ipu==0) {fname =  Form("../gammaJetAnalysis/histogramProducer/ffFiles/photonTrackCorr_%s_output_photonPtThr%d_to_%d_jetPtThr30_20130909.root",sampleName.Data(), (int)ptBin[ipt-1], (int)ptBin[ipt]);
            } else {fname =  Form("../gammaJetAnalysis/histogramProducer/ffFiles/photonTrackCorr_%s_output_photonPtThr%d_to_%d_jetPtThr30_20131002.root",sampleName.Data(), (int)ptBin[ipt-1], (int)ptBin[ipt]);
            }

            histFile[ipt][ipu] = new TFile(fname) ;
            cout << " Reading file : " << fname << endl;

            if ( histFile[ipt][ipu]->IsZombie()  == false ) {
                cout << " Success." << endl;
                hxjg[ipt][ipu] = (TH1D*)histFile[ipt][ipu]->Get(Form("xjg_icent%d_final", icent)) ;
                cout << " Getting histogram : " << Form("xjg_icent%d_final", icent) << endl;
                hJetPt[ipt][ipu] = (TH1D*)histFile[ipt][ipu]->Get(Form("jetPt_icent%d_final", icent)) ;
                cout << " Getting histogram : " << Form("jetPt_icent%d_final", icent) << endl;
            } else cout << " no such file " << endl;
        }
    }

    for (int ipt=1 ; ipt<=nPt ; ipt++) {
        for (int ipu=0 ; ipu< nPurity ; ipu++ ) { 
            if (hxjg[ipt][ipu] == NULL) 
                continue;   // emtpy histogram 
            double rVal, rErr;
            rVal = hxjg[ipt][ipu]->IntegralAndError(1, hxjg[ipt][ipu]->GetNbinsX(), rErr, "width");
            rjg[ipu]->SetBinContent( ipt, rVal );
            rjg[ipu]->SetBinError  ( ipt, rErr );
            meanXjg[ipu]->SetBinContent( ipt, hxjg[ipt][ipu]->GetMean() );
            meanXjg[ipu]->SetBinError  ( ipt, hxjg[ipt][ipu]->GetMeanError() );
            meanJetPt[ipu]->SetBinContent( ipt, hJetPt[ipt][ipu]->GetMean() );
            meanJetPt[ipu]->SetBinError  ( ipt, hJetPt[ipt][ipu]->GetMeanError() );
        }
    }
//
// xjg distribution sysError calculation.
//
    for (int ipt=1 ; ipt<=nPt ; ipt++) {
        //  for(int ipu=0 ; ipu < nPurity ; ipu++){
        if (hxjg[ipt][0] == NULL) 
            continue;   // emtpy histogram 
        int nbin = hxjg[ipt][0]->GetNBinsX();
        cout << nbin << endl;
        for ( ibin = 0 ; ibin < nbin ; ibin++) {
            xjg_Err[ipt][ibin] = abs(hxjg[ipt][0]->GetBinContent(ibin)-hxjg[ipt][0]->GetBinContent(ibin))/hxjg[ipt][0]->GetBinContent(ibin); 
        }
        //       }
 //       cout << 
    }

    for(int ipt=1 ; ipt<=nPt ; ipt++) {
        meanXjg_upErr[ipt] = ((meanXjg[0]->GetBinContent(ipt)) - (meanXjg[1]->GetBinContent(ipt)))/(meanXjg[0]->GetBinContent(ipt));     
    //    meanXjg_downErr[ipt] = ((meanXjg[2]->GetBinContent(ipt)) - (meanXjg[0]->GetBinContent(ipt)))/(meanXjg[0]->GetBinContent(ipt));     
        //hmeanxjgErr -> SetBinContent ( ipt, meanXjg
        
        meanJetPt_upErr[ipt] = ((meanJetPt[0]->GetBinContent(ipt)) - (meanJetPt[1]->GetBinContent(ipt)))/(meanJetPt[0]->GetBinContent(ipt));     
    //    meanJetPt_downErr[ipt] = ((meanJetPt[2]->GetBinContent(ipt)) - (meanJetPt[0]->GetBinContent(ipt)))/(meanJetPt[0]->GetBinContent(ipt));     
        //hJetPtErr

        rjg_upErr[ipt] = ((rjg[0]->GetBinContent(ipt)) - (rjg[1]->GetBinContent(ipt)))/(rjg[0]->GetBinContent(ipt));     
   //     rjg_downErr[ipt] = ((rjg[2]->GetBinContent(ipt)) - (rjg[0]->GetBinContent(ipt)))/(rjg[0]->GetBinContent(ipt));     
        //hrjgErr
        cout << " === ptBin : " << ipt << " ===" << endl;  
        cout << " meanXjg    Err" << meanXjg_upErr[ipt] << endl;  
        cout << " meanJetPt  Err: " << meanJetPt_upErr[ipt] << endl;  
        cout << " rjg        Err: " << rjg_upErr[ipt] << endl;  
       
     //   cout << " === ptBin : " << ipt << " ===" << endl;  
     //   cout << " meanXjg    upErr , downErr : " << meanXjg_upErr[ipt] << ", " << meanXjg_downErr[ipt] << endl;  
     //   cout << " meanJetPt  upErr , downErr : " << meanJetPt_upErr[ipt] << ", " << meanJetPt_downErr[ipt] << endl;  
     //   cout << " rjg        upErr , downErr : " << rjg_upErr[ipt] << ", " << rjg_downErr[ipt] << endl;  
    }
    
    TCanvas* c_hist = new TCanvas("c_hist", Form("hist_sampleType%d_icent%d",collision_,icent),1200,400);
    c_hist -> Divide(3,1);
    
    TH1D* hJetPtErr = new TH1D("hJetPtErr", "Jet p_{T};p_{T}^{#gamma} (GeV); Err", nPt, ptBinPaDraw);
    TH1D* hrjgErr = new TH1D("hrjgErr", "r_{J,#gamma};p_{T}^{#gamma} (GeV); Err", nPt, ptBinPaDraw);
    TH1D* hmeanxjgErr = new TH1D("hmeanxjgErr", "mean x_{J,#gamma};p_{T}^{#gamma} (GeV); Err", nPt, ptBinPaDraw);

    for(int ipt=1 ; ipt<=nPt ; ipt++) {
        hJetPtErr -> SetBinContent(ipt, abs(meanJetPt_upErr[ipt]));        
        hrjgErr -> SetBinContent(ipt, abs(rjg_upErr[ipt]));        
        hmeanxjgErr -> SetBinContent(ipt, abs(meanXjg_upErr[ipt]));        
    }
    
    c_hist -> cd(1);
    hJetPtErr -> Draw();
 
    c_hist -> cd(2);
    hrjgErr -> Draw();
 
    c_hist -> cd(3);
    hmeanxjgErr -> Draw();

    c_hist -> SaveAs(Form("SysErrHist_Type%d_icent%d.pdf",collision_,icent));
    c_hist -> SaveAs(Form("SysErrHist_Type%d_icent%d.gif",collision_,icent));
 /*
TLegend *ly = new TLegend(0.4913112,0.6561548,0.9997611,0.9431145,NULL,"brNDC");
if( (collision_== kPPDATA) || (collision_==kPPMC)) easyLeg(ly,"2.76TeV");
    ly->AddEntry(meanJetPt[7][1],"pp ","p");
    ly->AddEntry(meanJetPt[kHIDATA][2][1],"PbPb 0-30%","p");

    TLegend *l1 = new TLegend(0.4913112,0.6561548,0.9997611,0.9431145,NULL,"brNDC");
    easyLeg(l1,"2.76TeV");
    l1->AddEntry(meanJetPt[kPPDATA][7][1],"pp ","p");
    l1->AddEntry(meanJetPt[kHIDATA][1][1],"PbPb 30-100%","p");
    l1->AddEntry(meanJetPt[kHIDATA][2][1],"PbPb 0-30%","p");
*/

    TCanvas* cJetpt = new TCanvas("cJetpt","",500,500);
    for(int ipu=0; ipu<nPurity; ipu++){
        handsomeTH1(meanJetPt[ipu],ipu+1);
            meanJetPt[ipu]->SetYTitle("<p_{T}^{Jet}>  (>30GeV)");
            //meanJetPt[ipu]->SetAxisRange(-2,2,"X");
            meanJetPt[ipu]->SetAxisRange(30,95,"Y");
            //meanJetPt[ipu]->SetMarkerStyle(24);
        if (ipu==0) meanJetPt[ipu]->Draw();
        else meanJetPt[ipu]->Draw("same");
    }
    //l1 ->Draw();

    TCanvas* cXjg = new TCanvas("cXjg","",500,500);
    for(int ipu=0; ipu<nPurity; ipu++){
        handsomeTH1(meanXjg[ipu],ipu+1);
            meanXjg[ipu]->SetYTitle("<x_{J#gamma}>  (>30GeV)");
            //meanXjg[ipu]->SetAxisRange(-2,2,"X");
            meanXjg[ipu]->SetAxisRange(0.6, 1.2,"Y");
            //meanXjg[ipu]->SetMarkerStyle(24);
        if (ipu==0) meanXjg[ipu]->Draw();
        else meanXjg[ipu]->Draw("same");
    }
    //l1 ->Draw();

    TCanvas* cRjg = new TCanvas("cRjg","",500,500);
    for(int ipu=0; ipu<nPurity; ipu++){
        handsomeTH1(rjg[ipu],ipu+1);
            rjg[ipu]->SetYTitle("<r_{J#gamma}>  (>30GeV)");
            //rjg[ipu]->SetAxisRange(-2,2,"X");
            rjg[ipu]->SetAxisRange(0.0, 1.1,"Y");
            //rjg[ipu]->SetMarkerStyle(24);
        if (ipu==0) rjg[ipu]->Draw();
        else rjg[ipu]->Draw("same");
    }
    //l1 ->Draw();

}
