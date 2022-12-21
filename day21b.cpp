#include <bits/stdc++.h>
#include "cpplite.h"

using namespace std;

#define ll long long
#define hash unordered_map

/*
g++ day21b.cpp cpplite.cpp -o day21b.exe -std=c++1z
*/

// handy function for trimming for a number
string trim_for_num(const string &s) {
	return trim(s, "abcdefghijklmnopqrstuvwxyz :\n");
}


// ok ok in my defense this is not production code
hash<string, ll> table;
hash<string, bool> visited;
hash<string, vector<string>> info;
ll invariant;


// calculate monkeys value based on name
ll calculate(string key) {

	// case where we know the value
	if (visited[key])
		return table[key];

	// cases where we don't know value yet
	visited[key] = true;

	//print(info[key], " ");

	if (info[key][1] == "+") 
		return (calculate(info[key][0]) + calculate(info[key][2]));
	
	if (info[key][1] == "-") 
		return (calculate(info[key][0]) - calculate(info[key][2]));
	
	if (info[key][1] == "*") 
		return (calculate(info[key][0]) * calculate(info[key][2]));
	
	if (info[key][1] == "/") 
		return (calculate(info[key][0]) / calculate(info[key][2]));
}


// test whether monkey depends on value of humn
bool has_humn(string key) {

	// base cases
	if (key == "humn")
		return true;

	if (visited[key]) {
		return false;
	}

	// recurse otherwise
	return (has_humn(info[key][0]) || has_humn(info[key][2]));
}


/* these two humn functions handle all the annoying cases */

// humn $ some = invariant
ll humn_left(ll invariant, ll right, string op) {

	if (op == "+") 
		return (invariant - right);

	if (op == "-") 
		return (invariant + right);

	if (op == "*") 
		return (invariant / right);

	if (op == "/") 
		return (invariant * right);
}
// left $ humn = invariant
ll humn_right(ll invariant, ll left, string op) {

	if (op == "+") 
		return (invariant - left);

	if (op == "-") 
		return (-(invariant - left));

	if (op == "*") 
		return (invariant / left);

	if (op == "/") 
		return (left / invariant);
}


// traverse through tree doing reverse operations to solve for humn
void traverse(string key) {
	if (key == "humn")
		return;

	// case humn on left
	if (has_humn(info[key][0])) {
		// cout << "humn left: " << endl;
		// print(info[key], " ");

		// do opposite operation
		invariant = humn_left(invariant, calculate(info[key][2]), info[key][1]);

		// continue traversing to humn
		traverse(info[key][0]);
	}

	// case humn on right
	if (has_humn(info[key][2])) {
		// cout << "humn right: " << endl;
		// print(info[key], " ");

		// do opposite operation
		invariant = humn_right(invariant, calculate(info[key][0]), info[key][1]);

		// continue traversing to humn
		traverse(info[key][2]);
	}
}



int main() {

	vector<string> input = slurp_lines();

	// input processing
	for (int i = 0; i < input.size(); ++i)
	{
		string key = input[i].substr(0, 4);

		// assign lone number monkeys
		if (isdigit(input[i].at(6))) {
			table[key] = stoll(trim_for_num(input[i]));
			visited[key] = true;
			continue;
		}

		// otherwise get info about the operation
		info[key] = vector<string>{input[i].substr(6, 4), input[i].substr(11, 1), input[i].substr(13, 4)};
	}



	// by chance this is true for both inputs
	invariant = calculate(info["root"][2]);

	assert(!has_humn(info["root"][2]));  // as proof :P



	// do the opposite operations of the (last to first) operations done on humn to invariant
	traverse(info["root"][0]);

	cout << "ans: " << invariant << endl;

}
