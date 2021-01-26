#include<bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
#define maxN 100005
#define mod 998244353
#define INF 0x3f3f3f3f
#define eps 1e-10
#define lll __int128
using namespace std;
ll n,a[maxN],m[maxN];
inline ll getint() {
	ll num = 0, bj = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == EOF)
			return EOF;
		bj = (c == '-' || bj == -1) ? -1 : 1, c = getchar();
	}
	while (c >= '0' && c <= '9') {
		num = num * 10 + c - '0';
		c = getchar();
	}
	return num * bj;
}
ll mul(ll a,ll b,ll p)
{
    ll res=0;
    while(b){
        if(b&1) res=(res+a)%p;
        a=(a+a)%p;
        b>>=1;
    }
    return res;
}
void exgcd(ll a,ll b,ll &d,ll &x ,ll &y)
{
	if(!b){
		d=a;x=1;y=0;
		return;
	}
	exgcd(b,a%b,d,x,y);
	ll t=x;x=y;y=t-(a/b)*x;
}
void exCRT()
{
    ll lcm=m[1],ans=a[1];
    for(ll i=2;i<=n;++i)
    {
        ll l=lcm,m2=m[i],a2=(a[i]-ans%m2+m2)%m2,g,x,y;
        exgcd(l,m2,g,x,y);
        if(a2%g){
            cout<<-1<<endl;
            return ;
        }
        m2/=g;lcm=lcm*m2;a2/=g;
        x=(((lll)x*a2)%m2+m2)%m2;
        // x=mul(x<0?m2+x:x,a2,m2);
        ans= ((ans+l*x%lcm)%lcm+lcm)%lcm;
    }
    cout<<ans<<endl;
}
void init()
{
	n=getint();
	for(int i=1;i<=n;++i){
		m[i]=getint();a[i]=getint();
	}
}
void solve()
{
    exCRT();
}
int main()
{
	// freopen("P4777_15.in","r", stdin);
	init();
	solve();
}