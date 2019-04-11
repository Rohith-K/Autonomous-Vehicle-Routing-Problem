// =================================================================
// AUTHOR			: Rohith Krishnan
// CREATE DATE      : 01.23.2019
// PURPOSE			: Vehicle Class definition to store the status 
//					  of the vehicle at every instance
// =================================================================
// Change History:
//
// =================================================================


/*


Class attributes:
					- Vehicle spawn location
					- Current vehicle position
					- Current target for the vehicle
					- City Grid dimensions
					- Time step counter
					- List to store current passengers in the car
					- List to store the order queue received
					

Class Methods:
					- Constructor to initialize some of the parameters
					- move() overloaded method to advance the car by one time step
					  based on whether a new order has been placed
					- print_info() method to print the current vehicle details
					- mission_planner() method to decide next target grid point
					- advance_step() to advance the time step 
					- is_pickup() method to pickup passengers at a pickup spot
					- is_dropoff() to drop off passengers at a drop point
					- is_home() method to determine if the vehicle has reached home
*/


#pragma once

#include "Grid_pt.h"
#include <vector>
#include <list>
#include "Passenger.h"
#include "helper_functions.h"


class Vehicle {

	grid_pt spawn_loc;
	grid_pt curr_pos;
	grid_pt curr_target;
	char** city_grid;
	const int grid_x;
	const int grid_y;
	void reset_grid();
	int time_step = 0;

public:

	std::list<Passenger> curr_pass;
	std::list<Passenger> order_queue;
	Vehicle(grid_pt spawn_loc, const int M, const int N);
	~Vehicle();
	void move(std::vector<Passenger> &order_list);
	void move();
	void print_info();
	void show_veh();
	void mission_planner();
	void advance_step();
	void is_pickup();
	void is_dropoff();
	bool is_home();

};