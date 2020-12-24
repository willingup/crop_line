#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

//Open-CV headers
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/objdetect.hpp"

using namespace std;
using namespace cv;
#include "follow_crop/pos.h"
#include "follow_crop/angle.h"
#define PI 3.14159265

class Crop_Detector{
  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;
  image_transport::Publisher image_pub_;
  ros::Publisher anglePub;

public:

float first_white_pixel=0;
int first_mark=0;

Crop_Detector()
  :it_(nh_)
      {
        image_sub_ = it_.subscribe("/usb_cam/image_raw", 1, &Crop_Detector::imageCallback,this);
        image_pub_ = it_.advertise("/follow_crop_image/output_video", 1);  
        anglePub = nh_.advertise<follow_crop::angle>("/send_angle_topic",1);

      }
      ~Crop_Detector()
      {
          
      }

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
  {

    cv_bridge::CvImagePtr cv_ptr;

    try
    {
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }
    //cv_ptr->image这个就是可以用于opencv处理的图象
    cv::Mat output = detectAndDraw(cv_ptr->image);
    cv_ptr->image = output;
    image_pub_.publish(cv_ptr->toImageMsg());
    waitKey(1); 
}

void EXG(const cv::Mat &img, cv::Mat &gray){
        gray = cv::Mat(img.rows, img.cols, CV_8UC1);
        float R, G, B;
        for (int y = 0; y < img.rows; y++)
        {
	        uchar* data1 = gray.ptr<uchar>(y);
	        for (int x = 0; x < img.cols; x++)
	        {
		        B = img.at<Vec3b>(y, x)[0];
		        G = img.at<Vec3b>(y, x)[1];
		        R = img.at<Vec3b>(y, x)[2];
                float value = G*1.26 -0.31*B -0.89*R;
                if (value>0)
                {
                    /* code for True */
                    if(value>255){
                    data1[x]=255;
                }
                data1[x] = value;
            }
                else{
                    data1[x] = 0;
                }
	         }
      }
}

int Otsu(cv::Mat& src, cv::Mat& dst, int thresh){
	const int Grayscale = 256;
	int graynum[Grayscale] = { 0 };
	int r = src.rows;
	int c = src.cols;
	for (int i = 0; i < r; ++i){
		const uchar* ptr = src.ptr<uchar>(i);
		for (int j = 0; j < c; ++j){        //直方图统计
			graynum[ptr[j]]++;
		}
	}
 
    double P[Grayscale] = { 0 };   
	double PK[Grayscale] = { 0 };
	double MK[Grayscale] = { 0 };
	double srcpixnum = r*c, sumtmpPK = 0, sumtmpMK = 0;
	for (int i = 0; i < Grayscale; ++i){
		P[i] = graynum[i] / srcpixnum;   //每个灰度级出现的概率
		PK[i] = sumtmpPK + P[i];         //概率累计和 
		sumtmpPK = PK[i];
		MK[i] = sumtmpMK + i*P[i];       //灰度级的累加均值                                                                                                                                                                                                                                                                                                                                                                                                        
		sumtmpMK = MK[i];
	}
	
	//计算类间方差
	double Var=0;
	for (int k = 0; k < Grayscale; ++k){
		if ((MK[Grayscale-1] * PK[k] - MK[k])*(MK[Grayscale-1] * PK[k] - MK[k]) / (PK[k] * (1 - PK[k])) > Var){
			Var = (MK[Grayscale-1] * PK[k] - MK[k])*(MK[Grayscale-1] * PK[k] - MK[k]) / (PK[k] * (1 - PK[k]));
			thresh = k;
		}
	}
 
	//阈值处理
	src.copyTo(dst);
	for (int i = 0; i < r; ++i){
	    uchar* ptr = dst.ptr<uchar>(i);
		for (int j = 0; j < c; ++j){
			if (ptr[j]> thresh)
				ptr[j] = 255;
			else
				ptr[j] = 0;
		}
	}
	return thresh;
}

int pixelSum(Mat src){
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

cv::Mat detectAndDraw(Mat& src){

    int w=120;
    int img_split_distance = 30;

    //ROI image
    int src_width = src.cols;
    int src_height = src.rows;
    int roi_top = 50;
    int roi_height = src_height-150;
    cv::Mat roi = src(Rect(src_width/4,roi_top,src_width/2,roi_height));
    cv::Mat img1;
    roi.copyTo(img1);

    //EXG image
    cv::Mat gray_img;
    EXG(img1,gray_img);

    //OTSU image
    cv::Mat dst;
    int thresh=0;
    double t2 = (double)cv::getTickCount();
    thresh=Otsu(gray_img, dst, thresh);
    cv::Mat close_img;
    cv::Mat element = getStructuringElement(MORPH_RECT, Size(8, 8));
    morphologyEx(dst, close_img, MORPH_CLOSE, element);

    //Horizontal segmentation
    int t = 0;
    int m = close_img.rows /img_split_distance;
    
    int i=1;
    std::vector<Mat> ceil_img;
    std::vector<int> name;
    for (t; t < m; t++)
       name.push_back(t);

    Mat image_cut, roi_img, tim_img;
    vector<Point> centers;
    int centers_size;
    int count_pixels= 0;

    for(i;i<=m;i++){
       Rect rect(0, close_img.rows-img_split_distance*i, close_img.cols, img_split_distance);
       image_cut = Mat(close_img, rect);
       
       //Saves the white pixels in the lower half of the image
       if(i>int(m/2)&&i<=m){
           count_pixels= count_pixels+pixelSum(image_cut);

           if(first_mark==0)
               first_mark = 1; //第一帧图象的时候才能改变为1
           else
               first_mark = 2;
       }

       vector<vector<Point> > contours;
       vector<Vec4i> hierarchy;
       
       findContours(image_cut, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE,Point(0,0));
       if(contours.size()==0){
           continue;
       }

       //计算轮廓矩 	
       vector<Moments> mu(contours.size() );
	     for(int num = 0; num < contours.size(); num++ ) 	
	     { 
		      mu[num] = moments( contours[num], false ); 
	     } 	

       //计算轮廓的质心 	
	     vector<Point2f> mc( contours.size() ); 	
	     for( int index = 0; index < contours.size(); index++ ) 	
	     { 
		      mc[index] = Point2d( mu[index].m10/mu[index].m00 , mu[index].m01/mu[index].m00 ); 
	     } 

       //findContours(image_cut, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE,Point(0,0));
       Mat contoursImage(image_cut.rows, image_cut.cols, CV_8U, Scalar(255));
       
       for (int index = 0; index >= 0; index = hierarchy[index][0]) {
		      cv::Scalar color(rand() & 255, rand() & 255, rand() & 255);
		      //cv::drawContours(contoursImage, contours, index, Scalar(0), 3, 8, hierarchy);
      
		      Rect rect = boundingRect(contours[index]); //检测外轮廓，返回外部矩形边界
           //RotatedRect rect = minAreaRect(contours[index]);
           if (rect.width < 40)     //去掉小的矩阵框
			 continue;
           
           cv::Point pt1,pt2_center,pt3,last_point;
           float distance = 0.0;
   
           pt2_center.x = mc[index].x;
           pt2_center.y = mc[index].y;

		       rectangle(contoursImage, rect, Scalar(0,0,255), 1); //绘制外轮廓的矩形框
           cv::circle(contoursImage,pt2_center,1, (255, 0, 0), 2, 8, 0);//绘制中心点
           
           if (pt2_center.x<image_cut.cols/2+w)
           {
               if(image_cut.cols/2-w < pt2_center.x){
                    pt3.x = pt2_center.x;
                    pt3.y = close_img.rows-img_split_distance*i+pt2_center.y;
                    
                    //判断上一个特征点和现在的特征点的距离，如果距离大于某个特定值，排除
                    centers_size = centers.size();
                    if(centers_size>1)
                    {
                        //cout << "上一个点的坐标" << endl << centers[centers_size-1] << endl;
                        distance = pow(pow(centers[centers_size-1].x - pt3.x, 2) + pow(centers[centers_size-1].y - pt3.y, 2), 0.5);
                    }
                    //cout <<"重新计算两点之间的距离"<<endl<<distance<<endl;
                    //欧式距离
                    if(distance<130){
                        cout<<"加入"<<endl;
                        centers.push_back(pt3);
                    }
               
               } 
           } 
      }
       roi_img = contoursImage.clone();
       ceil_img.push_back(roi_img);
    }  
    
    cout << "特征点的集合" << endl << centers << endl; 
    cout<<"筛选后特征点的个数是："<<centers.size()<<endl;

    for (int j = 0;j < centers.size();j++)
	{
		//在原图上画出点
        cout<<"特征点"<<endl<<centers[j]<<endl;
        cv::circle(roi,centers[j],3, (255, 0, 0), 2, 8, 0);	
	}
    //记录第一帧图象中下半部分白色像素值
    if(first_mark==1)
       first_white_pixel = count_pixels;

    float proportion = count_pixels/first_white_pixel;
    if(proportion<0.5){
        //判定机器人快要到达行末了，发出一个信号，其他地方的来接受这个信号，如果接受到了那就调用GPS判断，是否到达计划点
        cout<<"已经快要到边界了，请注意"<<endl;
        
    }
    cv::Vec4f line_para;  //存放拟合之后的直线
    cv::fitLine(centers, line_para, cv::DIST_L1, 0, 1e-2, 1e-2);
    
    //cv::fitLine(centers_change, line_para, cv::DIST_L2, 0, 1e-2, 1e-2);
    //获取点斜式的点和斜率
 
	cv::Point point0; 
    point0.x = line_para[2];
	point0.y = line_para[3];
    double k = line_para[1] / line_para[0];
    
    cv::Point point01,point02;
    point01.x = 0;
    point01.y = k * (0-point0.x)+point0.y;

    point02.x = 640;
    point02.y = k*(640-point0.x)+point0.y;
    
    cv::line(roi,point01,point02,cv::Scalar(0,255,0),2,8,0);
    
    double lines_acrtan = atan (1/k);
    double angle_img = lines_acrtan * 180/PI;
    cout<<"拟合秧苗线的斜率是："<<k<<endl;
    cout<<"拟合秧苗线相对于中央线倾斜的角度是："<<angle_img<<endl;   
    cv::Point img_center_point;
    img_center_point.x = roi.cols/2;
    img_center_point.y = src_height/2+roi_top;

    //直线 kx-y+ point02.y-k point02.x=0
    double a = k;
    double b = -1;
    double c = point02.y-k*point02.x;
    double d = fabs(a*img_center_point.x+b*img_center_point.y+c)/sqrt(a*a+b*b);
    cout<<"d的值为："<<d<<endl;
    double X0 = d/cos(lines_acrtan);
    cout<<"X0的值为："<<X0<<endl;

    //如何自动的获取标定文件中的内参矩阵呢
    double ax = 552.04388;
    double ay = 554.00103;
    double angle_camera = 55*PI/180;

    double flight_radian = atan(ay*tan(lines_acrtan)*sin(angle_camera)/ax-X0*cos(angle_camera)/ax);
    double flight_angle = flight_radian * 180/PI;

    cout<<"航偏角的弧度值为："<<flight_radian<<endl;
    cout<<"航偏角的值为："<<flight_angle<<endl;

    double Xw,Zw;
    double h = 600; 
    Xw = h*X0/(ax*sin(angle_camera));
    Zw = h/tan(angle_camera);
    double offset = fabs(Xw*cos(flight_radian)+Zw*sin(flight_radian));
    cout<<"偏距："<<offset<<"mm"<<endl;

    //把角度发送给pid的程序
    follow_crop::angle angle_msg;
    angle_msg.angle =(float)flight_angle;
    anglePub.publish(angle_msg);

    //把角度输出到图象中去
    
    std::string str = std::to_string(angle_img);
    putText(roi,str,Point(20,20),FONT_HERSHEY_SIMPLEX,0.5,Scalar(255,0,0),0.5,8);

    return roi;
}
};


int main(int argc, char** argv)
{
  ros::init(argc, argv, "crop_line_tracker");
  Crop_Detector ic;
  ros::spin();
  return 0;
}