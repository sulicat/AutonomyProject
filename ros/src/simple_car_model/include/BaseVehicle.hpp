#ifndef _BASE_VEHICLE_H_
#define _BASE_VEHICLE_H_

#include "V2.hpp"
#include <math.h>

#define PI 3.141592653589793
#define RAD_TO_DEG (180.0/PI)
#define DEG_TO_RAD (PI/180.0)

class BaseVehicle{
public:
    V2<float> pos;
    V2<float> vel;
    V2<float> accel;
    float steering_angle;	// angle of stearing from vehicle angle degrees/sec
    float vehicle_angle_vel;
    float vehicle_angle;	// angle of vehicle from x axis
    float linear_vel;
    float steering_angle_vel;
    float width;		// in m
    float length;		// in m

    BaseVehicle(){
	pos = V2<float>(0, 0);
	vel = V2<float>(0,0);
        accel = V2<float>(0,0);
	steering_angle = 0;	// inline with vehicle
	vehicle_angle = 0;	// inline with x axis
	vehicle_angle_vel = 0;
	width = 1.7;
	length = 4;
    }

    void update( float dt ){

	steering_angle += dt * steering_angle_vel;
	vehicle_angle_vel = (linear_vel/length) * tan( steering_angle * DEG_TO_RAD );

	vel.x = dt * linear_vel * cos( vehicle_angle * DEG_TO_RAD );
	vel.y = dt * linear_vel * sin( vehicle_angle * DEG_TO_RAD );

	vehicle_angle += vehicle_angle_vel;
	pos.x += vel.x;
	pos.y += vel.y;
    }

};

#endif
