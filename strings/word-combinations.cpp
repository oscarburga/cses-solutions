#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5e5+5, maxs = 1e6+5, mod = 1e9+7;
bool term[maxs];
int n, k, nodes = 1, go[maxs][26], dp[maxn];
char s[maxs], t[maxs];

inline int add(int x, int y) { return (x+y) % mod; }
inline void chadd(int &x, int y) { x = add(x, y); }

void insert() {
	int pos = 0;
	for(int i = 0; t[i]; i++) {
		char nxt = t[i] - 'a';
		if (!go[pos][nxt]) go[pos][nxt] = nodes++;
		pos = go[pos][nxt];
	}
	term[pos] = true;
}

int main(){
	scanf("%s", s);
	scanf("%d", &k);
	n = strlen(s);
	for(int i = 0; i<k; i++) {
		scanf("%s", t);
		insert();
	}
	dp[n] = 1;
	for(int i = n-1; i>=0; i--) {
		int pos = 0; 
		for(int j = i; j<n && go[pos][s[j]-'a'] > 0; j++) {
			pos = go[pos][s[j]-'a'];
			chadd(dp[i], dp[j+1] * term[pos]);
		}
	}
	printf("%d\n", dp[0]);
	return 0;
}

