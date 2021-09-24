#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define maxN 2000005
#define mod 1000000007
#define INF 0x3f3f3f3f
#define eps 1e-10
using namespace std;
struct NODE{
	int ch[26],f,len,w;
}st[maxN];
struct EDGE{
	int from,to,next;
}edge[maxN];
string s;
int sz=1,last=1,head[maxN],tot,ans=0;
void add(int c)
{
	int np=++sz,p=last;
	st[np].len=st[last].len+1;
	st[np].w=1;
	last=np;
	while(p && !st[p].ch[c]){
		st[p].ch[c]=np;
		p=st[p].f;
	}
	if(!p){
		st[np].f=1;
		return;
	}
	int q=st[p].ch[c];
	if(st[p].len+1==st[q].len){ //点p代表的子串是后缀,q也是后缀
		st[np].f=q;
	}
	else{ //p是后缀但q不是后缀
		int nq=++sz;
		st[nq]=st[q];
		st[nq].w=0;
		st[nq].len=st[p].len+1;
		st[q].f=st[np].f=nq;
		while(p&&st[p].ch[c]==q){
			st[p].ch[c]=nq;
			p=st[p].f;
		}
	}
}
void add_ed(int u,int v)
{
	edge[++tot].from=u;
	edge[tot].to=v;
	edge[tot].next=head[u];
	head[u]=tot;
}
void dfs(int x)
{
	for(int i=head[x];i;i=edge[i].next){
		int v=edge[i].to;
		dfs(v);
		st[x].w+=st[v].w;
	}
	if(st[x].w>1) ans=max(ans,st[x].w*st[x].len);
	return;
}
void init()
{
	cin>>s;
	int len=s.length();
	for(int i=0;i<len;++i) add(s[i]-'a');
	for(int i=2;i<=sz;++i) add_ed(st[i].f,i);
}
void solve()
{
	dfs(1);
	cout<<ans<<endl;
}
int main()
{
	// freopen("P3804_1.in","r", stdin);
	init();
	solve();
}