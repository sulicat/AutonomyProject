#include "node.h"

Node::Node() : Node(0,0){
}

Node::Node( float _x, float _y ) : Node( _x, _y, 0 ){
}

Node::Node( float _x, float _y, float _angle ){
    x = _x;
    y = _y;
    angle = _angle;
    visited = false;
    r = 0;
    g = 0;
    b = 0;
}

void Node::add_child( Node* n ){
    children.push_back(n);
}


// assume no circular depen
std::vector<Node*> Node::get_all(){
    std::vector<Node*> stack;
    std::map<Node*, Node*> parent_map;
    std::vector<Node*> visited;
    stack.push_back(this);

    while( stack.size() > 0 ){
	Node* current = stack[stack.size()-1];
	stack.pop_back();

	visited.push_back(current);
	parent_map[current] = NULL; // we don't care about parents here

	for( int i = 0; i < current->children.size(); i++ ){
	    // if we have not yet seen this child
	    if( parent_map.find( current->children[i] ) == parent_map.end() )
		stack.push_back( current->children[i] );
	}
    }

    return visited;
}


local_planner::RenderTree Node::create_render_tree(){
    local_planner::RenderTree out_tree;

    std::vector<Node*> stack;
    std::map<Node*, Node*> parent_map;
    stack.push_back(this);
    Node* current = this;
    Node* parent = this;
    while( stack.size() > 0 ){

	parent_map[current] = parent;
	current = stack[stack.size()-1];
	parent = current;

	stack.pop_back();

	for( int i = 0; i < current->children.size(); i++ ){
	    if( parent_map.find( current->children[i] ) == parent_map.end() ){
		stack.push_back( (current->children[i]) );

		local_planner::Line line;
		line.x1 = current->x;
		line.y1 = current->y;
		line.x2 = current->children[i]->x;
		line.y2 = current->children[i]->y;

		out_tree.edges.push_back( line );
	    }
	}
    }

    return out_tree;
}


local_planner::Trajectory Node::bfs_traj( Node* end ){
    local_planner::Trajectory out;
    std::vector<Node*> stack;
    std::map<Node*, Node*> parent_map;
    stack.push_back(this);
    Node* current = this;
    Node* parent = this;

    while( stack.size() > 0 ){

	current = stack[stack.size()-1];
	stack.pop_back();

	for( int i = 0; i < current->children.size(); i++ ){
	    if( parent_map.find( current->children[i] ) == parent_map.end() ){
		stack.push_back( (current->children[i]) );
		parent_map[current->children[i]] = current;
	    }
	}
    }

    parent_map[this] = NULL;

    current = end;
    while( current != NULL &&
	   parent_map.find( current ) != parent_map.end() ){

	current = parent_map[current];
	if(current == this){
	    break;
	}

	local_planner::Waypoint wp;
	wp.state.pos.x = parent_map[current]->x;
	wp.state.pos.y = parent_map[current]->y;
	out.points.push_back( wp );
    }

    return out;
}


local_planner::Trajectory Node::dfs_traj( Node* end ){
    local_planner::Trajectory out;
    std::queue<Node*> queue;
    std::map<Node*, Node*> parent_map;
    queue.push(this);
    Node* current = this;
    Node* parent = this;

    while( queue.size() > 0 ){

	current = queue.front();
	queue.pop();

	for( int i = 0; i < current->children.size(); i++ ){
	    if( parent_map.find( current->children[i] ) == parent_map.end() ){
		queue.push( (current->children[i]) );
		parent_map[current->children[i]] = current;
	    }
	}
    }

    parent_map[this] = NULL;

    current = end;
    local_planner::Waypoint wp;
    wp.state.pos.x = current->x;
    wp.state.pos.y = current->y;
    out.points.insert( out.points.begin(), wp );

    while( current != NULL &&
	   parent_map.find( current ) != parent_map.end() ){

	current = parent_map[current];
	if(current == this){
	    break;
	}

	wp.state.pos.x = parent_map[current]->x;
	wp.state.pos.y = parent_map[current]->y;
	out.points.insert( out.points.begin(), wp );
    }

    return out;
}
