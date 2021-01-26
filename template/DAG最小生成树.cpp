#include<bits/stdc++.h>
#define maxN 105
#define maxM 10005
#define INF 1e9
typedef long long ll;
using namespace std;
int n,m,r,tot;
struct EDGE{
    int from,to,w,next;
}edge[maxM];
int head[maxN];
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
void init()
{
    n=getint();m=getint();r=getint();
    int u,v,w;
    for(int i=0;i<m;++i){
        u=getint();v=getint();w=getint();
        if(u==v) continue;
        add(u,v,w);
    }
}
int ine[maxN],pre[maxN],id[maxN],vis[maxN];
int solve()
{
    ll ans=0;
    while(true)
    {
        for(int i=0;i<=n;++i) ine[i]=INF;
        for(int i=1;i<=m;++i){
            int u=edge[i].from,v=edge[i].to;
            if(u!=v&&ine[v]>edge[i].w){
                ine[v]=edge[i].w;pre[v]=u;
            }
        } 
        for(int i=1;i<=n;++i){
            if(i!=r&&ine[i]==INF) return -1;
        }
        int cnt=0;
        for(int i=0;i<=n;++i) vis[i]=id[i]=0;
        for(int i=1;i<=n;++i)
        {
            if(i==r) continue;
            ans+=ine[i];
            int v=i;
            while(vis[v]!=i&&!id[v]&&v!=r)
            {
                vis[v]=i;
                v=pre[v];
            }
            if(!id[v]&&v!=r)
            {
                id[v]=++cnt;
                for(int u=pre[v];u!=v;u=pre[u]) id[u]=cnt;
            }
        }
        if(cnt==0) break;
        for(int i=1;i<=n;++i) if(!id[i]) id[i]=++cnt;
        for(int i=1;i<=m;++i)
        {
            int u=edge[i].from,v=edge[i].to;
            edge[i].from=id[u];edge[i].to=id[v];
            if(id[u]!=id[v]) edge[i].w-=ine[v];
        }
        r=id[r];
        n=cnt;
    }
    return ans;
}
int main()
{
    init();
    cout<<solve()<<"\n";
}