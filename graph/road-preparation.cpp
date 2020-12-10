#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;

struct edge { 
	int u, v, w;
	bool operator < (const edge&e) const { return w < e.w; }
};

struct dset{
	vector<int> p, sz;
	dset(int n) : p(n, -1), sz(n, 1) {}
	int find(int x) { return p[x] == -1 ? x : p[x] = find(p[x]); }
	int join(edge&e){
		int u = find(e.u), v = find(e.v);
		if (u == v) return 0;
		if (sz[u] < sz[v]) swap(u, v);
		sz[u] += sz[v];
		p[v] = u;
		return e.w;
	}
};

int n, m;

int main(){
	scanf("%d %d", &n, &m);
	vector<edge> es(m);
	for(int i = 0; i<m; i++){
		int x, y, w;
		scanf("%d %d %d", &x, &y, &w);
		es.push_back({x, y, w});
	}
	dset dsu(n+1);
	sort(es.begin(), es.end());
	ll ans = 0;
	for(edge&e: es) ans += dsu.join(e); 
	int c = dsu.find(1);
	for(int i = 2; i<=n; i++){
		if (dsu.find(i) != c) { puts("IMPOSSIBLE"); return 0; }
	}
	printf("%lld\n", ans);
	

	return 0;
}

