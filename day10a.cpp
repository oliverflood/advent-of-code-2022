#include <bits/stdc++.h>

using namespace std;

// I know I need to make a header + implementation file aaaaaaa
vector<string> slurp();
vector<string> split(string s, string delimiter);
vector<int> vtoi(vector<string> v);
void print(vector<string> v);
void print(vector<int> v) ;


int main() {

	vector<string> input = slurp();
	long long x = 1;
	long long signal = 0;

	print(input);

	for (int i = 0; i < input.size(); ++i)
	{
		// i+1-th cycle
		//cout << "start of " << (i+1) << "th cycle" << endl;
		if ((i+1)%40 == 20) {
			signal += (i+1)*x;
			cout << "i: " << i << endl;
			cout << "x: " << x << endl;
			cout << "signal: " << (i*x) << endl << endl;
		}
		// after i+1-th cycle
		//cout << "end of " << (i+1) << "th cycle" << endl;
		if (isdigit(input[i][0]) || input[i][0] == '-') {
			x += stoll(input[i]);
		}

		
	}

	cout << "ans: " << signal << endl;

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
		cout << v[i] << endl;
	}
	cout << endl;
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
