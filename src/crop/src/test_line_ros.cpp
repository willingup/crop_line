#include <cv_bridge/cv_bridge.h>
#include <cstdlib>
#include <string>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"
#include "ros/ros.h"
#include "ros/console.h"
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<ros/ros.h>
using namespace cv;
using namespace std;
#include<iostream>
#include<string>
#include<fstream>
#include <vector> 


int main(int argc, char **argv) {
    ros::init(argc, argv, "detection");
    ros::NodeHandle n;
    LineDetect det;
    ros::Subscriber sub = n.subscribe("/camera/rgb/image_raw",1, &LineDetect::imageCallback, &det);
    //不需要有发布只需要有订阅就好了
    while (ros::ok()) {
        if (!det.img.empty()) {
            // Perform image processing
            int w=30;
            int img_split_distance = 30;

            int width = det.img.cols;
            int height = det.img.rows;
    
            det.img_filt = det.Gauss(det.img);
            msg.direction = det.colorthresh(det.img_filt);
    
            // Publish direction message
            dirPub.publish(msg);
            }
        ros::spinOnce();
    }
    cv::destroyWindow("Turtlebot View");
}