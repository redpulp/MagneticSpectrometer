#include "header.h"
using namespace std;

double vadd(double v1,double v2,double B1,double B2) {
  double v = B2*v1-B1*v2;
  return v;
}
void generate(unsigned short int n,int N, double *p0, int *eff, bool *pass, double *BP) {
  //Defining the magnetic field's components
  double Bx = 0, By = 0.3, Bz = 0;
  
  //Particle beam properties
  double modv,phi,costh,vx,vy,vz,x,y,z;
  
  //Every particle will be associated to the extrems of their paths inside the detector
  double ax,ay,az,bx,by,bz;

  TRandom3* rg = new TRandom3(0);
  for(int i=0;i<N;i++) {
    
    //n will determine the distribution of initial momentum
    if(n==0)
      p0[i] = rg->Uniform(0.1,1000);
    else
      p0[i] = 0.01*(pow(10,n));
    modv = p0[i]/(sqrt(1+p0[i]));
    phi = rg->Uniform(0,6.283);
    costh = rg->Rndm();
    vx = modv*(sqrt(1-costh))*sin(phi);
    vy = modv*(sqrt(1-costh))*cos(phi);
    vz = modv*(sqrt(costh));
    x = rg->Uniform(-3.9,3.9);
    y = rg->Uniform(-3.9,3.9);
    z = 1.95;
    
    double vx0, vy0, vz0;
    z=1.95;
    x=x+(vx*1.95)/vz;
    y=y+(vy*1.95)/vz;
    if(pow(x,2)+pow(y,2)<=0.25) {
      
      //Calculating the Bending Power for particles inside the detector
      pass[i]=1;      
      ax=x;
      ay=y;
      az=z;
	while(pow(x,2)+pow(y,2)<=1) {
	 vx0=vx;
	 vy0=vy;
	 vz0=vz;
	 vx = vx0+h*vadd(vy0+(h/2)*vadd(vy0,vz0,By,Bz),vz0+h/2*vadd(vy0,vz0,By,Bz),By,Bz);
	 vy = vy0+h*vadd(vz0+(h/2)*vadd(vz0,vx0,Bz,Bx),vx0+h/2*vadd(vy0,vz0,Bz,Bx),Bz,Bx);
	 vz = vz0+h*vadd(vx0+(h/2)*vadd(vx0,vy0,Bx,By),vy0+h/2*vadd(vx0,vy0,Bx,By),Bx,By);
	 x = x+h*(vx+h/2*vx);
	 y = y+h*(vy+h/2*vy);
	 z = z+h*(vz+h/2*vz);
	 //The fraction of particles passing through the whole detector will define its efficiency
         if(z>=2.95) {
	   int cy = (int) (p0[i]/100);
	   eff[cy]++;
	   break;
	 }
       }
       bx=x;
       by=y;
       bz=z;
       //Calculating the Bending Power using the components of the variation of the momentum
       double BPx = ((bz-az)*By)-((by-ay)*Bz);
       double BPy = ((bx-ax)*Bz)-((bz-az)*Bx);
       double BPz = ((by-ay)*Bx)-((bx-ax)*By);
       BP[i] = sqrt(pow(BPx,2)+pow(BPy,2)+pow(BPz,2));
    }
  }
}
    
