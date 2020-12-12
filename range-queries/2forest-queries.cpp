#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e3+5;
bool mat[maxn][maxn];
int n, m, ft[maxn][maxn];

void upd(int x, int y, int v) {
	while (x <= n) {
		int pos = y;
		while(pos <= n) ft[x][pos] += v, pos += pos & (-pos);
		x += x & (-x);
	}
}

int query(int x, int y) {
	int ret = 0;
	while (x > 0) {
		int pos = y;
		while(pos > 0) ret += ft[x][pos], pos &= pos-1;
		x &= x-1;
	}
	return ret;
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i<=n; i++) {
		for(int j = 1; j<=n; j++) {
			char c;
			scanf(" %c", &c);
			mat[i][j] = c == '*';
			upd(i, j, mat[i][j]);
		}
	}
	while (m--) {
		int t;
		scanf("%d", &t);
		if (t == 1) {
			int x, y;
			scanf("%d %d", &x, &y);
			if (mat[x][y]) upd(x, y, -1);
			else upd(x, y, 1);
			mat[x][y] ^= 1;
		} else {
			int x1, y1, x2, y2;
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			printf("%d\n", query(x2, y2) - query(x1-1, y2) - query(x2, y1-1) + query(x1-1, y1-1));
		}
	}

	return 0;
}

