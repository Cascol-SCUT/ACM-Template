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
int n;
ll p[65];
inline ll getint() {
	ll num = 0, bj = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == EOF)
			return EOF;
		bj = (c == '-' || bj == -1) ? -1 : 1, c = getchar();
	}
	while (c >= '0' && c <= '9') num = num * 10 + c - '0', c = getchar();
	return num * bj;
}
void proc(ll x)
{
	for (ll i = 60; i >= 0; --i)
	{
		if (x&(1ll<<i))
		{
			if (!p[i])
			{
				p[i] = x;
				break;
			}
			x ^= p[i];
		}
	}
}
void init()
{
	n = getint();
	ll x;
	for (int i = 0; i < n; ++i) {
		x = getint();
		proc(x);
	}
}
void solve()
{
	ll ans = 0;
	for (int i = 60; i >= 0; --i) {
		ans = max(ans, ans^p[i]);
	}
	cout << ans << endl;
}
int main() {
	//cin.tie(0);
	init();
	solve();
	//system("pause");
}