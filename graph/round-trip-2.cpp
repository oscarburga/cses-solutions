#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, m, vis[maxn], p[maxn];
vector<int> vs[maxn];

void dfs(int v){
	vis[v] = 1;
	for(int e: vs[v]){
		if (vis[e] == 0) p[e] = v, dfs(e);
		else if (vis[e] == 1) {
			int x = v;
			vector<int> path = { e };
			while(x != p[e]) path.emplace_back(x), x = p[x];
			reverse(path.begin(), path.end());
			printf("%zu\n", path.size());
			for(int i = 0; i<path.size(); i++) printf("%d%c", path[i], " \n"[i+1==path.size()]);
			exit(0);
		}
	}
	vis[v] = 2;
	
}

int main(){
	memset(p, -1, sizeof(p));
	scanf("%d %d", &n, &m);
	for(int i = 0; i<m; i++){
		int x, y;
		scanf("%d %d", &x, &y);
		vs[x].emplace_back(y);
	}
	for(int i = 1; i<=n; i++) if (vis[i] == 0) dfs(i);
	puts("IMPOSSIBLE");
	return 0;
}

