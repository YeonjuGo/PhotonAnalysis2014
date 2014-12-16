//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Feb  1 18:25:39 2013 by ROOT version 5.32/01
// from TTree trackAndGenParticles_first_cBin2icent39_ivz6/track and jets
// found on file: skim_tracks_pbpbMB_v3_data.root
//////////////////////////////////////////////////////////

#ifndef trackAndGenParticles_first_cBin2icent39_ivz6_h
#define trackAndGenParticles_first_cBin2icent39_ivz6_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class trackAndGenParticles_first_cBin2icent39_ivz6 {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           evt_run;
   Int_t           evt_evt;
   Int_t           evt_cBin;
   Int_t           evt_pBin;
   Bool_t          evt_trig;
   Bool_t          evt_offlSel;
   Bool_t          evt_noiseFilt;
   Bool_t          evt_anaEvtSel;
   Float_t         evt_vz;
   Float_t         evt_reweight;
   Int_t           nTrk;
   Float_t         trkPt[1];   //[nTrk]
   Float_t         trkEta[1];   //[nTrk]
   Float_t         trkPhi[1];   //[nTrk]
   Float_t         trkWeight[1];   //[nTrk]
   Int_t           nJet;
   Float_t         jetPt[1];   //[nJet]
   Float_t         jetEta[1];   //[nJet]
   Float_t         jetPhi[1];   //[nJet]
   Int_t           nGp;
   Float_t         gpPt[1];   //[nGp]
   Float_t         gpEta[1];   //[nGp]
   Float_t         gpPhi[1];   //[nGp]
   Int_t           gpChg[1];   //[nGp]

   // List of branches
   TBranch        *b_evt;   //!
   TBranch        *b_nTrk;   //!
   TBranch        *b_trkPt;   //!
   TBranch        *b_trkEta;   //!
   TBranch        *b_trkPhi;   //!
   TBranch        *b_trkWeight;   //!
   TBranch        *b_nJet;   //!
   TBranch        *b_jetPt;   //!
   TBranch        *b_jetEta;   //!
   TBranch        *b_jetPhi;   //!
   TBranch        *b_nGp;   //!
   TBranch        *b_gpPt;   //!
   TBranch        *b_gpEta;   //!
   TBranch        *b_gpPhi;   //!
   TBranch        *b_gpChg;   //!

   trackAndGenParticles_first_cBin2icent39_ivz6(TTree *tree=0);
   virtual ~trackAndGenParticles_first_cBin2icent39_ivz6();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef trackAndGenParticles_first_cBin2icent39_ivz6_cxx
trackAndGenParticles_first_cBin2icent39_ivz6::trackAndGenParticles_first_cBin2icent39_ivz6(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("skim_tracks_pbpbMB_v3_data.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("skim_tracks_pbpbMB_v3_data.root");
      }
      f->GetObject("trackAndGenParticles_first_cBin2icent39_ivz6",tree);

   }
   Init(tree);
}

trackAndGenParticles_first_cBin2icent39_ivz6::~trackAndGenParticles_first_cBin2icent39_ivz6()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t trackAndGenParticles_first_cBin2icent39_ivz6::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t trackAndGenParticles_first_cBin2icent39_ivz6::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void trackAndGenParticles_first_cBin2icent39_ivz6::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("evt", &evt_run, &b_evt);
   fChain->SetBranchAddress("nTrk", &nTrk, &b_nTrk);
   fChain->SetBranchAddress("trkPt", trkPt, &b_trkPt);
   fChain->SetBranchAddress("trkEta", trkEta, &b_trkEta);
   fChain->SetBranchAddress("trkPhi", trkPhi, &b_trkPhi);
   fChain->SetBranchAddress("trkWeight", trkWeight, &b_trkWeight);
   fChain->SetBranchAddress("nJet", &nJet, &b_nJet);
   fChain->SetBranchAddress("jetPt", &jetPt, &b_jetPt);
   fChain->SetBranchAddress("jetEta", &jetEta, &b_jetEta);
   fChain->SetBranchAddress("jetPhi", &jetPhi, &b_jetPhi);
   fChain->SetBranchAddress("nGp", &nGp, &b_nGp);
   fChain->SetBranchAddress("gpPt", &gpPt, &b_gpPt);
   fChain->SetBranchAddress("gpEta", &gpEta, &b_gpEta);
   fChain->SetBranchAddress("gpPhi", &gpPhi, &b_gpPhi);
   fChain->SetBranchAddress("gpChg", &gpChg, &b_gpChg);
   Notify();
}

Bool_t trackAndGenParticles_first_cBin2icent39_ivz6::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void trackAndGenParticles_first_cBin2icent39_ivz6::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t trackAndGenParticles_first_cBin2icent39_ivz6::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef trackAndGenParticles_first_cBin2icent39_ivz6_cxx
