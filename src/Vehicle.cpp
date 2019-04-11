// =================================================================
// AUTHOR			: Rohith Krishnan
// CREATE DATE      : 01.23.2019
// PURPOSE			: Vehicle class definition file
// =================================================================
// Change History:
//
// =================================================================


#include "Vehicle.h"


// Constructor
Vehicle::Vehicle(grid_pt spawn_loc, const int M, const int N) :
	spawn_loc(spawn_loc), curr_pos(spawn_loc), curr_target(spawn_loc), grid_x(N), grid_y(M) {

	std::cout << std::endl << "Vehicle spawned at: ";
	this->spawn_loc.print_pos();

	// dynamic allocation
	city_grid = new char*[grid_x];
	for (int i = 0; i < grid_x; ++i)
		city_grid[i] = new char[grid_y];

	reset_grid();
	std::cout << "Grid created..." << std::endl;
	show_veh();
	std::cout << "--------------------------------------------------------\n" << std::endl;

};

// Destructor
Vehicle::~Vehicle() {

	for (int i = 0; i < grid_x; ++i)
		delete[] city_grid[i];
	delete[] city_grid;

	
	std::cout << "\nGrid destroyed..." << std::endl;
	std::cin.ignore();
	std::cin.get();

};

// re-initialize the grid
void Vehicle::reset_grid()
{

	for (int i = 0; i < grid_x; ++i)
		for (int j = 0; j < grid_y; ++j)
			city_grid[i][j] = '.';

	city_grid[curr_pos.y][curr_pos.x] = 'X';

}

// show the vehicle on the grid
void Vehicle::show_veh() {

	for (int i = 0; i < grid_x; ++i) {
		for (int j = 0; j < grid_y; ++j) {
			std::cout << city_grid[i][j] << " ";
		}
		std::cout << std::endl;
	}	
	std::cout << std::endl;

}

// method to print current position, next destination 
// and the passengers presently in the car
void Vehicle::print_info() {

	std::cout << "Time step:" << time_step << std::endl;
	std::cout << "Current position: ";
	curr_pos.print_pos();
	std::cout << "Current target: ";
	curr_target.print_pos();
	std::cout << "Current passengers: ";
	if (curr_pass.empty()) {
		std::cout << "None" << std::endl;
	}
	else {
		for (Passenger p : curr_pass) {
			std::cout << p.name << " ";
		}
	}
	std::cout << "\n\n\n";

}

// method that determines if any passengers need to be picked up 
void Vehicle::is_pickup() {

	std::list <Passenger> temp;

	if (order_queue.empty()) {
		return;
	}
	
	for (std::list<Passenger>::iterator it = order_queue.begin(); it != order_queue.end(); it++) {
		if ((*it).get_pick_up().is_equal(curr_pos)) {
			curr_pass.push_back(*it);
			temp.push_back(*it);
			std::cout << "Update: Passenger picked up!" << std::endl;
		}
	}

	for (std::list<Passenger>::iterator it = temp.begin(); it != temp.end(); it++) {
		order_queue.remove(*it);
	}

	mission_planner();
}

// method that determines if any passenger needs to be dropped off
void Vehicle::is_dropoff() {

	std::list <Passenger> temp;

	if (curr_pass.empty()) {
		return;
	}

	for (std::list<Passenger>::iterator it = curr_pass.begin(); it != curr_pass.end(); it++) {
		if ((*it).get_drop_pt().is_equal(curr_pos)) {
			temp.push_back(*it);
			std::cout << "Update: Passenger dropped!" << std::endl;
		}
	}

	for (std::list<Passenger>::iterator it = temp.begin(); it != temp.end(); it++) {
		curr_pass.remove(*it);
	}

	mission_planner();
}

bool Vehicle::is_home() {

	// check if vehicle is already at home
	if (order_queue.empty() && curr_pass.empty() && curr_pos.is_equal(spawn_loc))
		return true;
	return false;

}

// method that accepts new orders and advances the vehicle based on the next target location
void Vehicle::move(std::vector<Passenger> &order_list) {

	std::cout << "Update: Pickup request received!" << std::endl;

	for (std::vector<Passenger>::iterator it = order_list.begin(); it != order_list.end(); ++it) {
		order_queue.push_back(*it);
	}

	mission_planner();

	if (curr_pos.is_equal(curr_target)) {
		is_pickup();
		is_dropoff();
		mission_planner();
		if (is_home()) {
			return;
		}
	}

	advance_step();

}

// overloaded method that advances the vehicle if no new orders are given
void Vehicle::move() {

	if (curr_pos.is_equal(curr_target)) {
		is_pickup();
		is_dropoff();
		if (is_home()) {
			return;
		}
		mission_planner();
	}
	advance_step();

}

// method to advance the vehicle by one step
void Vehicle::advance_step()
{
	reset_grid();
	show_veh();
	print_info();
	++time_step;
	std::pair<int, int> step = path_plan(curr_pos, curr_target);
	curr_pos.x += step.first;
	curr_pos.y += step.second;

}

/*
Method that governs the scheduling and routing decision. 
Scheduling decisions are based on a greedy approach. Passengers closest to the 
current vehicle location are picked up first to minimize their travel time.
This could however lead to some current passengers in the car having extended
journey times. Alternately, heuristic solutions which are variants of the 
Travelling Salesman Problem (TSP) / Vehicle Routing Problem (VRP) can also be used
*/
void Vehicle::mission_planner() {

	std::list<grid_pt> nodes;
	int min_pathcost = INT_MAX;
	grid_pt target_node;

	// if all passengers are dropped and there are no more orders, then return home
	if (order_queue.empty() && curr_pass.empty() && curr_pos.is_equal(curr_target)) {
		curr_target = spawn_loc;
		std::cout << "Update: Time to get back home..." << std::endl;
		while (!curr_pos.is_equal(curr_target)) {
			advance_step();
		}
		advance_step();
		std::cout << "Update: Trip complete. Reached home!!!" << std::endl;
		return;
	}
	
	// adding all pickup points of new orders
	if (!order_queue.empty())
	{
		for (std::list<Passenger>::iterator it = order_queue.begin(); it != order_queue.end(); ++it) {
			nodes.push_back((*it).get_pick_up());
		}
	}

	// adding all drop points of existing passengers
	if (!curr_pass.empty())
	{
		for (std::list<Passenger>::iterator it = curr_pass.begin(); it != curr_pass.end(); ++it) {
			nodes.push_back((*it).get_drop_pt());
		}
	}

	// finding closest point to the current vehicle location
	for (grid_pt &node : nodes) {
		if (path_cost(curr_pos, node) < min_pathcost) {
			min_pathcost = path_cost(curr_pos, node);
			target_node = node;
		}
	}

	// setting the target node
	curr_target = target_node;

}
