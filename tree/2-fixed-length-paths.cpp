#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
bool rem[maxn];
int n, k1, k2, tmr, sz[maxn], dep[maxn], tin[maxn], tout[maxn], tour[maxn], ft[maxn];
ll ans;
vector<int> vs[maxn];

void upd(int pos, int val) {
	++pos;
	while(pos <= n) ft[pos] += val, pos += pos & (-pos);
}

int query(int pos) {
	++pos;
	int ret = 0; 
	while (pos > 0) ret += ft[pos], pos &= pos-1;
	return ret;
}

void dfs(int v, int p = -1) {
	tour[tin[v] = tmr++] = v;
	sz[v] = 1;
	for(int e: vs[v]) if (e != p && !rem[e]) {
		dep[e] = dep[v] + 1;
		dfs(e, v);
		sz[v] += sz[e];
	}
	tout[v] = tmr;
}

int centroid(int v, int p, int tsz) {
	for(int e: vs[v]) 
		if (e != p && !rem[e] && (sz[e] << 1) > tsz) 
			return centroid(e, v, tsz);
	return v;
}

void solve(int v) {
	dep[v] = tmr = 0, dfs(v);
	upd(0, 1);
	for(int e: vs[v]) if (!rem[e]) {
		for(int i = tin[e], u; i < tout[e]; i++) {
			u = tour[i];
			ans += query(k2 - dep[u]) - query(k1 - dep[u] - 1);
		}
		for(int i = tin[e]; i < tout[e]; i++) upd(dep[tour[i]], 1);
	}
	for(int e: vs[v]) if (!rem[e]) {
		for(int i = tin[e]; i < tout[e]; i++) upd(dep[tour[i]], -1);
	}
	upd(0, -1);
}

void decompose(int v) {
	dep[v] = tmr = 0, dfs(v);
	int c = centroid(v, -1, sz[v]);
	solve(c);
	rem[c] = true;
	for(int e: vs[c]) if (!rem[e]) decompose(e);
}

int main(){
	scanf("%d %d %d", &n, &k1, &k2);
	for(int i = 1, x, y; i < n; i++) {
		scanf("%d %d", &x, &y);
		vs[x].emplace_back(y);
		vs[y].emplace_back(x);
	}
	decompose(1);
	printf("%lld\n", ans);
	return 0;
}

