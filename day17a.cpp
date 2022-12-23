#include <bits/stdc++.h>
#include "cpplite.h"

using namespace std;

#define ll long long

/*
g++ day17a.cpp cpplite.cpp -o day17a.exe -std=c++1z
*/

const int CHAMBER_WIDTH = 7;
//int highest_rock = -1;

struct shape {
	map<pair<int, int>, bool> area;
	int width;
	int height;
};

void shape_setup(vector<shape> &shapes);

void print_shape(shape s) {
	for (int i = 3; i >= 0; --i)
	{
		for (int k = 0; k < 4; ++k)
		{
			if (s.area[{k, i}])
				cout << "#";
			else 
				cout << " ";
		}
		cout << endl;
	}
	cout << endl;
}


bool valid_position(map<pair<int, int>, bool> chamber, const shape shape, const pair<int, int> pos) {

	// check that shape is above ground
	if (pos.second < 0)
		return false;

	// check that shape is within walls of chamber
	if (shape.width + pos.first > CHAMBER_WIDTH || pos.first < 0)
		return false;

	// check that shape isn't in contact with rocks
	for (auto & [shape_pos, shape_filled] : shape.area) {

		int true_x = pos.first + shape_pos.first;
		int true_y = pos.second + shape_pos.second;

		// checking contact with chamber and shape
		if (chamber[{true_x, true_y}] && shape_filled)
			return false;
	}

	// shape is good to go
	return true;
}

void set_position(map<pair<int, int>, bool> &chamber, const shape shape, const pair<int, int> pos) {

	//cout << "calling set position with pos: " << pos.first << " " << pos.second << endl;

	// set shape to rocks in chamber
	for (auto & [shape_pos, shape_filled] : shape.area) {

		int true_x = pos.first + shape_pos.first;
		int true_y = pos.second + shape_pos.second;

		chamber[{true_x, true_y}] = true;
	}
}

vector<int> get_pattern(string s) {
	vector<int> ans;

	for (int i = 0; i < s.size(); ++i)
	{
		if (s.at(i) == '>')
			ans.push_back(1);
		else if (s.at(i) == '<')
			ans.push_back(-1);
	}

	return ans;
}

int highest_rock(const map<pair<int, int>, bool> chamber) {
	int ans = -1;

	for (auto & [pos, filled] : chamber) {
		if (pos.second > ans)
			ans = pos.second;
	}

	return ans;
}

int get_next_dir(vector<int> pattern, int &index) {

	// increment index and return looping jet info
	index++;
	return pattern[(index-1) % pattern.size()];
}

void place_shape(map<pair<int, int>, bool> &chamber, const shape shape, const vector<int> pattern, int &index) {

	// start 2 units from left, 3 units above highest rock
	pair<int, int> curr_pos = {2, highest_rock(chamber) + 4};

	while (true) {

		// get next x movement
		int jet = get_next_dir(pattern, index);

		// check whether we run into something
		if (valid_position(chamber, shape, {curr_pos.first + jet, curr_pos.second})) {

			// safely update x position
			curr_pos.first += jet;
		}

		// check y movement
		if (!valid_position(chamber, shape, {curr_pos.first, curr_pos.second-1})) {

			// set position if we land on something
			set_position(chamber, shape, {curr_pos.first, curr_pos.second});

			return;
		}

		// move shape down
		curr_pos.second--;
	}
}


void print_chamber(map<pair<int, int>, bool> chamber) {
	cout << "chamber: " << endl;

	for (int y = highest_rock(chamber)+1; y >= 0; --y)
	{
		for (int x = 0; x < CHAMBER_WIDTH; ++x)
		{
			if (chamber[{x, y}])
				cout << "#";
			else
				cout << " ";
		}
		cout << endl;
	}
	cout << endl;
}


const int YEAR = 2022;

int main() {

	vector<string> input = slurp();
	vector<int> pattern = get_pattern(input[0]);

	map<pair<int, int>, bool> chamber;
	vector<shape> shapes;
	shape_setup(shapes);
	int index = 0;


	for (int i = 0; i < YEAR; ++i)
	{
		place_shape(chamber, shapes[i%5], pattern, index);
		cout << i << "  \n";
		cout << "highest is: " << highest_rock(chamber) << endl;
	}

	print_chamber(chamber);

	cout << "ans: " << (highest_rock(chamber)+1) << endl;

}





// pls don't judge me
void shape_setup(vector<shape> &shapes) {

	shape a, b, c, d, e;
	a.width = 4;
	b.width = 3;
	c.width = 3;
	d.width = 1;
	e.width = 2;

	a.height = 1;
	b.height = 3;
	c.height = 3;
	d.height = 4;
	e.height = 2;

	a.area[{0, 0}] = true;
	a.area[{1, 0}] = true;
	a.area[{2, 0}] = true;
	a.area[{3, 0}] = true;

	b.area[{1, 1}] = true;
	b.area[{0, 1}] = true;
	b.area[{1, 0}] = true;
	b.area[{1, 2}] = true;
	b.area[{2, 1}] = true;

	c.area[{0, 0}] = true;
	c.area[{1, 0}] = true;
	c.area[{2, 0}] = true;
	c.area[{2, 1}] = true;
	c.area[{2, 2}] = true;

	d.area[{0, 0}] = true;
	d.area[{0, 1}] = true;
	d.area[{0, 2}] = true;
	d.area[{0, 3}] = true;

	e.area[{0, 0}] = true;
	e.area[{0, 1}] = true;
	e.area[{1, 0}] = true;
	e.area[{1, 1}] = true;

	shapes.push_back(a);
	shapes.push_back(b);
	shapes.push_back(c);
	shapes.push_back(d);
	shapes.push_back(e);
}