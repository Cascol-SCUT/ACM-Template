#include<bits/stdc++.h>
#define maxN 105
#define maxM 505
#define maxK 10
#define INF 0x3f3f3f3f
typedef long long ll;
using namespace std;
struct EDGE{
    int from,to,w,next;
}edge[maxM*2];
int tot,head[maxN];
int dp[maxN][(1<<maxK)-1];
int n,m,k;
void add(int u,int v,int w)
{
    edge[++tot]={u,v,w,head[u]};
    head[u]=tot;
}
int p[maxK+5];
bool vis[maxN];
struct node{
    int w,id;
    bool operator <(const node x) const{
        return w>x.w;
    }  
};
priority_queue<node> q;
void dij(int s)
{
    memset(vis,0,sizeof(vis));
    while(!q.empty())
    {
        node cur=q.top();q.pop();
        if(vis[cur.id]) continue;
        vis[cur.id]=1;
        for(int i=head[cur.id];i;i=edge[i].next){
            if(dp[edge[i].to][s]>cur.w+edge[i].w){
                dp[edge[i].to][s]=cur.w+edge[i].w;
                q.push({dp[edge[i].to][s],edge[i].to});
            }
        }
    }
}
void stn()
{
    memset(dp,INF,sizeof(dp));
    for(int i=0;i<k;++i){
        cin>>p[i];
        dp[p[i]][1<<i]=0;
    }
    for(int s=1;s<(1<<k);++s){
        for(int i=1;i<=n;++i){
            for(int sub=s&(s-1);sub>0;sub=s&(sub-1)){
                dp[i][s]=min(dp[i][s],dp[i][sub]+dp[i][s^sub]);
            }
            if(dp[i][s]!=INF) q.push({dp[i][s],i});
        }
        dij(s);
    }
    cout<<dp[p[0]][(1<<k)-1]<<"\n";
}
int main()
{
    // freopen("P6192_1.in","r+",stdin);
    cin>>n>>m>>k;
    for(int i=0;i<m;++i){
        int u,v,w;cin>>u>>v>>w;
        add(u,v,w);add(v,u,w);
    }
    stn();
}