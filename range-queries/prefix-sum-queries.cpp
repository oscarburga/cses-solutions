#include <bits/stdc++.h>
#define debug(...) fprintf(stderr, __VA_ARGS__)
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
const ll inf = 1e18;
int n, q, a[maxn];
ll pre[maxn], st[maxn*4], lazy[maxn*4];

void build(int pos = 1, int l = 1, int r = n) {
	if (l == r) { st[pos] = pre[l]; return; }
	int mid = (l+r) >> 1, child = pos<<1;
	build(child, l, mid);
	build(child|1, mid+1, r); 
	st[pos] = max(st[child], st[child|1]);
}

void push(int pos, int l, int r) { 
	if (lazy[pos] == 0) return;
	st[pos] += lazy[pos];
	if (l < r) lazy[pos<<1] += lazy[pos], lazy[(pos<<1)|1] += lazy[pos];
	lazy[pos] = 0;
}

void updr(int ql, int qr, ll v, int pos = 1, int l = 1, int r = n) { 
	push(pos, l, r);
	if (r < ql or l > qr) return;
	if (ql <= l && r <= qr) {
		lazy[pos] += v;
		push(pos, l, r);
		return;
	}
	int mid = (l+r) >> 1, child = pos << 1;
	updr(ql, qr, v, child, l, mid);
	updr(ql, qr, v, child|1, mid+1, r);
	st[pos] = max(st[child], st[child|1]);
}

ll qmax(int ql, int qr, int pos = 1, int l = 1, int r = n) {
	push(pos, l, r);
	if (qr < 1) return 0ll;
	if (r < ql or l > qr) return -inf;
	if (ql <= l && r <= qr) return st[pos];
	int mid = (l+r) >> 1, child = pos<<1;
	return max(qmax(ql, qr, child, l, mid), qmax(ql, qr, child|1, mid+1, r));
}

int main(){
	scanf("%d %d", &n, &q);
	for(int i = 1; i<=n; i++) {
		scanf("%d", &a[i]);
		pre[i] = pre[i-1] + a[i];
	}
	build();
	for(int t, k, u; q--; ) {
		scanf("%d %d %d", &t, &k, &u);
		if (t == 1) {
			updr(k, n, ll(u) - a[k]);
			a[k] = u;
		} else printf("%lld\n", max(qmax(k, u) - qmax(k-1, k-1), 0ll));
	}

	return 0;
}

