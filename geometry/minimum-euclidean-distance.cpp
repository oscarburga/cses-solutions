#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;

using pt = pair<ll,ll>;
int n;
pt pts[maxn];

inline ll sqr(ll x) { return x * x; }
inline ll dis(const pt &p, const pt &q) {
	return sqr(q.first - p.first) + sqr(q.second - p.second);
}

int main(){
	scanf("%d", &n);
	ll best = LLONG_MAX;
	set<pt> st;
	for(int i = 0; i<n; i++) scanf("%lld %lld", &pts[i].first, &pts[i].second);
	sort(pts, pts+n);
	for(int i = 0, j = 0; i<n; i++) {
		while (j < i && sqr(pts[j].first - pts[i].first) >= best) {
			st.erase(make_pair(pts[j].second, pts[j].first));
			j++;
		}
		ll d = sqrt(best);
		d += 1;
		ll lo = pts[i].second - d;
		ll hi = pts[i].second + d;
		auto it = st.lower_bound({ lo, LLONG_MIN });
		pt p = pts[i];
		swap(p.first, p.second);
		for(; it != st.end() && it->first <= hi; it++) best = min(best, dis(p, *it));
		st.insert(p);
	}
	printf("%lld\n", best);
	return 0;
}

