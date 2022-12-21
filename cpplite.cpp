/*
================= IMPLEMENTATION FILE =================
I really ought to separate these into different files 
too, but I'll do that later
Also I know I really ought to use cpp templates, those
are coming soon

> Oliver Flood

             ,\
             \\\,_
              \` ,\
         __,.-" =__)
       ."        )
    ,_/   ,    \/\_
    \_|    )_-\ \_-`
       `-----` `--`
*/

#include <bits/stdc++.h>
#include "cpplite.h"

using namespace std;




/*
============
 FILE INPUT 
============
*/

// slurps up file input from stdin
vector<string> slurp_lines() {

	// open file i/o
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	vector<string> input;

	while (true) {
		string s;
		getline(cin, s);
		input.push_back(s);
		if (cin.eof())
			break;
	}

	return input;
}

// slurps up file input from stdin
vector<string> slurp() {

	// open file i/o
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	vector<string> input;

	while (true) {
		string s;
		cin >> s;
		input.push_back(s);
		if (cin.eof())
			break;
	}

	return input;
}












/*
====================
 INPUT MANIPULATION
====================
*/

// trimming with specified things to be removed
string ltrim(const string &s, const string remove)
{
	size_t start = s.find_first_not_of(remove);
	return (start == std::string::npos) ? "" : s.substr(start);
}
string rtrim(const string &s, const string remove)
{
	size_t end = s.find_last_not_of(remove);
	return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
string trim(const string &s, const string remove) {
	return rtrim(ltrim(s, remove), remove);
}



// trim whitespace
const string REMOVE = " \n\r\t\f\v";
string ltrim(const string &s)
{
	size_t start = s.find_first_not_of(REMOVE);
	return (start == std::string::npos) ? "" : s.substr(start);
}
string rtrim(const string &s)
{
	size_t end = s.find_last_not_of(REMOVE);
	return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
string trim(const string &s) {
	return rtrim(ltrim(s));
}














/*
=====================
 OUTPUT MANIPULATION
=====================
*/

// prints vector of ints
// (no args means print with endl)
void print(vector<int> v) {
	for (int i = 0; i < v.size(); ++i)
	{
		cout << v[i] << endl;
	}
	cout << endl;
}

// prints vector of ints with separator
void print(vector<int> v, string s) {
	for (int i = 0; i < v.size(); ++i)
	{
		cout << v[i] << s;
	}
	cout << endl;
}

// prints vector of strings
// (no args means print with endl)
void print(vector<string> v) {
	for (int i = 0; i < v.size(); ++i)
	{
		cout << v[i] << endl;
	}
	cout << endl;
}

// prints vector of strings with separator
void print(vector<string> v, string s) {
	for (int i = 0; i < v.size(); ++i)
	{
		cout << v[i] << s;
	}
	cout << endl;
}


















/*
================
 MISCELLANEOUS?
================
*/

// changes string vector to int vector
vector<int> vtoi(vector<string> v) {
	vector<int> v2;
	for (int i = 0; i < v.size(); ++i)
	{
		v2.push_back(stoi(v[i]));
	}
	return v2;
}

// splits string by delimiter
// vector<string> split(string s, string delimiter) {
// 	vector<string> v;
// 	int pos1 = 0;

// 	while(true)
// 	{
// 		if (s.find(delimiter, pos1) == string::npos) {
// 			v.push_back(s.substr(pos1, s.size()-pos1-1));
// 			break;
// 		}
// 		int pos2 = s.find(delimiter, pos1);
// 		v.push_back(s.substr(pos1, pos2-pos1));
// 		pos1 = pos2+delimiter.size();
// 	}

// 	return(v);
// }


vector<string> split(string s, string delimiter) {
    vector<string> v;
    int pos1 = 0;

    for (int i = 0; i < count(s.begin(), s.end(), delimiter.at(0))+1; ++i)
    {
        
        int pos2 = s.find(delimiter, pos1);
        v.push_back(s.substr(pos1, pos2-pos1));
        pos1 = pos2+1;
    }

    return(v);
}
