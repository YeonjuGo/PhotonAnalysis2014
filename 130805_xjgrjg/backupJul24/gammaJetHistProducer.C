///////////////////////////////////////////////////////////////////                                
// gammaTrack.C                                                  //                                                 
// Creator : Yongsun Kim (MIT), jazzitup@mit.edu                 //                                                 
// Function : Make the correlation function between Photon and   //
//            tracks.  Signal and Background are calculated      //
//            separately, and then background subtraction is     //
//            done.  Output histogrmas are saved in output file  //
///////////////////////////////////////////////////////////////////         
//  int icout = 0;
//  cout << " line " << icout << endl; icout++;

#include <TStyle.h>
#include <TH1F.h>
#include <TH2D.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TGraphAsymmErrors.h>
#include <iostream>
#include <TLine.h>
#include <TMath.h>
#include <math.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TROOT.h>
#include <TRandom.h>
#include <TCut.h>
#include <TClonesArray.h>
#include "commonUtility.h"
#include <TRandom3.h>
#include "CutAndBinCollection2012.h"
#include "corrFunctionJetTrk.h"

GjSpectra* nullGj;

void gammaTrkSingle(     GjSpectra* gjSpec_=nullGj,
			 multiTreeUtil* tObj[3]=0,
			 corrFunctionTrk* corr_=0,
			 float purity=0,
			 sampleType collision_=kHIDATA,
			 TString var_ = "",
			 TCut cut_ ="",
			 TString theWeight="",
			 TCut phoCandCut_="",
			 TCut phoDecayCut_="",
			 TH1D* hTemplate_ =0,
			 TString outName="");

fitResult getPurity(TString fname="", sampleType collision=kHIDATA, TCut candEvtCut = "", TCut sbEvtCut="", TString ccanvasName="",float photonPtThr=60, float photonPtThrUp=1000000);


