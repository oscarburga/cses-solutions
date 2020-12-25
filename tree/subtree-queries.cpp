#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, q, tmr = 1, a[maxn], tin[maxn], tout[maxn];
ll ft[maxn];
vector<int> vs[maxn];

void upd(int pos, int val) {
	while (pos <= n) ft[pos] += val, pos += pos & (-pos);
}

ll query(int pos) {
	ll res = 0;
	while (pos > 0) res += ft[pos], pos &= pos-1;
	return res;
}

void dfs(int v, int p = -1) {
	tin[v] = tmr++;
	upd(tin[v], a[v]);
	for(int e: vs[v]) if (e != p) dfs(e, v);
	tout[v] = tmr;
}

int main(){
	scanf("%d %d", &n, &q);
	for(int i = 1; i<=n; i++) scanf("%d", &a[i]);
	for(int i = 1; i<n; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		vs[x].push_back(y);
		vs[y].push_back(x);
	}
	dfs(1);
	while(q--) {
		int t;
		scanf("%d", &t);
		if (t == 1) {
			int s, x;
			scanf("%d %d", &s, &x);
			int dif = x - a[s];
			upd(tin[s], dif);
			a[s] = x;
		} else {
			int s;
			scanf("%d", &s);
			printf("%lld\n", query(tout[s]-1) - query(tin[s]-1));
		}
	}
	return 0;
}

