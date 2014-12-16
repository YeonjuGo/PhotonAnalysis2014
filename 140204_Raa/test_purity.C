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
#include "../gammaJetAnalysis/commonUtility.h"
#include "../gammaJetAnalysis/yj_fitResult.h"

using namespace std;
 
const TString MC_FILE = "/home/goyeonju/recent2013/jetAnalysis/files/yskimfiles/pA/yskim_pA_Pyquen_allQCDPhoton_hiForest2_53x_2013-18-14-1922.root ";
 
void test_purity(){

    TFile* ff = new TFile(MC_FILE);


}
