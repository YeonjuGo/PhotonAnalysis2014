///////////////////////////////////////////////////////////////////                                
// forest2yskim.C                                                //                                                 
// Creator : Yongsun Kim (MIT), jazzitup@mit.edu                 //                                                 
// Function : Transform hiForest files into yskim file           //
// yskims for MinBias1, Minbias2 and photon jet skims            //
///////////////////////////////////////////////////////////////////         

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TFile.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <TMath.h>
#include "../HiForest_V2_thesis/hiForest.h"
#include "CutAndBinCollection2012.h"
#include <time.h>
#include <TRandom3.h>

using namespace std;

static const int MAXTRK  = 10000;   // This is very enough.
static const int MAXMTRK = 30000;   // Again this is very enough for 10 mixing  
static const int MAXMJET = 2000;
static const long MAXTREESIZE = 10000000000;


class Isolation{
public:
  float cc1,cc2,cc3,cc4,cc5;
  float cr1,cr2,cr3,cr4,cr5;
  float ct1PtCut20,ct2PtCut20,ct3PtCut20,ct4PtCut20,ct5PtCut20;
  float ecalIso,hcalIso,trackIso;

  void Set(HiForest * c, int j) {    cc1=c->photon.cc1[j];
    cc2=c->photon.cc2[j];
    cc3=c->photon.cc3[j];
    cc4=c->photon.cc4[j];
    cc5=c->photon.cc5[j];
    cr1=c->photon.cr1[j];
    cr2=c->photon.cr2[j];
    cr3=c->photon.cr3[j];
    cr4=c->photon.cr4[j];
    cr5=c->photon.cr5[j];
    ct1PtCut20=c->photon.ct1PtCut20[j];
    ct2PtCut20=c->photon.ct2PtCut20[j];
    ct3PtCut20=c->photon.ct3PtCut20[j];
    ct4PtCut20=c->photon.ct4PtCut20[j];
    ct5PtCut20=c->photon.ct5PtCut20[j];
    ecalIso = c->photon.ecalRecHitSumEtConeDR04[j];
    hcalIso = c->photon.hcalTowerSumEtConeDR04[j];
    trackIso = c->photon.trkSumPtHollowConeDR04[j];
  }
};

vector<jetKinem> nullVec;




