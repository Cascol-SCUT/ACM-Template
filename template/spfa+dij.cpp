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
#define maxN 10015
#define INF 1000000000

typedef long long ll;
using namespace std;
int n, m, tot = 0, head[maxN], h[maxN] , cnt[maxN], vis[maxN];
ll dist[maxN];
struct EDGE {
	int from, to, next;
	ll weight;
}edge[maxN];
struct node {
	int u;
	ll dis;
	bool operator <(const node &a)const {
		return dis > a.dis;
	}
	node(int u, ll dis) {
		this->u = u;
		this->dis = dis;
	}
};
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
	edge[tot].weight = w;
	edge[tot].next = head[u];
	head[u] = tot;
}
bool SPFA(int st)
{
	queue<int> q;
	q.push(st);
	memset(h, 63, sizeof(h));
	//for (int i = 0; i <= n; ++i)h[i] = INF;
	h[st] = 0;
	while (!q.empty())
	{
		int u = q.front(); q.pop();
		vis[u] = false;
		for (int i = head[u]; i; i = edge[i].next)
		{
			int v = edge[i].to;
			if (h[v] > h[u] + edge[i].weight)
			{
				h[v] = h[u] + edge[i].weight;
				if (!vis[v])
				{
					q.push(v);
					vis[v] = true;
					cnt[v]++;
					if (cnt[v] == n+1) return false;
				}
			}
		}
	}
	return true;
}
void dij(int st) {
	memset(vis, 0, sizeof(vis));
	priority_queue<node> q;
	for (int i = 1; i <= n; ++i) dist[i] = INF;
	dist[st] = 0;
	q.push(node(st, 0));
	while (!q.empty())
	{
		int u = q.top().u; q.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (int i = head[u]; i; i = edge[i].next)
		{
			int v = edge[i].to, w = edge[i].weight;
			if (dist[v] > dist[u] + w && dist[u] != INF) {
				dist[v] = dist[u] + w;
				if (!vis[v])q.push(node(v, dist[v]));
			}
		}
	}
}
void init()
{
	n = getint(); m = getint();
	int u, v, w;
	for (int i = 0; i < m; ++i) {
		u = getint(); v = getint(); w = getint();
		add(u, v, w);
	}
	for (int i = 1; i <= n; ++i) add(0, i, 0);
}
void solve()
{
	bool flag = SPFA(0);
	if (!flag) {
		cout << "-1\n";
		return;
	}
	else {
		for (int i = 1; i <= m; ++i) {
			edge[i].weight += h[edge[i].from] - h[edge[i].to];
		}
		for (int i = 1; i <= n; ++i) {
			dij(i);
			ll ans = 0;
			for (int j = 1; j <= n; ++j) {
				if (dist[j] == INF) ans += (ll)j * INF;
				else ans +=  (ll)j * (dist[j] + h[j] - h[i]);
			}
			cout << ans << endl;
		}
	}
}
signed main() {
	init();
	solve();
	system("pause");
}