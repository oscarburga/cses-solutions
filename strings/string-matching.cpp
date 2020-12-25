#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e6+5;
char s[maxn], t[maxn];
int n, m, b[maxn];

int main(){
	scanf("%s", t);
	scanf("%s", s);
	m = strlen(t);
	n = strlen(s);
	int sz = n+m+1;
	s[n+1] = '#';
	memcpy(s+n+1, t, m);
	int ans = 0;
	for(int i = 1, j = 0; i<sz; i++) {
		while(j > 0 && s[i] != s[j]) j = b[j-1];
		b[i] = (j += s[i] == s[j]);
		ans += b[i] == n;
	}
	printf("%d\n", ans);
	return 0;
}

