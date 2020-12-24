#include <opencv2/core.hpp> 
#include <opencv2/imgcodecs.hpp> 
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp> 
#include <iostream> 

using namespace cv; 
using namespace std;
 
int main() 
{ 
 //相机打开，初始化并分配内存以从摄像机加载视频流，分辨率为320*240、1280*720（延迟太大）、720*480 
 //initialize and allocate memory to load the video stream from camera 
 VideoCapture camera0(0);
 camera0.set(CAP_PROP_FRAME_WIDTH, 640); 
 camera0.set(CAP_PROP_FRAME_HEIGHT, 480); 
 
 if (!camera0.isOpened()) return 1; 

 int a = 1; 
 int f = 1; 
 while (true) { 
 //依次抓取和检索视频的每个帧 
 //grab and retrieve each frames of the video sequentially 
  Mat3b frame0; 
  camera0 >> frame0; 

  imshow("Video0", frame0);

  //std::cout << frame1.rows() << std::endl; 
  //wait for 40 milliseconds 
 
  int c = waitKey(20); 
  //exit the loop if user press "Esc" key (ASCII value of "Esc" is 27)
 
  if (27 == char(c)) break; 
 
  int b = waitKey(20);
  if (32 == char(b)) { 
     imwrite("/home/robot/pictures/crop_pic//" + to_string(a++) + ".png", frame0); 
  } 
  
  
 } 
 return 0; 
}

