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
#include<assert.h>
#define mod 100
#define maxN 1000005
#define INF 1000000000
typedef long long ll;
using namespace std;
ll a, b;
int phi[maxN], prime[maxN], q[maxN], fc[maxN], p, d, cnt = 0;
bool rt[maxN];
vector<ll> ans;
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
void proc(int p)
{
	for (int i = 1; prime[i]*prime[i]<= p && prime[i]; ++i) {
		if (p%prime[i] == 0) {
			fc[++cnt] = prime[i];
			while (p%prime[i] == 0) {
				p /= prime[i];
			}
		}
	}
    if(p>1) fc[++cnt]=p;
}
ll quickpow(ll a, ll b, ll p) {
	ll ans = 1;
	while (b) {
		if (b & 1) ans = (ans * a) % p;
		a = (a*a) % p; b >>= 1;
	}
	return ans;
}
bool check(int x, int p) {
	if (quickpow(x, phi[p], p) != 1) return false;
	for (int i = 1; i <= cnt; ++i) {
		if (quickpow(x, phi[p] / fc[i], p) == 1) return false;
	}
	return true;
}
int findrt(int p) 
{
	for (int i = 1; i < p; ++i) {
		if (check(i, p)) return i;
	}
	return 0;
}
int gcd(int a, int b)
{
	if (!b) return a;
	return gcd(b, a%b);
}
void getrt(int p, int x)
{
	ll pd = 1;
	for (int i = 1; i <= phi[p]; ++i) {
		pd = (pd*x) % p;
		if (gcd(i, phi[p]) == 1) {
			ans.push_back(pd);
		}
	}
}
void init()
{
	phi[1] = 1;
	int t = 0;
	for (int i = 2; i <= maxN; ++i)
	{
		if (!q[i]) {
			phi[i] = i - 1;
			prime[++t] = i;
		}
		for (int j = 1; j <= t && i*prime[j] < maxN; ++j) {
			q[i*prime[j]] = 1;
			if (!(i%prime[j])) {
				phi[i*prime[j]] = phi[i] * prime[j];
				break;
			}
			phi[i*prime[j]] = phi[i] * phi[prime[j]];
		}
	}
	rt[2] = rt[4] = 1;
	for (int i = 2; i <= t; ++i) {
		for (int j = 1; 1ll * j*prime[i] <= maxN; rt[j *= prime[i]] = 1);
		for (int j = 2; 1ll * j*prime[i] <= maxN; rt[j *= prime[i]] = 1);
	}
}
void solve()
{
	int T; T = getint();
	while (T--)
	{
		ans.clear();
		p = getint(); d = getint();
		if (!rt[p]) {
			cout << "0\n\n";
			continue;
		}
		cnt = 0;
		proc(phi[p]);
		int mr = findrt(p);
		getrt(p, mr);
		sort(ans.begin(), ans.end());
		cout << ans.size() << endl;
		int v = d;
		while (v <= ans.size())
		{
			cout << ans[v-1] << " ";
			v += d;
		}
		cout << endl;
	}
}
int main() {
	cin.tie(0);
	init();
	solve();
	system("pause");
}