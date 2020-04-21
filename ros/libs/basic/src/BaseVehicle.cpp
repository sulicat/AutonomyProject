#include "BaseVehicle.h"

BaseVehicle::BaseVehicle(){
    pos = V2<float>(0, 0);
    vel = V2<float>(0,0);
    accel = V2<float>(0,0);
    steering_angle = 0;	// inline with vehicle
    vehicle_angle = 0;	// inline with x axis
    vehicle_angle_vel = 0;
    width = 1.7;
    length = 4;
    max_steering_angle = 50;
}

void BaseVehicle::update( float dt ){

    steering_angle += dt * steering_angle_vel;
    if (steering_angle > max_steering_angle) {
	steering_angle = max_steering_angle;
    }
    else if (steering_angle < -max_steering_angle) {
	steering_angle = -max_steering_angle;
    }


    vehicle_angle_vel = (linear_vel/length) * tan( steering_angle * DEG_TO_RAD );

    vel.x = dt * linear_vel * cos( vehicle_angle * DEG_TO_RAD );
    vel.y = dt * linear_vel * sin( vehicle_angle * DEG_TO_RAD );

    vehicle_angle += vehicle_angle_vel;
    pos.x += vel.x;

    if (pos.x > 400) {
	pos.x = 400;
    }

    pos.y += vel.y;

    if (pos.y > 400) {
	pos.y = 400;
    }
}
