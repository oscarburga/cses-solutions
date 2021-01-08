#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

const long double eps = 1e-9;
template<typename T> int sgn(T x) { return (x > 0) - (x < 0); }
template<> int sgn(long double x) { return (x > eps) - (x < -eps); }

template<typename T> 
struct pt { 
	T x, y;
	explicit pt(T x = 0, T y = 0) : x(x), y(y) {}
	template<typename R> explicit pt(const pt<R> &p) : x(p.x), y (p.y) {}
	pt& operator += (const pt &p) { x += p.x, y += p.y; return *this; }
	pt& operator -= (const pt &p) { x -= p.x, y -= p.y; return *this; }
	pt& operator *= (const T &k) { x *= k, y *= k; return *this; }
	pt& operator /= (const T &k) { x /= k, y /= k; return *this; }
	friend pt operator + (const pt &p, const pt &q) { return pt(p.x + q.x, p.y + q.y); }
	friend pt operator - (const pt &p, const pt &q) { return pt(p.x - q.x, p.y - q.y); }
	friend pt operator * (const pt &p, const T &k) { return pt(p.x * k, p.y * k); }
	friend pt operator / (const pt &p, const T &k) { return pt(p.x / k, p.y / k); }
	friend pt ccw90(const pt &p) { return pt(-p.y, p.x); }
	friend pt cw90(const pt &p) { return pt(p.y, -p.x); }
	friend pt swapxy(const pt &p) { return pt(p.y, p.x); }
	friend pt<long double> unit(const pt &p) { return pt<long double>(p) / len(p); }
	friend pt<long double> rot(const pt &p, const long double &t) { 
		long double cost = cosl(t), sint = sinl(t);
		return pt<long double>(cost * p.x - sint * p.y, sint * p.x + cost * p.y); 
	}
	friend T operator * (const pt &p, const pt &q) { return p.x * q.x + p.y * q.y; }
	friend T operator % (const pt &p, const pt &q) { return p.x * q.y - p.y * q.x; }
	friend T len2(const pt &p) { return p.x * p.x + p.y * p.y; }
	friend T dis2(const pt &p, const pt &q) { return (q-p) * (q-p); }
	friend long double len(const pt &p) { return sqrtl(len2(p)); }
	friend long double dis(const pt &p, const pt &q) { return sqrtl(dis2(p, q)); }
	friend long double angle(const pt &p, const pt &q) { return atan2l(p % q, p * q); }
	friend ostream& operator << (ostream &o, const pt &p) { return o<<'('<<p.x<<", "<<p.y<<")\n"; }
	bool operator == (const pt<long long> &q) const { return x == q.x && y == q.y; }
	bool operator == (const pt<long double> &q) const { return sgn(x - q.x) == 0 && sgn(y - q.y) == 0; }
	bool operator < (const pt<long long> &q) const { return (x < q.x) || (x == q.x && y < q.y); }
	bool operator < (const pt<long double> &q) const { 
		return (x < q.x - eps) || (sgn(x - q.x) == 0 && y < q.y - eps); 
	}
};

void read(pt<long double> &p) { scanf("%Lf %Lf", &p.x, &p.y); }
void read(pt<long long> &p) { scanf("%lld %lld", &p.x, &p.y); }

namespace Geo {
	template<typename T, typename V, T Eps = T(1)>  //use Eps = 1e-9 for doubles
	pair<pt<T>, pt<T>> closest_pair(const int n, V& pts) {
		sort(begin(pts), begin(pts)+n);
		set<pt<T>> st;
		pt<T> p;
		T best = 8e18;
		pair<pt<T>, pt<T>> ret = make_pair(p, p);
		#define sqr(x) ((x)*(x))
		for(int i = 0, j = 0; i<n; i++) {
			p = pts[i];
			while(j < i && sqr(p.x - pts[j].x) >= best) st.erase(swapxy(pts[j++]));
			T cur = sqrtl(best);
			T lo = p.y - cur - Eps;
			T hi = p.y + cur + Eps;
			auto it = st.lower_bound(pt<T>(lo, -8e18));
			p = swapxy(p);
			for(; it != st.end() && it->x <= hi; it++) {
				T aux = dis2(p, *it);
				if (aux < best) ret = make_pair(p, *it), best = aux;
			}
			st.insert(p);
		}
		#undef sqr
		return make_pair(swapxy(ret.first), swapxy(ret.second));
	}
};

int n;
vector<pt<ll>> pts;

int main(){
	scanf("%d", &n);
	pts.resize(n);
	for(auto&p: pts) read(p);
	auto cp = Geo::closest_pair<ll>(n, pts);
	printf("%lld\n", dis2(cp.first, cp.second));
	return 0;
}

