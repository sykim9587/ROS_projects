#ifndef BEBOP_POINT_H
#define BEBOP_POINT_H

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <math.h>
#include <std_msgs/Empty.h>

class PointToPoint
{
private:
    ros::Publisher cmd_pub;
    ros::Publisher takeoff_pub;
    ros::Publisher land_pub;

    int argc;
    char** argv;

    double tarLat;
    double tarLog;
    double tarAlt;
    double tarAtt;

    bool isTarAlt;
    bool isTarAtt;
    bool isTarLatLog;



public:
    PointToPoint(int argc, char** argv);
    void checkTarget(double lat, double log, double alt, double att); 
    void takeoff();
    void land();
    bool isFinish;
};


#endif 