#include <bits/stdc++.h>

using namespace std;

// I know I need to make a header + implementation file aaaaaaa
vector<string> slurp();
vector<string> split(string s, string delimiter);
vector<int> vtoi(vector<string> v);
void print(vector<string> v);
void print(vector<int> v) ;

vector<string> split2(string s, string delimiter) {
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

pair<int, int> string_to_pair(string s) {
	vector<string> vec = split2(s, ",");
	
	return {stoi(vec[0]), stoi(vec[1])};
}

void fill_rocks(map<pair<int, int>, bool> &graph, pair<int, int> a, pair<int, int> b) {
	for (int i = min(a.first, b.first); i <= max(a.first, b.first); ++i)
	{
		for (int k = min(a.second, b.second); k <= max(a.second, b.second); ++k)
		{
			graph[{i, k}] = true;
		}
	}
}

bool blocked(map<pair<int, int>, bool> graph, pair<int, int> pos) {
	return(graph[{pos.first-1, pos.second+1}] && graph[{pos.first, pos.second+1}] && graph[{pos.first+1, pos.second+1}]);
}

void print_graph(map<pair<int, int>, bool> graph) {
	for (int y = 0; y < 200; ++y)
	{
		for (int x = 300; x < 600; ++x)
		{
			if (graph[{x, y}])
				cout << "#";
			else
				cout << ".";
		}
		cout << endl;
	}
	cout << endl;
}

const int LIMIT = 300;

bool place_sand(map<pair<int, int>, bool> &graph) {
	pair<int, int> pos = {500, 0};

	while (!blocked(graph, pos)) {

		//cout << "pos: " << pos.first << " " << pos.second << endl;
		if (pos.second >= LIMIT) {
			return false;
		}
		// down
		if (!graph[{pos.first, pos.second+1}]) {
			pos = {pos.first, pos.second+1};
			continue;
		}

		// down left
		if (!graph[{pos.first-1, pos.second+1}]) {
			pos = {pos.first-1, pos.second+1};
			continue;
		}

		// down right
		if (!graph[{pos.first+1, pos.second+1}]) {
			pos = {pos.first+1, pos.second+1};
			continue;
		}
	}

	graph[{pos.first, pos.second}] = true;
	return true;
}

int main() {

	vector<string> input = slurp();
	vector<vector<string>> rocks;
	map<pair<int, int>, bool> graph;

	for (int i = 0; i < input.size(); ++i)
	{
		rocks.push_back(split(input[i], " -> "));
	}

	for (int i = 0; i < rocks.size(); ++i)
	{
		print(rocks[i]);
	}

	for (int i = 0; i < rocks.size(); ++i)
	{
		for (int k = 0; k < rocks[i].size()-1; ++k)
		{
			fill_rocks(graph, string_to_pair(rocks[i][k]), string_to_pair(rocks[i][k+1]));
		}
	}

	print_graph(graph);


	// still quite slow, needs improvement
	int count = 0;
	while (place_sand(graph)) {
		//print_graph(graph);
		count++;
	}

	print_graph(graph);
	cout << "ans: " << count << endl;


}
// 920 too high



// slurps up file input from stdin
vector<string> slurp() {

	// open file i/o
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	vector<string> input;

	while (true) {
		string x;
		getline(cin, x);
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
	cout << endl;
}

// prints vector
void print(vector<int> v) {
	for (int i = 0; i < v.size(); ++i)
	{
		cout << v[i] << " ";
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

	while(true)
	{
		if (s.find(delimiter, pos1) == string::npos) {
			v.push_back(s.substr(pos1, s.size()-pos1-1));
			break;
		}
		int pos2 = s.find(delimiter, pos1);
		v.push_back(s.substr(pos1, pos2-pos1));
		pos1 = pos2+delimiter.size();

	}

	return(v);
}
