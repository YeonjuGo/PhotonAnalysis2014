 {  

    gStyle->SetPalette(1,0);
      gStyle->SetPadColor(0);
      gStyle->SetPadBorderSize(0);
      gStyle->SetPadBorderMode(0);
      gStyle->SetCanvasColor(0);
      gStyle->SetCanvasBorderMode(0);
      gStyle->SetCanvasBorderSize(0);
      gStyle->SetFrameBorderMode(0);
      gStyle->SetFrameLineColor(0);
      gStyle->SetTitleColor(0);
      gStyle->SetTitleBorderSize(0);
      gStyle->SetPalette(1,0);
      gStyle->SetPadTickX(1);
      gStyle->SetPadTickY(1);
      gStyle->SetPadColor(0);
      gStyle->SetPadBorderSize(0);
      gStyle->SetPadBorderMode(0);
      gStyle->SetCanvasColor(0);
      gStyle->SetCanvasBorderMode(0);
      gStyle->SetCanvasBorderSize(0);
      gStyle->SetFrameBorderMode(0);
      gStyle->SetFrameLineColor(0);
      gStyle->SetFrameFillColor(0);
      gStyle->SetTextFont(42);
      gStyle->SetLabelFont(42,"XYZ");
      gStyle->SetTitleFont(42,"XYZ");
      gStyle->SetTitleColor(0);
      gStyle->SetTitleBorderSize(0);
      gStyle->SetTitleXSize(.055);
      gStyle->SetTitleYSize(.055);
      gStyle->SetTitleXOffset(1.0);
      gStyle->SetTitleYOffset(1.3);
      gStyle->SetLabelSize(0.045,"XYZ");
      gStyle->SetLabelOffset(0.01,"X");
      gStyle->SetLabelOffset(0.01,"Y");
      gStyle->SetTitleColor(1,"XYZ");
      //     gStyle->SetHistFillColor(1);
      //     gStyle->SetHistFillStyle(0);
      gStyle->SetHistLineColor(1);
      gStyle->SetHistLineStyle(0);
      gStyle->SetHistLineWidth(3);
      gStyle->SetHistLineWidth(1);
      gStyle->SetEndErrorSize(0);
      gStyle->SetErrorX(0);
      gStyle->SetMarkerStyle(20);
      gStyle->SetMarkerSize(1);
      //      gStyle->SetOptFit(1111);
      gStyle->SetOptFit(0);
      gStyle->SetStatColor(0);
      gStyle->SetStatBorderSize(1);
      gStyle->SetPadLeftMargin(0.17);
      gStyle->SetPadBottomMargin(0.15);
      gStyle->SetPadTopMargin(0.05);
      gStyle->SetPadRightMargin(0.08);
      //   gStyle->SetPadRightMargin(0.15);
      gStyle->SetOptStat(0);

      gSystem->Load("libFWCoreFWLite.so");  
      //or gSystem->Load("libPhysicsToolsFWLite.so"); for CMSSW < 0.8.0
      AutoLibraryLoader::enable();
      
      const Int_t NRGBs = 5;
      //const Int_t NCont = 255;
      const Int_t NCont = 200;
      
      Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
      Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
      Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
      Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
      
	 
      // for isolation study
      //     Double_t stops[NRGBs] = { 0.00, 0.001, 0.002, 0.999, 1.00 };      
      //   Double_t green[NRGBs] = { 0.00, 0.00, 1.0, 0.1, 0.00 };
      //   Double_t blue[NRGBs]  = { 0.00, 0.00, 1.00, 0.1, 0.00 };
      //  Double_t red[NRGBs]   = { 0.00, 0.00, 1.0, 0.8, 0.0 };
      
      //    Double_t stops[NRGBs] = { 0.00, 0.001, 0.002, 0.999, 1.00 };
      //     Double_t green[NRGBs] = { 0.00, 0.00, 1.0, 0.1, 0.00 };
      //  Double_t blue[NRGBs]  = { 0.00, 0.00, .01, 0.02, 0.00 };
      //   Double_t red[NRGBs]   = { 0.00, 0.00, 1.0, 0.8, 0.0 };
      
      
      TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
      //gStyle->CreateColorGradientTable(NRGBs, stops, red, green, blue, NCont); 
      
      gStyle->SetNumberContours(NCont);

      gROOT->ForceStyle();


      gSystem->Load("libDataFormatsHeavyIonEvent");
      gSystem->AddIncludePath("-I$CMSSW_BASE/src/");
      gSystem->AddIncludePath("-I$CMSSW_RELEASE_BASE/src/");
}


