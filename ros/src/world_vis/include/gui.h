#ifndef _GUI_H_
#define _GUI_H_

#include "imgui.h"
#include "imgui-SFML.h"
#include "world_vis/VehicleState.h"
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

private:
    GUI();
    static GUI* instance;
    char path_obstacles[255];
    World* world;
    std::string* status;
    int* tele_angle;
    int* tracked_angle;

};

#endif
