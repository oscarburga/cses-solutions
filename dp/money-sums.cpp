#include <bits/stdc++.h>
using namespace std;

const int maxn = 105, maxs = maxn * int(1e3);

int n, a[maxn];
bitset<maxs> dp;

int main(){
	scanf("%d", &n);
	dp[0] = true;
	for(int i = 0; i<n; i++){
		int x;
		scanf("%d", &x);
		dp |= (dp<<x);
	}
	int cnt = dp.count(), cur = 0;
	printf("%d\n", --cnt);
	for(int i = 1; i<maxs; i++){
		if (dp[i]){
			cur++;
			printf("%d%c", i, " \n"[cur==cnt]);
			i += maxs * (cur == cnt);
		}
	}
	return 0;
}
