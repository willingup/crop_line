#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp"  
#include "opencv2/core/core.hpp"
#include <opencv/ml.h>
#include <iostream>
#include "cv.h"
#include "highgui.h"
#include <vector>
#include <math.h>
#include <string.h>
#include <fstream>
using namespace std;
using namespace cv;
 
 
int bSums(Mat src)
{
	int counter = 0;
	//迭代器访问像素点
	Mat_<uchar>::iterator it = src.begin<uchar>();
	Mat_<uchar>::iterator itend = src.end<uchar>();  
    //0是黑素，255是白
	for (; it!=itend; ++it)
	{
		if((*it)>0) counter+=1;//二值化后，像素点是0或者255
	}			
	return counter;
}
int main()
{
	static string imgPath = "/home/robot/pictures/auto_pictures6/132.png";//读取源图
    //Mat src = cv::imread("/home/robot/pictures/auto_pictures6/157.png");

	Mat a1 = imread(imgPath);
	cvtColor(a1,a1,COLOR_BGR2GRAY);//转灰度图
	threshold(a1,a1,200,255,THRESH_BINARY);//二值化

	int a = bSums(a1);//调用函数bSums

	imshow("A",a1);
	cout<<"A:"<<a<<endl;
	waitKey();
	return 0;
}
 