#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 4e5+5;
int n, tmr = 1, a[maxn], tin[maxn], tout[maxn], tour[maxn], qu[maxn], ans[maxn];
ll ft[maxn];
vector<int> vs[maxn];

map<int,int> last;

void dfs(int v, int p = -1) {
	tour[tmr] = a[v];
	tin[v] = tmr++;
	for(int e: vs[v]) if (e != p) dfs(e, v);
	tour[tmr] = a[v];
	qu[tmr] = v;
	tout[v] = tmr++;
}

void upd(int pos, int val) {
	while(pos <= n+n) ft[pos] += val, pos += pos & (-pos);	
}

ll query(int pos) {
	ll res = 0;
	while(pos > 0) res += ft[pos], pos &= pos-1;
	return res;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i<=n; i++) scanf("%d", &a[i]);
	for(int i = 1; i<n; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		vs[x].push_back(y);
		vs[y].push_back(x);
	}
	dfs(1);
	for(int i = 1; i<=n+n; i++) {
		if (last.count(tour[i])) upd(last[tour[i]], -1);
		upd(last[tour[i]] = i, 1);
		if (qu[i] != 0) ans[qu[i]] = query(i) - query(tin[qu[i]]-1);
	}
	for(int i = 1; i<=n; i++) printf("%d%c", ans[i], " \n"[i==n]);
	return 0;
}

