#include <bits/stdc++.h>

using namespace std;

vector<string> slurp();
string common(string a, string b);



int main() {

	// file i/o setup
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	vector<string> input = slurp();
	int score = 0;
	
	// compute scores of common chars
	for (int i = 0; i < input.size(); i+=3)
	{
		string c = common(common(input[i], input[i+1]), input[i+2]);

		if (isupper(c[0]))
			score += (int)(c[0]) - 38;
		else
			score += (int)(c[0]) - 96;
	}

	cout << "score: " << score << endl;
}



// returns intersection of two strings (only one char)
string common(string a, string b) {
	string common = "";
	for (int k = 0; k < a.size(); ++k)
	{
		if (b.find(a.substr(k, 1)) != string::npos) {
			common += a.substr(k, 1);
		}
	}
	return common;
}


// slurps up file input from stdin
vector<string> slurp() {
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