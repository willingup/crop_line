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
    int w=30;
    int img_split_distance = 20;
    //original image
    Mat src = cv::imread("/home/robot/pictures/10.jpg");
    imshow("original image", src);

    //ROI image
    //Mat roi=src(Rect(150,0,280,480));
    //Mat roi=src(Rect(100,100,230,200));
    int width = src.cols;
    int height = src.rows;
    Mat roi=src(Rect(160,0,160,height));
    Mat img1;
    roi.copyTo(img1);
    imshow("ROI-image",img1);
    
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
    String outpath = "/home/robot/pictures/old/pic";
    int t = 0;
    int m = close_img.rows /img_split_distance ;
    
    std::vector<Mat> ceil_img;
    std::vector<int> name;

    for (t; t < m; t++)
       name.push_back(t);
    Mat image_cut, roi_img, tim_img;
    vector<Point> centers;
    int i=0;
    for(i;i <m;i++){
       cout<<i<<endl;
       Rect rect(0, close_img.rows-img_split_distance*(i+1), close_img.cols, img_split_distance);
       image_cut = Mat(close_img, rect);
       
       vector<vector<Point> > contours;
       vector<Vec4i> hierarchy;
       findContours(image_cut, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE,Point(0,0)); //CV_RETR_EXTERNAL只检测外部轮廓，可根据自身需求进行调整
       //findContours(image_cut, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE,Point(0,0));
       Mat contoursImage(image_cut.rows, image_cut.cols, CV_8U, Scalar(255));
       cout<<123<<endl;
       for (int index = 0; index >= 0; index = hierarchy[index][0]) {
           
		   cv::Scalar color(rand() & 255, rand() & 255, rand() & 255);
		   //cv::drawContours(contoursImage, contours, index, Scalar(0), 3, 8, hierarchy);
           cout<<123<<endl;
		   Rect rect = boundingRect(contours[index]); //检测外轮廓
           //RotatedRect rect = minAreaRect(contours[index]);
           cout<<123<<endl;
           if (rect.width < 10)     //去掉小的矩阵框
			   continue;

           cv::Point pt1,pt2_center,pt3;
           pt2_center.x = rect.x + rect.width/2;
           pt2_center.y = rect.y + rect.height/2;

		   rectangle(contoursImage, rect, Scalar(0,0,255), 1); //对外轮廓加矩形框
           cv::circle(contoursImage,pt2_center,1, (255, 0, 0), 2, 8, 0);
           
           if (pt2_center.x<image_cut.cols/2+w)
           {
               if(image_cut.cols/2-w < pt2_center.x){
                    pt3.x = pt2_center.x;
                    pt3.y = close_img.rows-img_split_distance*i+pt2_center.y;
                    centers.push_back(pt3);
               }  
           }           
      }
       roi_img = contoursImage.clone();
       ceil_img.push_back(roi_img);
    }
    //cout << "image_cut 图像的中点" << endl << image_cut.cols/2 << endl;
    cout << "特征点的集合" << endl << centers << endl;  

    
    //将分割之后的图像显示在各个子图中，保存在某个文件夹中
    for (int t=0; t < m;t++){
        cout<<t<<endl;
        imwrite(outpath +to_string(name[t])+".png", ceil_img[t]);       
    }
    
     
     /*
     Mat cut_img = ceil_img[0];
     vector<vector<Point> > contours;
     vector<Vec4i> hierarchy;
     findContours(cut_img, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE); //CV_RETR_EXTERNAL只检测外部轮廓，可根据自身需求进行调整
     Mat contoursImage(cut_img.rows, cut_img.cols, CV_8U, Scalar(255));
  
     for (int index = 0; index >= 0; index = hierarchy[index][0]) {
		cv::Scalar color(rand() & 255, rand() & 255, rand() & 255);
		//cv::drawContours(contoursImage, contours, index, Scalar(0), 3, 8, hierarchy);
		Rect rect = boundingRect(contours[index]);//检测外轮廓
		rectangle(contoursImage, rect, Scalar(0,0,255), 3);//对外轮廓加矩形框
      }
    */

    //imwrite("/home/robot/pictures/00.jpg", contoursImage);
    //cv::imshow("contour_Image", contoursImage);
    
    
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
                float value = G*2 -B -R;
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