void forest2yskim_jetSkim(TString inputFile_="mergedFiles/allQcdPhoton50-HYDJET-START44-V12-v1.root",
			  std::string MinbiasFname = "skim_trackJet_minbiasTrackJet_mc.root",
			  float cutphotonPt  = 40, 
			  bool isMC=true,
			  std::string outname = "testPhotonSkim.root",
			  TString jetAlgo="akPu3PF",
			  bool isPP=false,
			  float cQnch=0,   // Delta E = cQnch * l^2
			  bool fixedLpath=0
			  )
{ 
  
  // path length histogram
  TFile* fpath = new TFile("pathLengthHistogram_v1.root");
  TH1D* hPath = (TH1D*)fpath->Get("pathLengthDistribution");
  
  int seconds = time(NULL);
  cout << " time = " <<seconds%10000<< endl;
  TRandom3 rand(seconds%10000);
  TString datafname  = "";
  float cutphotonEta = 1.44;
  float preCutPhotonEt = 30;
   
  const int nMaxPho = 100;
  
  
  cout << endl << endl << endl << "WARNING.. the noise filter is off!!! " <<endl << endl << endl ;
  HiForest *c = new HiForest(inputFile_.Data(),jetAlgo);
  c->doTrackCorrections = true;
  c->doTrackingSeparateLeadingSubleading = false;
  c->triggerMode = kPHOTON; // kJET, kPHOTON, kMB
   
  c->InitTree();
  c->GetEnergyScaleTable("photonEnergyScaleTable_Hydjet_GammaJet.root");
  


  
  // now open new root file
  TFile* newfile_data = new TFile(outname.data(),"recreate");
  
  TTree* newtreePhoton;
  float newPt[nMaxPho];  // <<= temporary space                                                                              
  int isLeading[nMaxPho];
  int order[nMaxPho];
  float corrPt[nMaxPho];
  newtreePhoton = c->photonTree->CloneTree(0);
  newtreePhoton->SetName("yongsunPhotonTree");
  newtreePhoton->SetMaxTreeSize(MAXTREESIZE);
  newtreePhoton->Branch("order",  order, "order[nPhotons]/I");
  newtreePhoton->Branch("corrPt", corrPt,"corrPt[nPhotons]/F");
  newtreePhoton->Branch("leading",isLeading,"leading[nPhotons]/I");
   
  // jet tree! 
  int nJet;    
  float jetPt[500];
  float jetEta[500];
  float jetPhi[500];
  float jetDphi[500];
  int jetSubid[500];
  TTree *newtreeJet = new TTree("yJet","jets");
  newtreeJet->SetMaxTreeSize(MAXTREESIZE);
  newtreeJet->Branch("nJet",&nJet,"nJet/I");
  newtreeJet->Branch("pt",jetPt,"pt[nJet]/F");
  newtreeJet->Branch("eta",jetEta,"eta[nJet]/F");
  newtreeJet->Branch("phi",jetPhi,"phi[nJet]/F");
  newtreeJet->Branch("dphi",jetDphi,"dphi[nJet]/F");
  if ( isMC) 
    newtreeJet->Branch("subid",jetSubid,"subid[nJet]/I");
  
  



  // Track tree
  int nTrk;
  float trkPt[MAXTRK];
  float trkEta[MAXTRK];
  float trkPhi[MAXTRK];
  float trkDphi[MAXTRK];
  float trkWeight[MAXTRK];
  TTree *newtreeTrack = new TTree("yTrk","tracks");
  newtreeTrack->SetMaxTreeSize(MAXTREESIZE);
  newtreeTrack->Branch("ntrk",&nTrk,"ntrk/I");
  newtreeTrack->Branch("pt",trkPt,"pt[ntrk]/F");
  newtreeTrack->Branch("eta",trkEta,"eta[ntrk]/F");
  newtreeTrack->Branch("phi",trkPhi,"phi[ntrk]/F");
  newtreeTrack->Branch("dphi", trkDphi, "dphi[ntrk]/F");
  newtreeTrack->Branch("trkWeight",trkWeight,"trkWeight[ntrk]/F");
   
  
  const int maxGp = 30000;
  int nGp;
  int   gpSube[maxGp];
  int   gpChg[maxGp];
  float gpPt[maxGp];
  float gpEta[maxGp];
  float gpPhi[maxGp];
  float gpDphi[maxGp];
    
  TTree *newtreeGp;
  if ( isMC ) { 
    newtreeGp = new TTree("gp","gen chg particle");
    newtreeGp->SetMaxTreeSize(MAXTREESIZE);
    newtreeGp->Branch("nGp",&nGp,"nGp/I");
    newtreeGp->Branch("sube",gpSube,"sube[nGp]/I");
    newtreeGp->Branch("chg",gpChg,"chg[nGp]/I");
    newtreeGp->Branch("pt",gpPt,"pt[nGp]/F");
    newtreeGp->Branch("eta",gpEta,"eta[nGp]/F");
    newtreeGp->Branch("phi",gpPhi,"phi[nGp]/F");
    newtreeGp->Branch("dphi",gpDphi,"dphi[nGp]/F");
  }
  
  int nMtrk;
  float mTrkPt[MAXMTRK];
  float mTrkEta[MAXMTRK];
  float mTrkPhi[MAXMTRK];
  float mTrkWeight[MAXMTRK];
  float mTrkDphi[MAXMTRK];
  
  TTree * tmixTrk = new TTree("mTrk","Track from second minbias events");
  tmixTrk->SetMaxTreeSize(MAXTREESIZE);
  tmixTrk->Branch("ntrk",&nMtrk,"ntrk/I");
  tmixTrk->Branch("pt",mTrkPt,"pt[ntrk]/F");
  tmixTrk->Branch("eta",mTrkEta,"eta[ntrk]/F");
  tmixTrk->Branch("phi",mTrkPhi,"phi[ntrk]/F");
  tmixTrk->Branch("trkWeight",mTrkWeight,"trkWeight[ntrk]/F");
  tmixTrk->Branch("dphi", mTrkDphi, "dphi[ntrk]/F");
  
  
  TTree * tmixGp;
  int   nMgp;
  float mGpPt[MAXMTRK];
  float mGpEta[MAXMTRK];
  float mGpPhi[MAXMTRK];
  float mGpDphi[MAXMTRK];
  int   mGpChg[MAXMTRK];
    
  
  if ( isMC) { 
    tmixGp = new TTree("mGp","genParticle from second minbias events");
    tmixGp->SetMaxTreeSize(MAXTREESIZE);
    tmixGp->Branch("nGp",&nMgp,"nGp/I");
    tmixGp->Branch("pt",mGpPt,"pt[nGp]/F");
    tmixGp->Branch("eta",mGpEta,"eta[nGp]/F");
    tmixGp->Branch("phi",mGpPhi,"phi[nGp]/F");
    tmixGp->Branch("chg",mGpChg,"chg[nGp]/I");
    tmixGp->Branch("dphi", mGpDphi, "dphi[nGp]/F");
  }
  

  int nMjet;
  float mJetPt[MAXMJET];
  float mJetEta[MAXMJET];
  float mJetPhi[MAXMJET];
  float mJetDphi[MAXMJET];
  
  TTree * tmixJet = new TTree("mJet","Jet from minbias events");
  tmixJet->SetMaxTreeSize(MAXTREESIZE);
  tmixJet->Branch("nJet",&nMjet,"nJet/I");
  tmixJet->Branch("pt",mJetPt,"pt[nJet]/F");
  tmixJet->Branch("eta",mJetEta,"eta[nJet]/F");
  tmixJet->Branch("phi",mJetPhi,"phi[nJet]/F");
  tmixJet->Branch("dphi", mJetDphi, "dphi[nJet]/F");
  
  
  
  // Imb means that it was imported from input file
  EvtSel          evtImb;
  
  Int_t           nTrkImb;
  Float_t         trkPtImb[4000];   
  Float_t         trkEtaImb[4000];  
  Float_t         trkPhiImb[4000];  
  Float_t         trkWeightImb[4000];
  
  Int_t           nJetImb;
  Float_t         jetPtImb[100];
  Float_t         jetEtaImb[100];
  Float_t         jetPhiImb[100];
  
  
  Int_t           nGpImb;
  Float_t         gpPtImb[4000];  
  Float_t         gpEtaImb[4000]; 
  Float_t         gpPhiImb[4000]; 
  Int_t           gpChgImb[4000]; 
  TBranch        *b_evt;
  TBranch        *b_nTrkImb;   //!
  TBranch        *b_trkPtImb; 
  TBranch        *b_trkEtaImb;
  TBranch        *b_trkPhiImb;
  TBranch        *b_trkWeightImb;
  TBranch        *b_nJetImb;
  TBranch        *b_jetPtImb;
  TBranch        *b_jetEtaImb;
  TBranch        *b_jetPhiImb;
  TBranch        *b_nGpImb; 
  TBranch        *b_gpPtImb;  
  TBranch        *b_gpEtaImb; 
  TBranch        *b_gpPhiImb; 
  TBranch        *b_gpChgImb; 
  
  TChain         *tjmb[100][nVtxBin+1];
  int nMB[100][nVtxBin+1] ; //= 199109;                                                                                          
  int mbItr[100][nVtxBin+1];
  
  for( int icent = 0 ; icent< nCentBinSkim ; icent++) {
    for( int ivz = 1 ; ivz<=nVtxBin ; ivz++) {
      
      tjmb[icent][ivz] = new TChain(Form("trackAndGenParticles_first_cBin2icent%d_ivz%d",icent,ivz));
      tjmb[icent][ivz]->Add(MinbiasFname.data());
      
      tjmb[icent][ivz]->SetBranchAddress("evt", &evtImb,&b_evt);
      
      tjmb[icent][ivz]->SetBranchAddress("nTrk", &nTrkImb,&b_nTrkImb);
      tjmb[icent][ivz]->SetBranchAddress("trkPt", trkPtImb, &b_trkPtImb);
      tjmb[icent][ivz]->SetBranchAddress("trkEta", trkEtaImb, &b_trkEtaImb);
      tjmb[icent][ivz]->SetBranchAddress("trkPhi", trkPhiImb, &b_trkPhiImb);
      tjmb[icent][ivz]->SetBranchAddress("trkWeight", trkWeightImb, &b_trkWeightImb);
      
      tjmb[icent][ivz]->SetBranchAddress("nJet",   &nJetImb,   &b_nJetImb);
      tjmb[icent][ivz]->SetBranchAddress("jetPt",  &jetPtImb,  &b_jetPtImb);
      tjmb[icent][ivz]->SetBranchAddress("jetEta", &jetEtaImb, &b_jetEtaImb);
      tjmb[icent][ivz]->SetBranchAddress("jetPhi", &jetPhiImb, &b_jetPhiImb);
            

      if ( isMC) {
	tjmb[icent][ivz]->SetBranchAddress("nGp", &nGpImb, &b_nGpImb);
	tjmb[icent][ivz]->SetBranchAddress("gpPt", gpPtImb, &b_gpPtImb);
	tjmb[icent][ivz]->SetBranchAddress("gpEta", gpEtaImb, &b_gpEtaImb);
	tjmb[icent][ivz]->SetBranchAddress("gpPhi", gpPhiImb, &b_gpPhiImb);
	tjmb[icent][ivz]->SetBranchAddress("gpChg", gpChgImb, &b_gpChgImb);
      }      
      
      nMB[icent][ivz] = tjmb[icent][ivz]->GetEntries();
      cout << "number of evetns in (icent = " << icent << ", iVtxZ = "<< ivz << ")  = " << nMB[icent][ivz] << endl;
      int primeSeed = rand.Integer(37324);
      mbItr[icent][ivz] = primeSeed%(nMB[icent][ivz]);
      cout <<" initial itr = " << mbItr[icent][ivz] << endl;
    }
    
  }
  

  
  // reweighting factor should go here
  EvtSel evt;
  GammaJet gj;
  Isolation isol;
  TTree *tgj;
  tgj = new TTree("tgj","gamma jet tree");
  tgj->SetMaxTreeSize(MAXTREESIZE);
  tgj->Branch("evt",&evt.run,"run/I:evt:cBin:pBin:trig/O:offlSel:noiseFilt:anaEvtSel:vz/F:reweight/F"); // todo : add ncoll later
  tgj->Branch("lpho",&gj.photonEt,"photonEt/F:photonRawEt:photonEta:photonPhi:hovere:sigmaIetaIeta:sumIso:genIso:genMomId/I:lJetPt/F:lJetEta:lJetPhi:lJetDphi:lJetSubid/I");
  tgj->Branch("isolation",&isol.cc1,"cc1:cc2:cc3:cc4:cc5:cr1:cr2:cr3:cr4:cr5:ct1PtCut20:ct2PtCut20:ct3PtCut20:ct4PtCut20:ct5PtCut20:ecalIso:hcalIso:trackIso");  // ecalIso,hcalIso,trackIso are the pp style isolation
  
  
  float vzCut = vtxCutData;
  if ( isMC )
    vzCut = vtxCutMc;
  
  
  TH1F* hvz = new TH1F("hvz","",nVtxBin,-vzCut,vzCut);


  // event plane hitogram   
  TH1F* hEvtPlnBin = new TH1F("hEvtPlnBin", "", nPlnBin, -PI/2., PI/2.);
  const int theEvtPlNumber = 21;
   
   // jet algos
                                                                                                                                              
  Jets* theJet;
  theJet = &(c->selectedJet) ;  // made by jetAlgo string!!!!                
  
  if ( isPP )   // No MIXING!!                                                                                                                 
    cout << " This is pp.  Mixing step is skipped" << endl;
    
  
  // LOOP!!
  int nentries = c->GetEntries();
  cout << "number of entries = " << nentries << endl;
  for (Long64_t jentry = 0 ; jentry < nentries; jentry++) {
    //for (Long64_t jentry = 0 ; jentry < 20000; jentry++) {
    if (jentry% 1000 == 0)  {
      cout <<jentry<<" / "<<nentries<<" "<<setprecision(2)<<(double)jentry/nentries*100<<endl;
     }
    c->GetEntry(jentry);
    
    //here
    evt.clear();
    evt.run   = c->evt.run;
    evt.evt = c->evt.evt;
    evt.cBin = c->evt.hiBin;
    evt.pBin   = hEvtPlnBin->FindBin( c->evt.hiEvtPlanes[theEvtPlNumber] ) ;
    evt.reweight = 1;
    evt.trig = 0;
    evt.offlSel = (c->skim.pcollisionEventSelection > 0);
    evt.noiseFilt = (c->skim.pHBHENoiseFilter > 0);
    evt.anaEvtSel = c->selectEvent() && evt.trig;
    evt.vz = c->evt.vz;
    
    //    if (  (isMC ==0 ) && (evt.offlSel!=1) ) // Seems that event selection is already done
    //   continue;
    //  if ( (isMC ==0 ) && (evt.noiseFilt!=1)  )
    //  continue;
        
    int cBin = evt.cBin;
    int vzBin = hvz->FindBin(evt.vz)  ;
    if ( (vzBin<1) || ( vzBin > nVtxBin) )
      continue;
    
    /// correct the photon energy and make order 

    for (int j=0;j< c->photon.nPhotons;j++) {
      if (  ( c->photon.pt[j] > preCutPhotonEt ) && ( fabs( c->photon.eta[j] ) < cutphotonEta ) )
	newPt[j] = c->getCorrEt(j);
      else 
	newPt[j]  =  c->photon.pt[j] - 10000;

      if ( isPP ) 
	newPt[j] = c->photon.pt[j] ;  // if it is pp, the use the original energy value 
      
      corrPt[j] = newPt[j];

      
      if ( (c->isSpike(j)) || (c->photon.hadronicOverEm[j]>0.2) ||  (c->photon.isEle[j]) )
	newPt[j] = newPt[j] - 20000;
      if (c->photon.seedTime[j] ==0 )   // clustering bug
	newPt[j] = newPt[j] - 30000;
      
    }
    TMath::Sort(c->photon.nPhotons, newPt, order);
    
     
    // find the leading photon
    gj.clear();
    int leadingIndex=-1;
    for (int j=0;j<c->photon.nPhotons;j++) {
      if ( c->photon.pt[j]  < preCutPhotonEt ) continue; 
      if ( fabs(c->photon.eta[j]) > cutphotonEta ) continue;
      if (c->isSpike(j)) continue;       
      if (!(c->isLoosePhoton(j))) continue;
	
      // sort using corrected photon pt        
      float theCorrPt= corrPt[j];
      if ( theCorrPt > gj.photonEt) {
	gj.photonEt = theCorrPt;
	  leadingIndex = j;
      }
    }
     
    // give the leading bit to the photon candidates                                                                          
    for (int j=0;j<c->photon.nPhotons;j++) {
      if ( j==leadingIndex)       isLeading[j] = 1;
      else                        isLeading[j] = 0;
    }
       
 
     if ( (gj.photonEt < cutphotonPt) ) 
       continue;
   
     /// Save leading photons 
     if (leadingIndex!=-1) {
       gj.photonRawEt=c->photon.pt[leadingIndex];
       gj.photonEta=c->photon.eta[leadingIndex];
       gj.photonPhi=c->photon.phi[leadingIndex];
       gj.hovere=c->photon.hadronicOverEm[leadingIndex];
       gj.sigmaIetaIeta=c->photon.sigmaIetaIeta[leadingIndex];
       gj.sumIsol=(c->photon.cr4[leadingIndex]+c->photon.cc4[leadingIndex]+c->photon.ct4PtCut20[leadingIndex])/0.9;
       gj.genIso   = c->photon.genCalIsoDR04[leadingIndex];
       gj.genMomId = c->photon.genMomId[leadingIndex];
       isol.Set(c,leadingIndex);
     }
     else {
	gj.clear();
     }
     
     

     ///////////////////// Jet tree ///////////////////////////////////
     nJet = 0 ;
     for (int ij=0; ij< theJet->nref ; ij++) {
       float pLength = hPath->GetRandom();
       if (fixedLpath) pLength = 5.5;
       //      cout << "pLength = " << pLength << endl;
       float qJetPt = theJet->jtpt[ij] - cQnch * pLength*pLength;
       if ( qJetPt < cutjetPtSkim)
	 continue;
       if ( fabs( theJet->jteta[ij] ) > cutjetEta ) //   
	 continue;
       if ( getDR( theJet->jteta[ij], theJet->jtphi[ij], gj.photonEta, gj.photonPhi) < 0.3 )
	 continue;
       
       jetPt[nJet] = qJetPt;
       jetEta[nJet] = theJet->jteta[ij];
       jetPhi[nJet] = theJet->jtphi[ij];
       jetSubid[nJet] = theJet->subid[ij];
       if (jetPt[nJet] >0) 
	 jetDphi[nJet] = getAbsDphi( theJet->jtphi[ij], gj.photonPhi) ;
       else
	 jetDphi[nJet] = -1;
       
       nJet++ ; 
     }
     

     float maxJpt = 0;
     int jetLeadingIndex = -1;
     
     for (int ij=0; ij< nJet ; ij++) {
       // leading jet cut is same for analysis 
       if ( jetDphi[ij] < awayRange ) 
	 continue; 
       if ( fabs( jetEta[ij] ) > cutjetEta ) 
	 continue;
       if ( jetPt[ij] > maxJpt) {
	 maxJpt = jetPt[ij] ; 
	 jetLeadingIndex = ij;
       }
       
       if ( jetLeadingIndex > -1 ) {
	 gj.lJetPt = jetPt[jetLeadingIndex];
	 gj.lJetEta = jetEta[jetLeadingIndex];
	 gj.lJetPhi = jetPhi[jetLeadingIndex];
	 gj.lJetDphi =  jetDphi[jetLeadingIndex];
	 gj.lJetSubid=  jetSubid[jetLeadingIndex];
       }
       else {
	 gj.lJetPt = -1;
	 gj.lJetEta = 999;
	 gj.lJetPhi = 999;
	 gj.lJetDphi = 0;
	 gj.lJetSubid=  -99;
       }
     }
     
 
 
//////////////////////////////////////////// New collection of tracks                                                 
 nTrk = 0;
     for (int it=0; it < c->track.nTrk; it++ ) {
       if ( c->track.highPurity[it] == 0 )
         continue;   // only high purity high pt tracks and all pixel track                                                 
       if ( c->track.trkPt[it] < cuttrkPt )
	 continue;
       if ( fabs( c->track.trkEta[it]  ) > cuttrkEtaSkim )
         continue;
       
       trkPt[nTrk]  = c->track.trkPt[it];
       trkEta[nTrk] = c->track.trkEta[it];
       trkPhi[nTrk] = c->track.trkPhi[it];
       
       if  (trkPt[nTrk] > 0 )
	 trkDphi[nTrk] = getAbsDphi ( trkPhi[nTrk], gj.photonPhi) ;
       else
         trkDphi[nTrk] = -1;

       
       trkWeight[nTrk] = c->getTrackCorrection(it);
       
       nTrk++;
     }
     
     
          
     /// Gen Particle 
     nGp = 0;
     if ( isMC ) {
       for ( int ig = 0 ; ig < c->genparticle.mult ; ig++) {
	 if ( c->genparticle.pt[ig] < cuttrkPt )  /// not possibly though..                                 
	   continue;
	 if ( fabs( c->genparticle.eta[ig] ) > cuttrkEtaSkim )
	   continue;
	 if ( c->genparticle.chg[ig] == 0 )
	   continue;
	 
	 gpChg[nGp] =  c->genparticle.chg[ig] ;
	 gpPt[nGp]  = c->genparticle.pt[ig];
	 gpEta[nGp] = c->genparticle.eta[ig];
	 gpPhi[nGp] = c->genparticle.phi[ig];
	 gpSube[nGp] = c->genparticle.sube[ig];
	 if ( gpPt[nGp]>0 )
	   gpDphi[nGp] = getAbsDphi (gpPhi[nGp], gj.photonPhi) ; 
	 else
	   gpDphi[nGp] = -1 ;
	 
	 nGp++;
       }
     }
     
     // now let's mix minbias tracks
     
     int iCounter=0;
     int loopCounter=0;
     bool noSuchEvent = false;
     int nMixing = nMixing1;
     //    nMixing = nMixing2;    // = 1 
     
     nMtrk = 0;
     nMjet = 0;
     nMgp  = 0;
    
     if ( isPP )  {   // No MIXING!!
       iCounter = nMixing+1;
     }
     while (iCounter<nMixing)  {
       loopCounter++;
       if ( loopCounter > nMB[cBin][vzBin]+1) {
	 iCounter = 999999 ;
	 noSuchEvent = true;
	 cout << " no such event!! :  icent = " << cBin << ",  vzBin = " << vzBin << ",  pBin = " << evt.pBin << endl;
       }
       
       mbItr[cBin][vzBin] = mbItr[cBin][vzBin] + 1;
       if ( mbItr[cBin][vzBin] == nMB[cBin][vzBin] )
	 mbItr[cBin][vzBin] =  mbItr[cBin][vzBin] - nMB[cBin][vzBin];
	
       /// Load the minbias tracks!!
       tjmb[cBin][vzBin]->GetEntry(mbItr[cBin][vzBin]);
       
       if  ( evt.pBin != evtImb.pBin ) 
	 continue;
       
       if ( evt.vz == evtImb.vz ) {
	 cout << " exactly same event!!" << endl;
	 continue;
       }
       
       // ok found the event!! ///////////
       loopCounter =0;
       ////////////////////////////////////
       
       for (int it = 0 ; it < nTrkImb ; it++) {
	 if ( trkPtImb[it] < cuttrkPt )
	   continue;
	 if ( fabs( trkEtaImb[it] ) > cuttrkEtaSkim )
	   continue;
	 
	  mTrkPt[nMtrk]    = trkPtImb[it];
	  mTrkEta[nMtrk]   = trkEtaImb[it];
	  mTrkPhi[nMtrk]   = trkPhiImb[it];
	  mTrkWeight[nMtrk]= trkWeightImb[it];
	  if  ( mTrkPt[nMtrk]>0 )  
	    mTrkDphi[nMtrk]  =   getAbsDphi(mTrkPhi[nMtrk], gj.photonPhi) ;
	  else 
	    mTrkDphi[nMtrk]=-1;

	  nMtrk++;
       }

       for (int it = 0 ; it < nJetImb ; it++) {
         if ( jetPtImb[it] < cutjetPtSkim )
           continue;
         if ( fabs( jetEtaImb[it] ) > cuttrkEtaSkim )
           continue;
	 
	 mJetPt[nMjet]    = jetPtImb[it];
	 mJetEta[nMjet]   = jetEtaImb[it];
	 mJetPhi[nMjet]   = jetPhiImb[it];
	 if  ( mJetPt[nMjet]>0 )
	   mJetDphi[nMjet]  =   getAbsDphi(mJetPhi[nMjet], gj.photonPhi) ;
	 else
	   mJetDphi[nMjet]=-1;
	 
	 nMjet++;
       }
       
       
       if ( isMC) { 
	 for (int it = 0 ; it < nGpImb ; it++) {
	   if ( gpPtImb[it] < cuttrkPt )
	     continue;
	   if ( fabs(gpEtaImb[it]) > cuttrkEtaSkim )
	     continue;
	   if ( gpChgImb[it] == 0 ) 
	     continue;
	   
	   mGpPt[nMgp]  =   gpPtImb[it];
	   mGpEta[nMgp]  =   gpEtaImb[it];
	   mGpPhi[nMgp]  =   gpPhiImb[it];
	   mGpChg[nMgp]  =   gpChgImb[it];
	   if  (mGpPt[nMgp] > 0 ) 
	     mGpDphi[nMgp] = getAbsDphi ( mGpPhi[nMgp], gj.photonPhi );
	   else 
	     mGpDphi[nMgp]=-1;

	   nMgp++;
	 }
       }
       iCounter++;
     }
     
     
     if ( noSuchEvent )
       continue;
     
     
     tgj->Fill();
     newtreeJet->Fill();
     newtreeTrack->Fill();
     tmixTrk->Fill();
     tmixJet->Fill();     
     if ( isMC ) {
       newtreeGp->Fill();
       tmixGp->Fill();
     }
     
     newtreePhoton->Fill();
     
   }
   
   
   
   newfile_data->Write();
   //   newfile_data->Close();   // <<=== If there is close() function. writing stucks in the middle of looping.. I don't know why!!
   cout << " Done! "<< endl;
}

