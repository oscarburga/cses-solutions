#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 4e5+5;
int n, q, tmr = 1, a[maxn], tin[maxn], tout[maxn], tour[maxn];
ll ft[maxn];
vector<int> vs[maxn];

void upd(int pos, int val) {
	while(pos <= n+n) ft[pos] += val, pos += pos & (-pos);
}

ll query(int pos) {
	ll ret = 0;
	while(pos > 0) ret += ft[pos], pos &= pos-1;
	return ret;
}

void dfs(int v, int p = -1) {
	upd(tmr, a[v]);
	tour[tin[v] = tmr++] = a[v];
	for(int e: vs[v]) if (e != p) dfs(e, v);
	upd(tmr, -a[v]);
	tour[tout[v] = tmr++] = -a[v];
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
			int d1 = x - a[s];
			int d2 = -x + a[s];
			upd(tin[s], d1);
			upd(tout[s], d2);
			a[s] = x;
		} else {
			int s;
			scanf("%d", &s);
			printf("%lld\n", query(tin[s]));
		}
	}
	return 0;
}

