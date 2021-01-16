#include <bits/stdc++.h>
using namespace std;
using ll = long long;

string s;
ll dp[2][20][11][2];

ll solve(bool started, int i, int last, bool smaller) {
	if (i == s.size()) return started;
	ll &ret = dp[started][i][last][smaller];
	if (ret != -1) return ret;
	ret = last != 0 ? solve(started, i+1, started ? 0 : 10, smaller || ('0' < s[i])) : 0;
	int lim = smaller ? 9 : s[i]-'0';
	for(int d = 1; d <= lim; d++) if (d != last) {
		ret += solve(1, i+1, d, smaller || (d < s[i] - '0'));
	}
	return ret;
}

int main(){
	ll x, y;
	cin >> x >> y;
	x--;
	memset(dp, -1, sizeof(dp));
	s = to_string(y);
	ll ans = solve(0, 0, 10, 0);
	if (x >= 0) {
		memset(dp, -1, sizeof(dp));
		s = to_string(x);
		ans -= solve(0, 0, 10, 0);
	} else ans++;
	printf("%lld\n", ans);
	return 0;
}

