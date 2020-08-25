#include "parking.h"

int main(int argc, char** argv)
{
    int target_marker = 685;

    Parking turtlebot3_parking(argc, argv, target_marker);

    while(ros::ok())
    {
        ros::spinOnce();
        if (turtlebot3_parking.is_find_tag == true){
            if(turtlebot3_parking.is_target_angle ==false)
                turtlebot3_parking.move_to_target_angle();
            else if(turtlebot3_parking.is_target_distnace == false)
                turtlebot3_parking.move_to_target_distnace();
            else if(turtlebot3_parking.is_turn_degree == false)
                turtlebot3_parking.turn_ninety_degree();
            else if(turtlebot3_parking.is_destination == false)
                turtlebot3_parking.close_to_marker();
                
        }
    }

    return 0;
    

}
