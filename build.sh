mkdir output
echo "Building and running the image"
docker build -t redpulp/magnetic-spectrometer .
docker run -d --rm -it --name magnetic-spectrometer redpulp/magnetic-spectrometer
echo "Getting the results of the simulation"
docker cp magnetic-spectrometer:/src/graph.png ${PWD}/output/graph.png
echo "Killing container and deleting image"
docker kill magnetic-spectrometer
# docker image rm redpulp/magnetic-spectrometer