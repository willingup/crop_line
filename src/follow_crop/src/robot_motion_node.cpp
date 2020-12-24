#include <cv_bridge/cv_bridge.h>
#include <cstdlib>
#include <string>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"
#include "ros/ros.h"
#include "ros/console.h"
#include "robot.hpp"
#include "follow_crop/pos.h"

int main(int argc,char **argv) {

    // Initializing node and object
    ros::init(argc, argv, "Velocity");
    ros::NodeHandle n;
    robot myrobot;
    geometry_msgs::Twist velocity;
    
    // Creating subscriber and publisher 发布与订阅  订阅从detect中的消息，将速度发布到turtlebot
    ros::Subscriber sub = n.subscribe("/direction",1, &robot::dir_sub, &myrobot);
    
    //声明发布者,创建一个使用geometry_msg功能包Twist消息文件的发布者pub,话题名称是/cmd_vel，消息发布者队列设置为10
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
	
    //设定循环周期10HZ 0.1秒
    ros::Rate rate(10);
    while (ros::ok()) {
      
        //ros消息回调函数,通常在主函数中
        ros::spinOnce();
	
        // Publish velocity commands to robot
        myrobot.vel_cmd(velocity, pub, rate);
        rate.sleep();
    }
    return 0;
}