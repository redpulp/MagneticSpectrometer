R_LDFLAGS =     `root-config --ldflags`
R_LIBS    =     `root-config --libs`
R_CFLAGS  =     `root-config --cflags`
R_ALL     =     $(R_LDFLAGS) $(R_LIBS)
CXX      := g++
CXXP     := g++ -c
CXXFLAGS := -O -Wall #-pedantic

specter: main.o beam.o
	$(CXX) main.o beam.o $(R_LIBS) -o specter

beam.o: beam.cpp header.h
	$(CXXP) $(CXXFLAGS) beam.cpp $(R_CFLAGS)

main.o: main.cpp header.h
	$(CXXP) $(CXXFLAGS) main.cpp $(R_CFLAGS)

default: specter
