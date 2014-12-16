#include "../HiForestAnalysis/hiForest.h"
#include "../gammaJetAnalysis/CutAndBinCollection2012.h"
#include "TH1D.h"
#include "TTree.h"
#include "TFile.h"
#include "TStyle.h"
#include "TCanvas.h"
#include <iostream>

void showerShape(){
    gStyle -> SetOptStat(0);

    const int npt = 4;
    int ptBin[npt+1] = {40, 50,60,80,9999};
    TH1D* ecalEM[5];//[pt]
    TH1D* hcalEM[5];//[pt]
    TH1D* trackEM[5];//[pt]
    TH1D* sumEM[5];//[pt]
    TH1D* hovereEM[5];//[pt]

    TH1D* ecal[5];//[pt]
    TH1D* hcal[5];//[pt]
    TH1D* track[5];//[pt]
    TH1D* sum[5];//[pt]
    TH1D* hovere[5];//[pt]

    for(int ipt=0; ipt< npt; ipt++){
        ecal[ipt] = new TH1D(Form("ecal_%d", ipt), ";photon Ecal ISO (GeV) ; Normalized Entries", 40, 0, 20);
        ecalEM[ipt] = new TH1D(Form("ecalEM_%d", ipt), ";photon Ecal ISO ; Normalized Entries", 40, 0, 20);
        hcal[ipt] = new TH1D(Form("hcal_%d", ipt), ";photon Hcal ISO (GeV) ; Normalized Entries", 40, 0, 15);
        hcalEM[ipt] = new TH1D(Form("hcalEM_%d", ipt), ";photon Hcal ISO ; Normalized Entries", 40, 0, 15);
        track[ipt] = new TH1D(Form("track_%d", ipt), ";photon Track ISO (GeV); Normalized Entries", 60, 0, 30);
        trackEM[ipt] = new TH1D(Form("trackEM_%d", ipt), ";photon Track ISO ; Normalized Entries", 60, 0, 30);
        sum[ipt] = new TH1D(Form("sum_%d", ipt), ";photon Sum ISO (GeV); Normalized Entries", 40, -25, 270);
        sumEM[ipt] = new TH1D(Form("sumEM_%d", ipt), ";photon Sum ISO ; Normalized Entries", 40, -25, 270);
        hovere[ipt] = new TH1D(Form("hovere_%d", ipt), "; H/E ratio; Normalized Entries", 40, 0, 0.1);
        hovereEM[ipt] = new TH1D(Form("hovereEM_%d", ipt), "; H/E ratio; Normalized Entries", 40, 0, 0.1);
    }

    multiTreeUtil* tgj = new multiTreeUtil();
    multiTreeUtil* tgjEM = new multiTreeUtil();

    multiTreeUtil* photon = new multiTreeUtil();
    multiTreeUtil* photonEM = new multiTreeUtil();


    //pp                                            

    tgj->addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_merged_allQCDPhoton30to50_genPhotonPtCut30_CMSSW538HIp2.root", "tgj", "",29329. / 29329.);
    tgj->addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_merged_allQCDPhoton50to80_genPhotonPtCut30_CMSSW538HIp2.root", "tgj", "",8098. / 87988.);
    tgj->addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_merged_allQCDPhoton80to120_genPhotonPtCut30_CMSSW538HIp2.root", "tgj", "",1680. / 96756.);
    tgj->addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_merged_allQCDPhoton120to9999_genPhotonPtCut30_CMSSW538HIp2.root", "tgj", "", 438.   / 90972.);

    tgj->AddFriend("yJet");
    tgj->AddFriend("yPhotonTree");

    tgjEM->addFile("/home/jazzitup/forestFiles/yskimmedFiles/everythingBeforeOct19th/yskim_emDijet30to50_CMSSW538HIp2.root", "tgj", "",31957./31957.);
    tgjEM->addFile("/home/jazzitup/forestFiles/yskimmedFiles/everythingBeforeOct19th/yskim_emDijet50to80_CMSSW538HIp2.root", "tgj", "",46494./114811.);
    tgjEM->addFile("/home/jazzitup/forestFiles/yskimmedFiles/everythingBeforeOct19th/yskim_emDijet80to120_CMSSW538HIp2.root", "tgj", "",17265./121988.);
    tgjEM->addFile("/home/jazzitup/forestFiles/yskimmedFiles/everythingBeforeOct19th/yskim_emDijet120to9999_CMSSW538HIp2.root", "tgj", "", 4284./130444.);

    tgjEM->AddFriend("yJet");
    tgjEM->AddFriend("yPhotonTree");

    //for hovere, not skimmed file.                                            

    photon->addFile("/home/jazzitup/forestFiles/pp/merged_allQCDPhoton30to50_genPhotonPtCut30_CMSSW538HIp2.root", "photon", "",29329. / 29329.);
    photon->addFile("/home/jazzitup/forestFiles/pp/merged_allQCDPhoton50to80_genPhotonPtCut30_CMSSW538HIp2.root", "photon", "",8098. / 87988.);
    photon->addFile("/home/jazzitup/forestFiles/pp/merged_allQCDPhoton80to120_genPhotonPtCut30_CMSSW538HIp2.root", "photon", "",1680. / 96756.);
    photon->addFile("/home/jazzitup/forestFiles/pp/merged_allQCDPhoton120to9999_genPhotonPtCut30_CMSSW538HIp2.root", "photon", "", 438.   / 90972.);

  //  photon->AddFriend("yJet");
  //  photon->AddFriend("yPhotonTree");

    photonEM->addFile("/home/jazzitup/forestFiles/pp/emDijet30to50_CMSSW538HIp2.root", "photon", "",31957./31957.);
    photonEM->addFile("/home/jazzitup/forestFiles/pp/emDijet50to80_CMSSW538HIp2.root", "photon", "",46494./114811.);
    photonEM->addFile("/home/jazzitup/forestFiles/pp/emDijet80to120_CMSSW538HIp2.root", "photon", "",17265./121988.);
    photonEM->addFile("/home/jazzitup/forestFiles/pp/emDijet120to9999_CMSSW538HIp2.root", "photon", "", 4284./130444.);

  //  photonEM->AddFriend("yJet");
  //  photonEM->AddFriend("yPhotonTree");

    TCanvas* c1 = new TCanvas("c1", "ecal", 1200, 300);
    c1 -> Divide(4,1); 

    TCanvas* c2 = new TCanvas("c2", "hcal", 1200, 300);
    c2 -> Divide(4,1); 

    TCanvas* c3 = new TCanvas("c3", "track", 1200, 300);
    c3 -> Divide(4,1); 

    TCanvas* c4 = new TCanvas("c4", "sum", 1200, 300);
    c4 -> Divide(4,1); 

    TCanvas* c5 = new TCanvas("c5", "hovere", 1200, 300);
    c5 -> Divide(4,1); 

    for(int ipt=0; ipt< npt; ipt++) {
        c1 -> cd(ipt+1);
        tgj -> Draw2(ecal[ipt], "ecalIso", Form("photonEt>%d && photonEt<%d", ptBin[ipt], ptBin[ipt+1]), "");
        tgjEM -> Draw2(ecalEM[ipt], "ecalIso", Form("photonEt>%d && photonEt<%d", ptBin[ipt], ptBin[ipt+1]), "");
        ecal[ipt] -> Scale(1./ecal[ipt]->Integral("width"));
        ecalEM[ipt] -> Scale(1./ecalEM[ipt]->Integral("width"));
        ecal[ipt] -> SetFillStyle(3005);
        ecalEM[ipt] -> SetFillStyle(3002);
        ecal[ipt] -> SetFillColor(kRed);
        ecalEM[ipt] -> SetFillColor(kBlue);

        ecal[ipt] ->GetXaxis()->CenterTitle();
        ecal[ipt] -> Draw("hist");
        ecalEM[ipt] -> Draw("same hist");
        /*  if(ipt==0){ l2 -> AddEntry(ecal[0], "MC #gamma-jet + HYDJET");
            l2 -> AddEntry(ecalEM[0], "MC dijet Background");
            l2 -> Draw();
            } */ 
        double dx1=0.15;

        if ( ipt == npt ) 
            drawText(Form("p_{T}^{#gamma} > %dGeV, ", (int)ptBin[ipt]), 0.12+dx1+0.25,0.85,1,15);
        else
            drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV, ", (int)ptBin[ipt], (int)ptBin[ipt+1]), 0.12+dx1,0.85,1,15);

        c2 -> cd(ipt+1);
        tgj -> Draw2(hcal[ipt], "hcalIso", Form("photonEt>%d && photonEt<%d", ptBin[ipt], ptBin[ipt+1]), "");
        tgjEM -> Draw2(hcalEM[ipt], "hcalIso", Form("photonEt>%d && photonEt<%d", ptBin[ipt], ptBin[ipt+1]), "");
        hcal[ipt] -> Scale(1./hcal[ipt]->Integral("width"));
        hcalEM[ipt] -> Scale(1./hcalEM[ipt]->Integral("width"));
        hcal[ipt] -> SetFillStyle(3005);
        hcalEM[ipt] -> SetFillStyle(3002);
        hcal[ipt] -> SetFillColor(kRed);
        hcalEM[ipt] -> SetFillColor(kBlue);
        hcal[ipt]->GetXaxis()->CenterTitle();
        hcal[ipt] ->Draw("hist");
        hcalEM[ipt] -> Draw("same hist");
    /*    if(ipt==0){ 
            l2 -> AddEntry(ecal[0], "MC #gamma-jet + HYDJET");
            l2 -> AddEntry(ecalEM[0], "MC dijet Background");
            l2 -> Draw();
        } */  
        if ( ipt == npt ) 
            drawText(Form("p_{T}^{#gamma} > %dGeV, ", (int)ptBin[ipt]), 0.12+dx1+0.25,0.85,1,15);
        else
            drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV, ", (int)ptBin[ipt], (int)ptBin[ipt+1]), 0.12+dx1,0.85,1,15);


        c3 -> cd(ipt+1);
        tgj -> Draw2(track[ipt], "trackIso", Form("photonEt>%d && photonEt<%d", ptBin[ipt], ptBin[ipt+1]), "");
        tgjEM -> Draw2(trackEM[ipt],"trackIso", Form("photonEt>%d && photonEt<%d", ptBin[ipt], ptBin[ipt+1]), "");
        track[ipt] -> SetFillStyle(3005);
        trackEM[ipt] -> SetFillStyle(3002);
        track[ipt] -> SetFillColor(kRed);
        trackEM[ipt] -> SetFillColor(kBlue);
        track[ipt] -> Scale(1./track[ipt]->Integral("width"));
        trackEM[ipt] -> Scale(1./trackEM[ipt]->Integral("width"));

        track[ipt]->GetXaxis()->CenterTitle(); 
        track[ipt] -> Draw("hist");
        trackEM[ipt] -> Draw("same hist");
      /*  if(ipt==0){ l2 -> AddEntry(hcal[0], "MC #gamma-jet + HYDJET");
            l2 -> AddEntry(hcalEM[0], "MC dijet Background");
            l2 -> Draw();
        } */
        if ( ipt == npt ) 
            drawText(Form("p_{T}^{#gamma} > %dGeV, ", (int)ptBin[ipt]), 0.12+dx1+0.25,0.85,1,15);
        else
            drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV, ", (int)ptBin[ipt], (int)ptBin[ipt+1]), 0.12+dx1,0.85,1,15);


        c4 -> cd(ipt+1);
        tgj -> Draw2(sum[ipt], "sumIso", Form("photonEt>%d && photonEt<%d", ptBin[ipt], ptBin[ipt+1]), "");
        tgjEM -> Draw2(sumEM[ipt], "sumIso", Form("photonEt>%d && photonEt<%d", ptBin[ipt], ptBin[ipt+1]), "");
        sum[ipt] -> Scale(1./sum[ipt]->Integral("width"));
        sumEM[ipt] -> Scale(1./sumEM[ipt]->Integral("width"));
        sum[ipt] -> SetFillStyle(3005);
        sumEM[ipt] -> SetFillStyle(3002);
        sum[ipt] -> SetFillColor(kRed);
        sumEM[ipt] -> SetFillColor(kBlue);

        sum[ipt]->GetXaxis()->CenterTitle(); 
        sum[ipt] ->Draw("hist");
        sumEM[ipt] -> Draw("same hist");
    /*    if(ipt==0){ l2 -> AddEntry(sum[0], "MC #gamma-jet + HYDJET");
            l2 -> AddEntry(sumEM[0], "MC dijet Background");
            l2 -> Draw();
        }*/
        if ( ipt == npt ) 
            drawText(Form("p_{T}^{#gamma} > %dGeV, ", (int)ptBin[ipt]), 0.12+dx1+0.25,0.85,1,15);
        else
            drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV, ", (int)ptBin[ipt], (int)ptBin[ipt+1]), 0.12+dx1,0.85,1,15);
        
        c5 -> cd(ipt+1);
        photon -> Draw2(hovere[ipt], "hadronicOverEm", Form("pt>%d && pt<%d", ptBin[ipt], ptBin[ipt+1]), "");
        photonEM -> Draw2(hovereEM[ipt], "hadronicOverEm", Form("pt>%d && pt<%d", ptBin[ipt], ptBin[ipt+1]), "");
       // photon -> Draw2(hovere[ipt], "hadronicOverEm", Form("photonEt>%d && photonEt<%d", ptBin[ipt], ptBin[ipt+1]), "");
       // photonEM -> Draw2(hovereEM[ipt], "hadronicOverEm", Form("photonEt>%d && photonEt<%d", ptBin[ipt], ptBin[ipt+1]), "");
        hovere[ipt] -> Scale(1./hovere[ipt]->Integral("width"));
        hovereEM[ipt] -> Scale(1./hovereEM[ipt]->Integral("width"));
        hovere[ipt] -> SetFillStyle(3005);
        hovereEM[ipt] -> SetFillStyle(3002);
        hovere[ipt] -> SetFillColor(kRed);
        hovereEM[ipt] -> SetFillColor(kBlue);
        hovere[ipt]->GetXaxis()->CenterTitle();
        hovere[ipt] ->Draw("hist");
        hovereEM[ipt] -> Draw("same hist");
    /*    if(ipt==0){ 
            l2 -> AddEntry(ecal[0], "MC #gamma-jet + HYDJET");
            l2 -> AddEntry(ecalEM[0], "MC dijet Background");
            l2 -> Draw();
        } */  
        if ( ipt == npt ) 
            drawText(Form("p_{T}^{#gamma} > %dGeV, ", (int)ptBin[ipt]), 0.12+dx1+0.25,0.85,1,15);
        else
            drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV, ", (int)ptBin[ipt], (int)ptBin[ipt+1]), 0.12+dx1,0.85,1,15);



    }
    TLegend* l2 = new TLegend(0.2618875,0.5862845,0.7817362,0.7888655,NULL,"brNDC");
    l2 -> SetFillStyle(0); 
    l2 -> SetBorderSize(0);
    l2 -> AddEntry(sum[0], "pythia #gamma-jet");
    l2 -> AddEntry(sumEM[0], "pythia dijet Background");
    
    c1 -> cd(1);        
    l2 -> Draw();
    c2 -> cd(1);        
    l2 -> Draw();
    c3 -> cd(1);        
    l2 -> Draw();
    c4 -> cd(1);        
    l2 -> Draw();
    c5 -> cd(1);        
    l2 -> Draw();
     
    c1 -> SaveAs("graphics/ecal_phoIdVariable.pdf");
    c2 -> SaveAs("graphics/hcal_phoIdVariable.pdf");
    c3 -> SaveAs("graphics/track_phoIdVariable.pdf");
    c4 -> SaveAs("graphics/sum_phoIdVariable.pdf");
    c5 -> SaveAs("graphics/hovere_phoIdVariable.pdf");

}


