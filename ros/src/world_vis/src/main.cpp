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
#include "world_vis/Line.h"
#include "world_vis/RenderTree.h"
#include <iostream>

#include "world.h"
#include "gui.h"

#define ZOOM_SENSITIVITY 0.01

World world;
BaseVehicle vehicle;
world_vis::Waypoint wpt_tracking_goal;
world_vis::Trajectory global_plan;
world_vis::RenderTree global_tree;

BaseVehicle wpt_tracking_goal_state;
int mouse_drag_x_press = 0;
int mouse_drag_y_press = 0;
bool drag_on = false;
std::string status;
int tele_angle;
int tracked_angle;

void veh_state_callback( world_vis::VehicleState veh_state ){
    simple_car::state_to_model( vehicle, veh_state );
    GUI::Instance()->updateVehicleState( veh_state );
}

void tracked_goal_callback( world_vis::Waypoint wpnt ){
    std::cout << "Got tracked goal\n";
    wpt_tracking_goal = wpnt;
}

void end_goal_callback( world_vis::VehicleState _end ){
    std::cout << "Got end goal\n";
    std::cout << "   " << _end.pos.x << ", " << _end.pos.y << "\n";
    world.update_end_goal( _end.pos.x, _end.pos.y );
}

void global_plan_callback( world_vis::Trajectory plan_in ){
    global_plan = plan_in;
}

void global_tree_callback( world_vis::RenderTree tree_in ){
    std::cout << "Got a GLobal Planner Tree\n";
    global_tree = tree_in;
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
    status = "none";

    sf::RenderWindow window(sf::VideoMode(world.WINDOW_WIDTH, world.WINDOW_HEIGHT), "World Vis");
    window.setFramerateLimit(60);

    GUI::Instance()->set_world( &world );
    GUI::Instance()->setStatus( &status );
    GUI::Instance()->setTeleAngle( &tele_angle );
    GUI::Instance()->setTrackedAngle( &tracked_angle );

    ImGui::SFML::Init(window);

    ros::init(argc, argv, "world_vis");
    ros::NodeHandle node_handle;

    ros::Publisher move_command_pub = node_handle.advertise<world_vis::VehicleMoveCommand>( "vehicle_move_command", 1 );
    ros::Subscriber sub = node_handle.subscribe("vehicle_state", 1, veh_state_callback);
    ros::Subscriber sub_tracked = node_handle.subscribe("tracked_goal", 1, tracked_goal_callback);
    ros::Subscriber sub_end = node_handle.subscribe("end_goal", 1, end_goal_callback);
    ros::Subscriber sub_global_plan = node_handle.subscribe("global_plan", 1, global_plan_callback);
    ros::Subscriber sub_global_tree = node_handle.subscribe("global_tree", 1, global_tree_callback);

    world = World(&node_handle);
    world.set_vehicle( &vehicle );
    world.set_global_plan( &global_plan );
    world.set_global_tree( &global_tree );
    world.set_tracked_wpt( &wpt_tracking_goal );

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

	    if (event.type == sf::Event::Resized) {
		world.window_width_m = world.window_width_m * ((float)event.size.width / (float)world.WINDOW_WIDTH);
		world.WINDOW_WIDTH = event.size.width;
		world.WINDOW_HEIGHT = event.size.height;
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

		if( event.mouseButton.button == sf::Mouse::Left){

		    if( status == "tele" ){
			std::cout << "tele to: "
				  << event.mouseButton.x << " " << event.mouseButton.y
				  << " " << tele_angle << "\n";
			world.teleport( event.mouseButton.x,
					event.mouseButton.y,
					tele_angle);

		    }else if( status == "end_goal" ){
			world.set_end_goal( event.mouseButton.x, event.mouseButton.y );

		    }else if( status == "tracked"){
			world.set_track( event.mouseButton.x,
					 event.mouseButton.y,
					 tracked_angle );

		    }

		    status = "none";
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
