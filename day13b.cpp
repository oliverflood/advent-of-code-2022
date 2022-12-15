#include <bits/stdc++.h>

using namespace std;

// I know I need to make a header + implementation file aaaaaaa
vector<string> slurp();
vector<string> split(string s, string delimiter);
vector<int> vtoi(vector<string> v);
void print(vector<string> v);
void print(vector<int> v) ;


const string REMOVE = " \n\r\t\f\v";

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


bool is_int(string s) {
	for (int i = 0; i < s.size(); ++i)
	{
		if (!isdigit(s.at(i))) 
			return false;
	}

	return true;
}


vector<string> convert(string s) {
	vector<string> result;

	// case empty
	if (s == "[]") {
		return result;
	}

	// other cases
	for (int i = 1; i < s.size(); ++i)
	{
		string curr_char = s.substr(i, 1);

		if (isdigit(curr_char.at(0))) {
			// case 10
			if (isdigit(s.substr(i+1, 1)[0])) {
				result.push_back("10");
				i++;
			}
			// case 1-9
			else {
				result.push_back(curr_char);
			}
		}

		else if (curr_char == "[") {
			vector<int> stack;
			int end;

			// should be a function
			for (int k = i+1; k < s.size(); ++k)
			{
				if (s.at(k) == '[') {
					stack.push_back(0);
				}
				if (s.at(k) == ']') {
					if (stack.size() == 0) {
						end = k;
						break;
					}
					else {
						stack.pop_back();
					}
				}
			}

			result.push_back(s.substr(i, end - i + 1));
			i += end - i + 1;

			//[[1,[2]]]
			//0123456789
		}
	}
}


int compare(string left, string right) {

	if (is_int(left) && is_int(right)) {
		if (stoi(left) < stoi(right))
			return 1;
		if (stoi(left) > stoi(right))
			return 0;
		return -1;
	}

	if (is_int(left)) {
		string s = "[" + left + "]";
		return compare(s, right);
	}

	if (is_int(right)) {
		string s = "[" + right + "]";
		return compare(left, s);
	}

	// convert to lists
	vector<string> left_list = convert(left);
	vector<string> right_list = convert(right);

	// empty list cases
	if (left_list.size() == 0 && right_list.size() != 0)
		return 1;
	if (right_list.size() == 0 && left_list.size() != 0)
		return 0;

	// cout << "comparing: " << endl;
	// cout << "left_list: "; 
	// print(left_list);
	// cout << "right_list: ";
	// print(right_list);


	int i = 0;
	while (true) {
		// check for running out of items
		if (i == left_list.size() && i < right_list.size()){ // case left list runs out
			return 1;
			break;
		}
		if (i == right_list.size() && i < left_list.size()) { // case right list runs out
			return 0;
			break;
		}
		if (i == right_list.size() && i == left_list.size()) { // case both run out
			break;
		}

		int result = compare(left_list[i], right_list[i]);

		// if conclusive then return
		if (result == 1 || result == 0)
			return result;

		i++;
	}

	return -1; // inconclusive
}


int main() {

	vector<string> input = slurp();
	vector<string> extra = {"[[2]]", "[[6]]"};

	input.push_back(extra[0]);
	input.push_back(extra[1]);
	
	sort(input.begin(), input.end(), compare);

	// print(input);
	int ans = find(input.begin(), input.end(), extra[0])-input.begin() + 1;
	ans *= find(input.begin(), input.end(), extra[1])-input.begin() + 1;

	cout << "ans: " << ans << endl;

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
