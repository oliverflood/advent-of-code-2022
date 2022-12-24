#include <bits/stdc++.h>
#include "cpplite.h"

using namespace std;

#define ll long long

/*
g++ day20b.cpp cpplite.cpp -o day20b.exe -std=c++1z
*/

void print_grove(vector<ll> grove, map<ll, ll> movement_info);
void move(vector<ll> &grove, map<ll, ll> movement_info, ll item);
void mix(vector<ll> &grove, map<ll, ll> movement_info);
void input_setup(vector<ll> &grove, map<ll, ll> &movement_info, vector<ll> file);
ll sum_coordinates(vector<ll> grove, map<ll, ll> movement_info);
ll modulo(ll num, ll modulizer);

const ll DECRYPTION_KEY = 811589153;
const ll grove_size = 5000;

int main() {

	vector<ll> file = vtoll(slurp());
	map<ll, ll> movement_info; // the original values
	vector<ll> grove; // unique identifier [0, size] for each elem

	// input setup
	input_setup(grove, movement_info, file);
	printf("initial grove: \n");
	if (grove.size() < 10)
		print_grove(grove, movement_info);

	// mix ten times
	for (ll i = 0; i < 10; ++i) {
		cout << "round: " << (i+1) << ": " << endl;
		mix(grove, movement_info);
		if (grove.size() < 10)
			print_grove(grove, movement_info);
	}

	// answer
	printf("final grove: \n");
	print_grove(grove, movement_info);
	printf("ans: %d", sum_coordinates(grove, movement_info));
}

// 1786887030 too low
// 1786887030
// 1143110556

// 0 4 5 6 2 9 1 8
// 0 5 6 2 9 4 1 8


ll modulo(ll n, ll M) {

	return (((n % M) + M) % M);
	// if (num == modulizer)
	// 	return 0;

	// if (num > 0)
	// 	return (num % modulizer);

	// if (num == 0)
	// 	return 0;

	// if (num < 0) {
	// 	if ((modulizer-((0-num) % modulizer)) == modulizer)
	// 		return 0;
	// 	return (modulizer-((0-num) % modulizer));
	// }
}


void mix(vector<ll> &grove, map<ll, ll> movement_info) {	
	for (int i = 0; i < grove.size(); ++i)
	{
		move(grove, movement_info, i);
	}
}

void print_grove(vector<ll> grove, map<ll, ll> movement_info) {
	for (int i = 0; i < grove.size(); ++i)
	{
		cout << movement_info[grove[i]] << " ";
	}
	cout << endl << endl;
}

// void move(vector<ll> &grove, map<ll, ll> movement_info, ll item) {
// 	if (movement_info[item] == 0)
// 		return;

// 	// find index of item to move
// 	assert(find(grove.begin(), grove.end(), item) != grove.end());
// 	ll item_index = find(grove.begin(), grove.end(), item)-grove.begin();

// 	// rotate to get element in front
// 	// rotate(grove.begin(), grove.begin() + item_index, grove.end());
// 	// assert(grove[0] == item);
	
// 	// find new index of item
// 	//ll new_index = movement_info[item];

// 	// normalize to bounds of [0, grove.size()-1)
// 	assert(grove.size()-1 == grove_size-1);
// 	ll new_index = modulo(item_index-1+movement_info[item], grove.size()-1);
// 	cout << "new_index: " << new_index << "   " << (grove.size()-1) << endl;

// 	// while(new_index < 0)
// 	// 	new_index += 100*grove.size()-1;
// 	// new_index = new_index % (grove.size()-1);

// 	assert(new_index >= 0);
// 	assert(new_index < grove.size()-1);

// 	// remove item
// 	grove.erase(grove.begin() + item_index);

// 	// re-insert item
// 	grove.insert(grove.begin() + new_index, item);
// }

void move(vector<ll> &grove, map<ll, ll> movement_info, ll item) {
	if (movement_info[item] == 0)
		return;

	// find index of item to move
	assert(find(grove.begin(), grove.end(), item) != grove.end());
	ll item_index = find(grove.begin(), grove.end(), item)-grove.begin();

	// rotate to get element in front
	rotate(grove.begin(), grove.begin() + item_index, grove.end());
	assert(grove[0] == item);
	
	// find new index of item
	//ll new_index = movement_info[item];

	// normalize to bounds of [0, grove.size()-1)
	assert(grove.size()-1 == grove_size-1);
	ll new_index = modulo(movement_info[item], grove.size()-1);

	// while(new_index < 0)
	// 	new_index += 100*grove.size()-1;
	// new_index = new_index % (grove.size()-1);

	assert(new_index >= 0);
	assert(new_index < grove.size()-1);

	// remove item
	grove.erase(grove.begin());

	// re-insert item
	grove.insert(grove.begin() + new_index, item);
}


void input_setup(vector<ll> &grove, map<ll, ll> &movement_info, vector<ll> file) {
	for (int i = 0; i < file.size(); ++i)
	{
		grove.push_back(i);
		movement_info[i] = file[i] * DECRYPTION_KEY;
	}
}


ll sum_coordinates(vector<ll> grove, map<ll, ll> movement_info) {

	// find element which has movement info equal to zero
	// ll elem;
	// for (auto & [key, value] : movement_info) {
	// 	if (value == 0)
	// 		elem = key;
	// }

	ll zero_index;
	for (int i = 0; i < grove.size(); ++i)
	{
		if (movement_info[grove[i]] == 0) {
			zero_index = i;
		}

	}

	assert(movement_info[grove[zero_index]] == 0);

	// find index of zero(info value) element
	//ll zero_index = find(grove.begin(), grove.end(), elem) - grove.begin();

	// rotate to get zero(info value) element in front
	//rotate(grove.begin(), grove.begin() + item_index, grove.end());

	//assert(grove[0] == 0);

	// calculate our answer
	cout << "ANS: \n" << movement_info[grove[(zero_index+1000) % grove.size()]] << " " << 
	movement_info[grove[(zero_index+2000) % grove.size()]] << " " <<
	movement_info[grove[(zero_index+3000) % grove.size()]] << endl << endl;

	// ll ans = movement_info[grove[(zero_index+1000) % grove.size()]];
	// cout << ans << endl;
	// ans += movement_info[grove[(zero_index+2000) % grove.size()]];
	// cout << ans << endl;
	// ans += movement_info[grove[(zero_index+3000) % grove.size()]];
	// cout << ans << endl;

	ll ans = movement_info[grove[(zero_index+1000) % grove.size()]] + movement_info[grove[(zero_index+2000) % grove.size()]]
		+movement_info[grove[(zero_index+3000) % grove.size()]];

	cout << "FINAL ANS: " << ans << "/ \n" << endl;

	return ans;
}
