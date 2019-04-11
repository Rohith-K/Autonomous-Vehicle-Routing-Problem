// =================================================================
// AUTHOR			: Rohith Krishnan
// CREATE DATE      : 01.23.2019
// PURPOSE			: Passenger Class header file to store the
//					  details of the passengers
// =================================================================
// Change History:
//
// =================================================================


#pragma once

#include "Grid_pt.h"
#include <string>


class Passenger {

	grid_pt start;	// start point on the grid
	grid_pt end;	// drop point on the grid	

public:

	std::string name;	

	// overload '==' operator so that remove method can be used for the list container in STL
	bool operator == (const Passenger& p) {
		return (name == p.name) && (start.is_equal(p.start)) && (end.is_equal(p.end));
	}

	// function to determine of passenger has been picked up
	//bool is_picked_up;

	// Constructor
	Passenger(std::string name, grid_pt start,
		grid_pt end){
		//this->is_picked_up = false;
		this->name = name;
		this->start = start;
		this->end = end;
	};

	// print passenger details
	void passenger_details() {
		std::cout << "Name: " << this->name << std::endl;
		this->start.print_pos();
		this->end.print_pos();
	}

	// return pick-up point 
	grid_pt get_pick_up() {
		return start;
	}

	// return drop-off point
	grid_pt get_drop_pt() {
		return end;
	}

};
