#include <bits/stdc++.h>
#include "cpplite.h"

using namespace std;

/*
g++ day22b.cpp cpplite.cpp -o day22b.exe -std=c++1z
*/

// global variables lol
const int BOARD_SIZE = 4;
int BOARD_WIDTH = 0;
int BOARD_HEIGHT = 0;

struct cube {
	vector<vector<int>> front;
	vector<vector<int>> back;
	vector<vector<int>> left;
	vector<vector<int>> right;
	vector<vector<int>> top;
	vector<vector<int>> bottom;
};
map<pair<int, int>, vector<vector<int>>> boards;
vector<vector<int>> board;
cube the_cube;

vector<vector<int>> board_setup(vector<string> &input);
vector<pair<int, int>> instructions_setup(string info);
pair<int, int> get_starting_pos();
pair<int, int> pair_sum(pair<int, int> a, pair<int, int> b);
pair<int, int> raycast(pair<int, int> current_pos, pair<int, int> raycast_dir);
pair<int, int> next_step(pair<int, int> current_pos, pair<int, int> current_dir);
void print_board();
void print_instructions(vector<pair<int, int>> instructions);
void execute_instruction(pair<int, int> instruction, pair<int, int> &current_pos, pair<int, int> &current_dir);
int modulo(int n, int modulus);
bool within_bounds(pair<int, int> pos);
void print_pair(pair<int, int> p);
int calculate_score(pair<int, int> current_pos, pair<int, int> current_dir);
void execute_all_instructions(vector<pair<int, int>> instruction, pair<int, int> &current_pos, pair<int, int> &current_dir);
void cube_setup(vector<vector<int>> super_board);


int main() {

	// prepare board and instructions
	vector<string> input = slurp_lines();
	vector<pair<int, int>> instructions = instructions_setup(input[input.size()-1]);
	vector<vector<int>> super_board = board_setup(input);

	cube_setup(super_board);
}

void cube_setup(vector<vector<int>> super_board) {
	for (int Y = 0; Y < BOARD_HEIGHT/BOARD_SIZE; ++Y)
	{
		for (int X = 0; X < BOARD_WIDTH/BOARD_SIZE; ++X)
		{
			
		}
	}
}

vector<vector<int>> board_setup(vector<string> &input) {
	vector<vector<int>> board;

	// trim annoying whitespace off input
	for (int i = 0; i < input.size(); ++i)
	{
		input[i] = trim(input[i], "\n\r\t\f\v");
	}

	// get board width
	for (int i = 0; i < input.size(); ++i)
	{
		if (input[i].size() > BOARD_WIDTH)
			BOARD_WIDTH = input[i].size();
	}

	// get board height
	BOARD_HEIGHT = input.size()-2;

	// add values from the input into our board map
	for (int i = BOARD_HEIGHT-1; i >= 0; --i)
	{
		vector<int> temp_vec(BOARD_WIDTH, 0);
		board.push_back(temp_vec);
		for (int x = 0; x < BOARD_WIDTH; ++x)
		{
			int y = BOARD_HEIGHT-1-i;

			// cases for " ", ".", and "#"
			if (x >= input[i].size() || input[i].at(x) == ' ')
				board[y][x] = -1;
			else if (input[i].at(x) == '.')
				board[y][x] = 0;
			else
				board[y][x] = 1;
		}
	}
	return board;
}

pair<int, int> next_step(pair<int, int> current_pos, pair<int, int> current_dir) {

	pair<int, int> next = pair_sum(current_pos, current_dir);

	// case where we go outside board bounds


	// case where we run into wall
	if (board[next.second][next.first] == 1) {
		return current_pos;
	}

	// case where its empty space yaaay
	if (board[next.second][next.first] == 0) {
		return next;
	}

	assert(false);
}



void execute_all_instructions(vector<pair<int, int>> instructions, pair<int, int> &current_pos, pair<int, int> &current_dir) {

	// loop through and execute each instruction
	for (int i = 0; i < instructions.size(); ++i) {
		if (i%10 == 0)
			cout << i << endl;
		execute_instruction(instructions[i], current_pos, current_dir);
	}
}


