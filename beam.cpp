#include "header.h"
using namespace std;

double vadd(double v1,double v2,double B1,double B2) {
  double v = B2*v1-B1*v2;
  return v;
}
void generate(unsigned short int n,int N, double *p0, int *eff, bool *pass, double *BP) {
  //definisco le componenti del campo magnetico
  double Bx = 0, By = 0.3, Bz = 0;
  
  //genero un fascio di particelle con le seguenti proprietà
  double modv,phi,costh,vx,vy,vz,x,y,z;
  
  //associo ad ogni particella gli estremi della traiettoria compiuta all'interno del cilindro
  double ax,ay,az,bx,by,bz;

  TRandom3* rg = new TRandom3(0);
  for(int i=0;i<N;i++) {
    
    //il valore n determina l'utilizzo della funzione: se n=0 genera un flusso di particelle con momento iniziale uniformemente distribuito nell'intervallo [0.1,1000]; per altri valori di n genera particelle con momento iniziale determinato per 5 valori (0.1,1,10,100,1000)
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
    
    //definisco delle variabili dove salvare le componenti di v che verranno utilizzate per aggiornarle tutte contemporaneamente
    double vx0, vy0, vz0;
    z=1.95;
    x=x+(vx*1.95)/vz;
    y=y+(vy*1.95)/vz;
    if(pow(x,2)+pow(y,2)<=0.25) {
      
      //segno quali particelle entrano nel cilindro per sapere quali usare per calcolare il Bending Power
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
	 //le particelle che attraversano tutta la lunghezza del cilindro senza uscire dai bordi andranno a contribuire al valore dell'efficienza del rivelatore
         if(z>=2.95) {
	   int cy = (int) (p0[i]/100);
	   eff[cy]++;
	   break;
	 }
       }
       bx=x;
       by=y;
       bz=z;
       //calcolo il Bending Power a partire dalle componenti della variazione di momento
       double BPx = ((bz-az)*By)-((by-ay)*Bz);
       double BPy = ((bx-ax)*Bz)-((bz-az)*Bx);
       double BPz = ((by-ay)*Bx)-((bx-ax)*By);
       BP[i] = sqrt(pow(BPx,2)+pow(BPy,2)+pow(BPz,2));
    }
  }
}
    
