#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e3+5;

char s[maxn], t[maxn];
int n, m, dp[maxn][maxn];

int main(){
	scanf("%s", s+1);
	scanf("%s", t+1);
	n = strlen(s+1), m = strlen(t+1);
	for(int i = 1; i<=n; i++) dp[i][0] = i;
	for(int i = 1; i<=m; i++) dp[0][i] = i;
	for(int i = 1; i<=n; i++){
		for(int j = 1; j<=m; j++){
			dp[i][j] = dp[i-1][j-1] + (s[i] != t[j]);
			dp[i][j] = min(dp[i][j], min(dp[i-1][j], dp[i][j-1]) + 1);
		}
	}
	printf("%d\n", dp[n][m]);

	return 0;
}
