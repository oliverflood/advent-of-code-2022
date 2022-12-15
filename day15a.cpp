#include <bits/stdc++.h>

using namespace std;

// I know I need to make a header + implementation file aaaaaaa
vector<string> slurp();
vector<string> split(string s, string delimiter);
vector<int> vtoi(vector<string> v);
void print(vector<string> v);
void print(vector<int> v) ;

const string REMOVE = " \n\r\t\f\vxy=,:";

string ltrim(const string &s)
{
	size_t start = s.find_first_not_of(REMOVE);
	return (start == std::string::npos) ? "" : s.substr(start);
}
string rtrim(const string &s)
{
	size_t end = s.find_last_not_of(REMOVE);
	return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
string trim(const string &s) {
	return rtrim(ltrim(s));
}


bool compare(pair<int, int> a, pair<int, int> b) {
	return (a.first < b.first);
}

void interval_union(vector<pair<int, int>> &intervals) {
	for (int i = 0; i < intervals.size(); ++i)
	{
		if (i+1 >= intervals.size())
			break;
		if (intervals[i+1].first <= intervals[i].second) {

			if (intervals[i+1].second > intervals[i].second)
				intervals[i].second = intervals[i+1].second;

			intervals.erase(intervals.begin()+i+1);
			i--;
			
		}
	}
}

const int Y_VALUE = 2000000;

int main() {

	vector<string> input = slurp();

	vector<pair<int, int>> sensors;
	vector<int> distances;

	long long ans = 0;

	for (int i = 0; i < input.size(); i+=10)
	{
		//cout << trim(input[i+2]) << "  " << trim(input[i+3]) << endl;
		sensors.push_back({stoi(trim(input[i+2])), stoi(trim(input[i+3]))});
		pair<int, int> beacon = {stoi(trim(input[i+8])), stoi(trim(input[i+9]))};

		// account for beacons in the far future on our line
		// if (beacon.second == Y_VALUE){
		// 	ans--;
		// }

		cout << "beacon: " << beacon.first << "  " << beacon.second << endl;
		distances.push_back(abs(beacon.first-sensors[sensors.size()-1].first) + abs(beacon.second-sensors[sensors.size()-1].second));
	}

	for (int i = 0; i < sensors.size(); ++i)
	{
		cout << i << ": " << sensors[i].first << "  " << sensors[i].second << endl;
	}

	//print(distances);

	vector<pair<int, int>> intervals;

	// compute intervals across y stripe
	for (int i = 0; i < sensors.size(); ++i)
	{
		int range = distances[i] - abs(Y_VALUE-sensors[i].second);

		// check range
		if (range < 0)
			continue;

		intervals.push_back({sensors[i].first-range, sensors[i].first+range});
	}

	sort(intervals.begin(), intervals.end(), compare);
	for (int i = 0; i < intervals.size(); ++i)
	{
		cout << i << ": " << intervals[i].first << "  " << intervals [i].second << endl;
	}

	interval_union(intervals);

	cout << "ans: " << ans << endl;


	for (int i = 0; i < intervals.size(); ++i)
	{
		ans += abs(intervals[i].first-intervals[i].second) + 1;
		cout << i << ": " << intervals[i].first << "  " << intervals [i].second << endl;
	}

	// account for one beacon at 2000000 already :P
	ans--;

	cout << "ans: " << ans << endl;
	//4724222 too low
	//4724242 too high
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

	while(true)
	{
		if (s.find(delimiter, pos1) == string::npos) {
			v.push_back(s.substr(pos1, s.size()-pos1-1));
			break;
		}
		int pos2 = s.find(delimiter, pos1);
		v.push_back(s.substr(pos1, pos2-pos1));
		pos1 = pos2+delimiter.size();

	}

	return(v);
}
