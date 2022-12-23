#include <bits/stdc++.h>
#include "cpplite.h"

using namespace std;

#define ll long long

/*
g++ day17b.cpp cpplite.cpp -o day17b.exe -std=c++1z
*/

const int CHAMBER_WIDTH = 7;
const ll SIZE = 1000000000000;
int high_rock = -1;

struct shape {
	map<pair<int, int>, bool> area;
	int width;
	int height;
};

void shape_setup(vector<shape> &shapes);
int highest_rock(const map<pair<int, int>, bool> chamber);
void place_shape(map<pair<int, int>, bool> &chamber, const shape shape, const vector<int> pattern, int &index);
void set_position(map<pair<int, int>, bool> &chamber, const shape shape, const pair<int, int> pos);
bool valid_position(map<pair<int, int>, bool> chamber, const shape shape, const pair<int, int> pos);
void print_shape(shape s);
vector<int> get_pattern(string s);
void print_chamber(map<pair<int, int>, bool> chamber);

int global_index = 0;
int global_index2 = 0;

int get_next_dir(vector<int> pattern, int &index, map<pair<int, int>, bool> chamber) {
	
	// if (index % pattern.size() == 0) {
	// 	cout << "INDEX IS 0" << endl;
	// 	print_chamber(chamber);
	// }


	// increment index and return looping jet info
	index++;

	global_index = index%pattern.size();
	global_index2 = index;

	return pattern[(index-1) % pattern.size()];
}


void chamber_trim(map<pair<int, int>, bool> &c, ll cutoff) {

	// for (auto & [pos, filled] : chamber) {
	// 	if (pos.second < cutoff) 
	// 		chamber.erase(pos);
	// }

	for(auto it = c.begin(); it != c.end(); ) {
		if(it->first.second < cutoff)
			it = c.erase(it);
		else
			++it;
	}
}

string chamber_strip(map<pair<int, int>, bool> chamber) {
	int y = highest_rock(chamber);

	string ans;
	for (int i = 0; i < CHAMBER_WIDTH; ++i)
	{
		if (chamber[{i, y}]) 
			ans += "#";
		else 
			ans += " ";
	}

	return ans;
}


int main() {

	vector<string> input = slurp();
	vector<int> pattern = get_pattern(input[0]);

	map<pair<int, int>, bool> chamber;
	vector<shape> shapes;
	shape_setup(shapes);
	int index = 0;


	cout << "pattern size: " << pattern.size() << endl;



	/*
	This is so messy lol
	Looked for repeats, it follows from there ;)
	(I hand calculated the last bit on wolfram alpha, should come back and make this nice soon)
	*/


	vector<pair<int, string>> repeats;

	for (int i = 0; i < 1010; ++i)
	{
		// if (i % 100 == 0)
		// 	cout << i << endl;
		if (global_index == 0) {
			cout << "GLOBAL INDEX 0" << endl;
			if (find(repeats.begin(), repeats.end(), pair<int, string>{i%5, chamber_strip(chamber)}) != repeats.end()) {
				cout << "\n\n\n\nHORAYYYYYYYYY\n" << global_index2 << "\n" << highest_rock(chamber) << "\n" << i << "\n\n\n";
			}
			repeats.push_back(pair<int, string>{i%5, chamber_strip(chamber)});
			cout << "REPEATS: " << endl;
			for (int i = 0; i < repeats.size(); ++i)
			{
				cout << " > " << repeats[i].first << "   " << repeats[i].second << endl;
			}
			cout << endl;
			print_chamber(chamber);
		}
		place_shape(chamber, shapes[i%5], pattern, index);
		//chamber_trim(chamber, highest_rock(chamber) - 40);
		//cout << "highest is: " << highest_rock(chamber) << endl;
	}

	print_chamber(chamber);

	cout << "ans: " << (highest_rock(chamber)+1) << endl;

	cout << "fin" << endl;

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


int highest_rock(const map<pair<int, int>, bool> chamber) {
	int ans = -1;

	for (auto & [pos, filled] : chamber) {
		if (pos.second > ans)
			ans = pos.second;
	}

	return ans;
}



void place_shape(map<pair<int, int>, bool> &chamber, const shape shape, const vector<int> pattern, int &index) {

	// start 2 units from left, 3 units above highest rock
	pair<int, int> curr_pos = {2, highest_rock(chamber) + 4};

	for (int i = 0; i < 3; ++i)
	{
		// get next x movement
		int jet = get_next_dir(pattern, index, chamber);

		// check whether we run into something
		if (valid_position(chamber, shape, {curr_pos.first + jet, curr_pos.second})) {

			// safely update x position
			curr_pos.first += jet;
		}
	}

	curr_pos.second -= 3;

	while (true) {

		// get next x movement
		int jet = get_next_dir(pattern, index, chamber);

		// check whether we run into something
		if (valid_position(chamber, shape, {curr_pos.first + jet, curr_pos.second})) {

			// safely update x position
			curr_pos.first += jet;
		}

		// check y movement
		if (!valid_position(chamber, shape, {curr_pos.first, curr_pos.second-1})) {

			// set position if we land on something
			set_position(chamber, shape, {curr_pos.first, curr_pos.second});
			// if (shape.height + curr_pos.second > high_rock)
			// 	high_rock = shape.height + curr_pos.second;
			chamber_trim(chamber, curr_pos.second - 40);
			return;
		}

		// move shape down
		curr_pos.second--;
	}
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


void print_chamber(map<pair<int, int>, bool> chamber) {
	cout << "chamber: " << endl;

	for (int y = highest_rock(chamber)+1; y >= highest_rock(chamber)+1-30; --y)
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