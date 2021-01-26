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
#include<cmath>
#include<unordered_map>
typedef long long ll;
typedef unsigned long long ull;
#define maxN 15
#define mod 998244353
#define INF 0x3f3f3f3f
#define eps 1e-10
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
void exgcd(ll a,ll b,ll &d,ll &x ,ll &y)
{
	if(!b){
		d=a;x=1;y=0;
		return;
	}
	exgcd(b,a%b,d,x,y);
	ll t=x;x=y;y=t-(a/b)*x;
}
void Chinese_re()
{
	ll M=1,ans=0;
	for(int i=1;i<=n;++i) M*=m[i];
	ll d,t,y,pre=0;
	for(int i=1;i<=n;++i){
		exgcd(M/m[i],m[i],d,t,y);
		ans+=a[i]*(M/m[i])*t;
		ans= (ans%M+M)%M;
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
	Chinese_re();
}
int main()
{
	//freopen("reflection.in","r", stdin);
	init();
	solve();
}