#include "subscriber.h"

   
void BebopSubscriber::init()
{
    ros::init(init_argc, init_argv,"Bebop_mission_plan");
    ros::NodeHandle nh;

    this->position_sub = nh.subscribe("/bebop/states/ardrone3/PilotingState/PositionChanged",1, &BebopSubscriber::positionCallback, this);
    this->altitude_sub = nh.subscribe("/bebop/states/ardrone3/PilotingState/AltitudeChanged",1,&BebopSubscriber::altitudeCallback, this);
    this->attitude_sub = nh.subscribe("/bebop/states/ardrone3/PilotingState/AttitudeChanged",1,&BebopSubscriber::attitudeCallback,this);
}

BebopSubscriber::BebopSubscriber(int argc, char** argv){
    this->init_argc = argc;
    this->init_argv = argv;

    this->latitude = this->longitude = this-> altitude = this->altitude2 = 0;
    this->attitude = 0;

}

void BebopSubscriber::positionCallback(const bebop_msgs::Ardrone3PilotingStatePositionChanged::ConstPtr& msg)
{
    //ROS_INFO("position");
    this->latitude = msg->latitude;
    this->longitude = msg->longitude;
    this->altitude = msg->altitude;
    // ROS_INFO("latitude : %f, longitude : %f, altitude : %f", this->latitude, this-> longitude,
    // this->altitude);
}

void BebopSubscriber::altitudeCallback(const bebop_msgs::Ardrone3PilotingStateAltitudeChanged::ConstPtr& msg)
{
    this->altitude2 = msg->altitude;
    //ROS_INFO("altitude2 : %f", this->altitude2);
}


void BebopSubscriber::attitudeCallback(const bebop_msgs::Ardrone3PilotingStateAttitudeChanged::ConstPtr& msg)
{
    this->attitude = msg->yaw;
    //ROS_INFO("attitude yaw : %f", this->attitude);

}