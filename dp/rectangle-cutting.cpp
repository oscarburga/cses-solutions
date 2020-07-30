#include <bits/stdc++.h>
using namespace std;

const int maxn = 505;
int n, m, dp[maxn][maxn];

int solve(int x, int y){
	if (x == y) return dp[x][y] = 0;
	if (dp[x][y] != -1) return dp[x][y];
	int mn = 1e9;
	for(int i = 1; i<x; i++) mn = min(mn, 1 + solve(i, y) + solve(x-i, y));
	for(int i = 1; i<y; i++) mn = min(mn, 1 + solve(x, i) + solve(x, y-i));
	return dp[x][y] = mn;
}

int main(){
	memset(dp, -1, sizeof(dp));
	scanf("%d %d", &n, &m);
	printf("%d\n", solve(n, m));
	return 0;
}
