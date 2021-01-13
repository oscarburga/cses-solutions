#include <bits/stdc++.h>
using namespace std;
using ll = long long;

namespace KMP {
	template<typename V, typename S>
	void kmp(const int n, V& b, const S& s) {
		b[0] = 0;
		for(int i = 1, j = 0; i<n; b[i++] = j) {
			while(j > 0 && s[i] != s[j]) j = b[j-1];
			j += s[i] == s[j];
		}
	}
	template<typename M, typename V, typename S> 
	void kmp_automaton(const int n, M& go, const V& b, const S& s, const char lo='a', const char hi='z') {
		go[0][s[0]-lo] = 1;
		for(int i = 1; i<n; i++) {
			for(char c = lo; c<=hi; c++) {
				go[i][c-lo] = s[i] == c ? i+1 : go[b[i-1]][c-lo];
			}
		}
	}
};

namespace ZF {
	template<typename V, typename S>
	void zfunction(const int n, V& z, const S& s) {
		z[0] = 0;
		for(int i = 1, l = 0, r = -1; i<n; i++) {
			int k = i > r ? 0 : min(z[i-l], r-i+1);
			while(i+k < n && s[k] == s[i+k]) k++;
			z[i] = k--;
			if (i + k > r) l = i, r = i+k;
		}
	}

}

const int maxn = 1e6+5;
int n, b[maxn], z[maxn];
char s[maxn];

int main(){
	scanf("%s", s);
	n = strlen(s);
	KMP::kmp(n, b, s);
	ZF::zfunction(n, z, s);
	for(int i = 0; i<n; i++) printf("%d%c", z[i], " \n"[i+1==n]);
	for(int i = 0; i<n; i++) printf("%d%c", b[i], " \n"[i+1==n]);
	return 0;
}

