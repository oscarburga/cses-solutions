#include <bits/stdc++.h>
#define debug(...) fprintf(stderr, __VA_ARGS__)
using namespace std;
using ll = long long;

const int maxn = 2e5+5;

int n, q, a[maxn];

struct node {
	ll sum, l_add, l_set;
	node(ll v = 0) : sum(v), l_add(0), l_set(0) {}
	node(const node &L, const node &R) : sum(L.sum + R.sum), l_add(0), l_set(0) {}
	void pull(const node &par) {
		if (par.l_set) l_set = par.l_set, l_add = 0;
		l_add += par.l_add;
	}
} st[4*maxn];

void build(int pos = 1, int l = 1, int r = n) {
	if (l == r) { st[pos] = node(a[l]); return; }
	int mid = (l+r) >> 1, child = pos << 1;
	build(child, l, mid);
	build(child|1, mid+1, r);
	st[pos] = node(st[child], st[child|1]);
}

void push(int pos, int l, int r) {
	node &cur = st[pos];
	if (max(cur.l_add, cur.l_set) <= 0) return;
	if (cur.l_set) cur.sum = cur.l_set * (r-l+1);
	cur.sum += cur.l_add * (r-l+1);
	if (l < r) st[pos<<1].pull(cur), st[(pos<<1)|1].pull(cur);
	cur.l_set = cur.l_add = 0;
}

void upd(int ql, int qr, int v, int pos = 1, int l = 1, int r = n) {
	push(pos, l, r);
	if (r < ql or l > qr) return;
	if (ql <= l && r <= qr) {
		if (v < 0) st[pos].l_set = -v;
		else st[pos].l_add += v;
		push(pos, l, r);
		return;
	}
	int mid = (l+r) >> 1, child = pos << 1;
	upd(ql, qr, v, child, l, mid);
	upd(ql, qr, v, child|1, mid+1, r);
	st[pos] = node(st[child], st[child|1]);
}

ll query(int ql, int qr, int pos = 1, int l = 1, int r = n) {
	push(pos, l, r);
	if (r < ql or l > qr) return 0ll;
	if (ql <= l && r <= qr) return st[pos].sum;
	int mid = (l+r) >> 1, child = pos << 1;
	return query(ql, qr, child, l, mid) + query(ql, qr, child|1, mid+1, r);
}


int main(){
	scanf("%d %d", &n, &q);
	for(int i = 1; i<=n; i++) scanf("%d", &a[i]);
	build();
	for(int t, l, r, x; q--;) {
		scanf("%d %d %d", &t, &l, &r);
		if (t == 3) printf("%lld\n", query(l, r));
		else {
			scanf("%d", &x);
			upd(l, r, t == 1 ? x : -x);
		}
	}
	return 0;
}

