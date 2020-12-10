#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//Tried some stuff with SCCs, too annoying to implement properly. Just use Binary Lifting.

const int stK = 31, maxn = 2e5+5;
int n, q, st[maxn][stK];

int main(){
	scanf("%d %d", &n, &q);
	for(int i = 1; i<=n; i++) scanf("%d", &st[i][0]);
	for(int k = 1; k<stK; k++){
		for(int i = 1; i<=n; i++){
			st[i][k] = st[st[i][k-1]][k-1];
		}
	}
	while(q--){
		int v, k;
		scanf("%d %d", &v, &k);
		for(int i = stK-1; i >= 0; i--){
			if ((k>>i)&1) v = st[v][i], k -= (1<<i);
		}
		printf("%d\n", v);
	}
	return 0;
}

