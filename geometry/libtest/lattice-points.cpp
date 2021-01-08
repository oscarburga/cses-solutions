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

/*
Pick's theorem:
	* I: Lattice points strictly in the interior
	* B: Lattice points on the boundary of polygon
	* A: Area of polygon
	A = I + (B/2) - 1;
	2A - B + 2 = 2I
*/

namespace Geo { 
	template<typename V> //returns tuple of I, B, 2A
	tuple<long long, long long, long long> lattice_points(const int n, V& pts) {
		long long area = 0, B = 0, I;
		for(int i = 0; i<n; i++) {
			pt<long long> &p = pts[i], &q = pts[(i+1)%n], d1;
			area += p % q;
			d1 = q-p;
			B += __gcd(abs(d1.x), abs(d1.y));
		}
		area = abs(area);
		I = (area - B + 2) >> 1;
		return { I, B, area };
	}
}

const int maxn = 1e5+5;

int n;
pt<ll> pts[maxn];


int main(){
	scanf("%d", &n);
	for(int i = 0; i<n; i++) read(pts[i]);
	auto t = Geo::lattice_points(n, pts);
	printf("%lld %lld\n", get<0>(t), get<1>(t));
	return 0;
}

