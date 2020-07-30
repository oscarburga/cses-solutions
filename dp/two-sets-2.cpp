#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 505, maxs = (maxn*(maxn+1))/2, mod = 1e9+7;

int add(int x, int y) { return (x+y) % mod; }
int mul(ll x, ll y) { return (x*y) % mod; }
int n, dp[maxs];

int fpow(ll a, int b){
	ll res = 1;
	while(b > 0){
		if (b&1) res = mul(res, a);
		a = mul(a, a);
		b >>= 1;
	}
	return int(res);
}

int main(){
	scanf("%d", &n);
	dp[0] = 1;
	int lim = (n * (n+1))/2;
	if (lim%2) { puts("0"); return 0; }
	for(int i = 1; i<=n; i++){
		for(int s = (i*(i+1))/2; s>=i; s--) dp[s] = add(dp[s], dp[s-i]);
	}
	printf("%d\n", mul(dp[lim/2], fpow(2, mod-2)));
	return 0;
}
