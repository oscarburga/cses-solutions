#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, m, p[maxn];
vector<int> vs[maxn];
queue<int> q;

int main(){
	memset(p, -1, sizeof(p));
	p[1] = -2;
	scanf("%d %d", &n, &m);
	for(int i = 0; i<m; i++){
		int x, y;
		scanf("%d %d", &x, &y);
		vs[x].emplace_back(y);
		vs[y].emplace_back(x);
	}
	q.push(1);
	while(q.size()){
		int v = q.front(); q.pop();
		for(int e: vs[v]) if (p[e] == -1){
			p[e] = v;
			q.push(e);
		}
	}
	if (p[n] == -1) puts("IMPOSSIBLE");
	else {
		vector<int> path;
		int v = n;
		while(v != -2) path.emplace_back(v), v = p[v]; 
		printf("%zu\n", path.size());
		reverse(path.begin(), path.end());
		for(int i = 0; i<path.size(); i++) printf("%d%c", path[i], " \n"[i+1==path.size()]);
	}

	return 0;
}

