
#pragma once
#include <cv_bridge/cv_bridge.h>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"
#include "ros/ros.h"


class LineDetect {
 public:
    cv::Mat src;  /// Input image in opencv matrix format
    cv::Mat img_filt;  /// Filtered image in opencv matrix format
    cv::Mat roi;
    cv::Mat img1;
    cv::Mat gray_img;

    int w=120;
    int img_split_distance = 30;
    void imageCallback(const sensor_msgs::ImageConstPtr& msg);
    //void EXG(const cv::Mat &img,cv::Mat &gray);
    //int Otsu(cv::Mat& src, cv::Mat& dst, int thresh);
    int direction;

 private:
    cv::Scalar Lower;
    cv::Scalar Upper;
    cv::Mat img_hsv;
    cv::Mat img_mask;
};