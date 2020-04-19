#ifndef _GUI_H_
#define _GUI_H_

#include "imgui.h"
#include "imgui-SFML.h"
#include "world_vis/VehicleState.h"


class GUI{
public:
    static GUI* Instance();
    void render();

    void updateVehicleState( world_vis::VehicleState _state ){
	veh_state = _state;
    }


    world_vis::VehicleState veh_state;

private:
    GUI();
    static GUI* instance;

};

#endif
