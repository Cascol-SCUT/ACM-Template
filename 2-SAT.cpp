#include <bits/stdc++.h>
typedef long long ll;
#define maxN 1000005
#define maxK 10000005
#define INF 0x3f3f3f3f
using namespace std;
int n,m,head[maxN*2],tot;
int dfn[maxN*2],low[maxN*2],cnt,col;
int sd[maxN*2];
bool vis[maxN*2];
struct EDGE{
    int from,to,next;
}edge[maxN*2];
vector<int> st;
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
void tarjan(int u)
{
    dfn[u]=low[u]=++cnt;
    vis[u]=1;
    st.push_back(u);
    for(int i=head[u];i;i=edge[i].next)
    {
        int v=edge[i].to;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(vis[v]) low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u])
    {
        int y;++col;
        while(true){
            y=st.back();st.pop_back();
            sd[y]=col;
            vis[y]=0;
            if(u==y) break;
        }
    }
}
void add(int u,int v)
{
    edge[++tot].from=u;
    edge[tot].to=v;
    edge[tot].next=head[u];
    head[u]=tot;
}
void init()
{
    n=getint();m=getint();
    int u,v,w1,w2,p1,p2;
    for(int i=1;i<=m;++i){ //a 或 b
        u=getint();w1=getint();v=getint();w2=getint();
        add(v+n*(w2^1),u+n*(w1&1));
        add(u+n*(w1^1),v+n*(w2&1));
    }
    // for(int i=1;i<=tot;++i) cout<<edge[i].from<<" "<<edge[i].to<<endl;
    for(int i=1;i<=2*n;++i) if(!dfn[i]) tarjan(i); 
    // for(int i=1;i<=2*n;++i) cout<<sd[i]<<" ";cout<<endl;
    // cout<<low[3]<<endl;
}
void solve()
{
    for(int i=1;i<=n;++i)
    {
        if(sd[i]==sd[i+n]){
            cout<<"IMPOSSIBLE\n";return;
        }
    }
    cout<<"POSSIBLE\n";
    for(int i=1;i<=n;++i){
        if(sd[i]>sd[i+n]) cout<<1<<" ";
        else cout<<0<<" ";
    }
    cout<<endl;
}
int main()
{
	// freopen("D:\\","w+",stdout);
    init();
	solve();
}