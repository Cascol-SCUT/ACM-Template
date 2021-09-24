#include<bits/stdc++.h>
typedef long long ll;
#define mod 998244353
using namespace std;
ll p,b,n;
unordered_map<int,int> mp;
ll qp(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1) ans=ans*a%p;
		a=a*a%p;
		b>>=1;
	}
	return ans;
}
ll BSGS(ll b,ll n,ll p)
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
int main()
{
	//freopen("reflection.in","r", stdin);
	cin>>p>>b>>n;
	ll ans=BSGS(b,n,p);
	if(ans==-1){
		cout<<"no solution";return;
	}
	cout<<ans<<endl;
}