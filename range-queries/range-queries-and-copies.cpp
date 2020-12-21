#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
const ll inf = 1e18;
int n, q, a[maxn];
ll ft[maxn], ans[maxn];

void upd(int pos, int x) {
	while(pos <= n) ft[pos] += x, pos += pos & (-pos);
}

ll getsum(int l, int r) {
	ll res = 0;
	l--;
	while(r > 0) res += ft[r], r &= r-1;
	while(l > 0) res -= ft[l], l &= l-1;
	return res;
}

struct query { int id, type, k, a, b; };
vector<query> qs[maxn];

void dfs(int id, int l) {
	if (qs[id].size() <= l) return;
	query &cur = qs[id][l];
	if (cur.type == 1) {
		assert(id == cur.k);
		int pval = a[cur.a];
		int diff = cur.b - pval;
		a[cur.a] = cur.b;
		upd(cur.a, diff);
		dfs(id, l+1);
		upd(cur.a, -diff);
		a[cur.a] = pval;
	} else if (cur.type == 2) {
		ans[cur.id] = getsum(cur.a, cur.b);
		dfs(id, l+1);
	} else if (cur.type == 3) {
		dfs(cur.a, 0);
		dfs(id, l+1);
	}
}

int main(){
	scanf("%d %d", &n, &q);
	for(int i = 1; i<=n; i++) scanf("%d", &a[i]), upd(i, a[i]); 
	int ars = 1;
	for(int i = 1; i<=q; i++) {
		ans[i] = inf;
		query t;
		t.id = i;
		scanf("%d", &t.type);
		if (t.type <= 2) scanf("%d %d %d", &t.k, &t.a, &t.b);
		else if (t.type == 3) scanf("%d", &t.k), t.a = ++ars;
		qs[t.k].push_back(t);
	}
	dfs(1, 0);
	for(int i = 1; i<=q; i++) if (ans[i] != inf) printf("%lld\n", ans[i]);
	return 0;
}

