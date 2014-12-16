#include <TROOT.h>
#include <TStyle.h>
#include <TH1D.h>
#include <TH1F.h>
#include <TTree.h>
#include <TBranch.h>
#include <TFile.h>
#include <TChain.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <TCanvas.h>
#include <TString.h>
#include <TF1.h>
#include <TGraphAsymmErrors.h>
#include <TLegend.h>
#include <TCut.h>
#include <TPad.h>

void ptHatDist(int num=1){

   //   TFile* f = new TFile("Pyquen_AllQCDPhotons_PtHat5_PhotonFilter_pt5GeV_eta3_TuneZ2_Unquenched_2760GeV.root");
     TFile* f = new TFile("Pyquen_NonLeadingQCDPhotons_PtHat15_PhotonFilter_pt15GeV_eta3_TuneZ2_Unquenched_2760GeV_event1000.root");
    // TFile* f = new TFile("Pyquen_LeadingQCDPhotons_PtHat15_PhotonFilter_pt15GeV_eta3_TuneZ2_Unquenched_2760GeV_event1000.root");
  //  TFile* f = new TFile("Pyquen_AllQCDPhotons_PtHat15_PhotonFilter_pt15GeV_eta3_TuneZ2_Unquenched_2760GeV.root");

    TTree* t = (TTree*) f -> Get("genpana/photon");

    Int_t cBin, nPar, id[3000], momId[3000], status[3000], collId[3000];
    Float_t hf, recoVtxZ, ptHat, pt[3000], et[3000], eta[3000], phi[3000], charge[3000]; 

    t -> SetBranchAddress("cBin", &cBin);
    t -> SetBranchAddress("hf", &hf);
    t -> SetBranchAddress("nPar", &nPar);
    t -> SetBranchAddress("recoVtxZ", &recoVtxZ);
    t -> SetBranchAddress("et", &et);
    t -> SetBranchAddress("pt", &pt);
    t -> SetBranchAddress("ptHat", &ptHat);
    t -> SetBranchAddress("eta", &eta);
    t -> SetBranchAddress("phi", &phi);
    t -> SetBranchAddress("charge", &charge);
    t -> SetBranchAddress("id", &id);
    t -> SetBranchAddress("momId", &momId);
    t -> SetBranchAddress("status", &status);
    t -> SetBranchAddress("collId", &collId);

    TH1D* hptHat = new TH1D("hptHat", ";p_{T}Hat (GeV); Entries", 50, 0, 200);
    int nonPhoton = 0; 
    bool isPhotonExist = 0;
    for(int i=0; i<t->GetEntries(); i++){
        t -> GetEntry(i);
        cout << i <<" th the number of nPar : " << nPar << endl; 
        for(int j=0; j<nPar; j++){
            cout << " j = " << j <<endl;
            if(id[j]!=22) continue;
            if(fabs(eta[j])>3) continue;
            if(status[j]!=1) continue;//   
            if(abs(momId[j])>22) continue;
            if(pt[j]<=35) continue;
            //if(fabs(phi[j])<3) continue;
           // if(fabs(phi[j])<3) {
           //     continue;
           // } else if(j==nPar-1) {
           //     break; 
           // } else {
            isPhotonExist = 1;
           // }
            cout << "ptHat = " << ptHat << ", leading photon pt = " << pt[j] << ", abs(momId)" << abs(momId[j])<<endl;
            //cout << id[j] << " " << fabs(eta[j]) << " " << status[j] << " " << momId[j] << " " << phi[j] << endl;
        }
        cout << " isPhotonExist = " << isPhotonExist << endl;
        if(isPhotonExist==0) nonPhoton += 1;
        if(isPhotonExist==1) hptHat -> Fill(ptHat);
        isPhotonExist = 0;
    }
    cout << " the number of events w/o any leading photons = " << nonPhoton<< endl; 
    TCanvas* c1 = new TCanvas("c1", "c1", 400, 400);
    hptHat -> Draw();
    gPad -> SetLogy();

//    t -> Draw("ptHat >> hptHat");
 //   hptHat -> Draw();

    double IptHat[3];
    double ptHatRatio[3];
    IptHat[0] = hptHat->Integral(hptHat->FindBin(15),hptHat->FindBin(300));
    IptHat[1] = hptHat->Integral(hptHat->FindBin(30),hptHat->FindBin(300));
    IptHat[2] = hptHat->Integral(hptHat->FindBin(60),hptHat->FindBin(300));
    
    ptHatRatio[0] = IptHat[0]/(IptHat[0]);
    ptHatRatio[1] = IptHat[1]/(IptHat[0]);
    ptHatRatio[2] = IptHat[2]/(IptHat[0]);
    
    cout << ptHatRatio[0]<< endl;
    cout << ptHatRatio[1]<< endl;
    cout << ptHatRatio[2]<< endl;
    
    TLegend* l1 = new TLegend(0.4,0.6,0.87,0.80);
   // l1 -> AddEntry("hbkg", "background");
   // l1 -> AddEntry("hdirect", "direct photon");
   // l1 -> AddEntry("hfrag", "fragmentation photon");
   // l1 -> Draw();


  }

