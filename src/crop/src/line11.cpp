#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<ros/ros.h>
using namespace cv;
using namespace std;
#include<iostream>
#include<string>
#include<fstream>
#include <vector> 
#include <math.h>
#define PI 3.14159265
#include<time.h>
void EXG(const Mat &img, Mat &gray);
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

int main()
{
    double time = (double)getTickCount();
    int w=110;
    int img_split_distance = 30;
    
    //original image
    Mat src = cv::imread("/home/robot/pictures/auto_pictures6/25.png");
    
    imshow("original image", src);

    //ROI image
    //Mat roi=src(Rect(150,0,280,480));
    //Mat roi=src(Rect(100,100,230,200));

    int width = src.cols;
    int height = src.rows;
    int roi_top = 50;
    int roi_height = height-150;

    Mat roi=src(Rect(width/4,roi_top,width/2,roi_height));

    //Mat roi=src(Rect(150,50,400,380));
    //Mat roi=src(Rect(150,50,400,380));
    
    Mat img1;
    roi.copyTo(img1);
    imshow("ROI-image",img1);
    
    cout<<roi.cols<<endl;
    cout<<roi.rows<<endl;

    //EXG image
    Mat gray_img;
    EXG(img1,gray_img);
    imshow("gray image", gray_img);
    
    //OTSU image
    Mat dst;
    int thresh=0;
    double t2 = (double)cv::getTickCount();
	thresh=Otsu(gray_img, dst, thresh);
    cv::namedWindow("OTSU", CV_WINDOW_NORMAL);
	cv::imshow("OTSU", dst);
    
    //Morphological operation
    Mat close_img;
    Mat element = getStructuringElement(MORPH_RECT, Size(8, 8));
    morphologyEx(dst, close_img, MORPH_CLOSE, element);
    namedWindow("Display Morphological operation", 0 );
    imshow("Display Morphological operation",close_img);
    
    //cut image
    //String outpath = "/home/robot/pictures/new1/pic";

    int t = 0;
    int m = close_img.rows /img_split_distance;
    cout << "一共分为几个子图" << endl << m << endl;
    int i=1;
    std::vector<Mat> ceil_img;
    std::vector<int> name;

    for (t; t < m; t++)
       name.push_back(t);

    Mat image_cut, roi_img, tim_img;
    vector<Point> centers;
    
    int centers_size; 
    cout<<close_img.cols<<endl;
    cout<<close_img.rows<<endl;

    for(i;i<=m;i++){
       //cout<<i<<endl;
       Rect rect(0, close_img.rows-img_split_distance*i, close_img.cols, img_split_distance);
       image_cut = Mat(close_img, rect);
       
       vector<vector<Point> > contours;
       vector<Vec4i> hierarchy;
       
       findContours(image_cut, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE,Point(0,0)); //CV_RETR_EXTERNAL只检测外部轮廓，可根据自身需求进行调整
       //计算轮廓矩 	
       vector<Moments> mu(contours.size() );
	   for( int num = 0; num < contours.size(); num++ ) 	
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
           //cout<<678<<endl;
		   Rect rect = boundingRect(contours[index]); //检测外轮廓，返回外部矩形边界
           //RotatedRect rect = minAreaRect(contours[index]);
           if (rect.width < 40)     //去掉小的矩阵框
			   continue;
           
           cv::Point pt1,pt2_center,pt3,last_point;
           float distance = 0.0;
   
           //pt2_center.x = rect.x + rect.width/2;
           //pt2_center.y = rect.y + rect.height/2;
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
                        cout << "上一个点的坐标" << endl << centers[centers_size-1] << endl;
                        //cout << "上一个点的坐标的x" << endl << centers[centers_size-1].x << endl;
                        //cout << "上一个点的坐标的y" << endl << centers[centers_size-1].y << endl;
                        distance = pow(pow(centers[centers_size-1].x - pt3.x, 2) + pow(centers[centers_size-1].y - pt3.y, 2), 0.5);
                    }
                    cout <<"重新计算两点之间的距离"<<endl<<distance<<endl;
                    //欧式距离
                    if(distance<130){
                        cout<<"加入"<<endl;
                        centers.push_back(pt3);
                    }
               
               } 
           } 
      }
       //cout<<8<<endl;
       roi_img = contoursImage.clone();
       ceil_img.push_back(roi_img);
    }

    cout << "image_cut 图像的中点" << endl << image_cut.cols/2 << endl;
    cout << "特征点的集合" << endl << centers << endl; 
    //Mat line_img = roi.clone();

    for (int j = 0;j < centers.size();j++)
	{
		//在原图上画出点
        cout<<"特征点"<<endl<<centers[j]<<endl;
        cv::circle(roi,centers[j],3, (255, 0, 0), 2, 8, 0);	
	} 
    /*
    下面进行修改的内容是将点的顺序倒置保存到center_change,修改之后发现还是和原来一样
    */
    vector<Point> centers_change;
    int allnum = centers.size();
    cout<<"筛选后特征点的个数是："<<allnum<<endl;
    for(int order=allnum-1;order>=0;order--){
        centers_change.push_back(centers[order]) ;
    }

    cv::Vec4f line_para;  //存放拟合之后的直线
    cv::fitLine(centers_change, line_para, cv::DIST_L1, 0, 1e-2, 1e-2);
    //cv::fitLine(centers_change, line_para, cv::DIST_L2, 0, 1e-2, 1e-2);
    //获取点斜式的点和斜率
 
	cv::Point point0;
 
	point0.x = line_para[2];
	point0.y = line_para[3];
    double k = line_para[1] / line_para[0];
    
    cv::Point point01,point02;
    point01.x = 0;
    point01.y = k * (0-point0.x)+point0.y;

    point02.x = 500;
    point02.y = k*(500-point0.x)+point0.y;
    
    cv::line(roi,point01,point02,cv::Scalar(0,255,0),2,8,0);

    cv::imshow("line_img",roi);

    cout<<"拟合秧苗线的斜率是："<<k<<endl;

    double lines_acrtan = atan (1/k);
    //double lines_acrtan = atan (k);
    double result = lines_acrtan * 180/PI;
    cout<<"拟合秧苗线相对于中央线倾斜的角度是："<<result<<endl;
    
    /*
    //把子图保存在指定的文件中
    for (int t=0; t < m;t++){
        //cout<<t<<endl;
        imwrite(outpath +to_string(name[t])+".jpg", ceil_img[t]); 
    }
    */

    time = ((double)getTickCount() - time)/getTickFrequency();
    cout << "Times passed in seconds: " << time << endl;
    cv::waitKey(0);
    return 0;
    }

    void EXG(const Mat &img, Mat &gray){
        gray = Mat(img.rows, img.cols, CV_8UC1);
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
		    //data1[x] = (int)(G*2 -B -R);//利用公式计算灰度值（加权平均法）
	         }
        }
    }