void gammaJetHistProducer(sampleType collision = kHIDATA, float photonPtThr=60, float photonPtThrUp=1000000, float jetPtThr=30, int icent =1,  int genLevel=0, int qnch = 0) {
  TH1::SetDefaultSumw2();
  
  TString stringSampleType = getSampleName(collision); "";
  
  TDatime* date = new TDatime();
  TString outName=  Form("ffFiles/photonTrackCorr_%s_output_photonPtThr%d_to_%d_jetPtThr%d_%d_genLevel%d_qnch%d.root",stringSampleType.Data(),(int)photonPtThr, (int)photonPtThrUp, (int)jetPtThr,  date->GetDate(), (int)genLevel, (int)qnch);
  delete date;
    

  
  int lowerCent(0),  upperCent(0); 
  TCut centCut  = "";
  if ( (collision ==kHIDATA) || (collision==kHIMC) )   {
    lowerCent = centBin1[icent-1];
    upperCent = centBin1[icent]-1;
    if ( icent > 9999) {
      lowerCent = ((icent/100)%100)/2.5;
      upperCent =  (icent%100)/2.5 -1;
    }
    centCut = Form("cBin >= %d && cBin<= %d",lowerCent,upperCent);
  }
  else if (  (collision ==kPPDATA) || (collision==kPPMC)  ){  // if it's pp 
    centCut = "(1==1)";
    icent = 7;
  }
  else { // pPb
    cout << "pA analysis is not ready" << endl;
    return ;
  }
  
  cout <<" centrality : " << centCut.GetTitle() << endl;
      
  ///////// Photon cut //////////////////////////////////////////////////////////////////////////////
  
  cout <<" photon pt >" << photonPtThr << " GeV" << endl;
  TCut ptPhoCut  = Form("photonEt>%.1f && photonEt<%.1f", (float)photonPtThr, (float)photonPtThrUp  );
  TCut caloIso;
  
  if ( (collision==kPPMC) || (collision==kPPDATA) ) 
    caloIso = "(ecalIso < 4.2  &&  hcalIso < 2.2  &&  trackIso < 2) && hovere<0.1";
  else if ( (collision==kHIMC) || (collision==kHIDATA) )
    caloIso = "(sumIso<1) && hovere<0.1";
  else {
    cout << "pA analysis is not ready"<<endl;
    return ;
  }

  TCut sbIso   = "(sumIso>10) && (sumIso<20) && hovere<0.1";
  TCut basicPhoCut = centCut && ptPhoCut && caloIso ;
  TCut sbPhoCut    = centCut && ptPhoCut && sbIso   ;
  TCut evtSeltCut = basicPhoCut;
  TCut sbSeltCut  = sbPhoCut;

  TCut phoCandCut   = "sigmaIetaIeta<0.010";
  TCut phoDecayCut  = "(sigmaIetaIeta>0.011) && (sigmaIetaIeta<0.017)";
  if  ( ( collision == kHIMC ) || (collision == kPPMC) ) 
    phoCandCut = phoCandCut && "genIso<5 && abs(genMomId)<=22";
  
  
  TString fname;
  if ( collision == kHIMC)              fname = fnameHIMC_AllQcdPho30; 
  else if ( collision == kHIDATA)       fname = fnameDATAPbPbAk3;
  else if ( collision == kPPMC)         fname = fnameMCppAk3;
  else if ( collision == kPPDATA)         fname = fnameDATAppAk3;
  
  multiTreeUtil* tgj = new multiTreeUtil();
  multiTreeUtil* tgjMC = new multiTreeUtil();
  tgj->addFile(fname,  "tgj",  evtSeltCut,  1);
  tgj->AddFriend("yJet");

  // get purity with the current jet cut ! 
  float purity(0);
  
  TString canvasName = Form("gifs/purity_%s_output_icent%d_photonPtThr%d-%d_jetPtThr%d", stringSampleType.Data(),  (int)icent, (int)photonPtThr, (int)photonPtThrUp, (int)jetPtThr);
  
  if ( (collision==kHIDATA)||(collision==kPPDATA)||(collision==kPADATA) )  {
    fitResult fitr = getPurity(fname, collision, evtSeltCut, sbSeltCut, canvasName, photonPtThr, photonPtThrUp);
    purity = fitr.purity010;
  }
  else  {
    purity = 1;  
    cout << " MC purity = 1" << endl;
  }


  GjSpectra* gSpec = new GjSpectra();
  gSpec->init(Form("pho%.0f_%.0f", (float)photonPtThr, (float)photonPtThrUp));
  tgj->Draw2(gSpec->hPtPhoCand,  "photonEt", phoCandCut, "")  ;
  tgj->Draw2(gSpec->hPtPhoDecay, "photonEt", phoDecayCut, "") ;
  
  
  // Objects
  multiTreeUtil* tObj[3];
  tObj[kTrkRaw] = new multiTreeUtil();
  tObj[kTrkBkg] = new multiTreeUtil();
  
  if ( genLevel == 0 ) {
    tObj[kTrkRaw]->addFile(fname,  "yJet",  evtSeltCut,  1);
    tObj[kTrkBkg]->addFile(fname,  "mJet",  evtSeltCut,  1);
  }
  else if ( genLevel==1) {
    tObj[kTrkRaw]->addFile(fname,  "genJet",   evtSeltCut,  1);
    tObj[kTrkBkg]->addFile(fname,  "mGenjet",  evtSeltCut,  1);
  }
  tObj[kTrkRaw]->AddFriend("tgj");
  tObj[kTrkBkg]->AddFriend("tgj");
  TCut jetCut     =  Form("abs(eta)<%f && pt>%f", (float)cutjetEta, (float)jetPtThr );
  TCut jetCutDphi =  jetCut && (TCut)(Form("abs(dphi)>%f",(float)awayRange));
  TString jetWeight = "";
  if (genLevel==1)        jetWeight = "";
  
  TH1D* hJetDphi = new TH1D(Form("jetDphi_icent%d",icent),";#Delta#phi_{Jet,#gamma} ;dN/d#Delta#phi",20,0,3.141592);
  corrFunctionTrk* cJetDphi = new corrFunctionTrk();
  TString varJetDphi         = Form("dphi");

  gammaTrkSingle( gSpec,  tObj, cJetDphi,  purity, 
		  collision, varJetDphi, jetCut, jetWeight,
		  phoCandCut, phoDecayCut,  hJetDphi, outName);
  
  TH1D* hJetPt = new TH1D(Form("jetPt_icent%d",icent),";Jet p_{T} (GeV) ;dN/dp_{T} (GeV^{-1})",10,0,200);
  corrFunctionTrk* cJetPt = new corrFunctionTrk();
  TString varJetPt         = Form("pt");

  gammaTrkSingle( gSpec,  tObj, cJetPt,  purity, 
		  collision, varJetPt, jetCutDphi, jetWeight,
		  phoCandCut, phoDecayCut,  hJetPt, outName);
  
  TH1D* hJetXjg = new TH1D(Form("jetXjg_icent%d",icent),";p_{T}^{Jet}/p_{T}^{#gamma}  ; ",160,0,2);
  corrFunctionTrk* cJetXjg = new corrFunctionTrk();
  TString varJetXjg         = Form("pt/photonEt");

  gammaTrkSingle( gSpec,  tObj, cJetXjg,  purity, 
		  collision, varJetXjg, jetCutDphi, jetWeight,
		  phoCandCut, phoDecayCut,  hJetXjg, outName);
  

  
  /*
    TH1D* hFFJet = (TH1D*)hFFPho->Clone(Form("ffJet_type1_icent%d",icent));
    corrFunctionTrk* cFFJet = new corrFunctionTrk();
    TString trkVarFFJet         = Form("-log(pt/injPt)");
    gammaTrkSingle( gjSpec,  tObj, cFFJet,  purity, 
    collision, trkVarFFJet, trkCutFF,  trkWeight,
    phoCandCut, phoDecayCut,  
    hFFJet, outName);
  

  const int nTrkPtBins = 12;
  double trkPtBins[nTrkPtBins+1] = {1,2,3,4,5,7,9,12,15,20,25,50,100};
  
  TH1D* hFF_type3 = new TH1D(Form("ff_type3_icent%d",icent),";;",nTrkPtBins,trkPtBins);
  corrFunctionTrk* cFF_type3 = new corrFunctionTrk();
  TString trkVarFF_type3    = Form("pt");
  gammaTrkSingle( gjSpec,  tObj, cFF_type3,  purity,
                  collision, trkVarFF_type3, trkCutFF,  trkWeight,
                  phoCandCut, phoDecayCut,  hFF_type3, outName);
  
  corrFunctionTrk* cFF_type3_sube0 = new corrFunctionTrk();
  TH1D* hFF_type3_sube0 = new TH1D(Form("ff_type3_sube0_icent%d",icent),";;",nTrkPtBins,trkPtBins);
  corrFunctionTrk* cFF_type3_sube1 = new corrFunctionTrk();
  TH1D* hFF_type3_sube1 = new TH1D(Form("ff_type3_sube1_icent%d",icent),";;",nTrkPtBins,trkPtBins);
  if ( genLevel ==1 ) { 
    gammaTrkSingle( gjSpec,  tObj, cFF_type3_sube0,  purity,
		    collision, trkVarFF_type3, trkCutFF && "sube==0",  trkWeight,
		    phoCandCut, phoDecayCut,  hFF_type3_sube0, outName);
    gammaTrkSingle( gjSpec,  tObj, cFF_type3_sube1,  purity,
		    collision, trkVarFF_type3, trkCutFF && "sube!=0",  trkWeight,
		    phoCandCut, phoDecayCut,  hFF_type3_sube1, outName);
  }
  
  return;

  
  // weights!    
  
  TString weightRes         = "trkWeight * pt";//*-cos(dphi)";                                                                               
  
  TH1D* hMedRes03 = new TH1D(Form("medResDr03_icent%d",icent),"; #dphi; ",10,PI/2.,PI);
  corrFunctionTrk* cFFRes03 = new corrFunctionTrk();
  TCut trkCutRes03            = Form("abs(eta)<%.2f && injDr>0.3",(float)cuttrkEtaForAna);
  TString trkVarRes         = "dphi";

 
  gammaTrkSingle( gjSpec,  tObj, cFFRes03,  purity, 
		  collision, trkVarRes, trkCutRes03, weightRes, 
		  phoCandCut,   phoDecayCut,  hMedRes03, outName);


  */  
  /*
    TH1D* hMedResInc = new TH1D(Form("medResDrInc_icent%d",icent),"; #dphi; ",10,PI/2.,PI);
    corrFunctionTrk* cFFResInc = new corrFunctionTrk();
    TCut trkCutResInc            = Form("abs(eta)<%.2f",(float)cuttrkEtaForAna);
    gammaTrkSingle( gjSpec,  tObj, cFFResInc,  purity, 
    collision, trkVarRes, trkCutResInc, weightRes, 
    phoCandCut,   phoDecayCut,  hMedResInc, outName);
  */
  
}


