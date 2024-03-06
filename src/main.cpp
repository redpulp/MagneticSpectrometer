#include "header.h"

int main(int argc, char **argvw)
{
  TApplication theApp("App", &argc, argvw);
  const int N = 100000;  // Number of protons generated for a signle simulation
  const int iter_N = 10000; // Iterations of the simulation

  int efficiency[eff_dist_steps] = {};
  // bool pass[N];
  unsigned short int init_momentum = 0;

  // Filling the Bending Power histogram
  TH1 *h1 = new TH1D("data", "Bending Power", 200, 0, 1);
  h1->GetXaxis()->SetTitle("BP");

  for (int i = 0; i < iter_N; i++) {
    generate_particles(init_momentum, N, efficiency, h1);
  }

  // Graphing the efficiency of the detector
  double p0x[eff_dist_steps], p0y[eff_dist_steps];
  for (int i = 0; i < eff_dist_steps; i++) {
    p0x[i] = (i + 1) * (max_momentum / eff_dist_steps);
    p0y[i] = (double)(efficiency[i]) / (N * iter_N);
  }
  TGraph *gr1 = new TGraph(eff_dist_steps, p0x, p0y);

  TF1* fitFunc = new TF1("fitFunc", "[0]*x + [1]", 0, 6);
  fitFunc->SetParameters(1, 0);
  gr1->Fit(fitFunc, "Q");

  gr1->SetTitle("Efficiency");
  gr1->GetXaxis()->SetTitle("p (GeV)");
  gr1->SetMarkerColor(4);
  gr1->SetMarkerStyle(7);

  // Graphing mean and SD
  double mean[N], std[N];
  TH1 *ms = new TH1D("0", "mean", 1000, 0, 10);

  for (int i = 0; i < 5; i++) {
    init_momentum++;
    generate_particles(init_momentum, N, efficiency, ms);
    mean[i] = ms->GetMean();
    std[i] = ms->GetStdDev();
    ms->Reset();
  }

  double P0X[5] = {0.1, 1, 10, 100, 1000};
  TGraph *gr3 = new TGraph(5, P0X, mean);
  gr3->SetTitle("Mean");
  gr3->GetXaxis()->SetTitle("p0 (GeV)");
  gr3->SetMarkerColor(4);
  gr3->SetMarkerStyle(7);
  TGraph *gr4 = new TGraph(5, P0X, std);
  gr4->SetTitle("Standard Deviation");
  gr4->GetXaxis()->SetTitle("p0 (GeV)");
  gr4->SetMarkerColor(4);
  gr4->SetMarkerStyle(7);

  // Canvas set-up
  TCanvas *c = new TCanvas();
  TPad *pad1 = new TPad("pad1", "pad 1", 0, 0.5, 0.5, 1);
  pad1->Draw();
  pad1->cd();
  gr1->Draw("ALP");
  c->cd();
  TPad *pad2 = new TPad("pad2", "pad2", 0.5, 0.5, 1, 1);
  pad2->Draw();
  pad2->cd();
  h1->Draw("HIST");
  c->cd();
  TPad *pad3 = new TPad("pad3", "pad3", 0, 0, 0.5, 0.5);
  pad3->Draw();
  pad3->cd();
  pad3->SetLogx();
  gr3->Draw("ALP");
  c->cd();
  TPad *pad4 = new TPad("pad4", "pad4", 0.5, 0, 1, 0.5);
  pad4->Draw();
  pad4->cd();
  pad4->SetLogx();
  gr4->Draw("ALP");
  c->cd();
  c->Update();
  c->Modified();
  c->SetCanvasSize(1600, 1200);  // Set the canvas size to double the resolution (adjust as needed)
  c->SetWindowSize(1600 + (1600 - c->GetWw()), 1200 + (1200 - c->GetWh()));
  c->Connect("Closed()", "TApplication", gApplication, "Terminate()");
  //theApp.Run(); // Use this command to open canvas interactively
  c->SaveAs("graph.png");
}
