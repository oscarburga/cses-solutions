#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, q, st[18][maxn];

int main(){
	scanf("%d %d", &n, &q);
	for(int i = 0; i<n; i++) scanf("%d", &st[0][i]);
	for(int k = 1; (1<<k) <= n; k++) {
		int d = 1<<(k-1), dis = 1<<k;
		for(int i = 0; i+dis<=n; i++) st[k][i] = min(st[k-1][i], st[k-1][i+d]);
	}
	while(q--){
		int l, r;
		scanf("%d %d", &l, &r);
		l--, r--;
		int k = 31 - __builtin_clz(r-l+1);
		printf("%d\n", min(st[k][l], st[k][r-(1<<k)+1]));
	}
	return 0;
}

