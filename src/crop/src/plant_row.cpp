#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<ros/ros.h>
using namespace cv;
using namespace std;
#include<iostream>
#include<string>
#include <susan.h>
#include<fstream>

/* image gray */
void ConvertRGB2GRAY(const Mat &image, Mat &imageGray);
int OTSU(Mat imageGray);

int main()
{
    Mat img;
    
    cv::Mat dst;
    /* code for main function */

    /* read image */
    img = imread("/home/robot/pictures/new/00.jpg",1);

    if (img.empty())
    {
        printf("No image data \n");
        return -1;
    }

    /* show original image ,and set window size*/
    namedWindow("Display original Image", 0 );
    cvResizeWindow("Display original Image",640,480);
    imshow("Display original Image", img);
        
    Mat grayImage;
	ConvertRGB2GRAY(img, grayImage);
    namedWindow("Display gray Image",0);
    cvResizeWindow("Display gray Image",640,480);
    imshow("Display gray Image", grayImage);
    
    /*Call the otsu function to get the image*/
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
    
    namedWindow("Display otsuResult Image", 0 );
    cvResizeWindow("Display otsuResult Image",640,480);
    imshow("Display otsuResult Image", otsuResultImage);


    Mat dilate_dst, gray, erode_dst,open,close, dfs;
    Mat element = getStructuringElement(MORPH_RECT, Size(8, 8));

	dilate(otsuResultImage, dilate_dst, element);
	erode(otsuResultImage, erode_dst, element);
    
    morphologyEx(otsuResultImage, open, MORPH_OPEN, element);
    morphologyEx(otsuResultImage, close, MORPH_CLOSE, element);
	morphologyEx(otsuResultImage, dfs, MORPH_GRADIENT, element);
    
    namedWindow("Display Morphological operation", 0 );
    cvResizeWindow("Display Morphological operation",640,480);
    imshow("Display Morphological operation", erode_dst);
    
    /*
    Mat edge_img = Susan(img, 5);
	namedWindow("edge_image", 0 );
    cvResizeWindow("edge_image",640,480);
	imshow("edge_image", edge_img);
    */

    Mat cornerStrength;
    cornerHarris(erode_dst,cornerStrength,2,3,0.01);
    
	threshold(cornerStrength, cornerStrength, 0.0001, 255, THRESH_BINARY);
    namedWindow("shiyan", 0 );
    cvResizeWindow("shiyan",640,480);
	imshow("shiyan", cornerStrength);   
    

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
