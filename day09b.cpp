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

pair<int, int> find_closest_adjacent(pair<int, int> a, pair<int, int> b) {
	// a is parent

	// cout << "a pos: " << a.first << "  " << a.second << endl;
	// cout << "b pos: " << b.first << "  " << b.second << endl;
	// cout << "test: " << sum_pairs(a, string_to_increment("L")).first << "  " << sum_pairs(a, string_to_increment("L")).second << endl;


	if (touching(sum_pairs(a, string_to_increment("U")), b))
		return sum_pairs(a, string_to_increment("U"));
	if (touching(sum_pairs(a, string_to_increment("D")), b))
		return sum_pairs(a, string_to_increment("D"));
	if (touching(sum_pairs(a, string_to_increment("R")), b))
		return sum_pairs(a, string_to_increment("R"));
	if (touching(sum_pairs(a, string_to_increment("L")), b))
		return sum_pairs(a, string_to_increment("L"));

	if (touching(sum_pairs(sum_pairs(a, string_to_increment("U")), string_to_increment("R")), b))
		return sum_pairs(sum_pairs(a, string_to_increment("U")), string_to_increment("R"));
	if (touching(sum_pairs(sum_pairs(a, string_to_increment("U")), string_to_increment("L")), b))
		return sum_pairs(sum_pairs(a, string_to_increment("U")), string_to_increment("L"));
	if (touching(sum_pairs(sum_pairs(a, string_to_increment("D")), string_to_increment("R")), b))
		return sum_pairs(sum_pairs(a, string_to_increment("D")), string_to_increment("R"));
	if (touching(sum_pairs(sum_pairs(a, string_to_increment("D")), string_to_increment("L")), b))
		return sum_pairs(sum_pairs(a, string_to_increment("D")), string_to_increment("L"));

	cout << "a pos: " << a.first << "  " << a.second << endl;
	cout << "b pos: " << b.first << "  " << b.second << endl;
	//assert(false);
}

//vector<pair<int, int>>


void one_rope_step(vector<pair<int, int>> &rope_links, map<pair<int, int>, bool> &visited, string direction) {

	rope_links[0] = sum_pairs(rope_links[0], string_to_increment(direction));

	for (int i = 1; i < rope_links.size(); ++i)
	{
		pair<int, int> headpos = rope_links[i-1];
		pair<int, int> tailpos = rope_links[i];

		if (!touching(headpos, rope_links[i])) {

			rope_links[i] = find_closest_adjacent(rope_links[i-1], rope_links[i]);
			//rope_links[i] = prev_rope_links[i-1];
			//cout << prev_headpos.first << "  " << prev_headpos.second << endl;

			if (i == rope_links.size()-1) {
				visited[rope_links[i]] = true;
			}
		}
	}
}


void graph(vector<pair<int, int>> rope_links) {
	for (int i = 20; i > -20; --i)
	{
		for (int k = -20; k < 20; ++k)
		{
			pair<int, int> a;
			a.first = k;
			a.second = i;
			if (find(rope_links.begin(), rope_links.end(), a) != rope_links.end()) {
				if ((find(rope_links.begin(), rope_links.end(), a)-rope_links.begin()) == 0) {
					cout << "H";
				}
				else {
					cout << (find(rope_links.begin(), rope_links.end(), a)-rope_links.begin());
				}
			}
			
			else {
				cout << ".";
			}
		}
		cout << endl;
	}
	cout << endl << endl;
}

const int ROPE_SIZE = 10;
const int TAIL = 9;

int main() {

	vector<string> input = slurp();
	
	// pair<int, int> headpos = {0, 0};
	// pair<int, int> tailpos = {0, 0};

	vector<pair<int, int>> rope_links;
	for (int i = 0; i < ROPE_SIZE; ++i)
	{
		rope_links.push_back({0, 0});
	}

	map<pair<int, int>, bool> visited;
	visited[{0,0}] = true;

	// cout << sum_pairs(headpos, tailpos).first << "  " << sum_pairs(headpos, tailpos).second << endl;
	// cout << string_to_increment("R").first <<
	

	for (int i = 0; i < input.size(); i+=2)
	{
		string direction = input[i];
		int steps = stoi(input[i+1]);

		for (int k = 0; k < steps; ++k)
		{

			//cout << "step" << endl;
			one_rope_step(rope_links, visited, direction);

			// graph(rope_links);

			// pair<int, int> prev_headpos = headpos;
			// headpos = sum_pairs(headpos, string_to_increment(direction));
			// if (!touching(headpos, tailpos)) {
			// 	tailpos = prev_headpos;
			// 	visited[tailpos] = true;
			// }
		}
		//graph(rope_links);
	}

	cout << "num visited: " << visited.size() << endl;




	//4580
	//4581

	/*

	What took so long:
	(A summary)

	Making the assumption that diagonal movements were not possible led me
	down the wrong path for way too long. Working with the easy example input
	from the start would have helped tremendously. Also, working through an 
	example and really verifying that the movement wasn't possible. 



	*/


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
