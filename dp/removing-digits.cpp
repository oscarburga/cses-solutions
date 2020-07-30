#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6+5, inf = 1e9;
int n, dp[maxn];

int main(){
	scanf("%d", &n);
	fill(dp, dp+maxn, inf);
	dp[n] = 0;
	for(int i = n; i>=0; i--){
		int x = i;
		while(x>0){
			int mod = x%10;
			dp[i-mod] = min(dp[i-mod], dp[i]+1);
			x/=10;
		}
	}
	printf("%d\n", dp[0]);

	return 0;
}
