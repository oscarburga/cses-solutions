#include <bits/stdc++.h>
using namespace std;
 
const int maxn = 1e3+5;
bool vis[maxn];
int n, m, k, cap[maxn][maxn];
vector<int> vs[maxn];
 
int sink;
int dfs(int v, int f){
	vis[v] = true;
	if (v == sink) return f;
	for(int e: vs[v]) if (!vis[e] && cap[v][e] > 0){
		int flow = dfs(e, min(f, cap[v][e]));
		if (flow > 0){
			cap[v][e] -= flow;
			cap[e][v] += flow;
			return flow;
		}
	}
	return 0;
}
 
int maxflow(int s, int t){
	int flow = 0, new_flow = 0;
	sink = t;
	while(new_flow = dfs(s, maxn)){
		flow += new_flow;
		memset(vis, 0, sizeof(vis));
	}
	return flow;
}
 
int main(){
	scanf("%d %d %d", &n, &m, &k);
	int s = 0, t = maxn-1;
	for(int i = 1; i<=n; i++) {
		vs[s].emplace_back(i);
		vs[i].emplace_back(s);
		cap[s][i] = 1;
	}
	for(int i = n+1; i<=n+m; i++){
		vs[i].emplace_back(t);
		vs[t].emplace_back(i);
		cap[i][t] = 1;
	}
	for(int i = 0; i<k; i++){
		int x, y;
		scanf("%d %d", &x, &y);
		y += n;
		vs[x].emplace_back(y);
		vs[y].emplace_back(x);
		cap[x][y] = 1;
	}
	printf("%d\n", maxflow(s, t));
	for(int i = 1; i<=n; i++) for(int e: vs[i]){
		if (e>n && e <= n+m && cap[e][i] == 1) {
			printf("%d %d\n", i, e-n); 
			break; 
		}
	}
	return 0;
}
