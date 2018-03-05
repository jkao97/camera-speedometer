CXX=g++
CXXFLAGS=-std=c++11 -Wall -O3 -g

all: speedometer

speedometer: CV.o
	$(CXX) $(CXXFLAGS) -o speedometer main.cpp CV.o

CV.o:
	$(CXX) $(CXXFLAGS) -o CV.o CV.cpp -c
	