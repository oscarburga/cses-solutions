#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 20, inf = 1e9+7;

bool vis[1<<maxn];
int n, W, a[maxn], dp[1<<maxn], w[1<<maxn];

int solve(int msk) {
	if (msk == 0) return 0;
	if (vis[msk]) return dp[msk];
	vis[msk] = true;
	int &ret = dp[msk] = n+1;
	int &curw = w[msk] = 0;
	for(int i = 0; i<n; i++) if ((msk>>i)&1) {
		int nxt = msk ^ (1<<i);
		int candc = solve(nxt), candw = w[nxt];
		if (candw + w[1<<i] > W) candc++, candw = 0;
		if (candc < ret) ret = candc, curw = candw + w[1<<i];
		else if (candc == ret) curw = min(curw, candw + w[1<<i]);
	}
	return ret;
}

int main(){
	scanf("%d %d", &n, &W);
	for(int i = 0; i<n; i++) scanf("%d", &w[1<<i]), dp[1<<i] = vis[1<<i] = true;
	printf("%d\n", solve((1<<n)-1));
	return 0;
}

