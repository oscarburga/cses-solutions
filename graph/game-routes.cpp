#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5, mod = 1e9+7;
int add(int a, int b) { return (a+b) % mod; }

bool vis[maxn];
int n, m, dp[maxn];
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
	reverse(topo.begin(), topo.end());
	dp[0] = 1;
	for(int v: topo){
		for(int e: vs[v]) dp[e] = add(dp[e], dp[v]);
	}
	printf("%d\n", dp[n-1]);

	return 0;
}

