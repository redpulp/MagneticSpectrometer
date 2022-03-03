## Magnetic Spectrometer

#### Goal of the simulation

This simulation aims to evaluate how the Bending Power of an isotropic magnetic field varies with the initial momentum of the particles that interact with it.

In our case, the particles will be protons beams distibuted as p<sup>-3</sup>, where p is the initial momentum and has 5 values: 0.1, 1, 10, 100 and 1000 GeV. The particles will be generated from a 3.9m sided square, and the detector, will be a cylinder with height and diameter of 1m, 1.95m away from the square.

We will also measure the efficiency of the detector as the squared portion of particles that traverse the whole cylinder.

#### Particles generation

We will generate a random value for the initial momentum and the angle of its trajectory.
Thanks to relativity we know that

![equation](http://www.sciweavers.org/tex2img.php?eq=%20%5Cfrac%7Bv%7D%7Bc%7D%20%3D%20%20%5Cbeta%20%3D%20%20%5Cfrac%7Bpc%7D%7BE%7D%20&bc=White&fc=Black&im=jpg&fs=12&ff=arev&edit=0)

where

![equation](http://www.sciweavers.org/tex2img.php?eq=E%20%3D%20%20%5Csqrt%5B%5D%7B%20m%5E%7B2%7Dc%5E%7B4%7D%20%2B%20p%5E%7B2%7Dc%5E%7B2%7D%20%7D%20&bc=White&fc=Black&im=jpg&fs=12&ff=arev&edit=0)

In our system we will consider c = 1, q = 1 and m = 1. For this reason:

![equation](http://www.sciweavers.org/tex2img.php?eq=v%20%3D%20%20%5Cfrac%7Bp%7D%7B1%20%2B%20p%5E%7B2%7D%20%7D%20&bc=White&fc=Black&im=jpg&fs=12&ff=arev&edit=0)

We can get the velocity 3D vector modules as

![equation](http://www.sciweavers.org/tex2img.php?eq=%20v_%7Bx%7D%20%3D%20v%20%20%20%20%2Acos%20%20%5Cphi%20%20%20%5Csqrt%7B1-%20cos%5E%7B2%7D%20%5Ctheta%20%7D%20&bc=White&fc=Black&im=jpg&fs=12&ff=arev&edit=0)

![equation](http://www.sciweavers.org/tex2img.php?eq=%20v_%7By%7D%20%3D%20v%20%20%20%20%2Asin%5Cphi%20%20%20%5Csqrt%7B1-%20cos%5E%7B2%7D%20%5Ctheta%20%7D%20&bc=White&fc=Black&im=jpg&fs=12&ff=arev&edit=0)

![equation](http://www.sciweavers.org/tex2img.php?eq=%20v_%7Bz%7D%20%3D%20v%20%20%20%20%20%2A%20%5Cphi%20%20%5Csqrt%7Bcos%5E%7B2%7D%20%5Ctheta%20%7D%20&bc=White&fc=Black&im=jpg&fs=12&ff=arev&edit=0)

Where 0 < ϕ < 2π.

#### Motion

Given the following system

![equation](http://www.sciweavers.org/tex2img.php?eq=%5Cbegin%7Bcases%7D%5Cdot%7Bv%7D_%7Bx%7D%20%3D%20%28v_%7By%7DB_%7Bz%7D-v_%7Bz%7DB_%7By%7D%29%20%20%5C%5C%20%5Cdot%7Bv%7D_%7By%7D%3D%20%28v_%7Bz%7DB_%7Bx%7D-v_%7Bx%7DB_%7Bz%7D%29%5C%5C%20%5Cdot%7Bv%7D_%7Bz%7D%20%3D%20%28v_%7Bx%7DB_%7By%7D-v_%7By%7DB_%7Bx%7D%29%5Cend%7Bcases%7D%20&bc=White&fc=Black&im=jpg&fs=12&ff=arev&edit=0)

We can use the Midpoint method to calculate the velocity components, which are interdependent. This method gives us an error of O(h³), where h is the resolution used to solve the differential equation.

So, given the following equation to describe the position variation

![equation](http://www.sciweavers.org/tex2img.php?eq=%20%5Cfrac%7Bdy_%7Bi%7D%7D%7Bdt%7D%20%20%3D%20f%28t%2C%20y_%7B1%7D...y_%7Bn%7D%29&bc=White&fc=Black&im=jpg&fs=12&ff=modern&edit=0)

We can update the components with the following formula

![equation](http://www.sciweavers.org/tex2img.php?eq=y_%7Bn%2B1%7D%3Dy_%7Bn%7D%20%2B%20hf%28x_%7Bn%7D%2B%20%5Cfrac%7Bh%7D%7B2%7Df%28x_%7Bn%7D%2Cy_%7Bn%7D%29%2C%20%20y_%7Bn%7D%2B%20%5Cfrac%7Bh%7D%7B2%7Df%28x_%7Bn%7D%2Cy_%7Bn%7D%29%29%20&bc=White&fc=Black&im=jpg&fs=12&ff=modern&edit=0)

#### Bending Power

The Bending Power is defined as

![equation](http://www.sciweavers.org/tex2img.php?eq=%20%5CDelta%20p%20%3D%20%20%5Csqrt%7B%20%5CDelta%20p_%7Bx%7D%5E%7B2%7D%20%2B%20%5CDelta%20p_%7By%7D%5E%7B2%7D%20%2B%20%5CDelta%20p_%7Bz%7D%5E%7B2%7D%7D%20&bc=White&fc=Black&im=jpg&fs=12&ff=modern&edit=0)

where

![equation](http://www.sciweavers.org/tex2img.php?eq=%5CDelta%20p_%7Bx%7D%20%3D%20q%28%20%5Cint%20B_%7Bz%7D%20dy%20-%20%5Cint%20B_%7By%7Ddz%29&bc=White&fc=Black&im=jpg&fs=12&ff=modern&edit=0)

![equation](http://www.sciweavers.org/tex2img.php?eq=%5CDelta%20p_%7By%7D%20%3D%20q%28%20%5Cint%20B_%7Bx%7D%20dz%20-%20%5Cint%20B_%7Bz%7Ddx%29&bc=White&fc=Black&im=jpg&fs=12&ff=modern&edit=0)

![equation](http://www.sciweavers.org/tex2img.php?eq=%5CDelta%20p_%7Bz%7D%20%3D%20q%28%20%5Cint%20B_%7By%7D%20dx%20-%20%5Cint%20B_%7Bx%7Ddy%29&bc=White&fc=Black&im=jpg&fs=12&ff=modern&edit=0)

With a conservative field that is independent from the position, we can calculate the integrals with B as fixed and the extremes of the particles' trajectory as the extremes of integration.
