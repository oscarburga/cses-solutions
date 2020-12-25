#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e3+5, maxm = 105, alf = 26, mod = 1e9+7;
bool vis[maxn][maxm][2];
char s[maxm];
int n, m, b[maxn], go[maxn][alf], dp[maxn][maxm][2];

int add(int x, int y) { return (x+y) % mod; }
void chadd(int &x, int y) { x = add(x, y); }

int solve(int i, int j, bool ok) {
	ok |= j == m;
	if (i == n) return ok;
	int &ret = dp[i][j][ok];
	if (vis[i][j][ok]) return ret;
	vis[i][j][ok] = true;
	for(char c = 'A'; c <= 'Z'; c++) chadd(ret, solve(i+1, go[j][c-'A'], ok));
	return ret;
}

int main(){
	scanf("%d", &n);
	scanf("%s", s);
	m = strlen(s);
	s[m] = '#';
	for(int i = 1, j = 0; i<=m; i++) {
		while(j > 0 && s[i] != s[j]) j = b[j-1];
		b[i] = (j += (s[i] == s[j]));
	}
	go[0][s[0]-'A'] = 1;
	for(int i = 1; i<=m; i++) {
		for(char c = 'A'; c<='Z'; c++) {
			int j = c - 'A';
			go[i][j] = s[i] == c ? i+1 : go[b[i-1]][j];
		}
	}
	printf("%d\n", solve(0, 0, 0));
	return 0;
}

