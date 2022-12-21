#include <bits/stdc++.h>
#include "cpplite.h"

using namespace std;

/*
g++ day18b.cpp cpplite.cpp -o day18b.exe -std=c++1z
*/

// check from -1 to 22

int count_sides(map<vector<int>, bool> grid, vector<int> coords) {
	int sides = 0;

	for (int i = 0; i <= 2; ++i) {
		vector<int> coords2 = coords;

		coords2[i]++;
		if (grid[vector<int>{coords2[0], coords2[1], coords2[2]}]){
			//cout << (coords2[0]) << " " << (coords2[1]) << " " << (coords2[2]) << endl;
			sides++;
		}

		coords2[i]-=2;
		if (grid[vector<int>{coords2[0], coords2[1], coords2[2]}]){
			//cout << (coords2[0]) << " " << (coords2[1]) << " " << (coords2[2]) << endl;
			sides++;
		}
	}
	return sides;
}

const int RANGE = 22;
int ans = 0; // ik ik global variables very dissapointing
			 // it is late and i am lazyyyyy


void flood_fill(map<vector<int>, bool> grid, map<vector<int>, bool> &visited, vector<int> coords) {

	visited[coords] = true;

	if (!grid[coords])
		ans += count_sides(grid, coords);

	// cycling through adjacent neighbors
	for (int i = 0; i <= 2; ++i) {
		vector<int> temp = coords;

		temp[i]++;
		if (temp[i] <= RANGE && !visited[temp] && !grid[temp]){
			flood_fill(grid, visited, temp);
		}

		temp[i]-=2;
		if (temp[i] >= -1 && !visited[temp] && !grid[temp]){
			flood_fill(grid, visited, temp);
		}
	}
}



int main() {

	vector<string> input = slurp();
	map<vector<int>, bool> grid;
	map<vector<int>, bool> visited;

	for (int i = 0; i < input.size(); ++i)
	{
		//print(split(input[i], ","), " ");
		vector<int> coords = vtoi(split(input[i], ","));
		grid[coords] = true;
	}

	// im sure theres a better way to do this but i mean this works

	flood_fill(grid, visited, vector<int>{-1, -1, -1});

	cout << "ans: " << ans << endl;
}
