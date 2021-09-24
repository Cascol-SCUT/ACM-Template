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
typedef unsigned long long ull;
#define maxN 460005
#define mod 1000000007
#define INF 0x3f3f3f3f
#define eps 1e-10
using namespace std;
int sz,a[maxN],original[maxN],n,m,root=1;
struct TREE{
	int fa,size,cnt,value,tag,son[2];
}s[maxN];
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
int get(int x)
{
	return s[s[x].fa].son[1]==x;
}
void update(int x)
{
	if(x){
		s[x].size=s[x].cnt;
		if(s[x].son[0]) s[x].size+=s[s[x].son[0]].size;
		if(s[x].son[1]) s[x].size+=s[s[x].son[1]].size;
	}
}
void pushdown(int x)
{
	if(x&&s[x].tag){
		s[s[x].son[0]].tag^=1;
		s[s[x].son[1]].tag^=1;
		swap(s[x].son[1],s[x].son[0]);
		s[x].tag=0;
	}
}
int build_tree(int l,int r,int fa)
{
	if(l>r) return 0;
	int now=++sz,mid=l+r>>1;
	s[now].fa=fa;
	s[now].son[0]=s[now].son[1]=0;
	s[now].cnt=1;s[now].size=1;
	s[now].value=original[mid];
	s[now].son[0]=build_tree(l,mid-1,now);
	s[now].son[1]=build_tree(mid+1,r,now);
	update(now);
	return now;
}
void rotate(int x) {
	int old = s[x].fa, oldf = s[old].fa;
	pushdown(x);pushdown(old);
	int which = get(x);
	s[old].son[which] = s[x].son[which ^ 1];
	if(s[old].son[which]) s[s[old].son[which]].fa = old;
	s[old].fa = x; s[x].son[which ^ 1] = old;
	s[x].fa = oldf;
	if (oldf)
		s[oldf].son[s[oldf].son[1] == old] = x;
	update(old); update(x);
}
void splay(int x,int goal)
{
	for(int fa;(fa=s[x].fa)!=goal;rotate(x))
	{
		if(s[fa].fa!=goal){
			rotate(get(x)==get(fa)?fa:x);
		}
	}
	if(!goal) root=x;
}
int find(int x)
{
	int cur=root;
	while(true)
	{
		pushdown(cur);
		if(x<=s[s[cur].son[0]].size){
			cur=s[cur].son[0];
		}
		else{
			x-=s[s[cur].son[0]].size+1;
			if(!x) return cur;
			cur=s[cur].son[1];
		}
	}
}
void reverse(int x,int y)
{
	int l=x,r=y+2;
	l=find(l);r=find(r);
	splay(l,0);
	splay(r,l);
	s[s[s[root].son[1]].son[0]].tag^=1;
}
void dfs(int x)
{
	if(!x) return;
	pushdown(x);
	dfs(s[x].son[0]);
	if(s[x].value!=INF && s[x].value!=-INF) cout<<s[x].value<<" ";
	dfs(s[x].son[1]);
}
void init()
{
	n=getint();m=getint();
	original[1]=INF;original[n+2]=-INF;
	for(int i=2;i<n+2;++i){
		original[i]=i-1;
	}
	build_tree(1,n+2,0);
	// cout<<"-----------------\n";
	// dfs(root); cout<<endl;
}
void solve()
{
	int l,r;
	for(int i=1;i<=m;++i){
		l=getint();r=getint();
		reverse(l,r);
		// cout<<"-----------------\n";
		// dfs(root); cout<<endl;
	}
	// cout<<"---------------\n";
	dfs(root);cout<<endl;
}
int main()
{
	//freopen("reflection.in","r", stdin);
	init();
	solve();
}