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

void CallbackFunction(XBEE::Frame *item) {
    XBEE::ReceivePacket *r_packet = dynamic_cast<XBEE::ReceivePacket *>(item);
    std::cout << "messaged received" << std::endl;
    std::cout << "speed: " << r_packet->GetData();
}

int main(int argc, char* argv[]) {
    XBEE::SerialXbee xbee_interface;
    xbee_interface.Connect();
    xbee_interface.ReadHandler = std::bind(&CallbackFunction, std::placeholders::_1);

    while(1) {

    }

    return 0;
}
