/*
================= HEADER FILE =================
Light file for a couple useful cpp functions

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

#ifndef CPPLITE
#define CPPLITE







#include <bits/stdc++.h>

using namespace std;


vector<string> slurp_lines();
vector<string> slurp();


string ltrim(const string &s, const string remove);
string rtrim(const string &s, const string remove);
string trim(const string &s, const string remove);

string ltrim(const string &s);
string rtrim(const string &s);
string trim(const string &s);


void print(vector<int> v);
void print(vector<int> v, string s);
void print(vector<string> v);
void print(vector<string> v, string s);


vector<int> vtoi(vector<string> v);
vector<long long> vtoll(vector<string> v);
vector<string> split(string s, string delimiter);







#endif