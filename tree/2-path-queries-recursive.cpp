#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;

int n, q, tmr, a[maxn], tour[maxn], tin[maxn], dep[maxn], par[maxn], head[maxn], sz[maxn], st[4*maxn];
vector<int> vs[maxn];

void dfs(int v) {
	sz[v] = 1;
	for(int i = 0, e; i<int(vs[v].size()); i++) {
		e = vs[v][i];
		if (e == par[v]) {
			swap(vs[v][i--], vs[v].back());
			vs[v].pop_back();
			continue;
		}
		par[e] = v;
		dep[e] = dep[v] + 1;
		dfs(e);
		sz[v] += sz[e];
		if (sz[e] > sz[vs[v][0]]) swap(vs[v][i], vs[v][0]);
	}
}

void hld(int v) {
	tour[tmr] = a[v];
	tin[v] = tmr++;
	for(int e : vs[v]) {
		head[e] = e == vs[v][0] ? head[v] : e;
		hld(e);
	}
}


void build(int pos = 1, int l = 0, int r = n-1) {
	if (l == r) { st[pos] = tour[l]; return; }
	int mid = (l+r) >> 1, child = pos << 1;
	build(child, l, mid);
	build(child|1, mid+1, r);
	st[pos] = max(st[child], st[child|1]);
}

//Cheesy query parameters as global variables to squeeze 
//recursive segtree into the time limit. Passes with 0.97s.
//Just use iterative segment tree instead honestly.

int qi, ql, qr, qv;
void upd(int pos = 1, int l = 0, int r = n-1) {
	if (l == r) { st[pos] = qv; return; }
	int mid = (l+r) >> 1, child = pos << 1;
	if (qi <= mid) upd(child, l, mid);
	else upd(child|1, mid+1, r);
	st[pos] = max(st[child], st[child|1]);
}

int query(int pos = 1, int l = 0, int r = n-1) {
	if (r < ql or l > qr) return -1;
	if (ql <= l && r <= qr) return st[pos];
	int mid = (l+r) >> 1, child = pos << 1;
	return max(query(child, l, mid), query(child|1, mid+1, r));
}

int path_query(int u, int v) {
	int res = -1;
	while(head[u] != head[v]) {
		if (dep[head[u]] < dep[head[v]]) swap(u, v);
		ql = tin[head[u]], qr = tin[u];
		res = max(res, query());
		u = par[head[u]];
	}
	if (dep[u] < dep[v]) swap(u, v);
	ql = tin[v], qr = tin[u];
	return max(res, query());
}

int main(){
	scanf("%d %d", &n, &q);
	for(int i = 1; i<=n; i++) scanf("%d", &a[i]);
	for(int i = 1, x, y; i<n; i++) {
		scanf("%d %d", &x, &y);
		vs[x].push_back(y);
		vs[y].push_back(x);
	}
	dfs(1);
	hld(1);
	build();
	for(int i = 0, t, x, y; i<q; i++) {
		scanf("%d %d %d", &t, &x, &y);
		if (t == 1) qi = tin[x], qv = y, upd();
		else printf("%d\n", path_query(x, y));
	}
	return 0;
}

