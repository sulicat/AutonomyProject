#include "node.h"

Node::Node( float _x, float _y ){
    x = _x;
    y = _y;
    visited = false;
    r = 0;
    g = 0;
    b = 0;
}

void Node::add_child( Node n ){
    children.push_back(n);
}


// assume no circular depen
std::vector<Node*> Node::get_all(){
    std::vector<Node*> stack;
    std::vector<Node*> visited;
    stack.push_back(this);

    while( stack.size() > 0 ){
	Node* current = stack[stack.size()-1];
	stack.pop_back();

	visited.push_back(current);

	for( int i = 0; i < current->children.size(); i++ ){
	    stack.push_back( &(current->children[i]) );
	}
    }

    return visited;
}


global_planner::RenderTree Node::create_render_tree(){
    global_planner::RenderTree out_tree;

    std::vector<Node*> stack;
    stack.push_back(this);

    while( stack.size() > 0 ){
	Node* current = stack[stack.size()-1];
	stack.pop_back();


	for( int i = 0; i < current->children.size(); i++ ){
	    stack.push_back( &(current->children[i]) );

	    global_planner::Line line;
	    line.x1 = current->x;
	    line.y1 = current->y;
	    line.x2 = current->children[i].x;
	    line.y2 = current->children[i].y;

	    out_tree.edges.push_back( line );
	}
    }

    return out_tree;
}
