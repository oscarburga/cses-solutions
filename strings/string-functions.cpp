#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+5;
int n, b[maxn], z[maxn];
char s[maxn];

int main(){
	scanf("%s", s);
	n = strlen(s);
	for(int i = 1, j = 0; i<n; b[i++] = j) {
		while(j > 0 && s[i] != s[j]) j = b[j-1];
		j += s[i] == s[j];
	}
	for(int i = 1, l = 0, r = -1; i<n; i++) {
		int k = i > r ? 0 : min(z[i-l], r-i+1);
		while(i+k < n && s[k] == s[i+k]) k++;
		z[i] = k--;
		if (i + k > r) l = i, r = i+k;
	}
	for(int i = 0; i<n; i++) printf("%d%c", z[i], " \n"[i+1==n]);
	for(int i = 0; i<n; i++) printf("%d%c", b[i], " \n"[i+1==n]);
	return 0;
}

