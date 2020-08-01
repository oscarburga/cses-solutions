#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e3+5;
int n, m, k, p[maxn], cap[maxn][maxn];
vector<int> vs[maxn];

int bfs(int s, int t){
	memset(p, -1, sizeof(p));
	p[s] = -2;
	queue<pair<int,int>> q;
	q.emplace(make_pair(s, int(1e9)));
	while(q.size()){
		int v = q.front().first, f = q.front().second;
		q.pop();
		for(int e: vs[v]) if (p[e] == -1 && cap[v][e] > 0){
			p[e] = v;
			int nf = min(f, cap[v][e]);
			if (e == t) return nf;
			q.emplace(make_pair(e, nf));
		}
	}
	return 0;
}


int maxflow(int s, int t){
	int flow = 0, new_flow = 0;
	while(new_flow = bfs(s,t)){
		flow += new_flow;
		int v = t;
		while(v != s) {
			int u = p[v];
			cap[u][v] -= new_flow;
			cap[v][u] += new_flow;
			v = u;
		}
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
