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
#define maxN 50005
#define mod 998244353
#define INF 0x3f3f3f3f
#define eps 1e-10
using namespace std;
ll p,b,n;
unordered_map<int,int> mp;
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
ll qp(ll a,ll b){
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
	int m=sqrt(p)+1;
	ll r=n;
	for(int i=0;i<m;++i){
		if(mp.find(r)!=mp.end()) continue;
		mp[r]=i;r=r*b%p;
	}
	ll q=qp(b,m),l=q;
	for(int i=1;i<=m+1;++i,l=l*q%p){
		if(mp.find(l)==mp.end()) continue;
		return i*m-mp[l];
	}
	return -1;
}
void init()
{
	p=getint();b=getint();n=getint();
}
void solve()
{
	ll ans=BSGS();
	if(ans==-1){
		cout<<"no solution";return;
	}
	cout<<ans<<endl;
}
int main()
{
	//freopen("reflection.in","r", stdin);
	init();
	solve();
}