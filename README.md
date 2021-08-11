## Magnetic-Spectrometer 
A simulation based on the experiment AMS-02, made to study the bending power and efficiency of the spectrometer when hit with an isotropic beam of protons.  

The number of protons generated in the beam is initialised in `main.cpp` as `N`. The resolution used to resolve the differential equation is initialised through the step `h` in `header.h`.

## How to run locally

docker exec -t -i magnetic-spectrometer /bin/bash

This project was built to use Docker as a Makefile that will output the resulting graphs in `/output/graph.png`

Build the image
```
docker build -t luciomoriconi/magnetic-spectrometer .
```
Run the container
```
docker run -d --rm -it --name magnetic-spectrometer luciomoriconi/magnetic-spectrometer
```
Get the result of the simulation
```
docker cp magnetic-spectrometer:/src/graph.png ${PWD}/output/graph.png
```
Kill the container and delete the image
```
docker kill magnetic-spectrometer
docker image rm luciomoriconi/magnetic-spectrometer
```