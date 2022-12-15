#include <bits/stdc++.h>

using namespace std;

vector<string> slurp();
vector<string> split(string s, string delimiter);
vector<int> vtoi(vector<string> v);
void print(vector<string> v);
void print(vector<int> v) ;

void move(vector<vector<string>> &crates, int num, int a, int b) {
	vector<string> temp;
	for (int i = 0; i < num; ++i)
	{
		temp.push_back(crates[a].back());
		crates[a].pop_back();
	}
	reverse(temp.begin(), temp.end());
	for (int i = 0; i < temp.size(); ++i)
	{
		crates[b].push_back(temp[i]);
	}
}

int main() {

	vector<string> input = slurp();


	for (int i = 0; i < input.size(); ++i)
	{
		if (input[0] == "move")
			break;
		input.erase(input.begin());
	}

	vector<vector<string>> crates = {
		{"S", "C", "V", "N"},
		{"Z", "M", "J", "H", "N", "S"},
		{"M", "C", "T", "G", "J", "N", "D"},
		{"T", "D", "F", "J", "W", "R", "M"},
		{"P", "F", "H"},
		{"C", "T", "Z", "H", "J"},
		{"D", "P", "R", "Q", "F", "S", "L", "Z"},
		{"C", "S", "L", "H", "D", "F", "P", "W"},
		{"D", "S", "M", "P", "F", "N", "G", "Z"}};

	for (int i = 0; i < crates.size(); ++i)
	{
		print(crates[i]);
	}
	cout << endl << endl;
	

	for (int i = 0; i < input.size(); i+=6)
	{

		//cout << input[i+1] << "  " << input[i+3] << "  " << input[i+5] << endl;
		move(crates, stoi(input[i+1]), stoi(input[i+3])-1, stoi(input[i+5])-1);
	}

	cout << endl << endl;
	for (int i = 0; i < crates.size(); ++i)
	{
		print(crates[i]);
	}
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