int calculate_score(pair<int, int> current_pos, pair<int, int> current_dir) {

	vector<pair<int, int>> directions = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};

	int final_col = current_pos.first+1;
	int final_row = BOARD_HEIGHT - current_pos.second;

	auto it = find(directions.begin(), directions.end(), current_dir);
	assert(it != directions.end());
	int index = it - directions.begin();

	return (1000*final_row + 4*final_col + index);
}

void print_pair(pair<int, int> p) {
	cout << p.first << " " << p.second << endl;
}

bool within_bounds(pair<int, int> pos) {

	// x and y mins
	if (pos.first < 0 || pos.second < 0)
		return false;

	// x max
	if (pos.first >= BOARD_WIDTH)
		return false;

	// y max
	if (pos.second >= BOARD_HEIGHT)
		return false;

	return true;
}

pair<int, int> pair_sum(pair<int, int> a, pair<int, int> b) {
	return {a.first + b.first, a.second + b.second};
}

pair<int, int> rotate(pair<int, int> dir, int turn) {

	vector<pair<int, int>> directions = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};

	auto it = find(directions.begin(), directions.end(), dir);
	assert(it != directions.end());
	int index = it - directions.begin();

	return directions[modulo(index + turn, directions.size())];

}

// pos and dir passed by reference
void execute_instruction(pair<int, int> instruction, pair<int, int> &current_pos, pair<int, int> &current_dir) {

	// note that instruction holds <direction, magnitude>
	int direction = instruction.first;
	int magnitude = instruction.second;

	// update our steps
	for (int i = 0; i < magnitude; ++i)
	{
		// cout << "STEP: " << i << endl;
		// cout << "next_step: ";
		// print_pair(next_step(board, current_pos, current_dir));
		current_pos = next_step(current_pos, current_dir);
		// cout << "current_pos: ";
		// print_pair(current_pos);
		// cout << "current_dir: ";
		// print_pair(current_dir);
	}

	// update our direction
	current_dir = rotate(current_dir, direction);

	// nothing to return -> current pos and dir and passed by reference
}


// returns our starting position
pair<int, int> get_starting_pos() {

	for (int i = 0; i < BOARD_WIDTH; ++i)
	{
		if (board[BOARD_HEIGHT-1][i] == 0)
			return {i, BOARD_HEIGHT-1};
	}

	assert(false);
}

void print_board() {
	for (int y = BOARD_HEIGHT-1; y >= 0; --y)
	{
		for (int x = 0; x < BOARD_WIDTH; ++x)
		{
			if (board[y][x] == -1)
				cout << " ";
			if (board[y][x] == 0)
				cout << ".";
			if (board[y][x] == 1)
				cout << "#";
		}
		cout << endl;
	}
	cout << endl;
}

vector<pair<int, int>> instructions_setup(string info) {
	vector<pair<int, int>> instructions;

	// get our rotations
	vector<int> dirs;
	for (int i = 0; i < info.size(); ++i)
	{
		if (info.at(i) == 'R') {
			info.at(i) = ',';
			dirs.push_back(1);
		}
		if (info.at(i) == 'L') {
			info.at(i) = ',';
			dirs.push_back(-1);
		}
	}
	dirs.push_back(0); // arbitrary-> ignored later

	// get our path lengths
	vector<int> magnitudes = vtoi(split(info, ","));

	assert(dirs.size() == magnitudes.size());

	// put them together
	for (int i = 0; i < dirs.size(); ++i)
	{
		instructions.push_back({dirs[i], magnitudes[i]});
	}

	// note that instructions holds <direction, magnitude>
	return instructions;
}

void print_instructions(vector<pair<int, int>> instructions) {

	// print instructions
	for (int i = 0; i < instructions.size(); ++i)
	{
		cout << instructions[i].first << " " << instructions[i].second << endl;
	}
}



// returns the ACTUAL MATH MODULO NOT THE STUPID CPP "MODULO" REEEE
int modulo(int n, int modulus) {
	return ((n % modulus) + modulus) % modulus;
}