void gammaTrkSingle(     GjSpectra* gSpec,  multiTreeUtil* tObj[3],   corrFunctionTrk* corr, 
			 float purity,       sampleType collision, 	     TString var,     
			 TCut cut, 		TString theWeight,	 TCut phoCandCut,   TCut phoDecayCut,
			 TH1D* hTemplate,  TString outfName)
{
  TH1::SetDefaultSumw2();
  corr->init(gSpec, collision, purity, hTemplate);

  tObj[kTrkRaw]->Draw2(corr->Func[kPhoCand][kTrkRaw],  var,  phoCandCut  && cut, theWeight);
  if ( tObj[kTrkBkg]!=0)  
    tObj[kTrkBkg]->Draw2(corr->Func[kPhoCand][kTrkBkg],  var,  phoCandCut  && cut, theWeight);
  
  
  if ( (collision==kHIDATA) || (collision==kPPDATA) ) {
    tObj[kTrkRaw]->Draw2(corr->Func[kPhoDecay][kTrkRaw], var, phoDecayCut && cut,  theWeight);
    if (tObj[kTrkBkg]!=0)  
      tObj[kTrkBkg]->Draw2(corr->Func[kPhoDecay][kTrkBkg], var, phoDecayCut && cut,  theWeight);
  }
  TH1ScaleByWidth( corr->Func[kPhoCand][kTrkRaw]); 
  TH1ScaleByWidth( corr->Func[kPhoCand][kTrkBkg]);
  TH1ScaleByWidth( corr->Func[kPhoDecay][kTrkRaw]);
  TH1ScaleByWidth( corr->Func[kPhoDecay][kTrkBkg]);
  
  corr->calCorr();
  TFile outf = TFile(outfName.Data(),"update");
  corr->Func[kPhoCand][kTrkRaw]->Write();
  corr->Func[kPhoCand][kTrkBkg]->Write();
  corr->Func[kPhoCand][kTrkSig]->Write();
  corr->Func[kPhoDecay][kTrkRaw]->Write();
  corr->Func[kPhoDecay][kTrkBkg]->Write();
  corr->Func[kPhoDecay][kTrkSig]->Write();
  corr->Func[kPhoSig][kTrkRaw]->Write();
  corr->Func[kPhoSig][kTrkBkg]->Write();
  corr->Func[kPhoSig][kTrkSig]->Write();
  
  outf.Close();  
}



