#include<bits/stdc++.h>
#define maxN 200005
#define N 1000000
#define INF 1000000000
#define lowbit(x) ((x)&(-x))
typedef long long ll;
using namespace std;

struct node{
	friend ostream & operator <<(ostream &out,node &obj);
	int a,b,c,cnt,ans;
	bool operator !=(const node x) const{
		return  a!=x.a||b!=x.b||c!=x.c;
	}
}s1[maxN],s2[maxN];
int n,m,k,an[maxN];
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
bool cmp1(node x,node y)
{
	return x.a<y.a||(x.a==y.a&&x.b<y.b)||(x.a==y.a&&x.b==y.b&&x.c<y.c);
}
bool cmp2(node x,node y)
{
	return x.b<y.b||(x.b==y.b&&x.c<y.c);
}
int tr[maxN];
void add(int x,int v)
{
	for(;x<=k;x+=lowbit(x)) tr[x]+=v;
}
int query(int x)
{
	int res=0;
	for(;x;x-=lowbit(x)) res+=tr[x];
	return res;
}
void init()
{
	n=getint();k=getint();
	for(int i=1;i<=n;++i) s1[i].a=getint(),s1[i].b=getint(),s1[i].c=getint();
	sort(s1+1,s1+n+1,cmp1);
	int top=0;
	m=0;
	for(int i=1;i<=n;++i)
	{
		top++;
		if(s1[i]!=s1[i+1]){
			s2[++m]=s1[i];
			s2[m].cnt=top;
			top=0;
		}
	}
}
void CDQ(int l,int r)
{
	if(l==r) return;
	int mid=l+r>>1;
	CDQ(l,mid);CDQ(mid+1,r);
	sort(s2+l,s2+mid+1,cmp2);
	sort(s2+mid+1,s2+r+1,cmp2);
	int i,j=l;
	for(i=mid+1;i<=r;++i)
	{
		while(j<=mid&&s2[i].b>=s2[j].b)
		{
			add(s2[j].c,s2[j].cnt);
			++j;
		}
		s2[i].ans+=query(s2[i].c);
	}
	for(i=l;i<j;++i) add(s2[i].c,-s2[i].cnt); // 回退
}
void solve()
{
	CDQ(1,m);
	for(int i=1;i<=m;++i)
		an[s2[i].ans+s2[i].cnt-1]+=s2[i].cnt;	
	for(int i=0;i<n;++i) cout<<an[i]<<endl;

}
int main()
{
	// ios::sync_with_stdio(0);
	// cin.tie(0);
	init();
	solve();
}