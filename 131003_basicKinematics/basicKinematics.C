#include "../HiForestAnalysis/hiForest.h"
#include "../gammaJetAnalysis/CutAndBinCollection2012.h"
#include <TCut.h>
#include <TTree.h>
#include <TH1D.h>
#include <TH1.h>
#include <TStyle.h>
#include <iostream>
#include <TLegend.h>

void basicKinematics(sampleType collision=kPPDATA, int icent =1){
    TH1::SetDefaultSumw2();
    gStyle -> SetOptStat(0);
    TLegend* l1 = new TLegend(0.5237065,0.6729505,0.9948735,0.8804912,NULL,"brNDC");
    if ( (collision==kPPMC) || (collision==kPPDATA) ) 
        easyLeg(l1, "p+p 2.76 TeV");
    else if ( (collision==kHIMC) || (collision==kHIDATA) )
        easyLeg(l1, "Pb+Pb 2.76 TeV");
    else {
        easyLeg(l1, "p+Pb 5.02 TeV");
    }

    //=====================photon cut =====================
    TCut centCut  = ""; 
    if ( (collision ==kHIDATA) || (collision==kHIMC) )   {   
        if ( icent == 13099) centCut = "(1==1)"; //centCut = "cBin >= 12";
        else centCut = "(1==1)"; //"cBin < 12";
    }
    else if (  (collision ==kPPDATA) || (collision==kPPMC)  ){  // if it's pp 
        centCut = "(1==1)";
    }
    else { // pPb
        centCut = "(1==1)";
     //centCut = Form( "hf4Sum > %f && hf4Sum <= %f", (float)centBinPa[icent-1], (float)centBinPa[icent]);
    }

//    cout <<" centrality : " << centCut.GetTitle() << endl;

//    cout <<" photon pt >" << photonPtThr << " GeV" << endl;
//    TCut ptPhoCut  = Form("photonEt>%.1f && photonEt<%.1f", (float)photonPtThr, (float)photonPtThrUp  );  
    TCut caloIso;

    if ( (collision==kPPMC) || (collision==kPPDATA) ) 
        caloIso = "(ecalIso < 4.2  &&  hcalIso < 2.2  &&  trackIso < 2) && hovere<0.1";
    else if ( (collision==kHIMC) || (collision==kHIDATA) )
        caloIso = "(sumIso<1) && hovere<0.1";
    else {
        caloIso = "ecalIso < 4.2  &&  hcalIso < 2.2  &&  trackIso < 2 && hovere<0.1";
    }

    TCut evtSeltCut = centCut && caloIso;

    TCut phoCandCut   = "(sigmaIetaIeta<0.010) && (abs(photonEta) < 1.44) && (photonEt>40)";
    TCut phoCut = evtSeltCut && phoCandCut;
    TCut jetCut = evtSeltCut && "abs(eta) < 1.6 && dphi > 0.5 && pt>30";

    TCut MCCut = "genIso<5 && abs(genMomId)<=22";
    TCut MCphoCut = phoCut && MCCut;
    TCut MCjetCut = jetCut && MCCut;

    //=================tree!!!!!!!!=====================
    TString fname = "";
    if ( collision == kHIDATA)      fname = fnameHIDATA;
    else if ( collision == kPADATA) fname = fnamePADATA;
    else if ( collision == kPPDATA) {
        if ( icent == 7 ) fname = fnamePPDATA;
        else if ( icent == 10010 ) fname = fnamePPDATA0010;
        else if ( icent == 11030 ) fname = fnamePPDATA1030;
        else if ( icent == 13050 ) fname = fnamePPDATA3050;
        else if ( icent == 15099 ) fname = fnamePPDATA5099;
    }
    else fname = "";

    multiTreeUtil* tgj = new multiTreeUtil();
    multiTreeUtil* tgjMC = new multiTreeUtil();
    
    if ( collision == kPPDATA || collision == kPPMC ) {
        tgj->addFile(fnamePPDATA,  "tgj",  evtSeltCut,  1);
        tgjMC->addFile(fnamePPMC_AllQcdPho30to50,    "tgj", evtSeltCut, wPPMC_AllQcdPho30to50 );
        tgjMC->addFile(fnamePPMC_AllQcdPho50to80,    "tgj", evtSeltCut, wPPMC_AllQcdPho50to80 );
        tgjMC->addFile(fnamePPMC_AllQcdPho80to120,   "tgj", evtSeltCut, wPPMC_AllQcdPho80to120 );
        tgjMC->addFile(fnamePPMC_AllQcdPho120to9999, "tgj", evtSeltCut, wPPMC_AllQcdPho120to9999 );
    }
    else if ( collision == kPAMC || collision==kPADATA ) {
        tgj->addFile(fnamePADATA,  "tgj",  evtSeltCut,  1);
        tgjMC->addFile(fnamePAMC_AllQcdPho30to50,    "tgj", evtSeltCut, wPAMC_AllQcdPho30to50 );
        tgjMC->addFile(fnamePAMC_AllQcdPho50to80,    "tgj", evtSeltCut, wPAMC_AllQcdPho50to80 );
        tgjMC->addFile(fnamePAMC_AllQcdPho80to120,   "tgj", evtSeltCut, wPAMC_AllQcdPho80to120 );
        tgjMC->addFile(fnamePAMC_AllQcdPho120to9999, "tgj", evtSeltCut, wPAMC_AllQcdPho120to9999 );
    }
    else  {    // kHIMC or kHIDATA
        tgj->addFile(fnameHIDATA,  "tgj",  evtSeltCut,  1);
        tgjMC->addFile(fnameHIMC_AllQcdPho30to50,    "tgj", evtSeltCut, wHIMC_AllQcdPho30to50 );
        tgjMC->addFile(fnameHIMC_AllQcdPho50to80,    "tgj", evtSeltCut, wHIMC_AllQcdPho50to80 );
        tgjMC->addFile(fnameHIMC_AllQcdPho80to9999,  "tgj", evtSeltCut, wHIMC_AllQcdPho80to9999 );
    }
    
    tgj->AddFriend("yJet");
    tgjMC->AddFriend("yJet");
   

    /*
    multiTreeUtil* yJet = new multiTreeUtil();
    //pp 
    yJet->addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_merged_allQCDPhoton30to50_genPhotonPtCut30_CMSSW538HIp2.root", "yJet", "",29329. / 29329.);
    yJet->addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_merged_allQCDPhoton50to80_genPhotonPtCut30_CMSSW538HIp2.root", "yJet", "",8098. / 87988.);
    yJet->addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_merged_allQCDPhoton80to120_genPhotonPtCut30_CMSSW538HIp2.root", "yJet", "",1680. / 96756.);
    yJet->addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_merged_allQCDPhoton120to9999_genPhotonPtCut30_CMSSW538HIp2.root", "yJet", "", 438.   / 90972.);

    yJet -> AddFriend("tgj");
    yJet -> AddFriend("yPhotonTree");
*/
 
//
    TH1D* photonEt[2];//[data or MC]    
    TH1D* photonEta[2];
    TH1D* photonPhi[2];
    TH1D* jetPt[2];    
    TH1D* jetEta[2];    
    TH1D* jetPhi[2];   

    for(int itype=0; itype<2; itype++){
        //=============initialize the histograms=============
        photonEt[itype] = new TH1D(Form("photonEt_%d", itype), ";E_{T}^{#gamma} ; Normalized Entires ", 28, 0, 140);
        photonEta[itype] = new TH1D(Form("photonEta_%d", itype), ";photon #eta ; Noralized Entries ", 40, -4, 4);
        photonPhi[itype] = new TH1D(Form("photonPhi_%d", itype), ";photon #phi ; Normalized Entries ", 40, -4, 4);
        jetPt[itype] = new TH1D(Form("jetPt_%d", itype), ";p_{T}^{Jet} ; Normalized Entires ", 28, 0, 140);
        jetEta[itype] = new TH1D(Form("jetEta_%d", itype), ";jet #eta ; Noralized Entries ", 40, -4, 4);
        jetPhi[itype] = new TH1D(Form("jetPhi_%d", itype), ";jet #phi ; Normalized Entries ", 40, -4, 4);
    }

    for(int itype=0; itype<2; itype++){
        if (itype==0) {
            tgj -> Draw2(photonEt[itype], "photonEt", phoCut, "");
            tgj -> Draw2(photonEta[itype], "photonEta", phoCut, "");
            tgj -> Draw2(photonPhi[itype], "photonPhi", phoCut, "");
            tgj -> Draw2(jetPt[itype], "yJet.pt", jetCut, "");
            tgj -> Draw2(jetEta[itype], "yJet.eta", jetCut, "");
            tgj -> Draw2(jetPhi[itype], "yJet.phi", jetCut, "");
        } else {
            tgjMC -> Draw2(photonEt[itype], "photonEt", MCphoCut, "");
            tgjMC -> Draw2(photonEta[itype], "photonEta", MCphoCut, "");
            tgjMC -> Draw2(photonPhi[itype], "photonPhi", MCphoCut, "");
            tgjMC -> Draw2(jetPt[itype], "yJet.pt", MCjetCut, "");
            tgjMC -> Draw2(jetEta[itype], "yJet.eta", MCjetCut, "");
            tgjMC -> Draw2(jetPhi[itype], "yJet.phi", MCjetCut, "");
        }
    }
    for(int itype=0; itype<2; itype++){
        photonEt[itype]->SetTitleOffset(1.19, "Y");
        photonEta[itype]->SetTitleOffset(1.19, "Y");
        photonPhi[itype]->SetTitleOffset(1.19, "Y");
        jetPt[itype] ->SetTitleOffset(1.19, "Y");
        jetEta[itype]->SetTitleOffset(1.19, "Y");
        jetPhi[itype]->SetTitleOffset(1.19, "Y");
       
        photonEt[itype]->GetXaxis()->CenterTitle();
        photonEta[itype]->GetXaxis()->CenterTitle();
        photonPhi[itype]->GetXaxis()->CenterTitle();
        jetPt[itype] ->GetXaxis()->CenterTitle();
        jetEta[itype]->GetXaxis()->CenterTitle();
        jetPhi[itype]->GetXaxis()->CenterTitle();
      
        if(itype==0){ 
        photonEt[itype]->SetLineColor(2); 
        photonEta[itype] ->SetLineColor(2);
        photonPhi[itype]->SetLineColor(2);
        jetPt[itype] ->SetLineColor(2);
        jetEta[itype]->SetLineColor(2);
        jetPhi[itype]->SetLineColor(2);
       }
        photonEt[itype] ->Scale(1./photonEt[itype]->Integral("width"));
        photonEta[itype] -> Scale(1./photonEta[itype]->Integral("width"));
        photonPhi[itype] -> Scale(1./photonPhi[itype]->Integral("width"));
        jetPt[itype] -> Scale(1./jetPt[itype]->Integral("width"));
        jetEta[itype] -> Scale(1./jetEta[itype]->Integral("width"));
        jetPhi[itype] -> Scale(1./jetPhi[itype]->Integral("width"));
    } 

    TLegend* l2 = new TLegend(0.5103716,0.4935144,0.832632,0.6967312,NULL,"brNDC");
    l2 -> AddEntry(jetPt[0], "DATA");
    l2 -> AddEntry(jetPt[1], "MC");
    l2 -> SetFillStyle(0); 
    l2 -> SetBorderSize(0);
    
    TCanvas* c1 = new TCanvas("c1", "c1", 1500, 500);
    c1 -> Divide(3,1); 

    TCanvas* c2 = new TCanvas("c2", "c2", 1500, 500);
    c2 -> Divide(3,1); 

    c1 -> cd(1); 
    photonEt[0] -> Draw("e");
    photonEt[1] -> Draw("same hist");
    l1 -> Draw();
    l2 -> Draw();

    c1 -> cd(2); 
    photonEta[0] -> Draw("e");
    photonEta[1] -> Draw("same hist");
   
    c1 -> cd(3); 
    photonPhi[0] -> Draw("e");
    photonPhi[1] -> Draw("same hist");
   
    c2 -> cd(1); 
    jetPt[0] -> Draw("e");
    jetPt[1] -> Draw("same hist");
    l1 -> Draw();
    l2 -> Draw();   

    c2 -> cd(2); 
    jetEta[0] -> Draw("e");
    jetEta[1] -> Draw("same hist");
   
    c2 -> cd(3); 
    jetPhi[0] -> Draw("e");
    jetPhi[1] -> Draw("same hist");

    //c1 -> Update();   
    
 //   c1 -> SaveAs(Form("basicKinematics_photon_%s.pdf",getSampleName(collision)));
 //   c2 -> SaveAs(Form("basicKinematics_jet_%s.pdf",getSampleName(collision)));
}
