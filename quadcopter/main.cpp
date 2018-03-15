/*

*/

#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/imgproc.hpp>

#include <chrono>
#include <thread>
#include <sstream>

#include <raspicam/raspicam_cv.h>

#include "CV.hpp"

#include <SerialXbee.hpp>
#include <ReceivePacket.hpp>
#include <TransmitRequest.hpp>

#define GCS_MAC 0x0

static void setupCamera(raspicam::RaspiCam_Cv &cam)
{
    /*
    cam.set(CV_CAP_PROP_FRAME_WIDTH, configs->cam_Width);
    cam.set(CV_CAP_PROP_FRAME_HEIGHT, configs->cam_Height);
    cam.set(CV_CAP_PROP_FORMAT, CV_8UC3);
    cam.set(CV_CAP_PROP_BRIGHTNESS, BRIGHTNESS);
    cam.set(CV_CAP_PROP_CONTRAST, CONTRAST);
    cam.set(CV_CAP_PROP_SATURATION, SATURATION);
    cam.set(CV_CAP_PROP_GAIN, GAIN);
    */

    if (!cam.open())
    {
    fprintf(stderr, "\nCamera has not been opened. Exiting...\n");
    throw std::runtime_error("Camera failed to open.\n");
    exit(EXIT_FAILURE);
    }
}

int sendSpeed(double speed, XBEE::SerialXbee &xbee_interface) {
    XBEE::TransmitRequest frame_gcs(GCS_MAC);

    std::ostringstream strs;
    strs << speed;
    std::string str = strs.str();

    frame_gcs.setData(str);
    xbee_interface.ASyncWriteFrame(&frame_gcs);
}

int main(int argc, char **argv) {

    raspicam::RaspiCam_Cv cam;
    auto oldTime;
    cv::Mat image;
    std::vector<cv::KeyPoint> oldKeys, newKeys;
    std::vector<cv::Mat> oldDescs, newDescs;
    double distance, speed;
    unsigned int iterations = 0;

    setupCamera(cam);
    cam.grab();

    while(1) {
        cam.grab();
        auto newTime = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        cam.retrieve(image);
        
        newKeys = keyDetect(image);
        newDescs = descDetect(image, newKeys);
        
        if(iterations) {
            distance = calculateDistance(newKeys, oldKeys, newDescs, oldDescs);
            speed = distance / ((newTime - oldTime) / 1000);
            sendSpeed(speed);
        }

        oldTime = newTime;
        iterations++;
        
    }
    return 0;
}
