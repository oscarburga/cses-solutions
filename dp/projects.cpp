#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
const int maxn = 2e5+5, maxs = 4e5+5;
int n, len=1;
ll dp[maxs];
 
struct inter{
	int l, r, v;
	bool operator<(inter e) const { return r < e.r; }
} a[maxn];
 
int main(){
	scanf("%d", &n);
	for(int i = 1; i<=n; i++) scanf("%d %d %d", &a[i].l, &a[i].r, &a[i].v);
	a[0].r = -1;
	ll mx = 0;
	sort(a+1, a+n+1);
	for(int i = 1; i<=n; i++){
		dp[i] = dp[i-1];
		inter aux = {0, a[i].l, 0};
		int l = lower_bound(a, a+n, aux) - a - 1;
		dp[i] = max(dp[i], dp[l] + a[i].v);
		mx = max(mx, dp[i]);
	}

	printf("%lld\n", mx);
	return 0;
}
