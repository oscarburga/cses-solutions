#include <bits/stdc++.h>
using namespace std;
const int maxn = 105, maxs = 1e6+5, mod = 1e9+7;

int add(int x, int y) { return (x+y) % mod; }
int n, x, a[maxn], dp[maxs];

int main(){
	scanf("%d %d", &n, &x);
	for(int i = 1; i<=n; i++) scanf("%d", &a[i]);
	dp[0] = 1;
	for(int s = 1; s<=x; s++){
		for(int i = 1; i<=n; i++){
			if (s>=a[i]) dp[s] = add(dp[s], dp[s-a[i]]);
		}
	}
	printf("%d\n", dp[x]);

	return 0;
}
