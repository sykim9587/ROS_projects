#ifndef TURTLEBOT3_PARKING_H
#define TURTLEBOT3_PARKING_H

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Image.h>
#include <math.h>

class Parking
{
private:
    ros::Publisher cmd_pub;
    ros::Subscriber marker_sub;
    ros::Subscriber markercont_sub;

    int argc;
    char** argv;

    visualization_msgs::Marker marker;
    geometry_msgs::Twist twist;

    int target_marker; //for now



public:
    bool is_find_tag;
    bool is_target_angle;
    bool is_target_distnace;
    bool is_turn_degree;
    bool is_destination;
    Parking(int argc, char** argv,int target_marker);
    void poseCallback(const visualization_msgs::Marker::ConstPtr& msg1);
    void contCallback(const sensor_msgs::Image::ConstPtr& msg2);
    void get_tag(); //searching for the marker by spinning and stop when it detects
    void move_to_target_angle();
    void move_to_target_distnace();
    void turn_ninety_degree();
    void close_to_marker();
};

#endif //TURTLEBOT3_PARKING_H