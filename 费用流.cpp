#include <iostream>
#include <algorithm>
#include <iomanip>
#include <queue>
#include<string>
#include<complex>
#include<string.h>
#include <vector>
#include <cstdio>
#include<map>
#include<random>
#include<cmath>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define maxM 100025
#define maxN 10015
#define maxK 35
#define mod 1000000007
#define INF 0x3f3f3f3f
#define eps 1e-6
using namespace std;
struct EGDE{
	int from,to,next,cost,f;
}edge[maxM];
int tot=-1,head[maxN],n,m,s,t,pre[maxN],flow[maxN],dis[maxN];
queue<int> q;
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
void add(int u,int v,int cost,int f)
{
	edge[++tot].from=u;
	edge[tot].to=v;
	edge[tot].next=head[u];
	edge[tot].cost=cost;
	edge[tot].f=f;
	head[u]=tot;
}
bool spfa(int s,int t)
{
	memset(dis,INF,sizeof(dis));
	memset(vis,0,sizeof(vis));
	memset(flow,0,sizeof(flow));
	dis[s]=0;q.push(s);
	pre[s]=-1;
	flow[s]=INF;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		vis[u]=false;
		for(int i=head[u];i!=-1;i=edge[i].next)
		{
			if(edge[i].f<=0) continue;
			int v=edge[i].to,cost=edge[i].cost;
			if(dis[v]>dis[u]+cost)
			{
				dis[v]=dis[u]+cost;
				pre[v]=i;
				flow[v]=min(flow[u],edge[i].f);
				if(vis[v]) continue;
				q.push(v); vis[v]=true;
			}
		}
	}
	return dis[t]!=INF;
}
void pr()
{
	cout<<"-------------------------\n";
	for(int i=0;i<tot;++i)
	{
		cout<<edge[i].from<<" "<<edge[i].to<<" "<<edge[i].f<<endl;
	}
}
void init()
{
	n=getint();m=getint();s=getint();t=getint();
	memset(head,-1,sizeof(head));
	int u,v,cost,f;
	for(int i=1;i<=m;++i){
		u=getint();v=getint();f=getint();cost=getint();
		add(u,v,cost,f);
		add(v,u,-cost,0);
	}
}
void solve()
{
	ll ans=0,ans2=0;
	while(spfa(s,t))
	{
		// while(x!=s){
		// 	int i=pre[x];
		// 	edge[i].f-=flow[t];
		// 	edge[i^1].f+=flow[t];
		// 	x=edge[i^1].to;
		// }
		for(int i=pre[t];i!=-1;i=pre[edge[i].from])
		{
			edge[i].f-=flow[t];
			edge[i^1].f+=flow[t];
		}
		ans+=flow[t];
		ans2+=flow[t]*dis[t];
		// pr();
	}
	cout<<ans<<" "<<ans2<<endl;
}
int main()
{
	// freopen("D:\\","w+",stdout);
	cin.tie(0);
	init();
	solve();
}