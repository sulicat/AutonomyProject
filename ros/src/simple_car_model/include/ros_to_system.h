#ifndef _ROS_TO_SYSTEM_SIMPLE_H_
#define _ROS_TO_SYSTEM_SIMPLE_H_

#include "simple_car_model/VehicleState.h"
#include "BaseVehicle.h"

namespace simple_car{

    void model_to_state( simple_car_model::VehicleState& veh_state,
			 BaseVehicle veh_model );

    void state_to_model( BaseVehicle& veh_model,
			 simple_car_model::VehicleState veh_state );

};

#endif
