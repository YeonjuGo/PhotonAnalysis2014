#include "../HiForestAnalysis/hiForest.h"
#include "../gammaJetAnalysis/CutAndBinCollection2012.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include <iostream>
#include "TStyle.h"

void getPtMean(sampleType collision_=kPPDATA, int icent=7){
    gStyle -> SetOptStat(0);

    const int nPt = 4;
    double ptBin[nPt+1] = {40,50,60,80,9999};
    
    TH1D* hpho[nPt+1];
    TFile* histFile[nPt+1];  // [pt]                                                                                      
    double meanPt[nPt+1];
    double errorPt[nPt+1];

    for (int ipt=1 ; ipt<=nPt ; ipt++) {
        TString sampleName = getSampleName( collision_ ) ;
        char* fname = "";
        fname =  Form("../gammaJetAnalysis/histogramProducer/ffFiles/photonTrackCorr_%s_output_photonPtThr%d_to_%d_jetPtThr30_20131004.root",sampleName.Data(), (int)ptBin[ipt-1], (int)ptBin[ipt]);

        histFile[ipt] = new TFile(fname) ;
      //  cout << " Reading file : " << fname << endl;

        if ( histFile[ipt]->IsZombie()  == false ) {
         //   cout << " Success." << endl;
            hpho[ipt] = (TH1D*)histFile[ipt]->Get(Form("hPhoPtSig_icent%d", icent)) ;
         //   cout << " Getting histogram : " << Form("hPhoPtSig_icent%d", icent) << endl;
            meanPt[ipt] = hpho[ipt] -> GetMean();
            errorPt[ipt] = hpho[ipt] -> GetMeanError();
        } else cout << " no such file " << endl;
        
        cout << "sampleType" << collision_ << ", icent" << icent << ", pt "<<ptBin[ipt-1] << "to"<<ptBin[ipt]<< " mean value : " << meanPt[ipt] << " error : " <<  errorPt[ipt] << endl;
    }

}
