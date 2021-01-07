#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;

int m[maxn], nm[maxn], head[maxn], sbs[maxn];
void suffix_array(const int n, char s[maxn], int a[maxn], int lcp[maxn]) {
	iota(a, a+n, 0);
	sort(a, a+n, [&](int i, int j) { return s[i] < s[j]; });
	m[a[0]] = 0;
	for(int i = 1; i<n; i++) m[a[i]] = m[a[i-1]] + (s[a[i]] != s[a[i-1]]);
	for(int len = 1; len<n; len <<= 1) {
		for(int i = 0; i<n; i++) sbs[i] = (a[i] - len + n) % n;
		for(int i = n-1; i>=0; i--) head[m[a[i]]] = i;
		for(int i = 0; i<n; i++) a[head[m[sbs[i]]]++] = sbs[i];
		nm[a[0]] = 0;
		for(int i = 1; i<n; i++) {
			if (m[a[i]] != m[a[i-1]]) nm[a[i]] = nm[a[i-1]] + 1;
			else nm[a[i]] = nm[a[i-1]] + (m[(a[i]+len)%n] != m[(a[i-1]+len)%n]);
		}
		swap(m, nm);
	}
	for(int i = 0, k = 0; i+1<n; i++, k -= k > 0) {
		int j = a[m[i]-1];
		while(s[i+k] == s[j+k]) k++;
		lcp[m[i]-1] = k;
	}
}

char s[maxn];
int n, sa[maxn], lcp[maxn];

int main(){
	scanf("%s", s);
	n = strlen(s);
	suffix_array(n+1, s, sa, lcp);
	//for(int i = 1; i<=n; i++) printf("%s\n", s+sa[i]);
	//for(int i = 1; i<n; i++) printf("%d%c", lcp[i], " \n"[i+1==n]);
	int idx = max_element(lcp+1, lcp+n) - lcp;
	if (lcp[idx] == 0) { puts("-1"); return 0; }
	for(int i = sa[idx], e = sa[idx] + lcp[idx]; i < e; i++) putchar(s[i]);
	puts("");
	return 0;
}

