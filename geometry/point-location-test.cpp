#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct pt {
	ll x, y;
	pt operator - (pt p) { return { x - p.x, y - p.y }; }
	ll operator % (pt p) { return x * p.y - y * p.x; }
	void read() { scanf("%lld %lld", &x, &y); }
};

int main(){
	int tc;
	scanf("%d", &tc);
	while(tc--) {
		pt p, q, r;
		p.read();
		q.read();
		r.read();
		ll t = (q-p) % (r-p);
		puts(t > 0ll ? "LEFT" : t < 0ll ? "RIGHT" : "TOUCH");
	}

	return 0;
}

