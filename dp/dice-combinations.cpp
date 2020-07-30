#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6+10, mod = 1e9+7;

int add(int x, int y) { return (x+y)%mod; }
int n, dp[maxn];

int main(){
	scanf("%d", &n);
	dp[0] = 1;
	for(int i = 0; i<n; i++){
		for(int j = 1; j<=6; j++) dp[i+j] = add(dp[i+j], dp[i]);
	}
	printf("%d\n", dp[n]);
	return 0;
}
