#ifndef BEBOP_SUB_H
#define BEPOP_SUB_H

#include <ros/ros.h>
#include <bebop_msgs/Ardrone3PilotingStatePositionChanged.h>
#include <bebop_msgs/Ardrone3PilotingStateAltitudeChanged.h>
#include <bebop_msgs/Ardrone3PilotingStateAttitudeChanged.h>
#include <iostream>


class BebopSubscriber
{
private:
    int init_argc;
    char** init_argv;

    ros::Subscriber position_sub;
    ros::Subscriber altitude_sub;
    ros::Subscriber attitude_sub; 
    

public:
    double latitude;
    double longitude;
    double altitude;

    double altitude2;   //from altitude changed msg
    double attitude;    //from attitude changed msg

    BebopSubscriber(int argc, char** argv);
    void init();
    void positionCallback(const bebop_msgs::Ardrone3PilotingStatePositionChanged::ConstPtr& msg);
    void altitudeCallback(const bebop_msgs::Ardrone3PilotingStateAltitudeChanged::ConstPtr& msg);
    void attitudeCallback(const bebop_msgs::Ardrone3PilotingStateAttitudeChanged::ConstPtr& msg);
};


#endif