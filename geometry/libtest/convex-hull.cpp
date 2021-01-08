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
	friend pt<long double> unit(const pt &p) { return pt<long double>(p) / len(p); }
	friend pt<long double> rot(const pt &p, const long double &t) { 
		long double cost = cosl(t), sint = sinl(t);
		return pt<long double>(cost * p.x - sint * p.y, sint * p.x + cost * p.y); 
	}
	friend T operator * (const pt &p, const pt &q) { return p.x * q.x + p.y * q.y; }
	friend T operator % (const pt &p, const pt &q) { return p.x * q.y - p.y * q.x; }
	friend T len2(const pt &p) { return p.x * p.x + p.y * p.y; }
	friend T dist2(const pt &p, const pt &q) { return (q-p) * (q-p); }
	friend long double len(const pt &p) { return sqrtl(len2(p)); }
	friend long double dist(const pt &p, const pt &q) { return sqrtl(dist2(p, q)); }
	friend long double angle(const pt &p, const pt &q) { return atan2l(p % q, p * q); }
	friend ostream& operator << (ostream &o, const pt &p) { return o<<'('<<p.x<<", "<<p.y<<")\n"; }
	bool operator == (const pt<long long> &q) { return x == q.x && y == q.y; }
	bool operator == (const pt<long double> &q) { return sgn(x - q.x) == 0 && sgn(y - q.y) == 0; }
	bool operator < (const pt<long long> &q) { return (x < q.x) || (x == q.x && y < q.y); }
	bool operator < (const pt<long double> &q) { return (x < q.x-eps) || (sgn(x-q.x) == 0 && y<q.y-eps); }
};

void read(pt<long double> &p) { scanf("%Lf %Lf", &p.x, &p.y); }
void read(pt<long long> &p) { scanf("%lld %lld", &p.x, &p.y); }

template<typename T>
vector<pt<T>> convex_hull(vector<pt<T>> &pts) { //change comparators >= and <= to strict if need collinears
	sort(pts.begin(), pts.end());
	pts.erase(unique(pts.begin(), pts.end()), pts.end());
	vector<pt<T>> upper, lower;
	for(int i = 0, lu = 0, lo = 0; i<int(pts.size()); i++) { 
		while(lu > 1 && sgn((upper[lu-1] - upper[lu-2]) % (pts[i] - upper[lu-2])) > 0) {
			upper.pop_back(), lu--;
		}
		upper.emplace_back(pts[i]), lu++;
		while(lo > 1 && sgn((lower[lo-1] - lower[lo-2]) % (pts[i] - lower[lo-2])) < 0) {
			lower.pop_back(), lo--;
		}
		lower.emplace_back(pts[i]), lo++;
	}
	reverse(upper.begin(), upper.end());
	lower.pop_back();
	lower.insert(lower.end(), upper.begin(), upper.end());
	lower.pop_back();
	return lower;
}


int n;
vector<pt<ll>> pts;

int main(){
	scanf("%d", &n);
	pts.resize(n);
	for(auto&p: pts) read(p);
	vector<pt<ll>> chull = convex_hull(pts);
	printf("%zu\n", chull.size());
	for(auto&p: chull) printf("%lld %lld\n", p.x, p.y);
	return 0;
}

