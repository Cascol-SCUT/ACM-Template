#include <iostream>
#include <algorithm>
#include <iomanip>
#include <queue>
#include<string>
#include<string.h>
#include <vector>
#include <cstdio>
#include <cstring>
#include<map>
#include<cmath>
#include<assert.h>
#define mod 100
#define maxN 50005
#define INF 1000000000
typedef long long ll;
using namespace std;
int head[505], n, m, e, tot = 0;
int matched[505],mp[505][505];
bool ask[505];
struct EDGE {
	int from, to, next;
}edge[maxN];
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
void add(int u, int v)
{
	edge[++tot].from = u;
	edge[tot].to = v;
	edge[tot].next = head[u];
	head[u] = tot;
}
void init()
{
	n = getint(); m = getint(); e = getint();
	int u, v;
	for (int i = 0; i < e; ++i) {
		u = getint(); v = getint();
		if (!mp[u][v]) {
			add(u, v);
			mp[u][v] = 1;
		}
	}
}
bool find(int u)
{
	for (int i = head[u]; i; i = edge[i].next)
	{
		int v = edge[i].to;
		if (!ask[v])
		{
			ask[v] = true;
			if (!matched[v] || find(matched[v])) {
				matched[v] = u;
				// ask[v] = false;
				return true;
			}
			//ask[v] = false;
		}
	}
	return false;
}
void solve()
{
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		memset(ask, 0, sizeof(ask));
		ans += find(i);
	}
	cout << ans << endl;
}
int main() {
	init();
	solve();
	system("pause");
}