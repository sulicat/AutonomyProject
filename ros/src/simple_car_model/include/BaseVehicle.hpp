#ifndef _BASE_VEHICLE_H_
#define _BASE_VEHICLE_H_

#include "V2.hpp"

class BaseVehicle{
public:
    V2<float> pos;
    V2<float> vel;
    V2<float> accel;
    float steering_angle; // angle of stearing from vehicle angle
    float vehicle_angle; // angle of vehicle from x axis
    float width; // in m
    float length; // in m

    BaseVehicle(){
	pos = V2<float>(10, 10);
	vel = V2<float>(0,0);
        accel = V2<float>(0,0);
	steering_angle = 20; // inline with vehicle
	vehicle_angle = 10;  // inline with x axis
	width = 1.7;
	length = 4;
    }

};


#endif
