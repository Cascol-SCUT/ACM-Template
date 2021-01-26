#include <iostream>
#include <algorithm>
#include <iomanip>
#include <queue>
#include<string>
#include<string.h>
#include <vector>
#include <cstdio>
#include<map>
#include<cmath>
#include<set>
#define mod 100
#define maxN 5000015
#define INF 1000000000
typedef long long ll;
using namespace std;
int n, m,deg[maxN];
int a[maxN], ans[maxN];
int father[maxN];
inline int getint() {
	int num = 0, bj = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == EOF)
			return EOF;
		bj = (c == '-' || bj == -1) ? -1 : 1, c = getchar();
	}
	while (c >= '0' && c <= '9') num = num * 10 + c - '0', c = getchar();
	return num * bj;
}
void init()
{
	n = getint(); m = getint();
}
void solve()
{
	if (m == 1) {
		int x;
		for (int i = 1; i < n; ++i) {
			x = getint();
			father[i] = x;
			deg[x]++;
		}
		int ptr = 1, leaf;
		while (deg[ptr] != 0) ++ptr;
		leaf = ptr;
		for (int i = 1; i < n - 1; ++i) {
			int nxt = father[leaf];
			ans[i] = nxt;
			if (--deg[nxt] == 0 && nxt < ptr) {
				leaf = nxt;
			}
			else {
				++ptr;
				while (deg[ptr] != 0)++ptr;
				leaf = ptr;
			}
		}
		ll res = 0;
		for (int i = 1; i < n-1; ++i) {
			//cout << ans[i] << " ";
			res ^= (ll)i*ans[i];
		}
		cout << res << endl;
	}
	else if (m == 2) {
		for (int i = 1; i < n - 1; ++i) {
			a[i] = getint();
			deg[a[i]]++;
		}
		int ptr = 1, leaf, nxt;
		while (deg[ptr]) ++ptr;
		leaf = ptr;
		for (int i = 1; i < n - 1; ++i)
		{
			ans[leaf] = a[i];
			--deg[a[i]];
			if (!deg[a[i]] && a[i] < ptr) {
				leaf = a[i];
			}
			else {
				++ptr;
				while (deg[ptr])++ptr;
				leaf = ptr;
			}
		}
		ans[leaf] = n;
		ll res = 0;
		for (int i = 1; i < n; ++i) {
			res ^= (ll)i * ans[i];
			//cout << ans[i] << " ";
		}
		cout << res << endl;
	}
}
int main() {
	//cin.tie(0);
	init();
	solve();
	//system("pause");
}