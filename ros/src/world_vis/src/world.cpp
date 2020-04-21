#include "world.h"

World::World(){
    vehicle_set = false;
    window_width_m = 100;// adjust to 100 for 1080x720 screen
    wpt_tracking_vehicle = new BaseVehicle();
    wpt_tracking = NULL;
}

void World::set_vehicle( BaseVehicle* new_vehicle ){
    vehicle = new_vehicle;
    vehicle_set = true;
}

void World::set_tracked_wpt( world_vis::Waypoint* wpt ){
    wpt_tracking = wpt;
    simple_car::state_to_model( *wpt_tracking_vehicle, wpt_tracking->state );
}

void World::render_vehicle( sf::RenderWindow& window,
			    BaseVehicle* input_vehicle,
			    int alpha ){

    float ZOOM_FACTOR = (float)WINDOW_WIDTH / window_width_m;

    // chassis
    render_v_chassis = sf::RectangleShape( sf::Vector2f(input_vehicle->length * ZOOM_FACTOR,
							input_vehicle->width * ZOOM_FACTOR) );

    render_v_chassis.move( input_vehicle->pos.x * ZOOM_FACTOR,
			   input_vehicle->pos.y * ZOOM_FACTOR );

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

    render_v_wheel_bl.move( (input_vehicle->pos.x) * ZOOM_FACTOR,
			    (input_vehicle->pos.y + input_vehicle->width - wheel_width) * ZOOM_FACTOR );

    render_v_wheel_br.move( (input_vehicle->pos.x) * ZOOM_FACTOR,
			    (input_vehicle->pos.y) * ZOOM_FACTOR );

    render_v_wheel_fl.move( (input_vehicle->pos.x + input_vehicle->length - wheel_length) * ZOOM_FACTOR,
			    (input_vehicle->pos.y + input_vehicle->width - wheel_width) * ZOOM_FACTOR );

    render_v_wheel_fr.move( (input_vehicle->pos.x + input_vehicle->length - wheel_length) * ZOOM_FACTOR,
			    (input_vehicle->pos.y) * ZOOM_FACTOR );


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

}

void World::render_current_tracked_point( sf::RenderWindow& window ){
    if( wpt_tracking != NULL ){
	simple_car::state_to_model( *wpt_tracking_vehicle, wpt_tracking->state );
	render_vehicle(window, wpt_tracking_vehicle, 100);
    }
}

void World::render( sf::RenderWindow& window ){
    render_vehicle(window, vehicle);
    render_current_tracked_point( window );
    render_obstacles(window);
}

