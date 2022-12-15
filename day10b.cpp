#include <bits/stdc++.h>

using namespace std;

vector<string> slurp();
vector<string> split(string s, string delimiter);
vector<int> vtoi(vector<string> v);
void print(vector<string> v);
void print(vector<int> v) ;


void print_image(vector<vector<bool>> image) {
	for (int i = 0; i < image.size(); ++i)
	{
		for (int k = 0; k < image[i].size(); ++k)
		{
			if (image[i][k])
				cout << "#";
			else
				cout << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main() {

	vector<string> input = slurp();
	long long x = 1;
	long long signal = 0;

	vector<vector<bool>> image;
	vector<bool> temp;
	for (int i = 0; i < 40; ++i)
	{
		temp.push_back(0);
	}
	for (int i = 0; i < 6; ++i)
	{
		image.push_back(temp);
	}


	//print(input);

	for (int i = 0; i < input.size(); ++i)
	{
		// i+1-th cycle
		//cout << "start of " << (i+1) << "th cycle" << endl;
		int row = ((i)/40);
		int position = i;

		if (abs((i%40) - x) <= 1) {
			image[row][i%40] = 1;
		}
		if ((i+1)/40) {
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


	print_image(image);


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
