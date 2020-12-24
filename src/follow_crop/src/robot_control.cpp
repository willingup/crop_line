#include <geometry_msgs/Twist.h>
#include <vector>
#include "ros/ros.h"
#include "ros/console.h"
#include "robot.hpp"
#include "follow_crop/pos.h"

void robot::dir_sub(follow_crop::pos msg) {
    robot::dir = msg.direction;
}

void robot::vel_cmd(geometry_msgs::Twist &velocity,ros::Publisher &pub, ros::Rate &rate){
    
    // If direction is left
    if (robot::dir == 0) {
        velocity.linear.x = 0.1;
        velocity.angular.z = 0.1;       
        pub.publish(velocity);
        rate.sleep();
        ROS_INFO_STREAM("Turning Left");
    }
    // If direction is straight
    if (robot::dir == 1) {
        velocity.linear.x = 0.1;
        velocity.angular.z = 0;
        pub.publish(velocity);
        rate.sleep();
        ROS_INFO_STREAM("Straight");
    }
    // If direction is right
    if (robot::dir == 2) {
        velocity.linear.x = 0.1;
        velocity.angular.z = -0.1;
        pub.publish(velocity);
        rate.sleep();
        ROS_INFO_STREAM("Turning Right");
    }
    
}