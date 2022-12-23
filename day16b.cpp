#include <bits/stdc++.h>
#include "cpplite.h"

using namespace std;

//#define hash unordered_map;

/*
g++ day16b.cpp cpplite.cpp -o day16b.exe -std=c++1z
*/

// info on valves
int total = 0;
map<string, int> flow_rates;
map<string, vector<string>> connections;
vector<string> valves;


struct path_info {
	map<string, bool> opened;
	int pressure;
	int rate;
	string debug;
	int minutes;
};

struct posrate {
	pair<string, string> pos;
	int rate;
};

// current best path given positions of human and elephant
map<pair<pair<string, string>, int>, path_info> best_path;
map<pair<string, string>, bool> visited;
map<pair<string, string>, pair<int, int>> best_rate_pressure;

// minutes shouldn't matter, will update all paths at same time

// (passing in rate is redundant)
void add_into_map(map<pair<pair<string, string>, int>, path_info> &path_map, path_info path, pair<string, string> position, int rate) {
	
	pair<pair<string, string>, int> info = {position, rate};
	// info.pos = position;
	// info.rate = rate;


	if (best_rate_pressure[position].first <= rate) {
		best_rate_pressure[position] = {rate, path.pressure};
	}
	else {
		if (best_rate_pressure[position].second > path.pressure) {
			return;
		}
	}

	visited[position] = true; // <-- wish i didn't have to do this

	

	// keep whatever has more rate
	if (path_map[info].rate < path.rate) {
		path_map[info] = path;
	}
	// if rate is same keep with higher pressure
	if (path_map[info].rate == path.rate) {
		if (path_map[info].pressure <= path.pressure) {
			path_map[info] = path;
		}
	}
}



void update_paths(int mins) {

	map<pair<pair<string, string>, int>, path_info> new_best_path = best_path;


	for (auto & [info, path] : best_path)
	// for (int a = 0; a < valves.size(); ++a) 
	// {
	// for (int b = 0; b < valves.size(); ++b)
	{
		//path_info path = best_path[{valves[a], valves[b]}];
		pair<string, string> position = info.first;
		/* POSRATE */


		if (!visited[{position}]) // <-- wish i didn't have to do this
			continue;

		// testing random
		if (path.minutes != mins) {
			continue;
		}
		path.minutes++;


		// path rate stuff
		path.pressure += path.rate;


		// debugging stuff
		path.debug += "mins: " + to_string(mins) + "  ";
		path.debug += "1: " + position.first + "  2: " + position.second + "  pressure: " + to_string(path.pressure) + "  rate: " + to_string(path.rate) + "\n";

		// nobody opens
			// check all paths
		for (int i = 0; i < connections[position.first].size(); ++i)
		{
			for (int k = 0; k < connections[position.second].size(); ++k) {
				add_into_map(new_best_path, path, {connections[position.first][i], connections[position.second][k]}, path.rate);
			}
		}



		// only human opens current
			// check all paths
		if (!path.opened[position.first]) {
		if (flow_rates[position.first] > 0) {

			path_info human_stays = path;
			human_stays.opened[position.first] = true;
			human_stays.rate += flow_rates[position.first];

			for (int k = 0; k < connections[position.second].size(); ++k)
			{
				add_into_map(new_best_path, human_stays, {position.first, connections[position.second][k]}, human_stays.rate);
			}
		}
		}


		// only elephant opens current
			// check all paths
		if (!path.opened[position.second]) {
		if (flow_rates[position.second] > 0) {

			path_info elephant_stays = path;
			elephant_stays.opened[position.second] = true;
			elephant_stays.rate += flow_rates[position.second];

			for (int i = 0; i < connections[position.first].size(); ++i)
			{
				add_into_map(new_best_path, elephant_stays, {connections[position.first][i], position.second}, elephant_stays.rate);
			}
		}
		}


		// both open current
			// check all paths
		if (!path.opened[position.first] && !path.opened[position.second]) {
		if (flow_rates[position.first] > 0 && flow_rates[position.second] > 0 && position.first != position.second) {
			path_info both_stay = path;

			both_stay.opened[position.first] = true;
			both_stay.opened[position.second] = true;

			both_stay.rate += flow_rates[position.first];
			both_stay.rate += flow_rates[position.second];

			add_into_map(new_best_path, both_stay, {position.first, position.second}, both_stay.rate);
		}
		}
	}
	//}


	// update best paths (AFTER looping through them...)
	best_path = new_best_path;
}


int main() {

	vector<string> input = slurp_lines();

	// input processing
	for (int i = 0; i < input.size(); ++i)
	{
		vector<string> split_input = split(input[i], " ");

		// get valves
		string valve = split_input[1];
		valves.push_back(valve);

		// get flow rates
		int rate = stoi(trim(split_input[4], "rate=;"));
		flow_rates[valve] = rate;

		// add flow rates to total
		total += rate;

		// add to important valves
		// if (rate > 0)
		// 	important_valves.push_back(valve);

		// get connections
		for (int k = 9; k < split_input.size(); ++k)
		{
			connections[valve].push_back(trim(split_input[k], " ,\n\r\t\f\v"));
		}
	}

	for (int i = 0; i < valves.size(); ++i){
		cout << valves[i] << ":  ";
		print(connections[valves[i]], "/");
	}


	// initial path
	path_info starter;
	// starter.valve1 = "AA";
	// starter.valve2 = "AA";
	starter.pressure = 0;
	starter.rate = 0;
	starter.debug = "";
	starter.minutes = 1;

	pair<pair<string, string>, int> starter_info = {{"AA", "AA"}, 0};
	// starter_info.pos = {"AA", "AA"};
	// starter_info.rate = 0;

	best_path[starter_info] = starter;

	

	// ** assuming that best path is highest rate



	for (int a = 0; a < valves.size(); ++a) {
		for (int b = 0; b < valves.size(); ++b) {
			visited[{valves[a], valves[b]}] = false;
		}
	}
	visited[{"AA", "AA"}] = true;





	const int NUM_MINS = 26;
	
	// updating paths for each min
	for (int mins = 1; mins <= NUM_MINS; ++mins)
	{
		cout << "mins: " << mins << "    " << best_path.size() << endl;
		update_paths(mins);
	}

	// find and print largest pressure of all paths
	int largest_pressure = 0;

	// for (int a = 0; a < valves.size(); ++a) 
	// {
	// 	for (int b = 0; b < valves.size(); ++b)
	// 	{
	// 		//cout << "\n\n\n\n\n\ndebug:\n\n" << best_path[{valves[a], valves[b]}].debug << endl;

	// 		if (best_path[{valves[a], valves[b]}].pressure > largest_pressure){
	// 			largest_pressure = best_path[{valves[a], valves[b]}].pressure;
	// 			cout << "\n\n\n\n\n\ndebug:\n\n" << best_path[{valves[a], valves[b]}].debug << endl;
	// 		}
	// 	}
	// }

	for (auto & [info, path] : best_path) {

		if (best_path[info].pressure > largest_pressure){
			largest_pressure = best_path[info].pressure;
			cout << "\n\n\n\n\n\ndebug:\n\n" << best_path[info].debug << endl;
		}
	}

	cout << "ans: " << largest_pressure << endl;

	//1938 too low
	//2000 not right
}
