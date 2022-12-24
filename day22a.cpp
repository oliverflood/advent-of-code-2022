#include <bits/stdc++.h>
#include "cpplite.h"

using namespace std;

/*
g++ day22a.cpp cpplite.cpp -o day22a.exe -std=c++1z
*/

// global variables lol
int BOARD_WIDTH = 0;
int BOARD_HEIGHT = 0;

vector<vector<int>> board_setup(vector<string> &input);
vector<pair<int, int>> instructions_setup(string info);
pair<int, int> get_starting_pos(vector<vector<int>> board);
pair<int, int> pair_sum(pair<int, int> a, pair<int, int> b);
pair<int, int> raycast(vector<vector<int>> board, pair<int, int> current_pos, pair<int, int> raycast_dir);
pair<int, int> next_step(vector<vector<int>> board, pair<int, int> current_pos, pair<int, int> current_dir);
void print_board(vector<vector<int>> board);
void print_instructions(vector<pair<int, int>> instructions);
void execute_instruction(vector<vector<int>> board, pair<int, int> instruction, pair<int, int> &current_pos, pair<int, int> &current_dir);
int modulo(int n, int modulus);
bool within_bounds(pair<int, int> pos);
void print_pair(pair<int, int> p);
int calculate_score(pair<int, int> current_pos, pair<int, int> current_dir);
void execute_all_instructions(vector<vector<int>> board, vector<pair<int, int>> instruction, pair<int, int> &current_pos, pair<int, int> &current_dir);

int main() {

	// prepare board and instructions
	vector<string> input = slurp_lines();
	vector<vector<int>> board = board_setup(input);
	vector<pair<int, int>> instructions = instructions_setup(input[input.size()-1]);

	// note that an instruction holds <direction, magnitude>

	cout << "BOARD_HEIGHT: " << BOARD_HEIGHT << endl;
	cout << "BOARD_WIDTH: " << BOARD_WIDTH << endl;
	// print_board(board);
	// print_instructions(instructions);
	
	// prepare starting position
	pair<int, int> current_pos = get_starting_pos(board);
	pair<int, int> current_dir = {1, 0};

	// cout << "current_pos: ";
	// print_pair(current_pos);
	// cout << "current_dir: ";
	// print_pair(current_dir);


	/*
	As a whole this program runs a little slow but premature optimization is
	the root of all evil and 30 seconds isn't too long to wait -> I'll improve
	runtime later maybe :P
	*/
	
	cout << "instructions size: " << instructions.size() << endl;
	cout << "EXECUTING INSTRUCTIONS\n\n";
	execute_all_instructions(board, instructions, current_pos, current_dir);
	

	// cout << "final pos: ";
	// print_pair(current_pos);
	// cout << "final dir: ";
	// print_pair(current_dir);

	cout << "\nans: " << calculate_score(current_pos, current_dir) << endl;
}


void execute_all_instructions(vector<vector<int>> board, vector<pair<int, int>> instructions, pair<int, int> &current_pos, pair<int, int> &current_dir) {

	// loop through and execute each instruction
	for (int i = 0; i < instructions.size(); ++i) {
		if (i%10 == 0)
			cout << i << endl;
		execute_instruction(board, instructions[i], current_pos, current_dir);
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

pair<int, int> raycast(vector<vector<int>> board, pair<int, int> current_pos, pair<int, int> raycast_dir) {

	assert(abs(raycast_dir.first+raycast_dir.second) == 1);

	while (within_bounds(pair_sum(current_pos, raycast_dir)) && board[pair_sum(current_pos, raycast_dir).second][pair_sum(current_pos, raycast_dir).first] != -1) {
		current_pos = pair_sum(current_pos, raycast_dir);
	}

	assert(board[current_pos.second][current_pos.first] != -1);
	return current_pos;
}

pair<int, int> next_step(vector<vector<int>> board, pair<int, int> current_pos, pair<int, int> current_dir) {

	assert(abs(current_dir.first+current_dir.second) == 1);

	pair<int, int> next = pair_sum(current_pos, current_dir);

	// check that we actually change anything lol
	assert((next.first != current_pos.first) || (next.second != current_pos.second));

	// case where we run off map
	if (!within_bounds(next) || board[next.second][next.first] == -1) {
		// cout << "raycast case: ";
		// if (!within_bounds(next))
		// 	cout << "not within bounds";
		// if (board[next] == -1)
		// 	cout << "looping around";
		// cout << endl;

		// find next possible position
		pair<int, int> raycast_pos = raycast(board, current_pos, {-current_dir.first, -current_dir.second});

		// if its empty we go ther	
		if (board[raycast_pos.second][raycast_pos.first] == 0) 
			return raycast_pos;
		else
			return current_pos;
	}

	// case where we run into wall
	if (board[next.second][next.first] == 1) {
		// cout << "wall case" << endl;
		return current_pos;
	}

	// case where its empty space yaaay
	if (board[next.second][next.first] == 0) {
		// cout << "empty case" << endl;
		return next;
	}

	assert(false);
}

pair<int, int> rotate(pair<int, int> dir, int turn) {

	vector<pair<int, int>> directions = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};

	auto it = find(directions.begin(), directions.end(), dir);
	assert(it != directions.end());
	int index = it - directions.begin();

	return directions[modulo(index + turn, directions.size())];

}

// pos and dir passed by reference
void execute_instruction(vector<vector<int>> board, pair<int, int> instruction, pair<int, int> &current_pos, pair<int, int> &current_dir) {

	// note that instruction holds <direction, magnitude>
	int direction = instruction.first;
	int magnitude = instruction.second;

	// update our steps
	for (int i = 0; i < magnitude; ++i)
	{
		// cout << "STEP: " << i << endl;
		// cout << "next_step: ";
		// print_pair(next_step(board, current_pos, current_dir));
		current_pos = next_step(board, current_pos, current_dir);
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
pair<int, int> get_starting_pos(vector<vector<int>> board) {

	for (int i = 0; i < BOARD_WIDTH; ++i)
	{
		if (board[BOARD_HEIGHT-1][i] == 0)
			return {i, BOARD_HEIGHT-1};
	}

	assert(false);
}

void print_board(vector<vector<int>> board) {
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

// returns the ACTUAL MATH MODULO NOT THE STUPID CPP "MODULO" REEEE
int modulo(int n, int modulus) {
	return ((n % modulus) + modulus) % modulus;
}