#ifndef _RRT_H_
#define _RRT_H_

#include "global_planner/VehicleState.h"
#include "global_planner/CostMap.h"
#include "global_planner/Trajectory.h"
#include "global_planner/Line.h"
#include "global_planner/RenderTree.h"
#include "point.hpp"
#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RAD_TO_DEG (180.0 / 3.1415)
#define DEG_TO_RAD (3.1415 / 180.0)
#define MAX_KIN_ANGLE (10)

class RRT{
public:

    const global_planner::CostMap& cost_map;
    const global_planner::VehicleState& start;
    const global_planner::VehicleState& end;
    Node* root;
    Node* goal;
    float cost_map_w;
    float cost_map_h;
    float radius_of_influence;
    bool reached = false;
    std::vector<Node*> all_tree_nodes;

    RRT( const global_planner::CostMap& _cost_map_in,
	 const global_planner::VehicleState& st,
	 const global_planner::VehicleState& ed ) : cost_map( _cost_map_in ),
						    start( st ),
						    end( ed ){

	srand (time(NULL));
	cost_map_w = cost_map.cell_num_x * cost_map.cell_dimension;
	cost_map_h = cost_map.cell_num_y * cost_map.cell_dimension;
	radius_of_influence = 5*5;

    }

    bool is_free( float x, float y ){
	// outside bound, assume no obstacle since cost map size depends on obstacles
	if( x < cost_map.x ||
	    y < cost_map.y ||
	    x > cost_map.x + cost_map_w ||
	    y > cost_map.y + cost_map_h ){
	    return true;
	}

	x -= cost_map.x; // zero out
	y -= cost_map.y; // zero out

	int c = x / cost_map_w * cost_map.cell_num_x;
	int r = y / cost_map_h * cost_map.cell_num_y;
	if( cost_map.cells[ r*cost_map.cell_num_x + c ] != 0 ){
	    return false;
	}

	return true;
    }

    float dist_between( Node* n1, Node* n2 ){
	return (n1->x - n2->x)*(n1->x - n2->x) + (n1->y - n2->y)*(n1->y - n2->y);
    }

    Node* closest_node( Node* _n ){
	Node* closest = root;
	float min_dist = 99999;

	for( int i = 0; i < all_tree_nodes.size(); i++ ){
	    float test_dist = dist_between( all_tree_nodes[i], _n);
	    if( test_dist < min_dist ){
		min_dist = test_dist;
		closest = all_tree_nodes[i];
	    }
	}

	return closest;
    }

    Node* project_towards( Node* from, Node* to, float dt = 3 ){
	float edge_len = sqrt( dist_between(from, to) );
	float normal_x = (to->x - from->x) / edge_len;
	float normal_y = (to->y - from->y) / edge_len;

	Node* out = new Node( from->x + normal_x * dt,
			      from->y + normal_y * dt );
	return out;
    }

    Node* project_towards_using_kin( bool& add, Node* from, Node* to, float dt = 3 ){
	//asd
	float x_dist = to->x - from->x;
	float y_dist = to->y - from->y;
	float path_angle = atan2( y_dist, x_dist ) * RAD_TO_DEG;
	float angle_diff = from->angle - path_angle;

	Node* out;

	float edge_len = sqrt( dist_between(from, to) );
	float normal_x = (to->x - from->x) / edge_len;
	float normal_y = (to->y - from->y) / edge_len;

	if( abs(angle_diff) <= MAX_KIN_ANGLE ){

	    out = new Node( from->x + normal_x * dt,
			    from->y + normal_y * dt,
			    path_angle );
	    add = true;

	}else{
	    // implement me at some point pls
/*	    float new_angle = (from->angle + MAX_KIN_ANGLE) * signbit(angle_diff);
	    float x_max = from->x + (dt * cos( DEG_TO_RAD * (new_angle) ));
	    float y_max = from->y + (dt * sin( DEG_TO_RAD * (new_angle) ));
	    std::cout << "    max: " << x_max << "  " << y_max << "\n";
	    out = new Node( from->x,
			    from->y,
			    path_angle );
*/
	    add = false;
	}


	return out;
    }


    bool step( bool at_goal = false ){
	float sampled_pnt_x;
	float sampled_pnt_y;
	if( !at_goal ){
	    sampled_pnt_x = (rand() / (float)RAND_MAX) * (cost_map_w*2 + cost_map.x - cost_map_w);
	    sampled_pnt_y = (rand() / (float)RAND_MAX) * (cost_map_h*2 + cost_map.y - cost_map_h);

	}else{
	    sampled_pnt_x = goal->x;
	    sampled_pnt_y = goal->y;
	}

	Node temp( sampled_pnt_x, sampled_pnt_y );
	Node* closest = closest_node( &temp );
	Node sampled_node = Node(sampled_pnt_x, sampled_pnt_y);
	// get the node projected towards the sampled node
	//Node* to_add_node = project_towards( closest, &sampled_node );
	bool should_add;
	Node* to_add_node = project_towards_using_kin( should_add, closest, &sampled_node );

	if( should_add && is_free( to_add_node->x, to_add_node->y ) ){

	    closest->add_child( to_add_node );
	    all_tree_nodes.push_back(to_add_node);

	    if( dist_between( to_add_node, goal ) < 10 ){
		to_add_node->add_child(goal);
		reached = true;
		std::cout << "RRT REACHED GOAL!!!\n\n";
	    }

	    return true;

	}else{
	    return false;
	}
    }

    void create_tree( int itter = 15000 ){
	std::cout << "--------------------\n\n";
	reached = false;
	all_tree_nodes.clear();

	cost_map_w = cost_map.cell_num_x * cost_map.cell_dimension;
        cost_map_h = cost_map.cell_num_y * cost_map.cell_dimension;

	// add the root to all the nodes
	float _start_x = start.pos.x + start.vehicle_length + 1;
	float _start_y = start.pos.y + start.vehicle_width/2;
	root = new Node( _start_x, _start_y );
	all_tree_nodes.push_back(root);

	// goal not added yet, since we don't want to consider it
	goal = new Node( end.pos.x, end.pos.y );

	int i = 0;
	int i_max = itter * 100;
	while( i < itter && i_max > 0 && !reached ){
	    bool added = step( i_max % 20 == 0 );

	    i_max--;
	    if( added )
		i++;
	}

    }

    Node* get_tree(){
	return root;
    }

};

#endif
