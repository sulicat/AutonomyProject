// Simple Vehicle Model

// The inputs for this module are:
//   U1: Linear Velocity of vehicle
//   U2: angular velocity of steering angle

// The output are:
//   vehicle_state: Published topic

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "simple_car_model/VehicleState.h"
#include "BaseVehicle.hpp"

int main( int argc, char** argv){

    ros::init(argc, argv, "vehicle_model");
    ros::NodeHandle node_handle;
    ros::Rate rate(20); // 10 hz

    simple_car_model::VehicleState vehicle_state;
    ros::Publisher vehicle_state_pub = node_handle.advertise<simple_car_model::VehicleState>( "vehicle_state",
											     1 );

    while( ros::ok() ){

	vehicle_state.position.x = 100;
	vehicle_state_pub.publish(vehicle_state);

	ros::spinOnce();
	rate.sleep();
    }

    return 0;
}
