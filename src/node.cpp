#include "../include/node/node.h"  
#include "../include/util/util.h"

void rwa2::Node::set_wall(int direction, bool is_wall) {
    m_walls.at(direction) = is_wall;
}

bool rwa2::Node::is_wall(int direction) const {
    return m_walls.at(direction);
}

int rwa2::Node::compute_number_of_walls() const {
    int weight{ 0 };
    int weight_n{ 0 };
    int weight_s{ 0 };
    int weight_e{ 0 };
    int weight_w{ 0 };
    if (is_wall(direction::NORTH))
        weight_n = 1;
    if (is_wall(direction::EAST))
        weight_s = 1;
    if (is_wall(direction::SOUTH))
        weight_e = 1;
    if (is_wall(direction::WEST))
        weight_w = 1;
    return weight + weight_n + weight_s + weight_e + weight_w;
}

int rwa2::Node::get_x(){
    return x;
}

void rwa2::Node::set_x(int X){
    x = X;
}

int rwa2::Node::get_y(){
    return y;
}

void rwa2::Node::set_y(int Y){
    y = Y;
}

bool rwa2::Node::operator==(rwa2::Node n){
    return (this->x == n.x && this->y == n.y);
    
}

void rwa2::Node::operator=(rwa2::Node n){
    this->x=n.x;
    this->y=n.y;
    this->m_walls=n.m_walls;
}

std::array<bool, 4> rwa2::Node::get_mwalls(){
    return m_walls;
}