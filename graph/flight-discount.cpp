#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct node {
	ll c;
	int v;
	bool used;
	bool operator < (const node& e) const { return c < e.c; }
};
const ll inf = 1e17;
const int maxn = 1e5+5;
bool vis[2][maxn];
int n, m;
ll d[2][maxn];
vector<pair<int,int>> vs[maxn];
priority_queue<node> q;

void process_node(const node &t){
	for(pair<int,int>& e: vs[t.v]) {
		ll aux = t.c + e.second;
		if (!vis[t.used][e.first] && aux < d[t.used][e.first]) {
			d[t.used][e.first] = aux;
			q.push({-aux, e.first, t.used});
		}
		aux = t.c + (e.second/2);
		if (!t.used && !vis[1][e.first] && aux < d[1][e.first]) {
			d[1][e.first] = aux;
			q.push({-aux, e.first, 1});
		}
	}
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 0; i<m; i++){
		int x, y, w;
		scanf("%d %d %d", &x, &y, &w);
		vs[x].push_back({y, w});
	}
	q.push({0, 1, 0});
	fill(d[0], d[0]+maxn, inf);
	fill(d[1], d[1]+maxn, inf);
	d[0][1] = 0;
	while(q.size()){
		node t = q.top();
		t.c *= -1ll;
		q.pop();
		if (vis[t.used][t.v]) continue;
		vis[t.used][t.v] = true;
		process_node(t);
	}
	printf("%lld\n", min(d[0][n], d[1][n]));

	return 0;
}

