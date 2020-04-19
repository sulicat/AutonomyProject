// Vehicle Controller

#include "ros/ros.h"

#define RATE (20)

int main( int argc, char** argv){

    ros::init(argc, argv, "local_planner");

    ros::Rate rate(RATE);

    while( ros::ok() ){

	ros::spinOnce();
	rate.sleep();
    }

    return 0;
}
