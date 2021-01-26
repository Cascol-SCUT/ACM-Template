#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define maxN 10005
#define maxK 10000005
#define mod 1000000007
#define INF 0x3f3f3f3f
#define eps 1e-6
using namespace std;
int tot,head[maxN],n,m,k[105],sz[maxN],cnt,dis[maxK],ans[105];
struct EDGE{
    int from,to,w,next;
}edge[maxN*2];
bool vis[maxN];
vector<int> op;
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
inline void add(int u,int v,int w)
{
    edge[++tot].from=u;
    edge[tot].to=v;
    edge[tot].w=w;
    edge[tot].next=head[u];
    head[u]=tot;
}
void dfs(int u,int p,int dep,int x)
{
    if(dep>=maxK) return;
    dis[dep]++;op.push_back(dep);
    for(int i=1;i<=m;++i){
        if(k[i]>=dep) ans[i]+=x*dis[k[i]-dep];
    }
    int v;
    for(int i=head[u];i;i=edge[i].next){
        v=edge[i].to;
        if(v==p||vis[v]) continue;
        dfs(v,u,dep+edge[i].w,x);
    }
}
void dfs_cal(int u,int dep,int x)
{
    dfs(u,0,dep,x);
    for(auto &item:op) dis[item]--; //清空
    op.clear();
}
void dfs_root(int u,int p,int tot,int &rt)
{
    sz[u]=1;
    int v,mx=0;
    for(int i=head[u];i;i=edge[i].next){
        v=edge[i].to;
        if(v==p||vis[v]) continue;
        dfs_root(v,u,tot,rt);
        sz[u]+=sz[v];
        mx=max(mx,sz[v]);
    }
    mx=max(mx,tot-sz[u]);
    if(mx<=tot/2) rt=u;
}
void dfs_div(int u,int tot)
{
    int rt;dfs_root(u,0,tot,rt);
    dfs_cal(rt,0,1);vis[rt]=1;
    int v;
    for(int i=head[rt];i;i=edge[i].next){
        v=edge[i].to;
        if(vis[v]) continue;
        dfs_cal(v,edge[i].w,-1);
        dfs_div(v,sz[v]<sz[rt]?sz[v]:tot-sz[rt]);
    }
    vis[rt]=0;
}
void init()
{
    n=getint();m=getint();
    int u,v,w;
    for(int i=1;i<n;++i){
        u=getint();v=getint();w=getint();
        add(u,v,w);add(v,u,w);
    }
    for(int i=1;i<=m;++i) k[i]=getint();
    dfs_div(1,n);
}
void solve()
{
    for(int i=1;i<=m;++i)
    {
        if(k[i]) cout<<"AYE\n";
        else cout<<"NAY\n";
    }
}
int main()
{
	// freopen("D:\\","w+",stdout);
    cin.tie(0);
	init();
	solve();
}