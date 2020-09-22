#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2505, maxm = 5e3+5;
const ll inf = 1e17;
struct edge { int u, v, w; } ed[maxm];
bool changed[maxn];
int n, m;
ll d[maxn];

bool bellman(){
	bool ret = false;
	memset(changed, 0, sizeof(changed));
	for(int i = 0; i<m; i++) {
		edge &e = ed[i];
		if (d[e.u] == inf) continue;
		changed[e.v] |= d[e.u] + e.w < d[e.v];
		ret |= changed[e.v];
		d[e.v] = min(d[e.v], d[e.u] + e.w);
	}
	return ret;
}
void propagate(){
	for(int i = 0; i<m; i++){
		edge&e = ed[i];
		changed[e.v] |= changed[e.u];
	}
}

int main(){
	fill(d, d+maxn, inf);
	d[1] = 0;
	scanf("%d %d", &n, &m);
	for(int i = 0; i<m; i++){
		edge e;
		scanf("%d %d %d", &e.u, &e.v, &e.w);
		e.w *= -1;
		ed[i] = e;
	}
	bool ncycle = false;
	for(int i = 0; i<n; i++) ncycle = bellman();
	if (ncycle) for(int i = 1; i<n; i++) propagate();
	printf("%lld\n", changed[n] ? -1ll : -d[n]);
	return 0;
}

