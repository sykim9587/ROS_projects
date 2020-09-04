#include "point_to_point.h"


PointToPoint::PointToPoint(int argc, char** argv)
{
    //value initializing
    this->argc = argc;
    this->argv = argv;
    
    this->tarLat = 36.519640;  //36.519 //48.87896 //36.52048
    this->tarAlt = 2;
    this->tarLog = 127.172944; //127.172 //2.36777
    this->tarAtt = 0;

    this->isTarAlt = true;
    this->isTarAtt = false;
    this->isTarLatLog = false;
    this->isFinish = false;

    ros::init(this->argc, this->argv, "point_to_point_node");
    ros::NodeHandle nh;
    this->cmd_pub = nh.advertise<geometry_msgs::Twist>("/bebop/cmd_vel",1);
    this->takeoff_pub = nh.advertise<std_msgs::Empty>("/bebop/takeoff",1);
    this->land_pub = nh.advertise<std_msgs::Empty>("/bebop/land",1);
}

void PointToPoint::takeoff()
{
    
    std_msgs::Empty empty_msgs;
    this->takeoff_pub.publish(empty_msgs);
}


void PointToPoint::checkTarget(double lat, double log, double alt, double att)
{
    if(this->isTarAlt)
    {
        ROS_INFO("Altitude checking");
        geometry_msgs::Twist twist;

        twist.linear.x = 0;       //forward, backward (-)
        twist.linear.y = 0;         //left (+), and right (-)
        twist.linear.z = 0.1;         //up(+), down (-)

        twist.angular.x = 0;
        twist.angular.y = 0;
        twist.angular.z = 0;        //left turn, right turn (-)

        this->cmd_pub.publish(twist);
        ros::Duration(1).sleep();

        if((alt <= (this->tarAlt + 0.1)) && (alt >= (this->tarAlt - 0.1))){
            this->isTarAlt = false;
            this->isTarAtt = true;
        }
    }
    else if(this->isTarAtt)
    {
        ROS_INFO("attitude checking");
        
        //getting the target angle
        double lat1 = (lat * 3.14)/180;
        double lat2 = (this->tarLat*3.14)/180;
        double lon_diff = (this->tarLog - log) * (3.14/180);
        double y = sin(lon_diff) * cos(lat2);
        double x = cos(lat1) * sin(lat2) - sin(lat1)*cos(lat2)*cos(lon_diff);

        this->tarAtt = atan2(y,x);

        double var = att - this->tarAtt;
        double turn = 0.0;
        if (var >= 0 && var<=3.14)
            turn = 0.1;
        else
        {
            turn = -0.1;
        }
        
        ROS_INFO("%f",this->tarAtt);



        geometry_msgs::Twist twist;
        twist.linear.x = 0;       //forward, backward (-)
        twist.linear.y = 0;         //left (+), and right (-)
        twist.linear.z = 0;         //up(+), down (-)
        twist.angular.x = 0;
        twist.angular.y = 0;
        twist.angular.z = turn;        //left turn, right turn (-)

        cmd_pub.publish(twist);
        ros::Duration(1).sleep();

        if((att <= (this->tarAtt + 0.05)) && (att >= (this->tarAtt - 0.05))){
            this->isTarAtt = false;
            this->isTarLatLog = true;
        }
    }
    else if(this->isTarLatLog)
    {
        ROS_INFO("position checking");
        geometry_msgs::Twist twist;
        twist.linear.x = 0.2;       //forward, backward (-)
        twist.linear.y = 0;         //left (+), and right (-)
        twist.linear.z = 0;         //up(+), down (-)

        twist.angular.x = 0;
        twist.angular.y = 0;
        twist.angular.z = 0;        //left turn, right turn (-)

        this->cmd_pub.publish(twist);
        ros::Duration(1).sleep();

        if((lat <= (this->tarLat + 0.00005)) && (lat >= (this->tarLat - 0.00005))
            && (log <= (this->tarLog + 0.00005)) && (log >= (this->tarLog - 0.00005))){
            this->isTarLatLog = false;
            this->isFinish = true;
            ROS_INFO("while loop finish");
        }
    }

}


void PointToPoint::land()
{
    std_msgs::Empty empty_msgs;
    this->land_pub.publish(empty_msgs);
}
