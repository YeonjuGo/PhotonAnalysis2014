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

     //  TFile* f = new TFile("Pyquen_NonLeadingQCDPhotons_PtHat15_PhotonFilter_pt15GeV_eta3_TuneZ2_Unquenched_2760GeV_event1000.root");
    // TFile* f = new TFile("Pyquen_LeadingQCDPhotons_PtHat15_PhotonFilter_pt15GeV_eta3_TuneZ2_Unquenched_2760GeV_event1000.root");
  
    //TFile* f = new TFile("Pyquen_AllQCDPhotons_PtHat5_PhotonFilter_pt15GeV_eta3_TuneZ2_Unquenched_2760GeV_numEvent780.root");
    //TFile* f = new TFile("Pyquen_AllQCDPhotons_PtHat15_PhotonFilter_pt15GeV_eta3_TuneZ2_Unquenched_2760GeV_numEvent1000.root");
     //  TFile* f = new TFile("Pyquen_LeadingQCDPhotons_PtHat15_PhotonFilter_pt35GeV_eta3_TuneZ2_Unquenched_2760GeV_numEvent1000.root");
     //  TFile* f = new TFile("Pyquen_NonLeadingQCDPhotons_PtHat15_PhotonFilter_pt35GeV_eta3_TuneZ2_Unquenched_2760GeV_numEvent720.root");
     //  TFile* f = new TFile("Pyquen_AllQCDPhotons_PtHat15_PhotonFilter_pt35GeV_eta3_TuneZ2_Unquenched_2760GeV_numEvent1000.root");
    TFile* f = new TFile("Pyquen_AllQCDPhotons_PtHat5_PhotonFilter_pt15GeV_eta3_TuneZ2_Unquenched_2760GeV_numEvent10000.root");
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

    TH1D* hptHatall = new TH1D("hptHat", ";p_{T}Hat (GeV); Entries", 50, 0, 200);
    TH1D* hptHatdirect = (TH1D*) hptHatall -> Clone("hptHatdirect");
    TH1D* hptHatfrag = (TH1D*) hptHatall -> Clone("hptHatfrag");

    int nonPhoton = 0; 
    int allPhoton = 0;
    int directPhoton = 0;
    int fragPhoton = 0;
    bool isPhotonExist = 0; // does leading photon which we are interested in exist?
    bool isDirect = 0; // momId == 22 ?
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

            isPhotonExist = 1;
            if(abs(momId[j])==22) isDirect = 1;
            cout << "ptHat = " << ptHat << ", leading photon pt = " << pt[j] << ", abs(momId)" << abs(momId[j])<<endl;
        }
        cout << " isPhotonExist = " << isPhotonExist << endl;
        if(isPhotonExist==0) nonPhoton += 1;

        if(isPhotonExist==1) {
            allPhoton += 1;
            hptHatall -> Fill(ptHat);
            if(isDirect ==1) {
                directPhoton += 1;
                hptHatdirect -> Fill(ptHat);
            } else {
                fragPhoton += 1;
                hptHatfrag -> Fill(ptHat);
            }

        }
        isPhotonExist = 0;
        isDirect = 0;
    }

    cout << " the number of events w/o any leading photons = " << nonPhoton<< endl; 
    cout << " the number of all leading photons = " << allPhoton<< endl; 
    cout << " the number of direct leading photons = " << directPhoton<< endl; 
    cout << " the number of frag. leading photons = " << fragPhoton<< endl; 
    TCanvas* c1 = new TCanvas("c1", "c1", 400, 400);
    hptHatall -> Draw();
    hptHatall -> SetTitle("AllQCD Photons");
    //gPad -> SetLogy();

    TCanvas* c2 = new TCanvas("c2", "c2", 400, 400);
    hptHatdirect -> Draw();
    hptHatdirect -> SetTitle("LeadingOrder(direct) Photons");
   // gPad -> SetLogy();

    TCanvas* c3 = new TCanvas("c3", "c3", 400, 400);
    hptHatfrag -> Draw();
    hptHatfrag -> SetTitle("Non-LeadingOrder(fragmentation) Photons");
    //gPad -> SetLogy();

