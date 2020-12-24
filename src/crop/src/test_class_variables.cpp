#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp"  
#include "opencv2/core/core.hpp"
#include <opencv/ml.h>
#include <iostream>
#include "cv.h"
#include "highgui.h"
#include <vector>
#include <math.h>
#include <string.h>
#include <fstream>
using namespace std;
using namespace cv;
 
class Detector{
     public:
        float first_white_pixel=0;
        int first_mark=1;

        int xiugaivules(){
            if (first_mark!=0)
            {
                /* code for True */
                xiugai2();
                cout<<"B:first_mark"<<first_mark<<endl;
            }
            
            
        }
        int xiugai2(){
            first_mark = first_mark +10;
        }
        Detector(){
           
            for(int i=0;i<10;i++){
                
                 xiugaivules();
                 cout<<i<<endl;
            
            }           
           
        }
        ~Detector(){

        }

};
int main()
{
	//写这个的目的是为了什么呢，是为了，测试类成员函数和类成员
    Detector detec;
	cout<<"A:"<<detec.first_mark<<endl;
	
	return 0;
}
 