#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//Substring Order 2 will have to wait until I learn suffix automaton

const int maxn = 1e5+5;

int m[maxn], nm[maxn], head[maxn], sbs[maxn];
void sa_build(const int n, char s[maxn], int a[maxn], int lcp[maxn]) {
	iota(a, a+n, 0);
	sort(a, a+n, [&](int i, int j) { return s[i] < s[j]; });
	m[a[0]] = 0;
	for(int i = 1; i<n; i++) m[a[i]] = m[a[i-1]] + (s[a[i]] != s[a[i-1]]);
	for(int len = 1; len<n; len <<= 1) {
		for(int i = 0; i<n; i++) sbs[i] = (a[i]-len+n) % n;
		for(int i = n-1; i >= 0; i--) head[m[a[i]]] = i;
		for(int i = 0; i<n; i++) a[head[m[sbs[i]]]++] = sbs[i];
		nm[a[0]] = 0;
		for(int i = 1; i<n; i++) {
			if (m[a[i]] != m[a[i-1]]) nm[a[i]] = nm[a[i-1]] + 1;
			else nm[a[i]] = nm[a[i-1]] + (m[(a[i]+len)%n] != m[(a[i-1]+len)%n]);
		}
		swap(m, nm);
	}
	for(int i = 0, k = 0; i+1<n; i++, k -= k > 0) {
		for(int j = a[m[i]-1]; s[i+k] == s[j+k]; k++);
		lcp[m[i]-1] = k;
	}
}

char s[maxn];
int n, k, sa[maxn], lcp[maxn];
ll pre[maxn];

int main(){
	scanf("%s", s);
	n = strlen(s);
	sa_build(n+1, s, sa, lcp);
	for(int i = 1; i<=n; i++) pre[i] = pre[i-1] + n - sa[i] - lcp[i-1];
	ll k;
	scanf("%lld", &k);
	int idx = lower_bound(pre, pre+n+1, k) - pre;
	k -= pre[idx-1];
	for(int i = 0; i<k + lcp[idx-1]; i++) putchar(s[sa[idx]+i]);
	puts("");
	return 0;
}

