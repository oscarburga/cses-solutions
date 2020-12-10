#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5, mod = 1e9+7;
const ll inf = 1e17;
int add(int a, int b) { return (a+b) % mod; }

vector<pair<int,int>> vs[maxn];
bool vis[maxn];
int n, m, ways[maxn], mn[maxn], mx[maxn];
ll d[maxn];
priority_queue<pair<ll, int>> q;
vector<int> g[maxn], topo;

void dfs(int v){
	vis[v] = true;
	for(int e: g[v]) if (!vis[e]) dfs(e);
	topo.emplace_back(v);
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 0; i<m; i++){
		int x, y, w;
		scanf("%d %d %d", &x, &y, &w);
		x--, y--;
		vs[x].push_back({y, w});
	}
	fill(d, d+maxn, inf);
	d[0] = 0;
	q.push({0, 0});
	while(q.size()){
		int v = q.top().second;
		ll c = -q.top().first;
		q.pop();
		if (vis[v]) continue;
		vis[v] = true;
		for(pair<int,int> &e: vs[v]) if (!vis[e.first] && c + e.second < d[e.first]) {
			d[e.first] = c + e.second;
			q.push({-d[e.first], e.first});
		}
	}
	for(int i= 0 ; i<n; i++) {
		for(pair<int,int>&e: vs[i]) if (d[i] + e.second == d[e.first]) {
			g[i].emplace_back(e.first);
		}
	}
	memset(vis, 0, sizeof(vis));
	dfs(0);
	reverse(topo.begin(), topo.end());
	fill(mn, mn + maxn, mod);
	ways[0] = 1;
	mn[0] = mx[0] = 0;
	for(int v: topo){
		for(int e: g[v]) {
			ways[e] = add(ways[v], ways[e]);
			mn[e] = min(mn[e], mn[v] + 1);
			mx[e] = max(mx[e], mx[v] + 1);
		}
	}
	printf("%lld %d %d %d\n", d[n-1], ways[n-1], mn[n-1], mx[n-1]);
	return 0;
}

