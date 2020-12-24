#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<ros/ros.h>
using namespace cv;
using namespace std;
#include<iostream>
#include<string>
#include<fstream>

void ConvertRGB2GRAY(const Mat &image, Mat &imageGray);
int OTSU(Mat imageGray);

int main(int argc, char *argv[])
{
    /* code for main function */
    Mat img;
    Mat dst;
    Mat src = cv::imread("/home/robot/pictures/07.png");
    imshow("Display original Image", img);
    
    //ROI
    img = imread("/home/robot/pictures/00.jpg");
    Mat roi=img(Rect(150,0,280,480));
    Mat img1;
    roi.copyTo(img1);
    imshow("ROI-image",img1);

    //gray
    Mat grayImage;
	ConvertRGB2GRAY(img1, grayImage);
    imshow("Display gray Image", grayImage);

    int otsuThreshold = OTSU(grayImage);
    //Define the output result image
    Mat otsuResultImage = Mat::zeros(grayImage.rows, grayImage.cols, CV_8UC1);
    for (int i = 0; i < grayImage.rows; i++)
    {
        for (int j = 0; j < grayImage.cols; j++)
        {
                cvtColor(img,dst,CV_BGR2GRAY);//cout << (int)srcGray.at<uchar>(i, j) << endl;
            //
            if (grayImage.at<uchar>(i, j) > otsuThreshold)
            {
                otsuResultImage.at<uchar>(i, j) = 255;
            }
            else
            {
                otsuResultImage.at<uchar>(i, j) = 0;
            }
            //cout <<(int)otsuResultImage.at<uchar>(i, j) << endl;
        }
    }
    
    imshow("Display otsuResult Image", otsuResultImage);
    Mat dilate_dst, gray, erode_dst,open,close, dfs;
    Mat element = getStructuringElement(MORPH_RECT, Size(2,2));

	dilate(otsuResultImage, dilate_dst, element);
	erode(otsuResultImage, erode_dst, element);
    
    morphologyEx(otsuResultImage, open, MORPH_OPEN, element);
    morphologyEx(otsuResultImage, close, MORPH_CLOSE, element);
	morphologyEx(otsuResultImage, dfs, MORPH_GRADIENT, element);
    
    
    imshow("Display Morphological operation", erode_dst);

    waitKey(0);
    return 0;
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

int OTSU(Mat srcImage) {
    int nCols = srcImage.cols;
    int nRows = srcImage.rows;
    int threshold = 0;
    //init the parameters
    int nSumPix[256];
    float nProDis[256];
    for (int i = 0; i < 256; i++)
    {
        nSumPix[i] = 0;
        nProDis[i] = 0;
    }

    
    for (int i = 0; i < nRows; i++)
    {
        for (int j = 0; j < nCols; j++)
        {
            nSumPix[(int)srcImage.at<uchar>(i, j)]++;
        }
    }

    
    for (int i = 0; i < 256; i++)
    {
        nProDis[i] = (float)nSumPix[i] / (nCols*nRows);
    }

    

    float w0, w1, u0_temp, u1_temp, u0, u1, delta_temp;
    double delta_max = 0.0;
    for (int i = 0; i < 256; i++)
    {
        
        w0 = w1 = u0 = u1 = u0_temp = u1_temp = delta_temp = 0;
        for (int j = 0; j < 256; j++)
        {
            
            if (j <= i)
            {
                w0 += nProDis[j];
                u0_temp += j*nProDis[j];
            }
            
            else
            {
                w1 += nProDis[j];
                u1_temp += j*nProDis[j];
            }
        }
        
        u0 = u0_temp / w0;
        u1 = u1_temp / w1;
        
        delta_temp = (float)(w0*w1*pow((u0 - u1), 2)); 
        if (delta_temp > delta_max)
        {
            delta_max = delta_temp;
            threshold = i;
        }
   }
    return threshold;
}
