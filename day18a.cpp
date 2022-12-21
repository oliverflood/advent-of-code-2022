#include <bits/stdc++.h>
#include "cpplite.h"

using namespace std;

/*
g++ day18a.cpp cpplite.cpp -o day18a.exe -std=c++1z
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

int main() {

	vector<string> input = slurp();
	map<vector<int>, bool> grid;

	for (int i = 0; i < input.size(); ++i)
	{
		//print(split(input[i], ","), " ");
		vector<int> coords = vtoi(split(input[i], ","));
		grid[coords] = true;
	}

	int ans = 0;

	// this shouldnt take as long as it does
	// maybe map is slow-> unordered map???

	for (int i = -1; i <= RANGE; ++i) {
		for (int j = -1; j <= RANGE; ++j) {
			for (int k = -1; k <= RANGE; ++k) {
				if (!grid[vector<int>{i, j, k}])
					ans += count_sides(grid, vector<int>{i, j, k});
			}
		}
	}

	cout << "ans: " << ans << endl;
}
