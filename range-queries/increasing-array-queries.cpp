#include <bits/stdc++.h>
#define debug(...) fprintf(stderr, __VA_ARGS__)
using namespace std;
using ll = long long;

const int maxn = 2e5+5, inf = 1e9+7;
int n, q, a[maxn], lazy[maxn<<2];
ll st[maxn<<2], pre[maxn], ans[maxn];

void push(int pos, int l, int r) { 
	if (!lazy[pos]) return;
	st[pos] = 1ll * lazy[pos] * (r-l+1);
	if (l < r) lazy[pos<<1] = lazy[pos<<1|1] = lazy[pos];
	lazy[pos] = 0;
}

void upd(int ql, int qr, int v, int pos = 1, int l = 1, int r = n) { 
	push(pos, l, r);
	if (r < ql or l > qr) return;
	if (ql <= l && r <= qr) { 
		lazy[pos] = v;
		push(pos, l, r);
		return;
	}
	int mid = (l+r) >> 1, child = pos<<1;
	upd(ql, qr, v, child, l, mid);
	upd(ql, qr, v, child|1, mid+1, r);
	st[pos] = st[child] + st[child|1];
}

ll query(int ql, int qr, int pos = 1, int l = 1, int r = n) { 
	push(pos, l, r);
	if (r < ql or l > qr) return 0;
	if (ql <= l && r <= qr) return st[pos];
	int mid = (l+r) >> 1, child = pos<<1;
	return query(ql, qr, child, l, mid) + query(ql, qr, child|1, mid+1, r);
}

vector<pair<int,pair<int,int>>> stk;
vector<pair<int,int>> qs[maxn];

int main(){
	scanf("%d %d", &n, &q);
	for(int i = 1; i<=n; i++) {
		scanf("%d", &a[i]), 
		pre[i] = pre[i-1] + a[i];
	}
	for(int i = 0, l, r; i<q; i++) {
		scanf("%d %d", &l, &r);
		qs[l].emplace_back(r, i);
	}
	stk.emplace_back(inf, make_pair(n+1, n+1));
	for(int i = n, r; i > 0; --i) {
		r = i;
		while (stk.back().first < a[i]) {
			r = stk.back().second.second;
			stk.pop_back();
		}
		stk.emplace_back(a[i], make_pair(i, r));
		upd(i, r, a[i]);
		for(auto &p: qs[i]) ans[p.second] = query(i, p.first) - pre[p.first] + pre[i-1];
	}
	for(int i = 0; i<q; i++) printf("%lld\n", ans[i]);
	return 0;
}

