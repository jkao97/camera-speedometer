#ifndef CV_HPP
#define CV_HPP

#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

cv::Mat descDetect(cv::Mat img, std::vector<cv::KeyPoint> key);
std::vector<cv::KeyPoint> keyDetect(cv::Mat img);
double calculateDistance(std::vector<cv::KeyPoint> new_key, 
				std::vector <cv::KeyPoint> old_key, 
				cv::Mat new_desc,
				cv::Mat old_desc);

#endif