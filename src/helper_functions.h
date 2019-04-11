// =================================================================
// AUTHOR			: Rohith Krishnan
// CREATE DATE      : 01.23.2019
// PURPOSE			: Helper functions declarations to plan a path and
//					  to calculate cost of travelling to a location
// =================================================================
// Change History:
//
// =================================================================

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "json.hpp"
#include "Grid_pt.h"
#include "Passenger.h"
#include <iomanip>

using nlohmann::json;

// path plan
std::pair<int, int> path_plan(grid_pt &a, grid_pt &b);

// path cost
int path_cost(grid_pt &a, grid_pt &b);

void create_json();

void parse_json(std::vector<Passenger> &order_list, std::string &file_name);
