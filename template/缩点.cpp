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
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const ll mod = 1000000007;
const int maxN = 1e4 + 15;
struct EDGE {
	int from, to, next;
}edge[maxN*10], ed[maxN*10];
vector<int> p, st;
int n, m, tot = 0, head[maxN],h[maxN];
int dfn[maxN], low[maxN],sd[maxN];
int in[maxN],dist[maxN], cur = 0;
bool vis[maxN];
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
	edge[++tot].next = head[u];
	edge[tot].from = u;
	edge[tot].to = v;
	head[u] = tot;
}
void init()
{
	n = getint(); m = getint();
	p.push_back(-1);
	for (int i = 0; i < n; ++i) p.push_back(getint());
	int u, v;
	for (int i = 0; i < m; ++i) {
		u = getint(); v = getint();
		add(u, v);
	}
}
void tarjian(int u)
{
	++cur; dfn[u] = low[u] = cur; vis[u] = 1;
	st.push_back(u);
	for (int i = head[u]; i; i = edge[i].next)
	{
		int v = edge[i].to;
		if (!dfn[v])
		{
			tarjian(v);
			low[u] = min(low[u], low[v]);
		}
		else if (vis[v]){
			low[u] = min(low[u], dfn[v]);
		}
	}
	if (low[u] == dfn[u])
	{
		int y;
		while (true) {
			y = st.back(); st.pop_back();
			sd[y] = u;
			vis[y] = 0;
			if (u == y) break;
			p[u] += p[y];
		}
	}
}
ll topo()
{
	queue<int> q;
	for(int i=1;i<=n;++i)
		if (sd[i] == i && !in[i])
		{
			q.push(i);
			dist[i] = p[i];
		}
	while (!q.empty())
	{
		int u = q.front(); q.pop();
		for (int i = h[u]; i; i = ed[i].next)
		{
			int v = ed[i].to;
			dist[v] = max(dist[v], dist[u] + p[v]);
			in[v]--;
			if (!in[v]) q.push(v);
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i)
		ans = max(ans, dist[i]);
	return ans;
}
void solve()
{
	for (int i = 1; i <= n; ++i)
		if (!dfn[i]) tarjian(i);
	// cout << p[1] << " " << p[2] << endl;
	tot = 0;
	for (int i = 1; i <= m; ++i)
	{
		int u = sd[edge[i].from], v = sd[edge[i].to];
		if (u != v)
		{
			ed[++tot].from = u;
			ed[tot].to = v;
			ed[tot].next = h[u];
			h[u] = tot;
			in[v]++;
		}
	}
	cout << topo() << endl;
}
int main()
{
	//freopen("reflection.in","r", stdin);
	init();
	solve();
	//system("pause");
}