// =================================================
// Calculate the relative ratio of ptHat distribution
// =================================================
    
// AllQCDPhotons

    double IptHatall[3];
    double ptHatallRatio[3];
    
    IptHatall[0] = hptHatall->Integral(hptHatall->FindBin(15),hptHatall->FindBin(300));
    IptHatall[1] = hptHatall->Integral(hptHatall->FindBin(30),hptHatall->FindBin(300));
    IptHatall[2] = hptHatall->Integral(hptHatall->FindBin(60),hptHatall->FindBin(300));

    ptHatallRatio[0] = IptHatall[0]/(IptHatall[0]);
    ptHatallRatio[1] = IptHatall[1]/(IptHatall[0]);
    ptHatallRatio[2] = IptHatall[2]/(IptHatall[0]);

    cout << "for AllQCDPhotons, (ptHat>15)/(ptHat>15) = " << ptHatallRatio[0]<< endl;
    cout << "for AllQCDPhotons, (ptHat>30)/(ptHat>15) = " << ptHatallRatio[1]<< endl;
    cout << "for AllQCDPhotons, (ptHat>60)/(ptHat>15) = " << ptHatallRatio[2]<< endl;


// direct Photons

    double IptHatdirect[3];
    double ptHatdirectRatio[3];
    
    IptHatdirect[0] = hptHatdirect->Integral(hptHatdirect->FindBin(15),hptHatdirect->FindBin(300));
    IptHatdirect[1] = hptHatdirect->Integral(hptHatdirect->FindBin(30),hptHatdirect->FindBin(300));
    IptHatdirect[2] = hptHatdirect->Integral(hptHatdirect->FindBin(60),hptHatdirect->FindBin(300));

    ptHatdirectRatio[0] = IptHatdirect[0]/(IptHatdirect[0]);
    ptHatdirectRatio[1] = IptHatdirect[1]/(IptHatdirect[0]);
    ptHatdirectRatio[2] = IptHatdirect[2]/(IptHatdirect[0]);

    cout << "for directQCDPhotons, (ptHat>15)/(ptHat>15) = " << ptHatdirectRatio[0]<< endl;
    cout << "for directQCDPhotons, (ptHat>30)/(ptHat>15) = " << ptHatdirectRatio[1]<< endl;
    cout << "for directQCDPhotons, (ptHat>60)/(ptHat>15) = " << ptHatdirectRatio[2]<< endl;

// frag QCDPhotons

    double IptHatfrag[3];
    double ptHatfragRatio[3];
    
    IptHatfrag[0] = hptHatfrag->Integral(hptHatfrag->FindBin(15),hptHatfrag->FindBin(300));
    IptHatfrag[1] = hptHatfrag->Integral(hptHatfrag->FindBin(30),hptHatfrag->FindBin(300));
    IptHatfrag[2] = hptHatfrag->Integral(hptHatfrag->FindBin(60),hptHatfrag->FindBin(300));

    ptHatfragRatio[0] = IptHatfrag[0]/(IptHatfrag[0]);
    ptHatfragRatio[1] = IptHatfrag[1]/(IptHatfrag[0]);
    ptHatfragRatio[2] = IptHatfrag[2]/(IptHatfrag[0]);

    cout << "for fragQCDPhotons, (ptHat>15)/(ptHat>15) = " << ptHatfragRatio[0]<< endl;
    cout << "for fragQCDPhotons, (ptHat>30)/(ptHat>15) = " << ptHatfragRatio[1]<< endl;
    cout << "for fragQCDPhotons, (ptHat>60)/(ptHat>15) = " << ptHatfragRatio[2]<< endl;





    TLegend* l1 = new TLegend(0.4,0.6,0.87,0.80);
    // l1 -> AddEntry("hbkg", "background");
    // l1 -> AddEntry("hdirect", "direct photon");
    // l1 -> AddEntry("hfrag", "fragmentation photon");
    // l1 -> Draw();


}

