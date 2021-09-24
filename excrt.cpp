#include<bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
#define maxN 100005
#define mod 998244353
#define INF 0x3f3f3f3f
#define eps 1e-10
#define lll __int128
using namespace std;
void exgcd(ll a,ll b,ll &d,ll &x ,ll &y)
{
	if(!b){
		d=a;x=1;y=0;
		return;
	}
	exgcd(b,a%b,d,x,y);
	ll t=x;x=y;y=t-(a/b)*x;
}
ll exCRT(vector<ll> &a,vector<ll> &m)
{
    ll lcm=m[0],ans=a[0];
	int n=a.size();
    for(ll i=1;i<n;++i)
    {
        ll l=lcm,m2=m[i],a2=(a[i]-ans%m2+m2)%m2,g,x,y;
        exgcd(l,m2,g,x,y);
        if(a2%g){
            return -1;
        }
        m2/=g;lcm=lcm*m2;a2/=g;
        x=(((lll)x*a2)%m2+m2)%m2;
        ans= ((ans+l*x%lcm)%lcm+lcm)%lcm;
    }
    return ans;
}
vector<ll> a,m;
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;++i){
		ll x,y;cin>>x>>y;
		m.push_back(x);a.push_back(y);
	}
	cout<<exCRT(a,m)<<"\n";
}