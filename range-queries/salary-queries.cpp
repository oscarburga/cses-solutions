#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;

//Treap is way overkill for this but I wanted to practice my treap impl. :)

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int randp() { return uniform_int_distribution<int>(INT_MIN, INT_MAX)(rng); }

int node_cnt = 0;
struct node {
	int k, p, cnt, sz;
	node *L = nullptr, *R = nullptr;
	node(){}
	node(int _k) : k(_k), p(randp()), cnt(1), sz(1) {}
} nodes[2*maxn];

node *makenode(int x) {
	nodes[node_cnt] = node(x);
	return &nodes[node_cnt++];
}

int sz(node *&cur) { return cur ? cur->sz : 0; }
void upd_node(node *&cur) { if (cur) cur->sz = cur->cnt + sz(cur->L) + sz(cur->R); }

pair<node*, node*> split(int x, node *t) {
	if (!t) return { nullptr, nullptr };
	if (t->k <= x) {
		auto p = split(x, t->R);
		t->R = p.first;
		upd_node(t);
		return { t, p.second };
	} else {
		auto p = split(x, t->L);
		t->L = p.second;
		upd_node(t);
		return { p.first, t };
	}
}

node *merge(node *t1, node *t2) { // t1 <= t2
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

void insert(int x, node *&t) {
	auto p = split(x, t);
	auto q = split(x-1, p.first);
	if (q.second) {
		q.second->cnt++;
		upd_node(q.second);
		t = merge(q.first, q.second);
	} else t = merge(q.first, makenode(x));
	t = merge(t, p.second);
}

void erase(int x, node *&t) { 
	auto p = split(x, t);
	auto q = split(x-1, p.first);
	if (q.second) {
		q.second->cnt--;
		if (q.second->cnt == 0) q.second = nullptr;
		upd_node(q.second);
		t = merge(q.first, q.second);
	} else assert(1 == 2);
	t = merge(t, p.second);
}

int order_of_key(int x, node *t) {
	if (!t) return 0;
	int ret = t->cnt * (t->k <= x);
	if (t->k <= x) ret += sz(t->L) + order_of_key(x, t->R);
	if (t->k > x) ret += order_of_key(x, t->L);
	return ret;
}

int n, q, a[maxn];

int main(){
	scanf("%d %d", &n, &q);
	node *t = nullptr;
	for(int i = 1; i<=n; i++) scanf("%d", &a[i]), insert(a[i], t);
	while(q--) {
		char c; int k, x;
		scanf(" %c %d %d", &c, &k, &x);
		if (c == '!') {
			erase(a[k], t);
			insert(a[k] = x, t);
		} else if (c == '?') printf("%d\n", order_of_key(x, t) - order_of_key(k-1, t));
	}
	return 0;
}

