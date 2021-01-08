#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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
	template<typename T, typename V> // 0 for edge, 1 inside, -1 outside
	int point_in_poly(const int n, const pt<T>& u, const V& pts) {
		bool onedge = false, inters = false;
		pt<T> p, q;
		for(int i = 0; i<n && !onedge; i++) {
			p = pts[i], q = pts[(i+1)%n];
			onedge |= (sgn((p-u) % (q-u)) == 0) && (sgn((p-u) * (q-u)) <= 0);
			if (p.y < q.y) swap(p, q);
			inters ^= (p.y >= u.y) && (q.y < u.y) && (sgn((q-p) % (u-p)) < 0);
		}
		return onedge ? 0 : inters ? 1 : -1;
	}
};

const int maxn = 1e5+5;

int n, q;
pt<ll> pts[maxn];

int main(){
	scanf("%d %d", &n, &q);
	for(int i = 0; i<n; i++) read(pts[i]);
	while(q--) {
		pt<ll> p;
		read(p);
		int pip = Geo::point_in_poly(n, p, pts);
		puts(pip == 0 ? "BOUNDARY" : pip < 0 ? "OUTSIDE" : "INSIDE");
	}
	return 0;
}

