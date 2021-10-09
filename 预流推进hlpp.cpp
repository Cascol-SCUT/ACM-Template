#include<bits/stdc++.h>
#define maxN 10005
#define maxM 200005
#define INF 0x3f3f3f3f
typedef int ll; //注意这里-------------------
typedef long double ld;
using namespace std;
struct EDGE{
    int from,to,next;
    ll w;
};
int ht[maxN],ex[maxN],gap[maxN]; //高度; 超额流; gap
struct HLPP{
    int n,m,s,t,head[maxN],tot=1;
    EDGE edge[maxM*2];
    void add_path(int u,int v,ll w) {
        edge[++tot]={u,v,head[u],w};;
        head[u]=tot;
    }
    void add_flow(int u,int v,ll w){
        add_path(u,v,w);
        add_path(v,u,0);
    }
    bool bfs_init(){
        memset(ht,INF,sizeof(ht));
        ht[t]=0;
        queue<int> q;q.push(t);
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int i=head[u];i;i=edge[i].next){
                int v=edge[i].to;
                if(edge[i^1].w&&ht[v]>ht[u]+1){
                    ht[v]=ht[u]+1;
                    q.push(v);
                }
            }
        }
        return ht[s]!=INF;
    }
    bool vis[maxN];
    struct cmp{
        bool operator ()(int a,int b){
            return ht[a]<ht[b];
        }
    };
    priority_queue<int,vector<int>,cmp> pq;
    int push(int u){
        for(int i=head[u];i;i=edge[i].next){
            int v=edge[i].to;ll w=edge[i].w;
            if(!w||ht[u]!=ht[v]+1) continue;
            ll k=min(w,ex[u]);
            ex[u]-=k;ex[v]+=k;edge[i].w-=k;edge[i^1].w+=k;
            if(v!=s&&v!=t&&!vis[v]) {
                pq.push(v);vis[v]=true;
            }
            if(!ex[u]) return 0;
        }
        return 1;
    }
    void relabel(int u){
        ht[u]=INF;
        for(int i=head[u];i;i=edge[i].next){
            if(edge[i].w) ht[u]=min(ht[u],ht[edge[i].to]);
        }
        ++ht[u];
    }
    int hlpp()
    {
        if(!bfs_init()) return 0;
        ht[s]=n;
        memset(gap,0,sizeof(gap));
        for(int i=1;i<=n;++i){
            if(ht[i]!=INF) gap[ht[i]]++;
        }
        for(int i=head[s];i;i=edge[i].next){
            int v=edge[i].to;ll w=edge[i].w;
            if(!w) continue;
            ex[s]-=w;ex[v]+=w;edge[i].w-=w;edge[i^1].w+=w;
            if(v!=s&&v!=t&&!vis[v]) pq.push(v),vis[v]=true;
        }
        while(!pq.empty())
        {
            int u=pq.top();pq.pop();
            vis[u]=0;
            while(push(u)){
                --gap[ht[u]];
                if(!gap[ht[u]]){
                    for(int i=1;i<=n;++i){
                        if(i!=s&&i!=t&&ht[i]>ht[u]&&ht[i]<n+1) ht[i]=n+1; //把高于u的点都删掉
                    }
                }
                relabel(u);
                gap[ht[u]]++;
            }
        }
        return ex[t];
    }
}hp;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>hp.n>>hp.m>>hp.s>>hp.t;
    for(int i=1;i<=hp.m;++i){
        int u,v,w;cin>>u>>v>>w;
        hp.add_flow(u,v,w);
    }
    cout<<hp.hlpp()<<"\n";
}