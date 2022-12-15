#include <bits/stdc++.h>

using namespace std;

// I know I need to make a header + implementation file aaaaaaa
vector<string> slurp();
vector<string> split(string s, string delimiter);
vector<int> vtoi(vector<string> v);
void print(vector<string> v);
void print(vector<int> v) ;


const string REMOVE = " \n\r\t\f\v,";

string ltrim(const std::string &s)
{
	size_t start = s.find_first_not_of(REMOVE);
	return (start == std::string::npos) ? "" : s.substr(start);
}
string rtrim(const std::string &s)
{
	size_t end = s.find_last_not_of(REMOVE);
	return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
string trim(const std::string &s) {
	return rtrim(ltrim(s));
}


// void run_item(vector<int> &monkey_counts, int item, int pos) {
// 	for (int i = 0; i < 20; ++i)
// 	{
// 		if (pos == 0) {
// 			monkey_counts[pos]++;
// 			item *= 19;
// 			item /= 3;

// 			if (item % 23 == 0)
// 				pos = 2;
// 			else 
// 				pos = 3;
// 		}
// 		if (pos == 1) {
// 			monkey_counts[pos]++;
// 			item += 6;
// 			item /= 3;

// 			if (item % 19 == 0)
// 				pos = 2;
// 			else 
// 				pos = 0;
			
// 		}
// 		if (pos == 2) {
// 			monkey_counts[pos]++;
// 			item *= item;
// 			item /= 3;

// 			if (item % 13 == 0)
// 				pos = 1;
// 			else 
// 				pos = 3;

// 		}
// 		if (pos == 3) {
// 			monkey_counts[pos]++;
// 			item += 3;
// 			item /= 3;

// 			if (item % 17 == 0)
// 				pos = 0;
// 			else 
// 				pos = 1;

// 		}
// 	}
// }

// FORGIVE ME FOR THIS ATROCITY!!!!!!!!!!
// i will come back and repair this later maybe probably
// (i am lazy)

#define ll long long
const int ROUNDS = 10000;

void run_item(vector<int> &monkey_counts, ll item, int pos) {
	for (int i = 0; i < ROUNDS; ++i)
	{
		if (pos == 0) {
			monkey_counts[pos]++;
			item *= 11;
			item %= 9699690;

			if (item % 2 == 0)
				pos = 7;
			else 
				pos = 4;
		}
		if (pos == 1) {
			monkey_counts[pos]++;
			item += 1;
			item %= 9699690;

			if (item % 13 == 0)
				pos = 3;
			else 
				pos = 6;
		}
		if (pos == 2) {
			monkey_counts[pos]++;
			item += 6;
			item %= 9699690;

			if (item % 3 == 0)
				pos = 1;
			else 
				pos = 6;
		}
		if (pos == 3) {
			monkey_counts[pos]++;
			item *= item;
			item %= 9699690;

			if (item % 17 == 0)
				pos = 7;
			else 
				pos = 0;
		}


		if (pos == 4) {
			monkey_counts[pos]++;
			item *= 7;
			item %= 9699690;

			if (item % 19 == 0)
				pos = 5;
			else 
				pos = 2;
		}
		if (pos == 5) {
			monkey_counts[pos]++;
			item += 8;
			item %= 9699690;

			if (item % 7 == 0)
				pos = 2;
			else 
				pos = 1;
		}
		if (pos == 6) {
			monkey_counts[pos]++;
			item += 5;
			item %= 9699690;

			if (item % 11 == 0)
				pos = 3;
			else 
				pos = 0;
		}
		if (pos == 7) {
			monkey_counts[pos]++;
			item += 7;
			item %= 9699690;

			if (item % 5 == 0)
				pos = 4;
			else 
				pos = 5;
		}
	}
}

int main() {

	vector<string> input = slurp();

	//vector<int> monkey_counts = {0, 0, 0, 0};
	vector<int> monkey_counts = {0, 0, 0, 0, 0, 0, 0, 0};
	//vector<vector<int>> starting_items = {{79, 98}, {54, 65, 75, 74}, {79, 60, 97}, {74}};
	vector<vector<ll>> starting_items = {
											{89, 95, 92, 64, 87, 68},
											{87, 67},
											{95, 79, 92, 82, 60},
											{67, 97, 56},

											{80, 68, 87, 94, 61, 59, 50, 68},
											{73, 51, 76, 59},
											{92},
											{99, 76, 78, 76, 79, 90, 89}
										};


	for (int i = 0; i < starting_items.size(); ++i)
	{
		for (int k = 0; k < starting_items[i].size(); ++k)
		{
			run_item(monkey_counts, starting_items[i][k], i);
		}
	}

	cout << "monkey_counts: " << endl;
	print(monkey_counts);

	// 14123287936 too low

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
