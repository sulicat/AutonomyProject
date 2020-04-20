// Global Planner

#include "ros/ros.h"
#include "global_planner/VehicleState.h"
#include "global_planner/CostMap.h"
#include "global_planner/Trajectory.h"
#include <std_msgs/Empty.h>
#include "global_planner.h"

#define RATE (20)

global_planner::CostMap cost_map;
global_planner::VehicleState vehicle_state;
global_planner::VehicleState end_goal;
ros::Publisher pub_global_plan;

void cost_map_callback( global_planner::CostMap cost_map_in ){
    cost_map = cost_map_in;
}

void start_plan_callback( std_msgs::Empty e ){
    global_planner::Trajectory out = create_global_plan( vehicle_state, end_goal, cost_map );
    std::cout << "Created plan with: " << out.points.size() << " points\n";
    pub_global_plan.publish(out);
}

void vehicle_state_callback( global_planner::VehicleState vs_in ){
    vehicle_state = vs_in;
}

void end_goal_callback( global_planner::VehicleState eg_in ){
    end_goal = eg_in;
}

int main( int argc, char** argv){

    ros::init(argc, argv, "global_planner");
    ros::NodeHandle node_handle;
    ros::Subscriber sub_veh_state = node_handle.subscribe("vehicle_state", 1, vehicle_state_callback);
    ros::Subscriber sub_end_goal = node_handle.subscribe("end_goal", 1, end_goal_callback);
    ros::Subscriber sub_cost_map = node_handle.subscribe("cost_map_global", 1, cost_map_callback);
    ros::Subscriber sub_start = node_handle.subscribe("global_start_command", 1, start_plan_callback);
    pub_global_plan = node_handle.advertise<global_planner::Trajectory>( "global_plan", 1 );;

    ros::Rate rate(RATE);

    while( ros::ok() ){

	ros::spinOnce();
	rate.sleep();
    }

    return 0;
}
