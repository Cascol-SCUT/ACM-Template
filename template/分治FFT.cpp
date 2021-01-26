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
typedef long long ll;
typedef unsigned long long ull;
#define maxN 460005
#define mod 1000000007
#define INF 0x3f3f3f3f
#define eps 1e-10
using namespace std;
const ll G=3,Gi=332748118,P=998244353;
const double PI = acos(-1);
// complex<double> f[maxN],g[maxN];
ll a[maxN],g[maxN],ans[maxN],f[maxN];
int n,m,tax[maxN];
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
void makerev(int n)
{
	int d=n>>1,p=0;
	tax[p++]=0;tax[p++]=d;
	for(int w=2;w<=n;w<<=1){
		d>>=1;
		for(int i=0;i<w;++i){
			tax[p++]=tax[i]|d;
		}
	}
}
ll qp(ll a,ll b)
{
	ll res=1;
	while(b){
		if(b&1) res=res*a%P;
		a=a*a%P;b>>=1;
	}
	return res;
}
void NTT(ll *a,int n,int opt)
{
	for(int i=1;i<n;++i){
		if(tax[i]>i) swap(a[i],a[tax[i]]);
	}
	ll wn,w,*a0,*a1,t;
	int len;
	for(int i=1;i<n;i<<=1){
		len=i<<1;
		wn=qp(opt==1?G:Gi,(P-1)/len);
		for(int st=0;st<n;st+=len){
			w=1;a0=a+st;a1=a0+i;
			for(int k=0;k<i;++k){
				t=*a1*w%P;*a1=*a0-t+P;*a0+=t;
				*a1%=P;*a0%=P;
				++a0;++a1;w=w*wn%P;
			}
		}
	}
}
void CDQ(int l,int r)
{
	if(l+1>=r) return;
	int mid=l+r>>1;
	CDQ(l,mid);
	int len=r-l;
	makerev(len);
	for(int i=0;i<len;++i) g[i]=a[i];
	for(int i=l;i<mid;++i) f[i-l]=ans[i];
	for(int i=mid;i<r;++i) f[i-l]=0;
	NTT(f,len,1);NTT(g,len,1);
	for(int i=0;i<len;++i) f[i]=f[i]*g[i]%P;
	NTT(f,len,-1);
	ll inv=qp(len,P-2);
	for(int i=mid;i<r;++i) ans[i]=(ans[i]+f[i-l]*inv)%P;
	// cout<<"l r:"<<l<<" "<<r<<endl;
	// for(int i=l;i<r;++i) cout<<ans[i]<<" ";
	// cout<<endl;
	CDQ(mid,r);
}
void init()
{
	n=getint();
	for(int i=1;i<n;++i) a[i]=getint();
	m=n;
	for(n=1;n<m;n<<=1);
	ans[0]=1;
}
void solve()
{
	CDQ(0,n);
	for(int i=0;i<m;++i) cout<<ans[i]<<" ";
	cout<<endl;
}
int main()
{
	//freopen("reflection.in","r", stdin);
	init();
	solve();
}