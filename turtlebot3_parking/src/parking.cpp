#include "parking.h"

Parking::Parking(int argc, char** argv,int target_marker)
{
    this->argc = argc;
    this->argv = argv;
    this->target_marker = target_marker;

    ros::init(this->argc, this->argv, "turtlebot3_parking_node");
    ros::NodeHandle nh;

    this->marker_sub = nh.subscribe("/aruco_multi/marker",1, &Parking::poseCallback,this);
    this->markercont_sub = nh.subscribe("/aruco_multi/result",1, &Parking::contCallback,this);
    this->cmd_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel",1);
}

void Parking::poseCallback(const visualization_msgs::Marker::ConstPtr& msg1)
{
    this->marker.id = msg1->id;
    this->marker.pose = msg1->pose;

    get_tag(); //constructor -> posecallback -> finding
}


void Parking::contCallback(const sensor_msgs::Image::ConstPtr& msg2)
{
    ROS_INFO("STILL FINDING>>>");
    this->twist.linear.x = 0;
    this->twist.linear.y = 0;
    this->twist.linear.z = 0;
    this->twist.angular.x = 0;
    this->twist.angular.y = 0;
    if (this->marker.id != target_marker)
        this->twist.angular.z = 0.2;
    else
    {
        this->twist.angular.z = 0;
    }
    

    this-> cmd_pub.publish(this->twist);
}

void Parking::get_tag()
{
    if(this->marker.id == target_marker)    //stop
    {
        ROS_INFO("FOUND MARKER : %d",this->marker.id);
        this->twist.linear.x = 0;
        this->twist.linear.y = 0;
        this->twist.linear.z = 0;
        this->twist.angular.x = 0;
        this->twist.angular.y = 0;
        this->twist.angular.z = 0;

        this-> cmd_pub.publish(this->twist);
        is_find_tag = true;
    }
    else    //spin
    {
        ROS_INFO("STILL FINDING>>>");
        this->twist.linear.x = 0;
        this->twist.linear.y = 0;
        this->twist.linear.z = 0;
        this->twist.angular.x = 0;
        this->twist.angular.y = 0;
        this->twist.angular.z = 0.2;

        this-> cmd_pub.publish(this->twist);
    }
}

void Parking::move_to_target_angle()
{
    ROS_INFO("moving to target angle>>>");
    double target_angle =(90*3.14/180)-atan2(this->marker.pose.position.y, this->marker.pose.position.x);
    int wise = 1;

    if(marker.pose.orientation.z < 0)
        wise = 1;
    else
    {
        wise = -1;
    }

    //0.05rad/s is maximum speed, so do for 2secs if 1sec is not enough
    if(target_angle > 0.05 || target_angle < -0.05)
    {
        this->twist.linear.x = 0;
        this->twist.linear.y = 0;
        this->twist.linear.z = 0;
        this->twist.angular.x = 0;
        this->twist.angular.y = 0;
        this->twist.angular.z = (target_angle * wise) / 2;

        this->cmd_pub.publish(this->twist);

        ros::Duration(2).sleep();        
    }
    else
    {
        this->twist.linear.x = 0;
        this->twist.linear.y = 0;
        this->twist.linear.z = 0;
        this->twist.angular.x = 0;
        this->twist.angular.y = 0;
        this->twist.angular.z = (target_angle * wise);

        this->cmd_pub.publish(this->twist);

        ros::Duration(1).sleep();
    }
    is_target_angle = true;
    ROS_INFO("finished moving to target angle>>>");
     
}

void Parking::move_to_target_distnace()
{
    ROS_INFO("moving to target distance>>>");
    double target_distance = sqrt(pow(this->marker.pose.position.x,2) + pow(this->marker.pose.position.y,2));
    double target_linear = target_distance * cos(atan2(this->marker.pose.position.y, this->marker.pose.position.x)-(90*3.14/180));

    if(target_linear < 0.05 || target_linear > -0.05)
    {
        this->twist.linear.x = -target_linear;
        this->twist.linear.y = 0;
        this->twist.linear.z = 0;
        this->twist.angular.x = 0;
        this->twist.angular.y = 0;
        this->twist.angular.z = 0;   

        this->cmd_pub.publish(twist);
        ros::Duration(1).sleep();    
    }
    else
    {
        this->twist.linear.x = -target_linear/2;
        this->twist.linear.y = 0;
        this->twist.linear.z = 0;
        this->twist.angular.x = 0;
        this->twist.angular.y = 0;
        this->twist.angular.z = 0;   

        this->cmd_pub.publish(twist);
        ros::Duration(2).sleep();
    }

    is_target_distnace = true;
    ROS_INFO("finished moving to target angle>>>");
    
}

void Parking::turn_ninety_degree()
{
    ROS_INFO("moving 90 degree>>>");
    int wise = 1;

    if(marker.pose.orientation.z < 0)
        wise = 1;   //clockwise
    else
    {
        wise = -1;
    }

    this->twist.linear.x = 0;
    this->twist.linear.y = 0;
    this->twist.linear.z = 0;
    this->twist.angular.x = 0;
    this->twist.angular.y = 0;
    this->twist.angular.z = 1.58 * wise;   //added minus

    this->cmd_pub.publish(twist);
    ros::Duration(1).sleep();

    is_turn_degree = true;
    ROS_INFO("moving 90 degree>>>");
}

void Parking::close_to_marker()
{
    ROS_INFO("coming to the destination>>>");
    double target_linear = this->marker.pose.position.z;
    if(target_linear > 0.05)
    {
        this->twist.linear.x = target_linear/2;
        this->twist.linear.y = 0;
        this->twist.linear.z = 0;
        this->twist.angular.x = 0;
        this->twist.angular.y = 0;
        this->twist.angular.z = 0;     

        this->cmd_pub.publish(twist);
        ros::Duration(2).sleep(); 
    }
    else
    {
        this->twist.linear.x = target_linear;
        this->twist.linear.y = 0;
        this->twist.linear.z = 0;
        this->twist.angular.x = 0;
        this->twist.angular.y = 0;
        this->twist.angular.z = 0;     

        this->cmd_pub.publish(twist);
        ros::Duration(1).sleep();
    }

    //to make it stop at the end
    this->twist.linear.x = 0;
    this->twist.linear.y = 0;
    this->twist.linear.z = 0;
    this->twist.angular.x = 0;
    this->twist.angular.y = 0;
    this->twist.angular.z = 0;     

    this->cmd_pub.publish(twist);
    is_destination = true;
    ROS_INFO("finished coming to the destination>>>");
    
}

