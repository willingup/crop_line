#include<iostream>
#include "math.h"
#include <iomanip>
#include <vector>
using namespace std;
#include <algorithm>

#define pi 3.1415926535897932384626433832795
#define EARTH_RADIUS 6378.137 //地球半径 KM

struct PointInfo{
    double latitude;
    double longitude;                   
};

struct signAndPoint{
    bool sign;
    PointInfo point;
};

//计算GPS两点之间的距离
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

std::vector<PointInfo> createPolygonBounds(PointInfo nw,PointInfo ne,PointInfo sw,PointInfo se){
    //目标是计算出新的四边形的顶点的经纬度值；判断出最大最小的经度值，把所有的经度、纬度值放入数组中，比较出最大最小值
    double lat[4]={nw.latitude,ne.latitude,sw.latitude,se.latitude};
    double lng[4]={nw.longitude,nw.longitude,sw.longitude,se.longitude};
    double max_lab = *max_element(lat,lat+4);
    double max_lng = *max_element(lng,lng+4);

    double min_lab = *min_element(lat,lat+4);
    double min_lng = *min_element(lng,lng+4);

    std::vector<PointInfo> new_polygon_point;
    PointInfo new_nw,new_ne,new_sw,new_se;
    new_nw={max_lab,min_lng};
    new_ne={max_lab,max_lng};
    new_sw={min_lab,min_lng};
    new_se={min_lab,max_lng};

    new_polygon_point.push_back(new_nw); 
    new_polygon_point.push_back(new_ne); 
    new_polygon_point.push_back(new_se); 
    new_polygon_point.push_back(new_sw); 
    return new_polygon_point;   
}
//这里留下一个小的BUG ：把计算出点的GPS值放在了全局变量中
signAndPoint calcPointInLineWithY(PointInfo p1,PointInfo p2,double lat){
        //根据纬度值计算经度值
        double s = p1.latitude- p2.latitude;
        double lng;
        signAndPoint return_value={false,{0,0}};
        cout<<"---------------------------------------------------"<<endl;
        cout<<"输入的纬度值是："<<lat<<endl;
        if (s) {
            lng = (lat - p1.latitude) * (p1.longitude - p2.longitude) / s + p1.longitude;
            
            cout<<"s的值为："<<s<<endl;
            cout<<"计算出的lng的值为："<<lng<<endl;
        } else {
            return return_value;
        }
        cout<<"p1.longitude:"<<p1.longitude<<endl;
        cout<<"p2.longitude:"<<p2.longitude<<endl;
        /**判断x是否在p1,p2在x轴的投影里，不是的话返回false*/
        if (lng > p1.longitude && lng > p2.longitude) {
            return return_value;
        }
        if (lng < p1.longitude && lng < p2.longitude) {
            return return_value;
        }
        return_value.sign = true;
        return_value.point = {lat,lng};
        return return_value;
  }

int main()
{
    /*
    以下代码 功能是输入的四条边不两两垂直，但是纬度的投影没有变化
    */

    PointInfo nw,ne,sw,se;
    double space=2;
    std::vector<PointInfo> polygon;
    nw = {23.16057,113.344633};
    ne = {23.16054,113.34525};
    se = {23.159569,113.345175};
    sw = {23.159608,113.344531};
    
    //多输入第一个顶点将四边形围起来
    polygon={nw,ne,se,sw,nw};
    
    std::vector<PointInfo> outRect;
    outRect=createPolygonBounds(nw,ne,sw,se);

    cout<<fixed<<setprecision(7)<<"outRect[0]:"<<outRect[0].latitude<<","<<outRect[0].longitude<<endl;
    cout<<fixed<<setprecision(7)<<"outRect[1]:"<<outRect[1].latitude<<","<<outRect[1].longitude<<endl;
    cout<<fixed<<setprecision(7)<<"outRect[2]:"<<outRect[2].latitude<<","<<outRect[2].longitude<<endl;
    cout<<fixed<<setprecision(7)<<"outRect[3]:"<<outRect[3].latitude<<","<<outRect[3].longitude<<endl;
    
    double distance_nw_sw = RealDistance(outRect[0].latitude,outRect[0].longitude,outRect[3].latitude,outRect[3].longitude);
    cout<<"distance_nw_sw:"<<distance_nw_sw<<endl;

    int lines = distance_nw_sw/space;   //计算出有多少条纬线
    double stepLat = (outRect[0].latitude-outRect[3].latitude)/lines; //纬度相差多少
    cout<<"lines:"<<lines<<endl;

    //计算每一条线的纬度，纬度值集合
    std::vector<double> lat_gather;
    for(int i=0;i<lines;i++){
        cout<<"lat_gather:"<<outRect[0].latitude-i*stepLat<<endl;
        lat_gather.push_back(outRect[0].latitude-i*stepLat);
    }
    //计算交点即导航点
    PointInfo westPoint,eastPoint;
    std::vector<PointInfo> fight_points;
    signAndPoint crossPoint;
    for(int j= 0;j<lat_gather.size();j++){
        std::vector<PointInfo> line_point;
        //遍历四边形
        for(int k=0;k<polygon.size()-1;k++){
            
            crossPoint = calcPointInLineWithY(polygon[k],polygon[k+1],lat_gather[j]);
            cout<<"crossPoint.point:"<<crossPoint.point.latitude<<","<<crossPoint.point.longitude<< endl;
            //我好像知道我哪里出现问题了，原来用的是
            if(crossPoint.sign){
                line_point.push_back(crossPoint.point);
            }
        }
        cout<<"直线与四边形的交点的个数是："<<line_point.size()<<endl;
        //去掉一个交点重合的纬度线
        
        if(line_point.size()<2){
            continue;
        }
        //去掉两个交点重合的纬度线
        if(line_point[0].longitude==line_point[1].longitude){
            continue;
        }            
        
        //基本上保留下来的点是两个，因为一条导航线与四边形的两条边相交，所以是有两个交点的       
        
        if(j%2==0){
            fight_points.push_back(line_point[0]);
            fight_points.push_back(line_point[1]);
        }else{  
            fight_points.push_back(line_point[1]);
            fight_points.push_back(line_point[0]);
        }
        
        
    }
    cout<<"航点有多少个："<<fight_points.size()<<endl;
    for(int u=0;u<fight_points.size();u++){
        cout<<"["<<fight_points[u].latitude<<","<<fight_points[u].longitude<<"]"<<",";
    }

}
    


    /*
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
*/
    //计算这个四边形的框穿过了多少纬度线
    /*
        westPoint=calcPointInLineWithY(nw,sw,lat_gather[j]); 
        eastPoint=calcPointInLineWithY(ne,se,lat_gather[j]);
        if(j%2==0){
            fight_points.push_back(westPoint);
            fight_points.push_back(eastPoint);
        }else{  
            fight_points.push_back(eastPoint);
            fight_points.push_back(westPoint);
        */
/*
for(var i=0;i<latLines.len;i++){
  line=[];
  
  for(var j=0;j<polygon.length;j++){
    var point=calcPointInLineWithY([
       polygon[i].lng,
       polygon[i].lat,
    ],[
      polygon[si(i+1,polygon.length)].lng
      polygon[si(i+1,polygon.length)].lat
    ],outRect.latlngs[0].lat - i*latLines.lat)
    if(point){
      line.push(point)
    }
  }
*/
    

