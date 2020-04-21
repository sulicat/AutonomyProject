#ifndef _GLOBAL_PLANNER_H_
#define _GLOBAL_PLANNER_H_

#include "global_planner/VehicleState.h"
#include "global_planner/CostMap.h"
#include "global_planner/Waypoint.h"
#include "global_planner/Trajectory.h"


global_planner::Trajectory create_global_plan( global_planner::VehicleState start,
					       global_planner::VehicleState end,
					       global_planner::CostMap cost_map );

#endif
