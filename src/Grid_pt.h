// =================================================================
// AUTHOR			: Rohith Krishnan
// CREATE DATE      : 01.23.2019
// PURPOSE			: Structure implemented to describe a datatype 
//					  that can store a grid-point
// =================================================================
// Change History:
//
// =================================================================

#pragma once

#include <iostream>

struct grid_pt {

	int x;
	int y;

	// Constructor
	grid_pt(int x_in = INT_MAX, int y_in = INT_MAX)
		:x(x_in), y(y_in) {};

	// Print grid position
	void print_pos() {
		std::cout << "(" << this->x << ", " << this->y << ")" << std::endl;
	}

	// Compare two grid points if they are equal
	bool is_equal(grid_pt inp) {
		if (this->x == inp.x && this->y == inp.y)
			return true;
		return false;
	}

};
