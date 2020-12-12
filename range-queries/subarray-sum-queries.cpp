#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;

struct node { ll pre = 0, suf = 0, all = 0, ans = 0; } st[4*maxn];

int n, m, a[maxn];

void make(node &ret, const node&L, const node&R) {
	ret.pre = max(L.pre, L.all + R.pre);
	ret.suf = max(R.suf, L.suf + R.all);
	ret.all = L.all + R.all;
	ret.ans = max({ L.ans, R.ans, L.suf + R.pre });
}

void make(node &ret, ll x) {
	ret.pre = ret.suf = ret.ans = max(x, 0ll);
	ret.all = x;
}

void build(int pos = 1, int l = 1, int r = n) {
	if (l == r) { make(st[pos], a[l]); return; }
	int mid = (l+r) >> 1;
	build(2*pos, l, mid);
	build(2*pos+1, mid+1, r);
	make(st[pos], st[2*pos], st[2*pos+1]);
}

void upd(int i, int v, int pos = 1, int l = 1, int r = n) {
	if (l == r) { make(st[pos], v); return; }
	int mid = (l+r) >> 1;
	if (i <= mid) upd(i, v, 2*pos, l, mid);
	else upd(i, v, 2*pos+1, mid+1, r);
	make(st[pos], st[2*pos], st[2*pos+1]);
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i<=n; i++) scanf("%d", &a[i]);
	build();
	while(m--) {
		int k, x;
		scanf("%d %d", &k, &x);
		upd(k, x);
		printf("%lld\n", st[1].ans);
	}
	return 0;
}

