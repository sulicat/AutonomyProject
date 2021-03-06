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
    float max_steering_angle;	// in degrees

    BaseVehicle();

    void update( float dt );
};

#endif
