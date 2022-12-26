#include <bits/stdc++.h>
#include "cpplite.h"

using namespace std;

#define ll long long

/*
g++ day25a.cpp cpplite.cpp -o day25a.exe -std=c++1z
*/

const int SNAFU_BASE = 5;

map<char, ll> snafu_to_decimal_map = {{'0', 0}, {'1', 1}, {'2', 2}, {'-', -1}, {'=', -2}};
map<ll, string> decimal_to_snafu_map = {{0, "0"}, {1, "1"}, {2, "2"}, {-1, "-"}, {-2, "="}};

// convert from base snafu to base decimal
ll snafu_to_decimal(string s) {
	ll ans = 0;

	for (ll i = s.size()-1; i >= 0; --i)
		ans += (ll)pow(SNAFU_BASE, i) * snafu_to_decimal_map[s.at(s.size()-i-1)];
	
	return ans;
}

// convert from base decimal to base snafu
string decimal_to_snafu(ll n) {

	ll power = ceil(log(n)/log(5));
	string ans = "";

	bool nonzero_seen = false;

	while (power >= 0) {
		ll magic_num = floor((double)(n+((double)pow(SNAFU_BASE, power)/2))/(pow(SNAFU_BASE, power)));

		if (magic_num >= -2 && magic_num <= 2 && magic_num != 0) {
			nonzero_seen = true;
			ans += decimal_to_snafu_map[magic_num];
			n -= magic_num * pow(SNAFU_BASE, power);
		}
		else if (nonzero_seen) {
			ans += "0";
		}
		power--;
	}

	return ans;
}



int main() {

	vector<string> input = slurp();

	ll ans = 0;

	for (int i = 0; i < input.size(); ++i)
	{
		cout << snafu_to_decimal(input[i]) << endl;
		ans += snafu_to_decimal(input[i]);
	}

	cout << "\n\nans in decimal: " << ans << endl;

	cout << "ans in snafu: " << decimal_to_snafu(ans) << endl;
	
}


