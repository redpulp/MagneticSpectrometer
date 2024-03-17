## Magnetic-Spectrometer

A simulation based on the experiment AMS-02, made to study the bending power and efficiency of a spectrometer when hit with an isotropic beam of protons.

Two parameters can be tweaked to play with the resolution of the simulation:

- `N` (initialised in `main.cpp`) - the number of protons generated in the beam
- `h` (initialised in `header.h`) - the resolution used to solve the differential equation in `beam.cpp`

## The simulation

An extensive description of how the simulation works, and its results, can be found in [simulation.md](simulation.md). The ROOT library it's used for random numbers generation and data analysis.

## How to run

This project was built to use Docker as a Makefile that will output the resulting graphs in `/output/graph.png`, run `build.sh` to build and generate the output. A rundown of what's inside the build file can be found below.

Create directory for the output

```
mkdir output
```

Build and run the image

```
docker build -t luciomoriconi/magnetic-spectrometer .
docker run -d --rm -it --name magnetic-spectrometer luciomoriconi/magnetic-spectrometer
```

Get the result of the simulation (change the destination path to `%cd%/output/graph.png` if you're using Command Prompt)

```
docker cp magnetic-spectrometer:/src/graph.png ${PWD}/output/graph.png
```

Kill the container and delete the image

```
docker kill magnetic-spectrometer
docker image rm luciomoriconi/magnetic-spectrometer
```
