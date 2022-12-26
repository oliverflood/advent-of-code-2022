#include <bits/stdc++.h>
#include "cpplite.h"

using namespace std;

/*
g++ day23b.cpp cpplite.cpp -o day23b.exe -std=c++1z
*/

int FIELD_HEIGHT = 20;
int FIELD_WIDTH = 20;

vector<vector<int>> new_grid() {
	vector<vector<int>> field;

	for (int i = 0; i < FIELD_HEIGHT; ++i)
	{
		vector<int> temp(FIELD_WIDTH);
		field.push_back(temp);
	}

	return field;
}

vector<vector<bool>> new_field() {
	vector<vector<bool>> field;

	for (int i = 0; i < FIELD_HEIGHT; ++i)
	{
		vector<bool> temp(FIELD_WIDTH);
		field.push_back(temp);
	}

	return field;
}

vector<vector<bool>> prepare_grid(vector<string> input) {

	vector<vector<bool>> field;
	
	for (int i = 0; i < FIELD_HEIGHT; ++i)
	{
		vector<bool> temp(FIELD_WIDTH);
		field.push_back(temp);
	}

	int y_start = FIELD_HEIGHT/2-(input.size()/2);
	int x_start = FIELD_WIDTH/2-(input[0].size()/2);

	for (int y = 0; y < input.size(); ++y)
	{
		for (int x = 0; x < input[y].size(); ++x)
		{
			if (input[y][x] == '#')
				field[input.size()-1-y+y_start][x + x_start] = true;
		}
	}

	return field;
}

void print_field(vector<vector<bool>> field) {

	for (int y = field.size()-1; y >= 0; --y)
	{
		for (int x = 0; x < field[y].size(); ++x)
		{
			if (field[y][x])
				cout << "#";
			else
				cout << ".";
		}
		cout << endl;
	}
	cout << endl;
}

void print_grid(vector<vector<int>> field) {

	for (int y = field.size()-1; y >= 0; --y)
	{
		for (int x = 0; x < field[y].size(); ++x)
		{
			cout << field[y][x];
		}
		cout << endl;
	}
	cout << endl;
}

bool is_direction_good(vector<vector<bool>> field, int x, int y, pair<int, int> dir) {

	// // north/south
	// if (dir.first == 0) {
	// 	if (!field[y+dir.second][x-1] && !field[y+dir.second][x] && !field[y+dir.second][x+1]) {
	// 		return true;
	// 	}
	// }
	// // west/east
	// else {
	// 	if (!field[y+1][x+dir.first] && !field[y][x+dir.first] && !field[y-1][x+dir.first]) {
	// 		return true;
	// 	}
	// }

	vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

	// north
	if (dir == directions[0])
	if (!field[y+1][x-1] && !field[y+1][x] && !field[y+1][x+1]) {
		return true;
	}

	// south
	if (dir == directions[1])
	if (!field[y-1][x-1] && !field[y-1][x] && !field[y-1][x+1]) {
		return true;
	}

	// west
	if (dir == directions[2])
	if (!field[y+1][x-1] && !field[y][x-1] && !field[y-1][x-1]) {
		return true;
	}

	// east
	if (dir == directions[3])
	if (!field[y+1][x+1] && !field[y][x+1] && !field[y-1][x+1]) {
		return true;
	}

	return false;
}

void add_proposal(vector<vector<bool>> field, vector<vector<int>> &proposal_grid, int x, int y, int index, vector<vector<int>> &direction_indicator) {
	//                                  north     south     west     east
	vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

	for (int i = 0; i < 4; ++i)
	{
		//cout << ((index+i) % 4) << endl;
		pair<int, int> dir = directions[(index+i) % 4];
		if (is_direction_good(field, x, y, dir)) {
			proposal_grid[y + dir.second][x + dir.first]++;

			direction_indicator[y][x] = ((index+i)%4)+1; // stupid
			return;
		}
	}

	//stationary_elves[y][x] = true;
}

bool elf_in_proximity(vector<vector<bool>> field, int x, int y) {

	for (int i = -1; i <= 1; ++i)
	{
		for (int k = -1; k <= 1; ++k)
		{
			if (i == 0 && k == 0)
				continue;

			if (field[y+k][x+i])
				return true;
		}
	}

	return false;
}

void do_round(vector<vector<bool>> &field, int index) {

	vector<vector<int>> proposal_grid = new_grid();

	//vector<vector<bool>> slaughter_proposers = new_field();
	vector<vector<int>> direction_indicator = new_grid();

	// add all proposals
	for (int y = 0; y < field.size(); ++y)
	{
		for (int x = 0; x < field[0].size(); ++x)
		{
			if (field[y][x] && elf_in_proximity(field, x, y)) {
				add_proposal(field, proposal_grid, x, y, index, direction_indicator);
			}
		}
	}

	//print_grid(proposal_grid);

	// look at all proposals
	for (int y = 0; y < proposal_grid.size(); ++y)
	{
		for (int x = 0; x < proposal_grid[0].size(); ++x)
		{
			if (proposal_grid[y][x] == 1) {

				// spaghetti code >:|

				// north
				if (direction_indicator[y+1][x] == 2)
					field[y+1][x] = false;

				// south
				if (direction_indicator[y-1][x] == 1)
					field[y-1][x] = false;

				// west
				if (direction_indicator[y][x-1] == 4)
					field[y][x-1] = false;

				// east
				if (direction_indicator[y][x+1] == 3)
					field[y][x+1] = false;

			}
		}
	}
	

	// place elves who made one proposal where they should be
	for (int y = 0; y < proposal_grid.size(); ++y)
	{
		for (int x = 0; x < proposal_grid[0].size(); ++x)
		{
			if (proposal_grid[y][x] == 1) {
				field[y][x] = true;
			}
		}
	}
}

int count_elves(vector<vector<bool>> field) {
	int ans = 0;
	for (int y = field.size()-1; y >= 0; --y)
	{
		for (int x = 0; x < field[y].size(); ++x)
		{
			if (field[y][x])
				ans++;
		}
	}
	return ans;
}

int score(vector<vector<bool>> field) {
	int y_min = FIELD_HEIGHT+100;
	int y_max = 0;
	int x_min = FIELD_WIDTH+100;
	int x_max = 0;

	for (int y = field.size()-1; y >= 0; --y)
	{
		for (int x = 0; x < field[y].size(); ++x)
		{
			if (field[y][x]) {
				if (y > y_max)
					y_max = y;
				if (y < y_min)
					y_min = y;
				if (x > x_max)
					x_max = x;
				if (x < x_min)
					x_min = x;
			}
		}
	}

	return (y_max-y_min+1)*(x_max-x_min+1)-count_elves(field);
}

int main() {
	vector<string> input = slurp();
	FIELD_HEIGHT = input.size()+600;
	FIELD_WIDTH = input[0].size()+600;
	vector<vector<bool>> field = prepare_grid(input);
	
	//print_field(field);
	// int num_elves = count_elves(field);
	// cout << num_elves << endl;


	/*
	This is stupidly slow
	I hate this 
	Have to fix this asap


	*/


	for (int i = 0; i < 1000; ++i){
		vector<vector<bool>> prev_field = field;
		do_round(field, i);
		if (field == prev_field) {
			cout << "ans: " << (i+1) << endl;
			break;
		}
		cout << "ROUND " << (i+1) << endl;
	}	
	print_field(field);

}
