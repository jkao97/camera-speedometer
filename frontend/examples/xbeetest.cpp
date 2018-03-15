#include <iostream>
#include <thread>
#include <cassert>
#include <chrono>
#include <unistd.h>
#include <string.h>
#include <string>

#include "../include/Utility.hpp"
#include "../src/Utility.cpp"
#include "../include/SerialXbee.hpp"
#include "../include/TransmitRequest.hpp"
#include "../include/Xbee.hpp"

#include "../include/TransmitRequest.hpp"

using namespace XBEE;
using namespace std;

#define QUAD_MAC 0x0

void CallbackFunction(XBEE::Frame *item) {
    std::cout << "messaged received" << std::endl;
    std::cout << "speed: " << item->GetData();
}

int main(int argc, char* argv[]) {
    XBEE::SerialXbee xbee_interface;
    xbee_interface.Connect();
    xbee_interface.ReadHandler = std::bind(&CallbackFunction, std::placeholders::_1);
}
