#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
bool rem[maxn];
int n, K, tmr, sz[maxn], tin[maxn], tout[maxn], tour[maxn], dep[maxn], cnt[maxn];
ll ans = 0;
vector<int> vs[maxn];

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

int centroid(int v, int p, int tsize) {
	for(int e: vs[v]) 
		if (e != p && !rem[e] && (sz[e] << 1) > tsize) 
			return centroid(e, v, tsize);
	return v;
}

void solve(int v) {
	dep[v] = tmr = 0, dfs(v);
	cnt[0] = 1;
	for(int e: vs[v]) if (!rem[e]) {
		for(int i = tin[e], u; i < tout[e]; i++) {
			u = tour[i];
			if (dep[u] <= K) ans += cnt[K - dep[u]];
		}
		for(int i = tin[e]; i < tout[e]; i++) ++cnt[dep[tour[i]]];
	}
	for(int e: vs[v]) if (!rem[e]) {
		for(int i = tin[e]; i < tout[e]; i++) cnt[dep[tour[i]]] = 0;
	}
}

void decompose(int v) {
	dep[v] = tmr = 0, dfs(v);
	int c = centroid(v, -1, sz[v]);
	solve(c);
	rem[c] = true;
	for(int e: vs[c]) if (!rem[e]) decompose(e);
}

int main(){
	scanf("%d %d", &n, &K);
	for(int i = 1, x, y; i<n; i++) {
		scanf("%d %d", &x, &y);
		vs[x].emplace_back(y);
		vs[y].emplace_back(x);
	}
	decompose(1);
	printf("%lld\n", ans);
	return 0;
}

