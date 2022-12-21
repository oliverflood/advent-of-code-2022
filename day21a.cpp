#include <bits/stdc++.h>
#include "cpplite.h"

using namespace std;

#define ll long long
#define hash unordered_map

/*
g++ day21a.cpp cpplite.cpp -o day21a.exe -std=c++1z
*/

string trim_for_num(const string &s) {
	return trim(s, "abcdefghijklmnopqrstuvwxyz :\n");
}

// ok ok in my defense this is not production code
hash<string, ll> table;
hash<string, bool> visited;
hash<string, vector<string>> info;

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

	cout << calculate("root") << endl;

}
