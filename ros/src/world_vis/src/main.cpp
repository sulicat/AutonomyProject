#include <SFML/Graphics.hpp>
#include "V2.hpp"
#include "BaseVehicle.hpp"
#include <iostream>

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720


class World{
public:
    BaseVehicle* vehicle;
    bool vehicle_set;
    float window_width_m;

    World(){
	vehicle_set = false;
	window_width_m = 100;
    }

    void set_vehicle( BaseVehicle* new_vehicle ){
	vehicle = new_vehicle;
	vehicle_set = true;
    }

    void render_vehicle( sf::RenderWindow& window ){
	float ZOOM_FACTOR = (float)WINDOW_WIDTH / window_width_m;

	// chassis
	render_v_chassis = sf::RectangleShape( sf::Vector2f(vehicle->length * ZOOM_FACTOR,
							    vehicle->width * ZOOM_FACTOR) );

	render_v_chassis.move( vehicle->pos.x * ZOOM_FACTOR,
			       vehicle->pos.y * ZOOM_FACTOR );

	render_v_chassis.setFillColor( sf::Color(0, 0, 0, 0) );
	render_v_chassis.setOutlineColor( sf::Color(0, 0, 0, 255) );
	render_v_chassis.setOutlineThickness(1.0);


	sf::Vector2f veh_center = sf::Vector2f(render_v_chassis.getPosition().x + render_v_chassis.getSize().x/2,
						    render_v_chassis.getPosition().y + render_v_chassis.getSize().y/2);

	sf::Transform veh_rotation;
	sf::Transform steering_angle_rotation_l;
	sf::Transform steering_angle_rotation_r;

	veh_rotation.rotate(vehicle->vehicle_angle, veh_center);
	steering_angle_rotation_l.rotate(vehicle->vehicle_angle, veh_center);
	steering_angle_rotation_r.rotate(vehicle->vehicle_angle, veh_center);

	//veh_rotation.rotate(0, veh_center);

	// wheels
	float wheel_width = vehicle->width * 0.2;
	float wheel_length = vehicle->length * 0.3;

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
        render_v_wheel_bl.setFillColor( sf::Color(0, 0, 0, 255) );
        render_v_wheel_br.setFillColor( sf::Color(0, 0, 0, 255) );
        render_v_wheel_fl.setFillColor( sf::Color(0, 0, 255, 255) );
        render_v_wheel_fr.setFillColor( sf::Color(0, 0, 255, 255) );

        render_v_wheel_bl.move( (vehicle->pos.x) * ZOOM_FACTOR,
				(vehicle->pos.y + vehicle->width - wheel_width) * ZOOM_FACTOR );

        render_v_wheel_br.move( (vehicle->pos.x) * ZOOM_FACTOR,
				(vehicle->pos.y) * ZOOM_FACTOR );

        render_v_wheel_fl.move( (vehicle->pos.x + vehicle->length - wheel_length) * ZOOM_FACTOR,
				(vehicle->pos.y + vehicle->width - wheel_width) * ZOOM_FACTOR );

        render_v_wheel_fr.move( (vehicle->pos.x + vehicle->length - wheel_length) * ZOOM_FACTOR,
				(vehicle->pos.y) * ZOOM_FACTOR );


	sf::Vector2f center_wheel_l = sf::Vector2f( render_v_wheel_fl.getPosition().x + render_v_wheel_fl.getSize().x/2,
						    render_v_wheel_fl.getPosition().y + render_v_wheel_fl.getSize().y/2 );

	sf::Vector2f center_wheel_r = sf::Vector2f( render_v_wheel_fr.getPosition().x + render_v_wheel_fr.getSize().x/2,
						    render_v_wheel_fr.getPosition().y + render_v_wheel_fr.getSize().y/2 );

	steering_angle_rotation_l.rotate(vehicle->steering_angle, center_wheel_l);
	steering_angle_rotation_r.rotate(vehicle->steering_angle, center_wheel_r);


	window.draw(render_v_chassis, veh_rotation);
	window.draw(render_v_wheel_bl, veh_rotation);
	window.draw(render_v_wheel_br, veh_rotation);
	window.draw(render_v_wheel_fl, steering_angle_rotation_l);
	window.draw(render_v_wheel_fr, steering_angle_rotation_r);

	sf::CircleShape orig(2);
	orig.setPosition(veh_center);
	orig.setFillColor(sf::Color(255,0,0));
	window.draw(orig);


    }

    void render_obstacles( sf::RenderWindow& window ){

    }

    void render( sf::RenderWindow& window ){
	render_vehicle(window);
	render_obstacles(window);
    }

private:
    // vehicle shapes
    sf::RectangleShape render_v_chassis;
    sf::RectangleShape render_v_wheel_bl;
    sf::RectangleShape render_v_wheel_br;
    sf::RectangleShape render_v_wheel_fl;
    sf::RectangleShape render_v_wheel_fr;


};




int main(){
    sf::RenderWindow window(sf::VideoMode(1080, 720), "World Vis");

    World world;
    BaseVehicle vehicle;
    world.set_vehicle( &vehicle );



    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear( sf::Color(255,255,255) );
	world.render( window );
	vehicle.vehicle_angle += 0.01;

        window.display();
    }

    return 0;
}
