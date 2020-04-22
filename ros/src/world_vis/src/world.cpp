#include <string>
#include <fstream>
#include <streambuf>

#include "world.h"
#include "json.hpp"

World::World(){
    WINDOW_WIDTH = 1080;
    WINDOW_HEIGHT = 720;
    window_width_m = 100;
}

World::World( ros::NodeHandle* node_handle ){
    vehicle_set = false;
    window_width_m = 100;// adjust to 100 for 1080x720 screen
    wpt_tracking_vehicle = new BaseVehicle();
    wpt_tracking = NULL;

    obstacles_static_pub = node_handle->advertise<world_vis::ObstacleList>( "obstacles_static", 1 );
    obstacles_dynamic_pub = node_handle->advertise<world_vis::ObstacleList>( "obstacles_dynamic", 1 );
    teleport_pub = node_handle->advertise<world_vis::VehicleState>( "vehicle_teleport", 1 );
    end_state_pub = node_handle->advertise<world_vis::VehicleState>( "end_goal", 1 );
    global_plan_start_pub = node_handle->advertise<std_msgs::Empty>( "global_start_command", 1 );
    tracked_pub = node_handle->advertise<world_vis::Waypoint>( "tracked_goal", 1 );

    WINDOW_WIDTH = 1080;
    WINDOW_HEIGHT = 720;

    render_circle_end_goal = sf::CircleShape(5);
    render_circle_end_goal.setFillColor( sf::Color(0, 180, 180) );

}

void World::set_vehicle( BaseVehicle* new_vehicle ){
    vehicle = new_vehicle;
    vehicle_set = true;
}

void World::set_global_tree( world_vis::RenderTree* tree_in ){
    global_tree = tree_in;
}


void World::set_tracked_wpt( world_vis::Waypoint* wpt ){
    wpt_tracking = wpt;
    simple_car::state_to_model( *wpt_tracking_vehicle, wpt_tracking->state );
}

void World::set_global_plan( world_vis::Trajectory* plan_in ){
    global_plan = plan_in;
}

void World::add_obstacle( int type, float x, float y, float w, float h ){
    std::string type_str = type == STATIC ? "static ... " : "dynamic ... ";
    std::cout << "\t" << "Adding obstacle: " << type_str << x << ", " << y << ", " << w << ", " << h << "\n";

    world_vis::Obstacle obst;
    obst.x = x;
    obst.y = y;
    obst.w = w;
    obst.h = h;

    if( type == STATIC ){
	obstacles_static.push_back(obst);
    }else{
	obstacles_dynamic.push_back(obst);
    }
}

void World::publish_global_plan_start(){
    global_plan_start_pub.publish( std_msgs::Empty() );
}

void World::publish_obstacles(){
    world_vis::ObstacleList obstacles_to_pub_static;
    for( int i = 0; i < obstacles_static.size(); i++ ){
	obstacles_to_pub_static.obstacles.push_back(obstacles_static[i]);
    }
    world_vis::ObstacleList obstacles_to_pub_dynamic;
    for( int i = 0; i < obstacles_dynamic.size(); i++ ){
	obstacles_to_pub_dynamic.obstacles.push_back(obstacles_dynamic[i]);
    }

    obstacles_static_pub.publish( obstacles_to_pub_static );
    obstacles_dynamic_pub.publish( obstacles_to_pub_dynamic );
}

void World::load_obstacles( std::string path ){

    std::cout << "World: loading obstacles in: " << path << "\n";
    std::ifstream t(path);
    std::string str((std::istreambuf_iterator<char>(t)),
		    std::istreambuf_iterator<char>());

    std::cout << "\n" << str << "\n\n";

    obstacles_static.clear();
    obstacles_dynamic.clear();

    auto json_parsed = nlohmann::json::parse(str);
    for( int i = 0; i < json_parsed["static"].size(); i++ ){
	add_obstacle( STATIC,
		      json_parsed["static"][i]["x"],
		      json_parsed["static"][i]["y"],
		      json_parsed["static"][i]["w"],
		      json_parsed["static"][i]["h"] );
    }

    for( int i = 0; i < json_parsed["dynamic"].size(); i++ ){
	add_obstacle( DYNAMIC,
		      json_parsed["dynamic"][i]["x"],
		      json_parsed["dynamic"][i]["y"],
		      json_parsed["dynamic"][i]["w"],
		      json_parsed["dynamic"][i]["h"] );
    }

    publish_obstacles();
}

