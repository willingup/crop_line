#include <stdio.h>
#include<ros/ros.h>
using namespace std;
#include<iostream>
#include <geometry_msgs/Twist.h>
#include "robot.hpp"
#include "follow_crop/angle.h"


#ifdef __cplusplus
extern "C"{
#endif
#include "pid.h"
float PID_Position_float_2(float Angle , Pid_Structure *PID);
void PID_Init(Pid_Structure* pid);
#ifdef __cplusplus
}
#endif

void robot::angle_sub(follow_crop::angle msg) {
    //robot::dir = msg.direction;
    robot::fight_angle = msg.angle;
}

int main(int argc,char *argv[])
{   
    ros::init(argc, argv, "robot_pid_node");
    ros::NodeHandle nh_;
    robot myrobot;
    Pid_Structure PID_Message;
    PID_Init(&PID_Message); //初始化各变量
    geometry_msgs::Twist vel_cmd;

    ros::Publisher velocityPub = nh_.advertise<geometry_msgs::Twist>("/cmd_vel",10);
    ros::Subscriber anglesub = nh_.subscribe("/send_angle_topic",1, &robot::angle_sub, &myrobot);
    
    
    ros::Rate rate(10);
    while (ros::ok())
    {
        ros::spinOnce();
        vel_cmd.angular.z = PID_Position_float_2(myrobot.fight_angle,&PID_Message);
        cout<<vel_cmd.angular.z<<endl;
        velocityPub.publish(vel_cmd);
        rate.sleep();
    }
    
    return 0;
}