#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, q, a[maxn];
ll pre[maxn];

int main(){
	scanf("%d %d", &n, &q);
	for(int i = 1; i<=n; i++) scanf("%d", &a[i]), pre[i] = a[i] + pre[i-1];
	while(q--){
		int l, r;
		scanf("%d %d", &l, &r);
		printf("%lld\n", pre[r] - pre[l-1]);
	}
	return 0;
}