// Too many divisions bro... clean this up when sober :/
void World::render_global_tree( sf::RenderWindow& window ){

    float ZOOM_FACTOR = (float)WINDOW_WIDTH / window_width_m;
    int offset_x = pan_x;
    int offset_y = pan_y;

    sf::VertexArray lines(sf::Lines, global_tree->edges.size()*2);

    int counter = 0;
    for( int i = 0; i < global_tree->edges.size()*2; i+=2 ){

	lines[i].position = sf::Vector2f( global_tree->edges[counter].x1 * ZOOM_FACTOR + offset_x,
					  global_tree->edges[counter].y1 * ZOOM_FACTOR + offset_y );

	lines[i+1].position = sf::Vector2f( global_tree->edges[counter].x2 * ZOOM_FACTOR + offset_x,
					    global_tree->edges[counter].y2 * ZOOM_FACTOR + offset_y );

	lines[i].color = sf::Color(0, 255,255);
	lines[i+1].color = sf::Color(0, 255,255);

	counter++;
    }
    window.draw(lines);

}

void World::render_global_plan( sf::RenderWindow& window ){

    float ZOOM_FACTOR = (float)WINDOW_WIDTH / window_width_m;
    int offset_x = pan_x;
    int offset_y = pan_y;

    sf::VertexArray lines(sf::LinesStrip, global_plan->points.size());

    for( int i = 0; i < global_plan->points.size(); i++ ){
	lines[i].position = sf::Vector2f( global_plan->points[i].state.pos.x * ZOOM_FACTOR + offset_x,
					  global_plan->points[i].state.pos.y * ZOOM_FACTOR + offset_y );

	lines[i].color = sf::Color::Blue;
    }
    window.draw(lines);
}

void World::render_meter_line( sf::RenderWindow& window ){
    float ZOOM_FACTOR = (float)WINDOW_WIDTH / window_width_m;

    render_rect_meter_line = sf::RectangleShape( sf::Vector2f(1 * ZOOM_FACTOR,
							      1 * ZOOM_FACTOR) );

    render_rect_meter_line.move( 10, 10 );
    render_rect_meter_line.setFillColor( sf::Color(0, 0, 0) );
    render_v_chassis.setOutlineColor( sf::Color(0, 0, 0) );

    window.draw( render_rect_meter_line );

}

void World::teleport( int x, int y, float angle ){
    float ZOOM_FACTOR = (float)WINDOW_WIDTH / window_width_m;

    float screen_to_world_x = (x - pan_x) / ZOOM_FACTOR;
    float screen_to_world_y = (y - pan_y) / ZOOM_FACTOR;

    world_vis::VehicleState tele_state;
    tele_state.pos.x = screen_to_world_x;
    tele_state.pos.y = screen_to_world_y;
    tele_state.linear_vel = 0.0;
    tele_state.steering_angle_vel = 0.0;
    tele_state.steering_angle = 0.0;
    tele_state.vehicle_angle = angle;

    teleport_pub.publish( tele_state );
}

void World::set_track( int x, int y, float angle ){
    float ZOOM_FACTOR = (float)WINDOW_WIDTH / window_width_m;

    float screen_to_world_x = (x - pan_x) / ZOOM_FACTOR;
    float screen_to_world_y = (y - pan_y) / ZOOM_FACTOR;

    world_vis::Waypoint wpt;
    wpt.state.pos.x = screen_to_world_x;
    wpt.state.pos.y = screen_to_world_y;
    wpt.state.vehicle_angle = angle;
    wpt.state.vehicle_width = 1.7;
    wpt.state.vehicle_length = 4.0;
    tracked_pub.publish( wpt );
}

