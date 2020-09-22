#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll inf = 1e17;
const int maxn = 1e5+5;
bool vis[maxn];
int n, m;
ll d[maxn];
vector<pair<int,int>> vs[maxn];
priority_queue<pair<ll, int>> q;

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 0; i<m; i++){
		int x, y, w;
		scanf("%d %d %d", &x, &y, &w);
		x--, y--;
		vs[x].push_back({y, w});
	}
	fill(d+1, d+maxn, inf);
	d[0] = 0;
	q.push({0, 0});
	while(q.size()){
		int v = q.top().second;
		q.pop();
		if (vis[v]) continue;
		vis[v] = true;
		for(pair<int,int>& e: vs[v]) if (!vis[e.first] && d[v] + e.second < d[e.first]) {
			d[e.first] = d[v] + e.second;
			q.push({-d[e.first], e.first});
		}
	}
	for(int i = 0; i<n; i++) printf("%lld%c", d[i], " \n"[i+1==n]);
	return 0;
}

