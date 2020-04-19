#ifndef _ROS_TO_SYSTEM_SIMPLE_H_
#define _ROS_TO_SYSTEM_SIMPLE_H_

#include "BaseVehicle.h"
#include "world_vis/VehicleState.h"

namespace simple_car{

    void model_to_state( world_vis::VehicleState& veh_state,
			 BaseVehicle veh_model );

    void state_to_model( BaseVehicle& veh_model,
			 world_vis::VehicleState veh_state );

};

#endif
