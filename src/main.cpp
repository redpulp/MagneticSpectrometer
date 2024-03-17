#include "header.h"
using namespace std;
int main(int argc, char **argvw)
{
  TApplication theApp("App", &argc, argvw);
  const int N = 10000;  // Number of protons generated for the simulation
  double p0[N];
  double BP[N];
  int eff[10] = {0};
  bool pass[N];
  unsigned short int n = 0;

  //Filling the Bending Power histogram
  int power = -3;
  TH1 *h1 = new TH1D("data", "Bending Power", 100, 0, 2);
  h1->GetXaxis()->SetTitle("BP");
  for(int i = 0; i < 1000; i++) {
    for(int j = 0; j < N; j++)
      pass[j] = false;
    generate(n, N, p0, eff, pass, BP);
    for (int k = 0; k < N; k++)
      if (pass[k])
        h1->Fill(BP[k], pow(p0[k], power));
  }

  //Graphing the efficiency of the detector
  const int steps = 10;
  double p0x[steps], p0y[steps];
  for (int i = 0; i < steps; i++) {
    p0x[i] = (i + 1) * 100;
    double cy = (double)(eff[i]);
    p0y[i] = cy / 1000000;
  }
  p0x[0] = 0.1;
  TGraph *gr1 = new TGraph(steps, p0x, p0y);
  gr1->SetTitle("Efficiency");
  gr1->GetXaxis()->SetTitle("p (GeV)");
  gr1->SetMarkerColor(4);
  gr1->SetMarkerStyle(7);

  //Graphing mean and SD
  double mean[N], std[N];
  TH1 *ms = new TH1D("0", "mean", 1000, 0, 10);
  for (int i = 0; i < 5; i++) {
    n++;
    generate(n, N, p0, eff, pass, BP);
    for (int j = 0; j < 1000; j++)
      for (int k = 0; k < N; k++)
        ms->Fill(BP[j]);
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

  //Canvas set-up
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
  gr3->Draw("ALP");
  c->cd();
  TPad *pad4 = new TPad("pad4", "pad4", 0.5, 0, 1, 0.5);
  pad4->Draw();
  pad4->cd();
  gr4->Draw("ALP");
  c->cd();
  c->Update();
  c->Modified();
  c->Connect("Closed()", "TApplication", gApplication, "Terminate()");
  //theApp.Run(); //Use this command to open canvas interactively
  c->SaveAs("graph.png");
}
