#ifndef _NODE_H_
#define _NODE_H_

#include <map>
#include <queue>
#include "local_planner/VehicleState.h"
#include "local_planner/CostMap.h"
#include "local_planner/Waypoint.h"
#include "local_planner/Trajectory.h"
#include "local_planner/Line.h"
#include "local_planner/RenderTree.h"

class Node{
public:
    float x;
    float y;
    float angle;
    float vel;
    float steering_angle;
    bool visited;
    int r;
    int g;
    int b;
    std::vector<Node*> children;

    Node( );
    Node( float _x, float _y );
    Node( float _x, float _y, float angle );
    void add_child( Node* n );

    std::vector<Node*> get_all();
    local_planner::RenderTree create_render_tree();
    local_planner::Trajectory bfs_traj( Node* end );
    local_planner::Trajectory dfs_traj( Node* end );
};


#endif
