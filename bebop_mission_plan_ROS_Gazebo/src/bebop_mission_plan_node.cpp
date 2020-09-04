#include <iostream>
#include "point_to_point.h"
#include "subscriber.h"

int main(int argc, char** argv)
{
    BebopSubscriber bebopsub = BebopSubscriber(argc, argv);
    bebopsub.init();
    PointToPoint beboppub = PointToPoint(argc, argv);
    
    while(1){
    beboppub.takeoff();
    ros::spinOnce();
    if(bebopsub.altitude2 >= 0.9 && bebopsub.altitude2 <= 1.1)
        break;

    }
   
    ROS_INFO("take off done");
    while(1)
    {
        ros::spinOnce();
        ROS_INFO("checking");
        beboppub.checkTarget(bebopsub.latitude,bebopsub.longitude,bebopsub.altitude2,
        bebopsub.attitude); 
        
        if(beboppub.isFinish)
            break;

    }
    
    while(1){
        beboppub.land();
        ROS_INFO("land done");
    }
    
    return 0;
}