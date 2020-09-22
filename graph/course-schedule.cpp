#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, m, vis[maxn];
vector<int> vs[maxn], topo;

void dfs(int v){
	vis[v] = 1;
	for(int e: vs[v]) {
		if (vis[e] == 1) {
			puts("IMPOSSIBLE");
			exit(0);
		} else if (vis[e] == 0) dfs(e);
	}
	vis[v] = 2;
	topo.emplace_back(v);
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 0; i<m; i++){
		int x, y;
		scanf("%d %d", &x, &y);
		vs[--x].emplace_back(--y);
	}
	for(int i = 0; i<n; i++) if(vis[i] == 0) dfs(i);
	reverse(topo.begin(), topo.end());
	for(int i = 0; i<n; i++) printf("%d%c", topo[i]+1, " \n"[i+1==n]);
	return 0;
}