fitResult getPurity(TString fname, sampleType collision, TCut evtSeltCut, TCut sbEvtCut, TString canvasName, float photonPtThr, float photonPtThrUp) {
  double purity(0);
  
  multiTreeUtil* tgj = new multiTreeUtil();
  multiTreeUtil* tgjMC = new multiTreeUtil();
  cout <<" 1 " << endl;
  tgj->addFile(fname,  "tgj",  "",  1);
  cout <<" 2 " << endl;
  tgj->AddFriend("yJet");
  if   (collision==kPPDATA)
    tgjMC->addFile(fnameMCppAk3, "tgj", "", 1);
  else if (collision==kHIDATA)  {
    if       (photonPtThr <65 )
      tgjMC->addFile(fnameHIMC_AllQcdPho30, "tgj", "", 1);
    else if  (photonPtThr <85 )
      tgjMC->addFile(fnameHIMC_AllQcdPho50, "tgj", "", 1);
    else 
      tgjMC->addFile(fnameHIMC_AllQcdPho80, "tgj", "", 1);
  }
  else if (collision==kPADATA)     {
    cout << "Error!! pA collision analysis is not ready yet" << endl;
    fitResult fitr0;
    return fitr0;
  }
  else { 
    cout << " Error: getPurity.  check the type of the collision!  " << endl;
    fitResult fitr0;
    return fitr0;
  }
  
  TH1D* hCand = new TH1D("cand","",25,0,0.025);
  TH1D* hBkg = (TH1D*)hCand->Clone("bkg");  TH1D* hSig = (TH1D*)hCand->Clone("sig");
  
  //  tgj->Draw2(   hCand, "sigmaIetaIeta", evtSeltCut, "");
  // tgj->Draw2(   hBkg, "sigmaIetaIeta", sbEvtCut, "");
  tgj->Draw2(   hCand, "sigmaIetaIeta", evtSeltCut , "");
  tgj->Draw2(   hBkg, "sigmaIetaIeta", sbEvtCut , "");
  tgjMC->Draw2( hSig, "sigmaIetaIeta", evtSeltCut && "genIso<5 && abs(genMomId)<=22", "");
  handsomeTH1(hCand,1);
  handsomeTH1(hSig,2);
  handsomeTH1(hBkg,4);

  TCanvas* cPurity = new TCanvas("cpurity","",500,500);
  fitResult fitr = doFit ( hSig, hBkg, hCand, 0.005, 0.025);
  drawText(Form("Purity : %.2f", (float)fitr.purity010), 0.5680963,0.429118);
  drawText(Form("p_{T}^{#gamma}: %d-%d GeV", (int)photonPtThr, (int)photonPtThrUp), 0.568,0.529118);
  cleverCanvasSaving(cPurity,canvasName);
  
  TCanvas* c1 = new TCanvas("c1","",100,100);
  
  
  delete tgj;
  delete tgjMC;
  delete hSig;
  delete hBkg;
  delete hCand;
  
  return fitr;
  
  
}

