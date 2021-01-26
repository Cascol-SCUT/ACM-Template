#include <iostream>
#include <algorithm>
#include <iomanip>
#include <queue>
#include<string>
#include <vector>
#include <cstdio>
#include<map>
#include<cmath>
#include<set>
#define mod 1000000007
#define maxN 405
#define INF 1000000000
typedef long long ll;
using namespace std;
int n;
ll mt[maxN][2 * maxN];
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
ll qp(ll a, ll p)
{
	ll res = 1;
	while (p)
	{
		if (p & 1) res = (res*a) % mod;
		p >>= 1;
		a = (a*a) % mod;
	}
	return res;
}
void init()
{
	n = getint();
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j)
			mt[i][j] = getint();
		mt[i][n + i] = 1;
	}
	for (int i = 1; i <= n; ++i)
	{
		int pos = i;
		for (int j = i + 1; j <= n; ++j) if (mt[j][i] > mt[pos][i]) pos = j;
		if (pos != i) swap(mt[i], mt[pos]);
		if (!mt[i][i]) {
			cout << "No Solution";
			return;
		}
		//ll rev = reverse(mt[i][i]);
		int m = 2 * n;
		ll rev = qp(mt[i][i], mod - 2);
		for (int j = i; j <= m; ++j) {
			mt[i][j] = (mt[i][j] * rev) % mod;
		}
		for (int r = 1; r <= n; ++r)
		{
			if (r != i)
			{
				ll t = mt[r][i];
				for (int k = i; k <= m; ++k) {
					mt[r][k] -= (t * mt[i][k]) % mod;
					mt[r][k] = (mt[r][k] % mod + mod) % mod;
				}
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = n + 1; j <= 2 * n; ++j) {
			printf("%lld ", mt[i][j]);
		}
		puts("");
	}
}
void solve()
{

}
int main() {
	cin.tie(0);
	init();
	solve();
	//system("pause");
}