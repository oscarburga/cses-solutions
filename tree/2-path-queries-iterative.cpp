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
 
//Time limit is very tight for recursive segment tree
//Passes easily with iterative though.

void build() {
	for(int i = 0; i<n; i++) st[n + i] = tour[i];
	for(int i = n-1; i>0; i--) st[i] = max(st[i<<1], st[(i<<1)|1]);
}
 
void upd(int i, int v) {
	for(st[i+=n] = v; i > 1; i >>= 1) st[i>>1] = max(st[i], st[i^1]);
}
 
int query(int l, int r) {
	int res = -1;
	for(l += n, r += n+1; l < r; l >>= 1, r >>= 1) {
		if (l&1) res = max(res, st[l++]);
		if (r&1) res = max(res, st[--r]);
	}
	return res;
}
 
int path_query(int u, int v) {
	int res = -1;
	while(head[u] != head[v]) {
		if (dep[head[u]] < dep[head[v]]) swap(u, v);
		res = max(res, query(tin[head[u]], tin[u]));
		u = par[head[u]];
	}
	if (dep[u] < dep[v]) swap(u, v);
	return max(res, query(tin[v], tin[u]));
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
		if (t == 1) upd(tin[x], y);
		else printf("%d\n", path_query(x, y));
	}
	return 0;
}

