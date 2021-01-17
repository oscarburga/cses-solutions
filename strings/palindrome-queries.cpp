#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;

using Hash = array<int, 2>;
const Hash mod = { int(1e9)+7, int(1e9)+9 };
const Hash bas = { 31, 37 };
const Hash ibas = { 129032259, 297297300 };
const Hash zero = { 0, 0 };
vector<Hash> pwr, inv;
inline int add(int x, int y, const int m) { return (x+y) % m; }
inline int sub(int x, int y, const int m) { return (((x-y) % m) + m) % m; }
inline int mul(int x, int y, const int m) { return (1ll * x * y) % m; }
Hash& operator += (Hash &p, const Hash &q) { 
	p[0] = add(p[0], q[0], mod[0]), p[1] = add(p[1], q[1], mod[1]);
	return p;
}
Hash operator + (const Hash &p, const Hash &q) { 
	return Hash{ add(p[0], q[0], mod[0]), add(p[1], q[1], mod[1]) };
}
Hash operator - (const Hash &p, const Hash &q) {
	return Hash{ sub(p[0], q[0], mod[0]), sub(p[1], q[1], mod[1]) };
}
Hash operator * (const Hash &p, const Hash &q) {
	return Hash{ mul(p[0], q[0], mod[0]), mul(p[1], q[1], mod[1]) };
}
Hash make_hash(signed char c, int i = 0) { return Hash{ c - 'a' + 1, c - 'a' + 1 } * pwr[i]; }

void init(const int n) {
	pwr.resize(n+1), inv.resize(n+1);
	pwr[0] = inv[0] = { 1, 1 };
	for(int i = 1; i<=n; i++) {
		pwr[i] = pwr[i-1] * bas;
		inv[i] = inv[i-1] * ibas;
	}
}

int n, q;
char s[maxn];
Hash ft[2][maxn];
void upd(int id, int pos, const Hash& val) {
	if (id == 1) pos = n - pos + 1;
	while(pos <= n) ft[id][pos] += val, pos += pos & (-pos);
}

Hash query(int id, int pos) {
	Hash res = zero;
	if (id == 1) pos = n - pos + 1;
	while(pos > 0) res += ft[id][pos], pos &= pos - 1;
	return res;
}

int main(){
	scanf("%d %d", &n, &q);
	init(n+1);
	scanf("%s", s+1);
	for(int i = 1; i<=n; i++) {
		upd(0, i, make_hash(s[i], i));
		upd(1, i, make_hash(s[i], n-i+1));
	}
	for(int i = 0, t; i<q; i++) {
		scanf("%d", &t);
		if (t == 1) {
			int k; char x;
			scanf("%d %c", &k, &x);
			upd(0, k, make_hash(s[k], k) * Hash{ -1, -1 });
			upd(1, k, make_hash(s[k], n-k+1) * Hash{ -1, -1 });
			upd(0, k, make_hash(x, k));
			upd(1, k, make_hash(x, n-k+1));
			s[k] = x;
		} else if (t == 2) {
			int l, r;
			scanf("%d %d", &l, &r);
			int len = r-l+1;
			int half = (len >> 1);
			Hash L = (query(0, l+half-1) - query(0, l-1)) * inv[l];
			Hash R = (query(1, r-half+1) - query(1, r+1)) * inv[n - r + 1];
			puts(L == R ? "YES" : "NO");
		} else assert(0);
	}
	return 0;
}

