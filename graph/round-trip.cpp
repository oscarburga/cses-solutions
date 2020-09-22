#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
bool vis[maxn];
int n, m, p[maxn];
vector<int> vs[maxn], path;

void dfs(int v){
	vis[v] = true;
	for(int e: vs[v]) {
		if (vis[e] && e != p[v]) {
			path.emplace_back(e);
			while(v != p[e]) path.emplace_back(v), v = p[v];
			return;
		} else if (!vis[e]) p[e] = v, dfs(e);
		if (path.size()) return;
	}
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 0; i<m; i++){
		int x, y;
		scanf("%d %d", &x, &y);
		vs[x].emplace_back(y);
		vs[y].emplace_back(x);
	}
	for(int i = 1; i<=n; i++) {
		if (!vis[i]) dfs(i);
		if (path.size()){
			printf("%zu\n", path.size());
			for(int i = 0; i<path.size(); i++) printf("%d%c", path[i], " \n"[i+1==path.size()]);
			return 0;
		}
	}
	puts("IMPOSSIBLE");

	return 0;
}

