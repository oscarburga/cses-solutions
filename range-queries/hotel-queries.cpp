#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, m, a[maxn], st[4*maxn];

void build(int pos = 1, int l = 1, int r = n) {
	if (l == r) { st[pos] = a[l]; return; }
	int mid = (l+r) >> 1;
	build(2*pos, l, mid);
	build(2*pos+1, mid+1, r);
	st[pos] = max(st[2*pos], st[2*pos+1]);
}

void query(int x, int pos = 1, int l = 1, int r = n) {
	if (st[pos] < x) { printf("0 "); return; }
	if (l == r) { 
		st[pos] -= x; 
		printf("%d ", l); 
		return;
	}
	int mid = (l+r) >> 1;
	if (st[2*pos] >= x) query(x, 2*pos, l, mid);
	else query(x, 2*pos+1, mid+1, r);
	st[pos] = max(st[2*pos], st[2*pos+1]);
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i<=n; i++) scanf("%d", &a[i]);
	build();
	while (m--) {
		int x;
		scanf("%d", &x);
		query(x);
	}
	puts("");
	return 0;
}

