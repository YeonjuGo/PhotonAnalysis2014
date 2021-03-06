//Author : Yeonju Go

#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TH1D.h"
#include "TCut.h"
#include "TProfile.h"
#include "TGraphAsymmErrors.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TString.h"
#include "TLatex.h"
#include "stdio.h"
#include <iostream>

//! pt binning
double ptbins[] ={10,15,20,27,35,45,57,72,90,120,150,200,300,400,550,750,1000};
const int npt = sizeof(ptbins)/sizeof(double) - 1;

const double etabins[]={-3.0,-2.4,-1.8,-1.4,-1.0,-0.8,-0.6,-0.4,-0.2,
	0.0,0.2,0.4,0.6,0.8,1.0,1.4,1.8,2.4,3.0};
const int neta = sizeof(etabins)/sizeof(double) - 1;

const double phibins[] = {-3.141,-2.700,-2.100,-1.500,-0.900,-0.300,
	0.300,0.900,1.500,2.100,2.700,3.141};
const int nphi = sizeof(phibins)/sizeof(double) - 1;

//for 2013 HiWinter pPb
const int kAlgos = 12; 
const char *calgo[kAlgos] = {"ak3PF","ak4PF","ak5PF","ak3Calo","ak4Calo","ak5Calo",
                     "akPu3PF","akPu4PF","akPu5PF","akPu3Calo","akPu4Calo","akPu5Calo"
};
const int nRadius = 3;
const int nAlgoGroup = 4;// akPF, akCalo, akPuPF, akPuCalo

//for 2014 private PbPb
/*
const int kAlgos = 24; 
const char *calgo[kAlgos] = {"ak2PF","ak3PF","ak4PF","ak5PF","ak2Calo","ak3Calo","ak4Calo","ak5Calo",
	"akPu2PF","akPu3PF","akPu4PF","akPu5PF","akPu2Calo","akPu3Calo","akPu4Calo","akPu5Calo",
	"akVs2PF","akVs3PF","akVs4PF","akVs5PF","akVs2Calo","akVs3Calo","akVs4Calo","akVs5Calo"};
const int nRadius = 4;
const int nAlgoGroup = 6; // akPF, akCalo, akPuPF, akPuCalo, akVsPF, akVsCalo
*/

//string corrFileName[kAlgos]= {"AK1PF","AK2PF","AK3PF","AK4PF","AK5PF","AK6PF","AK7PF","AK1Calo","AK2Calo","AK3Calo","AK4Calo","AK5Calo","AK6Calo","AK7Calo",
//"AKPu1PF","AKPu2PF","AKPu3PF","AKPu4PF","AKPu5PF","AKPu6PF","AKPu7PF","AKPu1Calo","AKPu2Calo","AKPu3Calo","AKPu4Calo","AKPu5Calo","AKPu6Calo","AKPu7Calo",
//                  "AK1PF","AK2PF","AK3PF","AK4PF","AK5PF","AK6PF","AK7PF","AK1Calo","AK2Calo","AK3Calo","AK4Calo","AK5Calo","AK6Calo","AK7Calo",
//                                    "AKVs1PF","AKVs2PF","AKVs3PF","AKVs4PF","AKVs5PF","AKVs6PF","AKVs7PF","AKVs1Calo","AKVs2Calo","AKVs3Calo","AKVs4Calo","AKVs5Calo","AKVs6Calo","AKVs7Calo"
//                                    };
//



