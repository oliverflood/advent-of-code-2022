#include <bits/stdc++.h>

using namespace std;

vector<string> slurp();
vector<string> split(string s, string delimiter);
vector<int> vtoi(vector<string> v);
void print(vector<string> v);
void print(vector<int> v) ;

pair<int, int> pair_sum(pair<int, int> a, pair<int, int> b) {
	return {a.first+b.first, a.second+b.second};
}

int index(vector<vector<int>> graph, pair<int, int> pos) {
	// pos <x, y>

	// check bounds
	if (pos.second < 0 || pos.second >= graph.size())
		return -1;
	if (pos.first < 0 || pos.first >= graph[pos.second].size())
		return -1;

	return graph[pos.second][pos.first];

}


int main() {

	vector<string> input = slurp();
	vector<vector<int>> graph;
	pair<int, int> end;
	vector<vector<int>> distances;

	for (int i = 0; i < input.size(); ++i)
	{
		vector<int> temp;
		vector<int> temp2;
		for (int k = 0; k < input[i].size(); ++k)
		{
			if (input[i].at(k) == 'E') {
				end = {k, i}; 
				temp.push_back(25);
				continue;
			}
			temp2.push_back(-1);
			temp.push_back(input[i].at(k)-'a');
		}
		graph.push_back(temp);
		distances.push_back(temp2);
	}

	for (int i = 0; i < graph.size(); ++i)
	{
		print(graph[i]);
	}

	cout << "end: " << end.first << " " << end.second << endl;

	vector<pair<int, int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	vector<pair<int, int>> stack;

	stack.push_back(end);
	distances[end.second][end.first] = 0;



	while(stack.size() > 0) {
		pair<int, int> current = stack.back();
		stack.pop_back();
		int current_distance = distances[current.second][current.first];

		for (int i = 0; i < directions.size(); ++i)
		{
			pair<int, int> new_pos = pair_sum(current, directions[i]);

			// make sure new pos in bounds
			if (index(graph, new_pos) == -1)
				continue;

			// make sure new pos not yet considered
			if (distances[new_pos.second][new_pos.first] != -1)
				continue;

			int new_pos_height = graph[new_pos.second][new_pos.first];

			// consider the node if we are within height bounds
			if (new_pos_height + 1 >= graph[current.second][current.first]) {
				stack.insert(stack.begin(), new_pos);
				distances[new_pos.second][new_pos.first] = current_distance + 1;
				if (graph[new_pos.second][new_pos.first] == 0) {
					cout << "answer: " << distances[new_pos.second][new_pos.first] << endl;
					cout << new_pos.first << "  " << new_pos.second << endl;
					exit(0);
				}
			}
		}

		// for (int i = 0; i < distances.size(); ++i)
		// {
		// 	print(distances[i]);
		// }
		// cout << "\n\n\n\n";
	}

	// for (int i = 0; i < distances.size(); ++i)
	// {
	// 	print(distances[i]);
	// }

	//cout << "answer: " << distances[end.second][end.first] << endl;

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

    for (int i = 0; i < count(s.begin(), s.end(), delimiter.at(0))+1; ++i)
    {
        
        int pos2 = s.find(delimiter, pos1);
        v.push_back(s.substr(pos1, pos2-pos1));
        pos1 = pos2+1;
    }

    return(v);
}
