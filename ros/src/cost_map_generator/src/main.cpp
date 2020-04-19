// cost_map_generator

#include "ros/ros.h"

#define RATE (20)

int main( int argc, char** argv){

    ros::init(argc, argv, "cost_map_generator");

    ros::Rate rate(RATE);

    while( ros::ok() ){

	ros::spinOnce();
	rate.sleep();
    }

    return 0;
}
