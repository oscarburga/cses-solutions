#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+5, maxm = 105, mod = 1e9+7;
int add(int x, int y) { return (x+y) % mod; }
int n, m, a[maxn], dp[maxn][maxm];

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 0; i<n; i++) scanf("%d", &a[i]);
	if (a[0] == 0) fill(dp[0]+1, dp[0]+m+1, 1);
	else dp[0][a[0]] = 1;
	for(int i = 1; i<n; i++){
		if (a[i] == 0) {
			for(int j = 1; j<=m; j++) 
				for(int x = -1; x<=1; x++) 
					dp[i][j] = add(dp[i][j], dp[i-1][j+x]);
		} else {
			for(int x = -1; x<=1; x++) 
				dp[i][a[i]] = add(dp[i][a[i]], dp[i-1][a[i]+x]);
		}
	}
	int s = 0;
	for(int i = 1; i<=m; i++) s = add(s, dp[n-1][i]);
	printf("%d\n", s);
	return 0;
}
