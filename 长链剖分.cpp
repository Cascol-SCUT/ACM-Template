#include <iostream>
#include <algorithm>
#include <iomanip>
#include <queue>
#include<string>
#include<complex>
#include<string.h>
#include <vector>
#include <cstdio>
#include<map>
#include<cmath>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define maxN 500025
#define maxK 35
#define mod 1000000007
#define INF 0x3f3f3f3f
#define eps 1e-6
using namespace std;
unsigned int s;
int n,q,f[maxN][maxK],dep[maxN],h[maxN],son[maxN],top[maxN],id[maxN],Log[maxN],root,cnt;
vector<vector<int>> edge,u,d;
ll ans;
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
inline unsigned int get(unsigned int x)
{
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return s=x;
} 
void dfs1(int x)
{
	dep[x]=h[x]=h[f[x][0]]+1;
	for(auto y:edge[x]){
		for(int i=0;f[y][i];++i) f[y][i+1]=f[f[y][i]][i];
		dfs1(y);
		if(dep[y]>dep[x]) dep[x]=dep[y],son[x]=y;
	}
}
void dfs2(int x,int topf)
{
	top[x]=topf;
	if(x==topf){
		for(int i=0,cur=x;i<=dep[x]-h[x]&&cur;++i,cur=f[cur][0])
			u[x].push_back(cur);
		for(int i=0,cur=x;i<=dep[x]-h[x]&&cur;++i,cur=son[cur])
			d[x].push_back(cur);
	}
	if(son[x]) dfs2(son[x],topf);
	for(auto y:edge[x]){
		if(y!=son[x]){
			dfs2(y,y);
		}
	}
}
int ask(int x,int k)
{
	if(!k) return x;
	x=f[x][Log[k]]; k-=1<<Log[k];
	k-=h[x]-h[top[x]]; x=top[x];
	if(k>0) return u[x][k];
	else return d[x][-k];
}
void init()
{
	cin>>n>>q>>s;
	edge.resize(n+1);
	u.resize(n+1);d.resize(n+1);
	Log[0]=-1;
	for(int i=1;i<=n;++i){
		f[i][0]=getint();
		edge[f[i][0]].push_back(i);
		Log[i]=Log[i>>1]+1;
	}
	root=edge[0][0];
	dfs1(root);
	dfs2(root,root);
	// for(int i=1;i<=n;++i) cout<<h[i]<<" ";cout<<endl;
}
void solve()
{
	int x=0,k=0;
	ll ANS=0;
	for(int i=1;i<=q;++i)
	{
		x=(get(s)^ans)%n+1;
		k=(get(s)^ans)%h[x];
		ANS^=i*(ans=ask(x,k));
		// cout<<ans<<endl;
	}
	cout<<ANS<<endl;
}
int main()
{
	//freopen("reflection.in","r", stdin);
	init();
	solve();
}