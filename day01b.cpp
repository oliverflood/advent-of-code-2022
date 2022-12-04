#include <bits/stdc++.h>

using namespace std;

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

int pop_max(vector<int>& v) {
  int max_index = 0;
  for (int i = 0; i < v.size(); ++i)
  {
    if (v[i] > v[max_index]) {
      max_index = i;
    }
  }
  int ans = v[max_index];

  v.erase(v.begin()+max_index);
  return ans;
}


int main() {

	// file i/o setup
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	vector<int> v;
	string str = "";
	int num = 0;
	int max = 0;

	// spaghetti code i dont remember
	// (going back to comment code but idk whats going on here)
	while (true)
	{
		getline(cin, str);

		if (!isdigit(str[0])) {
			v.push_back(num);
			if (num > max)
				max = num;
			
			num = 0;
			continue;
		}
		num += stoi(str);

		if (!str.empty() && str[str.length()-1] == '\n') {
			str.erase(str.length()-1);
		}

		if (cin.eof())
			break;
	}

	int ans = 0;
	for (int i = 0; i < 3; ++i)
	{
		ans += pop_max(v);
	}

	cout << "max: " << max << endl;
	cout << "sum of top 3: " << ans << endl;
}
