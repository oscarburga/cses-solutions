#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e3+5, maxs = 1e5+5, inf = 1e8;
int n, x, a[maxn], v[maxn], dp[maxs];

int main(){
	scanf("%d %d", &n, &x);
	for(int i = 1; i<=n; i++) scanf("%d", &a[i]);
	for(int i = 1; i<=n; i++) scanf("%d", &v[i]);
	for(int i = 1; i<=n; i++){
		for(int s = x; s>=a[i]; s--) dp[s] = max(dp[s], dp[s-a[i]] + v[i]);
	}
	printf("%d\n", dp[x]);
	return 0;
}
