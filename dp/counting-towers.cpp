#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+5, mod = 1e9+7;

inline int add(int x, int y) { return (x+y) % mod; }
inline int mul(int x, int y) { return (1ll * x * y) % mod; }

int dp[maxn][2];

int main(){
	dp[1][0] = dp[1][1] = 1;
	for(int i = 2; i<maxn; i++) {
		dp[i][0] = add(mul(dp[i-1][0], 2), dp[i-1][1]);
		dp[i][1] = add(dp[i-1][0], mul(dp[i-1][1], 4));
	}
	int tc;
	scanf("%d", &tc);
	while(tc--) {
		int x;
		scanf("%d", &x);
		printf("%d\n", add(dp[x][0], dp[x][1]));
	}
	return 0;
}

