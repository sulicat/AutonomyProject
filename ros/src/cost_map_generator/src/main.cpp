// cost_map_generator

#include "ros/ros.h"
#include "cost_map_generator/ObstacleList.h"
#include "cost_map_generator/CostMap.h"
#include "cost_map_generator/VehicleState.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>


#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#define RATE (10)

cost_map_generator::ObstacleList obstacles_static;
cost_map_generator::ObstacleList obstacles_dynamic;
cost_map_generator::CostMap cost_map_global;
cost_map_generator::CostMap cost_map_local;
cost_map_generator::VehicleState vehicle_state;

float cell_size = 2; // in m
float local_map_radius = 200; // in m


void print_cost_map( cost_map_generator::CostMap cost_map, char* name ){

    for( int r = 0; r < cost_map.cell_num_y; r++ ){
	for( int c = 0; c < cost_map.cell_num_x; c++ ){
	    float _x = c * cost_map.cell_dimension + cost_map.x;
	    float _y = r * cost_map.cell_dimension + cost_map.y;

	    if( !cost_map.cells[ r*cost_map.cell_num_x + c ] ){
		cost_map.cells[ r*cost_map.cell_num_x + c ] = 255;
	    }
	}
    }
    char* image = name;
    //stbi_flip_vertically_on_write(1);
    stbi_write_bmp(image, cost_map.cell_num_x, cost_map.cell_num_y, 1, cost_map.cells.data());
}


bool check_box_collision( float b1[4], float b2[4] ){

    if( b1[0] < b2[0] + b2[2] &&
	b1[0] + b1[2] > b2[0] &&
	b1[1] < b2[1] + b2[3] &&
	b1[1] + b1[3] > b2[1] )
	return true;

    return false;

}

bool check_collision( float x, float y, float w, float h, cost_map_generator::ObstacleList& obst_list ){
    bool out = false;
    float b1[4] = {x, y, w, h};

    for( int i = 0; i < obst_list.obstacles.size(); i++ ){
	float b2[4] = {obst_list.obstacles[i].x,
		       obst_list.obstacles[i].y,
		       obst_list.obstacles[i].w,
		       obst_list.obstacles[i].h};

	out |= check_box_collision( b1, b2 );
    }
    return out;
}


void generate_cost_map_local( cost_map_generator::CostMap& cost_map ){
    float min_x = vehicle_state.pos.x - local_map_radius;
    float min_y = vehicle_state.pos.y - local_map_radius;
    float max_x = vehicle_state.pos.x + local_map_radius;
    float max_y = vehicle_state.pos.y + local_map_radius;

    cost_map.x = min_x;
    cost_map.y = min_y;
    float temp_w = max_x - min_x;
    float temp_h = max_y - min_y;
    cost_map.cell_num_x = temp_w/cell_size;
    cost_map.cell_num_y = temp_h/cell_size;
    cost_map.cell_dimension = cell_size;

    cost_map.cells.clear();
    for( int r = 0; r < cost_map.cell_num_y; r++ ){
	for( int c = 0; c < cost_map.cell_num_x; c++ ){

	    float _x = c * cost_map.cell_dimension + min_x;
	    float _y = r * cost_map.cell_dimension + min_y;
	    float _w = cost_map.cell_dimension;
	    float _h = cost_map.cell_dimension;
	    cost_map.cells.push_back( check_collision(_x, _y, _w, _h, obstacles_static) ||
				      check_collision(_x, _y, _w, _h, obstacles_dynamic) );
	}
    }
}


void generate_cost_map_global( cost_map_generator::CostMap& cost_map, cost_map_generator::ObstacleList& obst_list ){
    // find the bouding box of the cost map
    float min_x = 9999;
    float min_y = 9999;
    float max_x = -9999;
    float max_y = -9999;
    for( int i = 0; i < obst_list.obstacles.size(); i++ ){
	if( obst_list.obstacles[i].x < min_x )
	    min_x = obst_list.obstacles[i].x;

	if( obst_list.obstacles[i].y < min_y )
	    min_y = obst_list.obstacles[i].y;

	if( obst_list.obstacles[i].x + obst_list.obstacles[i].w > max_x )
	    max_x = obst_list.obstacles[i].x + obst_list.obstacles[i].w;

	if( obst_list.obstacles[i].y + obst_list.obstacles[i].h > max_y )
	    max_y = obst_list.obstacles[i].y + obst_list.obstacles[i].h;
    }

    min_x -= 20;
    min_y -= 20;
    max_x += 20;
    max_y += 20;

    cost_map.x = min_x;
    cost_map.y = min_y;
    float temp_w = max_x - min_x;
    float temp_h = max_y - min_y;
    cost_map.cell_num_x = temp_w/cell_size;
    cost_map.cell_num_y = temp_h/cell_size;
    cost_map.cell_dimension = cell_size;

    std::cout << "Cost map generated: \n"
	      << "\t min_x: " << min_x << "\n"
	      << "\t min_y: " << min_y << "\n"
	      << "\t max_x: " << max_x << "\n"
	      << "\t max_y: " << max_y << "\n"
	      << "\t cell number X, Y: " << cost_map.cell_num_x << ", " << cost_map.cell_num_y << "\n"
	      << "\t cell_size: " << cost_map.cell_dimension << "\n\n";


    cost_map.cells.clear();
    for( int r = 0; r < cost_map.cell_num_y; r++ ){
	for( int c = 0; c < cost_map.cell_num_x; c++ ){

	    float _x = c * cost_map.cell_dimension + min_x;
	    float _y = r * cost_map.cell_dimension + min_y;
	    float _w = cost_map.cell_dimension;
	    float _h = cost_map.cell_dimension;
	    cost_map.cells.push_back( check_collision( _x, _y, _w, _h, obst_list ) );
	}
    }

}


void veh_state_callback( cost_map_generator::VehicleState st_in ){
    vehicle_state = st_in;
}


void obstacles_static_callback( cost_map_generator::ObstacleList obstacles ){
    std::cout << "Got static obstacles\n";
    obstacles_static = obstacles;
    generate_cost_map_global( cost_map_global, obstacles );
    print_cost_map(cost_map_global, "resources/global_cost_map.bmp");
}

void obstacles_dynamic_callback( cost_map_generator::ObstacleList obstacles ){
    obstacles_dynamic = obstacles;
}

int main( int argc, char** argv){
    ros::init(argc, argv, "cost_map_generator");
    ros::NodeHandle node_handle;

    ros::Rate rate(RATE);

    ros::Subscriber sub_static = node_handle.subscribe("obstacles_static", 1, obstacles_static_callback);
    ros::Subscriber sub_dynamic = node_handle.subscribe("obstacles_dynamic", 1, obstacles_dynamic_callback);
    ros::Subscriber sub_vs = node_handle.subscribe("vehicle_state", 1, veh_state_callback);
    ros::Publisher pub_cost_map_global = node_handle.advertise<cost_map_generator::CostMap>( "cost_map_global", 1 );
    ros::Publisher pub_cost_map_local = node_handle.advertise<cost_map_generator::CostMap>( "cost_map_local", 1 );

    while( ros::ok() ){

	// static obstacles
	pub_cost_map_global.publish( cost_map_global );

	// dynamic obstacles
	generate_cost_map_local( cost_map_local );
	print_cost_map( cost_map_local, "resources/local_cost_map.bmp" );
	pub_cost_map_local.publish( cost_map_local );

	ros::spinOnce();
	rate.sleep();
    }

    return 0;
}