void World::clear_track(){
    world_vis::Waypoint wpt;
    world_vis::VehicleState state;
    wpt.state.pos.x = 0.0;
    wpt.state.pos.y = 0.0;
    wpt.state.vehicle_angle = 0.0;
    wpt.state.vehicle_width = 0.0;
    wpt.state.vehicle_length = 0.0;
    tracked_pub.publish( wpt );
}

void World::set_end_goal( int x, int y ){
    float ZOOM_FACTOR = (float)WINDOW_WIDTH / window_width_m;
    float screen_to_world_x = (x - pan_x) / ZOOM_FACTOR;
    float screen_to_world_y = (y - pan_y) / ZOOM_FACTOR;

    world_vis::VehicleState end_state;
    end_state.pos.x = screen_to_world_x;
    end_state.pos.y = screen_to_world_y;
    end_state.vehicle_angle = 0;

    end_state_pub.publish( end_state );
}

void World::update_end_goal( int x, int y ){
    end_goal_x = x;
    end_goal_y = y;
}

void World::render_end_goal( sf::RenderWindow& window ){
    float ZOOM_FACTOR = (float)WINDOW_WIDTH / window_width_m;
    int offset_x = pan_x;
    int offset_y = pan_y;

    render_circle_end_goal.setPosition( end_goal_x * ZOOM_FACTOR + offset_x,
					end_goal_y * ZOOM_FACTOR + offset_y );

    window.draw( render_circle_end_goal );
}

void World::render_vehicle( sf::RenderWindow& window,
			    BaseVehicle* input_vehicle,
			    int alpha ){

    float ZOOM_FACTOR = (float)WINDOW_WIDTH / window_width_m;
    int offset_x = pan_x;
    int offset_y = pan_y;

    // chassis
    render_v_chassis = sf::RectangleShape( sf::Vector2f(input_vehicle->length * ZOOM_FACTOR,
							input_vehicle->width * ZOOM_FACTOR) );

    render_v_chassis.move( input_vehicle->pos.x * ZOOM_FACTOR + offset_x,
			   input_vehicle->pos.y * ZOOM_FACTOR + offset_y );

    render_v_chassis.setFillColor( sf::Color(0, 0, 0, 0) );
    render_v_chassis.setOutlineColor( sf::Color(0, 0, 0, alpha) );
    render_v_chassis.setOutlineThickness(1.0);


    sf::Vector2f veh_center = sf::Vector2f(render_v_chassis.getPosition().x + render_v_chassis.getSize().x/2,
					   render_v_chassis.getPosition().y + render_v_chassis.getSize().y/2);

    sf::Transform veh_rotation;
    sf::Transform steering_angle_rotation_l;
    sf::Transform steering_angle_rotation_r;

    veh_rotation.rotate(input_vehicle->vehicle_angle, veh_center);
    steering_angle_rotation_l.rotate(input_vehicle->vehicle_angle, veh_center);
    steering_angle_rotation_r.rotate(input_vehicle->vehicle_angle, veh_center);

    //veh_rotation.rotate(0, veh_center);

    // wheels
    float wheel_width = input_vehicle->width * 0.2;
    float wheel_length = input_vehicle->length * 0.3;

    //  set all the wheel widths
    render_v_wheel_bl = sf::RectangleShape( sf::Vector2f(wheel_length * ZOOM_FACTOR,
							 wheel_width * ZOOM_FACTOR) );
    render_v_wheel_br = sf::RectangleShape( sf::Vector2f(wheel_length * ZOOM_FACTOR,
							 wheel_width * ZOOM_FACTOR) );
    render_v_wheel_fl = sf::RectangleShape( sf::Vector2f(wheel_length * ZOOM_FACTOR,
							 wheel_width * ZOOM_FACTOR) );
    render_v_wheel_fr = sf::RectangleShape( sf::Vector2f(wheel_length * ZOOM_FACTOR,
							 wheel_width * ZOOM_FACTOR) );

    // set all the wheel colors
    render_v_wheel_bl.setFillColor( sf::Color(0, 0, 0, alpha) );
    render_v_wheel_br.setFillColor( sf::Color(0, 0, 0, alpha) );
    render_v_wheel_fl.setFillColor( sf::Color(0, 0, 255, alpha) );
    render_v_wheel_fr.setFillColor( sf::Color(0, 0, 255, alpha) );

    render_v_wheel_bl.move( (input_vehicle->pos.x) * ZOOM_FACTOR + offset_x,
			    (input_vehicle->pos.y + input_vehicle->width - wheel_width) * ZOOM_FACTOR + offset_y);

    render_v_wheel_br.move( (input_vehicle->pos.x) * ZOOM_FACTOR  + offset_x,
			    (input_vehicle->pos.y) * ZOOM_FACTOR  + offset_y);

    render_v_wheel_fl.move( (input_vehicle->pos.x + input_vehicle->length - wheel_length) * ZOOM_FACTOR  + offset_x,
			    (input_vehicle->pos.y + input_vehicle->width - wheel_width) * ZOOM_FACTOR  + offset_y);

    render_v_wheel_fr.move( (input_vehicle->pos.x + input_vehicle->length - wheel_length) * ZOOM_FACTOR  + offset_x,
			    (input_vehicle->pos.y) * ZOOM_FACTOR  + offset_y);


    sf::Vector2f center_wheel_l = sf::Vector2f( render_v_wheel_fl.getPosition().x + render_v_wheel_fl.getSize().x/2,
						render_v_wheel_fl.getPosition().y + render_v_wheel_fl.getSize().y/2 );

    sf::Vector2f center_wheel_r = sf::Vector2f( render_v_wheel_fr.getPosition().x + render_v_wheel_fr.getSize().x/2,
						render_v_wheel_fr.getPosition().y + render_v_wheel_fr.getSize().y/2 );

    steering_angle_rotation_l.rotate(input_vehicle->steering_angle, center_wheel_l);
    steering_angle_rotation_r.rotate(input_vehicle->steering_angle, center_wheel_r);


    window.draw(render_v_chassis, veh_rotation);
    window.draw(render_v_wheel_bl, veh_rotation);
    window.draw(render_v_wheel_br, veh_rotation);
    window.draw(render_v_wheel_fl, steering_angle_rotation_l);
    window.draw(render_v_wheel_fr, steering_angle_rotation_r);

///////////////////////////////////////////////////

//////////////////////////////////////////////////


}

