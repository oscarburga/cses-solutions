#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//solvable offline with regular fenwick/segment tree
//i wanted to practice persistent segment tree impl.

const int maxn = 2e5+5;
int n, m, a[maxn];
map<int,int> last;

struct psegtree {
	int nodes = 0;
	vector<int> st, L, R, root;

	psegtree() {
		root.push_back(nodes++);
		addnode();
		build(root.back());
	}

	void addnode(int x = 0) {
		st.push_back(x);
		L.push_back(-1);
		R.push_back(-1);
	}

	void build(int pos, int l = 1, int r = n) {
		if (l == r) return;
		int mid = (l+r) >> 1;
		L[pos] = nodes++, addnode();
		R[pos] = nodes++, addnode();
		build(L[pos], l, mid);
		build(R[pos], mid+1, r);
	}
	
	void upd(int i, int v, int last, int pos, int l = 1, int r = n) {
		if (l == r) { st[pos] = v; return; }
		int mid = (l+r) >> 1;
		if (i <= mid) {
			if (L[pos] == -1) L[pos] = nodes++, addnode(st[L[last]]);
			if (R[pos] == -1) R[pos] = R[last];
			upd(i, v, L[last], L[pos], l, mid);
		} else {
			if (L[pos] == -1) L[pos] = L[last];
			if (R[pos] == -1) R[pos] = nodes++, addnode(st[R[last]]);
			upd(i, v, R[last], R[pos], mid+1, r);
		}
		st[pos] = st[L[pos]] + st[R[pos]];
	}

	int query(int ql, int qr, int pos = 1, int l = 1, int r = n) {
		if (r < ql or l > qr) return 0;
		if (ql <= l && r <= qr) return st[pos];
		int mid = (l+r) >> 1;
		return query(ql, qr, L[pos], l, mid) + query(ql, qr, R[pos], mid+1, r);
	}

	void upd(int i) {
		root.push_back(nodes++);
		addnode();
		if (last.count(a[i])) upd(last[a[i]], 0, root[i-1], root[i]);
		upd(last[a[i]] = i, 1, root[i-1], root[i]);
	}

	int getans(int ql, int qr) { return query(ql, qr, root[qr]); }
};

int main(){
	scanf("%d %d", &n, &m);
	psegtree st;
	for(int i = 1; i<=n; i++) {
		scanf("%d", &a[i]);
		st.upd(i);
	}
	while(m--) {
		int l, r;
		scanf("%d %d", &l, &r);
		printf("%d\n", st.getans(l, r));
	}
	return 0;
}

