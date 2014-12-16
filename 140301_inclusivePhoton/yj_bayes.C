#include <TMath.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <iostream>

void yj_bayes(){

    double p[10];
    p[0]=0.99;
    for(int i=0; i<10; i++){
        p[i+1]=(10.0-i-1.0)/(10.0-i-p[i])*p[i];
        cout << "p(" << i+1<< ") = " << p[i+1] << endl;
    }
}

