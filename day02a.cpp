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
		input.push_back((int)x);
		if (cin.eof()) {
			break;
		}
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
		score += input[i+1]+1;
		if (input[i] == input[i+1])
			score += 3;
		
		if (input[i] == (input[i+1]+2)%3)
			score += 6;
	}

	cout << "score: " << score << endl;
}
