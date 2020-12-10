#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;

int n, q, a[maxn];
ll ft[maxn];
void upd(int pos, int val) {
	while (pos <= n) ft[pos] += val, pos += pos & (-pos);
}

ll query(int pos) {
	ll ret = 0;
	while (pos > 0) ret += ft[pos], pos &= pos-1;
	return ret;
}

int main(){
	scanf("%d %d", &n, &q);
	for(int i = 1; i<=n; i++) scanf("%d", &a[i]);
	while(q--) {
		int t;
		scanf("%d", &t);
		if (t == 1) {
			int a, b, u;
			scanf("%d %d %d", &a, &b, &u);
			upd(a, u);
			upd(b+1, -u);
		} else {
			int k;
			scanf("%d", &k);
			printf("%lld\n", query(k) + a[k]);
		}
	}
	return 0;
}

