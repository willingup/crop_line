#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>  
#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<ros/ros.h>
using namespace cv;
using namespace std;
#include<iostream>
#include<string>
#include<fstream>
#include <vector> 

 
int main()
{
	cv::VideoCapture cap(0);
	
        Mat frame;
    	char key;
    	char filename[600];
    	int i = 0;
         while (true)
         {
             String filename = "/home/robot/pictures/crop_picture4/" +to_string(i)+".jpg";
             char key = waitKey(100);
             cap >> frame;
             imshow("frame", frame);
             
                     switch (key)
                     {
                     case'p':
                         i++;
                         imwrite(filename, frame);
                         imshow("photo", frame);
                         waitKey(50);
                         destroyWindow("photo");
                         break;
                     default:
                         break;
                     }
		
         int c = waitKey(20); 
	 

         }
   waitKey(0);
   return 0;
}


