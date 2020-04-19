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
#include <iostream>


#define WINDOW_WIDTH 1080 //400 //1080 changed for testing purposes
#define WINDOW_HEIGHT 720 //400 //720 changed for testing purposes


class World{
public:
    BaseVehicle* vehicle;
    world_vis::Waypoint* wpt_tracking;
    BaseVehicle* wpt_tracking_vehicle;
    bool vehicle_set;
    float window_width_m;


    World();

    void set_vehicle( BaseVehicle* new_vehicle );

    void set_tracked_wpt( world_vis::Waypoint* wpt );

    void render_vehicle( sf::RenderWindow& window,
			 BaseVehicle* input_vehicle,
			 int alpha = 255 );

    void render_obstacles( sf::RenderWindow& window );

    void render_current_tracked_point( sf::RenderWindow& window );

    void render( sf::RenderWindow& window );

private:
    // vehicle shapes
    sf::RectangleShape render_v_chassis;
    sf::RectangleShape render_v_wheel_bl;
    sf::RectangleShape render_v_wheel_br;
    sf::RectangleShape render_v_wheel_fl;
    sf::RectangleShape render_v_wheel_fr;
};


#endif
