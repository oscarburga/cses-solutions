#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5, maxs = 5e5+5;

bool seen[maxs], vis[maxs];
int m, nodes = 1, go[maxs][26], suf[maxs];
vector<int> term[maxs]; 
char s[maxn], t[maxs];

int main(){
	scanf("%s", s);
	scanf("%d", &m);
	for(int i = 0; i<m; i++) {
		scanf("%s", t);
		int pos = 0;
		for(int j = 0, nxt; t[j]; j++) {
			nxt = t[j] - 'a';
			if (!go[pos][nxt]) go[pos][nxt] = nodes++;
			pos = go[pos][nxt];
		}
		term[pos].emplace_back(i);
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
	int pos = 0;
	for(int i = 0; s[i]; i++) vis[pos] = true, pos = go[pos][s[i]-'a'];
	vis[pos] = true;
	for(int x: order) {
		vis[suf[x]] |= vis[x];
		if (vis[x]) for(int i: term[x]) seen[i] = true;
	}
	for(int i = 0; i<m; i++) puts(seen[i] ? "YES" : "NO");
	return 0;
}

