#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e3+5;
char s[maxn][maxn];
int n, q, dp[maxn][maxn];

int main(){
	scanf("%d %d", &n, &q);
	for(int i = 1; i<=n; i++) {
		scanf("%s", s[i] + 1);
		for(int j = 1; j<=n; j++) {
			dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1] + (s[i][j] == '*');
		}
	}
	while (q--) {
		int x1, y1, x2, y2;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		printf("%d\n", dp[x2][y2] - dp[x1-1][y2] - dp[x2][y1-1] + dp[x1-1][y1-1]);
	}
	return 0;
}

