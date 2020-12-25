#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//This problems needs Booth's algorithm to fit in the TL (linear suffix array probably passes too).
//Hopefully someday I'll find the time to learn either of those algorithms.
//My O(NlogN) suffix array passes all cases except #6 and #7 :(

const int maxn = 1e6+5;
int n, a[maxn], m[maxn], nm[maxn], sbs[maxn], head[maxn];
char s[maxn];
 
int main(){
	scanf("%s", s);
	n = strlen(s);
	iota(a, a+n, 0);
	sort(a, a+n, [&](int i, int j) { return s[i] < s[j]; });
	m[a[0]] = 0;
	for(int i = 1; i<n; i++) m[a[i]] = m[a[i-1]] + (s[a[i]] != s[a[i-1]]);
	for(int len = 1; len<n; len <<= 1) {
		for(int i = 0; i<n; i++) sbs[i] = (a[i]-len+n) % n;
		for(int i = n-1; i>=0; i--) head[m[a[i]]] = i;
		for(int i = 0; i<n; i++) a[head[m[sbs[i]]]++] = sbs[i];
		nm[a[0]] = 0;
		for(int i = 1; i<n; i++) {
			if (m[a[i-1]] != m[a[i]]) nm[a[i]] = nm[a[i-1]] + 1;
			else nm[a[i]] = nm[a[i-1]] + (m[(a[i-1]+len)%n] != m[(a[i]+len)%n]);
		}
		swap(m, nm);
	}
	for(int i = 0; i<n; i++) putchar(s[(i+a[0])%n]);
	puts("");
	return 0;
}
