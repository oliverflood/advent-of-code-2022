#include <bits/stdc++.h>
#include "cpplite.h"

using namespace std;

/*
g++ day22b.cpp cpplite.cpp -o day22b.exe -std=c++1z
*/

// global variables lol
int BOARD_WIDTH = 0;
int BOARD_HEIGHT = 0;

vector<vector<int>> board_setup(vector<string> &input);
vector<pair<int, int>> instructions_setup(string info);
pair<int, int> get_starting_pos(vector<vector<int>> board);
pair<int, int> pair_sum(pair<int, int> a, pair<int, int> b);
pair<int, int> raycast(vector<vector<int>> board, pair<int, int> current_pos, pair<int, int> raycast_dir);
pair<int, int> next_step(vector<vector<int>> board, pair<int, int> current_pos, pair<int, int> &current_dir);
void print_board(vector<vector<int>> board);
void print_instructions(vector<pair<int, int>> instructions);
void execute_instruction(vector<vector<int>> board, pair<int, int> instruction, pair<int, int> &current_pos, pair<int, int> &current_dir);
int modulo(int n, int modulus);
bool within_bounds(pair<int, int> pos);
void print_pair(pair<int, int> p);
int calculate_score(pair<int, int> current_pos, pair<int, int> current_dir);
void execute_all_instructions(vector<vector<int>> board, vector<pair<int, int>> instruction, pair<int, int> &current_pos, pair<int, int> &current_dir);
pair<int, int> quadrant_coords(pair<int, int> current_pos);
void prep_info();
pair<int, int> translate_quadrant_coords(pair<int, int> coords, pair<int, int> quad_a, pair<int, int> quad_b);
pair<int, int> rotate(pair<int, int> dir, int turn);

const int BOARD_SIZE = 50;
int CURRENT_INSTRUCTION_NUMBER = 0;

vector<string> facingmap;

struct neighbor_info {

	int rotate = 0;
	pair<int, int> quad_coords;
};

// 1 right turn, -1 left turn, 2 180 degree turn

struct quad_info {

	neighbor_info up_info;
	neighbor_info down_info;
	neighbor_info left_info;
	neighbor_info right_info;
};

map<pair<int, int>, quad_info> quadrant_info;



// rotating board right is same as rotating cursor left

// rotation 1 is right, -1 is left
pair<int, int> quadrant_rotate(pair<int, int> current_coords, int rotation) {

	if (rotation == 0)
		return current_coords;

	pair<int, int> ans = {0, 0};
	pair<int, int> current_q_coords = quadrant_coords(current_coords);

	if (rotation == -1) {
		ans.second += current_coords.first % BOARD_SIZE;
		ans.first += BOARD_SIZE - 1 - (current_coords.second % BOARD_SIZE);

		ans.first += current_q_coords.first * BOARD_SIZE;
		ans.second += current_q_coords.second * BOARD_SIZE;
		return ans;
	}

	else if (rotation == 2) {
		return quadrant_rotate(quadrant_rotate(current_coords, -1), -1);
	}
	
	else if (rotation == 1) {
		return quadrant_rotate(quadrant_rotate(quadrant_rotate(current_coords, -1), -1), -1);
	}

	assert(false);
}


map<pair<int, int>, char> dir_to_facing;

