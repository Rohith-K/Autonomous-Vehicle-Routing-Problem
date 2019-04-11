// =================================================================
// AUTHOR			: Rohith Krishnan
// CREATE DATE      : 01.23.2019
// PURPOSE			: Main driver file
// =================================================================
// Change History:
//
// =================================================================


#include "Vehicle.h"
#include "helper_functions.h"


int main() {

	int grid_x, grid_y;
	int veh_x, veh_y;

	std::cout << "Enter the number of lanes in the city (Total X, Total Y): \n";
	std::cin >> grid_x >> grid_y;

	std::cout << "\nEnter the vehicle spawn location in the city (x,y): \n";
	std::cin >> veh_x >> veh_y;

	if (veh_x >= grid_x || veh_y >= grid_y) {
		std::cout << "Invalid input parameters. Program terminating...";
		std::cin.ignore();
		std::cin.get();
		return 0;
	}
	
	grid_pt V(veh_x, veh_y);
	Vehicle my_car(V, grid_x, grid_y);
	
	

	//--------------------DATA PARSING-----------------

	/*
	uncomment to write a new json test input
	change details in create_json() in helper_functions.cpp to edit 
	passenger details
	*/
	create_json();
	
	std::vector<Passenger> order_list;
	std::string file_name = "test_ip1.json";
	parse_json(order_list, file_name);	

	//-------------------------------------------------


	my_car.move(order_list);

	for(int i=0; i<10; ++i)
		my_car.move();
	
	return 0;
}