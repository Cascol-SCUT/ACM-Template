#include<bits/stdc++.h>
#define maxN 50005
typedef long long ll;
using namespace std;
ll cnt[maxN],a[maxN],ans1[maxN],ans2[maxN],n,m,sqn;
ll sum;
struct query{
	int l,r,no;
}q[maxN];
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
bool cmp(query x, query y)
{
	return (x.l/sqn<y.l/sqn) || (x.l/sqn==y.l/sqn && x.r<y.r);
}
int gcd(int a,int b)
{
	if(!b) return a;
	return gcd(b,a%b);
}
void del(int x)
{
	--cnt[x];
	sum-=cnt[x];
}
void add(int x)
{
	sum+=cnt[x];
	cnt[x]++;
}
int main()
{
	n=getint();m=getint();
	sqn=sqrt(n);
	for(int i=1;i<=n;++i) a[i]=getint();
	for(int i=1;i<=m;++i){
		q[i].l=getint();q[i].r=getint();q[i].no=i;
	}
	sort(q+1,q+m+1,cmp);
	int l=1,r=0;
	for(int i=1;i<=m;++i)
	{
		if(q[i].l==q[i].r){
			ans1[q[i].no]=0;ans2[q[i].no]=1;continue;
		}
		while(l>q[i].l) add(a[--l]);
		while(r<q[i].r) add(a[++r]);
		while(l<q[i].l) del(a[l++]);
		while(r>q[i].r) del(a[r--]);
		ans1[q[i].no]=sum;
		ans2[q[i].no]=1ll*(r-l+1)*(r-l)/2;
	}
	for(int i=1;i<=m;++i){
		if(ans1[i]){
			ll g=gcd(ans1[i],ans2[i]);
			ans1[i]/=g;ans2[i]/=g;
		}
		else ans2[i]=1;
		cout<<ans1[i]<<"/"<<ans2[i]<<"\n";
	}
}