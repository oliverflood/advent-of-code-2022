#include <bits/stdc++.h>

using namespace std;

vector<string> slurp();
vector<string> split(string s, string delimiter);
vector<int> vtoi(vector<string> v);
void print(vector<string> v);
void print(vector<int> v) ;
bool subset(vector<int> v);



int main() {

	// file i/o setup
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	vector<string> input = slurp();


	vector<vector<int>> tasks;

	// get our task input into a vector
	for (int i = 0; i < input.size(); ++i)
	{
		replace(input[i].begin(), input[i].end(), ',', '-');
		vector<int> quad = vtoi(split(input[i], "-"));
		tasks.push_back(quad);
	}


	// count subset tasks
	int ans = 0;

	for (int i = 0; i < tasks.size(); ++i)
	{
		if (subset(tasks[i]))
			ans++;
	}

	cout << "ans: " << ans << endl;

}



// checks if one one task is contained within another
bool subset(vector<int> v) {
	if (min(v[0], v[2]) == v[2] && max(v[1], v[3]) == v[3])
		return true;

	if (min(v[0], v[2]) == v[0] && max(v[1], v[3]) == v[1])
		return true;
	
	return false;
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
