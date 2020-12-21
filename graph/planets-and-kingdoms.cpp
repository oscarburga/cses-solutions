#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
const int maxn = 1e5+5;
bool vis[maxn];
int n, m, cnt, tag[maxn];
vector<int> vs[2][maxn], topo;
 
void dfs1(int v){
	vis[v] = true;
	for(int e: vs[0][v]) if (!vis[e]) dfs1(e);
	topo.emplace_back(v);
}
 
void dfs2(int v){
	vis[v] = true;
	tag[v] = cnt;
	for(int e: vs[1][v]) if (!vis[e]) dfs2(e);
}
 
int main(){
	scanf("%d %d", &n, &m);
	for(int i = 0; i<m; i++){
		int x, y;
		scanf("%d %d", &x, &y);
		x--, y--;
		vs[0][x].emplace_back(y);
		vs[1][y].emplace_back(x);
	}
	for(int i = 0; i<n; i++) if (!vis[i]) dfs1(i);
	reverse(topo.begin(), topo.end());
	memset(vis, 0, sizeof(vis));
	for(int v: topo) if (!vis[v]) dfs2(v), cnt++;
	printf("%d\n", cnt);
	for(int i = 0; i<n; i++) printf("%d%c", tag[i]+1, " \n"[i+1==n]);
	return 0;
}
