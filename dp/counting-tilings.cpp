#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
const int maxn = 1e3+5, maxm = 10, mod = 1e9+7;
 
int n, m, dp[maxn][1<<maxm];
 
inline int add(int x, int y) { return (x+y) % mod; }
inline void chadd(int &x, int y) { x = add(x, y); }
 
void solve(int i, int j, int msk, int nxt) {
	if (j == m) { 
		chadd(dp[i+1][nxt], dp[i][msk]); 
		return; 
	}
	if ((msk >> j) & 1) solve(i, j+1, msk, nxt);
	else {
		solve(i, j+1, msk, nxt | (1<<j));
		if (j+1 < m && ((msk>>(j+1))&1) == 0) solve(i, j+2, msk, nxt);
	}
}
 
int main(){
	scanf("%d %d", &n, &m);
	swap(n, m);
	dp[0][0] = 1;
	for(int i = 0; i < n; i++) {
		for(int msk = 0; msk < (1<<m); msk++) if (dp[i][msk] > 0) {
			solve(i, 0, msk, 0);
		}
	}
	printf("%d\n", dp[n][0]);
	return 0;
}
