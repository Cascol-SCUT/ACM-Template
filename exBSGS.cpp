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
#include<unordered_map>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define maxM 100025
#define maxN 1015
#define maxK 35
#define mod 1000000007
#define INF 0x7f7f7f7f
#define eps 1e-6
using namespace std;
ll a,p,b;
unordered_map<ll,int> mp;
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
ll gcd(ll a,ll b)
{
	if(!b) return a;
	return gcd(b,a%b);
}
void exgcd(ll a,ll b,ll &d,ll &x,ll &y)
{
	if(!b){
		d=a;x=1;y=0;
		return;
	}
	exgcd(b,a%b,d,x,y);
	ll t=x;x=y;y=t-(a/b)*x;
}
ll inverse(ll a,ll b)
{
	ll d,x,y;
	exgcd(a,b,d,x,y);
	return (x%b+b)%b;
}
ll qp(ll a,ll b)
{
	ll ans=1;
	while(b){
		if(b&1) ans=ans*a%p;
		a=a*a%p;
		b>>=1;
	}
	return ans;
}
ll BSGS()
{
	mp.clear();
	int m=sqrt(p)+1;
	ll r=b;
	for(int i=0;i<m;++i){
		mp[r]=i;r=r*a%p;
	}
	ll q=qp(a,m),l=q;
	for(int i=1;i<=m+1;++i,l=l*q%p){
		if(mp.find(l)==mp.end()) continue;
		return i*m-mp[l];
	}
	return -1;
}
ll exBSGS()
{
	ll g,k=0,l=1;
	if(b==1) return 0;
	while((g=gcd(a,p))>1)
	{
		if(b%g) return -1;
		b/=g;p/=g;++k;l=(l*a/g)%p;
		if(l==b) return k;
	}
	b=b*inverse(l,p)%p;
	ll ans=BSGS();
	return ans==-1?-1:ans+k;
}
void init()
{

}
void solve()
{
	while(cin>>a>>p>>b&&(a||b||p))
	{
		a%=p;b%=p;
		ll ans =exBSGS();
		if(ans==-1){
			cout<<"No Solution\n";
		}
		else{
			cout<<ans<<endl;
		}
	}
}
int main()
{
	// freopen("D:\\","w+",stdout);
	cin.tie(0);
	init();
	solve();
}