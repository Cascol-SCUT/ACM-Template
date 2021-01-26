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
#define maxN 200025
#define mod 1000000007
#define INF 0x3f3f3f3f
#define eps 1e-6
using namespace std;
int n,m,root,p,tot,cnt,id[maxN],v[maxN],fa[maxN],dep[maxN];
int wt[maxN],head[maxN],siz[maxN],son[maxN],top[maxN];
ll sum[maxN*4],ad[maxN*4];
struct EDGE{
	int from,to,next;
}edge[maxN];
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
void add(int u,int v)
{
	edge[++tot].from=u;
	edge[tot].to=v;
	edge[tot].next=head[u];
	head[u]=tot;
}
void dfs(int x,int f,int deep)
{
	dep[x]=deep;fa[x]=f;siz[x]=1;
	int mx=-1;
	for(int i=head[x];i;i=edge[i].next)
	{
		int v=edge[i].to;
		if(v==f) continue;
		dfs(v,x,deep+1);
		siz[x]+=siz[v];
		if(siz[v]>mx){
			mx=siz[v];
			son[x]=v;
		}
	}
}
void dfs2(int x,int topf)
{
	id[x]=++cnt;
	wt[cnt]=v[x];
	top[x]=topf;
	if(!son[x]) return;
	dfs2(son[x],topf);
	for(int i=head[x];i;i=edge[i].next)
	{
		int v=edge[i].to;
		if(v==fa[x]||v==son[x]) continue;
		dfs2(v,v);
	}
}
void ADD(int k,int l,int r,int v)
{
	if(l>r) return;
	sum[k]=(sum[k]+(r-l+1)*v)%p;
	ad[k]=(ad[k]+v)%p;
}
void pushdown(int k,int l,int r)
{
	if(ad[k]){
		int mid=l+r>>1;
		ADD(k*2,l,mid,ad[k]);
		ADD(k*2+1,mid+1,r,ad[k]);
		ad[k]=0;
	} 
}
void update(int k,int l,int r,int x,int y,int z)
{
	if(x<=l&&r<=y){
		ad[k]+=z;
		sum[k]=(sum[k]+(r-l+1)*z)%p;
		return;
	}
	pushdown(k,l,r);
	int mid=l+r>>1;
	if(mid>=x)update(k*2,l,mid,x,y,z);
	if(mid+1<=y)update(k*2+1,mid+1,r,x,y,z);
	sum[k]=sum[k*2]+sum[k*2+1];
}
int query(int k,int l,int r,int x,int y)
{
	// cout<<l<<" "<<r<<" "<<sum[k]<<endl;
	if(x<=l&&r<=y){
		return sum[k];
	}
	// if(l==r) return 0;
	pushdown(k,l,r);
	int mid=l+r>>1;
	ll ans=0;
	if(mid>=x) ans= (ans+query(k*2,l,mid,x,y))%p;
	if(mid+1<=y)ans=(ans+query(k*2+1,mid+1,r,x,y))%p;
	return ans%p;
}
void build(int k,int l,int r)
{
	if(l==r){
		sum[k]=wt[l];
		return;
	}
	int mid=l+r>>1;
	build(k*2,l,mid);
	build(k*2+1,mid+1,r);
	sum[k]=(sum[k*2]+sum[k*2+1])%p;
}
int qRange(int x,int y)
{
	ll ans=0;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		ans= (ans+query(1,1,n,id[top[x]],id[x]))%p;
		x=fa[top[x]];
	}
	if(dep[x]<dep[y]) swap(x,y);
	ans= (ans+query(1,1,n,id[y],id[x]))%p;
	return ans;
}
void uRange(int x,int y,int z)
{
	z%=p;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		update(1,1,n,id[top[x]],id[x],z);
		x=fa[top[x]];
	}
	if(dep[x]<dep[y]) swap(x,y);
	update(1,1,n,id[y],id[x],z);
}
int qson(int x)
{
	return query(1,1,n,id[x],id[x]+siz[x]-1);
}
void upson(int x,int z)
{
	update(1,1,n,id[x],id[x]+siz[x]-1,z);
}
void init()
{
	n=getint();m=getint();root=getint();p=getint();
	for(int i=1;i<=n;++i) v[i]=getint();
	int u,v;
	for(int i=1;i<n;++i){
		u=getint();v=getint();
		add(u,v);add(v,u);
	}
	dfs(root,0,0);
	dfs2(root,root);
	build(1,1,n);
	// for(int i=1;i<=n;++i) cout<<wt[i]<<" ";cout<<endl;
	// query(1,1,n,1,n);
	// for(int i=1;i<=n;++i) cout<<id[i]<<" ";cout<<endl;
}
void solve()
{
	int x,y,z;
	for(int i=1;i<=m;++i)
	{
		switch(getint())
		{
			case 1:{
				x=getint();y=getint();z=getint();
				uRange(x,y,z);
				break;
			}
			case 2:{
				x=getint();y=getint();
				cout<<qRange(x,y)<<endl;;
				break;
			}
			case 3:{
				x=getint();z=getint();
				upson(x,z);
				break;
			}
			case 4:{
				x=getint();
				cout<<qson(x)<<endl;
				break;
			}
		}
	}
}
int main()
{
	//freopen("reflection.in","r", stdin);
	init();
	solve();
}