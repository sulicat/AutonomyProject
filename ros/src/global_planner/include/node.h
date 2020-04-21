#ifndef _NODE_H_
#define _NODE_H_

#include "global_planner/VehicleState.h"
#include "global_planner/CostMap.h"
#include "global_planner/Waypoint.h"
#include "global_planner/Trajectory.h"
#include "global_planner/Line.h"
#include "global_planner/RenderTree.h"

class Node{
public:
    float x;
    float y;
    bool visited;
    int r;
    int g;
    int b;
    std::vector<Node> children;

    Node( float _x, float _y );
    void add_child( Node n );

    std::vector<Node*> get_all();
    global_planner::RenderTree create_render_tree();

};


#endif
