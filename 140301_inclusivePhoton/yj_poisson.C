#include <TMath.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <iostream>

void yj_poisson(){
    Double_t p1 = TMath::Poisson(0.0, 3.7);
    Double_t p2 = TMath::Poisson(1.0, 3.7);
    Double_t p3 = TMath::Poisson(2.0, 3.7);
    Double_t p4 = TMath::Poisson(3.0, 3.7);
    Double_t p5 = TMath::Poisson(4.0, 3.7);
    Double_t p6 = TMath::Poisson(5.0, 3.7);
    Double_t p7 = TMath::Poisson(6.0, 3.7);
    cout << "P(0) = " << p1 << endl;
    cout << "P(1) = " << p2 << endl;
    cout << "P(2) = " << p3 << endl;
    
    cout << "P(0)+P(1)+P(2) = " << p1+p2+p3 << endl; 
    //cout << p1+p2+p3 << endl; 
    //double tt = 1.1;
    TCanvas* c1 = new TCanvas("c1", "", 400, 400);
    TH1D* h1 = new TH1D("h1", "Poisson Distribution", 7, 0, 7);
    h1 -> Fill(0.0, p1);
    h1 -> Fill(1.0, p2);
    h1 -> Fill(2.0, p3);
    h1 -> Fill(3.0, p4);
    h1 -> Fill(4.0, p5);
    h1 -> Fill(5.0, p6);
    h1 -> Fill(6.0, p7);
    h1 -> Draw();
}

