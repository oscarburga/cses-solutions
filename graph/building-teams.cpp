#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
bool vis[maxn], c[maxn];
int n, m;
vector<int> vs[maxn];

bool bp = true;
void dfs(int v){
	vis[v] = true;
	for(int e: vs[v]) {
		if (!vis[e]) c[e] = !c[v], dfs(e);
		bp &= c[e] != c[v];
	}
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 0; i<m; i++){
		int x, y;
		scanf("%d %d", &x, &y);
		x--, y--;
		vs[x].emplace_back(y);
		vs[y].emplace_back(x);
	}
	for(int i = 0; i<n; i++) if (!vis[i]) dfs(i);
	if (bp){
		for(int i = 0; i<n; i++) printf("%d%c", int(c[i])+1, " \n"[i+1==n]);
	} else puts("IMPOSSIBLE");
	return 0;
}

