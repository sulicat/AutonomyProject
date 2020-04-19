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

#define ZOOM_SENSITIVITY 0.01

World world;
BaseVehicle vehicle;
world_vis::Waypoint wpt_tracking_goal;
BaseVehicle wpt_tracking_goal_state;
int mouse_drag_x_press = 0;
int mouse_drag_y_press = 0;
bool drag_on = false;

void veh_state_callback( world_vis::VehicleState veh_state ){
    simple_car::state_to_model( vehicle, veh_state );
    GUI::Instance()->updateVehicleState( veh_state );
}

void tracked_goal_callback( world_vis::Waypoint wpnt ){
    std::cout << "Got tracked goal\n";
    wpt_tracking_goal = wpnt;
}


void set_drag( bool state, int x, int y ){
    mouse_drag_x_press = x;
    mouse_drag_y_press = y;
    drag_on = state;
}

void mouse_move( int x, int y ){
    if( drag_on ){
	world.pan_x += x - mouse_drag_x_press;
	world.pan_y += y - mouse_drag_y_press;
	mouse_drag_y_press = y;
	mouse_drag_x_press = x;
    }
}

int main( int argc, char** argv ){
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "World Vis");
    window.setFramerateLimit(60);

    ImGui::SFML::Init(window);

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

	    // mouse scroll
	    if(event.type == sf::Event::MouseWheelMoved){
		world.window_width_m = world.window_width_m * (1 + ((float)event.mouseWheel.delta * ZOOM_SENSITIVITY));
            }

	    // mouse pressed
	    if( event.type == sf::Event::MouseButtonPressed ){
		if( event.mouseButton.button == sf::Mouse::Middle){
		    set_drag(true, event.mouseButton.x, event.mouseButton.y );
		}
	    }

	    if( event.type == sf::Event::MouseButtonReleased ){
		if( event.mouseButton.button == sf::Mouse::Middle){
		    set_drag(false, event.mouseButton.x, event.mouseButton.y );
		}
	    }

	    // mouse moved
	    if( event.type == sf::Event::MouseMoved ){
		mouse_move( event.mouseMove.x, event.mouseMove.y );
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
