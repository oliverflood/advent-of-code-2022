#include <bits/stdc++.h>

using namespace std;

vector<string> slurp2();


int main() {

	// file i/o setup
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	vector<string> input = slurp2();
	int score = 0;

	// do the thing
	for (int i = 0; i < input.size(); i+=2)
	{
		for (int k = 0; k < input[i].size(); ++k)
		{
			if (input[i+1].find(input[i].substr(k, 1)) != string::npos) {
				
				if (isupper(input[i].substr(k, 1)[0])) {
					score += (int)(input[i].substr(k, 1)[0]) - 38;
				}
				else {
					score += (int)(input[i].substr(k, 1)[0]) - 96;
				}

				break;
			}
		}
	}

	cout << "score: " << score << endl;
}

// slurps up file input from stdin
vector<string> slurp2() {
	vector<string> input;

	while (true) {
		string x;
		cin >> x;
		input.push_back(x.substr(0, x.size()/2));
		input.push_back(x.substr(x.size()/2, x.size()/2));
		if (cin.eof())
			break;
	}

	return input;
}