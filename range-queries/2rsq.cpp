#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, q, a[maxn];
ll ft[maxn];

void upd(int pos, int val) {
	while(pos <= n) ft[pos] += val, pos += pos & (-pos);
}

ll query(int pos) {
	ll ret = 0;
	while(pos > 0) ret += ft[pos], pos &= pos-1;
	return ret;
}

int main(){
	scanf("%d %d", &n, &q);
	for(int i = 1; i<=n; i++) scanf("%d", &a[i]), upd(i, a[i]);
	while(q--){
		int t, k, u;
		scanf("%d %d %d", &t, &k, &u);
		if (t == 1) upd(k, u - (query(k) - query(k-1)));
		else printf("%lld\n", query(u) - query(k-1));
	}
	return 0;
}

