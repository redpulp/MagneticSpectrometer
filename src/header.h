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
#define eff_dist_steps 10
#define max_momentum 1000

void generate_particles(unsigned short int n, int N, int *efficiency, TH1 *h1);

double vadd(double v1,double v2,double B1,double B2);