int main() {

	//dir_to_facing = {{{1, 0}, '>'}, {{-1, 0}, '<'}, {{0, 1}, '^'}, {{0, -1}, 'v'}};
	dir_to_facing[{1, 0}] = '>';
	dir_to_facing[{-1, 0}] = '<';
	dir_to_facing[{0, 1}] = '^';
	dir_to_facing[{0, -1}] = 'v';

	prep_info();

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


	/*
	As a whole this program runs a little slow but premature optimization is
	the root of all evil and 30 seconds isn't too long to wait -> I'll improve
	runtime later maybe :P
	*/
	
	
	// pair<int, int> b = next_step(board, a, d);

	// cout << "returned: ";
	// print_pair(b);

	//print_pair(quadrant_coords({-1, -1}));
	




	facingmap = input;

	// cout << "TESTING:\n\n";


	// pair<int, int> a = {50, 199};
	// pair<int, int> d = {-1, 0};
	// cout << "a: "; print_pair(a);
	// cout << "d: "; print_pair(d);

	// a = next_step(board, a, d);

	// cout << "a: "; print_pair(a);
	// cout << "d: "; print_pair(d);


	/*
	This program may be dumb and very scrappy however it does run very fast
	Needs a lot of revision to look presentable

	*/




	cout << "\n\nstarting pos: "; print_pair(current_pos);
	cout << "starting quadrant: "; print_pair(quadrant_coords(current_pos));
	cout << "starting dir: "; print_pair(current_dir); cout << endl;

	// run the thing
	//print_instructions(instructions);
	cout << "instructions size: " << instructions.size() << endl;
	cout << "EXECUTING INSTRUCTIONS\n\n";
	execute_all_instructions(board, instructions, current_pos, current_dir);
	

	cout << "\nans: " << calculate_score(current_pos, current_dir) << endl;

	print(facingmap);

	// 30529
	// 40000 too low
}


