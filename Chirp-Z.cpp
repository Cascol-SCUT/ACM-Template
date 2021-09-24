#include<bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define maxN 10000005
#define INF 0x3f3f3f3f
#define eps 1e-10
using namespace std;
const ll G=3,Gi=332748118,P=998244353;
ll a[maxN],b[maxN];
ll n,c,m;
int tax[maxN];
inline int getint() 
{
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
	ll WN,w,*a0,*a1,t;
	int len;
	for(int i=1;i<n;i<<=1){
		len=i<<1;
		WN=qp(opt==1?G:Gi,(P-1)/len);
		for(int st=0;st<n;st+=len){
            w=1;
			a0=a+st;a1=a0+i;
			for(int k=0;k<i;++k){
                // w=(opt==1?wn[1ll*k*n/(2*i)]:iwn[1ll*k*n/(2*i)]);
				t=*a1*w%P;*a1=*a0-t+P;*a0+=t;
				*a1%=P;*a0%=P;
				++a0;++a1;
                w=w*WN%P;
			}
		}
	}
	if(opt==1) return;
	ll inv=qp(n,P-2);
	for(int i=0;i<n;++i) a[i]=a[i]*inv%P;
}
ll f(ll x)
{
    return x*(x-1)/2%(P-1);
}
void init()
{
	cin>>n>>c>>m;
	for(int i=0;i<n;++i) a[i]=getint();
    for(int i=0;i<n;++i) a[i]=a[i]*qp(c,P-1-f(i))%P;
    for(int i=0;i<n+m;++i) b[i]=qp(c,f(i));
    // for(int i=0;i<n+m;++i) cout<<b[i]<<" ";cout<<endl;
    int lim;
    for(lim=1;lim<(2*n+m);lim<<=1);
    assert(lim<maxN);
    makerev(lim);
    reverse(a,a+n);
    NTT(a,lim,1);NTT(b,lim,1);
    for(int i=0;i<lim;++i) b[i]=a[i]*b[i]%P;
    NTT(b,lim,-1);
    // cout<<lim<<endl;
    // for(int i=0;i<n+m;++i) cout<<b[i]<<" ";cout<<endl;return;
    for(int i=0;i<m;++i) cout<<qp(c,P-1-f(i))*b[i+n-1]%P<<" \n"[i==m-1];
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