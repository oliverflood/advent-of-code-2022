#include <bits/stdc++.h>
#include "cpplite.h"

using namespace std;

/*
g++ day16b.cpp cpplite.cpp -o day16b.exe
*/
// last char not working???

// 30 mins total

// final answer
int ans = 0;
//             <pressure, rate>
// map<string, pair<pair<int, int>, int>> current_top; // cut off any connections at a node that are slower and lower


// IDEAS:
// per minute per pipe ~30*35 different paths
// go minute by minute advancing 35 paths
// ASSUMPTION:
// fastest path in the same place at same time will always be better than any other same place same time


// TAKES A MINUTE TO RUN BUT I DID PART 1!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


      // place   time  pressure
map<pair<pair<string, string>, int>, int> best;

int total = 0;


struct path_info {
	int pressure;
	int rate;
	map<string, bool> opened;
	string debug;
	bool active;
};

void search(map<string, vector<string>> connections, map<string, int> flow_rates, vector<string> valves, string curr_valve, int mins, int pressure, int rate, map<string, bool> opened, string debug, string curr_valve2) {
	debug += to_string(mins);
	debug += " " + curr_valve + "   rate: " + to_string(rate) + "\n";

	

	// // check if smaller than current top
	// if (current_top[curr_valve].first.first > pressure && current_top[curr_valve].first.second > rate && current_top[curr_valve].second <= mins_left) {
	// 	return;
	// }

	// // update current top
	// current_top[curr_valve].first.first = pressure;
	// current_top[curr_valve].first.second = rate;

	

	// === real stuff ===

	// update pressure
	pressure += rate;

	// kill slow paths
	if ((26-mins)*total + pressure < ans) {
		return;
	}

	// check/update best
	if (best[{{curr_valve, curr_valve2}, mins}] > pressure)
		return;
	best[{{curr_valve, curr_valve2}, mins}] = pressure;


	// check if out of time
	if (mins+1 > 26) {
		if (pressure > ans) {
			ans = pressure;
		
			cout << "finished with: " << pressure << endl;
			cout << debug << endl;
			// for(const auto& elem : opened)
			// {
			//    std::cout << " > " << elem.first << " " << elem.second << "\n";
			// }
			cout << endl << endl;
		}  // moved logging into here
		return;
	}


	// NOT NEEDED
	// stop path if we're staying twice at same valve (don't know if needed / works as intended)
	// if (opened[curr_valve] == true)
	// 	return;

	bool beans = false; // this is stupid

	// open current pipe
	if (opened[curr_valve] == false && flow_rates[curr_valve] > 0) {
		debug += "^^^ opened \n"; // potentially unreliable
		opened[curr_valve] = true;
		beans = true;
		// rate += flow_rates[curr_valve];  // added into search below
		// for elephant stays
		for (int i = 0; i < connections[curr_valve].size(); ++i)
		{
			search(connections, flow_rates, valves, connections[curr_valve][i], mins+1, pressure, rate + flow_rates[curr_valve], opened, debug, curr_valve2);   // call search
		}
		// for me stay
		//search(connections, flow_rates, valves, curr_valve, mins+1, pressure, rate + flow_rates[curr_valve], opened, debug, curr_valve2);                   // call search
		for (int i = 0; i < connections[curr_valve2].size(); ++i)
		{
			search(connections, flow_rates, valves, curr_valve, mins+1, pressure, rate + flow_rates[curr_valve], opened, debug, connections[curr_valve2][i]);   // call search
		}
	}

	if (beans)
		opened[curr_valve] = false;

	// go to next pipes
	for (int i = 0; i < connections[curr_valve].size(); ++i)
	{
		for (int k = 0; k < connections[curr_valve2].size(); ++k)
			search(connections, flow_rates, valves, connections[curr_valve][i], mins+1, pressure, rate, opened, debug, connections[curr_valve2][k]);   // call search
	}
}






int main() {

	vector<string> input = slurp_lines();
	
	map<string, int> flow_rates;
	map<string, vector<string>> connections;
	vector<string> valves;
	vector<string> important_valves;
	map<string, bool> opened; // empty for now

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
		if (rate > 0)
			important_valves.push_back(valve);

		// get connections
		for (int k = 9; k < split_input.size(); ++k)
		{
			connections[valve].push_back(trim(split_input[k], " ,"));
		}
	}

	for (int i = 0; i < valves.size(); ++i){
		cout << valves[i] << ":  ";
		print(connections[valves[i]], " ");
	}


	// start search
	search(connections, flow_rates, valves, "AA", 1, 0, 0, opened, "", "AA");                                            // call search

	cout << "total: " << total << endl << endl;
	//cout << "expect: 1651" << endl;
	cout << "ans: " << ans << endl;



/*

// idea: adjacency matrix storing distances (to get rid of 0 pipes)

// brute force adjacency matrix or do parallel paths

start with <pos1, pos2, 0, path_info_struct>

*/

	// cout << "NEW: " << endl;
	// map<pair<string, string>, path_info> paths;

	// path_info first_path;
	// first_path.active = true;
	// paths[{"AA", "AA"}] = first_path;

	// // for(const auto& pair : paths) {
	// // 	cout << pair.second.active << endl;
	// // }

	// for (int i = 0; i < 30; ++i)
	// {
	// 	map<pair<string, string>, path_info> new_paths = paths;
	// 	for(const auto& pair : paths)
	// 	{
	// 		// ignore non active paths
	// 		if (!pair.second.active) 
	// 			continue;


	// 	}
	// }

}