// this is stupid lol
void prep_info() {

	pair<int, int> current_face;
	map<string, pair<int, int>> face_positions;

	// rotation info is direction to rotate to get coords back to true up and down
	// what way to rotate next to get back to original










	face_positions["front"] = {1, 3};
	face_positions["back"] = {1, 1};

	face_positions["left"] = {0, 1};
	face_positions["right"] = {2, 3};

	face_positions["top"] = {0, 0};
	face_positions["bottom"] = {1, 2};


	// front face -/
	current_face = face_positions["front"];
	quadrant_info[current_face].up_info.quad_coords =  face_positions["top"];
	quadrant_info[current_face].up_info.rotate = 1;

	quadrant_info[current_face].down_info.quad_coords = face_positions["bottom"];
	quadrant_info[current_face].down_info.rotate = 0;

	quadrant_info[current_face].left_info.quad_coords = face_positions["left"];
	quadrant_info[current_face].left_info.rotate = 2;

	quadrant_info[current_face].right_info.quad_coords = face_positions["right"];
	quadrant_info[current_face].right_info.rotate = 0;

	// back face -
	current_face = face_positions["back"];
	quadrant_info[current_face].up_info.quad_coords =  face_positions["bottom"];
	quadrant_info[current_face].up_info.rotate = 0;

	quadrant_info[current_face].down_info.quad_coords = face_positions["top"];
	quadrant_info[current_face].down_info.rotate = 1;

	quadrant_info[current_face].left_info.quad_coords = face_positions["left"];
	quadrant_info[current_face].left_info.rotate = 0;

	quadrant_info[current_face].right_info.quad_coords = face_positions["right"];
	quadrant_info[current_face].right_info.rotate = 2;

	// left face -

	current_face = face_positions["left"];
	quadrant_info[current_face].up_info.quad_coords =  face_positions["bottom"];
	quadrant_info[current_face].up_info.rotate = 1;

	quadrant_info[current_face].down_info.quad_coords = face_positions["top"];
	quadrant_info[current_face].down_info.rotate = 0;

	quadrant_info[current_face].left_info.quad_coords = face_positions["front"];
	quadrant_info[current_face].left_info.rotate = 2;

	quadrant_info[current_face].right_info.quad_coords = face_positions["back"];
	quadrant_info[current_face].right_info.rotate = 0;

	// right face -/

	current_face = face_positions["right"];
	quadrant_info[current_face].up_info.quad_coords =  face_positions["top"];
	quadrant_info[current_face].up_info.rotate = 0;

	quadrant_info[current_face].down_info.quad_coords = face_positions["bottom"];
	quadrant_info[current_face].down_info.rotate = 1;

	quadrant_info[current_face].left_info.quad_coords = face_positions["front"];
	quadrant_info[current_face].left_info.rotate = 0;

	quadrant_info[current_face].right_info.quad_coords = face_positions["back"];
	quadrant_info[current_face].right_info.rotate = 2;

	// top face -/

	current_face = face_positions["top"];
	quadrant_info[current_face].up_info.quad_coords =  face_positions["left"];
	quadrant_info[current_face].up_info.rotate = 0;

	quadrant_info[current_face].down_info.quad_coords = face_positions["right"];
	quadrant_info[current_face].down_info.rotate = 0;

	quadrant_info[current_face].left_info.quad_coords = face_positions["front"];
	quadrant_info[current_face].left_info.rotate = -1;

	quadrant_info[current_face].right_info.quad_coords = face_positions["back"];
	quadrant_info[current_face].right_info.rotate = -1;

	// bottom face -/

	current_face = face_positions["bottom"];
	quadrant_info[current_face].up_info.quad_coords =  face_positions["front"];
	quadrant_info[current_face].up_info.rotate = 0;

	quadrant_info[current_face].down_info.quad_coords = face_positions["back"];
	quadrant_info[current_face].down_info.rotate = 0;

	quadrant_info[current_face].left_info.quad_coords = face_positions["left"];
	quadrant_info[current_face].left_info.rotate = -1;

	quadrant_info[current_face].right_info.quad_coords = face_positions["right"];
	quadrant_info[current_face].right_info.rotate = -1;












	// face_positions["front"] = {2, 2};
	// face_positions["back"] = {2, 0};

	// face_positions["left"] = {1, 1};
	// face_positions["right"] = {3, 0};

	// face_positions["top"] = {0, 1};
	// face_positions["bottom"] = {2, 1};



	// // front face -/
	// current_face = face_positions["front"];
	// quadrant_info[current_face].up_info.quad_coords =  face_positions["top"];
	// quadrant_info[current_face].up_info.rotate = 2;

	// quadrant_info[current_face].down_info.quad_coords = face_positions["bottom"];
	// quadrant_info[current_face].down_info.rotate = 0;

	// quadrant_info[current_face].left_info.quad_coords = face_positions["left"];
	// quadrant_info[current_face].left_info.rotate = -1;

	// quadrant_info[current_face].right_info.quad_coords = face_positions["right"];
	// quadrant_info[current_face].right_info.rotate = 2;

	// // back face -
	// current_face = face_positions["back"];
	// quadrant_info[current_face].up_info.quad_coords =  face_positions["bottom"];
	// quadrant_info[current_face].up_info.rotate = 0;

	// quadrant_info[current_face].down_info.quad_coords = face_positions["top"];
	// quadrant_info[current_face].down_info.rotate = 2;

	// quadrant_info[current_face].left_info.quad_coords = face_positions["left"];
	// quadrant_info[current_face].left_info.rotate = 1;

	// quadrant_info[current_face].right_info.quad_coords = face_positions["right"];
	// quadrant_info[current_face].right_info.rotate = 0;

	// // left face -

	// current_face = face_positions["left"];
	// quadrant_info[current_face].up_info.quad_coords =  face_positions["front"];
	// quadrant_info[current_face].up_info.rotate = 1;

	// quadrant_info[current_face].down_info.quad_coords = face_positions["back"];
	// quadrant_info[current_face].down_info.rotate = -1;

	// quadrant_info[current_face].left_info.quad_coords = face_positions["top"];
	// quadrant_info[current_face].left_info.rotate = 0;

	// quadrant_info[current_face].right_info.quad_coords = face_positions["bottom"];
	// quadrant_info[current_face].right_info.rotate = 0;

	// // right face -

	// current_face = face_positions["right"];
	// quadrant_info[current_face].up_info.quad_coords =  face_positions["bottom"];
	// quadrant_info[current_face].up_info.rotate = -1;

	// quadrant_info[current_face].down_info.quad_coords = face_positions["top"];
	// quadrant_info[current_face].down_info.rotate = -1;

	// quadrant_info[current_face].left_info.quad_coords = face_positions["back"];
	// quadrant_info[current_face].left_info.rotate = 0;

	// quadrant_info[current_face].right_info.quad_coords = face_positions["front"];
	// quadrant_info[current_face].right_info.rotate = 2;

	// // top face -

	// current_face = face_positions["top"];
	// quadrant_info[current_face].up_info.quad_coords =  face_positions["front"];
	// quadrant_info[current_face].up_info.rotate = 2;

	// quadrant_info[current_face].down_info.quad_coords = face_positions["back"];
	// quadrant_info[current_face].down_info.rotate = 2;

	// quadrant_info[current_face].left_info.quad_coords = face_positions["right"];
	// quadrant_info[current_face].left_info.rotate = 1;

	// quadrant_info[current_face].right_info.quad_coords = face_positions["left"];
	// quadrant_info[current_face].right_info.rotate = 0;

	// // bottom face -

	// current_face = face_positions["bottom"];
	// quadrant_info[current_face].up_info.quad_coords =  face_positions["front"];
	// quadrant_info[current_face].up_info.rotate = 0;

	// quadrant_info[current_face].down_info.quad_coords = face_positions["back"];
	// quadrant_info[current_face].down_info.rotate = 0;

	// quadrant_info[current_face].left_info.quad_coords = face_positions["left"];
	// quadrant_info[current_face].left_info.rotate = 0;

	// quadrant_info[current_face].right_info.quad_coords = face_positions["right"];
	// quadrant_info[current_face].right_info.rotate = 1;

}


