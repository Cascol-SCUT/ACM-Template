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
#include<random>
#include<cmath>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define maxN 1000025
#define maxK 35
#define mod 1000000007
#define INF 0x3f3f3f3f
#define eps 1e-6
using namespace std;
int a[maxN],root[maxN],tot,n,m;
struct NODE{
	int l,r,val;
}tr[maxN*20];
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
int clone(int node)
{
	tr[++tot]=tr[node];
	return tot;
}
int build(int l,int r)
{
	if(l==r){
		tr[++tot].val=a[l];
		return tot;
	}
	int mid=l+r>>1,node=++tot;
	tr[node].l=build(l,mid);
	tr[node].r=build(mid+1,r);
	return node;
}
inline int update(int node,int l,int r,int x,int v)
{
	node=clone(node);
	if(l==r){
		tr[node].val=v;
		return node;
	}
	int mid=l+r>>1;
	if(x<=mid){
		tr[node].l=update(tr[node].l,l,mid,x,v);
	}
	else{
		tr[node].r=update(tr[node].r,mid+1,r,x,v);
	}
	return node;
}
inline int query(int node,int l,int r,int x)
{
	if(l==r) return tr[node].val;
	int mid=l+r>>1;
	if(x<=mid) return query(tr[node].l,l,mid,x);
	else return query(tr[node].r,mid+1,r,x);
}
void init()
{
	n=getint();m=getint();
	for(int i=1;i<=n;++i){
		a[i]=getint();
	}
	build(1,n);
	root[0]=1;
}
void pr(int x)
{
	cout<<"tree "<<x<<": ";
	for(int i=1;i<=n;++i) cout<<query(root[x],1,n,i)<<" ";cout<<endl;
}
void solve()
{
	// pr(0);
	int v,c,x,val;
	for(int i=1;i<=m;++i)
	{
		v=getint();c=getint();
		if(c==1){
			root[i]=tot+1;
			x=getint();val=getint();
			update(root[v],1,n,x,val);
		}
		else{
			root[i]=root[v];
			x=getint();
			cout<<query(root[v],1,n,x)<<endl;
		}
		// pr(i);
	}
}
int main()
{
	// freopen("D:\\","w+",stdout);
	init();
	solve();
}