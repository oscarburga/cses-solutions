#include <bits/stdc++.h>
#define debug(...) fprintf(stderr, __VA_ARGS__)
using namespace std;
using ll = long long;

const int maxn = 2e5+5;

int n, q, a[maxn];

struct node {
	ll sum;
	ll l_a, l_k;
	explicit node(ll v = 0) : sum(v), l_a(0), l_k(0) {}
	void pull(const node &par, int l, int parl) { 
		l_a += par.l_a + par.l_k * (l-parl);
		l_k += par.l_k;
	}
} st[4*maxn];

void build(int pos = 1, int l = 1, int r = n) { 
	if (l == r) { st[pos].sum = a[l]; return; }
	int mid = (l+r) >> 1, child = pos << 1;
	build(child, l, mid);
	build(child|1, mid+1, r);
	st[pos].sum = st[child].sum + st[child|1].sum;
}

void push(int pos, int l, int r) { 
	node &cur = st[pos];
	if (cur.l_a == 0 && cur.l_k == 0) return;
	cur.sum += cur.l_a * (r-l+1);
	cur.sum += cur.l_k * ((1ll * (r-l) * (r-l+1)) >> 1);
	if (l < r) {
		int child = pos << 1, mid = (l+r) >> 1;
		st[child].pull(cur, l, l);
		st[child|1].pull(cur, mid+1, l);
	}
	cur.l_a = cur.l_k = 0;
}

void upd(int ql, int qr, int pos = 1, int l = 1, int r = n) {
	push(pos, l, r);
	if (r < ql or l > qr) return;
	if (ql <= l && r <= qr) {
		st[pos].l_a += l-ql+1;
		st[pos].l_k += 1;
		push(pos, l, r);
		return;
	}
	int mid = (l+r) >> 1, child = pos << 1;
	upd(ql, qr, child, l, mid);
	upd(ql, qr, child|1, mid+1, r);
	st[pos].sum = st[child].sum + st[child|1].sum;
}

ll query(int ql, int qr, int pos = 1, int l = 1, int r = n) {
	push(pos, l, r);
	if (r < ql or l > qr) return 0;
	if (ql <= l && r <= qr) return st[pos].sum;
	int mid = (l+r) >> 1, child = pos << 1;
	return query(ql, qr, child, l, mid) + query(ql, qr, child|1, mid+1, r);
}

int main(){
	scanf("%d %d", &n, &q);
	for(int i = 1; i<=n; i++) scanf("%d", &a[i]);
	build();
	for(int t, l, r; q--; ) {
		scanf("%d %d %d", &t, &l, &r);
		if (t == 1) upd(l, r);
		else printf("%lld\n", query(l, r));
	}
	return 0;
}

