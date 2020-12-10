#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5, inf = 1e9+7;
int n, q, st[4*maxn];

void build(int pos = 1, int l = 1, int r = n) {
	if (l == r) { scanf("%d", &st[pos]); return; }
	int mid = (l+r) >> 1;
	build(2*pos, l, mid);
	build(2*pos+1, mid+1, r);
	st[pos] = min(st[2*pos], st[2*pos+1]);
}

int query(int ql, int qr, int pos = 1, int l = 1, int r = n) {
	if (r < ql or l > qr) return inf;
	if (ql <= l && r <= qr) return st[pos];
	int mid = (l+r) >> 1;
	return min(query(ql, qr, 2*pos, l, mid), query(ql, qr, 2*pos+1, mid+1, r));
}

void upd(int i, int v, int pos = 1, int l = 1, int r = n) {
	if (l == r) { st[pos] = v; return; }
	int mid = (l+r) >> 1;
	if (i <= mid) upd(i, v, 2*pos, l, mid);
	else upd(i, v, 2*pos+1, mid+1, r);
	st[pos] = min(st[2*pos], st[2*pos+1]);
}

int main(){
	scanf("%d %d", &n, &q);
	build();
	while(q--){
		int t, k, u;
		scanf("%d %d %d", &t, &k, &u);
		if (t == 1) upd(k, u);
		else printf("%d\n", query(k, u));
	}
	return 0;
}

