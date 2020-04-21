#ifndef _PRM_H_
#define _PRM_H_

#include "global_planner/VehicleState.h"
#include "global_planner/CostMap.h"
#include "global_planner/Trajectory.h"
#include "global_planner/Line.h"
#include "global_planner/RenderTree.h"
#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

class PRM{
public:

    const global_planner::CostMap& cost_map;
    const global_planner::VehicleState& start;
    const global_planner::VehicleState& end;
    Node* root;
    Node* goal;
    float cost_map_w;
    float cost_map_h;
    float radius_of_influence;
    std::vector<Node*> sampled_nodes;

    PRM( const global_planner::CostMap& _cost_map_in,
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

    void sample( int amount = 5000 ){
	sampled_nodes.clear();
	cost_map_w = cost_map.cell_num_x * cost_map.cell_dimension;
        cost_map_h = cost_map.cell_num_y * cost_map.cell_dimension;
	std::cout << "Sampling\n";

	root = new Node( start.pos.x, start.pos.y );
	goal = new Node( end.pos.x, end.pos.y );
	sampled_nodes.push_back( root );
	sampled_nodes.push_back( goal );

	int count = 0;
	while( sampled_nodes.size() < amount || count > amount*5){
	    float random_x = (rand() / (float)RAND_MAX) * cost_map_w + cost_map.x;
	    float random_y = (rand() / (float)RAND_MAX) * cost_map_h + cost_map.y;

	    if( is_free( random_x, random_y) ){
		sampled_nodes.push_back(new Node(random_x, random_y));
		count += 1;
	    }
	}

    }

    void create_tree(){
	for( int i = 0; i < sampled_nodes.size(); i++ ){
	    for( int k = i+1; k < sampled_nodes.size(); k++ ){
		if( dist_between(sampled_nodes[i], sampled_nodes[k]) < radius_of_influence ){
		    sampled_nodes[i]->add_child( sampled_nodes[k] );
		    sampled_nodes[k]->add_child( sampled_nodes[i] );
		}
	    }
	}
    }

    Node* get_tree(){
	return root;
    }

};

#endif
