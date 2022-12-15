#include <bits/stdc++.h>

using namespace std;

vector<string> slurp();
vector<string> split(string s, string delimiter);
vector<int> vtoi(vector<string> v);
void print(vector<string> v);
void print(vector<int> v) ;

const int SIZE = 99;

// returns length of single line of visibility to tree given x,y position and increment for x and y
int visibility_line_len(vector<vector<int>> trees, int x, int y, int x_inc, int y_inc) {
	int my_height = trees[x][y];
	int curr_x = x + x_inc;
	int curr_y = y + y_inc;

	int length = 0;

	while ((curr_x >= 0 && curr_x < SIZE) && (curr_y >= 0 && curr_y < SIZE))
	{
		length++;
		int curr_height = trees[curr_x][curr_y];

		if (curr_height >= my_height)
			break;

		curr_x += x_inc;
		curr_y += y_inc;
	}

	return length;
}

// calculates a tree's scenic score
int scenic_score(vector<vector<int>> trees, int x, int y) {
	return  (visibility_line_len(trees, x, y, 1, 0) 
			*visibility_line_len(trees, x, y, -1, 0)
			*visibility_line_len(trees, x, y, 0, 1) 
			*visibility_line_len(trees, x, y, 0, -1));
}

int main() {

	vector<string> input = slurp();
	vector<vector<int>> trees;

	for (int i = 0; i < input.size(); ++i)
	{
		vector<int> temp;
		trees.push_back(temp);

		for (int k = 0; k < input[i].size(); ++k)
		{
			trees[i].push_back(int(input[i][k] - '0'));
		}
	}

	int max_scenic_score = 0;

	for (int i = 0; i < trees.size(); ++i)
	{
		//print(trees[i]);
		for (int k = 0; k < trees[i].size(); ++k)
		{
			int temp_scenic_score = scenic_score(trees, i, k);
			if (temp_scenic_score > max_scenic_score) 
				max_scenic_score = temp_scenic_score;
		}
	}

	cout << "max scenic score: " << max_scenic_score << endl;

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
