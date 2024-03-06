#include "header.h"

// To solve the motion equation
double vadd(double v1, double v2, double B1, double B2)
{
  return B2 * v1 - B1 * v2;
}

// To follow the entire particles' trajectory and extract data
void generate_particles(unsigned short int n, int N, int *efficiency, TH1 *h1)
{
  // Initial momentum distribution
  int power = -3;
  // Magnetic field components
  double Bx = 0, By = 0.3, Bz = 0;

  double square_size = 3.9;
  double cylinder_base_z = 1.95;

  TRandom3 *rg = new TRandom3(0);
  
  #pragma omp parallel for
  for (int i = 0; i < N; i++) {
    // Every particle will be associated to the extremes of its path inside the detector
    double ax, ay, az, bx, by, bz;

    // Final values to eval
    double p0;
    // Generating initial particle position
    double x = rg->Uniform(-square_size, square_size);
    double y = rg->Uniform(-square_size, square_size);
    double z = 0;

    // n will determine the distribution of initial momentum
    if (n == 0)
      p0 = rg->Uniform(0.1, max_momentum);
    else
      p0 = 0.01 * (pow(10, n));

    // Generating initial direction and velocity
    double modv = p0 / (sqrt(1 + p0));
    double phi = rg->Uniform(0, 6.283);
    double costh = rg->Rndm();
    double vx = modv * (sqrt(1 - costh)) * sin(phi);
    double vy = modv * (sqrt(1 - costh)) * cos(phi);
    double vz = modv * (sqrt(costh));

    // Position after straight trajectory to reach the cylinder
    x += (vx * cylinder_base_z) / vz;
    y += (vy * cylinder_base_z) / vz;
    z = cylinder_base_z;

    double vx0, vy0, vz0;

    // If the particle is inside the cylinder, start calculating bended trajectory
    if (pow(x, 2) + pow(y, 2) <= 0.25) {
      //Calculating the Bending Power for the particles inside the detector
      ax = x;
      ay = y;
      az = z;
      while (pow(x, 2) + pow(y, 2) <= 1) {
        vx0 = vx;
        vy0 = vy;
        vz0 = vz;

        vx = vx0 + h * vadd
        (
          vy0 + (h / 2) * vadd(vy0, vz0, By, Bz),
          vz0 + h / 2 * vadd(vy0, vz0, By, Bz),
          By,
          Bz
        );

        vy = vy0 + h * vadd
        (
          vz0 + (h / 2) * vadd(vz0, vx0, Bz, Bx),
          vx0 + h / 2 * vadd(vy0, vz0, Bz, Bx),
          Bz,
          Bx
        );

        vz = vz0 + h * vadd
        (
          vx0 + (h / 2) * vadd(vx0, vy0, Bx, By),
          vy0 + h / 2 * vadd(vx0, vy0, Bx, By),
          Bx,
          By
        );

        x += h * (vx + h / 2 * vx);
        y += h * (vy + h / 2 * vy);
        z += h * (vz + h / 2 * vz);
        //The fraction of particles passing through the whole detector will define its efficiency
        if (z >= 2.95) {
          int index = std::min((int)((p0 / max_momentum) * (eff_dist_steps)), eff_dist_steps - 1);
          efficiency[index]++;
          break;
        }
        bx = x;
        by = y;
        bz = z;
        //Calculating the Bending Power using the components of the variation of the momentum
        double BPx = ((bz - az) * By) - ((by - ay) * Bz);
        double BPy = ((bx - ax) * Bz) - ((bz - az) * Bx);
        double BPz = ((by - ay) * Bx) - ((bx - ax) * By);
        double bending_power = sqrt(pow(BPx, 2) + pow(BPy, 2) + pow(BPz, 2));
        h1->Fill(bending_power, pow(p0, power));
      }
    }

  }
}
