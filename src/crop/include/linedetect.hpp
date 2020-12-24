#include <cv_bridge/cv_bridge.h>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"
#include "ros/ros.h"

class LineDetect {
 public:
    cv::Mat img;  /// Input image in opencv matrix format
    cv::Mat img_filt;  /// Filtered image in opencv matrix format
    int dir;  /// Direction message to be published
    void imageCallback(const sensor_msgs::ImageConstPtr& msg);
    cv::Mat Gauss(cv::Mat input);
    int colorthresh(cv::Mat input);
    private:
    cv::Scalar Lower;
    cv::Scalar Upper;
    cv::Mat img_hsv;
    cv::Mat img_mask;
};