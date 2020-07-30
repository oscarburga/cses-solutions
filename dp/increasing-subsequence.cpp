#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5+5;
int n, a[maxn], dp[maxn];

int main(){
	scanf("%d", &n);
	for(int i = 0; i<n; i++) scanf("%d", &a[i]);
	fill(dp, dp+maxn, int(1e9+5));
	dp[0] = 0;
	for(int i = 0; i<n; i++){
		auto it = lower_bound(dp, dp+maxn, a[i]);
		*it = min(*it, a[i]);
	}
	for(int i = maxn-1; i>0; i--){
		if (dp[i] < 1e9) { printf("%d\n", i); return 0; }
	}
	return 0;
}
