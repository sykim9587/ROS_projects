#include "logger.h"
   
void Logger::init()
{
    ros::init(init_argc, init_argv,"Bebop_Logger");
    ros::NodeHandle nh;

    this->battery_sub = nh.subscribe("/bebop/states/common/CommonState/BatteryStateChanged",1, &Logger::batteryCallback, this);
    this->odom_sub = nh.subscribe("/bebop/odom",1,&Logger::odometryCallback, this);
    this->position_sub = nh.subscribe("/bebop/states/ardrone3/PilotingState/PositionChanged",1,&Logger::positionCallback,this);

    while(ros::ok())
    {
        ros::spinOnce();
        this->status.insert_status(this->status_cnt,this->droneId,this->latitude, this->longitude, this->altitude, this->percent);
        this->status_cnt++;
    }
}

Logger::Logger(int argc, char** argv, const char* droneName){
    this->init_argc = argc;
    this->init_argv = argv;

    this->droneInfo = DroneInfo("localhost","root","rosemfhs","mydb",3306);
    this->status = Status("localhost","root","rosemfhs","mydb",3306);

    this->droneName = droneName;
    this->droneId = droneInfo.get_DroneID_byname(this->droneName);

    this->latitude = this->longitude = this-> altitude = this->percent = 0;
    this->status_cnt = 1;

}

void Logger::batteryCallback(const bebop_msgs::CommonCommonStateBatteryStateChanged::ConstPtr& msg)
{
    ROS_INFO("Battery : %d", msg->percent); //int
    this->percent = msg ->percent;
}

void Logger::odometryCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
    this->positionX = msg->pose.pose.position.x;
    this->positionY = msg->pose.pose.position.y;
    this->positionZ = msg->pose.pose.position.z;

    this->orientationX = msg->pose.pose.orientation.x;
    this->orientationY = msg->pose.pose.orientation.y;
    this->orientationZ = msg->pose.pose.orientation.z;

    this->linearX = msg->twist.twist.linear.x;
    this->linearY = msg->twist.twist.linear.y;
    this->linearZ = msg->twist.twist.linear.z;
}


void Logger::positionCallback(const bebop_msgs::Ardrone3PilotingStatePositionChanged::ConstPtr& msg)
{
    this->altitude = msg->altitude;
    this->longitude = msg->longitude;
    this->latitude = msg->latitude;

}