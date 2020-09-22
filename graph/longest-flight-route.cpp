#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
bool vis[maxn];
int n, m, p[maxn], dp[maxn];
vector<int> vs[maxn], topo;

void dfs(int v){
	vis[v] = true;
	for(int e: vs[v]) if (!vis[e]) dfs(e);
	topo.emplace_back(v);
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 0; i<m; i++){
		int x, y;
		scanf("%d %d", &x, &y);
		vs[--x].emplace_back(--y);
	}	
	dfs(0);
	if (!vis[n-1]) { puts("IMPOSSIBLE"); return 0; }
	reverse(topo.begin(), topo.end());
	p[0] = -1;
	for(int v: topo){
		dp[v]++;
		for(int e: vs[v]) if (dp[v] > dp[e]) dp[e] = dp[v], p[e] = v;
	}
	int v = n-1;
	vector<int> path;
	while(v != -1) path.emplace_back(v), v = p[v];
	reverse(path.begin(), path.end());
	printf("%zu\n", path.size());
	for(int i = 0; i<path.size(); i++) printf("%d%c", path[i]+1, " \n"[i+1==path.size()]);
	return 0;
}

