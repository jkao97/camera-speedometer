/*

*/

#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/imgproc.hpp>

#include <chrono>
#include <thread>

double calculateDistance(std::vector<KeyPoint> new_key, 
				std::vector <KeyPoint> old_key, 
				Mat new_desc,
				Mat old_desc);
void descDetect(Mat img, std::vector<KeyPoint> key, cv::Mat desc);
std::vector<KeyPoint> keyDetect(Mat img);


int main(int argc, char **argv) {


    return 0;
}
