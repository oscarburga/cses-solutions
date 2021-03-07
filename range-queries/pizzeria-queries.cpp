#include <bits/stdc++.h>
#define debug(...) fprintf(stderr, __VA_ARGS__)
using namespace std;
using ll = long long;

const int maxn = 2e5+5, inf = 2e9;
int n, q, a[maxn], st[2][4*maxn];

void build(int id, int pos = 1, int l = 1, int r = n) {
	if (l == r) { 
		st[id][pos] = a[l] + (id == 0 ? -l : l);
		return;
	}
	int mid = (l+r) >> 1;
	build(id, pos<<1, l, mid);
	build(id, pos<<1|1, mid+1, r);
	st[id][pos] = min(st[id][pos<<1], st[id][pos<<1|1]);
}

void upd(int id, int i, int v, int pos = 1, int l = 1, int r = n) {
	if (l == r) { st[id][pos] = v; return; }
	int mid = (l+r) >> 1, child = pos << 1;
	if (i <= mid) upd(id, i, v, child, l, mid);
	else upd(id, i, v, child|1, mid+1, r);
	st[id][pos] = min(st[id][child], st[id][child|1]);
}

int query(int id, int ql, int qr, int pos = 1, int l = 1, int r = n) {
	if (r < l or r < ql or l > qr) return inf;
	if (ql <= l && r <= qr) return st[id][pos];
	int mid = (l+r) >> 1, child = pos << 1;
	return min(query(id, ql, qr, child, l ,mid), query(id, ql, qr, child|1, mid+1, r));
}

int main(){
	scanf("%d %d", &n, &q);
	for(int i = 1; i<=n; i++) scanf("%d", &a[i]);
	build(0);
	build(1);
	for(int t, k; q--; ) {
		scanf("%d %d", &t, &k);
		if (t == 1) scanf("%d", &a[k]), upd(0, k, a[k]-k), upd(1, k, a[k]+k);
		else printf("%d\n", min(query(0, 1, k) + k, query(1, k, n) - k));
	}

	return 0;
}