void draw_JEC(){
	TH1::SetDefaultSumw2();
	const int np = 10;
	TFile* fin = new TFile("JetResponse_histos_lowpt_ppSignal_pPbReco_leading_gammajet.root");
	//TFile* fin = new TFile("yj_JetResponse_histos_lowpt_ppSignal_pbpbReco_final_Track8_Jet28_MC.root");
	// raw/gen pt dep.
	TH1D* hresrrpt_genm[kAlgos][npt];
	double hresrrpt_genm_mean[kAlgos][npt];
	double hresrrpt_genm_sigma[kAlgos][npt];

	// reco/gen pt dep.
	TH1D* hrescrpt_genm[kAlgos][npt];
	double hrescrpt_genm_mean[kAlgos][npt];
	double hrescrpt_genm_sigma[kAlgos][npt];
	
    // reco/gen eta dep.
	TH1D* hrescrpt_genm_eta[kAlgos][npt][neta];
	double hrescrpt_genm_eta_mean[kAlgos][npt][neta];
	double hrescrpt_genm_eta_sigma[kAlgos][npt][neta];

	// reco/gen phi dep.
	TH1D* hrescrpt_genm_phi[kAlgos][npt][nphi];
	double hrescrpt_genm_phi_mean[kAlgos][npt][nphi];
	double hrescrpt_genm_phi_sigma[kAlgos][npt][nphi];

	// get reco/gen value for each pt bin.
	for(int nj=0; nj<kAlgos; nj++){ //for each algorithm,
		for(int ip=0; ip<np;ip++){ //for each pt bin.
			hresrrpt_genm[nj][ip] = (TH1D*) fin -> Get(Form("%sJetAnalyzer/hresrrpt_genm%d_%d", calgo[nj], nj, ip)); 
			hresrrpt_genm_mean[nj][ip] = hresrrpt_genm[nj][ip] -> GetMean(); 
			hresrrpt_genm_sigma[nj][ip] = hresrrpt_genm[nj][ip] -> GetMeanError();

			hrescrpt_genm[nj][ip] = (TH1D*) fin -> Get(Form("%sJetAnalyzer/hrescrpt_genm%d_%d", calgo[nj], nj, ip)); 
			hrescrpt_genm_mean[nj][ip] = hrescrpt_genm[nj][ip] -> GetMean(); 
			hrescrpt_genm_sigma[nj][ip] = hrescrpt_genm[nj][ip] -> GetMeanError();

			for(int ieta=0; ieta<neta; ieta++){	
				hrescrpt_genm_eta[nj][ip][ieta] = (TH1D*) fin -> Get(Form("%sJetAnalyzer/hrescrpt_genm_eta%d_%d_%d", calgo[nj], nj, ip, ieta)); 
				hrescrpt_genm_eta_mean[nj][ip][ieta] = hrescrpt_genm_eta[nj][ip][ieta] -> GetMean(); 
				hrescrpt_genm_eta_sigma[nj][ip][ieta] = hrescrpt_genm_eta[nj][ip][ieta] -> GetMeanError();
			}
			for(int iphi=0; iphi<nphi; iphi++){	
				hrescrpt_genm_phi[nj][ip][iphi] = (TH1D*) fin -> Get(Form("%sJetAnalyzer/hrescrpt_genm_phi%d_%d_%d", calgo[nj], nj, ip, iphi)); 
				hrescrpt_genm_phi_mean[nj][ip][iphi] = hrescrpt_genm_phi[nj][ip][iphi] -> GetMean(); 
				hrescrpt_genm_phi_sigma[nj][ip][iphi] = hrescrpt_genm_phi[nj][ip][iphi] -> GetMeanError();
			}
		}
	}
	//assemble values into one histogram	
	TH1D* all_hresrrpt_genm[kAlgos]; // raw/gen
	TH1D* all_hrescrpt_genm[kAlgos]; // reco/gen vs. gen pt
	TH1D* all_hrescrpt_genm_eta[kAlgos][npt]; // reco/gen vs. eta
	TH1D* all_hrescrpt_genm_phi[kAlgos][npt]; // reco/gen vs. phi

	TH1D* all_hresrrpt_genm_sigma[kAlgos]; // raw/gen
	TH1D* all_hrescrpt_genm_sigma[kAlgos]; // reco/gen vs. gen pt
	TH1D* all_hrescrpt_genm_eta_sigma[kAlgos][npt]; // reco/gen vs. eta
	TH1D* all_hrescrpt_genm_phi_sigma[kAlgos][npt]; // reco/gen vs. phi
	
    for(int nj=0; nj<kAlgos; nj++){
		all_hresrrpt_genm[nj] = new TH1D(Form("all_hresrrpt_genm%d", nj), Form("(Raw/Gen) jet pt vs. gen pt for %s", calgo[nj]), npt, ptbins);
		all_hresrrpt_genm[nj] -> SetAxisRange(10,120,"X"); 
		all_hresrrpt_genm[nj] -> SetAxisRange(0.8,1.2,"Y"); 
		all_hresrrpt_genm[nj] -> SetMarkerStyle(20); 
		all_hresrrpt_genm_sigma[nj] = new TH1D(Form("all_hresrrpt_genm_sigma%d", nj), Form("Sigma of (Raw/Gen) jet pt vs. gen pt for %s", calgo[nj]), npt, ptbins);
		all_hresrrpt_genm_sigma[nj] -> SetAxisRange(10,120,"X"); 
		all_hresrrpt_genm_sigma[nj] -> SetAxisRange(-0.01,0.01,"Y"); 
		all_hresrrpt_genm_sigma[nj] -> SetMarkerStyle(20); 

		all_hrescrpt_genm[nj] = new TH1D(Form("all_hrescrpt_genm%d", nj), Form("(Reco/Gen) jet pt vs. gen pt for %s", calgo[nj]), npt, ptbins);
		all_hrescrpt_genm[nj] -> SetAxisRange(10,120,"X"); 
		all_hrescrpt_genm[nj] -> SetAxisRange(0.5,1.5,"Y"); 
		all_hrescrpt_genm[nj] -> SetMarkerStyle(20); 
		all_hrescrpt_genm_sigma[nj] = new TH1D(Form("all_hrescrpt_genm_sigma%d", nj), Form("Sigma of (Reco/Gen) jet pt vs. gen pt for %s", calgo[nj]), npt, ptbins);
		all_hrescrpt_genm_sigma[nj] -> SetAxisRange(10,120,"X"); 
		all_hrescrpt_genm_sigma[nj] -> SetAxisRange(-0.01,0.01,"Y"); 
		all_hrescrpt_genm_sigma[nj] -> SetMarkerStyle(20); 
		
        for(int ip=0; ip<np;ip++){ //for each pt bin.
			all_hrescrpt_genm_eta[nj][ip] = new TH1D(Form("all_hrescrpt_genm_eta%d_%d", nj, ip), Form("(Reco/Gen) jet pt vs. eta for %s", calgo[nj]), neta, etabins);
			//all_hrescrpt_genm_eta[nj][ip] -> SetAxisRange(10,120,"X"); 
			all_hrescrpt_genm_eta[nj][ip] -> SetAxisRange(0.5,1.5,"Y"); 
			all_hrescrpt_genm_eta[nj][ip] -> SetMarkerStyle(20); 
			all_hrescrpt_genm_eta_sigma[nj][ip] = new TH1D(Form("all_hrescrpt_genm_eta_sigma%d_%d", nj, ip), Form("Sigma of (Reco/Gen) jet pt vs. eta for %s", calgo[nj]), neta, etabins);
			//all_hrescrpt_genm_eta_sigma[nj][ip] -> SetAxisRange(10,120,"X"); 
			all_hrescrpt_genm_eta_sigma[nj][ip] -> SetAxisRange(-0.01,0.03,"Y"); 
			all_hrescrpt_genm_eta_sigma[nj][ip] -> SetMarkerStyle(20); 

			all_hrescrpt_genm_phi[nj][ip] = new TH1D(Form("all_hrescrpt_genm_phi%d_%d", nj, ip), Form("(Reco/Gen) jet pt vs. phi for %s", calgo[nj]), nphi, phibins);
			//all_hrescrpt_genm[nj][ip] -> SetAxisRange(10,120,"X"); 
			all_hrescrpt_genm_phi[nj][ip] -> SetAxisRange(0.5,1.5,"Y"); 
			all_hrescrpt_genm_phi[nj][ip] -> SetMarkerStyle(20); 
			all_hrescrpt_genm_phi_sigma[nj][ip] = new TH1D(Form("all_hrescrpt_genm_phi_sigma%d_%d", nj, ip), Form("Sigma of (Reco/Gen) jet pt vs. phi for %s", calgo[nj]), nphi, phibins);
			//all_hrescrpt_genm_phi_sigma[nj][ip] -> SetAxisRange(10,120,"X"); 
			all_hrescrpt_genm_phi_sigma[nj][ip] -> SetAxisRange(-0.01,0.03,"Y"); 
			all_hrescrpt_genm_phi_sigma[nj][ip] -> SetMarkerStyle(20); 
		}

		for(int ip=0; ip<np;ip++){
			all_hresrrpt_genm[nj] -> SetBinContent(ip+1, hresrrpt_genm_mean[nj][ip]);	
			all_hrescrpt_genm[nj] -> SetBinContent(ip+1, hrescrpt_genm_mean[nj][ip]);	
			all_hresrrpt_genm_sigma[nj] -> SetBinContent(ip+1, hresrrpt_genm_sigma[nj][ip]);	
			all_hrescrpt_genm_sigma[nj] -> SetBinContent(ip+1, hrescrpt_genm_sigma[nj][ip]);	
			//cout << "are two same? : " << hresrrpt_genm_mean[nj][ip] << ", " << all_hresrrpt_genm[nj] -> GetBinContent(ip) << endl;

			for(int ieta=0; ieta<neta; ieta++){	
				all_hrescrpt_genm_eta[nj][ip] -> SetBinContent(ieta+1, hrescrpt_genm_eta_mean[nj][ip][ieta]);	
				all_hrescrpt_genm_eta_sigma[nj][ip] -> SetBinContent(ieta+1, hrescrpt_genm_eta_sigma[nj][ip][ieta]);	
			}	

			for(int iphi=0; iphi<nphi; iphi++){
				all_hrescrpt_genm_phi[nj][ip] -> SetBinContent(iphi+1, hrescrpt_genm_phi_mean[nj][ip][iphi]);	
				all_hrescrpt_genm_phi_sigma[nj][ip] -> SetBinContent(iphi+1, hrescrpt_genm_phi_sigma[nj][ip][iphi]);	
			}
		}
	}
 //========================
 // draw on canvas 
 //========================
 
 // Raw/Gen vs. gen pt
    TCanvas* cRaw[nAlgoGroup];
    for(int iG=0; iG<nAlgoGroup; iG++){ //for each algorithm,
        cRaw[iG] = new TCanvas(Form("cRaw%d",iG), Form("cRaw%d",iG), nRadius*300,600);
        cRaw[iG] -> Divide(nRadius,2);//# of different radius is 3
    }
    
    for(int iG=0 ; iG<nAlgoGroup; iG++){ 
        for(int iR=0; iR<nRadius; iR++){
        cRaw[iG] -> cd(iR+1);
        all_hresrrpt_genm[iG+iR] -> Draw("p");
        cRaw[iG] -> cd(iR+nRadius+1);
        all_hresrrpt_genm_sigma[iG+iR] -> Draw("p");
        }
    }

 // Reco/Gen vs. gen pt
    TCanvas* cReco[nAlgoGroup];
    for(int iG=0; iG<nAlgoGroup; iG++){ //for each algorithm,
        cReco[iG] = new TCanvas(Form("cReco%d",iG), Form("cReco%d",iG), nRadius*300,600);
        cReco[iG] -> Divide(nRadius,2);//# of different radius is 3
    }
    
    for(int iG=0 ; iG<nAlgoGroup; iG++){ 
        for(int iR=0; iR<nRadius; iR++){
        cReco[iG] -> cd(iR+1);
        all_hrescrpt_genm[iG+iR+6] -> Draw("p");
        cReco[iG] -> cd(iR+nRadius+1);
        all_hrescrpt_genm_sigma[iG+iR+6] -> Draw("p");
        }
    }

}
