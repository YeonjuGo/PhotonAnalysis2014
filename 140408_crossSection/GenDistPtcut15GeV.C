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

void GenDistPtcut15GeV(int num=1){

   // TFile* f = new TFile("Pyquen_AllQCDPhotons_PtHat15_PhotonFilter_pt15GeV_eta3_TuneZ2_Unquenched_2760GeV.root");
   // TFile* f = new TFile("Pyquen_AllQCDPhotons_PtHat15_PhotonFilter_pt15GeV_eta3_TuneZ2_Unquenched_2760GeV.root");
   // TFile* f = new TFile("Pyquen_AllQCDPhotons_PtHat30_PhotonFilter_pt15GeV_eta3_TuneZ2_Unquenched_2760GeV_event1000.root");
   // TFile* f = new TFile("Pyquen_AllQCDPhotons_PtHat50_PhotonFilter_pt15GeV_eta3_TuneZ2_Unquenched_2760GeV_event1000.root");
   // TFile* f = new TFile("Pyquen_AllQCDPhotons_PtHat80_PhotonFilter_pt15GeV_eta3_TuneZ2_Unquenched_2760GeV_event1000.root");
   // TFile* f = new TFile("Pyquen_AllQCDPhotons_PtHat120_PhotonFilter_pt15GeV_eta3_TuneZ2_Unquenched_2760GeV_event1000.root");
    TFile* f = new TFile("Pyquen_AllQCDPhotons_PtHat170_PhotonFilter_pt15GeV_eta3_TuneZ2_Unquenched_2760GeV_event1000.root");
    TTree* t = (TTree*) f -> Get("genpana/photon");
 //  cout << "lsdjf" << endl; 
    Int_t cBin, nPar, id[3000], momId[3000], status[3000], collId[3000];
    Float_t hf, recoVtxZ, ptHat, pt[3000], et[3000], eta[3000], phi[3000], charge[3000]; 
    
    t -> SetBranchAddress("cBin", &cBin);
    t -> SetBranchAddress("hf", &hf);
    t -> SetBranchAddress("nPar", &nPar);
    t -> SetBranchAddress("recoVtxZ", &recoVtxZ);
    t -> SetBranchAddress("et", &et);
    t -> SetBranchAddress("pt", &pt);
   // t -> SetBranchAddress("ptHat", &ptHat);
    t -> SetBranchAddress("eta", &eta);
    t -> SetBranchAddress("phi", &phi);
    t -> SetBranchAddress("charge", &charge);
    t -> SetBranchAddress("id", &id);
    t -> SetBranchAddress("momId", &momId);
    t -> SetBranchAddress("status", &status);
    t -> SetBranchAddress("collId", &collId);
    
//    cout << "sdgwggg" << endl;
    double tempPt = 0;
    int tempIndex =0;
    TH1D* h = new TH1D("h", ";p_{T} (GeV); Entries", 50, 0, 300);
    TH1D* hbkg = new TH1D("hbkg", ";p_{T} (GeV); Entries", 50, 0, 300);
    TH1D* hdirect = new TH1D("hdirect", ";p_{T} (GeV); Entries", 50, 0, 300);
    TH1D* hfrag = new TH1D("hfrag", ";p_{T} (GeV); Entries", 50, 0, 300);
    
    hbkg -> SetLineColor(2); 
    hdirect -> SetLineColor(3); 
    hfrag -> SetLineColor(4); 
    
    for(int i=0; i<t->GetEntries(); i++){
        t -> GetEntry(i);
      //  cout << "i = " << i <<  ", nPar : " << nPar << endl;
        for(int j=0; j<nPar; j++){
            if(id[j]!=22) continue;
            if(fabs(eta[j])>3) continue;
            if(status[j]!=1) continue;
          //  if(pt[j]<=35) continue;
          //  cout << "survive!! j = " << j << endl;
            if(pt[j]>=tempPt){
                tempPt = pt[j];
                tempIndex = j;
            }
          //  cout << "pt"<< j << " : " << pt[j] << ", temp : " << tempPt << endl;
        }
      //  if(tempPt>=35){
        h -> Fill(tempPt);
        if(abs(momId[tempIndex])<22) hfrag -> Fill(tempPt);
        else if(abs(momId[tempIndex])==22) hdirect -> Fill(tempPt);
        else if(abs(momId[tempIndex])>22) hbkg -> Fill(tempPt);
       // }
        tempPt =0;
        tempIndex =0;
    }
    TCanvas* c1 = new TCanvas("c1", "c1", 400, 400);
    h -> Draw();
    hbkg -> Draw("same");
    hdirect -> Draw("same");
    hfrag -> Draw("same");
    gPad -> SetLogy();

    TLegend* l1 = new TLegend(0.4,0.6,0.87,0.80);
    l1 -> AddEntry("hbkg", "background");
    l1 -> AddEntry("hdirect", "direct photon");
    l1 -> AddEntry("hfrag", "fragmentation photon");
    l1 -> Draw();
    
    
    // directRatio = direct/(direct+frag), fragRatio = frag/(direct+frag)
    // for 15, 30, 
    double directRatio[3];
    double fragRatio[3];
    double direct[3];
    double frag[3];
    direct[0] = hdirect->Integral(hdirect->FindBin(15),hdirect->FindBin(300));
    direct[1] = hdirect->Integral(hdirect->FindBin(30),hdirect->FindBin(300));
    direct[2] = hdirect->Integral(hdirect->FindBin(60),hdirect->FindBin(300));
    frag[0] = hfrag->Integral(hfrag->FindBin(15),hfrag->FindBin(300));
    frag[1] = hfrag->Integral(hfrag->FindBin(30),hfrag->FindBin(300));
    frag[2] = hfrag->Integral(hfrag->FindBin(60),hfrag->FindBin(300));
    
    directRatio[0] = direct[0]/(direct[0]+frag[0]);
    directRatio[1] = direct[1]/(direct[1]+frag[1]);
    directRatio[2] = direct[2]/(direct[2]+frag[2]);
    
    fragRatio[0] = frag[0]/(direct[0]+frag[0]);
    fragRatio[1] = frag[1]/(direct[1]+frag[1]);
    fragRatio[2] = frag[2]/(direct[2]+frag[2]); 
    
    
    cout << directRatio[0]<< endl;
    cout << directRatio[1]<< endl;
    cout << directRatio[2]<< endl;
    cout << fragRatio[0]<< endl;
    cout << fragRatio[1]<< endl;
    cout << fragRatio[2]<< endl;
}

