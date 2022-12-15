#include <bits/stdc++.h>

using namespace std;

vector<string> slurp();
vector<string> split(string s, string delimiter);
vector<int> vtoi(vector<string> v);
void print(vector<string> v);
void print(vector<int> v) ;

// tells if two positions are touching
bool touching(pair<int, int> headpos, pair<int, int> tailpos) {

	// this can look cleaner i know, prefer to write it out
	if (abs(headpos.first - tailpos.first) <= 1 && abs(headpos.second - tailpos.second) <= 1) {
		return true;
	}
	return false;
}

pair<int, int> string_to_increment(string s) {
	if (s == "U")
		return {0, 1};
	if (s == "D")
		return {0, -1};
	if (s == "R")
		return {1, 0};
	if (s == "L")
		return {-1, 0};

	assert(false);
}

pair<int, int> sum_pairs(pair<int, int> a, pair<int, int> b) {
	return pair<int, int>({a.first+b.first, a.second+b.second});
}


int main() {

	vector<string> input = slurp();
	
	pair<int, int> headpos = {0, 0};
	pair<int, int> tailpos = {0, 0};

	map<pair<int, int>, bool> visited;
	visited[tailpos] = true;

	// cout << sum_pairs(headpos, tailpos).first << "  " << sum_pairs(headpos, tailpos).second << endl;
	// cout << string_to_increment("R").first <<
	

	for (int i = 0; i < input.size(); i+=2)
	{
		string direction = input[i];
		int steps = stoi(input[i+1]);

		for (int k = 0; k < steps; ++k)
		{
			pair<int, int> prev_headpos = headpos;
			headpos = sum_pairs(headpos, string_to_increment(direction));
			if (!touching(headpos, tailpos)) {
				tailpos = prev_headpos;
				visited[tailpos] = true;
			}
		}
	}

	cout << "num visited: " << visited.size() << endl;






}



// slurps up file input from stdin
vector<string> slurp() {

	// open file i/o
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	vector<string> input;

	while (true) {
		string x;
		cin >> x;
		input.push_back(x);
		if (cin.eof())
			break;
	}

	return input;
}

// prints vector
void print(vector<string> v) {
	for (int i = 0; i < v.size(); ++i)
	{
		cout << v[i] << " ";
	}
	// cout << endl;
}

// prints vector
void print(vector<int> v) {
	for (int i = 0; i < v.size(); ++i)
	{
		cout << v[i] << endl;
	}
	cout << endl;
}

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
