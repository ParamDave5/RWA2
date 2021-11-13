#include "../include/mouse/mouse.h"  
#include "../include/api/api.h"  
#include "../include/util/util.h"
#include <string>
#include <iostream>

void rwa2::Mouse::display_walls() {
    for (int x = 0; x < m_maze_width; x += 1) {
        for (int y = 0; y < m_maze_height; y += 1) {
            if (m_maze.at(x).at(y).is_wall(direction::NORTH)) {
                //display this wall in the simulator
                API::setWall(x, y, 'n');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::EAST)) {
                //display this wall in the simulator
                API::setWall(x, y, 'e');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::SOUTH)) {
                //display this wall in the simulator
                API::setWall(x, y, 's');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::WEST)) {
                //display this wall in the simulator
                API::setWall(x, y, 'w');
            }
            //display the number of walls surrounding the current node
            API::setText(x, y, std::to_string(m_maze.at(x).at(y).compute_number_of_walls()));
        }
    }
}

int rwa2::Mouse::get_mx(){
    return m_x;
}

int rwa2::Mouse::get_my(){
    return m_y;
}

int rwa2::Mouse::get_mdirection(){
    return m_direction;
}

void rwa2::Mouse::set_mx(int mx){
    m_x = mx;
}

void rwa2::Mouse::set_my(int my){
    m_y = my;
}

void rwa2::Mouse::set_mdirection(int mdirection){
    m_direction = mdirection;
}

// Checks if the node in the maze is already visited by the mouse 
bool rwa2::Mouse::is_in_vector(rwa2::Node n, std::vector<rwa2::Node> v){
    for(int i=0;i<v.size();i++){
        if(n==v.at(i)) return true;
    }
    return false;
}

// The function Implements DFS for finding the Path in the maze from the start node to the end node
bool rwa2::Mouse::search_maze(rwa2::Node current_node, rwa2::Node goal_node, std::stack<rwa2::Node>& s, std::vector<rwa2::Node>& back_track, std::vector<rwa2::Node>& visited_vector){
    if(!(current_node == goal_node)){
        if(s.empty()){
            s.push(current_node);
        }
    }
    else return true; 
    //pushes the current node in the visited vector if it is not already present in the visited vector
    if(!is_in_vector(current_node,visited_vector)) visited_vector.push_back(current_node);

    //Checks the north direction of the current node to check if it is valid or not
    if(!m_maze.at(current_node.get_x()).at(current_node.get_y()).is_wall(NORTH) && !is_in_vector(m_maze.at(current_node.get_x()).at(current_node.get_y()+1),visited_vector)){
        current_node.set_y(current_node.get_y()+1);
        s.push(current_node);
    }
    //Checks the east direction of the current node to check if it is valid or not
    else if(!m_maze.at(current_node.get_x()).at(current_node.get_y()).is_wall(EAST) && !is_in_vector(m_maze.at(current_node.get_x()+1).at(current_node.get_y()),visited_vector)){
        current_node.set_x(current_node.get_x()+1);
        s.push(current_node);
    }
    //Checks the south direction of the current node to check if it is valid or not
    else if(!m_maze.at(current_node.get_x()).at(current_node.get_y()).is_wall(SOUTH) && !is_in_vector(m_maze.at(current_node.get_x()).at(current_node.get_y()-1),visited_vector)){
        current_node.set_y(current_node.get_y()-1);
        s.push(current_node);
    }
    //Checks the west direction of the current node to check if it is valid or not
    else if(!m_maze.at(current_node.get_x()).at(current_node.get_y()).is_wall(WEST) && !is_in_vector(m_maze.at(current_node.get_x()-1).at(current_node.get_y()),visited_vector)){
        current_node.set_x(current_node.get_x()-1);
        s.push(current_node);
    }

    /*If a valid node around the current node is not found the following statement removes the current node from stack and also 
    pushes the next node in the backtrack vector for the mouse to move to the valid node in the simulator*/
    else{
        if(!s.empty()){
            s.pop();
            back_track.push_back(s.top());
        } 
        else return false;
    }
    //If the stack is not empty after backtracking the following statement recursively call the search_maze function with the 
    //updated stack till a path is found
    if(!s.empty()){
        current_node = s.top();
        return search_maze(current_node,goal_node,s,back_track,visited_vector);
    }
    else return false; 
}

void rwa2::Mouse::move_forward(){
    if(m_direction==NORTH) m_y=m_y+1;
    else if(m_direction==EAST) m_x=m_x+1;
    else if(m_direction==SOUTH) m_y=m_y-1;
    else m_x=m_x-1;
    //Moves the mouse forward by one node in the simulator
    API::moveForward();
}

void rwa2::Mouse::turn_left(){
    if(m_direction==NORTH) m_direction=WEST;
    else if(m_direction==EAST) m_direction=NORTH;
    else if(m_direction==SOUTH) m_direction=EAST;
    else m_direction=SOUTH;
    //Turns the mouse in the left direction of the mouse in the simulator
    API::turnLeft();
}

void rwa2::Mouse::turn_right(){
    if(m_direction==NORTH) m_direction=EAST;
    else if(m_direction==EAST) m_direction=SOUTH;
    else if(m_direction==SOUTH) m_direction=WEST;
    else m_direction=NORTH;
    //Turns the mouse in the right direction of the mouse in the simulator
    API::turnRight();
}

rwa2::Node* rwa2::Mouse::get_maze(int x, int y){
     return &m_maze.at(x).at(y);
}
