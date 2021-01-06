#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e3+5;

struct pt {
	ll x, y;
	ll operator % (pt p) { return x * p.y - y * p.x; }
} pts[maxn];
int n;

int main(){
	scanf("%d", &n);
	for(int i = 0; i<n; i++) scanf("%lld %lld", &pts[i].x, &pts[i].y);
	ll t = 0;
	for(int i = 0; i<n; i++) {
		t += pts[i] % pts[(i+1)%n];
	}
	printf("%lld\n", abs(t));
	return 0;
}

