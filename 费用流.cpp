#include<bits/stdc++.h>
typedef long long ll;
#define maxM 100025
#define maxN 10015
#define INF 0x3f3f3f3f
using namespace std;
struct Edge{
	int from,to,f,cost;
}edge[maxM];
int n,m,s,t;
struct MCMF{
	vector<Edge> edges;
  	vector<int> G[maxN];
	int dis[maxN],flow[maxN],pre[maxN];
	bool vis[maxN];
	void init(int n){
		for(int i=1;i<=n;++i) G[i].clear();
		edges.clear();
	}
	void AddEdge(int u,int v,int flow,int cost){
		edges.push_back({u,v,flow,cost});
		G[u].push_back(edges.size()-1);
		edges.push_back({v,u,0,-cost});
		G[v].push_back(edges.size()-1);
	}
	
	bool spfa(int s,int t){
		memset(dis,INF,sizeof(dis));
		memset(flow,0,sizeof(flow));
		dis[s]=0; pre[s]=-1; flow[s]=INF;
		queue<int> q; q.push(s);
		while(!q.empty())
		{
			int u=q.front();q.pop();
			vis[u]=false;
			for(int i=0;i<G[u].size();++i)
			{
				Edge& e=edges[G[u][i]];
				if(e.f<=0) continue;
				if(dis[e.to]>dis[u]+e.cost)
				{
					dis[e.to]=dis[u]+e.cost;
					pre[e.to]=G[u][i];
					flow[e.to]=min(flow[u],e.f);
					if(vis[e.to]) continue;
					q.push(e.to); vis[e.to]=true;
				}
			}
		}
		return dis[t]!=INF;
	}
	pair<ll,ll> mcmf(int s,int t){
		ll max_flow=0,min_cost=0;
		while(spfa(s,t)){
			max_flow+=flow[t]; min_cost+=flow[t]*dis[t];
			for(int i=pre[t];i!=-1;i=pre[edges[i].from]){
				edges[i].f-=flow[t];
				edges[i^1].f+=flow[t];
			}
		}
		return make_pair(max_flow,min_cost);
	}
}mc;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n>>m>>s>>t;
	for(int i=0;i<m;++i){
		int u,v,f,cost; cin>>u>>v>>f>>cost;
		mc.AddEdge(u,v,f,cost);
	}
	auto ans=mc.mcmf(s,t);
	cout<<ans.first<<" "<<ans.second<<"\n";
}