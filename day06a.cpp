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

bool same_char(string s) {
	//cout << "str: " << s << "    ";
	for (int i = 0; i < s.size(); ++i)
	{
		if (count(s.begin(), s.end(), s.at(i)) >= 2) {
			//cout << s.at(i) << endl;
			return true;
		}
	}
	//cout << endl;

	return false;
}

int main() {

	vector<string> input = slurp();

	string s = input[0];

	cout << s << endl << endl;

	for (int i = 0; i < s.size(); ++i)
	{
		if (!same_char(s.substr(i, 4))) {
			cout << (i+4) << endl;
			break;
		}
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
