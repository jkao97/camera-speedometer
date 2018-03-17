/*

*/
#define _USE_MATH_DEFINES
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <cmath>

#define cam_angle 62.2 /* in degrees */
#define real_height 10 /* in meters */
#define pix_width 1280
#define PI 3.14159265358979323846264338327950288419716939937510582097494459230781640628

using namespace cv;
double euDistance(cv::Point2f pt1, cv::Point2f pt2);
double convertX(double pixel_dist, double camera_degree, double height, double img_width);

/* Returns keypoints of image */
Mat descDetect(Mat img, std::vector<KeyPoint> key) {
	Ptr<ORB> orb = ORB::create(10, 1.0f, 3, 31, 0, 4, ORB::FAST_SCORE, 31);

	Mat descriptors;
	orb->compute(img, key, descriptors);

	return descriptors;
}

/* Returns descriptors of image */
std::vector<KeyPoint> keyDetect(Mat img) {
	Ptr<ORB> orb = ORB::create(10, 1.0f, 3, 31, 0, 4, ORB::FAST_SCORE, 31);

	std::vector<KeyPoint> keypoints;

	orb->detect(img, keypoints);
	return keypoints;
}

/* Find average pixel distance of matching keypoints */
double calculateDistance(std::vector<KeyPoint> new_key, 
				std::vector <KeyPoint> old_key, 
				Mat new_desc,
				Mat old_desc) {
    
	BFMatcher matcher(NORM_HAMMING);
    std::vector< DMatch > matches;
    matcher.match(new_desc, old_desc, matches);

    unsigned int size = (unsigned int) (matches.size());
    unsigned int totalPoints= 0;
    double min_dist = 100;
    double second_min_dist;
    std::vector< double > pixel_distances; 

    for (int i = 0; i < int (matches.size()); i++){
    	if (matches[i].distance < min_dist) {
       	    min_dist = matches[i].distance;
	    	second_min_dist = min_dist;
		}
    }

    for (unsigned int i = 0; i < size; i++) {
	if (matches[i].distance < min(int (3 * second_min_dist), 100)) {
            Point2f pt_1= new_key.at(matches[i].queryIdx).pt;
	    Point2f pt_2 = old_key.at(matches[i].trainIdx).pt;
	    pixel_distances.push_back(euDistance(pt_1, pt_2);
	    totalPoints++;
	}
    }

    std::sort(pixel_distances.begin(), pixel_distances.end());
    size = pixel_distances.size();
    double median = 0;
    if (size % 2 == 0) {
  	median = (pixel_distances.at(size / 2) + pixel_distances.at((size / 2) - 1)) / 2;
    }
    else {
	median = pixel_distances.at((size / 2) + 1);
    }

    return convertX(median, cam_angle, real_height, pix_width);
}

/* Finds euclidean distance of matching */
double euDistance(Point2f pt1, Point2f pt2) {
	return sqrt(pow(abs(pt2.x - pt1.x), 2) + pow(abs(pt2.y - pt1.y), 2));
}

/* Convert pixel distance to actual distance */
double convertX(double pixel_dist, double camera_degree, double height, double img_width) {
	camera_degree = (camera_degree / 2) * PI / 180;
	double x = (height * tan(camera_degree));
	return ((x / (img_width / 2)) * pixel_dist);
}
