/*

*/

#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/imgproc.hpp>

#include <chrono>
#include <ctime>
#include <sstream>
#include <iostream>

#include <raspicam/raspicam_cv.h>

#include "CV.hpp"

#include <SerialXbee.hpp>
#include <ReceivePacket.hpp>
#include <TransmitRequest.hpp>

#define CAM_WIDTH 1280
#define CAM_HEIGHT 720
#define BRIGHTNESS 50.0f
#define CONTRAST 50.0f
#define SATURATION 50.0f
#define GAIN 50.0f

#define GCS_MAC 0x0

static void setupCamera(raspicam::RaspiCam_Cv &cam)
{
    cam.set(CV_CAP_PROP_FRAME_WIDTH, CAM_WIDTH);
    cam.set(CV_CAP_PROP_FRAME_HEIGHT, CAM_HEIGHT);
    cam.set(CV_CAP_PROP_FORMAT, CV_8UC3);
    cam.set(CV_CAP_PROP_BRIGHTNESS, BRIGHTNESS);
    cam.set(CV_CAP_PROP_CONTRAST, CONTRAST);
    cam.set(CV_CAP_PROP_SATURATION, SATURATION);
    cam.set(CV_CAP_PROP_GAIN, GAIN);

    if (!cam.open()) {
        fprintf(stderr, "\nCamera has not been opened. Exiting...\n");
        throw std::runtime_error("Camera failed to open.\n");
        exit(EXIT_FAILURE);
    }
}

void sendSpeed(double speed, XBEE::SerialXbee &xbee_interface) {
    XBEE::TransmitRequest frame_gcs(GCS_MAC);

    std::ostringstream strs;
    strs << speed;
    std::string str = strs.str();

    std::cout << "Writing message: " << str << std::endl;

    frame_gcs.SetData(str);
    xbee_interface.AsyncWriteFrame(&frame_gcs);
}

int main(int argc, char **argv) {

    raspicam::RaspiCam_Cv cam;
    auto now = std::chrono::system_clock::now();
    auto oldTime = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    cv::Mat image;
    std::vector<cv::KeyPoint> oldKeys, newKeys;
    cv::Mat oldDescs, newDescs;
    double distance, speed;
    unsigned int iterations = 0;

    XBEE::SerialXbee xbee_interface;
    xbee_interface.Connect();

    setupCamera(cam);
    cam.grab();
    cam.retrieve(image);
    cv::cvtColor(image, image, cv::COLOR_RGB2BGR);
    cv::imwrite("test.png", image);

    while(1) {
        cam.grab();
        now = std::chrono::system_clock::now();
        auto newTime = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        cam.retrieve(image);

        newKeys = keyDetect(image);
        std::cout << "Number of keys: " << newKeys.size() << std::endl;

        std::cout << "Desc Detect" << std::endl;
        newDescs = descDetect(image, newKeys);
        
        if(iterations) {
            std::cout << "Calculate Distance" << std::endl;
            distance = calculateDistance(newKeys, oldKeys, newDescs, oldDescs);
            std::cout << "distance: " << distance << std::endl;

            long duration = (std::chrono::duration_cast<std::chrono::milliseconds>(newTime - oldTime)).count();
            std::cout << "duration: " << duration << std::endl;

            speed = distance / (((float)duration) / 1000);

            sendSpeed(speed, xbee_interface);
        }

        oldTime = newTime;
        oldKeys = newKeys;
        oldDescs = newDescs;
        iterations++;
        
    }
    return 0;
}
