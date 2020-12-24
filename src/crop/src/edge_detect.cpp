#include <susan.h>

#include "iostream"

#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<ros/ros.h>
using namespace cv;
using namespace std;
#include<string>

#include<fstream>



int main()
{
	Mat img = imread("/home/robot/pictures/T.jpg",1);
	
    namedWindow("Display original Image", 0 );
    cvResizeWindow("Display original Image",640,480);
	imshow("Display original Image", img);
	waitKey(1000);

	Mat edge_img = Susan(img, 5);
	namedWindow("edge_image", 0 );
    cvResizeWindow("edge_image",640,480);
	imshow("edge_image", edge_img);
	waitKey(0);

	return(0);
}
