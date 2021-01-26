#include<bits/stdc++.h>
#define maxN 205
#define maxM 2005
#define INF 1000000009
#define pi pair<int,int>
using namespace std;
int dis[maxN][maxN];
int u[maxM],v[maxM],b[maxM];
int n,m;
void init()
{
    // ios::sync_with_stdio(0);
    // cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j) dis[i][j]=INF;
    }
    for(int i=1;i<=n;++i) dis[i][i]=0;
    for(int i=1;i<=m;++i)
    {
        cin>>u[i]>>v[i]>>b[i];
        if(u[i]!=v[i]){
            dis[u[i]][v[i]]=1;
            dis[v[i]][u[i]]=(b[i]?-1:1);
        }
    }
}
void solve()
{
    for(int k=1;k<=n;++k){
        for(int i=1;i<=n;++i){
            for(int j=1;j<=n;++j){
                if(dis[i][k]!=INF&&dis[k][j]!=INF){
                    dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
                    if(dis[i][j]<=-INF){
                        cout<<"NO\n";
                        return;
                    }
                }
            }
        }
    }
    pi mx={-1,1};
    for(int i=1;i<=n;++i){
        if(dis[i][i]<0){
            cout<<"NO\n";return;
        }
        for(int j=1;j<=n;++j){
            mx=max(mx,{dis[i][j],i});
        }
    }
    int x=mx.second;
    for(int i=1;i<=m;++i){
        if(abs(dis[x][u[i]]-dis[x][v[i]])==0){
            // cout<<u[i]<<" "<<v[i]<<endl;
            cout<<"NO\n";
            return;
        }
    }
    cout<<"YES\n"<<mx.first<<endl;
    for(int i=1;i<=n;++i) cout<<dis[x][i]<<" \n"[i==n];
    // for(int i=1;i<=n;++i)
}
int main()
{
	init();
	solve();

}