/*

*/

#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv/nonfree/features2d.hpp>

int calculateDistance(cv::Mat newImg, cv::Mat oldImg) {
    
    SiftFeatureDetector detector; 
    SiftDescriptorExtractor extractor;

    vector<KeyPoint> keypoints_1, keypoints_2;
    Mat descriptor_1, descripter_2;

    detector.detect(newImg, keypoints_1);
    detector.detect(oldImg, keypoints_2);
    extractor.compute(newImg, keypoints_1, descriptor_1);
    extractor.compute(oldImg, keypoints_2, descriptor_2);

    BFMatcher matcher(NORM_L2);
    vector< DMatch > matches;
    matcher.match(descriptor_1, descriptor_2, matches);


    return -1;
}
