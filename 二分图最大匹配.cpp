#include<bits/stdc++.h>
#define mod 100
#define maxN 50005
#define INF 1000000000
typedef long long ll;
using namespace std;
int n, m, tot;
int matched[505],mp[505][505];
bool ask[505];
vector<int> e[maxN];

bool find(int u)
{
	for (auto v:e[u])
	{
		if (!ask[v])
		{
			ask[v] = true;
			if (!matched[v] || find(matched[v])) {
				matched[v] = u;
				// matched[u] = v; //双向图的时候
				return true;
			}
		}
	}
	return false;
}
int main() {
	cin>>n>>m>>tot;
	for (int i = 0; i < tot; ++i) {
		int u,v; cin>>u>>v;
		if (!mp[u][v]) {
			e[u].push_back(v);
			mp[u][v] = 1;
		}
	}

	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		memset(ask, 0, sizeof(ask));
		ans += find(i);
	}
	cout << ans << endl;
}