void World::render_obstacles( sf::RenderWindow& window ){
    float ZOOM_FACTOR = (float)WINDOW_WIDTH / window_width_m;
    int offset_x = pan_x;
    int offset_y = pan_y;

    sf::RectangleShape rect_static;
    for( int i = 0; i < obstacles_static.size(); i++ ){
	rect_static = sf::RectangleShape( sf::Vector2f(obstacles_static[i].w * ZOOM_FACTOR,
						       obstacles_static[i].h * ZOOM_FACTOR ));

	rect_static.move( obstacles_static[i].x * ZOOM_FACTOR + offset_x,
			  obstacles_static[i].y * ZOOM_FACTOR + offset_y );
	rect_static.setFillColor( sf::Color(0, 0, 0) );
	window.draw(rect_static);
    }

    sf::RectangleShape rect_dynamic;
    for( int i = 0; i < obstacles_dynamic.size(); i++ ){
	rect_dynamic = sf::RectangleShape( sf::Vector2f( obstacles_dynamic[i].w * ZOOM_FACTOR,
							 obstacles_dynamic[i].h * ZOOM_FACTOR ));

	rect_dynamic.move( obstacles_dynamic[i].x * ZOOM_FACTOR + offset_x,
			   obstacles_dynamic[i].y * ZOOM_FACTOR + offset_y );
	rect_dynamic.setFillColor( sf::Color(100, 100, 100) );
	window.draw(rect_dynamic);
    }

}

void World::render_current_tracked_point( sf::RenderWindow& window ){
    if( wpt_tracking != NULL ){
	simple_car::state_to_model( *wpt_tracking_vehicle, wpt_tracking->state );
	render_vehicle(window, wpt_tracking_vehicle, 100);
    }
}

void World::render( sf::RenderWindow& window ){
    render_vehicle( window, vehicle );
    render_current_tracked_point( window );
    render_obstacles( window );
    render_meter_line( window );
    render_end_goal( window );
    render_global_tree( window );
    render_global_plan( window );
}

