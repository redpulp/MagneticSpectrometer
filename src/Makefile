R_LDFLAGS =     `root-config --ldflags`
R_LIBS    =     `root-config --libs`
R_CFLAGS  =     `root-config --cflags`
R_ALL     =     $(R_LDFLAGS) $(R_LIBS)
CXX      := g++
CXXP     := g++ -c
CXXO		 := -fopenmp
CXXFLAGS := -O -Wall -pedantic

specter: main.o beam.o
	$(CXX)  $(CXXO) main.o beam.o $(R_LIBS) -o specter

beam.o: beam.cpp header.h
	$(CXXP) $(CXXFLAGS) $(CXXO) beam.cpp $(R_CFLAGS)

main.o: main.cpp header.h
	$(CXXP) $(CXXFLAGS) $(CXXO) main.cpp $(R_CFLAGS)

default: specter
