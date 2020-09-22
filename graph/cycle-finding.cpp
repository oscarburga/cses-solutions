#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2505, maxm = 5e3+5;
struct edge { int u, v, w; };
vector<edge> edges;
bool seen[maxn];
bool changed[maxn];
int n, m, p[maxn];
ll d[maxn];

bool bellman(){
	bool ret = false;
	memset(changed, 0, sizeof(changed));
	for (edge &e: edges){
		if (d[e.u] + e.w < d[e.v]){
			d[e.v] = d[e.u] + e.w;
			changed[e.v] = ret = true;
			p[e.v] = e.u;
		}
	}
	return ret;
}
void propagate(){
	for(edge&e: edges){
		if (changed[e.u] && !changed[e.v]) {
			p[e.v] = e.u;
			changed[e.v] = true;
		}
	}
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 0; i<m; i++){
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		edges.push_back({ u, v, w });
	}
	bool ncycle = false;
	for(int i = 0; i<n; i++) ncycle = bellman();
	if (ncycle) {
		for(int i = 0; i<n; i++) propagate();
		for(int i = 1; i<=n; i++) if (changed[i] && p[i] > 0){
			vector<int> path;
			int v = i;
			while(!seen[v]){
				seen[v] = true;
				path.emplace_back(v);
				v = p[v];
			}
			puts("YES");
			printf("%d ", v);
			while(path.back() != v) printf("%d ", path.back()), path.pop_back();
			printf("%d\n", v);
			return 0;
		}
	} else puts("NO");

	return 0;
}

