#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e3+5;
int n, q;
struct pt {
	int x, y;
	pt operator - (pt p) { return { x - p.x, y - p.y }; }
	ll operator % (pt p) { return 1ll * x * p.y - 1ll * y * p.x; }
	ll operator * (pt p) { return 1ll * x * p.x + 1ll * y * p.y; }
} pts[maxn];

int main(){
	scanf("%d %d", &n, &q);
	for(int i = 0; i<n; i++) scanf("%d %d", &pts[i].x, &pts[i].y);
	while(q--) {
		pt u;
		scanf("%d %d", &u.x, &u.y);
		bool onedge = false, inters = false;
		pt p, q;
		for(int i = 0; i<n && !onedge; i++) {
			p = pts[i], q = pts[(i+1)%n];
			onedge |= ((p-u) % (q-u) == 0) && ((p-u) * (q-u) <= 0);
			if (p.y < q.y) swap(p, q);
			inters ^= (p.y >= u.y) && (q.y < u.y) && ((q-p) % (u-p) < 0ll);
		}
		if (onedge) puts("BOUNDARY");
		else if (inters) puts("INSIDE");
		else puts("OUTSIDE");
	}
	return 0;
}

