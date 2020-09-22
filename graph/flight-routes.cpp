#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5, maxk = 10;
int n, m, k, cnt[maxn];
vector<pair<int,int>> vs[maxn];
priority_queue<ll> d[maxn];
priority_queue<pair<ll, int>> q;

int main(){
	scanf("%d %d %d", &n, &m, &k);
	for(int i = 0; i<m; i++){
		int x, y, w;
		scanf("%d %d %d", &x, &y, &w);
		vs[--x].push_back({--y, w});
	}
	q.push({0, 0});
	while(q.size()){
		int v = q.top().second;
		ll c = -q.top().first;
		q.pop();
		if (cnt[v] >= k) continue;
		cnt[v]++;
		for(pair<int,int>&e: vs[v]) if (d[e.first].size() < k or c + e.second < d[e.first].top()) {
			if (d[e.first].size() >= k) d[e.first].pop();
			ll aux = c + e.second;
			d[e.first].push(aux);
			q.push({ -aux, e.first });
		}
	}
	vector<ll> ts(k);
	for(int i = k-1; i>=0; i--) ts[i] = d[n-1].top(), d[n-1].pop();
	for(int i = 0; i<k; i++) printf("%lld%c", ts[i], " \n"[i+1==k]);
	return 0;
}

