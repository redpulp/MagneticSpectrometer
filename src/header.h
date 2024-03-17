#include "TH1.h"
#include "TH1D.h"
#include <TCanvas.h>
#include <TPad.h>
#include <TGraph.h>
#include <TApplication.h>
#include <TFile.h>
#include <cmath>
#include "TRandom3.h"

#define h 0.001 // Resolution used to resolve the differential equations

void generate(unsigned short int n, int N, double *p0, int *eff, bool *pass, double *BP);

double vadd(double v1,double v2,double B1,double B2);
