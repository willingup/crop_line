#include<iostream>
#include<opencv2/core.hpp>
using namespace cv;
using namespace std;
#include <vector>
#include <fstream>
#include <iomanip>

/*
*** 代码的功能是从文件中读取出经纬度投影后的平面坐标，放在pointABCD
*/
int main(){
    	ifstream pointTxt;
        std::vector<Point2d> pointABCD;
        cv::Point2d temp;
        //cv::Point temp;
        double temp1,temp2;
        pointTxt.open("/home/robot/hei/lng.txt");
        for(int i = 0; !pointTxt.eof(); i++)
	    {
	        //读取txt文件的坐标值
	        pointTxt >> temp1 >>temp2;
	        temp.x = temp1;
	        temp.y = temp2;
 	        pointABCD.push_back(temp);
	    }
        for (int j = 0; j < pointABCD.size(); j++)
        {
            /* code for loop body */
            cout<<fixed<<setprecision(9)<<pointABCD[j]<<endl;
        }
        
}