#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+5;
char s[maxn];
int n, b[maxn];

int main(){
	scanf("%s", s);
	n = strlen(s);
	for(int i = 1, j = 0; i<n; i++) {
		while(j > 0 && s[i] != s[j]) j = b[j-1];
		b[i] = (j += s[i] == s[j]);
	}
	vector<int> ans;
	for(int j = b[n-1]-1; j >= 0; j = b[j]-1) ans.push_back(j+1);
	reverse(ans.begin(), ans.end());
	for(int i = 0; i<ans.size(); i++) printf("%d%c", ans[i], " \n"[i+1==ans.size()]);
	return 0;
}

