#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
#define maxN 100005
using namespace std;
unordered_map<int,int> c[maxN];
vector<int> e[maxN];
ll ans[maxN];
int mx[maxN];
void merge(int u,int v)
{
    if(c[u].size()<c[v].size()) swap(c[u],c[v]),mx[u]=mx[v],ans[u]=ans[v];
    for(auto &item:c[v]){
        if(c[u].find(item.first)==c[u].end()) c[u][item.first]=item.second;
        else c[u][item.first]+=item.second;
        if(c[u][item.first]>mx[u]){
            mx[u]=c[u][item.first];
            ans[u]=item.first;
        }
        else if(c[u][item.first]==mx[u]) ans[u]+=item.first;
    }
}
void dfs(int u,int p)
{
    for(auto &v:e[u]){
        if(v==p) continue;
        dfs(v,u);merge(u,v);
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;cin>>n;
    for(int i=1;i<=n;++i) {
        int x;cin>>x;
        mx[i]=1;ans[i]=x;
        c[i][x]=1;
    }
    int u,v;
    for(int i=1;i<n;++i){
        cin>>u>>v;
        e[u].push_back(v);e[v].push_back(u);
    }
    dfs(1,0);
    for(int i=1;i<=n;++i) cout<<ans[i]<<" \n"[i==n];
}
