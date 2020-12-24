#include<iostream>
#include "math.h"
#include <iomanip>
#include <vector>
using namespace std;
#define pi 3.1415926535897932384626433832795
#define EARTH_RADIUS 6378.137 //地球半径 KM

struct PointInfo{
        double latitude;
        double longitude;                   
    };


PointInfo calcPointInLineWithY(PointInfo p1,PointInfo p2,double lat){
        //根据纬度值计算经度值
        double s = p1.latitude- p2.latitude;
        double lng;
        int lab;
        if (s) {
            lng = (lat - p1.latitude) * (p1.longitude - p2.longitude) / s + p1.longitude;
        } else {
            //return false;
            lab = 1;
        }
        
        /**判断x是否在p1,p2在x轴的投影里，不是的话返回false*/
        if (lng > p1.longitude && lng > p2.longitude) {
            //return false;
            lab = 1;
        }
        if (lng < p1.longitude && lng < p2.longitude) {
            //return false;
            lab = 1;
        }
        PointInfo point = {lat,lng};
        return point;
  }

double rad(double d)
{
    return d * pi /180.0;
}
double RealDistance(double lat1,double lng1,double lat2,double lng2)//lng1第一个点经度,lat1第一个点纬度,lng2第二个点经度,lat2第二个点纬度
{
	
	double a;
   	double b;
   	double radLat1 = rad(lat1);
    double radLat2 = rad(lat2);
    a = radLat1 - radLat2;
    b = rad(lng1) - rad(lng2);
    double s = 2 * asin(sqrt(pow(sin(a/2),2) + cos(radLat1)*cos(radLat2)*pow(sin(b/2),2)));
    s = s * EARTH_RADIUS;
    s = s * 1000;
    return s;
}

 

int main()
{
    /*
    以下代码 功能是输入的四条边不两两垂直，但是纬度的投影没有变化
    */
    PointInfo nw,ne,sw,se;
    nw = {23.16057,113.344633};
    ne = {23.16054,113.34525};
    sw = {23.159608,113.344531};
    se = {23.159569,113.345175};
    
    double distance_long = RealDistance(23.16054,113.34525,23.159569,113.345175);
    double distance_short = RealDistance(23.16057,113.344633,23.16054,113.34525);

    
    int lines = distance_long/0.6;
    cout<<lines<<endl;
    
    std::vector<double> lat_gather;
    double stepLat = (nw.latitude-sw.latitude)/lines;
    for(int i=0;i<lines;i++){
        lat_gather.push_back(nw.latitude-i*stepLat);
    }

    
    for(int i=0;i<lat_gather.size();i++){
        PointInfo westPoint=calcPointInLineWithY(nw,sw,lat_gather[i]);
        cout<<fixed<<setprecision(7)<<westPoint.latitude<<","<<westPoint.longitude<<endl;
        PointInfo eastPoint=calcPointInLineWithY(ne,se,lat_gather[i]);
        cout<<fixed<<setprecision(7)<<eastPoint.latitude<<","<<eastPoint.longitude<<endl;
    }
    

}