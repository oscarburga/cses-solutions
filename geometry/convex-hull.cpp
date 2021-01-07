#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
const int maxn = 2e5+5; 
 
int n;
struct pt {
	int x, y;
	pt operator + (pt p) { return { x + p.x, y + p.y }; }
	pt operator - (pt p) { return { x - p.x, y - p.y }; }
	ll operator % (pt p) { return 1ll * x * p.y - 1ll * y * p.x; }
	bool operator == (pt p) { return x == p.x && y == p.y; }
} pts[maxn];
vector<pt> up, lo;
 
int main(){
	scanf("%d", &n);
	for(int i = 0; i<n; i++) scanf("%d %d", &pts[i].x, &pts[i].y);
	//For this problem you should include collinear points in the convex hull, even though
	//it's not mentioned in the statement. Costed me 2 WAs.
	sort(pts, pts+n, [&](pt &p, pt &q) { return p.x < q.x || (p.x == q.x && p.y < q.y); });
	up.reserve(maxn);
	lo.reserve(maxn);
	int l1 = 0, l2 = 0;
	for(int i = 0; i<n; i++) {
		while(l1 > 1 && (up[l1-1]-up[l1-2]) % (pts[i]-up[l1-2]) > 0) up.pop_back(), --l1;
		up.emplace_back(pts[i]);
		l1++;
		while(l2 > 1 && (lo[l2-1]-lo[l2-2]) % (pts[i]-lo[l2-2]) < 0) lo.pop_back(), --l2;
		lo.emplace_back(pts[i]);
		l2++;
	}
	reverse(up.begin(), up.end());
	lo.pop_back();
	lo.insert(lo.end(), up.begin(), up.end());
	lo.pop_back();
	printf("%zu\n", lo.size());
	for(auto&p: lo) printf("%d %d\n", p.x, p.y);
	return 0;
}
