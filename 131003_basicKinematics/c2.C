{
//=========Macro generated from canvas: c2/c2
//=========  (Fri Oct  4 06:45:05 2013) by ROOT version5.34/02
   TCanvas *c2 = new TCanvas("c2", "c2",0,44,1440,500);
   gStyle->SetOptStat(0);
   c2->Range(0,0,1,1);
   c2->SetFillColor(0);
   c2->SetBorderMode(0);
   c2->SetBorderSize(2);
   c2->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: c2_1
   TPad *c2_1 = new TPad("c2_1", "c2_1",0.01,0.01,0.3233333,0.99);
   c2_1->Draw();
   c2_1->cd();
   c2_1->Range(-17.5,-0.009903809,157.5,0.08913428);
   c2_1->SetFillColor(0);
   c2_1->SetBorderMode(0);
   c2_1->SetBorderSize(2);
   c2_1->SetFrameBorderMode(0);
   c2_1->SetFrameBorderMode(0);
   
   TH1D *jetPt_0 = new TH1D("jetPt_0","",28,0,140);
   jetPt_0->SetBinContent(7,0.07430512);
   jetPt_0->SetBinContent(8,0.03551703);
   jetPt_0->SetBinContent(9,0.02134239);
   jetPt_0->SetBinContent(10,0.01492537);
   jetPt_0->SetBinContent(11,0.0115828);
   jetPt_0->SetBinContent(12,0.009580838);
   jetPt_0->SetBinContent(13,0.007275002);
   jetPt_0->SetBinContent(14,0.00532666);
   jetPt_0->SetBinContent(15,0.004683171);
   jetPt_0->SetBinContent(16,0.003324694);
   jetPt_0->SetBinContent(17,0.002806328);
   jetPt_0->SetBinContent(18,0.002144964);
   jetPt_0->SetBinContent(19,0.001680222);
   jetPt_0->SetBinContent(20,0.001000983);
   jetPt_0->SetBinContent(21,0.001143981);
   jetPt_0->SetBinContent(22,0.0008937349);
   jetPt_0->SetBinContent(23,0.0006613638);
   jetPt_0->SetBinContent(24,0.0005004916);
   jetPt_0->SetBinContent(25,0.0003396193);
   jetPt_0->SetBinContent(26,0.000357494);
   jetPt_0->SetBinContent(27,0.0003038699);
   jetPt_0->SetBinContent(28,0.0003038699);
   jetPt_0->SetBinContent(29,0.001519349);
   jetPt_0->SetBinError(7,0.001152468);
   jetPt_0->SetBinError(8,0.0007967786);
   jetPt_0->SetBinError(9,0.0006176478);
   jetPt_0->SetBinError(10,0.0005165138);
   jetPt_0->SetBinError(11,0.0004550155);
   jetPt_0->SetBinError(12,0.0004138292);
   jetPt_0->SetBinError(13,0.0003606085);
   jetPt_0->SetBinError(14,0.0003085651);
   jetPt_0->SetBinError(15,0.0002893273);
   jetPt_0->SetBinError(16,0.0002437784);
   jetPt_0->SetBinError(17,0.0002239693);
   jetPt_0->SetBinError(18,0.0001958075);
   jetPt_0->SetBinError(19,0.0001733016);
   jetPt_0->SetBinError(20,0.000133762);
   jetPt_0->SetBinError(21,0.0001429976);
   jetPt_0->SetBinError(22,0.0001263932);
   jetPt_0->SetBinError(23,0.0001087275);
   jetPt_0->SetBinError(24,9.458401e-05);
   jetPt_0->SetBinError(25,7.7914e-05);
   jetPt_0->SetBinError(26,7.993808e-05);
   jetPt_0->SetBinError(27,7.369927e-05);
   jetPt_0->SetBinError(28,7.369927e-05);
   jetPt_0->SetBinError(29,0.0001647966);
   jetPt_0->SetEntries(11274);
   jetPt_0->SetStats(0);
   jetPt_0->SetLineColor(2);
   jetPt_0->GetXaxis()->SetTitle("p_{T}^{Jet} ");
   jetPt_0->GetXaxis()->CenterTitle(true);
   jetPt_0->GetXaxis()->SetLabelFont(42);
   jetPt_0->GetXaxis()->SetLabelSize(0.035);
   jetPt_0->GetXaxis()->SetTitleSize(0.035);
   jetPt_0->GetXaxis()->SetTitleFont(42);
   jetPt_0->GetYaxis()->SetTitle(" Normalized Entires ");
   jetPt_0->GetYaxis()->SetLabelFont(42);
   jetPt_0->GetYaxis()->SetLabelSize(0.035);
   jetPt_0->GetYaxis()->SetTitleSize(0.035);
   jetPt_0->GetYaxis()->SetTitleOffset(1.19);
   jetPt_0->GetYaxis()->SetTitleFont(42);
   jetPt_0->GetZaxis()->SetLabelFont(42);
   jetPt_0->GetZaxis()->SetLabelSize(0.035);
   jetPt_0->GetZaxis()->SetTitleSize(0.035);
   jetPt_0->GetZaxis()->SetTitleFont(42);
   jetPt_0->Draw("e");
   
   TH1D *jetPt_1 = new TH1D("jetPt_1","",28,0,140);
   jetPt_1->SetBinContent(7,0.04042173);
   jetPt_1->SetBinContent(8,0.0313853);
   jetPt_1->SetBinContent(9,0.02679816);
   jetPt_1->SetBinContent(10,0.02270393);
   jetPt_1->SetBinContent(11,0.01796666);
   jetPt_1->SetBinContent(12,0.0137383);
   jetPt_1->SetBinContent(13,0.01052933);
   jetPt_1->SetBinContent(14,0.008057255);
   jetPt_1->SetBinContent(15,0.005906475);
   jetPt_1->SetBinContent(16,0.004821629);
   jetPt_1->SetBinContent(17,0.003837323);
   jetPt_1->SetBinContent(18,0.003008605);
   jetPt_1->SetBinContent(19,0.002408373);
   jetPt_1->SetBinContent(20,0.001861046);
   jetPt_1->SetBinContent(21,0.001491909);
   jetPt_1->SetBinContent(22,0.001218535);
   jetPt_1->SetBinContent(23,0.000977735);
   jetPt_1->SetBinContent(24,0.0008589842);
   jetPt_1->SetBinContent(25,0.0006691069);
   jetPt_1->SetBinContent(26,0.0005582464);
   jetPt_1->SetBinContent(27,0.0004188233);
   jetPt_1->SetBinContent(28,0.0003625403);
   jetPt_1->SetBinContent(29,0.002089684);
   jetPt_1->SetBinError(7,0.0004833797);
   jetPt_1->SetBinError(8,0.0004297425);
   jetPt_1->SetBinError(9,0.0003926409);
   jetPt_1->SetBinError(10,0.0003453586);
   jetPt_1->SetBinError(11,0.0002898541);
   jetPt_1->SetBinError(12,0.0002327985);
   jetPt_1->SetBinError(13,0.0001943003);
   jetPt_1->SetBinError(14,0.0001604282);
   jetPt_1->SetBinError(15,0.0001265377);
   jetPt_1->SetBinError(16,0.0001091635);
   jetPt_1->SetBinError(17,9.327041e-05);
   jetPt_1->SetBinError(18,7.776614e-05);
   jetPt_1->SetBinError(19,6.615726e-05);
   jetPt_1->SetBinError(20,5.306616e-05);
   jetPt_1->SetBinError(21,4.572723e-05);
   jetPt_1->SetBinError(22,3.843527e-05);
   jetPt_1->SetBinError(23,3.428051e-05);
   jetPt_1->SetBinError(24,3.28211e-05);
   jetPt_1->SetBinError(25,2.646925e-05);
   jetPt_1->SetBinError(26,2.551724e-05);
   jetPt_1->SetBinError(27,1.909973e-05);
   jetPt_1->SetBinError(28,1.890006e-05);
   jetPt_1->SetBinError(29,4.274124e-05);
   jetPt_1->SetEntries(26940.15);
   jetPt_1->SetStats(0);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   jetPt_1->SetLineColor(ci);
   jetPt_1->GetXaxis()->SetTitle("p_{T}^{Jet} ");
   jetPt_1->GetXaxis()->CenterTitle(true);
   jetPt_1->GetXaxis()->SetLabelFont(42);
   jetPt_1->GetXaxis()->SetLabelSize(0.035);
   jetPt_1->GetXaxis()->SetTitleSize(0.035);
   jetPt_1->GetXaxis()->SetTitleFont(42);
   jetPt_1->GetYaxis()->SetTitle(" Normalized Entires ");
   jetPt_1->GetYaxis()->SetLabelFont(42);
   jetPt_1->GetYaxis()->SetLabelSize(0.035);
   jetPt_1->GetYaxis()->SetTitleSize(0.035);
   jetPt_1->GetYaxis()->SetTitleOffset(1.19);
   jetPt_1->GetYaxis()->SetTitleFont(42);
   jetPt_1->GetZaxis()->SetLabelFont(42);
   jetPt_1->GetZaxis()->SetLabelSize(0.035);
   jetPt_1->GetZaxis()->SetTitleSize(0.035);
   jetPt_1->GetZaxis()->SetTitleFont(42);
   jetPt_1->Draw("same hist");
   
   TLegend *leg = new TLegend(0.5237065,0.6729505,0.9948735,0.8804912,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("NULL","Pb+Pb 2.76 TeV","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   leg = new TLegend(0.5103716,0.4935144,0.832632,0.6967312,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(0);
   entry=leg->AddEntry("jetPt_0","DATA","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(2);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("jetPt_1","MC","lpf");
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   leg->Draw();
   c2_1->Modified();
   c2->cd();
  
// ------------>Primitives in pad: c2_2
   c2_2 = new TPad("c2_2", "c2_2",0.3433333,0.01,0.6566667,0.99);
   c2_2->Draw();
   c2_2->cd();
   c2_2->Range(-5,-0.04797677,5,0.4317909);
   c2_2->SetFillColor(0);
   c2_2->SetBorderMode(0);
   c2_2->SetBorderSize(2);
   c2_2->SetFrameBorderMode(0);
   c2_2->SetFrameBorderMode(0);
   
   TH1D *jetEta_0 = new TH1D("jetEta_0","",40,-4,4);
   jetEta_0->SetBinContent(13,0.3454852);
   jetEta_0->SetBinContent(14,0.2798474);
   jetEta_0->SetBinContent(15,0.2811779);
   jetEta_0->SetBinContent(16,0.2935959);
   jetEta_0->SetBinContent(17,0.2838389);
   jetEta_0->SetBinContent(18,0.2896044);
   jetEta_0->SetBinContent(19,0.3286323);
   jetEta_0->SetBinContent(20,0.3530247);
   jetEta_0->SetBinContent(21,0.3432677);
   jetEta_0->SetBinContent(22,0.3388327);
   jetEta_0->SetBinContent(23,0.3197623);
   jetEta_0->SetBinContent(24,0.2802909);
   jetEta_0->SetBinContent(25,0.3135533);
   jetEta_0->SetBinContent(26,0.3224233);
   jetEta_0->SetBinContent(27,0.2869434);
   jetEta_0->SetBinContent(28,0.3397197);
   jetEta_0->SetBinError(13,0.01237829);
   jetEta_0->SetBinError(14,0.01114055);
   jetEta_0->SetBinError(15,0.011167);
   jetEta_0->SetBinError(16,0.01141093);
   jetEta_0->SetBinError(17,0.01121972);
   jetEta_0->SetBinError(18,0.0113331);
   jetEta_0->SetBinError(19,0.01207261);
   jetEta_0->SetBinError(20,0.01251263);
   jetEta_0->SetBinError(21,0.0123385);
   jetEta_0->SetBinError(22,0.01225854);
   jetEta_0->SetBinError(23,0.01190857);
   jetEta_0->SetBinError(24,0.01114937);
   jetEta_0->SetBinError(25,0.01179239);
   jetEta_0->SetBinError(26,0.01195802);
   jetEta_0->SetBinError(27,0.01128091);
   jetEta_0->SetBinError(28,0.01227457);
   jetEta_0->SetEntries(11274);
   jetEta_0->SetStats(0);
   jetEta_0->SetLineColor(2);
   jetEta_0->GetXaxis()->SetTitle("jet #eta ");
   jetEta_0->GetXaxis()->CenterTitle(true);
   jetEta_0->GetXaxis()->SetLabelFont(42);
   jetEta_0->GetXaxis()->SetLabelSize(0.035);
   jetEta_0->GetXaxis()->SetTitleSize(0.035);
   jetEta_0->GetXaxis()->SetTitleFont(42);
   jetEta_0->GetYaxis()->SetTitle(" Noralized Entries ");
   jetEta_0->GetYaxis()->SetLabelFont(42);
   jetEta_0->GetYaxis()->SetLabelSize(0.035);
   jetEta_0->GetYaxis()->SetTitleSize(0.035);
   jetEta_0->GetYaxis()->SetTitleOffset(1.19);
   jetEta_0->GetYaxis()->SetTitleFont(42);
   jetEta_0->GetZaxis()->SetLabelFont(42);
   jetEta_0->GetZaxis()->SetLabelSize(0.035);
   jetEta_0->GetZaxis()->SetTitleSize(0.035);
   jetEta_0->GetZaxis()->SetTitleFont(42);
   jetEta_0->Draw("e");
   
   TH1D *jetEta_1 = new TH1D("jetEta_1","",40,-4,4);
   jetEta_1->SetBinContent(13,0.2540004);
   jetEta_1->SetBinContent(14,0.2448837);
   jetEta_1->SetBinContent(15,0.2954961);
   jetEta_1->SetBinContent(16,0.3180177);
   jetEta_1->SetBinContent(17,0.3250712);
   jetEta_1->SetBinContent(18,0.3470012);
   jetEta_1->SetBinContent(19,0.3759836);
   jetEta_1->SetBinContent(20,0.3454416);
   jetEta_1->SetBinContent(21,0.3628281);
   jetEta_1->SetBinContent(22,0.3684002);
   jetEta_1->SetBinContent(23,0.3267449);
   jetEta_1->SetBinContent(24,0.3206265);
   jetEta_1->SetBinContent(25,0.3232426);
   jetEta_1->SetBinContent(26,0.2903533);
   jetEta_1->SetBinContent(27,0.2484613);
   jetEta_1->SetBinContent(28,0.2534475);
   jetEta_1->SetBinError(13,0.005564102);
   jetEta_1->SetBinError(14,0.005355445);
   jetEta_1->SetBinError(15,0.005878272);
   jetEta_1->SetBinError(16,0.006111398);
   jetEta_1->SetBinError(17,0.00616296);
   jetEta_1->SetBinError(18,0.006338279);
   jetEta_1->SetBinError(19,0.006608676);
   jetEta_1->SetBinError(20,0.006343622);
   jetEta_1->SetBinError(21,0.006515625);
   jetEta_1->SetBinError(22,0.006477989);
   jetEta_1->SetBinError(23,0.006116703);
   jetEta_1->SetBinError(24,0.006092527);
   jetEta_1->SetBinError(25,0.006106235);
   jetEta_1->SetBinError(26,0.005764114);
   jetEta_1->SetBinError(27,0.005447868);
   jetEta_1->SetBinError(28,0.005536552);
   jetEta_1->SetEntries(26940.15);
   jetEta_1->SetStats(0);

   ci = TColor::GetColor("#000099");
   jetEta_1->SetLineColor(ci);
   jetEta_1->GetXaxis()->SetTitle("jet #eta ");
   jetEta_1->GetXaxis()->CenterTitle(true);
   jetEta_1->GetXaxis()->SetLabelFont(42);
   jetEta_1->GetXaxis()->SetLabelSize(0.035);
   jetEta_1->GetXaxis()->SetTitleSize(0.035);
   jetEta_1->GetXaxis()->SetTitleFont(42);
   jetEta_1->GetYaxis()->SetTitle(" Noralized Entries ");
   jetEta_1->GetYaxis()->SetLabelFont(42);
   jetEta_1->GetYaxis()->SetLabelSize(0.035);
   jetEta_1->GetYaxis()->SetTitleSize(0.035);
   jetEta_1->GetYaxis()->SetTitleOffset(1.19);
   jetEta_1->GetYaxis()->SetTitleFont(42);
   jetEta_1->GetZaxis()->SetLabelFont(42);
   jetEta_1->GetZaxis()->SetLabelSize(0.035);
   jetEta_1->GetZaxis()->SetTitleSize(0.035);
   jetEta_1->GetZaxis()->SetTitleFont(42);
   jetEta_1->Draw("same hist");
   c2_2->Modified();
   c2->cd();
  
// ------------>Primitives in pad: c2_3
   c2_3 = new TPad("c2_3", "c2_3",0.6766667,0.01,0.99,0.99);
   c2_3->Draw();
   c2_3->cd();
   c2_3->Range(-5,-0.02647543,5,0.2382788);
   c2_3->SetFillColor(0);
   c2_3->SetBorderMode(0);
   c2_3->SetBorderSize(2);
   c2_3->SetFrameBorderMode(0);
   c2_3->SetFrameBorderMode(0);
   
   TH1D *jetPhi_0 = new TH1D("jetPhi_0","",40,-4,4);
   jetPhi_0->SetBinContent(5,0.1126486);
   jetPhi_0->SetBinContent(6,0.1698599);
   jetPhi_0->SetBinContent(7,0.1756253);
   jetPhi_0->SetBinContent(8,0.1716338);
   jetPhi_0->SetBinContent(9,0.1578854);
   jetPhi_0->SetBinContent(10,0.1609899);
   jetPhi_0->SetBinContent(11,0.136154);
   jetPhi_0->SetBinContent(12,0.1339365);
   jetPhi_0->SetBinContent(13,0.124623);
   jetPhi_0->SetBinContent(14,0.1339365);
   jetPhi_0->SetBinContent(15,0.1365975);
   jetPhi_0->SetBinContent(16,0.1574419);
   jetPhi_0->SetBinContent(17,0.1765123);
   jetPhi_0->SetBinContent(18,0.1654249);
   jetPhi_0->SetBinContent(19,0.1507894);
   jetPhi_0->SetBinContent(20,0.142363);
   jetPhi_0->SetBinContent(21,0.1512329);
   jetPhi_0->SetBinContent(22,0.1445805);
   jetPhi_0->SetBinContent(23,0.141476);
   jetPhi_0->SetBinContent(24,0.1521199);
   jetPhi_0->SetBinContent(25,0.1618769);
   jetPhi_0->SetBinContent(26,0.1840518);
   jetPhi_0->SetBinContent(27,0.1490154);
   jetPhi_0->SetBinContent(28,0.1649814);
   jetPhi_0->SetBinContent(29,0.1645379);
   jetPhi_0->SetBinContent(30,0.1884868);
   jetPhi_0->SetBinContent(31,0.1880433);
   jetPhi_0->SetBinContent(32,0.1924783);
   jetPhi_0->SetBinContent(33,0.1747383);
   jetPhi_0->SetBinContent(34,0.1632074);
   jetPhi_0->SetBinContent(35,0.1574419);
   jetPhi_0->SetBinContent(36,0.1153096);
   jetPhi_0->SetBinError(5,0.0070682);
   jetPhi_0->SetBinError(6,0.008679433);
   jetPhi_0->SetBinError(7,0.008825505);
   jetPhi_0->SetBinError(8,0.008724639);
   jetPhi_0->SetBinError(9,0.008367909);
   jetPhi_0->SetBinError(10,0.008449778);
   jetPhi_0->SetBinError(11,0.007770718);
   jetPhi_0->SetBinError(12,0.007707179);
   jetPhi_0->SetBinError(13,0.007434386);
   jetPhi_0->SetBinError(14,0.007707179);
   jetPhi_0->SetBinError(15,0.007783364);
   jetPhi_0->SetBinError(16,0.008356149);
   jetPhi_0->SetBinError(17,0.008847764);
   jetPhi_0->SetBinError(18,0.008565375);
   jetPhi_0->SetBinError(19,0.008177705);
   jetPhi_0->SetBinError(20,0.007945926);
   jetPhi_0->SetBinError(21,0.008189722);
   jetPhi_0->SetBinError(22,0.008007571);
   jetPhi_0->SetBinError(23,0.007921133);
   jetPhi_0->SetBinError(24,0.008213704);
   jetPhi_0->SetBinError(25,0.008473023);
   jetPhi_0->SetBinError(26,0.009034748);
   jetPhi_0->SetBinError(27,0.008129458);
   jetPhi_0->SetBinError(28,0.008553886);
   jetPhi_0->SetBinError(29,0.008542381);
   jetPhi_0->SetBinError(30,0.009142952);
   jetPhi_0->SetBinError(31,0.009132189);
   jetPhi_0->SetBinError(32,0.009239253);
   jetPhi_0->SetBinError(33,0.00880319);
   jetPhi_0->SetBinError(34,0.008507773);
   jetPhi_0->SetBinError(35,0.008356149);
   jetPhi_0->SetBinError(36,0.007151195);
   jetPhi_0->SetEntries(11274);
   jetPhi_0->SetStats(0);
   jetPhi_0->SetLineColor(2);
   jetPhi_0->GetXaxis()->SetTitle("jet #phi ");
   jetPhi_0->GetXaxis()->CenterTitle(true);
   jetPhi_0->GetXaxis()->SetLabelFont(42);
   jetPhi_0->GetXaxis()->SetLabelSize(0.035);
   jetPhi_0->GetXaxis()->SetTitleSize(0.035);
   jetPhi_0->GetXaxis()->SetTitleFont(42);
   jetPhi_0->GetYaxis()->SetTitle(" Normalized Entries ");
   jetPhi_0->GetYaxis()->SetLabelFont(42);
   jetPhi_0->GetYaxis()->SetLabelSize(0.035);
   jetPhi_0->GetYaxis()->SetTitleSize(0.035);
   jetPhi_0->GetYaxis()->SetTitleOffset(1.19);
   jetPhi_0->GetYaxis()->SetTitleFont(42);
   jetPhi_0->GetZaxis()->SetLabelFont(42);
   jetPhi_0->GetZaxis()->SetLabelSize(0.035);
   jetPhi_0->GetZaxis()->SetTitleSize(0.035);
   jetPhi_0->GetZaxis()->SetTitleFont(42);
   jetPhi_0->Draw("e");
   
   TH1D *jetPhi_1 = new TH1D("jetPhi_1","",40,-4,4);
   jetPhi_1->SetBinContent(5,0.1100002);
   jetPhi_1->SetBinContent(6,0.1694034);
   jetPhi_1->SetBinContent(7,0.1605322);
   jetPhi_1->SetBinContent(8,0.176369);
   jetPhi_1->SetBinContent(9,0.1601536);
   jetPhi_1->SetBinContent(10,0.1590315);
   jetPhi_1->SetBinContent(11,0.1573236);
   jetPhi_1->SetBinContent(12,0.1551814);
   jetPhi_1->SetBinContent(13,0.1443497);
   jetPhi_1->SetBinContent(14,0.1379641);
   jetPhi_1->SetBinContent(15,0.1485588);
   jetPhi_1->SetBinContent(16,0.1564198);
   jetPhi_1->SetBinContent(17,0.1515591);
   jetPhi_1->SetBinContent(18,0.1613528);
   jetPhi_1->SetBinContent(19,0.1640942);
   jetPhi_1->SetBinContent(20,0.148908);
   jetPhi_1->SetBinContent(21,0.1630638);
   jetPhi_1->SetBinContent(22,0.158688);
   jetPhi_1->SetBinContent(23,0.1575104);
   jetPhi_1->SetBinContent(24,0.145538);
   jetPhi_1->SetBinContent(25,0.1591552);
   jetPhi_1->SetBinContent(26,0.1626662);
   jetPhi_1->SetBinContent(27,0.1582859);
   jetPhi_1->SetBinContent(28,0.1812712);
   jetPhi_1->SetBinContent(29,0.1664509);
   jetPhi_1->SetBinContent(30,0.1601467);
   jetPhi_1->SetBinContent(31,0.1491727);
   jetPhi_1->SetBinContent(32,0.166776);
   jetPhi_1->SetBinContent(33,0.1734875);
   jetPhi_1->SetBinContent(34,0.1689964);
   jetPhi_1->SetBinContent(35,0.1533632);
   jetPhi_1->SetBinContent(36,0.1142262);
   jetPhi_1->SetBinError(5,0.003549736);
   jetPhi_1->SetBinError(6,0.004453942);
   jetPhi_1->SetBinError(7,0.004306466);
   jetPhi_1->SetBinError(8,0.00460209);
   jetPhi_1->SetBinError(9,0.004306249);
   jetPhi_1->SetBinError(10,0.004341446);
   jetPhi_1->SetBinError(11,0.004306526);
   jetPhi_1->SetBinError(12,0.004165515);
   jetPhi_1->SetBinError(13,0.004115704);
   jetPhi_1->SetBinError(14,0.003960953);
   jetPhi_1->SetBinError(15,0.004128313);
   jetPhi_1->SetBinError(16,0.004228036);
   jetPhi_1->SetBinError(17,0.004180106);
   jetPhi_1->SetBinError(18,0.004314262);
   jetPhi_1->SetBinError(19,0.004347108);
   jetPhi_1->SetBinError(20,0.004123915);
   jetPhi_1->SetBinError(21,0.004346513);
   jetPhi_1->SetBinError(22,0.004280421);
   jetPhi_1->SetBinError(23,0.004304328);
   jetPhi_1->SetBinError(24,0.004115781);
   jetPhi_1->SetBinError(25,0.004301342);
   jetPhi_1->SetBinError(26,0.004381247);
   jetPhi_1->SetBinError(27,0.004324506);
   jetPhi_1->SetBinError(28,0.004760213);
   jetPhi_1->SetBinError(29,0.004425396);
   jetPhi_1->SetBinError(30,0.004312768);
   jetPhi_1->SetBinError(31,0.004129724);
   jetPhi_1->SetBinError(32,0.004468958);
   jetPhi_1->SetBinError(33,0.004518345);
   jetPhi_1->SetBinError(34,0.004550276);
   jetPhi_1->SetBinError(35,0.004170074);
   jetPhi_1->SetBinError(36,0.003600025);
   jetPhi_1->SetEntries(26940.15);
   jetPhi_1->SetStats(0);

   ci = TColor::GetColor("#000099");
   jetPhi_1->SetLineColor(ci);
   jetPhi_1->GetXaxis()->SetTitle("jet #phi ");
   jetPhi_1->GetXaxis()->CenterTitle(true);
   jetPhi_1->GetXaxis()->SetLabelFont(42);
   jetPhi_1->GetXaxis()->SetLabelSize(0.035);
   jetPhi_1->GetXaxis()->SetTitleSize(0.035);
   jetPhi_1->GetXaxis()->SetTitleFont(42);
   jetPhi_1->GetYaxis()->SetTitle(" Normalized Entries ");
   jetPhi_1->GetYaxis()->SetLabelFont(42);
   jetPhi_1->GetYaxis()->SetLabelSize(0.035);
   jetPhi_1->GetYaxis()->SetTitleSize(0.035);
   jetPhi_1->GetYaxis()->SetTitleOffset(1.19);
   jetPhi_1->GetYaxis()->SetTitleFont(42);
   jetPhi_1->GetZaxis()->SetLabelFont(42);
   jetPhi_1->GetZaxis()->SetLabelSize(0.035);
   jetPhi_1->GetZaxis()->SetTitleSize(0.035);
   jetPhi_1->GetZaxis()->SetTitleFont(42);
   jetPhi_1->Draw("same hist");
   c2_3->Modified();
   c2->cd();
   c2->Modified();
   c2->cd();
   c2->SetSelected(c2);
}
