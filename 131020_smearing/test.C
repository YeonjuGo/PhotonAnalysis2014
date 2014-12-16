#include "../HiForestAnalysis/hiForest.h"
#include "../gammaJetAnalysis/CutAndBinCollection2012.h"
#include <TStyle.h>
#include <TH1D.h>
#include <TTree.h>
#include <TBranch.h>
#include <TFile.h>
#include <iostream>
#include <TCanvas.h>
#include <TF1.h>
#include <TGraphAsymmErrors.h>
#include <TLegend.h>
#include <TCut.h>
#include <TRandom3.h>

void test(){

  TH1D* h = new TH1D("h1","",100,0,4);
  TRandom3 rand(111);
  for (int i = 0 ; i<=10000;i++) {
    h->Fill( rand.Gaus(1,0.5));
  }
  TCanvas* c1= new TCanvas("c1","",500,500);
  h->Draw();

  
}

/*
            hRecoPt_ratio[icoll] -> SetYTitle("p_{T}^{PbPb}/p_{T}^{pp}");
        //    hRecoPt_ratio[icoll] -> SetTitleOffset(0.52, "Y");
        //    hRecoPt[icoll] -> SetTitleOffset(0.52, "Y");
        } else hRecoPt_ratio[icoll] -> Draw("same");
    }
    jumSun(0,1,200,1,2);
//
// reco/gen ratio
//
    TCanvas* crg = new TCanvas("crg", "", 1300, 300);
    makeMultiPanelCanvas(crg, 5, 1);
    TH1D* hrg[5];
    for(int icoll=0; icoll<5; icoll++){
        hrg[icoll]= (TH1D*) hRecoPt[icoll] -> Clone(Form("hrg%d",icoll));
       // hrg[icoll]= new TH1D(Form("hrg%d", icoll),"; p_{T} (GeV) ; p_{T}^{Reco}/p_{T}^{Gen}", 20, 0, 200);
    }
     
    for(int icoll=0; icoll<5; icoll++){
        crg -> cd(icoll+1);
        hrg[icoll] -> Divide(hGenPt[icoll]);
     //   hrg[icoll] -> Scale(1./hrg[icoll]->Integral());
        hrg[icoll] -> SetYTitle("p_{T}^{Reco}/p_{T}^{Gen}");
        hrg[icoll] -> SetAxisRange(0.5,1.5,"Y"); 
        hrg[icoll] -> Draw(); 
        jumSun(0,1,200,1,2);
    }

    double sigma[5]; 
    double cc[5]; 
    double ss[5]; 
    double nn[5]; 

    cc[0] =0.056762;
    ss[0] =0.808114;
    nn[0] =0.000244992;
    if(fixOpt==0) {
        cc[1] =0.056762;
        ss[1] =0.808114;
        nn[1] =9.6876;
        cc[2] =0.056762;
        ss[2] =0.808114;
        nn[2] =8.21968;
        cc[3] =0.056762;
        ss[3] =0.808114;
        nn[3] =7.02911;
        cc[4] =0.056762;
        ss[4] =0.808114;
        nn[4] =6.10214;
    } else if(fixOpt==1){
        cc[1] =0.0560882;
        ss[1] =1.47838;
        nn[1] =0.115188;
        cc[2] =0.0256674;
        ss[2] =1.40659;
        nn[2] =-0.0341018;
        cc[3] =0.00644361;
        ss[3] = 1.31446;
        nn[3] = -0.0721935;
        cc[4] =0.0170442;
        ss[4] = 1.22837;
        nn[4] = 0.0511498;
    }

    TCanvas* cSmear = new TCanvas("cSmear", "", 350, 900);
  //  makeMultiPanelCanvas(cSmear, 1, 3);
    cSmear -> Divide(1,3); 
    cSmear -> SetLeftMargin(0.5);

    TH1D* hSmear[5]; 
    TH1D* hRatio[5]; 
    TH1D* hRatioGen[5]; 
    for(int icoll=0; icoll<5; icoll++){    
        hSmear[icoll] = new TH1D(Form("hSmear%d",icoll), "; p_{T}^{Smeared} (GeV) ; Entries", 20, 0, 200);
    }

    TRandom3 rand(111);
    
    for(int icoll=0; icoll<5; icoll++){    
        cSmear -> cd(1);
        for(int i=0; i<10000; i++){
	  double pt = hGenPt[icoll] -> GetRandom();
	  sigma[icoll] = sqrt(cc[icoll]*cc[icoll] + ss[icoll]*ss[icoll]/pt + nn[icoll]*nn[icoll]/(pt*pt));
	  double factor = rand.Gaus(1,sigma[icoll]);
	  double newPt = pt*factor;
	  hSmear[icoll] -> Fill(newPt);
        }

        handsomeTH1(hSmear[icoll], icoll+1, 0.5);
        hSmear[icoll] -> Scale(1./10000);
        if(icoll==0) hSmear[icoll] -> Draw();
        else hSmear[icoll] -> Draw("same");
        
        cSmear -> cd(2);
        hRatioGen[icoll] = (TH1D*) hSmear[icoll] -> Clone(Form("hRatioGen%d",icoll));
        hRatioGen[icoll] -> Divide(hRecoPt[icoll]);
        hRatioGen[icoll] -> SetYTitle("p_{T}^{smeared}/p_{T}^{Gen}");
	//        hRatioGen[icoll] -> Scale(1./hRatioGen[icoll]->Integral());
      //  hRatioGen[icoll] -> SetTitleOffset(0.52, "Y");
        handsomeTH1(hRatioGen[icoll], icoll+1, 0.5);
        if(icoll==0) hRatioGen[icoll] -> Draw();
        else hRatioGen[icoll] -> Draw("same");
        jumSun(0,1,200,1,2);
        
        cSmear -> cd(3);
        hRatio[icoll] = (TH1D*) hSmear[icoll] -> Clone(Form("hRatio%d",icoll));
        hRatio[icoll] -> Divide(hRecoPt[icoll]);
        hRatio[icoll] -> SetYTitle("p_{T}^{smeared}/p_{T}^{Reco}");
      //  hRatio[icoll] -> SetTitleOffset(0.52, "Y");
        handsomeTH1(hRatio[icoll], icoll+1, 0.5);
        if(icoll==0) hRatio[icoll] -> Draw();
        else hRatio[icoll] -> Draw("same");
        jumSun(0,1,200,1,2);
        
    }
    cSmear -> cd(1);
    l1 -> Draw();
    l2 -> Draw();
//
// reco/smear ratio
//
    TCanvas* crs = new TCanvas("crs", "", 1300, 300);
    makeMultiPanelCanvas(crs, 5, 1);
    TH1D* hrs[5];//histogram reco/smear
    for(int icoll=0; icoll<5; icoll++){
        hrs[icoll]= (TH1D*) hRecoPt[icoll] -> Clone(Form("hrs%d",icoll));
    }
     
    for(int icoll=0; icoll<5; icoll++){
        crs -> cd(icoll+1);
        hrs[icoll] -> Divide(hSmear[icoll]);
        hrs[icoll] -> SetYTitle("p_{T}^{Reco}/p_{T}^{Smear}");
     //   hrs[icoll] -> SetTitleOffset(0.52, "Y");
        hrs[icoll] -> SetAxisRange(0.5,2.5,"Y"); 
        hrs[icoll] -> Draw(); 
        jumSun(0,1,200,1,2);
        
    }

    cSmear -> SaveAs(Form("smeared_fixOpt%d.pdf",fixOpt));
}

*/
