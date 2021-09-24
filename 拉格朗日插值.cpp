#include<bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
#define maxN 4200005
#define mod 998244353
#define INF 0x3f3f3f3f
#define eps 1e-10
using namespace std;
int n,k;
struct POINT{
	int x,y;
}p[maxN];
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
void exgcd(ll a,ll b,ll &d,ll &x,ll &y){
	if(!b){
		d=a;x=1;y=0;
		return;
	}
	exgcd(b,a%b,d,x,y);
	ll t=x;x=y;y=t-(a/b)*x;
}
ll inverse(ll v){
	if(v<0) v+=mod;
	ll d,x,y;
	exgcd(v,mod,d,x,y);
	return (x+mod)%mod;
}
ll qp(ll a,ll b){
	ll res=1;
	while(b){
		if(b&1) res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
ll f(int k)
{
	ll ans=0,fenz,m,pre=0;
	for(int i=0;i<n;++i){
		ll s1=1,s2=1;
		for(int j=0;j<n;++j){
			if(i==j) continue;
			s1=s1*(k-p[j].x)%mod;
			s2=s2*(p[i].x-p[j].x)%mod;
		}
		ans=(ans+p[i].y*s1%mod*qp(s2,mod-2))%mod;
	}
	return ans;
}
void init()
{
	n=getint();k=getint();
	for(int i=0;i<n;++i) p[i].x=getint(),p[i].y=getint();
	cout<<(f(k)%mod+mod)%mod<<endl;
}
void solve()
{

}
int main()
{
	//freopen("reflection.in","r", stdin);
	init();
	solve();
}