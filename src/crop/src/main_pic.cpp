/*
#include <CornerDetector.h>
#include <SusanCornerDetector.h>

#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<ros/ros.h>
using namespace cv;
using namespace std;
#include<iostream>
#include<string>
#include <susan.h>
#include<fstream>
using namespace std;

int main()
{
    Mat img;
    
    
    img = imread("/home/robot/pictures/02.jpg",1);

    if (img.empty())
    {
        printf("No image data \n");
        return -1;
    }

    
    namedWindow("Display original Image", 0 );
    cvResizeWindow("Display original Image",640,480);
    imshow("Display original Image", img);
    }
    */