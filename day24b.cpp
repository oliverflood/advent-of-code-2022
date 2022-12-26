#include <bits/stdc++.h>
#include "cpplite.h"

using namespace std;

/*
g++ day24b.cpp cpplite.cpp -o day24b.exe -std=c++1z
*/

int TRUE_HEIGHT;
int TRUE_WIDTH;
int HEIGHT;
int WIDTH;

// grid stores flood fill info (also visited with -1 not visited)
// blocked stores blocked info, including walls and blizzards

vector<vector<vector<int>>> grid;
vector<vector<vector<bool>>> blocked;

struct blizzard {
	int x;
	int y;
	int x_dir;
	int y_dir;
};

vector<blizzard> blizzards;




int modulo(int n, int modulus) {
	return ((n % modulus) + modulus) % modulus;
}


vector<vector<int>> new_grid() {
	vector<vector<int>> ans;
	for (int i = 0; i < TRUE_HEIGHT; ++i)
	{
		vector<int> temp(TRUE_WIDTH, -1);
		ans.push_back(temp);
	}
	return ans;
}

vector<vector<bool>> new_blocked() {
	vector<vector<bool>> ans;

	for (int i = 0; i < TRUE_HEIGHT; ++i)
	{
		vector<bool> row;
		// top
		if (i == 0) {
			vector<bool> temp(TRUE_WIDTH, true);
			temp[1] = false;
			row = temp;
		}
		// bottom
		else if (i == TRUE_HEIGHT-1) {
			vector<bool> temp(TRUE_WIDTH, true);
			temp[TRUE_WIDTH-2] = false;
			row = temp;
		}
		// middle stuff
		else {
			vector<bool> temp(TRUE_WIDTH, false);
			row = temp;
		}

		row[0] = true;
		row[TRUE_WIDTH-1] = true;
		

		ans.push_back(row);
	}

	assert(ans.size() == TRUE_HEIGHT);
	assert(ans[0].size() == TRUE_WIDTH);
	return ans;
}

vector<vector<bool>> blocked_at_time(int time) {

	vector<vector<bool>> blocked_instance = new_blocked();

	for (int i = 0; i < blizzards.size(); ++i)
	{
		blizzard b = blizzards[i];

		assert(1 + modulo(b.y + time*b.y_dir, HEIGHT) > 0);
		assert(1 + modulo(b.y + time*b.y_dir, HEIGHT) < TRUE_HEIGHT);
		assert(1 + modulo(b.x + time*b.x_dir, WIDTH) > 0);
		assert(1 + modulo(b.x + time*b.x_dir, WIDTH) < TRUE_WIDTH);

		blocked_instance[1 + modulo(b.y + time*b.y_dir, HEIGHT)][1 + modulo(b.x + time*b.x_dir, WIDTH)] = true;
	}

	return blocked_instance;
}

void print_blizzard(blizzard b) {
	cout << "blizzard: " << endl;
	cout << " pos: " << b.x << " " << b.y << endl;
	cout << " dir: " << b.x_dir << " " << b.y_dir << endl;
}

void print_b(vector<vector<bool>> v) {
	for (int i = 0; i < v.size(); ++i)
	{
		for (int k = 0; k < v[0].size(); ++k)
		{
			if (v[i][k])
				cout << "#";
			else
				cout << ".";
		}
		cout << endl;
	}
	cout << endl;
}

void blizzard_setup(vector<string> input) {
	TRUE_HEIGHT = input.size();
	TRUE_WIDTH = input[0].size();
	HEIGHT = input.size()-2;
	WIDTH = input[0].size()-2;

	// cout << WIDTH << " " << HEIGHT << endl;

	map<char, pair<int, int>> dirmap = {{'>', {1, 0}}, {'<', {-1, 0}}, {'^', {0, -1}}, {'v', {0, 1}}};

	for (int y = 1; y <= HEIGHT; ++y)
	{
		for (int x = 1; x <= WIDTH; ++x)
		{
			char current_char = input[y].at(x);
			if (dirmap.count(current_char)) {
				blizzard b;
				b.x = x-1;
				b.y = y-1;
				b.x_dir = dirmap[current_char].first;
				b.y_dir = dirmap[current_char].second;
				blizzards.push_back(b);
			}
		}
	}

	// cout << "num blizzards: " << blizzards.size() << endl;
	// for (int i = 0; i < blizzards.size(); ++i)
	// {
	// 	cout << i << endl;
	// 	print_blizzard(blizzards[i]);
	// }
}

bool within_bounds(int x, int y) {

	// check lower bounds
	if (x < 0 || y < 0)
		return false;

	// check upper bounds
	if (x >= TRUE_WIDTH || y >= TRUE_HEIGHT)
		return false;

	return true;
}


int index_exit(vector<vector<int>> g) {
	return g[TRUE_HEIGHT-1][TRUE_WIDTH-2];
}

int index_start(vector<vector<int>> g) {
	return g[0][1];
}

void print_grid_state(vector<vector<int>> g) {
	for (int y = 0; y < TRUE_HEIGHT; ++y)
	{
		for (int x = 0; x < TRUE_WIDTH; ++x)
		{
			if (g[y][x] == -1)
				cout << ".";
			else
				cout << g[y][x];
		}
		cout << endl;
	}
	cout << endl;
}


void flood_next(int index) {

	// add our next time state
	blocked.push_back(blocked_at_time(index));
	grid.push_back(new_grid());

	vector<pair<int, int>> increments = {{0, 0}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}};

	// "pour into" next time state
	for (int y = 0; y < TRUE_HEIGHT; ++y)
	{
		for (int x = 0; x < TRUE_WIDTH; ++x)
		{
			// ensure water at location
			if (grid[index][y][x] == -1)
				continue;

			// fill all possible next locations
			for (int i = 0; i < increments.size(); ++i)
			{
				int next_x = x + increments[i].first;
				int next_y = y + increments[i].second;

				// ensure within bounds
				if (!within_bounds(next_x, next_y))
					continue;

				// ensure not blocked
				if (blocked[index+1][next_y][next_x]) 
					continue;

				grid[index+1][next_y][next_x] = grid[index][y][x]+1;
			}
		}
	}
}



int main() {

	vector<string> input = slurp();
	blizzard_setup(input);

	blocked.push_back(blocked_at_time(0));
	grid.push_back(new_grid());
	grid[0][0][1] = 0;

	// print_grid_state(grid[0]);
	// print_b(blocked[0]);

	int index = 0;
	int ans = 0;

	// start to end
	while (index_exit(grid[index]) == -1) {
		//cout << "FLOODING " << index << endl;
		flood_next(index);
		index++;
		// print_grid_state(grid[index]);
		// print_b(blocked[index]);
	}
	ans += index_exit(grid[index]);

	// reset
	grid[index] = new_grid();
	grid[index][TRUE_HEIGHT-1][TRUE_WIDTH-2] = 0;

	// end to start
	while (index_start(grid[index]) == -1) {
		//cout << "FLOODING " << index << endl;
		flood_next(index);
		index++;
		// print_grid_state(grid[index]);
		// print_b(blocked[index]);
	}
	ans += index_start(grid[index]);

	// reset
	grid[index] = new_grid();
	grid[index][0][1] = 0;

	// start to end (again)
	while (index_exit(grid[index]) == -1) {
		//cout << "FLOODING " << index << endl;
		flood_next(index);
		index++;
		// print_grid_state(grid[index]);
		// print_b(blocked[index]);
	}
	ans += index_exit(grid[index]);

	// ans-1 because I start counting a bit early
	cout << "ans: " << (ans-1) << endl;
}