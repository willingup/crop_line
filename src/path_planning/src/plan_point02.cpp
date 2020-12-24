#include<iostream>
#include<opencv2/core.hpp>
using namespace cv;
using namespace std;
#include <vector>
#include <fstream>
#include <iomanip>

/*
*** 代码的功能是从文件中读取出经纬度投影后的平面坐标，放在pointABCD
*** 将坐标减去共有的部分，变成一个新的坐标，坐标轴与原来的平行，放在polygon中，x为纵轴，y为横轴
*/
int main(){
    	ifstream pointTxt;
        std::vector<Point2d> pointABCD,polygon;
        cv::Point2d temp,retemp;

        double temp1,temp2;
        double conX=2563000;
        double conY=19740000;
        pointTxt.open("/home/robot/hei/lng.txt");
        for(int i = 0;!pointTxt.eof(); i++)
	    {          
	        //读取txt文件的坐标值
	        pointTxt >> temp1 >>temp2;
	        temp.x = temp1;
	        temp.y = temp2;
 	        pointABCD.push_back(temp);    
	    }

        //在读取文件流时每次最后一个都要重复，那只好把pointABCD.size()-1
        for (int j = 0; j < pointABCD.size()-1; j++)
        {
            /* code for loop body */
            //cout<<fixed<<setprecision(9)<<pointABCD[j]<<endl;
            retemp.x = pointABCD[j].x-conX;
            retemp.y = pointABCD[j].y-conY;
            polygon.push_back(retemp);
            cout<<polygon[j].x<<","<<polygon[j].y<<endl;
            
        }
        
        
        
}