## Magnetic-Spectrometer 
A simulation based on the experiment AMS-02, made to study the bending power and efficiency of the spectrometer when hit with an isotropic beam of protons.  

Two parameters can be tweaked to play with the resolution of the simulation:
- `N` (initialised in `main.cpp`) - the number of protons generated in the beam
- `h` (initialised in `header.h`) - the resolution used to solve the differential equation in `beam.cpp`

## How to run locally

docker exec -t -i magnetic-spectrometer /bin/bash

This project was built to use Docker as a Makefile that will output the resulting graphs in `/output/graph.png`

Build and run the image
```
docker build -t luciomoriconi/magnetic-spectrometer .
docker run -d --rm -it --name magnetic-spectrometer luciomoriconi/magnetic-spectrometer
```
Get the result of the simulation (Change the destination path to %cd%/output/graph.png if you're using Command Prompt)
```
docker cp magnetic-spectrometer:/src/graph.png ${PWD}/output/graph.png
```
Kill the container and delete the image
```
docker kill magnetic-spectrometer
docker image rm luciomoriconi/magnetic-spectrometer
```

The list of commands can be found in `build.sh`. 
If you're using Git Bash in your terminal, you might some issues if you use the commands separately, so I suggest using `build.sh`
