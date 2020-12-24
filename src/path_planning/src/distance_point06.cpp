#include<iostream>
#include "math.h"
#include <iomanip>
#include <vector>
using namespace std;
#include <algorithm>
#include <math.h>

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

PointInfo transform(double x, double y, double tx, double ty, double deg) {
        
        PointInfo transPoint;
        deg = deg * pi / 180;
        int sy = 1;
        int sx = 1;
        transPoint.longitude = sx * ((x - tx) * cos(deg) - (y - ty) * sin(deg)) + tx;
        transPoint.latitude = sy * ((x - tx) * sin(deg) + (y - ty) * cos(deg)) + ty;
        return transPoint;
  }

//返回变换后的经纬度的值
std::vector<PointInfo> createRotatePolygon(std::vector<PointInfo> polygon,PointInfo outRect_center,double rotate){
    std::vector<PointInfo> rotatPolygon;
    for(int d=0;d<polygon.size();d++){
        PointInfo rotatePoint = transform(polygon[d].longitude,polygon[d].latitude,outRect_center.longitude,outRect_center.latitude,rotate);
        rotatPolygon.push_back(rotatePoint);
    }
    return rotatPolygon;

}

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

//计算出新的四边形的顶点的经纬度值
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

//根据纬度值计算经度值
signAndPoint calcPointInLineWithY(PointInfo p1,PointInfo p2,double lat){
        
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

int index(int i,int l){
  if (i > l - 1) {
    return i - l;
  }
  if (i < 0) {
    return l + i;
  }
  return i;
}

int main()
{
    PointInfo nw,ne,sw,se;
    double space = 15;
    double rotate = 0;

    //输入田块的坐标
    std::vector<PointInfo> polygon;
    nw = {23.16057,113.344633};
    ne = {23.16054,113.34525};
    se = {23.159569,113.345175};
    sw = {23.159608,113.344531};
    polygon={nw,ne,se,sw};    
    
    //计算四边形的外接矩阵
    std::vector<PointInfo> outRect;
    outRect=createPolygonBounds(nw,ne,sw,se);

    cout<<fixed<<setprecision(7)<<"outRect[0]:"<<outRect[0].latitude<<","<<outRect[0].longitude<<endl;
    cout<<fixed<<setprecision(7)<<"outRect[1]:"<<outRect[1].latitude<<","<<outRect[1].longitude<<endl;
    cout<<fixed<<setprecision(7)<<"outRect[2]:"<<outRect[2].latitude<<","<<outRect[2].longitude<<endl;
    cout<<fixed<<setprecision(7)<<"outRect[3]:"<<outRect[3].latitude<<","<<outRect[3].longitude<<endl;

    PointInfo outRect_center = {(outRect[0].latitude + outRect[1].latitude)/2,(outRect[3].longitude + outRect[0].longitude)/2};
    
    std::vector<PointInfo> rPolygon = createRotatePolygon(polygon,outRect_center,-rotate); 
    
    cout<<"---------------------------------------------------"<<endl;  
    cout<<fixed<<setprecision(7)<<"rPolygon[0]:"<<rPolygon[0].latitude<<","<<rPolygon[0].longitude<<endl;
    cout<<fixed<<setprecision(7)<<"rPolygon[1]:"<<rPolygon[1].latitude<<","<<rPolygon[1].longitude<<endl;
    cout<<fixed<<setprecision(7)<<"rPolygon[2]:"<<rPolygon[2].latitude<<","<<rPolygon[2].longitude<<endl;
    cout<<fixed<<setprecision(7)<<"rPolygon[3]:"<<rPolygon[3].latitude<<","<<rPolygon[3].longitude<<endl;
    cout<<"---------------------------------------------------"<<endl;  

    double distance_nw_sw = RealDistance(outRect[0].latitude,outRect[0].longitude,outRect[3].latitude,outRect[3].longitude);
    double distance_sw_se = RealDistance(outRect[3].latitude,outRect[3].longitude,outRect[2].latitude,outRect[2].longitude);
    cout<<"distance_nw_sw:"<<distance_nw_sw<<endl;
    cout<<"distance_sw_se:"<<distance_sw_se<<endl;

    int lines = distance_sw_se/space;   //计算出有多少条纬线
    double stepLat = (outRect[0].latitude-outRect[3].latitude)/lines; //纬度相差多少
    cout<<"计算出有多少条纬线:lines:"<<lines<<endl;

    //计算每一条线的纬度，纬度值集合
    std::vector<double> lat_gather;
    for(int i=0;i<lines;i++){
        cout<<"lat_gather:"<<outRect[0].latitude-i*stepLat<<endl;
        lat_gather.push_back(outRect[0].latitude-i*stepLat);
    }

    //计算交点即导航点
    PointInfo westPoint,eastPoint;
    std::vector<PointInfo> fight_points;
    int k_next;
    signAndPoint crossPoint;

    for(int j= 0;j<lat_gather.size();j++){
        std::vector<PointInfo> line_point;
        //遍历四边形
        for(int k=0;k<rPolygon.size();k++){
            crossPoint = calcPointInLineWithY(rPolygon[k],rPolygon[index(k+1,rPolygon.size())],lat_gather[j]);
            cout<<"crossPoint.point:"<<crossPoint.point.latitude<<","<<crossPoint.point.longitude<< endl;
            
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
    std::vector<PointInfo> last_fight_points = createRotatePolygon(fight_points,outRect_center,rotate);

    cout<<"最终的航点有多少个："<<last_fight_points.size()<<endl;
    for(int u=0;u<last_fight_points.size();u++){
        //cout<<"["<<last_fight_points[u].latitude<<","<<last_fight_points[u].longitude<<"]"<<",";
        cout<<last_fight_points[u].latitude<<" "<<last_fight_points[u].longitude<<endl;
        //cout<<last_fight_points[u].latitude<<" ";
        //cout<<last_fight_points[u].longitude<<" ";
    }

}
    
