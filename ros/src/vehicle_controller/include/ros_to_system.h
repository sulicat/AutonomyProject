#ifndef _ROS_TO_SYSTEM_SIMPLE_H_
#define _ROS_TO_SYSTEM_SIMPLE_H_

#include "BaseVehicle.h"
#include "vehicle_controller/VehicleState.h"

namespace simple_car{

    void model_to_state( vehicle_controller::VehicleState& veh_state,
			 BaseVehicle veh_model );

    void state_to_model( BaseVehicle& veh_model,
			 vehicle_controller::VehicleState veh_state );

};

#endif
