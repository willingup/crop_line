#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<ros/ros.h>

using namespace cv;
using namespace std;

#include<iostream>
#include<string>
#include<fstream>

int main(int argc, char *argv[])
{
    Mat img;
    /*
    //两种方法进行ROI选择
    IplImage *image = cvLoadImage("/home/robot/pictures/00.jpg");
    cvSetImageROI(image,cvRect(200,180,260,280));
    cvShowImage("ROI", image); 
    */

    img = imread("/home/robot/pictures/auto_pictures5/743.png");
    imshow("origal-image",img);
    int width = img.cols;
    int height = img.rows;
    //Mat roi=img(Rect(100,100,250,200));
    Mat roi=img(Rect(width/3,0,width/3,height));
    Mat img1;
    roi.copyTo(img1);
    namedWindow("ROI-image",1);
    imshow("ROI-image",img1);

    //cvResetImageROI(img);//★释放ROI，否则，只会显示ROI区域  
      

    waitKey(0);
    return 0;
}