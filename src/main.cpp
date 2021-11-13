#include <iostream>
#include <array>
#include <chrono>
#include <thread>
#include "../include/mouse/mouse.h"
#include "../include/api/api.h"

int main() {
	rwa2::Mouse mouse;
	rwa2::Node n;
	rwa2::Node g;
	g.set_x(7);
	g.set_y(7);
	mouse.display_walls();
	bool path_found;
	std::stack<rwa2::Node> s;
	std::vector<rwa2::Node> back_track;
	std::vector<rwa2::Node> v;
	std::vector<rwa2::Node> v1;
	std::stack<rwa2::Node> s_inv;
	//The following loops runs till the mouse reach the goal position
	while(true){
		API::clearAllColor();
		API::setColor(g.get_x(),g.get_y(),'g');
		API::setText(g.get_x(),g.get_y(),"G1");
		n = *mouse.get_maze(mouse.get_mx(),mouse.get_my());
		while(!back_track.empty()){
			back_track.pop_back();
		}
		while(!s_inv.empty()){
			s_inv.pop();
		}
		//calls the search_maze function in the class mouse to find a path
		path_found = mouse.search_maze(n,g,s,back_track,v);
		if(!path_found || n==g) break;
		int stack_length2 = s.size();
		int stack_length3 = 0;
		while(!v.empty()){
			v.pop_back();
		}
		//Below Loop is used to fill the visited vector with past iterations visited vector
		for(int i=0;i<v1.size();i++){
			v.push_back(v1.at(i));
		}

		for(int i=0;i<back_track.size();i++){
			if(mouse.is_in_vector(back_track.at(i),v1)) stack_length3++;
		}

		//The below loops are used to add the back_track nodes and respectively update the path stack with proper nodes so that the mouse follows
		//the backtrack path till it reaches the appropriate node to continue towards the goal node 
			for(int i=0;i<stack_length2;i++){
				API::setColor(s.top().get_x(),s.top().get_y(),'y');
				API::setColor(g.get_x(),g.get_y(),'g');
				if(mouse.is_in_vector(s.top(),v1)){
					s_inv.push(s.top());
					s.pop();
					break;
					}
				s_inv.push(s.top());
				s.pop();
			}
		for(int i=back_track.size()-1;i>=0;i--){
			if(mouse.is_in_vector(back_track.at(i),v1)){
				API::setColor(back_track.at(i).get_x(),back_track.at(i).get_y(),'y');
				s_inv.push(back_track.at(i));
			} 
		}
		if(s_inv.top() == *mouse.get_maze(mouse.get_mx(),mouse.get_my())){
			if(stack_length3==0){
				s.push(s_inv.top());
			}
			s_inv.pop();
			if(!stack_length3==0) stack_length3--;
		}
		stack_length2=s_inv.size();
		//The following loops moves the mouse on the path given by the search maze function while checking for the wall in front of the mouse
		//and breaks the for loop if a wall is encountered in front of the mouse on the path
		//It also sets the wall along the path as the mouse moves along the path
		for(int i=0;i<stack_length2;i++){

			//Following loop moves the mouse in +y direction while checking for the walls and considering current mouse direction.
			if(s_inv.top().get_y()==mouse.get_my()+1){
				if(mouse.get_mdirection()==NORTH){
					if(API::wallFront()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'n');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(NORTH,true);
						std::cerr<<mouse.get_maze(mouse.get_mx(),mouse.get_my())->is_wall(NORTH)<<"\n";
						break;
					}
					if(API::wallLeft()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'w');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(WEST,true);
					}
					if(API::wallRight()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'e');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(EAST,true);
					}
					mouse.move_forward();
					if(!mouse.is_in_vector(s_inv.top(),v)){
						v.push_back(s_inv.top());
						v1.push_back(s_inv.top());
					}
				}
				else if(mouse.get_mdirection()==EAST){
					if(API::wallFront()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'e');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(EAST,true);
					}
					if(API::wallLeft()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'n');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(NORTH,true);
						break;
					}
					if(API::wallRight()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'s');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(SOUTH,true);
					}
					mouse.turn_left();
					mouse.move_forward();
					if(!mouse.is_in_vector(s_inv.top(),v)){
						v.push_back(s_inv.top());
						v1.push_back(s_inv.top());
					}
				}
				else if(mouse.get_mdirection()==SOUTH){
					if(API::wallFront()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'s');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(SOUTH,true);
					}
					if(API::wallLeft()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'e');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(EAST,true);
					}
					if(API::wallRight()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'w');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(WEST,true);
					}
					mouse.turn_right();
					mouse.turn_right();
					mouse.move_forward();
					if(!mouse.is_in_vector(s_inv.top(),v)){
						v.push_back(s_inv.top());
						v1.push_back(s_inv.top());
					}
				}
				else{
					if(API::wallFront()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'w');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(WEST,true);
					}
					if(API::wallLeft()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'s');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(SOUTH,true);
					}
					if(API::wallRight()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'n');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(NORTH,true);
						break;
					}
					mouse.turn_right();
					mouse.move_forward();
					if(!mouse.is_in_vector(s_inv.top(),v)){
						v.push_back(s_inv.top());
						v1.push_back(s_inv.top());
					}
				}
			}
			
			//Following loop moves the mouse in +x direction while checking for the walls and considering current mouse direction.
			else if(s_inv.top().get_x()==mouse.get_mx()+1){
				if(mouse.get_mdirection()==EAST){
					if(API::wallFront()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'e');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(EAST,true);
						break;
					}
					if(API::wallLeft()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'n');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(NORTH,true);
					}
					if(API::wallRight()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'s');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(SOUTH,true);
					}
					mouse.move_forward();
					if(!mouse.is_in_vector(s_inv.top(),v)){
						v.push_back(s_inv.top());
						v1.push_back(s_inv.top());
					}
				}
				else if(mouse.get_mdirection()==SOUTH){
					if(API::wallFront()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'s');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(SOUTH,true);
					}
					if(API::wallLeft()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'e');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(EAST,true);
						break;
					}
					if(API::wallRight()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'w');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(WEST,true);
					}
					mouse.turn_left();
					mouse.move_forward();
					if(!mouse.is_in_vector(s_inv.top(),v)){
						v.push_back(s_inv.top());
						v1.push_back(s_inv.top());
					}
				}
				else if(mouse.get_mdirection()==WEST){
					if(API::wallFront()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'w');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(WEST,true);
					}
					if(API::wallLeft()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'s');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(SOUTH,true);
					}
					if(API::wallRight()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'n');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(NORTH,true);
					}
					mouse.turn_right();
					mouse.turn_right();
					mouse.move_forward();
					if(!mouse.is_in_vector(s_inv.top(),v)){
						v.push_back(s_inv.top());
						v1.push_back(s_inv.top());
					}
				}
				else{
					if(API::wallFront()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'n');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(NORTH,true);
					}
					if(API::wallLeft()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'w');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(WEST,true);
					}
					if(API::wallRight()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'e');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(EAST,true);
						break;
					}
					mouse.turn_right();
					mouse.move_forward();
					if(!mouse.is_in_vector(s_inv.top(),v)){
						v.push_back(s_inv.top());
						v1.push_back(s_inv.top());
					}
				}
			}
			
			//Following loop moves the mouse in -y direction while checking for the walls and considering current mouse direction.
			else if(s_inv.top().get_y()==mouse.get_my()-1){
				if(mouse.get_mdirection()==SOUTH){
					if(API::wallFront()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'s');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(SOUTH,true);
						break;
					}
					if(API::wallLeft()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'e');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(EAST,true);
					}
					if(API::wallRight()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'w');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(WEST,true);
					}
					mouse.move_forward();
					if(!mouse.is_in_vector(s_inv.top(),v)){
						v.push_back(s_inv.top());
						v1.push_back(s_inv.top());
					}
				}
				else if(mouse.get_mdirection()==WEST){
					if(API::wallFront()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'w');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(WEST,true);
					}
					if(API::wallLeft()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'s');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(SOUTH,true);
						break;
					}
					if(API::wallRight()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'n');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(NORTH,true);
					}
					mouse.turn_left();
					mouse.move_forward();
					if(!mouse.is_in_vector(s_inv.top(),v)){
						v.push_back(s_inv.top());
						v1.push_back(s_inv.top());
					}
				}
				else if(mouse.get_mdirection()==NORTH){
					if(API::wallFront()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'n');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(NORTH,true);
					}
					if(API::wallLeft()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'w');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(WEST,true);
					}
					if(API::wallRight()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'e');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(EAST,true);
					}
					mouse.turn_right();
					mouse.turn_right();
					mouse.move_forward();
					if(!mouse.is_in_vector(s_inv.top(),v)){
						v.push_back(s_inv.top());
						v1.push_back(s_inv.top());
					}
				}
				else{
					if(API::wallFront()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'e');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(EAST,true);
					}
					if(API::wallLeft()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'n');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(NORTH,true);
					}
					if(API::wallRight()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'s');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(SOUTH,true);
						break;
					}
					mouse.turn_right();
					mouse.move_forward();
					if(!mouse.is_in_vector(s_inv.top(),v)){
						v.push_back(s_inv.top());
						v1.push_back(s_inv.top());
					}
				}
			}
			
			//Following loop moves the mouse in -x direction while checking for the walls and considering current mouse direction.
			else if(s_inv.top().get_x()==mouse.get_mx()-1){
				if(mouse.get_mdirection()==WEST){
					if(API::wallFront()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'w');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(WEST,true);
						break;
					}
					if(API::wallLeft()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'s');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(SOUTH,true);
					}
					if(API::wallRight()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'n');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(NORTH,true);
					}
					mouse.move_forward();
					if(!mouse.is_in_vector(s_inv.top(),v)){
						v.push_back(s_inv.top());
						v1.push_back(s_inv.top());
					}
				}
				else if(mouse.get_mdirection()==NORTH){
					if(API::wallFront()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'n');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(NORTH,true);
					}
					if(API::wallLeft()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'w');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(WEST,true);
						break;
					}
					if(API::wallRight()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'e');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(EAST,true);
					}
					mouse.turn_left();
					mouse.move_forward();
					if(!mouse.is_in_vector(s_inv.top(),v)){
						v.push_back(s_inv.top());
						v1.push_back(s_inv.top());
					}
				}
				else if(mouse.get_mdirection()==EAST){
					if(API::wallFront()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'e');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(EAST,true);
					}
					if(API::wallLeft()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'n');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(NORTH,true);
					}
					if(API::wallRight()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'s');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(SOUTH,true);
					}
					mouse.turn_right();
					mouse.turn_right();
					mouse.move_forward();
					if(!mouse.is_in_vector(s_inv.top(),v)){
						v.push_back(s_inv.top());
						v1.push_back(s_inv.top());
					}
				}
				else{
					if(API::wallFront()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'s');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(SOUTH,true);
					}
					if(API::wallLeft()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'e');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(EAST,true);
					}
					if(API::wallRight()){
						API::setWall(mouse.get_mx(),mouse.get_my(),'w');
						mouse.get_maze(mouse.get_mx(),mouse.get_my())->set_wall(WEST,true);	
						break;
					}
					mouse.turn_right();
					mouse.move_forward();
					if(!mouse.is_in_vector(s_inv.top(),v)){
						v.push_back(s_inv.top());
						v1.push_back(s_inv.top());
					}
				}
			}

			if(!stack_length3==0) stack_length3--;
			if(stack_length3==0){
				s.push(s_inv.top());
			}
			s_inv.pop();
		}
	}
	//The following loop highlights the path from goal to start in green colour
	while(!s.empty()){
		using namespace std::this_thread; // sleep_for
    	using namespace std::chrono; // nanoseconds
		sleep_for(nanoseconds(100000000));
		API::setColor(s.top().get_x(),s.top().get_y(),'g');
		s_inv.push(s.top());
		s.pop();
	}
}