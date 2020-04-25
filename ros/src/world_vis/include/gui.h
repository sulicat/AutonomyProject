#ifndef _GUI_H_
#define _GUI_H_

#include "imgui.h"
#include "imgui-SFML.h"
#include "world_vis/VehicleState.h"
#include "world_vis/PID_Gains.h"
#include "world.h"



class GUI{
public:
    static GUI* Instance();
    void render();

    void set_world( World* new_world ){
	world = new_world;
    }

    void updateVehicleState( world_vis::VehicleState _state ){
	veh_state = _state;
    }

    void updatePID_Gains( world_vis::PID_Gains _gains ){
    pid_gains = _gains;
    }

    void setStatus( std::string* _stat ){
	status = _stat;
    }

    void setTeleAngle( int* _t_angle ){
	tele_angle = _t_angle;
    }

    void setTrackedAngle( int* _t_angle ){
	tracked_angle = _t_angle;
    }

    world_vis::VehicleState veh_state;
    world_vis::PID_Gains pid_gains;

    //world_vis::PID_Gains pid_gains;
private:
    GUI();
    static GUI* instance;
    char path_obstacles[255];
    World* world;
    std::string* status;
    int* tele_angle;
    int* tracked_angle;
    // int kp_ang_vel_direction;
    // int kp_ang_vel_heading;
    // int kp_lin_vel;
    // int kp_ang_vel;
    // int ki_lin_vel;
    // int ki_ang_vel;
    // int kd_lin_vel;
    // int kd_ang_vel;
};

#endif
