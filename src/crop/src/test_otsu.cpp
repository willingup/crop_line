#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;
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
 
 
void ConvertRGB2GRAY(const Mat &image, Mat &imageGray){
    imageGray = Mat::zeros(image.size(), CV_8UC1);
    uchar *pointImage = image.data;
	uchar *pointImageGray = imageGray.data;
    size_t stepImage = image.step;
	size_t stepImageGray = imageGray.step;
    cout<<23<<23;
    for (int i = 0; i < imageGray.rows; i++)
	{
		for (int j = 0; j < imageGray.cols; j++)
		{
			pointImageGray[i*stepImageGray + j] =
				(uchar)(2*pointImage[i*stepImage + 3 * j + 1] - pointImage[i*stepImage + 3 * j] - pointImage[i*stepImage + 3 * j + 2]);
		}
	}
}

int main(){
	cv::Mat src = cv::imread("/home/robot/pictures/00.jpg");
	if (src.empty()){
		return -1;
	}
    //img = imread("/home/robot/pictures/00.jpg");
    Mat roi=src(Rect(150,0,280,480));
    Mat img1;
    Mat img2;
    roi.copyTo(img1);

    cv::Mat grayImage;
	//使用了两种方法进行灰度处理  
	if (src.channels() > 1)
		cv::cvtColor(img1, img2, CV_RGB2GRAY);
    imshow("Display gray Image2", img2);

    ConvertRGB2GRAY(img1, grayImage);
    imshow("Display gray Image", grayImage);
   

	cv::Mat dst,dst2;
	int thresh=0;
	double t2 = (double)cv::getTickCount();

	thresh=Otsu(img2 , dst, thresh); //Otsu
	std::cout << "Mythresh=" << thresh << std::endl;
    
	t2 = (double)cv::getTickCount() - t2;
	double time2 = (t2 *1000.) / ((double)cv::getTickFrequency());
	std::cout << "my_process=" << time2 << " ms. " << std::endl << std::endl;
    double  Otsu = 0;
 
	Otsu=cv::threshold(grayImage, dst2, Otsu, 255, CV_THRESH_OTSU + CV_THRESH_BINARY);
	//std::cout << "OpenCVthresh=" << Otsu << std::endl;
 
	cv::namedWindow("src", CV_WINDOW_NORMAL);
	cv::imshow("src", src);
	cv::namedWindow("dst", CV_WINDOW_NORMAL);
	cv::imshow("dst", dst);
	cv::namedWindow("dst2", CV_WINDOW_NORMAL);
	cv::imshow("dst2", dst2);
    
	cv::waitKey(0);
}