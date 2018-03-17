CXX=g++
CXXFLAGS=-std=c++11 -Wall -O3 -g
OPENCV = -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_features2d

all: speedometer

speedometer: CV.o
	$(CXX) $(CXXFLAGS) -o speedometer main.cpp CV.o -lraspicam -lraspicam_cv -I/usr/local/include -lpthread -Ixbeeplus/include -Lxbeeplus/build -lxbee_plus $(OPENCV) -lboost_system -lboost_thread -lxbee_plus

CV.o:
	$(CXX) $(CXXFLAGS) -o CV.o CV.cpp -c $(OPENCV)

clean:
	rm -rf CV.O
	rm -rf speedometer
	