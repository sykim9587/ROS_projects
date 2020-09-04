#ifndef BEBOP_LOGGER_H
#define BEPOP_LOGGER_H

#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <bebop_msgs/CommonCommonStateBatteryStateChanged.h>
#include <bebop_msgs/Ardrone3PilotingStatePositionChanged.h>
#include <iostream>
#include "status.h"
#include "Droneinfo.h"

class Logger
{
private:
    int init_argc;
    char** init_argv;

    ros::Subscriber odom_sub;
    ros::Subscriber battery_sub;
    ros::Subscriber position_sub;

    int percent;
    double positionX;
    double positionY;
    double positionZ;
    double orientationX;
    double orientationY;
    double orientationZ;
    double linearX;
    double linearY;
    double linearZ;

    double latitude;
    double longitude;
    double altitude; 

    DroneInfo droneInfo;
    Status status;

    int status_cnt;
    const char* droneName;
    int droneId;
    

public:
    Logger(int argc, char** argv, const char* droneName);
    void init();
    void batteryCallback(const bebop_msgs::CommonCommonStateBatteryStateChanged::ConstPtr& msg);
    void odometryCallback(const nav_msgs::Odometry::ConstPtr& msg);
    void positionCallback(const bebop_msgs::Ardrone3PilotingStatePositionChanged::ConstPtr& msg);
};


#endif
