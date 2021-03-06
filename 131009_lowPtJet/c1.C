{
//=========Macro generated from canvas: c1/c1
//=========  (Fri Oct 11 10:19:55 2013) by ROOT version5.34/02
   TCanvas *c1 = new TCanvas("c1", "c1",124,349,900,600);
   gStyle->SetOptStat(0);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: c1_1
   TPad *c1_1 = new TPad("c1_1", "c1_1",0.01,0.51,0.3233333,0.99);
   c1_1->Draw();
   c1_1->cd();
   c1_1->Range(-0.3125,-0.4366337,2.8125,3.929703);
   c1_1->SetFillColor(0);
   c1_1->SetBorderMode(0);
   c1_1->SetBorderSize(2);
   c1_1->SetFrameBorderMode(0);
   c1_1->SetFrameBorderMode(0);
   
   TH1D *trackMax_0 = new TH1D("trackMax_0","",15,0,2.5);
   trackMax_0->SetBinContent(1,1.722772);
   trackMax_0->SetBinContent(2,2.910891);
   trackMax_0->SetBinContent(3,1.188119);
   trackMax_0->SetBinContent(4,0.1188119);
   trackMax_0->SetBinContent(5,0.05940594);
   trackMax_0->SetBinError(1,0.3199108);
   trackMax_0->SetBinError(2,0.4158416);
   trackMax_0->SetBinError(3,0.2656714);
   trackMax_0->SetBinError(4,0.08401269);
   trackMax_0->SetBinError(5,0.05940594);
   trackMax_0->SetEntries(101);
   trackMax_0->SetStats(0);
   trackMax_0->SetLineColor(2);
   trackMax_0->GetXaxis()->SetTitle("trackMax/jetpt ");
   trackMax_0->GetXaxis()->CenterTitle(true);
   trackMax_0->GetXaxis()->SetLabelFont(42);
   trackMax_0->GetXaxis()->SetLabelSize(0.035);
   trackMax_0->GetXaxis()->SetTitleSize(0.05);
   trackMax_0->GetXaxis()->SetTitleFont(42);
   trackMax_0->GetYaxis()->SetTitle(" Normalized Entires ");
   trackMax_0->GetYaxis()->SetLabelFont(42);
   trackMax_0->GetYaxis()->SetLabelSize(0.035);
   trackMax_0->GetYaxis()->SetTitleSize(0.05);
   trackMax_0->GetYaxis()->SetTitleOffset(0.8);
   trackMax_0->GetYaxis()->SetTitleFont(42);
   trackMax_0->GetZaxis()->SetLabelFont(42);
   trackMax_0->GetZaxis()->SetLabelSize(0.035);
   trackMax_0->GetZaxis()->SetTitleSize(0.035);
   trackMax_0->GetZaxis()->SetTitleFont(42);
   trackMax_0->Draw("e");
   
   TH1D *trackMax_1 = new TH1D("trackMax_1","",15,0,2.5);
   trackMax_1->SetBinContent(1,1.33138);
   trackMax_1->SetBinContent(2,3.04983);
   trackMax_1->SetBinContent(3,1.179123);
   trackMax_1->SetBinContent(4,0.34401);
   trackMax_1->SetBinContent(5,0.06029419);
   trackMax_1->SetBinContent(6,0.006526467);
   trackMax_1->SetBinContent(7,0.01365786);
   trackMax_1->SetBinContent(8,0.004326127);
   trackMax_1->SetBinContent(9,0.009752424);
   trackMax_1->SetBinContent(13,0.00110017);
   trackMax_1->SetBinContent(16,0.004326127);
   trackMax_1->SetBinError(1,0.1126566);
   trackMax_1->SetBinError(2,0.166107);
   trackMax_1->SetBinError(3,0.1036334);
   trackMax_1->SetBinError(4,0.05977688);
   trackMax_1->SetBinError(5,0.01906431);
   trackMax_1->SetBinError(6,0.004597404);
   trackMax_1->SetBinError(7,0.01365786);
   trackMax_1->SetBinError(8,0.004326127);
   trackMax_1->SetBinError(9,0.006216199);
   trackMax_1->SetBinError(13,0.00110017);
   trackMax_1->SetBinError(16,0.004326127);
   trackMax_1->SetEntries(161.4118);
   trackMax_1->SetStats(0);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   trackMax_1->SetLineColor(ci);
   trackMax_1->GetXaxis()->SetTitle("trackMax/jetpt ");
   trackMax_1->GetXaxis()->CenterTitle(true);
   trackMax_1->GetXaxis()->SetLabelFont(42);
   trackMax_1->GetXaxis()->SetLabelSize(0.035);
   trackMax_1->GetXaxis()->SetTitleSize(0.05);
   trackMax_1->GetXaxis()->SetTitleFont(42);
   trackMax_1->GetYaxis()->SetTitle(" Normalized Entires ");
   trackMax_1->GetYaxis()->SetLabelFont(42);
   trackMax_1->GetYaxis()->SetLabelSize(0.035);
   trackMax_1->GetYaxis()->SetTitleSize(0.05);
   trackMax_1->GetYaxis()->SetTitleOffset(0.8);
   trackMax_1->GetYaxis()->SetTitleFont(42);
   trackMax_1->GetZaxis()->SetLabelFont(42);
   trackMax_1->GetZaxis()->SetLabelSize(0.035);
   trackMax_1->GetZaxis()->SetTitleSize(0.035);
   trackMax_1->GetZaxis()->SetTitleFont(42);
   trackMax_1->Draw("same hist");
   
   TLegend *leg = new TLegend(0.5103716,0.4935144,0.832632,0.6967312,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("trackMax_0","DATA","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(2);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("trackSum_1","MC","lpf");
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   leg->Draw();
   c1_1->Modified();
   c1->cd();
  
// ------------>Primitives in pad: c1_2
   c1_2 = new TPad("c1_2", "c1_2",0.3433333,0.51,0.6566667,0.99);
   c1_2->Draw();
   c1_2->cd();
   c1_2->Range(-0.2819259,-0.5858662,2.837481,6.039151);
   c1_2->SetFillColor(0);
   c1_2->SetBorderMode(0);
   c1_2->SetBorderSize(2);
   c1_2->SetTopMargin(0.1139277);
   c1_2->SetBottomMargin(0.0884324);
   c1_2->SetFrameBorderMode(0);
   c1_2->SetFrameBorderMode(0);
   
   TH1D *photonMax_0 = new TH1D("photonMax_0","",15,0,2.5);
   photonMax_0->SetBinContent(1,4.514851);
   photonMax_0->SetBinContent(2,0.950495);
   photonMax_0->SetBinContent(3,0.3564356);
   photonMax_0->SetBinContent(4,0.1188119);
   photonMax_0->SetBinContent(5,0.05940594);
   photonMax_0->SetBinError(1,0.517889);
   photonMax_0->SetBinError(2,0.2376238);
   photonMax_0->SetBinError(3,0.1455142);
   photonMax_0->SetBinError(4,0.08401269);
   photonMax_0->SetBinError(5,0.05940594);
   photonMax_0->SetEntries(101);
   photonMax_0->SetStats(0);
   photonMax_0->SetLineColor(2);
   photonMax_0->GetXaxis()->SetTitle("photonMax/jetpt ");
   photonMax_0->GetXaxis()->CenterTitle(true);
   photonMax_0->GetXaxis()->SetLabelFont(42);
   photonMax_0->GetXaxis()->SetLabelSize(0.035);
   photonMax_0->GetXaxis()->SetTitleSize(0.05);
   photonMax_0->GetXaxis()->SetTitleFont(42);
   photonMax_0->GetYaxis()->SetTitle(" Normalized Entries ");
   photonMax_0->GetYaxis()->SetLabelFont(42);
   photonMax_0->GetYaxis()->SetLabelSize(0.035);
   photonMax_0->GetYaxis()->SetTitleSize(0.05);
   photonMax_0->GetYaxis()->SetTitleOffset(0.8);
   photonMax_0->GetYaxis()->SetTitleFont(42);
   photonMax_0->GetZaxis()->SetLabelFont(42);
   photonMax_0->GetZaxis()->SetLabelSize(0.035);
   photonMax_0->GetZaxis()->SetTitleSize(0.035);
   photonMax_0->GetZaxis()->SetTitleFont(42);
   photonMax_0->Draw("e");
   
   TH1D *photonMax_1 = new TH1D("photonMax_1","",15,0,2.5);
   photonMax_1->SetBinContent(1,4.581366);
   photonMax_1->SetBinContent(2,1.061408);
   photonMax_1->SetBinContent(3,0.2776463);
   photonMax_1->SetBinContent(4,0.03389229);
   photonMax_1->SetBinContent(5,0.02229403);
   photonMax_1->SetBinContent(6,0.02229403);
   photonMax_1->SetBinContent(8,0.001099377);
   photonMax_1->SetBinError(1,0.2031395);
   photonMax_1->SetBinError(2,0.1020687);
   photonMax_1->SetBinError(3,0.05150784);
   photonMax_1->SetBinError(4,0.01948816);
   photonMax_1->SetBinError(5,0.01495477);
   photonMax_1->SetBinError(6,0.01495477);
   photonMax_1->SetBinError(8,0.001099377);
   photonMax_1->SetEntries(161.4118);
   photonMax_1->SetStats(0);

   ci = TColor::GetColor("#000099");
   photonMax_1->SetLineColor(ci);
   photonMax_1->GetXaxis()->SetTitle("photonMax/jetpt ");
   photonMax_1->GetXaxis()->CenterTitle(true);
   photonMax_1->GetXaxis()->SetLabelFont(42);
   photonMax_1->GetXaxis()->SetLabelSize(0.035);
   photonMax_1->GetXaxis()->SetTitleSize(0.05);
   photonMax_1->GetXaxis()->SetTitleFont(42);
   photonMax_1->GetYaxis()->SetTitle(" Normalized Entries ");
   photonMax_1->GetYaxis()->SetLabelFont(42);
   photonMax_1->GetYaxis()->SetLabelSize(0.035);
   photonMax_1->GetYaxis()->SetTitleSize(0.05);
   photonMax_1->GetYaxis()->SetTitleOffset(0.8);
   photonMax_1->GetYaxis()->SetTitleFont(42);
   photonMax_1->GetZaxis()->SetLabelFont(42);
   photonMax_1->GetZaxis()->SetLabelSize(0.035);
   photonMax_1->GetZaxis()->SetTitleSize(0.035);
   photonMax_1->GetZaxis()->SetTitleFont(42);
   photonMax_1->Draw("same hist");
   
   leg = new TLegend(0.193674,0.5364219,0.9915464,0.7877331,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   entry=leg->AddEntry("NULL","30 < p_{T}^{Jet} < 40  ,  80 < p_{T}^{#gamma} < 9999","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   c1_2->Modified();
   c1->cd();
  
// ------------>Primitives in pad: c1_3
   c1_3 = new TPad("c1_3", "c1_3",0.6766667,0.51,0.99,0.99);
   c1_3->Draw();
   c1_3->cd();
   c1_3->Range(-0.3125,-0.7674927,2.8125,6.907434);
   c1_3->SetFillColor(0);
   c1_3->SetBorderMode(0);
   c1_3->SetBorderSize(2);
   c1_3->SetFrameBorderMode(0);
   c1_3->SetFrameBorderMode(0);
   
   TH1D *neutralMax_0 = new TH1D("neutralMax_0","",15,0,2.5);
   neutralMax_0->SetBinContent(1,5.287129);
   neutralMax_0->SetBinContent(2,0.5940594);
   neutralMax_0->SetBinContent(3,0.05940594);
   neutralMax_0->SetBinContent(4,0.05940594);
   neutralMax_0->SetBinError(1,0.5604345);
   neutralMax_0->SetBinError(2,0.1878581);
   neutralMax_0->SetBinError(3,0.05940594);
   neutralMax_0->SetBinError(4,0.05940594);
   neutralMax_0->SetEntries(101);
   neutralMax_0->SetStats(0);
   neutralMax_0->SetLineColor(2);
   neutralMax_0->GetXaxis()->SetTitle("neutralMax/jetpt ");
   neutralMax_0->GetXaxis()->CenterTitle(true);
   neutralMax_0->GetXaxis()->SetLabelFont(42);
   neutralMax_0->GetXaxis()->SetLabelSize(0.035);
   neutralMax_0->GetXaxis()->SetTitleSize(0.05);
   neutralMax_0->GetXaxis()->SetTitleFont(42);
   neutralMax_0->GetYaxis()->SetTitle(" Normalized Entries ");
   neutralMax_0->GetYaxis()->SetLabelFont(42);
   neutralMax_0->GetYaxis()->SetLabelSize(0.035);
   neutralMax_0->GetYaxis()->SetTitleSize(0.05);
   neutralMax_0->GetYaxis()->SetTitleOffset(0.8);
   neutralMax_0->GetYaxis()->SetTitleFont(42);
   neutralMax_0->GetZaxis()->SetLabelFont(42);
   neutralMax_0->GetZaxis()->SetLabelSize(0.035);
   neutralMax_0->GetZaxis()->SetTitleSize(0.035);
   neutralMax_0->GetZaxis()->SetTitleFont(42);
   neutralMax_0->Draw("e");
   
   TH1D *neutralMax_1 = new TH1D("neutralMax_1","",15,0,2.5);
   neutralMax_1->SetBinContent(1,5.41633);
   neutralMax_1->SetBinContent(2,0.4671585);
   neutralMax_1->SetBinContent(3,0.07787588);
   neutralMax_1->SetBinContent(4,0.03211393);
   neutralMax_1->SetBinContent(5,0.005422387);
   neutralMax_1->SetBinContent(6,0.001099377);
   neutralMax_1->SetBinError(1,0.2253037);
   neutralMax_1->SetBinError(2,0.05874301);
   neutralMax_1->SetBinError(3,0.02613468);
   neutralMax_1->SetBinError(4,0.01575997);
   neutralMax_1->SetBinError(5,0.004460611);
   neutralMax_1->SetBinError(6,0.001099377);
   neutralMax_1->SetEntries(161.4118);
   neutralMax_1->SetStats(0);

   ci = TColor::GetColor("#000099");
   neutralMax_1->SetLineColor(ci);
   neutralMax_1->GetXaxis()->SetTitle("neutralMax/jetpt ");
   neutralMax_1->GetXaxis()->CenterTitle(true);
   neutralMax_1->GetXaxis()->SetLabelFont(42);
   neutralMax_1->GetXaxis()->SetLabelSize(0.035);
   neutralMax_1->GetXaxis()->SetTitleSize(0.05);
   neutralMax_1->GetXaxis()->SetTitleFont(42);
   neutralMax_1->GetYaxis()->SetTitle(" Normalized Entries ");
   neutralMax_1->GetYaxis()->SetLabelFont(42);
   neutralMax_1->GetYaxis()->SetLabelSize(0.035);
   neutralMax_1->GetYaxis()->SetTitleSize(0.05);
   neutralMax_1->GetYaxis()->SetTitleOffset(0.8);
   neutralMax_1->GetYaxis()->SetTitleFont(42);
   neutralMax_1->GetZaxis()->SetLabelFont(42);
   neutralMax_1->GetZaxis()->SetLabelSize(0.035);
   neutralMax_1->GetZaxis()->SetTitleSize(0.035);
   neutralMax_1->GetZaxis()->SetTitleFont(42);
   neutralMax_1->Draw("same hist");
   c1_3->Modified();
   c1->cd();
  
// ------------>Primitives in pad: c1_4
   c1_4 = new TPad("c1_4", "c1_4",0.01,0.01,0.3233333,0.49);
   c1_4->Draw();
   c1_4->cd();
   c1_4->Range(-0.3125,-0.276617,2.8125,2.489553);
   c1_4->SetFillColor(0);
   c1_4->SetBorderMode(0);
   c1_4->SetBorderSize(2);
   c1_4->SetFrameBorderMode(0);
   c1_4->SetFrameBorderMode(0);
   
   TH1D *trackSum_0 = new TH1D("trackSum_0","",15,0,2.5);
   trackSum_0->SetBinContent(1,0.1188119);
   trackSum_0->SetBinContent(2,0.8316832);
   trackSum_0->SetBinContent(3,0.8910891);
   trackSum_0->SetBinContent(4,1.366337);
   trackSum_0->SetBinContent(5,1.782178);
   trackSum_0->SetBinContent(6,0.7128713);
   trackSum_0->SetBinContent(7,0.1782178);
   trackSum_0->SetBinContent(8,0.1188119);
   trackSum_0->SetBinError(1,0.08401269);
   trackSum_0->SetBinError(2,0.2222767);
   trackSum_0->SetBinError(3,0.2300782);
   trackSum_0->SetBinError(4,0.2849009);
   trackSum_0->SetBinError(5,0.3253797);
   trackSum_0->SetBinError(6,0.2057882);
   trackSum_0->SetBinError(7,0.1028941);
   trackSum_0->SetBinError(8,0.08401269);
   trackSum_0->SetEntries(101);
   trackSum_0->SetStats(0);
   trackSum_0->SetLineColor(2);
   trackSum_0->GetXaxis()->SetTitle("trackSum/jetpt ");
   trackSum_0->GetXaxis()->CenterTitle(true);
   trackSum_0->GetXaxis()->SetLabelFont(42);
   trackSum_0->GetXaxis()->SetLabelSize(0.035);
   trackSum_0->GetXaxis()->SetTitleSize(0.05);
   trackSum_0->GetXaxis()->SetTitleFont(42);
   trackSum_0->GetYaxis()->SetTitle(" Normalized Entires ");
   trackSum_0->GetYaxis()->SetLabelFont(42);
   trackSum_0->GetYaxis()->SetLabelSize(0.035);
   trackSum_0->GetYaxis()->SetTitleSize(0.05);
   trackSum_0->GetYaxis()->SetTitleOffset(0.8);
   trackSum_0->GetYaxis()->SetTitleFont(42);
   trackSum_0->GetZaxis()->SetLabelFont(42);
   trackSum_0->GetZaxis()->SetLabelSize(0.035);
   trackSum_0->GetZaxis()->SetTitleSize(0.035);
   trackSum_0->GetZaxis()->SetTitleFont(42);
   trackSum_0->Draw("e");
   
   TH1D *trackSum_1 = new TH1D("trackSum_1","",15,0,2.5);
   trackSum_1->SetBinContent(1,0.08434032);
   trackSum_1->SetBinContent(2,0.3526425);
   trackSum_1->SetBinContent(3,0.7458741);
   trackSum_1->SetBinContent(4,1.547375);
   trackSum_1->SetBinContent(5,2.016743);
   trackSum_1->SetBinContent(6,0.9283796);
   trackSum_1->SetBinContent(7,0.1697109);
   trackSum_1->SetBinContent(8,0.06054005);
   trackSum_1->SetBinContent(9,0.03112288);
   trackSum_1->SetBinContent(10,0.03435002);
   trackSum_1->SetBinContent(11,0.01696459);
   trackSum_1->SetBinContent(12,0.006528861);
   trackSum_1->SetBinContent(14,0.005428288);
   trackSum_1->SetBinContent(16,0.006528861);
   trackSum_1->SetBinError(1,0.02708189);
   trackSum_1->SetBinError(2,0.06034173);
   trackSum_1->SetBinError(3,0.07985519);
   trackSum_1->SetBinError(4,0.1255675);
   trackSum_1->SetBinError(5,0.1385647);
   trackSum_1->SetBinError(6,0.08741479);
   trackSum_1->SetBinError(7,0.02941497);
   trackSum_1->SetBinError(8,0.0179461);
   trackSum_1->SetBinError(9,0.01529125);
   trackSum_1->SetBinError(10,0.01585371);
   trackSum_1->SetBinError(11,0.01379521);
   trackSum_1->SetBinError(12,0.004599091);
   trackSum_1->SetBinError(14,0.004465464);
   trackSum_1->SetBinError(16,0.004599091);
   trackSum_1->SetEntries(161.4118);
   trackSum_1->SetStats(0);

   ci = TColor::GetColor("#000099");
   trackSum_1->SetLineColor(ci);
   trackSum_1->GetXaxis()->SetTitle("trackSum/jetpt ");
   trackSum_1->GetXaxis()->CenterTitle(true);
   trackSum_1->GetXaxis()->SetLabelFont(42);
   trackSum_1->GetXaxis()->SetLabelSize(0.035);
   trackSum_1->GetXaxis()->SetTitleSize(0.05);
   trackSum_1->GetXaxis()->SetTitleFont(42);
   trackSum_1->GetYaxis()->SetTitle(" Normalized Entires ");
   trackSum_1->GetYaxis()->SetLabelFont(42);
   trackSum_1->GetYaxis()->SetLabelSize(0.035);
   trackSum_1->GetYaxis()->SetTitleSize(0.05);
   trackSum_1->GetYaxis()->SetTitleOffset(0.8);
   trackSum_1->GetYaxis()->SetTitleFont(42);
   trackSum_1->GetZaxis()->SetLabelFont(42);
   trackSum_1->GetZaxis()->SetLabelSize(0.035);
   trackSum_1->GetZaxis()->SetTitleSize(0.035);
   trackSum_1->GetZaxis()->SetTitleFont(42);
   trackSum_1->Draw("same hist");
   c1_4->Modified();
   c1->cd();
  
// ------------>Primitives in pad: c1_5
   c1_5 = new TPad("c1_5", "c1_5",0.3433333,0.01,0.6566667,0.49);
   c1_5->Draw();
   c1_5->cd();
   c1_5->Range(-0.3125,-0.3359176,2.8125,3.023258);
   c1_5->SetFillColor(0);
   c1_5->SetBorderMode(0);
   c1_5->SetBorderSize(2);
   c1_5->SetFrameBorderMode(0);
   c1_5->SetFrameBorderMode(0);
   
   TH1D *photonSum_0 = new TH1D("photonSum_0","",15,0,2.5);
   photonSum_0->SetBinContent(1,1.841584);
   photonSum_0->SetBinContent(2,2.19802);
   photonSum_0->SetBinContent(3,0.950495);
   photonSum_0->SetBinContent(4,0.8316832);
   photonSum_0->SetBinContent(5,0.1782178);
   photonSum_0->SetBinError(1,0.3307583);
   photonSum_0->SetBinError(2,0.3613522);
   photonSum_0->SetBinError(3,0.2376238);
   photonSum_0->SetBinError(4,0.2222767);
   photonSum_0->SetBinError(5,0.1028941);
   photonSum_0->SetEntries(101);
   photonSum_0->SetStats(0);
   photonSum_0->SetLineColor(2);
   photonSum_0->GetXaxis()->SetTitle("photonSum/jetpt ");
   photonSum_0->GetXaxis()->CenterTitle(true);
   photonSum_0->GetXaxis()->SetLabelFont(42);
   photonSum_0->GetXaxis()->SetLabelSize(0.035);
   photonSum_0->GetXaxis()->SetTitleSize(0.05);
   photonSum_0->GetXaxis()->SetTitleFont(42);
   photonSum_0->GetYaxis()->SetTitle(" Normalized Entries ");
   photonSum_0->GetYaxis()->SetLabelFont(42);
   photonSum_0->GetYaxis()->SetLabelSize(0.035);
   photonSum_0->GetYaxis()->SetTitleSize(0.05);
   photonSum_0->GetYaxis()->SetTitleOffset(0.8);
   photonSum_0->GetYaxis()->SetTitleFont(42);
   photonSum_0->GetZaxis()->SetLabelFont(42);
   photonSum_0->GetZaxis()->SetLabelSize(0.035);
   photonSum_0->GetZaxis()->SetTitleSize(0.035);
   photonSum_0->GetZaxis()->SetTitleFont(42);
   photonSum_0->Draw("e");
   
   TH1D *photonSum_1 = new TH1D("photonSum_1","",15,0,2.5);
   photonSum_1->SetBinContent(1,1.913967);
   photonSum_1->SetBinContent(2,2.076719);
   photonSum_1->SetBinContent(3,1.349416);
   photonSum_1->SetBinContent(4,0.43332);
   photonSum_1->SetBinContent(5,0.1671571);
   photonSum_1->SetBinContent(6,0.05722169);
   photonSum_1->SetBinContent(7,0.002199157);
   photonSum_1->SetBinContent(16,0.001099579);
   photonSum_1->SetBinError(1,0.1278039);
   photonSum_1->SetBinError(2,0.1357369);
   photonSum_1->SetBinError(3,0.1201953);
   photonSum_1->SetBinError(4,0.06158986);
   photonSum_1->SetBinError(5,0.03955151);
   photonSum_1->SetBinError(6,0.02487414);
   photonSum_1->SetBinError(7,0.001555039);
   photonSum_1->SetBinError(16,0.001099579);
   photonSum_1->SetEntries(161.4118);
   photonSum_1->SetStats(0);

   ci = TColor::GetColor("#000099");
   photonSum_1->SetLineColor(ci);
   photonSum_1->GetXaxis()->SetTitle("photonSum/jetpt ");
   photonSum_1->GetXaxis()->CenterTitle(true);
   photonSum_1->GetXaxis()->SetLabelFont(42);
   photonSum_1->GetXaxis()->SetLabelSize(0.035);
   photonSum_1->GetXaxis()->SetTitleSize(0.05);
   photonSum_1->GetXaxis()->SetTitleFont(42);
   photonSum_1->GetYaxis()->SetTitle(" Normalized Entries ");
   photonSum_1->GetYaxis()->SetLabelFont(42);
   photonSum_1->GetYaxis()->SetLabelSize(0.035);
   photonSum_1->GetYaxis()->SetTitleSize(0.05);
   photonSum_1->GetYaxis()->SetTitleOffset(0.8);
   photonSum_1->GetYaxis()->SetTitleFont(42);
   photonSum_1->GetZaxis()->SetLabelFont(42);
   photonSum_1->GetZaxis()->SetLabelSize(0.035);
   photonSum_1->GetZaxis()->SetTitleSize(0.035);
   photonSum_1->GetZaxis()->SetTitleFont(42);
   photonSum_1->Draw("same hist");
   c1_5->Modified();
   c1->cd();
  
// ------------>Primitives in pad: c1_6
   c1_6 = new TPad("c1_6", "c1_6",0.6766667,0.01,0.99,0.49);
   c1_6->Draw();
   c1_6->cd();
   c1_6->Range(-0.3125,-0.7017327,2.8125,6.315594);
   c1_6->SetFillColor(0);
   c1_6->SetBorderMode(0);
   c1_6->SetBorderSize(2);
   c1_6->SetFrameBorderMode(0);
   c1_6->SetFrameBorderMode(0);
   
   TH1D *neutralSum_0 = new TH1D("neutralSum_0","",15,0,2.5);
   neutralSum_0->SetBinContent(1,4.811881);
   neutralSum_0->SetBinContent(2,0.8316832);
   neutralSum_0->SetBinContent(3,0.2376238);
   neutralSum_0->SetBinContent(4,0.05940594);
   neutralSum_0->SetBinContent(5,0.05940594);
   neutralSum_0->SetBinError(1,0.5346535);
   neutralSum_0->SetBinError(2,0.2222767);
   neutralSum_0->SetBinError(3,0.1188119);
   neutralSum_0->SetBinError(4,0.05940594);
   neutralSum_0->SetBinError(5,0.05940594);
   neutralSum_0->SetEntries(101);
   neutralSum_0->SetStats(0);
   neutralSum_0->SetLineColor(2);
   neutralSum_0->GetXaxis()->SetTitle("neutralSum/jetpt ");
   neutralSum_0->GetXaxis()->CenterTitle(true);
   neutralSum_0->GetXaxis()->SetLabelFont(42);
   neutralSum_0->GetXaxis()->SetLabelSize(0.035);
   neutralSum_0->GetXaxis()->SetTitleSize(0.05);
   neutralSum_0->GetXaxis()->SetTitleFont(42);
   neutralSum_0->GetYaxis()->SetTitle(" Normalized Entries ");
   neutralSum_0->GetYaxis()->SetLabelFont(42);
   neutralSum_0->GetYaxis()->SetLabelSize(0.035);
   neutralSum_0->GetYaxis()->SetTitleSize(0.05);
   neutralSum_0->GetYaxis()->SetTitleOffset(0.8);
   neutralSum_0->GetYaxis()->SetTitleFont(42);
   neutralSum_0->GetZaxis()->SetLabelFont(42);
   neutralSum_0->GetZaxis()->SetLabelSize(0.035);
   neutralSum_0->GetZaxis()->SetTitleSize(0.035);
   neutralSum_0->GetZaxis()->SetTitleFont(42);
   neutralSum_0->Draw("e");
   
   TH1D *neutralSum_1 = new TH1D("neutralSum_1","",15,0,2.5);
   neutralSum_1->SetBinContent(1,5.001766);
   neutralSum_1->SetBinContent(2,0.7637656);
   neutralSum_1->SetBinContent(3,0.1643978);
   neutralSum_1->SetBinContent(4,0.05915137);
   neutralSum_1->SetBinContent(5,0.008720519);
   neutralSum_1->SetBinContent(6,0.002198754);
   neutralSum_1->SetBinError(1,0.2176026);
   neutralSum_1->SetBinError(2,0.07760837);
   neutralSum_1->SetBinError(3,0.03746225);
   neutralSum_1->SetBinError(4,0.01901883);
   neutralSum_1->SetBinError(5,0.004850045);
   neutralSum_1->SetBinError(6,0.001554754);
   neutralSum_1->SetEntries(161.4118);
   neutralSum_1->SetStats(0);

   ci = TColor::GetColor("#000099");
   neutralSum_1->SetLineColor(ci);
   neutralSum_1->GetXaxis()->SetTitle("neutralSum/jetpt ");
   neutralSum_1->GetXaxis()->CenterTitle(true);
   neutralSum_1->GetXaxis()->SetLabelFont(42);
   neutralSum_1->GetXaxis()->SetLabelSize(0.035);
   neutralSum_1->GetXaxis()->SetTitleSize(0.05);
   neutralSum_1->GetXaxis()->SetTitleFont(42);
   neutralSum_1->GetYaxis()->SetTitle(" Normalized Entries ");
   neutralSum_1->GetYaxis()->SetLabelFont(42);
   neutralSum_1->GetYaxis()->SetLabelSize(0.035);
   neutralSum_1->GetYaxis()->SetTitleSize(0.05);
   neutralSum_1->GetYaxis()->SetTitleOffset(0.8);
   neutralSum_1->GetYaxis()->SetTitleFont(42);
   neutralSum_1->GetZaxis()->SetLabelFont(42);
   neutralSum_1->GetZaxis()->SetLabelSize(0.035);
   neutralSum_1->GetZaxis()->SetTitleSize(0.035);
   neutralSum_1->GetZaxis()->SetTitleFont(42);
   neutralSum_1->Draw("same hist");
   c1_6->Modified();
   c1->cd();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
