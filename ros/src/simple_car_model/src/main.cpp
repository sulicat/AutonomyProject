// Simple Vehicle Model

// The inputs for this module are:
//   U1: Linear Velocity of vehicle
//   U2: angular velocity of steering angle

// The output are:
//   vehicle_state: Published topic

#include "ros/ros.h"
#include "simple_car_model/VehicleState.h"
#include "simple_car_model/VehicleMoveCommand.h"
#include "std_msgs/String.h"

#include "BaseVehicle.h"
#include "ros_to_system.h"

#define RATE (100)

BaseVehicle vehicle_model;

void move_command_callback( simple_car_model::VehicleMoveCommand move_command){
    std::cout << "Got move command\n";
    std::cout << "  Move Command: vel" << move_command.linear_vel << "\n";
    std::cout << "  Move Command: steering vel" << move_command.steering_angle_vel << "\n";

    vehicle_model.linear_vel = move_command.linear_vel;
    vehicle_model.steering_angle_vel = move_command.steering_angle_vel;
}

void vehicle_teleport_callback( simple_car_model::VehicleState tele_pos){
    std::cout << "Got teleport command\n";
    std::cout << "\t" << "x: " << tele_pos.pos.x << "\n";
    std::cout << "\t" << "y: " << tele_pos.pos.y << "\n";
    std::cout << "\t" << "angle: " << tele_pos.vehicle_angle << "\n";

    vehicle_model.linear_vel = 0;
    vehicle_model.steering_angle = 0;
    vehicle_model.steering_angle_vel = 0;
    vehicle_model.pos.x = tele_pos.pos.x;
    vehicle_model.pos.y = tele_pos.pos.y;
    vehicle_model.vehicle_angle = tele_pos.vehicle_angle;

}


int main( int argc, char** argv){

    ros::init(argc, argv, "vehicle_model");
    ros::NodeHandle node_handle;

    ros::Rate rate(RATE);
    simple_car_model::VehicleState vehicle_state;
    ros::Publisher vehicle_state_pub = node_handle.advertise<simple_car_model::VehicleState>( "vehicle_state", 1 );
    ros::Subscriber sub = node_handle.subscribe("vehicle_move_command", 1000, move_command_callback);
    ros::Subscriber sub_tele = node_handle.subscribe("vehicle_teleport", 1, vehicle_teleport_callback);

    while( ros::ok() ){

	vehicle_model.update( 1.0 / (double)RATE );

	simple_car::model_to_state( vehicle_state,
				    vehicle_model );
	vehicle_state_pub.publish(vehicle_state);

	ros::spinOnce();
	rate.sleep();
    }

    return 0;
}
