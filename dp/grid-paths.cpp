#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e3+5, mod = 1e9+7;

int add(int x, int y) { return (x+y) % mod; }
char mat[maxn][maxn];
int n, dp[maxn][maxn];

int main(){
	scanf("%d", &n);
	for(int i = 1; i<=n; i++) scanf("%s", mat[i]+1);
	dp[1][1] = 1;
	for(int i = 1; i<=n; i++){
		for(int j = 1; j<=n; j++) {
			dp[i][j] = add(dp[i][j], add(dp[i-1][j], dp[i][j-1])) * (mat[i][j] == '.');
		}
	}
	printf("%d\n", dp[n][n]);
	return 0;
}
