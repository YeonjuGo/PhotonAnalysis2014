// yeonju
// pt fine bin 
#include "../HiForestAnalysis/hiForest.h"
#include "../gammaJetAnalysis/CutAndBinCollection2012.h"
#include <TStyle.h>
#include <TH1D.h>
#include <TTree.h>
#include <TBranch.h>
#include <TFile.h>
#include <iostream>
#include <TCanvas.h>
#include <TF1.h>
#include <TGraphAsymmErrors.h>
#include <TLegend.h>
#include <TCut.h>

double myFunc(double *x, double *par){
   return par[0]+ par[1]/sqrt(x[0]) + par[2]/x[0];
}

double myFunc2(double *x, double *par){
    return sqrt(0.0567511*0.0567511+ 0.808756*0.808756/x[0] + par[0]*par[0]/(x[0]*x[0]));
}  

double myFunc3(double *x, double *par){
    return sqrt(par[0]*par[0]+ par[1]*par[1]/x[0] + par[2]*par[2]/(x[0]*x[0]));
}


void phiResol(int collision = 2, int flvOpt = 0, int genOpt = 0){
    /*  const int kHIcentral = 0; // 0-30%
        const int kHIperipheral = 1;//30-100%
        const int kPP = 2;
        const int kPA = 3;
        const int kHI010 = 4; //0-10%
        const int kHI1030 = 5; //10-30%
        const int kHI3050 = 6;//30-50%
        const int kHI50100 = 7;//50-100%
*/
   // const int collision = 3;
    TLegend *l1 = new TLegend(0.4365615,0.6445304,0.9577623,0.846736,NULL,"brNDC");

    TCut centCut = "";
    if ( (collision ==0) )   {   // PbPb 0-30 %
        centCut = "cBin > 0 && cBin< 12";
        easyLeg(l1,"Pb+Pb 0-30%");
    }
    else if (  (collision ==1) ){  // PbPb 30-100 % 
        centCut = "cBin >=12";
        easyLeg(l1,"Pb+Pb 30-100%");
    }
    else if (collision == 2 || collision == 3){ // pPb
        centCut = "";
        if (collision == 2) easyLeg(l1,"p+p");
        else easyLeg(l1, "p+Pb");
    }
    else if (  (collision ==4) ){  //PbPb 0-10 %
        centCut = "cBin > 0 && cBin < 4";
        easyLeg(l1,"Pb+Pb 0-10%");
    } else if (  (collision ==5) ){  //PbPb 10-30 %
        centCut = "cBin >= 4 && cBin < 12";
        easyLeg(l1,"Pb+Pb 10-30%");
    } else if (  (collision ==6) ){  //PbPb 30-50 %
        centCut = "cBin >= 12 && cBin < 20";
        easyLeg(l1,"Pb+Pb 30-50%");
    } else if (  (collision ==7) ){  //PbPb 50-100 %
        centCut = "cBin >= 20";
        easyLeg(l1,"Pb+Pb 50-100%");
    }    

    TH1::SetDefaultSumw2();

    // gStyle->SetOptFit(0);
    gStyle -> SetOptStat(0);
    //  gStyle -> SetTitleYOffset(2.35);
    gStyle -> SetTitleYSize(0.04);


    TCut partonCut = "";
    if (flvOpt ==0 ) partonCut = "";
    else if (flvOpt == 1 ) partonCut = "refPartonFlv == 21";
    else if (flvOpt == 2 ) partonCut = "abs(refPartonFlv) < 21";
    else partonCut = "refPartonFlv < -200";


    const int nPtBin = 12;
    //const int nPtBin = 17;
    //double ptBin[nPtBin+1] = {30.0, 40.0, 50.0, 80.0, 9999.0}; 
    //double AvePtBin[nPtBin+1] = { 35.0, 45.0, 65.0, 100.0};
    double ptBin[nPtBin+1];
    double AvePtBin[nPtBin];

    ptBin[0] = 30.0;
    ptBin[1] = 40.0;
    ptBin[2] = 50.0;
    ptBin[3] = 60.0;
    ptBin[4] = 70.0;
    ptBin[5] = 80.0;
    ptBin[6] = 90.0;
    ptBin[7] = 100.0;
    ptBin[8] = 120.0;
    ptBin[9] = 140.0;
    ptBin[10] = 160.0;
    ptBin[11] = 180.0;
    ptBin[12] = 200.0;

    /*
       for(int i=0;i<=nPtBin;i++){
       ptBin[i] = 30.0+i*10.0;
       }
       */  
    for(int i=0;i<nPtBin;i++){
        AvePtBin[i] = (ptBin[i+1]+ptBin[i])/2.0;
    }

    int icent =1;
    //    const int nCentBinPa = 3;
    //   double centBinPa[nCentBinPa+1] = {0,20,30,100};

    //
    // fake rate
    //

    multiTreeUtil* yJet = new multiTreeUtil();
    //:PbPb
    if(collision ==1 || collision == 0  || collision == 4 || collision == 5 || collision == 6|| collision == 7){
        yJet -> addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_qcdAllPhoton30to50_genPhotonPtCut40_allCent.root", "yJet", "",32796./32796);
        yJet -> addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_qcdAllPhoton50to80_genPhotonPtCut40_allCent.root", "yJet", "",21470./53876);
        yJet -> addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_qcdAllPhoton80to9999_genPhotonPtCut40_allCent.root", "yJet", "",6462./58781);  
    } else if (collision ==3){
        // pA
        yJet->addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_PA2013_pyquen_allQCDPhoton30to50_forestv85.root", "yJet","", 56669./50385);
        yJet->addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_PA2013_pyquen_allQCDPhoton50to80_forestv85.root", "yJet","", 41906./114136);
        yJet->addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_PA2013_pyquen_allQCDPhoton80to120_forestv85.root", "yJet","",12044./103562);
        yJet->addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_PA2013_pyquen_allQCDPhoton120to9999_forestv85.root", "yJet","", 4481./151511);
    } else if (collision ==2){
        //pp 
        yJet->addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_merged_allQCDPhoton30to50_genPhotonPtCut30_CMSSW538HIp2.root", "yJet", "",29329. / 29329.);
        yJet->addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_merged_allQCDPhoton50to80_genPhotonPtCut30_CMSSW538HIp2.root", "yJet", "",8098. / 87988.);
        yJet->addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_merged_allQCDPhoton80to120_genPhotonPtCut30_CMSSW538HIp2.root", "yJet", "",1680. / 96756.);
        yJet->addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_merged_allQCDPhoton120to9999_genPhotonPtCut30_CMSSW538HIp2.root", "yJet", "", 438.   / 90972.);
    }

    yJet -> AddFriend("tgj");
    yJet->AddFriend("yPhotonTree");
    //
    // Energy Scale
    //
    TCanvas* c2 = new TCanvas("c2", "phi/refPhi distribution", 1200, 900); 
    makeMultiPanelCanvas(c2,4,3,0.0,0.0,0.2,0.15,0.02);
    TCanvas* ccc = new TCanvas("ccc", "pt/refpt 30-40GeV", 800, 400); 
    ccc -> Divide(2,1);

    TH1D* phi[nCentBinPa+5][nPtBin];
    double mean[nCentBinPa+5][nPtBin], var[nCentBinPa+5][nPtBin], resol[nCentBinPa+5][nPtBin], resolVar[nCentBinPa+5][nPtBin];
    for(int i=0; i < nPtBin ; i++){
        c2 -> cd(i+1);
        phi[icent][i] = new TH1D(Form("phi%d_%d",icent, i) , " ;  p_{T}^{RECO}/p_{T}^{GEN}", 50, 0, 2);

        if ( genOpt == 0 )  {
            yJet -> Draw2(phi[icent][i], "phi/refPhi", centCut && partonCut && Form(" (abs(eta) < 1.6) && (dphi > 0.5) && (refPt >= %d && refPt < %d)", (int)ptBin[i], (int)ptBin[i+1]),""); 
            //yJet -> Draw2(phi[icent][i], "phi/refPhi", centCut && partonCut && Form(" (abs(eta) < 1.6) && (phi > 7*3.141592/8.0) && (refPt >= %d && refPt < %d)", (int)ptBin[i], (int)ptBin[i+1]),""); 
        }
        else if (genOpt == 1)  {
            yJet -> Draw2(phi[icent][i], "phi/refPhi", centCut && partonCut && Form(" (abs(eta) < 1.6) && (dphi > 7*3.141592/8.0) && (pt >= %d && pt < %d) ", (int)ptBin[i], (int)ptBin[i+1]),"");
        }
        
        TF1* ff = cleverGaus(phi[icent][i]);
        gPad->SetLogy();
        mean[icent][i] = ff->GetParameter(1);
        var[icent][i] = ff->GetParError(1);
        resol[icent][i] = ff->GetParameter(2);
        resolVar[icent][i] = ff->GetParError(2);

        float dx1;    
        dx1=0.05;
        if ( i+1 == nPtBin ) 
            drawText(Form("p_{T}^{GEN Jet} > %dGeV, ", (int)ptBin[i]), 0.16+dx1,0.84,1,15);//yeonju 130823
        else
            drawText(Form("%dGeV < p_{T}^{GEN Jet} < %dGeV, ", (int)ptBin[i], (int)ptBin[i+1]), 0.17+dx1,0.84,1,12);//yeonju 130823
    }

    c2 -> Update();

    ccc -> cd(1);
    phi[1][0]->Draw();
    ccc -> cd(2);
    phi[1][1]->Draw();


    //
    // Energy Scale
    //

    TCanvas *c3 = new TCanvas("c3", "#phi Scale vs. jet pt",147,37,930,465);
    c3->Divide(2,1);
    c3->cd(1);
    
    double bin[nPtBin+1];
    
    for(int ibin=0; ibin<nPtBin+1; ibin++){
        bin[ibin]=ptBin[ibin];
    }
    
    TH1D* hscale = new TH1D("hscale", ";JetP_{T}^{GEN} (GeV); #phi Scale ", nPtBin, bin);
    l1 -> Draw();
    handsomeTH1(hscale,1);
//    hscale -> SetAxisRange(0.9, 1.15, "Y");
    hscale -> Draw();
    jumSun(30,1,200,1);
    
    TLegend *l3=new TLegend(0,0,0.4490239,0.08695652,NULL,"brNDC");
    l3->SetTextFont(42);
    l3->SetTextSize(0.04);
    l3->SetFillColor(0);
    l3->SetLineColor(0);

    for(int i=0; i < nPtBin ; i++){ 
        hscale -> SetBinContent(i+1, mean[icent][i]);
        hscale -> SetBinError(i+1, var[icent][i]);
        hscale -> SetMarkerStyle(20);
        hscale -> SetMarkerSize(1);
        hscale -> Draw("same p");
    }

    TF1 *fs = new TF1("fs", myFunc3, 30, 200, 3);
    fs -> SetParameters(0.9,0.8,0.001);
    fs -> SetParNames("scale_C", "scale_S", "scale_N");

    double params[3];

    hscale -> Fit("fs", "RLL");
    fs->GetParameters(params);
    cout << " scale C : " << params[0] << ", S : " << params[1] << ", N : : " << params[2] << endl;
    fs->Draw("same");


    //
    // Energy Resolution
    //
   // c3->cd(2);

    TCanvas *c4 = new TCanvas("c4", "phi resolution", 400, 400);
    c4 -> cd();

    TH1D* hresol = new TH1D("hresol", ";JetP_{T} (GeV); #phi Resolution ", nPtBin, bin);
    handsomeTH1(hresol,1);
    hresol -> SetAxisRange(0.0, 0.1, "Y");
    hresol->GetYaxis()->CenterTitle();
    hresol -> Draw();

    jumSun(30,0.0,30,0.3,2);

    TLegend *l_resol=new TLegend(0.40,0.20,0.85,0.42);
    l_resol->SetTextFont(42);
    l_resol->SetTextSize(0.04);
    l_resol->SetFillColor(0);
    l_resol->SetLineColor(0);

    for(int i=0; i < nPtBin ; i++){ 
        hresol -> SetBinContent(i+1, resol[icent][i]);
        hresol -> SetBinError(i+1, resolVar[icent][i]);
        hresol -> SetMarkerStyle(20);
        hresol -> SetMarkerSize(1);
        hresol -> Draw("same p");
    }
    
    TF1 *f;
    f = new TF1("f", myFunc3, 30, 200, 3);
    f -> SetParameters(0.02, 0.8, 0.001);
    f -> SetParNames("resol_C", "resol_S", "resol_N");
    
    double param[3];
    
    hresol -> Fit("f", "RLL");
    f->GetParameters(param);
   // cout << " resol_N : " << param[0]<< endl;
    cout << " resol C : " << param[0] << ", S : " << param[1] << ", N : : " << param[2] << endl;
 //  else cout << " N : " << param[0] << endl;
    f->Draw("same");
    l1 -> Draw();

    //  l_resol->Draw();
    c2 -> SaveAs(Form("./graph/phi_distribution_collision%d.pdf",collision));
   // c3 -> SaveAs(Form("./graph/phi_scale_resolution_fit_collision%d.pdf",collision));
    c4 -> SaveAs(Form("./graph/phi_resolution_fit_collision%d.pdf",collision));
}
