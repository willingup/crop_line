#include<iostream>
#include "math.h"
#include <iomanip>
#include <vector>
using namespace std;

#define pi 3.1415926535897932384626433832795
#define EARTH_RADIUS 6378.137 //地球半径 KM

double rad(double d)
{
    return d * pi /180.0;
}
double RealDistance(double lng1,double lat1,double lng2,double lat2)//lng1第一个点经度,lat1第一个点纬度,lng2第二个点经度,lat2第二个点纬度
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
    1、先定义4个点
    2、求出长边的长度 nw->sw
    3、根据间距求出航线的条数
    4、根据条数求出 计算出每一条横线的N 即交点的纬度坐标 一系列导航点的经纬度坐标
    */
    struct PointInfo{
        double longitude;
        double latitude;              
    };

    PointInfo nw,ne,sw,se;
    nw = {113.344633, 23.16057};
    ne = {113.34525, 23.16054};
    sw = {113.344531, 23.159608};
    se = {113.345175, 23.159569};
    
    double distance_long = RealDistance(113.34525,23.16054,113.345175,23.159569);
    double distance_short = RealDistance(113.344633, 23.16057,113.34525, 23.16054);

    cout<<fixed<<setprecision(7)<<distance_long<<endl;
    cout<<fixed<<setprecision(7)<<distance_short<<endl;
    
    int lines = distance_long/0.6;
    cout<<lines<<endl;
    
    std::vector<double> lat_gather;
    double stepLat = (nw.latitude-sw.latitude)/lines;
    for(int i=0;i<lines;i++){
        lat_gather.push_back(nw.latitude-i*stepLat);
    }
    
    //cout<<“每一个横条的纬度是多少”<<stepLat<<endl;
    for(int j=0;j<lat_gather.size();j++)
        cout<<"航点的纬度值："<<lat_gather[j]<<endl;

    //如果是严格按照长方形的话，那长宽垂直，那航点数量应该是计算出的lat_gather的两倍
    int all_fight_num = 2 * lat_gather.size();
    
    
    std::vector<PointInfo> fight_points;
    for(int k=1;k<=all_fight_num;k=k+2){
        //由于是蛇形旋转，所以无法用奇数偶数赋值
       
        PointInfo point_enter_left,point_enter_right;
        point_enter_left.longitude = nw.longitude;
        point_enter_left.latitude = lat_gather[(k+1)/2-1];
        
        point_enter_right.longitude = ne.longitude;
        point_enter_right.latitude = lat_gather[(k+1)/2];

        fight_points.push_back(point_enter_left);
        fight_points.push_back(point_enter_right);
    }
      
    for(int l=0;l<fight_points.size();l++){
        cout<<fight_points[l].longitude<<","<<fight_points[l].latitude<<endl;
    }
    cout<<"总的航点数目："<<fight_points.size()<<endl;
    //目前已经得到了所有的航点的坐标
         
   return 0;
}

/*
功能是：计算两个经纬度的点之间的距离




经过测试：39.941, 116.45, 39.94, 116.451 在网上的其他程序计算得到的结果是140.0285，当前程序跑出来的是140.273
         39.96, 116.45, 39.94, 116.40  4804.421 当前程序是4812.82 相差8米
         4公里相差8米，精度差不多
*/