#include <iostream>
#include <algorithm>
#include <iomanip>
#include <queue>
#include<string>
#include <vector>
#include <cstdio>
#include<map>
#include<cmath>
#include<cstring>
#include<set>
#define mod 1000000007
#define maxN 205
#define maxM 6005
#define INF 1000000000
typedef long long ll;
using namespace std;
struct EDGE {
	int from, to, next;
	ll w;
}edge[maxM*2];
int n, m, s, t, tot = -1, c[maxN][maxN], head[maxM * 2], pre[maxN], dis[maxN], now[maxN];
ll ans = 0;
bool has[maxN][maxN], vis[maxN];
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
void add(int u, int v, int w) 
{
	edge[++tot].from = u;
	edge[tot].to = v;
	edge[tot].w = w;
	edge[tot].next = head[u];
	head[u] = tot;
	c[u][v] = tot;
	has[u][v] = 1;
}
bool BFS()
{
	memset(vis, 0, sizeof(vis));
	queue<int> q;
	q.push(s);
	vis[s] = 1;dis[s] = 0;
	now[s] = head[s];
	while (!q.empty())
	{
		int u = q.front(); q.pop();
		for (int i = head[u]; i!=-1; i = edge[i].next)
		{
			if (!edge[i].w) continue;
			int v = edge[i].to;
			if (vis[v]) continue;
			vis[v] = 1;
			q.push(v);
			now[v] = head[v];
			dis[v] = dis[u] + 1;
			if (v == t) return 1;
		}
	}
	return 0;
}
ll dfs(int u, ll sum)
{
	if (u == t) return sum;
	ll res = 0;
	for (int i = now[u]; i != -1 && sum; i = edge[i].next)
	{
		now[u] = i;
		int v = edge[i].to;
		if (edge[i].w > 0 && dis[v] == dis[u] + 1)
		{
			ll k = dfs(v, min(sum, edge[i].w));
			if (!k) {
				dis[v] = INF;
				continue;
			}
			edge[i].w -= k;
			edge[i ^ 1].w += k;
			res += k;
			sum -= k;
		}
	}
	return res;
}
void init()
{
	n = getint(); m = getint(); s = getint(); t = getint();
	for (int i = 1; i <= n; ++i) head[i] = -1;
	int u, v, w;
	for (int i = 0; i < m; ++i) {
		u = getint(); v = getint(); w = getint();
		if (has[u][v]) {
			edge[c[u][v]].w += w;
		}
		else {
			add(u, v, w);
			add(v, u, 0);
		}
	}
}
void solve()
{
	ll ans = 0;
	while (BFS()) {
		ans += dfs(s, INF);
		//cout << "---------------------\n";
		//for (int i = 0; i <= tot; ++i)
		//{
		//	cout << edge[i].from << " " << edge[i].to << " " << edge[i].w << endl;
		//}
	}
	cout << ans << endl;
}
int main() {
	//freopen("D://ans.txt", "w+", stdout);
	//cin.tie(0);
	init();
	solve();
	system("pause");
}