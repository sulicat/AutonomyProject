// Simple Vehicle Model

// The inputs for this module are:
//   U1: Linear Velocity of vehicle
//   U2: angular velocity of steering angle

// The output are:
//   vehicle_state: Published topic

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "simple_car_model/VehicleState.h"
#include "simple_car_model/VehicleMoveCommand.h"
#include "BaseVehicle.hpp"

#define RATE (20)

BaseVehicle vehicle_model;

void veh_model_to_veh_state( simple_car_model::VehicleState& veh_state,
			     BaseVehicle veh_model ){

    veh_state.pos.x = veh_model.pos.x;
    veh_state.pos.y = veh_model.pos.y;
    veh_state.vel.x = veh_model.vel.x;
    veh_state.vel.y = veh_model.vel.y;
    veh_state.accel.x = veh_model.accel.x;
    veh_state.accel.y = veh_model.accel.y;
    veh_state.steering_angle = veh_model.steering_angle;
    veh_state.vehicle_angle = veh_model.vehicle_angle;
    veh_state.vehicle_width = veh_model.width;
    veh_state.vehicle_length = veh_model.length;
}


void move_command_callback( simple_car_model::VehicleMoveCommand move_command){
    std::cout << "Got move command\n";
    std::cout << "  Move Command: vel" << move_command.linear_vel << "\n";
    std::cout << "  Move Command: steering vel" << move_command.steering_angle_vel << "\n";

    vehicle_model.linear_vel = move_command.linear_vel;
    vehicle_model.steering_angle_vel;
}


int main( int argc, char** argv){

    ros::init(argc, argv, "vehicle_model");
    ros::NodeHandle node_handle;

    ros::Rate rate(RATE);
    simple_car_model::VehicleState vehicle_state;
    ros::Publisher vehicle_state_pub = node_handle.advertise<simple_car_model::VehicleState>( "vehicle_state", 1 );
    ros::Subscriber sub = node_handle.subscribe("vehicle_move_command", 1000, move_command_callback);

    while( ros::ok() ){

	vehicle_model.update( 1.0 / (double)RATE );

	veh_model_to_veh_state( vehicle_state,
				vehicle_model );
	vehicle_state_pub.publish(vehicle_state);

	ros::spinOnce();
	rate.sleep();
    }

    return 0;
}
