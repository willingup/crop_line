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
    //original image
    Mat src = cv::imread("/home/robot/pictures/11.png");
    //imshow("original image", src);

    //ROI
    int width = src.cols;
    int height = src.rows;
    //Mat roi=src(Rect(width/3,0,width/3,height));
    Mat roi=src(Rect(100,0,260,height));
    Mat img1;
    roi.copyTo(img1);
    imshow("ROI-image",img1);
    Mat gray_img;

    //EXG image
    EXG(img1,gray_img);
    imshow("gray image", gray_img);

    Mat dst;
    int thresh=0;
    double t2 = (double)cv::getTickCount();
	thresh=Otsu(gray_img, dst, thresh);
    cv::namedWindow("OTSU", CV_WINDOW_NORMAL);
	cv::imshow("OTSU", dst);
    
    
    Mat close_img;
    Mat element = getStructuringElement(MORPH_RECT, Size(8, 8));
    morphologyEx(dst, close_img, MORPH_CLOSE, element);
    namedWindow("Display Morphological operation", 0 );
    imshow("Display Morphological operation",close_img);
    
    String outpath = "/home/robot/pictures/old/pic";
    
    int img_split_distance = 30;
    int m = close_img.rows /img_split_distance ;
    cout << "一共分为几段" << endl << m << endl; 
    std::vector<Mat> ceil_img;
    std::vector<int> name;
    
    int t = 0;
    for (t; t < m; t++)
       name.push_back(t);
    Mat image_cut, roi_img, tim_img;
    
    int i=1;
    
    for( i;i <=m;i++){
       //cout<<i<<endl;
       Rect rect(0, close_img.rows-img_split_distance*i, close_img.cols, img_split_distance);
       image_cut = Mat(close_img, rect);
       
       roi_img = image_cut.clone();
       ceil_img.push_back(roi_img);     
    }
    //cv::imshow("image_cut", image_cut);
    /*
    imwrite(outpath+to_string(name[0])+".jpg",ceil_img[0]);
    imwrite(outpath+to_string(name[1])+".jpg",ceil_img[1]);
    imwrite(outpath+to_string(name[2])+".jpg",ceil_img[2]);
    imwrite(outpath+to_string(name[3])+".jpg",ceil_img[3]);
    imwrite(outpath+to_string(name[4])+".jpg",ceil_img[4]);
    imwrite(outpath+to_string(name[5])+".jpg",ceil_img[5]);
    imwrite(outpath+to_string(name[6])+".jpg",ceil_img[6]);
    imwrite(outpath+to_string(name[7])+".jpg",ceil_img[7]);
    */
    
    for (int t=0; t < m;t++){
        cout<<t<<endl;
        imwrite(outpath +to_string(name[t])+".jpg", ceil_img[t]);
        
    }
    
    
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
