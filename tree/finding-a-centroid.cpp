#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, sz[maxn];
vector<int> vs[maxn];

void dfs(int v, int p = -1) {
	sz[v] = 1;
	for(int e: vs[v]) if (e != p) dfs(e, v), sz[v] += sz[e];
}

int centroid(int v, int p = -1) {
	for(int e: vs[v]) if (e != p && (sz[e] << 1) > n) return centroid(e, v);
	return v;
}

int main(){
	scanf("%d", &n);
	for(int i = 1, x, y; i < n; i++) {
		scanf("%d %d", &x, &y);
		vs[x].emplace_back(y);
		vs[y].emplace_back(x);
	}
	dfs(1);
	printf("%d\n", centroid(1));
	return 0;
}

