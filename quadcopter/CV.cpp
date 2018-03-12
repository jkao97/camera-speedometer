/*

*/

#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/imgproc.hpp>
#include <cmath>


using namespace cv;
double euDistance(cv::Point2f pt1, cv::Point2f pt2);
double convertX(double pixel_dist, double camera_degree, double height, double img_width);

double calculateDistance(cv::Mat newImg, cv::Mat oldImg) {
    ORB detector = ORB(10, 1.0f, 3, 31, 0, 4, ORB::FAST_SCORE, 31);

    std::vector<KeyPoint> keypoints_1, keypoints_2;
    Mat descriptor_1, descripter_2;

    detector.detect(newImg, keypoints_1);
    detector.detect(oldImg, keypoints_2);
    detector.compute(newImg, keypoints_1, descriptor_1);
    detector.compute(oldImg, keypoints_2, descriptor_2);

    BFMatcher matcher(NORM_HAMMING);
    vector< DMatch > matches;
    matcher.match(descriptor_1, descriptor_2, matches);

    double sumDist = 0;
    unsigned int size = unsigned int (matches.size());
    unsigned int totalPoints= 0;

    for (unsigned int i = 0; i < size; i++) {
	if (matches[i].distance < 20) {
            Point2f pt_1= keypoints2.at(matches[i].queryIdx).pt;
	    Point2f pt_2 = keypoints1.at(matches[i].trainIdx).pt;
	    sumDist += euDistance(pt_1 , pt_2);
	    totalPoints++;
	}
    }
	
    double average = sumDist / totalPoints;

    /*return convertX(average, camera_degree, real_height, img_width);*/
    return average;
}

/* Finds euclidean distance of matching */
double euDistance(Point2f pt1, Point2f pt2) {
	return sqrt(pow(abs(pt2.x - pt1.x), 2) + pow(abs(pt2.y - pt1.y), 2));
}

/* Convert pixel distance to actual distance */
double convertX(double pixel_dist, double camera_degree, double height, double img_width) {
	double x = (height / tan(camera_degree));
	double half_width = img_width / 2;
	return ((half_width / x) * pixel_dist);
}
