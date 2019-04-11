// =================================================================
// AUTHOR			: Rohith Krishnan
// CREATE DATE      : 01.23.2019
// PURPOSE			: Helper functions definition
// =================================================================
// Change History:
//
// =================================================================


#include "helper_functions.h"


// structure to help create passenger details for the input json file
struct Pass_parse
{

	std::string name;
	std::list<int> start;
	std::list<int> end;
	Pass_parse(std::string name, std::list<int> start, std::list<int> end) :
		name(name), start(start), end(end) {};

};

// implemented to parse data with the json library
void to_json(json& j, const Pass_parse& r) {
	j = json{
		{"name", r.name},
		{"start", r.start},
		{"end", r.end}
	};
}

// helper method to create order requests into a 
// json file stored in the working directory
void create_json() {

	std::list<int> st1{ 1,1 };
	std::list<int> ed1{ 2,2 };

	std::list<int> st2{ 1,3 };
	std::list<int> ed2{ 0,3 };

	Pass_parse rm1("Elon", st1, ed1);
	Pass_parse rm2("George", st2, ed2);

	json j;
	j["requests"] = json::array();
	j["requests"].push_back(rm1);
	j["requests"].push_back(rm2);

	std::cout << j.dump(4) << std::endl;

	std::ofstream file("test_ip1.json");
	file << std::setw(4) << j << std::endl;
	std::cout << std::endl;

}

// method to parse order requests from existing json files
void parse_json(std::vector<Passenger> &order_list, std::string &file_name) {

	std::ifstream i(file_name);
	std::cout << "Data parsed from json file:" << std::endl;
	json j_i = json::parse(i);

	std::cout << j_i << std::endl;

	std::string name;
	std::list<int> start;
	std::list<int> end;

	for (auto& pass : j_i["requests"]) {

		name = pass.at("name").get<std::string>();
		start = pass.at("start").get<std::list<int>>();
		end = pass.at("end").get<std::list<int>>();
		grid_pt st1(start.front(), start.back());
		grid_pt end1(end.front(), end.back());
		Passenger P(name, st1, end1);
		order_list.push_back(P);
	}
	std::cout << std::endl;

}


// method that plans the path based on the current and target locations
// on the grid map. Alternately Breadth_First Search (BFS) can be used as well

std::pair<int, int> path_plan(grid_pt &a, grid_pt &b) {

	std::pair<int, int> next_step;

	if (a.x - b.x > 0) {
		next_step.first = -1;
		next_step.second = 0;
		return next_step;
	}

	else if (a.x - b.x < 0) {
		next_step.first = 1;
		next_step.second = 0;
		return next_step;
	}

	else if (a.y - b.y > 0) {
		next_step.first = 0;
		next_step.second = -1;
		return next_step;
	}

	else if (a.y - b.y < 0) {
		next_step.first = 0;
		next_step.second = 1;
		return next_step;
	}

	else if ((a.x - b.x == 0) && (a.y - b.y == 0)) {
		next_step.first = 0;
		next_step.second = 0;
		return next_step;
	}
}

// method that calculates the cost of travelling to any location on
// the grid map. Since the grid is of uniform cost, manhattan distance is used. 
int path_cost(grid_pt &a, grid_pt &b) {
	return (abs(a.x - b.x) + abs(a.y - b.y));
}
