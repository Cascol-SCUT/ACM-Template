#include<bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
#define maxN 100005
#define mod 998244353
#define INF 0x3f3f3f3f
#define eps 1e-10
#define lll __int128
using namespace std;
ll n,m,p,mi[1005],a[1005];

vector<int> pri,cnt;
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
void exgcd(ll a,ll b,ll &d,ll &x ,ll &y)
{
	if(!b){
		d=a;x=1;y=0;
		return;
	}
	exgcd(b,a%b,d,x,y);
	ll t=x;x=y;y=t-(a/b)*x;
}
ll inverse(ll a,ll p)
{
    ll d,x,y;
    exgcd(a,p,d,x,y);
    return (x%p+p)%p;
}
void proc()
{
    ll pc=p,c=0;
    for(int i=2;i<1005;++i)
    {
        if(pc%i==0){
            c=0;
            pri.push_back(i);
            while(pc%i==0) c++,pc/=i;
            cnt.push_back(c);
        }
    }
    if(pc>1) pri.push_back(pc),cnt.push_back(1);
}
ll qp(ll a,ll b)
{
    ll ans=1;
    while(b){
        if(b&1) ans*=a;
        a*=a;
        b>>=1;
    }
    return ans;
}
ll mod_fac(ll n,ll p,int &e)
{
    if(n==0) return 1;
    if(n<p){
        ll res=1;
        for(int i=2;i<=n;++i){
            res=res*i%p;
        }
        return res;
    }
    ll res;
    res=mod_fac(n/p,p,e);
    e+=n/p;
    if((n/p)%2) return res*(p-mod_fac(n%p,p,e))%p;
    else return res*mod_fac(n%p,p,e)%p;
}
ll C(ll n,ll m,ll prime,ll p)
{
    int a=0,b=0,c=0;
    // m=min(m,n-m);
    ll x=mod_fac(n,prime,a);
    ll y1=mod_fac(m,prime,b);
    ll y2=mod_fac(n-m,prime,c);
    ll r=a-b-c;
    // if(r>0) return 0;
    return x*inverse(y1,p)%p*inverse(y2,p)%p*qp(prime,r)%p;
    // cout<<x*qp(p,a)<<" "<<y1*qp(p,b)<<" "<<y2*qp(p,c)<<endl;
}
void init()
{
    cin>>n>>m>>p;
    proc();
}
void exCRT(int n)
{
    ll lcm=mi[1],ans=a[1];
    for(ll i=2;i<=n;++i)
    {
        ll l=lcm,m2=mi[i],a2=(a[i]-ans%m2+m2)%m2,g,x,y;
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
void solve()
{
    int len=pri.size();
    for(int i=0;i<len;++i){
        mi[i+1]=qp(pri[i],cnt[i]);
    }
    for(int i=0;i<len;++i){
        a[i+1]=C(n,m,pri[i],mi[i+1]);
    }
    exCRT(len);
}
int main()
{
	// freopen("P4777_15.in","r", stdin);
	init();
	solve();
}