// pair<int, int> raycast(vector<vector<int>> board, pair<int, int> current_pos, pair<int, int> raycast_dir) {

// 	assert(abs(raycast_dir.first+raycast_dir.second) == 1);

// 	while (within_bounds(pair_sum(current_pos, raycast_dir)) && board[pair_sum(current_pos, raycast_dir).second][pair_sum(current_pos, raycast_dir).first] != -1) {
// 		current_pos = pair_sum(current_pos, raycast_dir);
// 	}

// 	assert(board[current_pos.second][current_pos.first] != -1);
// 	return current_pos;
// }


pair<int, int> quadrant_coords(pair<int, int> current_pos) {

	// !!!doesnt work if given negative vals

	// pair<int, int> q;
	// if (current_pos.first < 0)
	// 	q.first = -1;
	// else 
	// 	q.first = current_pos.first / BOARD_SIZE;

	// if (current_pos.second < 0)
	// 	q.second = -1;
	// else
	return {current_pos.first / BOARD_SIZE, current_pos.second / BOARD_SIZE};
}

neighbor_info get_next_quadrant_info(pair<int, int> current_q_coords, pair<int, int> current_dir) {

	// right
	if (current_dir.first == 1 && current_dir.second == 0)
		return quadrant_info[current_q_coords].right_info;

	// left
	if (current_dir.first == -1 && current_dir.second == 0)
		return quadrant_info[current_q_coords].left_info;

	// up
	if (current_dir.first == 0 && current_dir.second == 1)
		return quadrant_info[current_q_coords].up_info;

	// down
	if (current_dir.first == 0 && current_dir.second == -1)
		return quadrant_info[current_q_coords].down_info;

	assert(false);
}

pair<int, int> translate_quadrant_coords(pair<int, int> coords, pair<int, int> quad_a, pair<int, int> quad_b) {
	return {(coords.first % BOARD_SIZE) + (quad_b.first * BOARD_SIZE), (coords.second % BOARD_SIZE) + (quad_b.second * BOARD_SIZE)};
}

