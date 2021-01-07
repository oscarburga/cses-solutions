#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5, maxs = 5e5+5;

int seen[maxs], vis[maxs];
int n, m, nodes = 1, go[maxs][26], suf[maxs];
vector<pair<int,int>> term[maxs]; 
char s[maxn], t[maxs];

int main(){
	scanf("%s", s);
	n = strlen(s);
	scanf("%d", &m);
	for(int i = 0; i<m; i++) {
		scanf("%s", t);
		int j = 0, pos = 0;
		for(int nxt; t[j]; j++) {
			nxt = t[j] - 'a';
			if (!go[pos][nxt]) go[pos][nxt] = nodes++;
			pos = go[pos][nxt];
		}
		term[pos].emplace_back(i, j);
	}
	queue<int> q;
	vector<int> order;
	q.emplace(0);
	while(q.size()) {
		int u = q.front(); q.pop();
		order.emplace_back(u);
		for(int i = 0; i<26; i++) {
			if (go[u][i]) {
				suf[go[u][i]] = u ? go[suf[u]][i] : 0;
				q.emplace(go[u][i]);
			} else go[u][i] = u ? go[suf[u]][i] : 0;
		}
	}
	reverse(order.begin(), order.end());
	fill(vis, vis+maxs, maxs);
	fill(seen, seen+maxs, maxs);
	int pos = 0;
	for(int i = 0; s[i]; i++) {
		vis[pos] = min(vis[pos], i+1);
		pos = go[pos][s[i]-'a'];
	}
	vis[pos] = min(vis[pos], n);
	for(int x: order) {
		vis[suf[x]] = min(vis[suf[x]], vis[x]);
		for(auto &p: term[x]) seen[p.first] = min(seen[p.first], vis[x] - p.second);
	}
	for(int i = 0; i<m; i++) printf("%d%c", seen[i] <= n ? seen[i] : -1, " \n"[i+1==m]);
	return 0;
}

