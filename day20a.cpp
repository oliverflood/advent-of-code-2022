#include <bits/stdc++.h>
#include "cpplite.h"

using namespace std;

#define ll long long

/*
g++ day20a.cpp cpplite.cpp -o day20a.exe -std=c++1z
*/



void move(vector<ll> &file, ll n) {

	cout << "moving " << n << endl;
	
	auto it = find(file.begin(), file.end(), n);
	assert(it != file.end());

	ll index = it - file.begin();

	int e = 0;
	if (n > 0)
		e = 1;


	file.insert(file.begin() + ((index + n+e + file.size()) % file.size()), n);

	for (int i = 0; i < file.size(); ++i)
		cout << file[i] << " ";
	cout << endl;


	if ((index + n+e) % file.size() > index)
		file.erase(file.begin() + index);
	else
		file.erase(file.begin() + index + 1);

	for (int i = 0; i < file.size(); ++i)
		cout << file[i] << " ";
	cout << endl;

}

int main() {

	vector<ll> file = vtoll(slurp());

	// for (int i = 0; i < file.size(); ++i)
	// {
	// 	cout << file[i] << endl;
	// }

	// 1st thing in list only changes when 1st thing in list moves, changes to 2th thing
	// zero doesn't moves
	// pos of zero changes when elements in [first, 0) move to (0, first)
	// way stuff moves depends on sign and size -> this can be used

	// nvm, guessing its just easy


	for (int i = 0; i < file.size(); ++i)
		cout << file[i] << " ";
	cout << endl;


	vector<ll> order = file;

	for (int i = 0; i < order.size(); ++i)
	{
		move(file, order[i]);
	}

	for (int i = 0; i < file.size(); ++i)
		cout << file[i] << " ";
	

}
