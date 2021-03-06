{
//=========Macro generated from canvas: c4/sum
//=========  (Fri Oct  4 06:15:33 2013) by ROOT version5.34/02
   TCanvas *c4 = new TCanvas("c4", "sum",1859,127,1200,300);
   gStyle->SetOptStat(0);
   c4->Range(0,0,1,1);
   c4->SetFillColor(0);
   c4->SetBorderMode(0);
   c4->SetBorderSize(2);
   c4->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: c4_1
   TPad *c4_1 = new TPad("c4_1", "c4_1",0.01,0.01,0.24,0.99);
   c4_1->Draw();
   c4_1->cd();
   c4_1->Range(-61.875,-0.01044207,306.875,0.09397862);
   c4_1->SetFillColor(0);
   c4_1->SetBorderMode(0);
   c4_1->SetBorderSize(2);
   c4_1->SetFrameBorderMode(0);
   c4_1->SetFrameBorderMode(0);
   
   TH1D *sum_0 = new TH1D("sum_0","",40,-25,270);
   sum_0->SetBinContent(0,0.0001167321);
   sum_0->SetBinContent(1,0.0002829253);
   sum_0->SetBinContent(2,0.001335209);
   sum_0->SetBinContent(3,0.02381877);
   sum_0->SetBinContent(4,0.07955862);
   sum_0->SetBinContent(5,0.005500809);
   sum_0->SetBinContent(6,0.004623302);
   sum_0->SetBinContent(7,0.003827142);
   sum_0->SetBinContent(8,0.004714319);
   sum_0->SetBinContent(9,0.005696923);
   sum_0->SetBinContent(10,0.003285172);
   sum_0->SetBinContent(11,0.00130821);
   sum_0->SetBinContent(12,0.000631236);
   sum_0->SetBinContent(13,0.0002344094);
   sum_0->SetBinContent(14,0.00016112);
   sum_0->SetBinContent(15,0.0001510846);
   sum_0->SetBinContent(16,0.0001278829);
   sum_0->SetBinContent(17,6.264159e-05);
   sum_0->SetBinContent(18,8.899141e-05);
   sum_0->SetBinContent(19,4.615469e-05);
   sum_0->SetBinContent(20,2.774208e-05);
   sum_0->SetBinContent(21,2.306536e-05);
   sum_0->SetBinContent(22,1.524504e-05);
   sum_0->SetBinContent(23,1.403654e-05);
   sum_0->SetBinContent(24,1.190495e-05);
   sum_0->SetBinContent(25,9.153944e-06);
   sum_0->SetBinContent(26,6.707496e-06);
   sum_0->SetBinContent(27,3.190995e-06);
   sum_0->SetBinContent(28,4.330268e-06);
   sum_0->SetBinContent(29,3.028241e-06);
   sum_0->SetBinContent(30,2.96417e-06);
   sum_0->SetBinContent(31,2.766806e-06);
   sum_0->SetBinContent(32,2.278546e-06);
   sum_0->SetBinContent(33,1.790286e-06);
   sum_0->SetBinContent(34,2.377228e-06);
   sum_0->SetBinContent(35,9.765199e-07);
   sum_0->SetBinContent(36,1.237955e-06);
   sum_0->SetBinContent(37,1.400708e-06);
   sum_0->SetBinContent(38,2.313156e-06);
   sum_0->SetBinContent(39,1.139273e-06);
   sum_0->SetBinContent(40,6.510133e-07);
   sum_0->SetBinContent(41,3.914504e-05);
   sum_0->SetBinError(0,9.098818e-06);
   sum_0->SetBinError(1,2.140145e-05);
   sum_0->SetBinError(2,8.702784e-05);
   sum_0->SetBinError(3,0.000827263);
   sum_0->SetBinError(4,0.00151491);
   sum_0->SetBinError(5,0.0003139249);
   sum_0->SetBinError(6,0.0002975881);
   sum_0->SetBinError(7,0.0002807506);
   sum_0->SetBinError(8,0.0003339789);
   sum_0->SetBinError(9,0.0003858016);
   sum_0->SetBinError(10,0.0002832095);
   sum_0->SetBinError(11,0.0001594797);
   sum_0->SetBinError(12,9.384187e-05);
   sum_0->SetBinError(13,2.112797e-05);
   sum_0->SetBinError(14,1.544663e-05);
   sum_0->SetBinError(15,3.593822e-05);
   sum_0->SetBinError(16,3.531789e-05);
   sum_0->SetBinError(17,6.816654e-06);
   sum_0->SetBinError(18,3.453449e-05);
   sum_0->SetBinError(19,7.848045e-06);
   sum_0->SetBinError(20,4.37782e-06);
   sum_0->SetBinError(21,5.058175e-06);
   sum_0->SetBinError(22,2.284708e-06);
   sum_0->SetBinError(23,2.006816e-06);
   sum_0->SetBinError(24,3.514998e-06);
   sum_0->SetBinError(25,1.797957e-06);
   sum_0->SetBinError(26,1.260799e-06);
   sum_0->SetBinError(27,8.765379e-07);
   sum_0->SetBinError(28,9.765957e-07);
   sum_0->SetBinError(29,8.612956e-07);
   sum_0->SetBinError(30,9.901393e-07);
   sum_0->SetBinError(31,6.710491e-07);
   sum_0->SetBinError(32,6.089671e-07);
   sum_0->SetBinError(33,5.397917e-07);
   sum_0->SetBinError(34,7.97418e-07);
   sum_0->SetBinError(35,3.986626e-07);
   sum_0->SetBinError(36,6.711594e-07);
   sum_0->SetBinError(37,6.906111e-07);
   sum_0->SetBinError(38,9.35105e-07);
   sum_0->SetBinError(39,4.306048e-07);
   sum_0->SetBinError(40,3.255066e-07);
   sum_0->SetBinError(41,3.382754e-05);
   sum_0->SetEntries(4015.813);
   sum_0->SetStats(0);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#ff0000");
   sum_0->SetFillColor(ci);
   sum_0->SetFillStyle(3005);

   ci = TColor::GetColor("#000099");
   sum_0->SetLineColor(ci);
   sum_0->GetXaxis()->SetTitle("photon Sum ISO (GeV)");
   sum_0->GetXaxis()->CenterTitle(true);
   sum_0->GetXaxis()->SetLabelFont(42);
   sum_0->GetXaxis()->SetLabelSize(0.035);
   sum_0->GetXaxis()->SetTitleSize(0.035);
   sum_0->GetXaxis()->SetTitleFont(42);
   sum_0->GetYaxis()->SetTitle(" Normalized Entries");
   sum_0->GetYaxis()->SetLabelFont(42);
   sum_0->GetYaxis()->SetLabelSize(0.035);
   sum_0->GetYaxis()->SetTitleSize(0.035);
   sum_0->GetYaxis()->SetTitleFont(42);
   sum_0->GetZaxis()->SetLabelFont(42);
   sum_0->GetZaxis()->SetLabelSize(0.035);
   sum_0->GetZaxis()->SetTitleSize(0.035);
   sum_0->GetZaxis()->SetTitleFont(42);
   sum_0->Draw("hist");
   
   TH1D *sumEM_0 = new TH1D("sumEM_0","",40,-25,270);
   sumEM_0->SetBinContent(0,3.144233e-05);
   sumEM_0->SetBinContent(1,5.545531e-05);
   sumEM_0->SetBinContent(2,0.0001871944);
   sumEM_0->SetBinContent(3,0.002627851);
   sumEM_0->SetBinContent(4,0.0217048);
   sumEM_0->SetBinContent(5,0.02250969);
   sumEM_0->SetBinContent(6,0.02088514);
   sumEM_0->SetBinContent(7,0.01788081);
   sumEM_0->SetBinContent(8,0.01342494);
   sumEM_0->SetBinContent(9,0.01204789);
   sumEM_0->SetBinContent(10,0.007622364);
   sumEM_0->SetBinContent(11,0.005373627);
   sumEM_0->SetBinContent(12,0.003277277);
   sumEM_0->SetBinContent(13,0.002420997);
   sumEM_0->SetBinContent(14,0.001827755);
   sumEM_0->SetBinContent(15,0.001194091);
   sumEM_0->SetBinContent(16,0.0006697036);
   sumEM_0->SetBinContent(17,0.0004715178);
   sumEM_0->SetBinContent(18,0.0002387358);
   sumEM_0->SetBinContent(19,0.0002574766);
   sumEM_0->SetBinContent(20,0.0002700231);
   sumEM_0->SetBinContent(21,0.0001191498);
   sumEM_0->SetBinContent(22,0.0001379334);
   sumEM_0->SetBinContent(23,6.101568e-05);
   sumEM_0->SetBinContent(24,5.823549e-05);
   sumEM_0->SetBinContent(25,4.75898e-05);
   sumEM_0->SetBinContent(26,3.546851e-05);
   sumEM_0->SetBinContent(27,3.752435e-05);
   sumEM_0->SetBinContent(28,1.207854e-05);
   sumEM_0->SetBinContent(29,1.270153e-05);
   sumEM_0->SetBinContent(30,4.026179e-06);
   sumEM_0->SetBinContent(31,6.330988e-05);
   sumEM_0->SetBinContent(32,1.068844e-05);
   sumEM_0->SetBinContent(33,2.013089e-06);
   sumEM_0->SetBinContent(34,4.026179e-06);
   sumEM_0->SetBinContent(35,1.068844e-05);
   sumEM_0->SetBinContent(36,4.026179e-06);
   sumEM_0->SetBinContent(37,2.013089e-06);
   sumEM_0->SetBinContent(38,1.270153e-05);
   sumEM_0->SetBinContent(39,1.068844e-05);
   sumEM_0->SetBinContent(41,6.637335e-05);
   sumEM_0->SetBinError(0,1.337502e-05);
   sumEM_0->SetBinError(1,2.001559e-05);
   sumEM_0->SetBinError(2,7.74489e-05);
   sumEM_0->SetBinError(3,0.0003142009);
   sumEM_0->SetBinError(4,0.0009886346);
   sumEM_0->SetBinError(5,0.0009274903);
   sumEM_0->SetBinError(6,0.0008585399);
   sumEM_0->SetBinError(7,0.0007536248);
   sumEM_0->SetBinError(8,0.0006302766);
   sumEM_0->SetBinError(9,0.0005967824);
   sumEM_0->SetBinError(10,0.0004532342);
   sumEM_0->SetBinError(11,0.0003428637);
   sumEM_0->SetBinError(12,0.0002632669);
   sumEM_0->SetBinError(13,0.0002256348);
   sumEM_0->SetBinError(14,0.0001899972);
   sumEM_0->SetBinError(15,0.0001301163);
   sumEM_0->SetBinError(16,8.577905e-05);
   sumEM_0->SetBinError(17,7.115852e-05);
   sumEM_0->SetBinError(18,4.504837e-05);
   sumEM_0->SetBinError(19,4.609642e-05);
   sumEM_0->SetBinError(20,7.785404e-05);
   sumEM_0->SetBinError(21,3.395359e-05);
   sumEM_0->SetBinError(22,4.191492e-05);
   sumEM_0->SetBinError(23,1.343977e-05);
   sumEM_0->SetBinError(24,1.704775e-05);
   sumEM_0->SetBinError(25,2.682912e-05);
   sumEM_0->SetBinError(26,1.367466e-05);
   sumEM_0->SetBinError(27,2.64488e-05);
   sumEM_0->SetBinError(28,4.931042e-06);
   sumEM_0->SetBinError(29,9.130543e-06);
   sumEM_0->SetBinError(30,2.846938e-06);
   sumEM_0->SetBinError(31,6.132983e-05);
   sumEM_0->SetBinError(32,8.905857e-06);
   sumEM_0->SetBinError(33,2.013089e-06);
   sumEM_0->SetBinError(34,2.846938e-06);
   sumEM_0->SetBinError(35,8.905857e-06);
   sumEM_0->SetBinError(36,2.846938e-06);
   sumEM_0->SetBinError(37,2.013089e-06);
   sumEM_0->SetBinError(38,9.130543e-06);
   sumEM_0->SetBinError(39,8.905857e-06);
   sumEM_0->SetBinError(41,3.638429e-05);
   sumEM_0->SetEntries(2213.673);
   sumEM_0->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   sumEM_0->SetFillColor(ci);
   sumEM_0->SetFillStyle(3002);

   ci = TColor::GetColor("#000099");
   sumEM_0->SetLineColor(ci);
   sumEM_0->GetXaxis()->SetTitle("photon Sum ISO ");
   sumEM_0->GetXaxis()->SetLabelFont(42);
   sumEM_0->GetXaxis()->SetLabelSize(0.035);
   sumEM_0->GetXaxis()->SetTitleSize(0.035);
   sumEM_0->GetXaxis()->SetTitleFont(42);
   sumEM_0->GetYaxis()->SetTitle(" Normalized Entries");
   sumEM_0->GetYaxis()->SetLabelFont(42);
   sumEM_0->GetYaxis()->SetLabelSize(0.035);
   sumEM_0->GetYaxis()->SetTitleSize(0.035);
   sumEM_0->GetYaxis()->SetTitleFont(42);
   sumEM_0->GetZaxis()->SetLabelFont(42);
   sumEM_0->GetZaxis()->SetLabelSize(0.035);
   sumEM_0->GetZaxis()->SetTitleSize(0.035);
   sumEM_0->GetZaxis()->SetTitleFont(42);
   sumEM_0->Draw("same hist");
   TLatex *   tex = new TLatex(0.27,0.85,"40GeV < p_{T}^{#gamma} < 50GeV, ");
tex->SetNDC();
   tex->SetTextFont(63);
   tex->SetTextSize(15);
   tex->Draw();
   
   TLegend *leg = new TLegend(0.2618875,0.5862845,0.7817362,0.7888655,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("sum_0","MC #gamma-jet + HYDJET","lpf");

   ci = TColor::GetColor("#ff0000");
   entry->SetFillColor(ci);
   entry->SetFillStyle(3005);

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("sumEM_0","MC dijet Background","lpf");

   ci = TColor::GetColor("#0000ff");
   entry->SetFillColor(ci);
   entry->SetFillStyle(3002);

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   leg->Draw();
   c4_1->Modified();
   c4->cd();
  
// ------------>Primitives in pad: c4_2
   c4_2 = new TPad("c4_2", "c4_2",0.26,0.01,0.49,0.99);
   c4_2->Draw();
   c4_2->cd();
   c4_2->Range(-61.875,-0.01010335,306.875,0.09093012);
   c4_2->SetFillColor(0);
   c4_2->SetBorderMode(0);
   c4_2->SetBorderSize(2);
   c4_2->SetFrameBorderMode(0);
   c4_2->SetFrameBorderMode(0);
   
   TH1D *sum_1 = new TH1D("sum_1","",40,-25,270);
   sum_1->SetBinContent(0,0.0002043025);
   sum_1->SetBinContent(1,0.0004483195);
   sum_1->SetBinContent(2,0.002968857);
   sum_1->SetBinContent(3,0.02566157);
   sum_1->SetBinContent(4,0.07697788);
   sum_1->SetBinContent(5,0.006020074);
   sum_1->SetBinContent(6,0.00373454);
   sum_1->SetBinContent(7,0.003582781);
   sum_1->SetBinContent(8,0.002884134);
   sum_1->SetBinContent(9,0.003011516);
   sum_1->SetBinContent(10,0.004148741);
   sum_1->SetBinContent(11,0.0028668);
   sum_1->SetBinContent(12,0.00118055);
   sum_1->SetBinContent(13,0.0007532735);
   sum_1->SetBinContent(14,0.0003777504);
   sum_1->SetBinContent(15,0.0002582601);
   sum_1->SetBinContent(16,0.000166079);
   sum_1->SetBinContent(17,0.0001116844);
   sum_1->SetBinContent(18,0.0001063793);
   sum_1->SetBinContent(19,7.556547e-05);
   sum_1->SetBinContent(20,4.550315e-05);
   sum_1->SetBinContent(21,6.010462e-05);
   sum_1->SetBinContent(22,2.690307e-05);
   sum_1->SetBinContent(23,3.180719e-05);
   sum_1->SetBinContent(24,2.430184e-05);
   sum_1->SetBinContent(25,9.813458e-06);
   sum_1->SetBinContent(26,9.015821e-06);
   sum_1->SetBinContent(27,5.18464e-06);
   sum_1->SetBinContent(28,1.464538e-05);
   sum_1->SetBinContent(29,4.229999e-06);
   sum_1->SetBinContent(30,2.392911e-06);
   sum_1->SetBinContent(31,5.18464e-06);
   sum_1->SetBinContent(32,2.392911e-06);
   sum_1->SetBinContent(33,2.791729e-06);
   sum_1->SetBinContent(34,4.229999e-06);
   sum_1->SetBinContent(35,1.994092e-06);
   sum_1->SetBinContent(36,2.392911e-06);
   sum_1->SetBinContent(37,1.994092e-06);
   sum_1->SetBinContent(38,7.97637e-07);
   sum_1->SetBinContent(39,1.595274e-06);
   sum_1->SetBinContent(40,1.196455e-06);
   sum_1->SetBinContent(41,4.287061e-05);
   sum_1->SetBinError(0,1.79712e-05);
   sum_1->SetBinError(1,4.060729e-05);
   sum_1->SetBinError(2,0.0001801309);
   sum_1->SetBinError(3,0.0009431522);
   sum_1->SetBinError(4,0.001729483);
   sum_1->SetBinError(5,0.0004239925);
   sum_1->SetBinError(6,0.000262387);
   sum_1->SetBinError(7,0.0003138071);
   sum_1->SetBinError(8,0.0002359922);
   sum_1->SetBinError(9,0.0002383648);
   sum_1->SetBinError(10,0.0003750676);
   sum_1->SetBinError(11,0.0002626939);
   sum_1->SetBinError(12,0.0001149236);
   sum_1->SetBinError(13,0.0001512605);
   sum_1->SetBinError(14,3.982992e-05);
   sum_1->SetBinError(15,3.000002e-05);
   sum_1->SetBinError(16,1.857674e-05);
   sum_1->SetBinError(17,1.326149e-05);
   sum_1->SetBinError(18,1.884674e-05);
   sum_1->SetBinError(19,1.50092e-05);
   sum_1->SetBinError(20,6.369668e-06);
   sum_1->SetBinError(21,1.596103e-05);
   sum_1->SetBinError(22,4.917778e-06);
   sum_1->SetBinError(23,8.759853e-06);
   sum_1->SetBinError(24,8.322062e-06);
   sum_1->SetBinError(25,2.325683e-06);
   sum_1->SetBinError(26,2.256255e-06);
   sum_1->SetBinError(27,1.43796e-06);
   sum_1->SetBinError(28,7.90035e-06);
   sum_1->SetBinError(29,1.78382e-06);
   sum_1->SetBinError(30,9.769018e-07);
   sum_1->SetBinError(31,1.43796e-06);
   sum_1->SetBinError(32,9.769018e-07);
   sum_1->SetBinError(33,1.055175e-06);
   sum_1->SetBinError(34,1.78382e-06);
   sum_1->SetBinError(35,8.917852e-07);
   sum_1->SetBinError(36,9.769018e-07);
   sum_1->SetBinError(37,8.917852e-07);
   sum_1->SetBinError(38,5.640145e-07);
   sum_1->SetBinError(39,7.97637e-07);
   sum_1->SetBinError(40,6.907739e-07);
   sum_1->SetBinError(41,1.5649e-05);
   sum_1->SetEntries(1639.91);
   sum_1->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   sum_1->SetFillColor(ci);
   sum_1->SetFillStyle(3005);

   ci = TColor::GetColor("#000099");
   sum_1->SetLineColor(ci);
   sum_1->GetXaxis()->SetTitle("photon Sum ISO (GeV)");
   sum_1->GetXaxis()->CenterTitle(true);
   sum_1->GetXaxis()->SetLabelFont(42);
   sum_1->GetXaxis()->SetLabelSize(0.035);
   sum_1->GetXaxis()->SetTitleSize(0.035);
   sum_1->GetXaxis()->SetTitleFont(42);
   sum_1->GetYaxis()->SetTitle(" Normalized Entries");
   sum_1->GetYaxis()->SetLabelFont(42);
   sum_1->GetYaxis()->SetLabelSize(0.035);
   sum_1->GetYaxis()->SetTitleSize(0.035);
   sum_1->GetYaxis()->SetTitleFont(42);
   sum_1->GetZaxis()->SetLabelFont(42);
   sum_1->GetZaxis()->SetLabelSize(0.035);
   sum_1->GetZaxis()->SetTitleSize(0.035);
   sum_1->GetZaxis()->SetTitleFont(42);
   sum_1->Draw("hist");
   
   TH1D *sumEM_1 = new TH1D("sumEM_1","",40,-25,270);
   sumEM_1->SetBinContent(0,1.493544e-05);
   sumEM_1->SetBinContent(1,8.42778e-05);
   sumEM_1->SetBinContent(2,0.0001406875);
   sumEM_1->SetBinContent(3,0.002407477);
   sumEM_1->SetBinContent(4,0.01647209);
   sumEM_1->SetBinContent(5,0.0212819);
   sumEM_1->SetBinContent(6,0.01948675);
   sumEM_1->SetBinContent(7,0.01766656);
   sumEM_1->SetBinContent(8,0.01336392);
   sumEM_1->SetBinContent(9,0.01161865);
   sumEM_1->SetBinContent(10,0.008710538);
   sumEM_1->SetBinContent(11,0.006477387);
   sumEM_1->SetBinContent(12,0.005512978);
   sumEM_1->SetBinContent(13,0.003568557);
   sumEM_1->SetBinContent(14,0.002895074);
   sumEM_1->SetBinContent(15,0.001974792);
   sumEM_1->SetBinContent(16,0.001034897);
   sumEM_1->SetBinContent(17,0.0007405891);
   sumEM_1->SetBinContent(18,0.0006832065);
   sumEM_1->SetBinContent(19,0.0004237482);
   sumEM_1->SetBinContent(20,0.0002746444);
   sumEM_1->SetBinContent(21,0.0002363572);
   sumEM_1->SetBinContent(22,0.000112608);
   sumEM_1->SetBinContent(23,5.476328e-05);
   sumEM_1->SetBinContent(24,0.0001041917);
   sumEM_1->SetBinContent(25,6.626095e-05);
   sumEM_1->SetBinContent(26,6.780165e-05);
   sumEM_1->SetBinContent(27,1.493544e-05);
   sumEM_1->SetBinContent(28,3.484936e-05);
   sumEM_1->SetBinContent(29,2.643311e-05);
   sumEM_1->SetBinContent(30,4.97848e-06);
   sumEM_1->SetBinContent(31,1.493544e-05);
   sumEM_1->SetBinContent(34,4.97848e-06);
   sumEM_1->SetBinContent(37,4.97848e-06);
   sumEM_1->SetBinContent(38,4.97848e-06);
   sumEM_1->SetBinContent(39,2.145463e-05);
   sumEM_1->SetBinContent(41,0.000192013);
   sumEM_1->SetBinError(0,8.622981e-06);
   sumEM_1->SetBinError(1,3.847134e-05);
   sumEM_1->SetBinError(2,7.227565e-05);
   sumEM_1->SetBinError(3,0.0003669778);
   sumEM_1->SetBinError(4,0.001143688);
   sumEM_1->SetBinError(5,0.001264251);
   sumEM_1->SetBinError(6,0.001141313);
   sumEM_1->SetBinError(7,0.001014948);
   sumEM_1->SetBinError(8,0.0008820192);
   sumEM_1->SetBinError(9,0.0007887554);
   sumEM_1->SetBinError(10,0.0006517648);
   sumEM_1->SetBinError(11,0.0005378618);
   sumEM_1->SetBinError(12,0.0004820508);
   sumEM_1->SetBinError(13,0.0003980086);
   sumEM_1->SetBinError(14,0.0003492089);
   sumEM_1->SetBinError(15,0.000305101);
   sumEM_1->SetBinError(16,0.0001540881);
   sumEM_1->SetBinError(17,0.0001250346);
   sumEM_1->SetBinError(18,0.0001291895);
   sumEM_1->SetBinError(19,9.356237e-05);
   sumEM_1->SetBinError(20,6.198176e-05);
   sumEM_1->SetBinError(21,6.328204e-05);
   sumEM_1->SetBinError(22,3.560331e-05);
   sumEM_1->SetBinError(23,1.651175e-05);
   sumEM_1->SetBinError(24,3.973896e-05);
   sumEM_1->SetBinError(25,2.614131e-05);
   sumEM_1->SetBinError(26,3.231916e-05);
   sumEM_1->SetBinError(27,8.622981e-06);
   sumEM_1->SetBinError(28,1.317182e-05);
   sumEM_1->SetBinError(29,2.202467e-05);
   sumEM_1->SetBinError(30,4.97848e-06);
   sumEM_1->SetBinError(31,8.622981e-06);
   sumEM_1->SetBinError(34,4.97848e-06);
   sumEM_1->SetBinError(37,4.97848e-06);
   sumEM_1->SetBinError(38,4.97848e-06);
   sumEM_1->SetBinError(39,2.145463e-05);
   sumEM_1->SetBinError(41,7.637265e-05);
   sumEM_1->SetEntries(895.8367);
   sumEM_1->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   sumEM_1->SetFillColor(ci);
   sumEM_1->SetFillStyle(3002);

   ci = TColor::GetColor("#000099");
   sumEM_1->SetLineColor(ci);
   sumEM_1->GetXaxis()->SetTitle("photon Sum ISO ");
   sumEM_1->GetXaxis()->SetLabelFont(42);
   sumEM_1->GetXaxis()->SetLabelSize(0.035);
   sumEM_1->GetXaxis()->SetTitleSize(0.035);
   sumEM_1->GetXaxis()->SetTitleFont(42);
   sumEM_1->GetYaxis()->SetTitle(" Normalized Entries");
   sumEM_1->GetYaxis()->SetLabelFont(42);
   sumEM_1->GetYaxis()->SetLabelSize(0.035);
   sumEM_1->GetYaxis()->SetTitleSize(0.035);
   sumEM_1->GetYaxis()->SetTitleFont(42);
   sumEM_1->GetZaxis()->SetLabelFont(42);
   sumEM_1->GetZaxis()->SetLabelSize(0.035);
   sumEM_1->GetZaxis()->SetTitleSize(0.035);
   sumEM_1->GetZaxis()->SetTitleFont(42);
   sumEM_1->Draw("same hist");
      tex = new TLatex(0.27,0.85,"50GeV < p_{T}^{#gamma} < 60GeV, ");
tex->SetNDC();
   tex->SetTextFont(63);
   tex->SetTextSize(15);
   tex->Draw();
   c4_2->Modified();
   c4->cd();
  
// ------------>Primitives in pad: c4_3
   c4_3 = new TPad("c4_3", "c4_3",0.51,0.01,0.74,0.99);
   c4_3->Draw();
   c4_3->cd();
   c4_3->Range(-61.875,-0.009436095,306.875,0.08492485);
   c4_3->SetFillColor(0);
   c4_3->SetBorderMode(0);
   c4_3->SetBorderSize(2);
   c4_3->SetFrameBorderMode(0);
   c4_3->SetFrameBorderMode(0);
   
   TH1D *sum_2 = new TH1D("sum_2","",40,-25,270);
   sum_2->SetBinContent(0,0.0004015095);
   sum_2->SetBinContent(1,0.0008252012);
   sum_2->SetBinContent(2,0.00752425);
   sum_2->SetBinContent(3,0.02464236);
   sum_2->SetBinContent(4,0.07189405);
   sum_2->SetBinContent(5,0.005261337);
   sum_2->SetBinContent(6,0.003099484);
   sum_2->SetBinContent(7,0.003303694);
   sum_2->SetBinContent(8,0.002616357);
   sum_2->SetBinContent(9,0.002378472);
   sum_2->SetBinContent(10,0.002841553);
   sum_2->SetBinContent(11,0.002453229);
   sum_2->SetBinContent(12,0.002795368);
   sum_2->SetBinContent(13,0.002252419);
   sum_2->SetBinContent(14,0.001448192);
   sum_2->SetBinContent(15,0.0007937515);
   sum_2->SetBinContent(16,0.0003813162);
   sum_2->SetBinContent(17,0.0002573333);
   sum_2->SetBinContent(18,0.0001659347);
   sum_2->SetBinContent(19,0.0001276119);
   sum_2->SetBinContent(20,0.0001258059);
   sum_2->SetBinContent(21,8.376316e-05);
   sum_2->SetBinContent(22,5.859666e-05);
   sum_2->SetBinContent(23,4.321533e-05);
   sum_2->SetBinContent(24,4.225838e-05);
   sum_2->SetBinContent(25,3.498285e-05);
   sum_2->SetBinContent(26,1.608491e-05);
   sum_2->SetBinContent(27,1.251049e-05);
   sum_2->SetBinContent(28,1.525465e-05);
   sum_2->SetBinContent(29,1.012754e-05);
   sum_2->SetBinContent(30,2.32526e-05);
   sum_2->SetBinContent(31,7.51006e-06);
   sum_2->SetBinContent(32,1.83022e-05);
   sum_2->SetBinContent(33,8.467009e-06);
   sum_2->SetBinContent(34,1.787212e-06);
   sum_2->SetBinContent(35,5.12711e-06);
   sum_2->SetBinContent(36,4.170162e-06);
   sum_2->SetBinContent(37,1.257935e-05);
   sum_2->SetBinContent(38,3.935636e-06);
   sum_2->SetBinContent(39,2.38295e-06);
   sum_2->SetBinContent(40,1.191475e-06);
   sum_2->SetBinContent(41,5.628258e-05);
   sum_2->SetBinError(0,2.883389e-05);
   sum_2->SetBinError(1,6.56058e-05);
   sum_2->SetBinError(2,0.0002931393);
   sum_2->SetBinError(3,0.000764866);
   sum_2->SetBinError(4,0.001315403);
   sum_2->SetBinError(5,0.0003184871);
   sum_2->SetBinError(6,0.0001510652);
   sum_2->SetBinError(7,0.00019973);
   sum_2->SetBinError(8,0.0001828373);
   sum_2->SetBinError(9,0.0001333106);
   sum_2->SetBinError(10,0.0001954965);
   sum_2->SetBinError(11,0.0001454388);
   sum_2->SetBinError(12,0.0001599616);
   sum_2->SetBinError(13,0.000220276);
   sum_2->SetBinError(14,0.0001996438);
   sum_2->SetBinError(15,0.0001402151);
   sum_2->SetBinError(16,4.425854e-05);
   sum_2->SetBinError(17,3.111191e-05);
   sum_2->SetBinError(18,2.382493e-05);
   sum_2->SetBinError(19,2.037708e-05);
   sum_2->SetBinError(20,1.993666e-05);
   sum_2->SetBinError(21,1.48156e-05);
   sum_2->SetBinError(22,1.345952e-05);
   sum_2->SetBinError(23,1.272745e-05);
   sum_2->SetBinError(24,1.257307e-05);
   sum_2->SetBinError(25,1.212749e-05);
   sum_2->SetBinError(26,3.095542e-06);
   sum_2->SetBinError(27,2.730012e-06);
   sum_2->SetBinError(28,3.524711e-06);
   sum_2->SetBinError(29,2.456288e-06);
   sum_2->SetBinError(30,5.525539e-06);
   sum_2->SetBinError(31,2.794611e-06);
   sum_2->SetBinError(32,1.171062e-05);
   sum_2->SetBinError(33,3.42283e-06);
   sum_2->SetBinError(34,1.031847e-06);
   sum_2->SetBinError(35,2.527892e-06);
   sum_2->SetBinError(36,1.576173e-06);
   sum_2->SetBinError(37,1.1419e-05);
   sum_2->SetBinError(38,2.383366e-06);
   sum_2->SetBinError(39,1.191475e-06);
   sum_2->SetBinError(40,8.424999e-07);
   sum_2->SetBinError(41,1.739769e-05);
   sum_2->SetEntries(1099.546);
   sum_2->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   sum_2->SetFillColor(ci);
   sum_2->SetFillStyle(3005);

   ci = TColor::GetColor("#000099");
   sum_2->SetLineColor(ci);
   sum_2->GetXaxis()->SetTitle("photon Sum ISO (GeV)");
   sum_2->GetXaxis()->CenterTitle(true);
   sum_2->GetXaxis()->SetLabelFont(42);
   sum_2->GetXaxis()->SetLabelSize(0.035);
   sum_2->GetXaxis()->SetTitleSize(0.035);
   sum_2->GetXaxis()->SetTitleFont(42);
   sum_2->GetYaxis()->SetTitle(" Normalized Entries");
   sum_2->GetYaxis()->SetLabelFont(42);
   sum_2->GetYaxis()->SetLabelSize(0.035);
   sum_2->GetYaxis()->SetTitleSize(0.035);
   sum_2->GetYaxis()->SetTitleFont(42);
   sum_2->GetZaxis()->SetLabelFont(42);
   sum_2->GetZaxis()->SetLabelSize(0.035);
   sum_2->GetZaxis()->SetTitleSize(0.035);
   sum_2->GetZaxis()->SetTitleFont(42);
   sum_2->Draw("hist");
   
   TH1D *sumEM_2 = new TH1D("sumEM_2","",40,-25,270);
   sumEM_2->SetBinContent(0,6.07511e-05);
   sumEM_2->SetBinContent(1,0.0001669604);
   sumEM_2->SetBinContent(2,0.0005305932);
   sumEM_2->SetBinContent(3,0.00219897);
   sumEM_2->SetBinContent(4,0.0139107);
   sumEM_2->SetBinContent(5,0.01784109);
   sumEM_2->SetBinContent(6,0.01647323);
   sumEM_2->SetBinContent(7,0.01433713);
   sumEM_2->SetBinContent(8,0.01443557);
   sumEM_2->SetBinContent(9,0.01094164);
   sumEM_2->SetBinContent(10,0.01057491);
   sumEM_2->SetBinContent(11,0.008225675);
   sumEM_2->SetBinContent(12,0.006416627);
   sumEM_2->SetBinContent(13,0.004513755);
   sumEM_2->SetBinContent(14,0.003961522);
   sumEM_2->SetBinContent(15,0.00284986);
   sumEM_2->SetBinContent(16,0.00209335);
   sumEM_2->SetBinContent(17,0.001683201);
   sumEM_2->SetBinContent(18,0.00117945);
   sumEM_2->SetBinContent(19,0.0007325212);
   sumEM_2->SetBinContent(20,0.0004506727);
   sumEM_2->SetBinContent(21,0.0004876365);
   sumEM_2->SetBinContent(22,0.0002657335);
   sumEM_2->SetBinContent(23,0.0002049824);
   sumEM_2->SetBinContent(24,0.0001041447);
   sumEM_2->SetBinContent(25,0.0002049824);
   sumEM_2->SetBinContent(26,3.471492e-05);
   sumEM_2->SetBinContent(27,0.0002398816);
   sumEM_2->SetBinContent(28,0.0001095164);
   sumEM_2->SetBinContent(29,0.0001095164);
   sumEM_2->SetBinContent(30,0.0001008377);
   sumEM_2->SetBinContent(31,1.735746e-05);
   sumEM_2->SetBinContent(32,1.735746e-05);
   sumEM_2->SetBinContent(33,1.735746e-05);
   sumEM_2->SetBinContent(34,8.678729e-06);
   sumEM_2->SetBinContent(35,0.0001070149);
   sumEM_2->SetBinContent(37,8.678729e-06);
   sumEM_2->SetBinContent(39,3.740075e-05);
   sumEM_2->SetBinContent(41,0.0001469172);
   sumEM_2->SetBinError(0,2.296176e-05);
   sumEM_2->SetBinError(1,7.580174e-05);
   sumEM_2->SetBinError(2,0.0001850555);
   sumEM_2->SetBinError(3,0.0004021164);
   sumEM_2->SetBinError(4,0.001162523);
   sumEM_2->SetBinError(5,0.001188787);
   sumEM_2->SetBinError(6,0.00108313);
   sumEM_2->SetBinError(7,0.0009597853);
   sumEM_2->SetBinError(8,0.0009844132);
   sumEM_2->SetBinError(9,0.0007900724);
   sumEM_2->SetBinError(10,0.0008025649);
   sumEM_2->SetBinError(11,0.0006623397);
   sumEM_2->SetBinError(12,0.0005325438);
   sumEM_2->SetBinError(13,0.0004563166);
   sumEM_2->SetBinError(14,0.0004730989);
   sumEM_2->SetBinError(15,0.0003221617);
   sumEM_2->SetBinError(16,0.0002918687);
   sumEM_2->SetBinError(17,0.0002605411);
   sumEM_2->SetBinError(18,0.0002002389);
   sumEM_2->SetBinError(19,0.0001348103);
   sumEM_2->SetBinError(20,8.446266e-05);
   sumEM_2->SetBinError(21,0.0001456051);
   sumEM_2->SetBinError(22,6.674338e-05);
   sumEM_2->SetBinError(23,6.266926e-05);
   sumEM_2->SetBinError(24,3.0064e-05);
   sumEM_2->SetBinError(25,6.266926e-05);
   sumEM_2->SetBinError(26,1.735746e-05);
   sumEM_2->SetBinError(27,0.0001169595);
   sumEM_2->SetBinError(28,5.566788e-05);
   sumEM_2->SetBinError(29,5.566788e-05);
   sumEM_2->SetBinError(30,5.49872e-05);
   sumEM_2->SetBinError(31,1.227358e-05);
   sumEM_2->SetBinError(32,1.227358e-05);
   sumEM_2->SetBinError(33,1.227358e-05);
   sumEM_2->SetBinError(34,8.678729e-06);
   sumEM_2->SetBinError(35,0.0001070149);
   sumEM_2->SetBinError(37,8.678729e-06);
   sumEM_2->SetBinError(39,3.740075e-05);
   sumEM_2->SetBinError(41,6.706511e-05);
   sumEM_2->SetEntries(513.892);
   sumEM_2->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   sumEM_2->SetFillColor(ci);
   sumEM_2->SetFillStyle(3002);

   ci = TColor::GetColor("#000099");
   sumEM_2->SetLineColor(ci);
   sumEM_2->GetXaxis()->SetTitle("photon Sum ISO ");
   sumEM_2->GetXaxis()->SetLabelFont(42);
   sumEM_2->GetXaxis()->SetLabelSize(0.035);
   sumEM_2->GetXaxis()->SetTitleSize(0.035);
   sumEM_2->GetXaxis()->SetTitleFont(42);
   sumEM_2->GetYaxis()->SetTitle(" Normalized Entries");
   sumEM_2->GetYaxis()->SetLabelFont(42);
   sumEM_2->GetYaxis()->SetLabelSize(0.035);
   sumEM_2->GetYaxis()->SetTitleSize(0.035);
   sumEM_2->GetYaxis()->SetTitleFont(42);
   sumEM_2->GetZaxis()->SetLabelFont(42);
   sumEM_2->GetZaxis()->SetLabelSize(0.035);
   sumEM_2->GetZaxis()->SetTitleSize(0.035);
   sumEM_2->GetZaxis()->SetTitleFont(42);
   sumEM_2->Draw("same hist");
      tex = new TLatex(0.27,0.85,"60GeV < p_{T}^{#gamma} < 80GeV, ");
tex->SetNDC();
   tex->SetTextFont(63);
   tex->SetTextSize(15);
   tex->Draw();
   c4_3->Modified();
   c4->cd();
  
// ------------>Primitives in pad: c4_4
   c4_4 = new TPad("c4_4", "c4_4",0.76,0.01,0.99,0.99);
   c4_4->Draw();
   c4_4->cd();
   c4_4->Range(-61.875,-0.008407353,306.875,0.07566617);
   c4_4->SetFillColor(0);
   c4_4->SetBorderMode(0);
   c4_4->SetBorderSize(2);
   c4_4->SetFrameBorderMode(0);
   c4_4->SetFrameBorderMode(0);
   
   TH1D *sum_3 = new TH1D("sum_3","",40,-25,270);
   sum_3->SetBinContent(0,0.00237676);
   sum_3->SetBinContent(1,0.005325501);
   sum_3->SetBinContent(2,0.01539691);
   sum_3->SetBinContent(3,0.01692415);
   sum_3->SetBinContent(4,0.06405602);
   sum_3->SetBinContent(5,0.004805934);
   sum_3->SetBinContent(6,0.003016394);
   sum_3->SetBinContent(7,0.002713361);
   sum_3->SetBinContent(8,0.002669363);
   sum_3->SetBinContent(9,0.002238345);
   sum_3->SetBinContent(10,0.002326102);
   sum_3->SetBinContent(11,0.002076258);
   sum_3->SetBinContent(12,0.002073185);
   sum_3->SetBinContent(13,0.001799581);
   sum_3->SetBinContent(14,0.001783923);
   sum_3->SetBinContent(15,0.001845716);
   sum_3->SetBinContent(16,0.001420313);
   sum_3->SetBinContent(17,0.001259783);
   sum_3->SetBinContent(18,0.0008062956);
   sum_3->SetBinContent(19,0.0006604536);
   sum_3->SetBinContent(20,0.000423108);
   sum_3->SetBinContent(21,0.0004383093);
   sum_3->SetBinContent(22,0.0003476922);
   sum_3->SetBinContent(23,0.0001932463);
   sum_3->SetBinContent(24,0.0001903445);
   sum_3->SetBinContent(25,0.0001347047);
   sum_3->SetBinContent(26,0.0001181729);
   sum_3->SetBinContent(27,8.32972e-05);
   sum_3->SetBinContent(28,9.370029e-05);
   sum_3->SetBinContent(29,5.321967e-05);
   sum_3->SetBinContent(30,7.627477e-05);
   sum_3->SetBinContent(31,4.019769e-05);
   sum_3->SetBinContent(32,4.551965e-05);
   sum_3->SetBinContent(33,2.955375e-05);
   sum_3->SetBinContent(34,3.007753e-05);
   sum_3->SetBinContent(35,2.342507e-05);
   sum_3->SetBinContent(36,1.197443e-05);
   sum_3->SetBinContent(37,1.810311e-05);
   sum_3->SetBinContent(38,1.729639e-05);
   sum_3->SetBinContent(39,1.064393e-05);
   sum_3->SetBinContent(40,1.677261e-05);
   sum_3->SetBinContent(41,0.0001974337);
   sum_3->SetBinError(0,7.063914e-05);
   sum_3->SetBinError(1,0.000133587);
   sum_3->SetBinError(2,0.0003238417);
   sum_3->SetBinError(3,0.0005303611);
   sum_3->SetBinError(4,0.0007729081);
   sum_3->SetBinError(5,0.0001848097);
   sum_3->SetBinError(6,0.0001407526);
   sum_3->SetBinError(7,0.0001315937);
   sum_3->SetBinError(8,0.0001402658);
   sum_3->SetBinError(9,0.0001152583);
   sum_3->SetBinError(10,0.000132511);
   sum_3->SetBinError(11,0.0001249056);
   sum_3->SetBinError(12,0.0001270581);
   sum_3->SetBinError(13,0.0001120193);
   sum_3->SetBinError(14,0.0001172753);
   sum_3->SetBinError(15,0.0001228618);
   sum_3->SetBinError(16,0.0001010876);
   sum_3->SetBinError(17,8.878764e-05);
   sum_3->SetBinError(18,6.188327e-05);
   sum_3->SetBinError(19,5.540562e-05);
   sum_3->SetBinError(20,3.334692e-05);
   sum_3->SetBinError(21,3.462365e-05);
   sum_3->SetBinError(22,4.402493e-05);
   sum_3->SetBinError(23,1.93283e-05);
   sum_3->SetBinError(24,2.048508e-05);
   sum_3->SetBinError(25,1.719576e-05);
   sum_3->SetBinError(26,1.43925e-05);
   sum_3->SetBinError(27,1.129004e-05);
   sum_3->SetBinError(28,1.382831e-05);
   sum_3->SetBinError(29,8.414769e-06);
   sum_3->SetBinError(30,2.734533e-05);
   sum_3->SetBinError(31,9.314505e-06);
   sum_3->SetBinError(32,9.687148e-06);
   sum_3->SetBinError(33,8.520466e-06);
   sum_3->SetBinError(34,7.527055e-06);
   sum_3->SetBinError(35,6.914154e-06);
   sum_3->SetBinError(36,3.991475e-06);
   sum_3->SetBinError(37,6.38159e-06);
   sum_3->SetBinError(38,4.797156e-06);
   sum_3->SetBinError(39,3.763199e-06);
   sum_3->SetBinError(40,6.241352e-06);
   sum_3->SetBinError(41,3.27926e-05);
   sum_3->SetEntries(499.9883);
   sum_3->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   sum_3->SetFillColor(ci);
   sum_3->SetFillStyle(3005);

   ci = TColor::GetColor("#000099");
   sum_3->SetLineColor(ci);
   sum_3->GetXaxis()->SetTitle("photon Sum ISO (GeV)");
   sum_3->GetXaxis()->CenterTitle(true);
   sum_3->GetXaxis()->SetLabelFont(42);
   sum_3->GetXaxis()->SetLabelSize(0.035);
   sum_3->GetXaxis()->SetTitleSize(0.035);
   sum_3->GetXaxis()->SetTitleFont(42);
   sum_3->GetYaxis()->SetTitle(" Normalized Entries");
   sum_3->GetYaxis()->SetLabelFont(42);
   sum_3->GetYaxis()->SetLabelSize(0.035);
   sum_3->GetYaxis()->SetTitleSize(0.035);
   sum_3->GetYaxis()->SetTitleFont(42);
   sum_3->GetZaxis()->SetLabelFont(42);
   sum_3->GetZaxis()->SetLabelSize(0.035);
   sum_3->GetZaxis()->SetTitleSize(0.035);
   sum_3->GetZaxis()->SetTitleFont(42);
   sum_3->Draw("hist");
   
   TH1D *sumEM_3 = new TH1D("sumEM_3","",40,-25,270);
   sumEM_3->SetBinContent(0,0.0002329307);
   sumEM_3->SetBinContent(1,0.0003292905);
   sumEM_3->SetBinContent(2,0.00126794);
   sumEM_3->SetBinContent(3,0.003975586);
   sumEM_3->SetBinContent(4,0.01242388);
   sumEM_3->SetBinContent(5,0.012745);
   sumEM_3->SetBinContent(6,0.01383526);
   sumEM_3->SetBinContent(7,0.01434223);
   sumEM_3->SetBinContent(8,0.01210107);
   sumEM_3->SetBinContent(9,0.01163876);
   sumEM_3->SetBinContent(10,0.009775873);
   sumEM_3->SetBinContent(11,0.008161468);
   sumEM_3->SetBinContent(12,0.00626553);
   sumEM_3->SetBinContent(13,0.006169788);
   sumEM_3->SetBinContent(14,0.003740745);
   sumEM_3->SetBinContent(15,0.002994815);
   sumEM_3->SetBinContent(16,0.003129302);
   sumEM_3->SetBinContent(17,0.00171578);
   sumEM_3->SetBinContent(18,0.002121325);
   sumEM_3->SetBinContent(19,0.002323673);
   sumEM_3->SetBinContent(20,0.001444722);
   sumEM_3->SetBinContent(21,0.001048188);
   sumEM_3->SetBinContent(22,0.0007861412);
   sumEM_3->SetBinContent(23,0.0006585809);
   sumEM_3->SetBinContent(24,0.0006876973);
   sumEM_3->SetBinContent(25,0.0005622212);
   sumEM_3->SetBinContent(26,0.0002038144);
   sumEM_3->SetBinContent(27,0.0002038144);
   sumEM_3->SetBinContent(28,2.911634e-05);
   sumEM_3->SetBinContent(29,0.0002038144);
   sumEM_3->SetBinContent(30,5.823268e-05);
   sumEM_3->SetBinContent(31,0.000174698);
   sumEM_3->SetBinContent(32,0.0001164654);
   sumEM_3->SetBinContent(33,2.911634e-05);
   sumEM_3->SetBinContent(34,5.823268e-05);
   sumEM_3->SetBinContent(36,2.911634e-05);
   sumEM_3->SetBinContent(38,5.823268e-05);
   sumEM_3->SetBinContent(39,0.0001254761);
   sumEM_3->SetBinContent(40,5.823268e-05);
   sumEM_3->SetBinContent(41,0.0005532105);
   sumEM_3->SetBinError(0,8.235345e-05);
   sumEM_3->SetBinError(1,0.0001472365);
   sumEM_3->SetBinError(2,0.0003120448);
   sumEM_3->SetBinError(3,0.0007631328);
   sumEM_3->SetBinError(4,0.00133272);
   sumEM_3->SetBinError(5,0.001239561);
   sumEM_3->SetBinError(6,0.001364968);
   sumEM_3->SetBinError(7,0.001286686);
   sumEM_3->SetBinError(8,0.001136001);
   sumEM_3->SetBinError(9,0.001047921);
   sumEM_3->SetBinError(10,0.001048535);
   sumEM_3->SetBinError(11,0.0008406617);
   sumEM_3->SetBinError(12,0.0006513418);
   sumEM_3->SetBinError(13,0.0007181381);
   sumEM_3->SetBinError(14,0.0004534794);
   sumEM_3->SetBinError(15,0.0003996788);
   sumEM_3->SetBinError(16,0.0004334058);
   sumEM_3->SetBinError(17,0.000293649);
   sumEM_3->SetBinError(18,0.0003664836);
   sumEM_3->SetBinError(19,0.0005318168);
   sumEM_3->SetBinError(20,0.0002573844);
   sumEM_3->SetBinError(21,0.000174698);
   sumEM_3->SetBinError(22,0.0001512929);
   sumEM_3->SetBinError(23,0.0002082238);
   sumEM_3->SetBinError(24,0.0002102496);
   sumEM_3->SetBinError(25,0.0001687029);
   sumEM_3->SetBinError(26,7.70346e-05);
   sumEM_3->SetBinError(27,7.70346e-05);
   sumEM_3->SetBinError(28,2.911634e-05);
   sumEM_3->SetBinError(29,7.70346e-05);
   sumEM_3->SetBinError(30,4.117672e-05);
   sumEM_3->SetBinError(31,7.132018e-05);
   sumEM_3->SetBinError(32,5.823268e-05);
   sumEM_3->SetBinError(33,2.911634e-05);
   sumEM_3->SetBinError(34,4.117672e-05);
   sumEM_3->SetBinError(36,2.911634e-05);
   sumEM_3->SetBinError(38,4.117672e-05);
   sumEM_3->SetBinError(39,0.0001254761);
   sumEM_3->SetBinError(40,4.117672e-05);
   sumEM_3->SetBinError(41,0.0001269152);
   sumEM_3->SetEntries(153.8286);
   sumEM_3->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   sumEM_3->SetFillColor(ci);
   sumEM_3->SetFillStyle(3002);

   ci = TColor::GetColor("#000099");
   sumEM_3->SetLineColor(ci);
   sumEM_3->GetXaxis()->SetTitle("photon Sum ISO ");
   sumEM_3->GetXaxis()->SetLabelFont(42);
   sumEM_3->GetXaxis()->SetLabelSize(0.035);
   sumEM_3->GetXaxis()->SetTitleSize(0.035);
   sumEM_3->GetXaxis()->SetTitleFont(42);
   sumEM_3->GetYaxis()->SetTitle(" Normalized Entries");
   sumEM_3->GetYaxis()->SetLabelFont(42);
   sumEM_3->GetYaxis()->SetLabelSize(0.035);
   sumEM_3->GetYaxis()->SetTitleSize(0.035);
   sumEM_3->GetYaxis()->SetTitleFont(42);
   sumEM_3->GetZaxis()->SetLabelFont(42);
   sumEM_3->GetZaxis()->SetLabelSize(0.035);
   sumEM_3->GetZaxis()->SetTitleSize(0.035);
   sumEM_3->GetZaxis()->SetTitleFont(42);
   sumEM_3->Draw("same hist");
      tex = new TLatex(0.27,0.85,"80GeV < p_{T}^{#gamma} < 9999GeV, ");
tex->SetNDC();
   tex->SetTextFont(63);
   tex->SetTextSize(15);
   tex->Draw();
   c4_4->Modified();
   c4->cd();
   c4->Modified();
   c4->cd();
   c4->SetSelected(c4);
}
