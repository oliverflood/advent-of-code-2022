#include <bits/stdc++.h>

using namespace std;


int main() {

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	vector<int> input;
	int score = 0;

	while (true) {
		char x;
		cin >> x;
		if (cin.eof()) {
			break;
		}
		input.push_back((int)x);
	}

	// map input (A B C) or (X Y Z) to (0 1 2)
	for (int i = 0; i < input.size(); i++)
	{
		if (i % 2 == 1)
			input[i] = (int)(input[i]-23);
		input[i] = (int)(input[i]-65);
	}

	// do thing
	for (int i = 0; i < input.size(); i+=2)
	{
		// invariant
		score += input[i+1]*3;

		// lose case
		if (input[i+1] == 0)
			score += (input[i]+2)%3+1;

		// draw case
		if (input[i+1] == 1)
			score += input[i]+1;
		
		// win case
		if (input[i+1] == 2)
			score += (input[i]+1)%3+1;
	}

	cout << "score: " << score << endl;
}
