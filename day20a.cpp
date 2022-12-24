#include <bits/stdc++.h>
#include "cpplite.h"

using namespace std;

#define ll long long

/*
g++ day20a.cpp cpplite.cpp -o day20a.exe -std=c++1z
*/

void print_grove(vector<int> grove, map<int, int> movement_info);
void move(vector<int> &grove, map<int, int> movement_info, int item);
void mix(vector<int> &grove, map<int, int> movement_info);
void input_setup(vector<int> &grove, map<int, int> &movement_info, vector<int> file);
int sum_coordinates(vector<int> grove, map<int, int> movement_info);




int main() {

	vector<int> file = vtoi(slurp());
	map<int, int> movement_info; // the original values
	vector<int> grove; // unique identifier [0, size] for each elem

	// input setup
	input_setup(grove, movement_info, file);

	// mix once
	mix(grove, movement_info);

	// answer
	printf("final grove: \n");
	print_grove(grove, movement_info);
	printf("ans: %d", sum_coordinates(grove, movement_info));
}




void mix(vector<int> &grove, map<int, int> movement_info) {
	for (int i = 0; i < grove.size(); ++i)
	{
		move(grove, movement_info, i);
	}
}

void print_grove(vector<int> grove, map<int, int> movement_info) {
	for (int i = 0; i < grove.size(); ++i)
	{
		cout << movement_info[grove[i]] << " ";
	}
	cout << endl;
}


void move(vector<int> &grove, map<int, int> movement_info, int item) {
	
	// find index of item to move
	int item_index = find(grove.begin(), grove.end(), item)-grove.begin();

	// rotate to get element in front
	rotate(grove.begin(), grove.begin() + item_index, grove.end());
	
	// find new index of item
	int new_index = movement_info[item];

	// normalize to bounds of [0, grove.size()-1)
	while(new_index < 0)
		new_index += grove.size()-1;
	new_index = new_index % (grove.size()-1);

	// remove item
	grove.erase(grove.begin());

	// re-insert item
	grove.insert(grove.begin() + new_index, item);
}


void input_setup(vector<int> &grove, map<int, int> &movement_info, vector<int> file) {
	for (int i = 0; i < file.size(); ++i)
	{
		grove.push_back(i);
		movement_info[i] = file[i];
	}
}


int sum_coordinates(vector<int> grove, map<int, int> movement_info) {

	// find element which has movement info equal to zero
	int elem;
	for (auto & [key, value] : movement_info) {
		if (value == 0)
			elem = key;
	}

	// find index of zero(info value) element
	int item_index = find(grove.begin(), grove.end(), elem) - grove.begin();

	// rotate to get zero(info value) element in front
	rotate(grove.begin(), grove.begin() + item_index, grove.end());

	// calculate our answer
	int ans = movement_info[grove[1000 % grove.size()]];
	ans += movement_info[grove[2000 % grove.size()]];
	ans += movement_info[grove[3000 % grove.size()]];

	return ans;
}
