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
int n,m,k[105],sz[maxN],cnt,dis[maxK],ans[105];
vector<pair<int,int>> e[maxN];
bool vis[maxN];
vector<int> op;
void dfs(int u,int p,int dep,int x) //计算答案
{
    if(dep>=maxK) return;
    dis[dep]++;op.push_back(dep);
    for(int i=1;i<=m;++i){
        if(k[i]>=dep) ans[i]+=x*dis[k[i]-dep];
    }
    for(auto it:e[u]){
        int v=it.first, w=it.second;
        if(v==p||vis[v]) continue;
        dfs(v,u,dep+w,x);
    }
}
void dfs_cal(int u,int dep,int x) // 调用递归计算并清空
{
    dfs(u,0,dep,x);
    for(auto &item:op) dis[item]--; //清空
    op.clear();
}
void dfs_root(int u,int p,int tot,int &rt) // 寻找根
{
    sz[u]=1;
    int mx=0;
    for(auto it:e[u]){
        int v=it.first;
        if(v==p||vis[v]) continue;
        dfs_root(v,u,tot,rt);
        sz[u]+=sz[v];
        mx=max(mx,sz[v]);
    }
    mx=max(mx,tot-sz[u]);
    if(mx<=tot/2) rt=u;
}
void dfs_div(int u,int tot) // 进行分割
{
    int rt;dfs_root(u,0,tot,rt); // 寻找rt
    dfs_cal(rt,0,1); vis[rt]=1; // 表示rt已被选择为根
    for(auto it:e[rt]){
        int v=it.first, w=it.second;
        if(vis[v]) continue;
        dfs_cal(v,w,-1);
        dfs_div(v,sz[v]<sz[rt]?sz[v]:tot-sz[rt]);
    }
    vis[rt]=0;
}
void init()
{
    cin>>n>>m;
    int u,v,w;
    for(int i=1;i<n;++i){
        cin>>u>>v>>w;
        e[u].push_back({v,w});
        e[v].push_back({u,w});
    }
    for(int i=1;i<=m;++i) cin>>k[i];
    dfs_div(1,n);
}
void solve()
{
    for(int i=1;i<=m;++i)
    {
        if(ans[i]) cout<<"AYE\n";
        else cout<<"NAY\n";
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
	init();
	solve();
}