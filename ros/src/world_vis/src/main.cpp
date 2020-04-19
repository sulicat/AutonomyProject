#include "imgui.h"
#include "imgui-SFML.h"


#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "ros/ros.h"
#include "V2.hpp"
#include "BaseVehicle.h"
#include "ros_to_system.h"
#include "world_vis/VehicleState.h"
#include "world_vis/VehicleMoveCommand.h"
#include "world_vis/Waypoint.h"
#include "world_vis/Trajectory.h"
#include <iostream>

#include "world.h"
#include "gui.h"

BaseVehicle vehicle;
world_vis::Waypoint wpt_tracking_goal;
BaseVehicle wpt_tracking_goal_state;

void veh_state_callback( world_vis::VehicleState veh_state ){
    simple_car::state_to_model( vehicle, veh_state );
    GUI::Instance()->updateVehicleState( veh_state );
}

void tracked_goal_callback( world_vis::Waypoint wpnt ){
    std::cout << "Got tracked goal\n";
    wpt_tracking_goal = wpnt;
}


int main( int argc, char** argv ){
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "World Vis");
    window.setFramerateLimit(60);

    ImGui::SFML::Init(window);

    World world;
    world.set_vehicle( &vehicle );
    world.set_tracked_wpt( &wpt_tracking_goal );

    ros::init(argc, argv, "world_vis");
    ros::NodeHandle node_handle;

    ros::Publisher move_command_pub = node_handle.advertise<world_vis::VehicleMoveCommand>( "vehicle_move_command", 1 );
    ros::Subscriber sub = node_handle.subscribe("vehicle_state", 1, veh_state_callback);
    ros::Subscriber sub_tracked = node_handle.subscribe("tracked_goal", 1, tracked_goal_callback);



    ros::Rate rate(60);
    sf::Clock deltaClock;

    while (window.isOpen() && ros::ok()){
        sf::Event event;
        while (window.pollEvent(event)){
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();

	    bool publish_move_command = false;
	    world_vis::VehicleMoveCommand move_command;
	    if( sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ){
		publish_move_command = true;
		move_command.linear_vel = vehicle.linear_vel;
		move_command.steering_angle_vel = -30;
	    }
	    if( sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ){
		publish_move_command = true;
		move_command.linear_vel = vehicle.linear_vel;
		move_command.steering_angle_vel = 30;
	    }
	    if( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ){
		publish_move_command = true;
		move_command.linear_vel = 10;
		move_command.steering_angle_vel = vehicle.steering_angle_vel;
	    }
	    if( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ){
		publish_move_command = true;
		move_command.linear_vel = -10;
		move_command.steering_angle_vel = vehicle.steering_angle_vel;
	    }
	    if( sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ){
		publish_move_command = true;
		move_command.linear_vel = 0;
		move_command.steering_angle_vel = 0;
	    }

	    if( publish_move_command ){
		move_command_pub.publish( move_command );
	    }
        }


	ImGui::SFML::Update(window, deltaClock.restart());

	GUI::Instance()->render();

        window.clear( sf::Color(255,255,255) );
	world.render( window );
        ImGui::SFML::Render(window);
        window.display();

	ros::spinOnce();
	rate.sleep();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
