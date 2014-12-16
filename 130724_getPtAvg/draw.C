#include <TFile.h>
#include <TDirectory.h>
#include <TTree.h>
#include <TH2D.h>
#include <TH1D.h>
#include <TCanvas.h>

void draw()
{
    TFile* f1 = new TFile("HydjetDrum03_HiForest_v05_merged_test02.root");
    TDirectory* d_gamma = (TDirectory*) f1 -> Get("multiPhotonAnalyzer");
    TDirectory* d_jet = (TDirectory*) f1 -> Get("akPu3PFJetAnalyzer");
    
    d_gamma -> cd();
    TTree* t_gamma = (TTree*) d_gamma -> Get("photon");
    
    d_jet -> cd();
    TTree* t_jet = (TTree*) d_jet -> Get("t");
    t_gamma -> AddFriend(t_jet);

    TCanvas* c[9];
    for(Int_t i = 0 ; i< 9 ; i++)
    {
        c[i] = new TCanvas(Form("c%d", i), Form("c%d", i), 20, 0, 600, 600);
    }

    c[0] -> cd();
    t_gamma -> Draw("pt");
    c[1] -> cd();
    t_gamma -> Draw("eta");
    c[2] -> cd();
    t_gamma -> Draw("phi");
    c[3] -> cd();
    t_jet -> Draw("jtpt");
    c[4] -> cd();
    t_jet -> Draw("jteta");
    c[5] -> cd();
    t_jet -> Draw("jtphi");
    c[6] -> cd();
    t_gamma -> Draw("photon.eta:t.jteta");
    c[7] -> cd();
    t_gamma -> Draw("phi-jtphi");
    c[8] -> cd();
    t_gamma -> Draw("acos(cos(phi-jtphi))", "pt>30");

}

