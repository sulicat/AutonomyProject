// Local Planner

#include <time.h>
#include <cstdio>
#include <ctime>
#include <chrono>

#include "ros/ros.h"
#include "local_planner/VehicleState.h"
#include "local_planner/Waypoint.h"
#include "local_planner/CostMap.h"
#include "local_planner/Trajectory.h"
#include "local_planner/Line.h"
#include "local_planner/RenderTree.h"

#include "node.h"
#include "RRT.h"

#define RATE (10)

local_planner::VehicleState vehicle_state;
local_planner::VehicleState end_goal;
local_planner::Trajectory global_plan;
local_planner::CostMap cost_map;
ros::Publisher pub_local_plan;
ros::Publisher pub_local_tree;

void vehicle_state_callback( local_planner::VehicleState _vs ){
    vehicle_state = _vs;
}

void end_goal_callback( local_planner::VehicleState _vs ){
    end_goal = _vs;
}

void cost_map_callback( local_planner::CostMap _cm ){
    cost_map = _cm;
}

void global_plan_callback( local_planner::Trajectory _gp ){
    global_plan = _gp;
}

bool plan_for( float time_alotted ){
	auto start_time = std::chrono::system_clock::now();
	double total_time = 0;

	local_planner::VehicleState goal;
	goal.pos.x = vehicle_state.pos.x + 20;
	goal.pos.y = vehicle_state.pos.y + 1;

	// create a tree at ther start
	RRT rrt( cost_map, vehicle_state, goal );
	rrt.reset_tree();
	int step_count = 0;

	while( total_time < time_alotted ){

	    // keep stepping the tree
	    rrt.step( step_count % 5 == 0 );

	    step_count += 1;
	    std::chrono::duration<double> time_diff = (std::chrono::system_clock::now() - start_time);
	    total_time += time_diff.count();
	    start_time = std::chrono::system_clock::now();
	}


	Node* out_tree = rrt.get_tree();
	pub_local_tree.publish( out_tree->create_render_tree() );

	local_planner::Trajectory out;
	out = out_tree->dfs_traj( rrt.goal );
	pub_local_plan.publish(out);


	std::cout << "[Local Planner] ran for: " << total_time << "\n";
	std::cout << "[Local Planner]   steps: " << step_count << "\n";
	std::cout << "[Local Planner]   path length: " << out.points.size() << "\n";

}


int main( int argc, char** argv){

    ros::init(argc, argv, "local_planner");
    ros::NodeHandle node_handle;
    ros::Rate rate(RATE);

    ros::Subscriber sub_veh_state = node_handle.subscribe("vehicle_state", 1, vehicle_state_callback);
    ros::Subscriber sub_end_goal = node_handle.subscribe("end_goal", 1, end_goal_callback);
    ros::Subscriber sub_cost_map = node_handle.subscribe("cost_map_local", 1, cost_map_callback);
    ros::Subscriber sub_global_plan = node_handle.subscribe("global_plan", 1, global_plan_callback);
    pub_local_plan = node_handle.advertise<local_planner::Trajectory>( "local_plan", 1 );
    pub_local_tree = node_handle.advertise<local_planner::RenderTree>( "local_tree", 1 );


    while( ros::ok() ){


	plan_for( 1.0/RATE );

	ros::spinOnce();
	rate.sleep();
    }

    return 0;
}
