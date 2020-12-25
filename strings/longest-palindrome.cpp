#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+5;
int n, d[2][maxn];
char s[maxn];

int main(){
	scanf("%s", s);
	n = strlen(s);
	int ansl = 0, ansr = 0;
	for(int v = 0; v<2; v++) { 
		for(int i = 0, l = 0, r = -1; i < n; i++) {
			int k = i > r ? 0 : min(r-i+1, d[v][l+r-i+v]);
			while(i >= k+v && i+k < n && s[i-k-v] == s[i+k]) k++;
			d[v][i] = k--;
			if (r < i+k) r = i+k, l = i-k-v;
			if (r-l > ansr-ansl) ansr = r, ansl = l;
		}
	}
	for(int i = ansl; i<=ansr; i++) putchar(s[i]);
	puts("");
	return 0;
}

