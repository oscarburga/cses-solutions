#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
inline int randp() { return uniform_int_distribution<int>(INT_MIN, INT_MAX)(rng); }

struct node {
	int v, p, sz;
	bool rev;
	node *L, *R, *par;
	node(int v = 0) : v(v), p(randp()), sz(v > 0), rev(false), L(nullptr), R(nullptr), par(nullptr) {};
} nodes[maxn], *root = nullptr;

inline int sz(node *t) { return t ? t->sz : 0; }

inline void upd_node(node *t) {
	if (!t) return;
	t->sz = 1 + sz(t->L) + sz(t->R);
	t->par = nullptr;
	if (t->L) t->L->par = t;
	if (t->R) t->R->par = t;
}

inline void push(node *t) {
	if (t == nullptr or t->rev == false) return;
	swap(t->L, t->R);
	if (t->L) t->L->rev ^= 1;
	if (t->R) t->R->rev ^= 1;
	t->rev = 0;
}

pair<node*, node*> split(node *t, int x, int add = 0) {
	push(t);
	if (!t) return { nullptr, nullptr };
	int k = add + sz(t->L) + 1;
	pair<node*, node*> p;
	if (k <= x) {
		p = split(t->R, x, k);
		t->R = p.first;
		upd_node(t);
		return { t , p.second };
	} else {
		p = split(t->L, x, add);
		t->L = p.second;
		upd_node(t);
		return { p.first, t };
	}
}

node *merge(node *t1, node *t2) {
	push(t1), push(t2);
	if (!t1) return t2;
	if (!t2) return t1;
	if (t1->p > t2->p) {
		t1->R = merge(t1->R, t2);
		upd_node(t1);
		return t1;
	} else {
		t2->L = merge(t1, t2->L);
		upd_node(t2);
		return t2;
	}
}

vector<node*> aux;
int order(node *t) {
	node *tcopy = t;
	aux.clear();
	while(t) aux.emplace_back(t), t = t->par;
	reverse(aux.begin(), aux.end());
	for(auto &p: aux) push(p);
	t = tcopy;
	int res = sz(t->L) + 1;
	while(t->par) {
		bool addl = t->par->R == t;
		t = t->par;
		res += (sz(t->L) + 1) * addl;
	}
	return res;
}

int n;

int main(){
	scanf("%d", &n);
	for(int i = 1, x; i<=n; i++) {
		scanf("%d", &x);
		root = merge(root, &(nodes[x] = node(x)));
	}
	vector<pair<int,int>> ans;
	for(int i = 1; i<=n; i++) {
		int k = order(&nodes[i]);
		if (k == i) continue;
		assert(i < k);
		auto p = split(root, k);
		auto q = split(p.first, i-1);
		q.second->rev ^= 1;
		root = merge(q.first, q.second);
		root = merge(root, p.second);
		ans.emplace_back(i, k);
	}
	printf("%zu\n", ans.size());
	for(auto&p: ans) printf("%d %d\n", p.first, p.second);
	return 0;
}

