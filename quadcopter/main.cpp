/*

*/

#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/imgproc.hpp>

#include <chrono>
#include <thread>

#include <raspicam/raspicam_cv.h>

#include "CV.hpp"


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

int sendMessage(double speed) {

}

int main(int argc, char **argv) {

    raspicam::RaspiCam_Cv cam;
    std::chrono::time_point<std::chrono::system_clock> oldTime, newTime;
    cv::Mat image;
    std::vector<cv::KeyPoint> oldFeatures, newFeatures;
    double distance, speed;

    setupCamera(cam);

    while(1) {
        cam.grab();
        newTime = std::chrono::system_clock::now();
        cam.retrieve(image);
        cv::imwrite("image.jpg", image);
        return 0;
        /*
        newFeatures = getFeatures(&image);
        distance = getDistance(newFeatures, oldFeatures);

        speed = distance / (newTime - oldTime);
        sendMessage(speed);

        oldTime = newTime;
        */
    }
    return 0;
}
