#ifndef _BASE_VEHICLE_H_
#define _BASE_VEHICLE_H_

#include "V2.hpp"
#include <math.h>

#define PI 3.141592653589793
#define DEG_TO_RAD (180.0/PI)
#define RAD_TO_DEG (PI/180.0)

class BaseVehicle{
public:
    V2<float> pos;
    V2<float> vel;
    V2<float> accel;
    float steering_angle;	// angle of stearing from vehicle angle degrees/sec
    float vehicle_angle;	// angle of vehicle from x axis
    float linear_vel;
    float steering_angle_vel;
    float width;		// in m
    float length;		// in m

    BaseVehicle(){
	pos = V2<float>(0, 0);
	vel = V2<float>(0,0);
        accel = V2<float>(0,0);
	steering_angle = 20;	// inline with vehicle
	vehicle_angle = 10;	// inline with x axis
	width = 1.7;
	length = 4;
    }

    void update( float dt ){
	pos.x += dt * linear_vel * cos( vehicle_angle * DEG_TO_RAD );
	pos.y += dt * linear_vel * sin( vehicle_angle * DEG_TO_RAD );
    }

};


#endif
