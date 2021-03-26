#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define debug(...) fprintf(stderr, __VA_ARGS__)

// Coding random CSES problems in C because I was bored

#define maxn 200005
typedef long long ll;
typedef struct Query { int id, t, a, b; } Query;

int n, q, v_cnt = 1, a[maxn];
int sz[maxn], cap[maxn];
Query *qs[maxn];

ll ans[maxn], pre[maxn], ft[maxn];

void vec_init(int id) {
	if (cap[id] > 0) return;
	cap[id] = 8;
	qs[id] = (Query*) malloc(8 * sizeof(Query));
}

void vec_readq(int qid) {
	int t, k, idx;
	scanf("%d %d", &t, &k);
	vec_init(k);
	idx = sz[k];
	if (sz[k] == cap[k]) qs[k] = (Query*) realloc(qs[k], (cap[k] <<= 1) * sizeof(Query));
	qs[k][idx].id = qid;
	qs[k][idx].t = t;
	if (t <= 2) scanf("%d %d", &qs[k][idx].a, &qs[k][idx].b);
	else qs[k][idx].a = ++v_cnt;
	++sz[k];
}

void ft_upd(int pos, int val) { 
	while (pos <= n) ft[pos] += val, pos += pos & (-pos); 
}

ll ft_query(int pos) {
	ll ret = 0;
	while (pos > 0) ret += ft[pos], pos &= pos-1;
	return ret;
}

void dfs(int k, int l) { 
	if (l >= sz[k]) return;
	Query *q = &qs[k][l];
	if (q->t == 1) {
		int old = a[q->a];
		ft_upd(q->a, q->b - old);
		a[q->a] = q->b;
		dfs(k, l+1);
		a[q->a] = old;
		ft_upd(q->a, old - q->b);
	} else if (q->t == 2) {
		ans[q->id] = ft_query(q->b) - ft_query(q->a - 1);
		dfs(k, l+1);
	} else if (q->t == 3) dfs(q->a, 0), dfs(k, l+1); 

}

int main() {
	scanf("%d %d", &n, &q);
	for(int i = 1; i<=n; i++) {
		scanf("%d", &a[i]);
		pre[i] = pre[i-1] + a[i];
		ft[i] = pre[i] - pre[i&(i-1)];
	}
	for(int i = 0; i<q; i++) vec_readq(i);
	dfs(1, 0);
	for(int i = 0; i<q; i++) if (ans[i] > 0ll) printf("%lld\n", ans[i]);
	return 0;
}

