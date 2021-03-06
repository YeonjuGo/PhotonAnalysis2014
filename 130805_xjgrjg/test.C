{
//=========Macro generated from canvas: c2/
//=========  (Fri Aug 16 11:17:52 2013) by ROOT version5.34/02
   TCanvas *c2 = new TCanvas("c2", "",195,344,800,402);
   gStyle->SetOptStat(0);
   c2->Range(0,0,1,1);
   c2->SetFillColor(0);
   c2->SetBorderMode(0);
   c2->SetBorderSize(2);
   c2->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: c2_1
   TPad *c2_1 = new TPad("c2_1", "c2_1",0.01,0.01,0.49,0.99);
   c2_1->Draw();
   c2_1->cd();
   c2_1->Range(8.749998,0.54375,221.25,1.10625);
   c2_1->SetFillColor(0);
   c2_1->SetBorderMode(0);
   c2_1->SetBorderSize(2);
   c2_1->SetFrameBorderMode(0);
   c2_1->SetFrameBorderMode(0);
   
   TH1D *hx1 = new TH1D("hx1","",200,30,200);
   hx1->SetMinimum(0.6);
   hx1->SetMaximum(1.05);
   hx1->SetStats(0);
   hx1->SetLineColor(2);
   hx1->SetMarkerColor(2);
   hx1->SetMarkerStyle(20);
   hx1->GetXaxis()->SetTitle("pT of photon (GeV)");
   hx1->GetXaxis()->CenterTitle(true);
   hx1->GetXaxis()->SetLabelFont(42);
   hx1->GetXaxis()->SetLabelSize(0.035);
   hx1->GetXaxis()->SetTitleFont(42);
   hx1->GetYaxis()->SetTitle("<x_{J,#gamma}>");
   hx1->GetYaxis()->CenterTitle(true);
   hx1->GetYaxis()->SetLabelFont(42);
   hx1->GetYaxis()->SetLabelSize(0.035);
   hx1->GetYaxis()->SetTitleOffset(1.17);
   hx1->GetYaxis()->SetTitleFont(42);
   hx1->GetZaxis()->SetLabelFont(42);
   hx1->GetZaxis()->SetLabelSize(0.035);
   hx1->GetZaxis()->SetTitleSize(0.035);
   hx1->GetZaxis()->SetTitleFont(42);
   hx1->Draw("");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(6);
   grae->SetName("gx_cent1");
   grae->SetTitle("");
   grae->SetFillColor(1);
   grae->SetLineColor(2);
   grae->SetMarkerColor(2);
   grae->SetMarkerStyle(25);
   grae->SetPoint(0,1.189217e-312,1.189217e-312);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,45,0.9773233);
   grae->SetPointError(1,0.01,0.01,0.007573649,0.007573649);
   grae->SetPoint(2,55,0.9071545);
   grae->SetPointError(2,0.01,0.01,0.008638534,0.008638534);
   grae->SetPoint(3,70,0.8566355);
   grae->SetPointError(3,0.01,0.01,0.01042453,0.01042453);
   grae->SetPoint(4,100,0.7988919);
   grae->SetPointError(4,0.01,0.01,0.01461797,0.01461797);
   grae->SetPoint(5,160,0.6950344);
   grae->SetPointError(5,0.01,0.01,0.03311339,0.03311339);
   
   TH1F *Graph_gx_cent11 = new TH1F("Graph_gx_cent11","",100,0,176.011);
   Graph_gx_cent11->SetMinimum(0);
   Graph_gx_cent11->SetMaximum(1.083387);
   Graph_gx_cent11->SetDirectory(0);
   Graph_gx_cent11->SetStats(0);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   Graph_gx_cent11->SetLineColor(ci);
   Graph_gx_cent11->GetXaxis()->SetLabelFont(42);
   Graph_gx_cent11->GetXaxis()->SetLabelSize(0.035);
   Graph_gx_cent11->GetXaxis()->SetTitleSize(0.035);
   Graph_gx_cent11->GetXaxis()->SetTitleFont(42);
   Graph_gx_cent11->GetYaxis()->SetLabelFont(42);
   Graph_gx_cent11->GetYaxis()->SetLabelSize(0.035);
   Graph_gx_cent11->GetYaxis()->SetTitleSize(0.035);
   Graph_gx_cent11->GetYaxis()->SetTitleFont(42);
   Graph_gx_cent11->GetZaxis()->SetLabelFont(42);
   Graph_gx_cent11->GetZaxis()->SetLabelSize(0.035);
   Graph_gx_cent11->GetZaxis()->SetTitleSize(0.035);
   Graph_gx_cent11->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_gx_cent11);
   
   grae->Draw(" p");
   
   grae = new TGraphAsymmErrors(6);
   grae->SetName("gx_cent2");
   grae->SetTitle("");
   grae->SetFillColor(1);
   grae->SetLineColor(2);
   grae->SetMarkerColor(2);
   grae->SetMarkerStyle(24);
   grae->SetPoint(0,2.829613e-316,2.822715e-316);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,45,0.9754428);
   grae->SetPointError(1,0.01,0.01,0.01008794,0.01008794);
   grae->SetPoint(2,55,0.8928048);
   grae->SetPointError(2,0.01,0.01,0.01142835,0.01142835);
   grae->SetPoint(3,70,0.8364082);
   grae->SetPointError(3,0.01,0.01,0.01309216,0.01309216);
   grae->SetPoint(4,100,0.7865641);
   grae->SetPointError(4,0.01,0.01,0.01752756,0.01752756);
   grae->SetPoint(5,160,0.78125);
   grae->SetPointError(5,0.01,0.01,0.03056542,0.03056542);
   
   TH1F *Graph_gx_cent22 = new TH1F("Graph_gx_cent22","",100,0,176.011);
   Graph_gx_cent22->SetMinimum(0);
   Graph_gx_cent22->SetMaximum(1.084084);
   Graph_gx_cent22->SetDirectory(0);
   Graph_gx_cent22->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gx_cent22->SetLineColor(ci);
   Graph_gx_cent22->GetXaxis()->SetLabelFont(42);
   Graph_gx_cent22->GetXaxis()->SetLabelSize(0.035);
   Graph_gx_cent22->GetXaxis()->SetTitleSize(0.035);
   Graph_gx_cent22->GetXaxis()->SetTitleFont(42);
   Graph_gx_cent22->GetYaxis()->SetLabelFont(42);
   Graph_gx_cent22->GetYaxis()->SetLabelSize(0.035);
   Graph_gx_cent22->GetYaxis()->SetTitleSize(0.035);
   Graph_gx_cent22->GetYaxis()->SetTitleFont(42);
   Graph_gx_cent22->GetZaxis()->SetLabelFont(42);
   Graph_gx_cent22->GetZaxis()->SetLabelSize(0.035);
   Graph_gx_cent22->GetZaxis()->SetTitleSize(0.035);
   Graph_gx_cent22->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_gx_cent22);
   
   grae->Draw(" p");
   
   grae = new TGraphAsymmErrors(6);
   grae->SetName("gx_cent3");
   grae->SetTitle("");
   grae->SetFillColor(1);
   grae->SetLineColor(2);
   grae->SetMarkerColor(2);
   grae->SetMarkerStyle(20);
   grae->SetPoint(0,2.822715e-316,2.829613e-316);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,45,0.9534911);
   grae->SetPointError(1,0.01,0.01,0.01049306,0.01049306);
   grae->SetPoint(2,55,0.9059483);
   grae->SetPointError(2,0.01,0.01,0.01556891,0.01556891);
   grae->SetPoint(3,70,0.8824841);
   grae->SetPointError(3,0.01,0.01,0.01857424,0.01857424);
   grae->SetPoint(4,100,0.7530669);
   grae->SetPointError(4,0.01,0.01,0.02268836,0.02268836);
   grae->SetPoint(5,160,0.8038793);
   grae->SetPointError(5,0.01,0.01,0.05970443,0.05970443);
   
   TH1F *Graph_gx_cent33 = new TH1F("Graph_gx_cent33","",100,0,176.011);
   Graph_gx_cent33->SetMinimum(0);
   Graph_gx_cent33->SetMaximum(1.060383);
   Graph_gx_cent33->SetDirectory(0);
   Graph_gx_cent33->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gx_cent33->SetLineColor(ci);
   Graph_gx_cent33->GetXaxis()->SetLabelFont(42);
   Graph_gx_cent33->GetXaxis()->SetLabelSize(0.035);
   Graph_gx_cent33->GetXaxis()->SetTitleSize(0.035);
   Graph_gx_cent33->GetXaxis()->SetTitleFont(42);
   Graph_gx_cent33->GetYaxis()->SetLabelFont(42);
   Graph_gx_cent33->GetYaxis()->SetLabelSize(0.035);
   Graph_gx_cent33->GetYaxis()->SetTitleSize(0.035);
   Graph_gx_cent33->GetYaxis()->SetTitleFont(42);
   Graph_gx_cent33->GetZaxis()->SetLabelFont(42);
   Graph_gx_cent33->GetZaxis()->SetLabelSize(0.035);
   Graph_gx_cent33->GetZaxis()->SetTitleSize(0.035);
   Graph_gx_cent33->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_gx_cent33);
   
   grae->Draw(" p");
   TLine *line = new TLine(30,1,200,1);
   line->SetLineStyle(7);
   line->Draw();
   
   TLegend *leg = new TLegend(0.3272613,0.6069783,0.8873534,0.8730524,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("NULL","2.76TeV","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("gx_cent1","pPb 0 GeV < E_{T}^{HF|#eta|>4} < 20 GeV","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(25);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("gx_cent2","pPb 20 GeV < E_{T}^{HF|#eta|>4} < 30 GeV","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("gx_cent3","pPb 30 GeV < E_{T}^{HF|#eta|>4} < 100 GeV","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   leg->Draw();
   c2_1->Modified();
   c2->cd();
  
// ------------>Primitives in pad: c2_2
   c2_2 = new TPad("c2_2", "c2_2",0.51,0.01,0.99,0.99);
   c2_2->Draw();
   c2_2->cd();
   c2_2->Range(8.749998,-0.12625,221.25,1.23625);
   c2_2->SetFillColor(0);
   c2_2->SetBorderMode(0);
   c2_2->SetBorderSize(2);
   c2_2->SetFrameBorderMode(0);
   c2_2->SetFrameBorderMode(0);
   
   TH1D *hr2 = new TH1D("hr2","",200,30,200);
   hr2->SetMinimum(0.01);
   hr2->SetMaximum(1.1);
   hr2->SetStats(0);
   hr2->SetLineColor(3);
   hr2->SetMarkerColor(3);
   hr2->SetMarkerStyle(20);
   hr2->GetXaxis()->SetTitle("pT of photon (GeV)");
   hr2->GetXaxis()->CenterTitle(true);
   hr2->GetXaxis()->SetLabelFont(42);
   hr2->GetXaxis()->SetLabelSize(0.035);
   hr2->GetXaxis()->SetTitleFont(42);
   hr2->GetYaxis()->SetTitle("r_{J,#gamma}");
   hr2->GetYaxis()->CenterTitle(true);
   hr2->GetYaxis()->SetLabelFont(42);
   hr2->GetYaxis()->SetLabelSize(0.035);
   hr2->GetYaxis()->SetTitleOffset(1.25);
   hr2->GetYaxis()->SetTitleFont(42);
   hr2->GetZaxis()->SetLabelFont(42);
   hr2->GetZaxis()->SetLabelSize(0.035);
   hr2->GetZaxis()->SetTitleSize(0.035);
   hr2->GetZaxis()->SetTitleFont(42);
   hr2->Draw("");
   
   grae = new TGraphAsymmErrors(6);
   grae->SetName("gr_cent1");
   grae->SetTitle("");
   grae->SetFillColor(1);
   grae->SetLineColor(2);
   grae->SetMarkerColor(2);
   grae->SetMarkerStyle(25);
   grae->SetPoint(0,1.189217e-312,1.189217e-312);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,45,0.3184945);
   grae->SetPointError(1,0.01,0.01,0.01006351,0.01006351);
   grae->SetPoint(2,55,0.4427962);
   grae->SetPointError(2,0.01,0.01,0.01578536,0.01578536);
   grae->SetPoint(3,70,0.5258224);
   grae->SetPointError(3,0.01,0.01,0.02033498,0.02033498);
   grae->SetPoint(4,100,0.6666667);
   grae->SetPointError(4,0.01,0.01,0.0350612,0.0350612);
   grae->SetPoint(5,160,0.7119353);
   grae->SetPointError(5,0.01,0.01,0.073567,0.073567);
   
   TH1F *Graph_gr_cent14 = new TH1F("Graph_gr_cent14","",100,0,176.011);
   Graph_gr_cent14->SetMinimum(0);
   Graph_gr_cent14->SetMaximum(0.8640525);
   Graph_gr_cent14->SetDirectory(0);
   Graph_gr_cent14->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gr_cent14->SetLineColor(ci);
   Graph_gr_cent14->GetXaxis()->SetLabelFont(42);
   Graph_gr_cent14->GetXaxis()->SetLabelSize(0.035);
   Graph_gr_cent14->GetXaxis()->SetTitleSize(0.035);
   Graph_gr_cent14->GetXaxis()->SetTitleFont(42);
   Graph_gr_cent14->GetYaxis()->SetLabelFont(42);
   Graph_gr_cent14->GetYaxis()->SetLabelSize(0.035);
   Graph_gr_cent14->GetYaxis()->SetTitleSize(0.035);
   Graph_gr_cent14->GetYaxis()->SetTitleFont(42);
   Graph_gr_cent14->GetZaxis()->SetLabelFont(42);
   Graph_gr_cent14->GetZaxis()->SetLabelSize(0.035);
   Graph_gr_cent14->GetZaxis()->SetTitleSize(0.035);
   Graph_gr_cent14->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_gr_cent14);
   
   grae->Draw(" p");
   
   grae = new TGraphAsymmErrors(6);
   grae->SetName("gr_cent2");
   grae->SetTitle("");
   grae->SetFillColor(1);
   grae->SetLineColor(2);
   grae->SetMarkerColor(2);
   grae->SetMarkerStyle(24);
   grae->SetPoint(0,1.189217e-312,1.189217e-312);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,45,0.3237924);
   grae->SetPointError(1,0.01,0.01,0.01284349,0.01284349);
   grae->SetPoint(2,55,0.4446474);
   grae->SetPointError(2,0.01,0.01,0.02184288,0.02184288);
   grae->SetPoint(3,70,0.5506984);
   grae->SetPointError(3,0.01,0.01,0.02779345,0.02779345);
   grae->SetPoint(4,100,0.696756);
   grae->SetPointError(4,0.01,0.01,0.04945169,0.04945169);
   grae->SetPoint(5,160,0.7692308);
   grae->SetPointError(5,0.01,0.01,0.09930727,0.09930727);
   
   TH1F *Graph_gr_cent25 = new TH1F("Graph_gr_cent25","",100,0,176.011);
   Graph_gr_cent25->SetMinimum(0);
   Graph_gr_cent25->SetMaximum(0.9553918);
   Graph_gr_cent25->SetDirectory(0);
   Graph_gr_cent25->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gr_cent25->SetLineColor(ci);
   Graph_gr_cent25->GetXaxis()->SetLabelFont(42);
   Graph_gr_cent25->GetXaxis()->SetLabelSize(0.035);
   Graph_gr_cent25->GetXaxis()->SetTitleSize(0.035);
   Graph_gr_cent25->GetXaxis()->SetTitleFont(42);
   Graph_gr_cent25->GetYaxis()->SetLabelFont(42);
   Graph_gr_cent25->GetYaxis()->SetLabelSize(0.035);
   Graph_gr_cent25->GetYaxis()->SetTitleSize(0.035);
   Graph_gr_cent25->GetYaxis()->SetTitleFont(42);
   Graph_gr_cent25->GetZaxis()->SetLabelFont(42);
   Graph_gr_cent25->GetZaxis()->SetLabelSize(0.035);
   Graph_gr_cent25->GetZaxis()->SetTitleSize(0.035);
   Graph_gr_cent25->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_gr_cent25);
   
   grae->Draw(" p");
   
   grae = new TGraphAsymmErrors(6);
   grae->SetName("gr_cent3");
   grae->SetTitle("");
   grae->SetFillColor(1);
   grae->SetLineColor(2);
   grae->SetMarkerColor(2);
   grae->SetMarkerStyle(20);
   grae->SetPoint(0,2.822923e-316,0);
   grae->SetPointError(0,0,0,0,0);
   grae->SetPoint(1,45,0.3145729);
   grae->SetPointError(1,0.01,0.01,0.01477242,0.01477242);
   grae->SetPoint(2,55,0.4343308);
   grae->SetPointError(2,0.01,0.01,0.02756656,0.02756656);
   grae->SetPoint(3,70,0.5369881);
   grae->SetPointError(3,0.01,0.01,0.03608211,0.03608211);
   grae->SetPoint(4,100,0.6993539);
   grae->SetPointError(4,0.01,0.01,0.06128509,0.06128509);
   grae->SetPoint(5,160,0.8529412);
   grae->SetPointError(5,0.01,0.01,0.1583872,0.1583872);
   
   TH1F *Graph_gr_cent36 = new TH1F("Graph_gr_cent36","",100,0,176.011);
   Graph_gr_cent36->SetMinimum(0);
   Graph_gr_cent36->SetMaximum(1.112461);
   Graph_gr_cent36->SetDirectory(0);
   Graph_gr_cent36->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gr_cent36->SetLineColor(ci);
   Graph_gr_cent36->GetXaxis()->SetLabelFont(42);
   Graph_gr_cent36->GetXaxis()->SetLabelSize(0.035);
   Graph_gr_cent36->GetXaxis()->SetTitleSize(0.035);
   Graph_gr_cent36->GetXaxis()->SetTitleFont(42);
   Graph_gr_cent36->GetYaxis()->SetLabelFont(42);
   Graph_gr_cent36->GetYaxis()->SetLabelSize(0.035);
   Graph_gr_cent36->GetYaxis()->SetTitleSize(0.035);
   Graph_gr_cent36->GetYaxis()->SetTitleFont(42);
   Graph_gr_cent36->GetZaxis()->SetLabelFont(42);
   Graph_gr_cent36->GetZaxis()->SetLabelSize(0.035);
   Graph_gr_cent36->GetZaxis()->SetTitleSize(0.035);
   Graph_gr_cent36->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_gr_cent36);
   
   grae->Draw(" p");
   line = new TLine(30,1,200,1);
   line->SetLineStyle(7);
   line->Draw();
   c2_2->Modified();
   c2->cd();
   c2->Modified();
   c2->cd();
   c2->SetSelected(c2);
}
