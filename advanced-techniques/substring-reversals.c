#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#define debug(...) fprintf(stderr, __VA_ARGS__)

// Coded in C because I was bored :)

#define maxn 200005

// Random code yoinked from Rainboy
unsigned int randval;
void init_random() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	randval = tv.tv_sec ^ tv.tv_usec;
	randval += randval % 2 == 0;
}
int genrand() { return (randval *= 3) >> 1; }

// Treap
typedef struct node node;
typedef struct pair_nodes { node *first, *second; } pair_nodes;
struct node {
	char c, rev;
	int p, sz;
	node *L, *R;
};

int node_cnt;
node *root = NULL, nodes[maxn];

node* makenode(char c) { 
	nodes[node_cnt] = (node){ .c = c, .rev = 0, .p = genrand(), .sz = 1, .L = NULL, .R = NULL };
	return &nodes[node_cnt++];
}

int sz(node *t) { return t == NULL ? 0 : t->sz; }
void push(node *t) {
	if (t == NULL || !t->rev) return;
	node *temp = t->L;
	t->L = t->R;
	t->R = temp;
	if (t->L != NULL) t->L->rev ^= 1;
	if (t->R != NULL) t->R->rev ^= 1;
	t->rev = 0;
}

void upd_node(node *t) {
	if (t == NULL) return;
	t->sz = 1 + sz(t->L) + sz(t->R);
}

node *merge(node *t1, node *t2) { 
	push(t1), push(t2);
	if (t1 == NULL) return t2;
	if (t2 == NULL) return t1;
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

pair_nodes split(node *t, int x, int add) {
	pair_nodes aux = (pair_nodes) { NULL, NULL };
	if (t == NULL) return aux;
	push(t);
	int k = sz(t->L) + add + 1;
	if (k <= x) {
		aux = split(t->R, x, k);
		t->R = aux.first;
		upd_node(t);
		return (pair_nodes) { t, aux.second };
	} else {
		aux = split(t->L, x, add);
		t->L = aux.second;
		upd_node(t);
		return (pair_nodes) { aux.first, t };
	}
}

void dfs(node *t) {
	if (t == NULL) return;
	push(t);
	dfs(t->L);
	putchar(t->c);
	dfs(t->R);
}

int n, q;

int main(){
	init_random();
	scanf("%d %d\n", &n, &q);
	for(int i = 0; i<n; i++) root = merge(root, makenode(getchar()));
	for(int l, r; q--; ) {
		scanf("%d %d", &l, &r);
		pair_nodes p = split(root, r, 0);
		pair_nodes q = split(p.first, l-1, 0);
		if (q.second != NULL) q.second->rev ^= 1;
		root = merge(q.first, q.second);
		root = merge(root, p.second);
	}
	dfs(root);
	return 0;
}

