docker build -t luciomoriconi/magnetic-spectrometer .
docker run -d --rm -it --name magnetic-spectrometer luciomoriconi/magnetic-spectrometer
docker cp magnetic-spectrometer:/src/graph.png ${PWD}/output/graph.png
docker kill magnetic-spectrometer
docker image rm luciomoriconi/magnetic-spectrometer