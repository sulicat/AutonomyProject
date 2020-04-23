#ifndef _WORLD_H_
#define _WORLD_H_

#include <SFML/Graphics.hpp>
#include "ros/ros.h"
#include "V2.hpp"
#include "BaseVehicle.h"
#include "ros_to_system.h"
#include "world_vis/VehicleState.h"
#include "world_vis/VehicleMoveCommand.h"
#include "world_vis/Waypoint.h"
#include "world_vis/Trajectory.h"
#include "world_vis/Obstacle.h"
#include "world_vis/ObstacleList.h"
#include "world_vis/Line.h"
#include "world_vis/RenderTree.h"
#include <std_msgs/Empty.h>
#include <iostream>


#define STATIC 0
#define DYNAMIC 1

class World{
public:
    BaseVehicle* vehicle;
    world_vis::Waypoint* wpt_tracking;
    world_vis::Trajectory* global_plan;
    world_vis::RenderTree* global_tree;
    BaseVehicle* wpt_tracking_vehicle;
    bool vehicle_set;
    float window_width_m;
    int pan_x = 0;
    int pan_y = 0;
    int WINDOW_WIDTH;
    int WINDOW_HEIGHT;

    std::vector< world_vis::Obstacle > obstacles_static;
    std::vector< world_vis::Obstacle > obstacles_dynamic;

    World( );
    World( ros::NodeHandle* nh );

    void set_vehicle( BaseVehicle* new_vehicle );

    void set_global_plan( world_vis::Trajectory* plan_in );

    void set_global_tree( world_vis::RenderTree* tree_in );

    void set_tracked_wpt( world_vis::Waypoint* wpt );

    void add_obstacle( int type, float x, float y, float w, float h );

    void load_obstacles( std::string path );

    void publish_obstacles();

    void publish_global_plan_start();

    void teleport( int x, int y, float angle );

    void set_track( int x, int y, float angle );

    void clear_track();

    void set_end_goal( int x, int y );

    void update_end_goal( int x, int y );

    void render_global_plan( sf::RenderWindow& window );

    void render_global_tree( sf::RenderWindow& window );

    void render_vehicle( sf::RenderWindow& window,
			 BaseVehicle* input_vehicle,
			 int alpha = 255 );

    void render_obstacles( sf::RenderWindow& window );

    void render_current_tracked_point( sf::RenderWindow& window );

    void render_meter_line( sf::RenderWindow& window );

    void render_end_goal( sf::RenderWindow& window );

    void render( sf::RenderWindow& window );

private:
    // vehicle shapes
    sf::RectangleShape render_v_chassis;
    sf::RectangleShape render_v_wheel_bl;
    sf::RectangleShape render_v_wheel_br;
    sf::RectangleShape render_v_wheel_fl;
    sf::RectangleShape render_v_wheel_fr;
    sf::RectangleShape render_rect_meter_line;
    sf::CircleShape render_circle_end_goal;
    sf::CircleShape render_circle_current_pos;


    ros::Publisher obstacles_static_pub;
    ros::Publisher obstacles_dynamic_pub;
    ros::Publisher teleport_pub;
    ros::Publisher end_state_pub;
    ros::Publisher global_plan_start_pub;
    ros::Publisher tracked_pub;

    float end_goal_x;
    float end_goal_y;
};


#endif
