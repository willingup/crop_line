#pragma once
#include <geometry_msgs/Twist.h>
#include <vector>
#include "ros/ros.h"
#include "follow_crop/pos.h"
#include "follow_crop/angle.h"

class robot {
 public:
    int dir; 
    double fight_angle; 
    void dir_sub(follow_crop::pos msg);
    void angle_sub(follow_crop::angle msg);
    void vel_cmd(geometry_msgs::Twist &velocity,ros::Publisher &pub, ros::Rate &rate);
};