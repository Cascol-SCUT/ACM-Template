#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
#define maxN (1<<20)+5
#define maxM 32000
#define mod 1000000007
#define eps 1e-10
using namespace std;
ll n;
int vis[maxN];
vector<int> pri,fac;
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
ll qp(ll a,ll b)
{
    ll ans=1;
    while(b){
        if(b&1) ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
void proc()
{
    int sz;
    for(int i=2;i<maxN;++i)
    {
        if(!vis[i]){
            pri.push_back(i);
            vis[i]=i;
        }
        sz=pri.size();
        for(int j=0;pri[j]<=vis[i]&&j<sz&&i*pri[j]<maxN;++j){
            vis[i*pri[j]]=pri[j];
        }
    }
    // for(int i=0;i<20;++i) cout<<pri[i]<<" ";cout<<endl;
}
void div()
{
    fac.clear();
    for(int i=1;i<=sqrt(n);++i)
    {
        if(!(n%i)){
            fac.push_back(i);
            if(n!=i*i) fac.push_back(n/i);
        }
    }
}
ll phi(ll x)
{
    int sz=pri.size();
    ll ans=x;
    for(int i=0;i<sz&&pri[i]*pri[i]<=x;++i)
    {
        if(x%pri[i]==0){
            ans=ans-ans/pri[i];
            while(x%pri[i]==0) x/=pri[i];
        }
    }
    if(x>1) ans=ans-ans/x;
    return ans;
}
void init()
{
    proc();
}
void solve()
{
    int T;cin>>T;
    ll ans;
    while(T--)
    {
        ans=0;
        n=getint();
        div();
        int sz=fac.size();
        for(int i=0;i<sz;++i){
            ans=(ans+qp(n,fac[i])*phi(n/fac[i]))%mod;
        }
        cout<<ans*qp(n,mod-2)%mod<<endl;
    }
}
int main()
{
	cin.tie(0);
	init();
	solve();
}