pair<int, int> next_step(vector<vector<int>> board, pair<int, int> current_pos, pair<int, int> &current_dir) {

	pair<int, int> next = pair_sum(current_pos, current_dir);

	assert(abs(current_dir.first) + abs(current_dir.second) == 1);

	// case where we run off cube edge
	if (quadrant_coords(next) != quadrant_coords(current_pos) || !within_bounds(next)) {
		pair<int, int> current_q_coords = quadrant_coords(current_pos);

		neighbor_info next_quadrant_info = get_next_quadrant_info(current_q_coords, current_dir);

		// cout << "next quadrant: ";
		// print_pair(next_quadrant_info.quad_coords);

		pair<int, int> current_q_rotated_coords = quadrant_rotate(current_pos, next_quadrant_info.rotate);
		// cout << "current_q_rotated_coords";
		// print_pair(current_q_rotated_coords);

		pair<int, int> almost_real_next_coords = translate_quadrant_coords(current_q_rotated_coords, current_q_coords, next_quadrant_info.quad_coords);

		pair<int, int> real_next_dir = rotate(current_dir, next_quadrant_info.rotate);

		// cout << "real_next_dir: ";
		// print_pair(real_next_dir);

		pair<int, int> real_next_dir_looped;
		real_next_dir_looped.first = real_next_dir.first * (-(BOARD_SIZE-1));
		real_next_dir_looped.second = real_next_dir.second * (-(BOARD_SIZE-1));

		pair<int, int> real_next_coords = pair_sum(almost_real_next_coords, real_next_dir_looped);

		assert(quadrant_coords(almost_real_next_coords) == quadrant_coords(real_next_coords));
		// cout << "real_next_coords: ";
		// print_pair(real_next_coords);

		if (board[real_next_coords.second][real_next_coords.first] == 0) {
			// change current dir
			current_dir = real_next_dir;

			assert(real_next_coords.first >= 0 && real_next_coords.first < BOARD_WIDTH);
			assert(real_next_coords.second >= 0 && real_next_coords.second < BOARD_HEIGHT);

			return real_next_coords;
		}
		assert(board[real_next_coords.second][real_next_coords.first] == 1);
		return current_pos;
	}

	assert(board[next.second][next.first] == 1 || board[next.second][next.first] == 0);

	// get our current quadrant coords and current direction
	// use this to find our next quadrant
	// find our rotated coords in current quadrant
	// translate those to next quadrant 
	// rotate current dir if needed
	// finally add current dir and see if that square is free
	// if it is then return in, if not return current pos

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



void execute_all_instructions(vector<vector<int>> board, vector<pair<int, int>> instructions, pair<int, int> &current_pos, pair<int, int> &current_dir) {

	// loop through and execute each instruction
	for (int i = 0; i < instructions.size(); ++i) {
		CURRENT_INSTRUCTION_NUMBER = i;
		if (i%100 == 0) {
			cout << "INSTRUCTION NUMBER " << i << endl;
			print(facingmap);
		}
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

	cout << "final row: " << final_row << endl;
	cout << "final col: " << final_col << endl;
	cout << "final dir: ";
	print_pair(current_dir);
	cout << endl;

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
	if (turn == 0)
		return dir;

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

	pair<int, int> prev_pos;

	// update our steps
	for (int i = 0; i < magnitude; ++i)
	{
		prev_pos = current_pos;
		// cout << "STEP: " << i << endl;
		// cout << "next_step: ";
		// print_pair(next_step(board, current_pos, current_dir));
		current_pos = next_step(board, current_pos, current_dir);

		facingmap[BOARD_HEIGHT-1 - current_pos.second].at(current_pos.first) = dir_to_facing[current_dir];
		//facingmap[BOARD_HEIGHT-1 - current_pos.second].replace(current_pos.first, 1, to_string(dir_to_facing[current_dir]));

		if (current_pos == prev_pos)
			break;
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
	for (int i = 0; i < input.size()-1; ++i)
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