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
void exgcd(ll a,ll b,ll &d,ll &x ,ll &y)
{
	if(!b){
		d=a;x=1;y=0;
		return;
	}
	exgcd(b,a%b,d,x,y);
	ll t=x;x=y;y=t-(a/b)*x;
}
ll Chinese_re(vector<int> &a,vector<int> &m)
{
	ll M=1,ans=0;
	int n=m.size();
	for(int i=0;i<n;++i) M*=m[i];
	ll d,t,y,pre=0;
	for(int i=0;i<n;++i){
		exgcd(M/m[i],m[i],d,t,y);
		ans+=a[i]*(M/m[i])*t;
		ans= (ans%M+M)%M;
	}
	return ans;
}
vector<int> a,m;
int main()
{
	//freopen("reflection.in","r", stdin);
	int n;cin>>n;
	for(int i=1;i<=n;++i){
		int x,y;cin>>x>>y;
		m.push_back(x);a.push_back(y);
	}
	cout<<Chinese_re(a,m)<<"\n";
}