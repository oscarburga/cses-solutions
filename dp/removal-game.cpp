#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5e3+5;

int n, a[maxn];
ll pre[maxn], dp[maxn][maxn][2];

ll getsum(int l, int r){ return pre[r] - pre[l-1]; }

ll solve(int l, int r, bool t){
	if (l == r) return a[l];
	if (dp[l][r][t] != -1) return dp[l][r][t];
	ll s = getsum(l, r) - min(solve(l+1, r, t^1), solve(l, r-1, t^1));
	return dp[l][r][t] = s;
}

int main(){
	memset(dp, -1, sizeof(dp));
	scanf("%d", &n);
	for(int i = 1; i<=n; i++) scanf("%d", &a[i]);
	for(int i = 1; i<=n; i++) pre[i] = pre[i-1] + a[i];
	printf("%lld\n", solve(1, n, 1));
	return 0;
}
