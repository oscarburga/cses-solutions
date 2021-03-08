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
	int v, p, sz;
	long long sum;
	char rev;
	node *L, *R;
};

int node_cnt;
node *root = NULL;
node default_node = (node){ 0, 0, 0, 0, 0, NULL, NULL };
node nodes[maxn];

node* makenode(int v) { 
	nodes[node_cnt] = (node) { .v = v, .p = genrand(), .sz = 1, .sum = v, .rev = 0, .L = NULL, .R = NULL };
	return &nodes[node_cnt++];
}

node* getn(node *t) { return t == NULL ? &default_node : t; }
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
	t->sz = 1 + getn(t->L)->sz + getn(t->R)->sz;
	t->sum = t->v + getn(t->L)->sum + getn(t->R)->sum;
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
	int k = getn(t->L)->sz + add + 1;
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

int n, q;

int main(){
	init_random();
	scanf("%d %d\n", &n, &q);
	for(int i = 0, x; i<n; i++) {
		scanf("%d", &x);
		root = merge(root, makenode(x));
	}
	for(int t, a, b; q--; ) {
		scanf("%d %d %d", &t, &a, &b);
		pair_nodes p = split(root, b, 0);
		pair_nodes q = split(p.first, a-1, 0);
		if (t == 2) printf("%lld\n", getn(q.second)->sum);
		else q.second->rev ^= 1;
		root = merge(q.first, q.second);
		root = merge(root, p.second);
	}
	return 0;
}

