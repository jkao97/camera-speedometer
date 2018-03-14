#ifndef CV_HPP
#define CV_HPP

#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

cv::Mat descDetect(cv::Mat img, std::vector<KeyPoint> key);
std::vector<KeyPoint> keyDetect(cv::Mat img);
double calculateDistance(std::vector<KeyPoint> new_key, 
				std::vector <KeyPoint> old_key, 
				cv::Mat new_desc,
				cv::Mat old_desc);

#endif