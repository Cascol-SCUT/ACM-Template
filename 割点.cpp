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
#define maxN 1000010
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
int dfn[maxN], low[maxN], cnt = 0, t = 0, head[maxN],cut[maxN],ans[maxN], root, n, m;
bool vis[maxN];
vector<int> fa;
struct EDGE {
	int from, to, next;
}edge[maxN];
int res=0;
inline int getint() {
	int num = 0, bj = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == EOF)
			return EOF;
		bj = (c == '-' || bj == -1) ? -1 : 1; c = getchar();
	}
	while (c >= '0' && c <= '9') num = num * 10 + c - '0', c = getchar();
	return num * bj;
}
void add(int u, int v) {
	edge[++t].from = u;
	edge[t].to = v;
	edge[t].next = head[u];
	head[u] = t;
}
void tarjan(int u)
{
	dfn[u] = low[u] = ++cnt;
	int tot = 0;
	for (int i = head[u]; i; i = edge[i].next)
	{
		int v = edge[i].to;
		if (!dfn[v])
		{
			tot++;
			tarjan(v);
			low[u] = min(low[u], low[v]);
			if (u != root && dfn[u] <= low[v]){
                cut[u] = true;
                ans[u]+=1;
            }
		}
		else low[u] = min(low[u], dfn[v]);
	}
    if(u==root && tot>1){
        ans[u]=tot-1;
        cut[u]=true;
    }
    else if(u==root && tot==0){
        ans[u]=-1;
    }
}
void init()
{
	n = getint(); m = getint();
	int u, v;
	for (int i = 0; i < m; ++i) {
		u = getint(); v = getint();
		add(u, v);
		add(v, u);
	}
}

void solve()
{
    
}
int main()
{
	//freopen("reflection.in","r", stdin);
	init();
	solve();
}