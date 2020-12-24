#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

#define PIC_PATH "/home/robot/pictures/"
#define PIC_NAME "00.jpg"

using namespace cv;
using namespace std;
Mat src, gray_src,dst;

int threshold_value = 200;
int threshold_max = 255;
void Draw_Demo(int, void*);
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
int main(void)
{
	string pic = string(PIC_PATH) + string(PIC_NAME);
	cout << "原始图片为:" << pic << endl;

	src = imread(pic);
	if (src.empty()) {
		cout << "图片不存在" << endl;
		return -1;
	}
	namedWindow("原始图片", WINDOW_AUTOSIZE);
	imshow("原始图片", src);

	//cvtColor(src, gray_src, CV_BGR2GRAY);   //图片转化为灰度图
	//namedWindow("灰度图片", WINDOW_AUTOSIZE);
	//imshow("灰度图片", gray_src);
    EXG(src,gray_src);
    imshow("gray image", gray_src);

	//均值模糊去除噪点干扰
	blur(gray_src, gray_src, Size(3, 3), Point(-1, -1));
	
	namedWindow("绘制图片", WINDOW_AUTOSIZE);
	namedWindow("阈值操作", WINDOW_AUTOSIZE);
	
	//创建滑动条 用来动态调整阈值范围
	createTrackbar("阈值调整", "阈值操作", &threshold_value, threshold_max, Draw_Demo);
	Draw_Demo(0, 0);   //什么也不做  保证回调函数 程序一运行就显示

	waitKey(0);
	cvDestroyAllWindows();
}

void Draw_Demo(int, void*)
{
	Mat threshold_dst;
	threshold(gray_src, threshold_dst, threshold_value, threshold_max, CV_THRESH_BINARY);
	imshow("阈值操作", threshold_dst);

	vector<vector<Point> > contours_points;
	vector<Vec4i> hierarchy;

	findContours(threshold_dst, contours_points, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	//namedWindow("轮廓图片", WINDOW_AUTOSIZE);

	vector<vector<Point>> contours_ploy(contours_points.size());    //定义精简过后的轮廓点集合
	vector<Rect> ploy_rects(contours_points.size());             //定义矩形集合
	vector<Point2f> ccs(contours_points.size());               //定义圆心坐标集合
	vector<float> radius(contours_points.size());               //定义半径集合

	vector<RotatedRect> rotated_rect(contours_points.size());   //定义最小矩形集合 带旋转角度的
	vector<RotatedRect> cir_rotated_rect(contours_points.size());   //定义椭圆所在最小矩形 带旋转角度
	for (size_t i = 0; i < contours_points.size(); i++)
	{
		approxPolyDP(contours_points[i], contours_ploy[i], 3, true);
		ploy_rects[i] = boundingRect(contours_ploy[i]);     //获取平行于边界的矩形集合
		minEnclosingCircle(contours_ploy[i], ccs[i], radius[i]);   //获取圆形圆心和半径集合
		if (contours_ploy[i].size() > 5)   //这两个函数对输入参数点的数量有要求  这里需要预处理
		{
			rotated_rect[i] = minAreaRect(contours_ploy[i]);   //获取最小矩形集合
			cir_rotated_rect[i] = fitEllipse(contours_ploy[i]); //获取最小椭圆所在矩形集合
		}
	}

	src.copyTo(dst);    //复制图片
	RNG rng(123456);    //定义随机数
	Point2f p[4];   //四个角的坐标集合
	for (size_t j = 0; j < contours_points.size(); j++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));   //随机颜色
		rectangle(dst, ploy_rects[j], color, 2, 8);    //绘制平行边界的矩形
		circle(dst, ccs[j], radius[j], color, 2, 8);   //绘制圆形

		if (contours_ploy[j].size() > 5)
		{
			rotated_rect[j].points(p);  //返回四个角的列表
			ellipse(dst, cir_rotated_rect[j], color, 2, 8);   //绘制椭圆
			for(int k=0;k<4;k++)
				line(dst, p[k], p[(k + 1) % 4], color, 2, 8);   //绘制带角度的最小的矩形   （k+1）%4防止数组越界
		}
	}
	imshow("绘制图片", dst);
}
