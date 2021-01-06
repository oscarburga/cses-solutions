#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct pt {
	int x, y;
	pt operator + (pt p) { return { x + p.x, y + p.y }; }
	pt operator - (pt p) { return { x - p.x, y - p.y }; }
	ll operator % (pt p) { return 1ll * x * p.y - 1ll * y * p.x; }
	ll operator * (pt p) { return 1ll * x * p.x + 1ll * y * p.y; }
	inline void read() { scanf("%d %d", &x, &y); }
};

inline bool seghas(pt p, pt q, pt r) {
	return ((p-r) % (q-r) == 0) && ((p-r) * (q-r) <= 0); 
}

inline int sgn(ll x) { return (x > 0) - (x < 0); }

int main(){
	int tc;
	scanf("%d", &tc);
	while(tc--) {
		pt p, q, u, v;
		p.read(), q.read(), u.read(), v.read();
		pt d1 = q-p, d2 = v-u;
		bool inter = false;
		if (d1 % d2 == 0) {
			inter |= seghas(p, q, u) || seghas(p, q, v);
			inter |= seghas(u, v, p) || seghas(u, v, q);
		} else {
			inter = true;
			ll num1 = (u-p) % d2;
			ll den1 = d1 % d2;
			ll num2 = (p-u) % d1;
			ll den2 = d2 % d1;
			inter &= (sgn(num1) == 0) || (sgn(num1) == sgn(den1));
			inter &= (sgn(num2) == 0) || (sgn(num2) == sgn(den2));
			inter &= abs(num1) <= abs(den1);
			inter &= abs(num2) <= abs(den2);
		}
		if (inter) puts("YES");
		else puts("NO");
	}
	return 0;
}
