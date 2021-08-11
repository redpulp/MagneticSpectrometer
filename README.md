## Magnetic-Spectrometer 
A simulation based on the experiment AMS-02, made to study the bending power and efficiency of the spectrometer when hit with an isotropic beam of protons.  

The number of protons generated in the beam is initialised in `main.cpp` as `N`. The resolution used to resolve the differential equation is initialised through the step `h` in `header.h`. 

The CERN software ROOT must be installed to build the executable. Any version after 5.34/00 will work.

## How to run locally

docker exec -t -i magnetic-spectrometer /bin/bash

```
docker build -t luciomoriconi/magnetic-spectrometer .
docker run -d --rm -it --name magnetic-spectrometer luciomoriconi/magnetic-spectrometer
docker cp magnetic-spectrometer:/src/graph.png ${PWD}/output/graph.png
docker kill magnetic-spectrometer
```