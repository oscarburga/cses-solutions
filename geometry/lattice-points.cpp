#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
Pick's theorem: 
	* I: Lattice points strictly in the interior
	* B: Lattice points on the boundary of polygon
	* A: Area of polygon
	A = I + (B/2) - 1;
	2A = 2I + B - 2;
	2A - B + 2 = 2I
*/

const int maxn = 1e5+5;

int n;
struct pt {
	int x, y;
	pt operator + (pt p) { return { x + p.x, y + p.y }; }
	pt operator - (pt p) { return { x - p.x, y - p.y }; }
	ll operator % (pt p) { return 1ll * x * p.y - 1ll * y * p.x; }
} pts[maxn];

int main(){
	scanf("%d", &n);
	for(int i = 0; i<n; i++) scanf("%d %d", &pts[i].x, &pts[i].y);
	ll area = 0, B = 0;
	for(int i = 0; i<n; i++) {
		pt &p = pts[i], &q = pts[(i+1)%n];
		area += pts[i] % pts[(i+1)%n];
		pt d1 = q-p;
		B += __gcd(abs(d1.x), abs(d1.y));
	}
	area = abs(area);
	assert((area - B + 2)%2 == 0);
	printf("%lld %lld\n", (area - B + 2) >> 1, B);
	return 0;
}

