#include "global_planner.h"

global_planner::Trajectory create_global_plan( global_planner::VehicleState start,
					       global_planner::VehicleState end,
					       global_planner::CostMap cost_map ){

    global_planner::Trajectory out;
    global_planner::Waypoint wpt;

    wpt.state = start;
    out.points.push_back( wpt );

    wpt.state = end;
    out.points.push_back( wpt );

    return out;
}

