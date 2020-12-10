#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct dset{
	vector<int> p, sz;
	dset(int n): p(n, -1), sz(n, 1) {}
	int find(int x) { return p[x] == -1 ? x : p[x] = find(p[x]); }
	bool join(int x, int y) {
		x = find(x), y = find(y);
		if (x == y) return false;
		if (sz[x] < sz[y]) swap(x, y);
		sz[x] += sz[y];
		p[y] = x;
		return true;
	}
};

int n, m;

int main(){
	scanf("%d %d", &n, &m);
	dset dsu(n);
	int ans = n, mx = 1;
	for(int i = 0; i<m; i++){
		int x, y;
		scanf("%d %d", &x, &y);
		x--, y--;
		ans -= dsu.join(x, y);
		mx = max(mx, dsu.sz[dsu.find(x)]);
		printf("%d %d\n", ans, mx);
	}

	return 0;
}

