#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
#define maxN (1<<20)+5
#define maxM 4005
#define mod 1000000009
#define eps 1e-10
#define lll __int128
using namespace std;
ll n,max_fac;
inline ll getint() {
	ll num = 0, bj = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == EOF)
			return EOF;
		bj = (c == '-' || bj == -1) ? -1 : 1, c = getchar();
	}
	while (c >= '0' && c <= '9') num = num * 10 + c - '0', c = getchar();
	return num * bj;
}
inline ll gcd(ll a,ll b)
{
    if(!b) return a;
    else return gcd(b,a%b);
}
inline ll qp(ll a,ll b,ll x)
{
    ll ans=1;
    while(b){
        if(b&1) ans=(lll)ans*a%x;
        a=(lll)a*a%x;
        b>>=1;
    }
    return ans;
}
inline bool milller_rabin(ll x,ll a)
{
    ll k=x-1;
    while(k)
    {
        ll cur=qp(a,k,x);
        if(cur!=1&&cur!=x-1) return false;
        if((k&1)||cur==x-1) return true;
        k>>=1;
    }
    return true;
}
inline bool prime(ll x)
{
    if(x==46856248255981ll || x<2)
        return false;
    if(x==2 || x==3 || x==7 || x==61 || x==24251)
        return true;
    return milller_rabin(x,2) && milller_rabin(x,61);
}
inline ll f(ll x,ll c,ll n)
{
    return ((lll)x*x+c)%n;
}
inline ll pollard_rho(ll n)
{
    if(n==4) return 2;
    ll c=1ll*rand()%(n-1)+1,x=1ll*rand()%(n-1)+1,y=x,d;
    x=f(x,c,n);y=f(f(y,c,n),c,n);    
    for(int goal=1,lim=127;x!=y;goal<<=1)
    {
        ll val=1;
        for(int st=1;st<=goal&&x!=y;++st){
            val=(lll)abs(x-y)*val%n;
            x=f(x,c,n);y=f(f(y,c,n),c,n);
            if(st%127==0){
                d=gcd(val,n);
                if(d>1) return d;
            }
        }
        d=gcd(val,n);
        if(d!=1) return d;
    }
    return n;
}
void fac(ll n)
{
    if(n<=max_fac||n<2) return;
    if(prime(n)){
        max_fac=max(max_fac,n);
        return;
    }
    ll p=n;
    while(p>=n) p=pollard_rho(n);
    while(!(n%p)) n/=p;
    fac(n);fac(p);
}
void init()
{
    
}
void solve()
{
    int T;cin>>T;
    srand(time(0));
    while(T--)
    {
        n=getint();
        max_fac=0;
        fac(n);
        if(max_fac==n) cout<<"Prime\n";
        else cout<<max_fac<<endl;
    }  
}
int main()
{
	cin.tie(0);
	init();
	solve();
}