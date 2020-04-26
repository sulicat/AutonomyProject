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
#include <std_msgs/Empty.h>
#include <std_msgs/Bool.h>

#include "node.h"
#include "RRT.h"

#define RATE (10)

local_planner::VehicleState vehicle_state;
local_planner::VehicleState end_goal;
local_planner::VehicleState global_goal;
local_planner::VehicleState moving_towards;
local_planner::Trajectory global_plan;
local_planner::CostMap cost_map;
ros::Publisher pub_local_plan;
ros::Publisher pub_local_tree;
ros::Publisher pub_move_command;
ros::Publisher pub_local_goal;

local_planner::VehicleState local_goal;

int goal_index = 0;
bool is_running = false;
float REACHED_RADIUS = 15;
float plan_fetch_radius = 500;

void local_plan_start_callback( std_msgs::Bool e ){
    is_running = e.data;
}

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
    is_running = false;

    if( global_plan.points.size() > 1 ){
	goal_index = 2;

    }else{
	goal_index = -1;
    }
}

float dist_between( float v1[2], float v2[2] ){
    return (v1[0] - v2[0])*(v1[0] - v2[0]) + (v1[1] - v2[1])*(v1[1] - v2[1]);
}

bool plan_for( float time_alotted ){
	auto start_time = std::chrono::system_clock::now();
	double total_time = 0;

	global_goal.pos.x = global_plan.points[ goal_index ].state.pos.x;
	global_goal.pos.y = global_plan.points[ goal_index ].state.pos.y;

	if (goal_index == global_plan.points.size()){
	    global_goal.vehicle_angle = global_plan.points[ goal_index ].state.vehicle_angle;
	} else {
	    global_goal.vehicle_angle = global_plan.points[ goal_index + 1].state.vehicle_angle;
	}

	pub_local_goal.publish( global_goal );

	// create a tree at ther start
	RRT rrt( cost_map, vehicle_state, global_goal );
	rrt.reset_tree();
	int step_count = 0;

	while( total_time < time_alotted ){
	    // keep stepping the tree
	    rrt.step( step_count % 2 == 0 );

	    step_count += 1;
	    std::chrono::duration<double> time_diff = (std::chrono::system_clock::now() - start_time);
	    total_time += time_diff.count();
	    start_time = std::chrono::system_clock::now();
	}

	Node* out_tree = rrt.get_tree();
	pub_local_tree.publish( out_tree->create_render_tree() );
	Node* best_node = rrt.find_cheapest_node();

	local_planner::Trajectory out;
	out = out_tree->dfs_traj( best_node );
	//out = out_tree->dfs_traj( rrt.goal );
	pub_local_plan.publish(out);

	local_goal.pos.x = best_node->x;
	local_goal.pos.y = best_node->y;
	local_goal.vehicle_angle = best_node->angle;

	std::cout << "[Local Planner] ran for: " << total_time << "\n";
	std::cout << "[Local Planner]   steps: " << step_count << "\n";
	std::cout << "[Local Planner]   path length: " << out.points.size() << "\n";
	std::cout << "[Local Planner]   tracking wpt: " << goal_index << "\n";
}

/* // increment based on reached status
void check_pos(){
    float v1[2] = {vehicle_state.pos.x, vehicle_state.pos.y};
    float v2[2] = {local_goal.pos.x, local_goal.pos.y};


    if( dist_between( v2, v1 ) < REACHED_RADIUS ){
	if( goal_index < global_plan.points.size() - 2 ){
	    goal_index += 1;
	}
    }

    std::cout << "dist between: " << dist_between( v2, v1 ) << "\n";
    std::cout << "goal index: " << goal_index << "\n";

}
*/

// increment based on distance from vehicle
void check_pos(){
    float v1[2] = {vehicle_state.pos.x, vehicle_state.pos.y};
    float v2[2];

    int max_index = goal_index;
    for( int i = goal_index; i < global_plan.points.size(); i++ ){
	v2[0] = global_plan.points[i].state.pos.x;
	v2[1] = global_plan.points[i].state.pos.y;

	if( dist_between( v2, v1 ) < plan_fetch_radius ){
	    max_index = i;
	}
    }

    goal_index = max_index;

    std::cout << "dist between: " << dist_between( v2, v1 ) << "\n";
    std::cout << "goal index: " << goal_index << "\n";

}

void send_move_command(){
    local_planner::Waypoint cmd;
    cmd.state.pos.x = local_goal.pos.x;
    cmd.state.pos.y = local_goal.pos.y;
    cmd.state.vehicle_angle = local_goal.vehicle_angle;
    cmd.state.vehicle_width = 1.7;
    cmd.state.vehicle_length = 4.0;

    pub_move_command.publish( cmd );
}


int main( int argc, char** argv){

    ros::init(argc, argv, "local_planner");
    ros::NodeHandle node_handle;
    ros::Rate rate(RATE);

    ros::Subscriber sub_veh_state = node_handle.subscribe("vehicle_state", 1, vehicle_state_callback);
    ros::Subscriber sub_end_goal = node_handle.subscribe("end_goal", 1, end_goal_callback);
    ros::Subscriber sub_cost_map = node_handle.subscribe("cost_map_local", 1, cost_map_callback);
    ros::Subscriber sub_global_plan = node_handle.subscribe("global_plan", 1, global_plan_callback);
    ros::Subscriber sub_local_start = node_handle.subscribe("local_start_command", 1, local_plan_start_callback);
    pub_local_plan = node_handle.advertise<local_planner::Trajectory>( "local_plan", 1 );
    pub_local_tree = node_handle.advertise<local_planner::RenderTree>( "local_tree", 1 );
    pub_move_command = node_handle.advertise<local_planner::Waypoint>( "tracked_goal", 1 );
    pub_local_goal = node_handle.advertise<local_planner::VehicleState>( "local_goal", 1 );


    while( ros::ok() ){

	if( is_running && goal_index >= 0 && goal_index < global_plan.points.size()){
	    plan_for( (1.0/RATE) * 0.5 );
	    send_move_command();
	    check_pos();
	}

	ros::spinOnce();
	rate.sleep();
    }

    return 0;
}
