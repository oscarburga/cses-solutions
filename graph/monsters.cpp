#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e3+5;
const int dx[] = { 1, -1, 0, 0 }, dy[] = { 0, 0, 1, -1 };
string dd = "DURL";
int n, m, d[2][maxn][maxn], p[maxn][maxn];
char mat[maxn][maxn]; 
queue<pair<int,int>> q;

int main(){
	scanf("%d %d\n", &n, &m);
	memset(d, -1, sizeof(d));
	memset(p, -1, sizeof(p));
	pair<int,int> start;
	for(int i = 0; i<n; i++) {
		for(int j = 0; j<m; j++) {
			mat[i][j] = getchar();
			if (mat[i][j] == 'A') start = { i, j };
			if (mat[i][j] == 'M') d[0][i][j] = 0, q.push({i, j});
		}
		getchar();
	}
	function<bool(int, int, int, bool)> valid = [&](int r, int c, int i, bool pl) {
		int x = r + dx[i], y = c + dy[i];
		bool t1 = x >= 0 && x < n && y >= 0 && y < m && mat[x][y] != '#';
		if (!pl) return t1 && d[pl][x][y] == -1;
		return t1 && d[pl][x][y] == -1 && (d[pl][r][c] + 1 < d[!pl][x][y] || d[!pl][x][y] == -1);
	};
	while(q.size()){
		int r = q.front().first, c = q.front().second;
		q.pop();
		for(int i = 0; i<4; i++) if (valid(r, c, i, 0)) {
			int nr = r+dx[i], nc = c+dy[i];
			d[0][nr][nc] = d[0][r][c] + 1;
			q.push({nr, nc});
		}
	}
	function<void(int, int)> reconstruct = [&](int r, int c) {
		string ans = "";
		while (p[r][c] != -1) {
			int i = p[r][c];
			ans.push_back(dd[i]);
			r -= dx[i], c -= dy[i];
		}
		reverse(ans.begin(), ans.end());
		puts("YES");
		printf("%zu\n", ans.size());
		printf("%s\n", ans.c_str());
	};
	d[1][start.first][start.second] = 0;
	q.push(start);
	while(q.size()){
		int r = q.front().first, c = q.front().second;
		q.pop();
		if (r == 0 || r == n-1 || c == 0 || c == m-1) { reconstruct(r, c); return 0; }
		for(int i = 0; i<4; i++) if (valid(r, c, i, 1)) {
			int nr = r+dx[i], nc = c+dy[i];
			d[1][nr][nc] = d[1][r][c] + 1;
			p[nr][nc] = i;
			q.push({nr, nc});
		}
	}
	puts("NO");
	return 0;
}

