#include <bits/stdc++.h>

using namespace std;

vector<string> slurp();
vector<string> split(string s, string delimiter);
vector<int> vtoi(vector<string> v);
void print(vector<string> v);
void print(vector<int> v) ;


// prints vector
void print(vector<long long> v) {
	for (int i = 0; i < v.size(); ++i)
	{
		cout << v[i] << " ";
	}
	cout << endl;
}

long long total = 0;

void update_sizes(map<string, long long> &dirmap, vector<string> stack, long long dirsize) {
	// cout << "updating sizes: ";
	// print(stack);
	for (int i = 0; i < stack.size(); ++i)
	{
		// dirmap.at(stack[i]) += dir_size;
		dirmap[stack[i]] += dirsize;
	}
}

const string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
 
std::string trim(const std::string &s) {
    return rtrim(ltrim(s));
}


int main() {

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	vector<vector<string>> input;
	
	vector<string> stack;
	map<string, long long> dirmap;

	while (true) {
		string s;
		getline(cin, s);

		if (s.size() == 0)
			break;
		
		// need trailing endline because of this stupid line of code
		// s.erase(s.length()-1);

		// vector<string> temp = split(s, " ");
		// if (temp[1] == "cd" && temp[2] != "..") {
		// 	dirmap.insert(std::map<string, long long>::value_type(temp, 0));
		// }

		input.push_back(split(s," "));
	}


	for (int i = 0; i < input.size(); ++i)
	{
		input[i][input[i].size()-1] = trim(input[i][input[i].size()-1]);
		//print(input[i]);
	}



	// vector<string> stack2;

	// for (int i = 0; i < input.size(); ++i)
	// {

	// 	if (input[i][1] == "cd" && input[i][2] != "..") {
	// 		stack.push_back(input[i][2]);
	// 		// stack2.push_back(input[i][2]);
	// 	}
	// 	else if (input[i][1] == "cd" && input[i][2] == "..") {
	// 		//cout << "-> popped:  " << (i+1) << "  " << stack[stack.size()-1] << endl;
	// 		if (dirmap[stack[stack.size()-1]] <= 100000){

	// 			// count(stack2.begin(), stack2.end(), stack[stack.size()-1]) == 0
	// 			if (true){
	// 				stack2.push_back(stack[stack.size()-1]);
	// 			}

	// 			cout << stack[stack.size()-1] << "  " << dirmap[stack[stack.size()-1]] << endl;
	// 			total += dirmap[stack[stack.size()-1]];
	// 			dirmap[stack[stack.size()-1]] = 0;
	// 		}
			
	// 		stack.pop_back();
	// 	}

	// 	else if (isdigit(input[i][0][0])) {
	// 		// print(stack);
	// 		// cout << stoll(input[i][0]) << endl;
	// 		update_sizes(dirmap, stack, stoll(input[i][0]));
	// 	}
	// 	//cout << endl;
	// }

	// cout << "REMAINING STACK:" << endl;
	// print(stack);

	// for (int i = 0; i < stack.size(); ++i)
	// {
	// 	cout << dirmap[stack[i]] << endl;
	// 	if (dirmap[stack[i]] <= 100000)
	// 		total += dirmap[stack[i]];
	// }


	// long long ans = 0;

	// for (auto &e: dirmap) {
	// 	assert(e.second >= 0);
	// 	if (e.second <= 100000){
	// 		ans += e.second;
	// 	}
    //     // cout << '{' << e.first << ", " << e.second << '}';
    //     // if (e.second <= 100000){
    //     // 	cout << "  <-----------";
    //     // }
    //     // cout << endl;
    // }

    // // for (int i = 0; i < stack2.size(); ++i)
    // // {
    // // 	assert(dirmap[stack2[i]] > 0);
    // // }

    // cout << endl << endl;
    // print(stack2);

    // cout << "\nans: " << ans << endl;
    // cout << "total: " << total << endl;



	vector<long long> stack3;
	vector<long long> stack4;

	int current_min = 70000000;

	stack3.push_back(0);

	for (int i = 0; i < input.size(); ++i)
	{

		if (input[i][1] == "cd" && input[i][2] != "..") {
			stack3.push_back(0);
		}

		else if (input[i][1] == "cd" && input[i][2] == "..") {
			if (stack3[stack3.size()-1] >= 3562874 && stack3[stack3.size()-1] < current_min) {
				current_min = stack3[stack3.size()-1];
			}
			stack4.push_back(stack3[stack3.size()-1]);
			stack3.pop_back();
		}

		else if (isdigit(input[i][0][0])) {
			for (int k = 0; k < stack3.size(); ++k)
			{
				stack3[k] += stoll(input[i][0]);
			}
		}
	}

	for (int i = 0; i < stack3.size(); ++i)
	{
		if (stack3[i] >= 3562874 && stack3[i] < current_min) {
			current_min = stack3[i];
		}
		stack4.push_back(stack3[i]);
	}

	print(stack4);

	for (int i = 0; i < stack4.size(); ++i)
	{
		if (stack4[i] < 3562874) {
			stack4[i] = 100000000;
		}
	}

	long long minimum = 100000000;
	for (int i = 0; i < stack4.size(); ++i)
	{
		if (stack4[i] < minimum)
			minimum = stack4[i];
	}

	print(stack4);


	cout << "total space used: " << stack3[0] << endl;
	cout << "total space unused: " << (70000000-stack3[0]) << endl;
	cout << "total extra space needed: " << (30000000-(70000000-stack3[0])) << endl;
	cout << "current_min: " << current_min << endl;
	cout << "minimum: " << minimum << endl;






















    // 1104798 too low
    // 1104798

    // 1176650 too low

    // 1253583

    // 1740349
    // 1813752
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
	// cout << endl;
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
