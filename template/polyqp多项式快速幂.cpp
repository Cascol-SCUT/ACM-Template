#include<bits/stdc++.h>
#define maxN 1000005
#define INF 0x3f3f3f3f
#define lll __int128
typedef long long ll;
using namespace std;
const ll P=998244353,G=3,Gi=(P+1)/G;
ll n,k;
ll a[maxN],b[maxN],A[maxN],Al[maxN],Ae[maxN],Be[maxN],ans[maxN],ans2[maxN];
int tax[maxN];
inline ll getint() {
	ll num = 0, bj = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == EOF)
			return EOF;
		bj = (c == '-' || bj == -1) ? -1 : 1, c = getchar();
	}
	while (c >= '0' && c <= '9') num = (num * 10 + c - '0')%P, c = getchar();
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
	if(opt==1) return;
	ll inv=qp(n,P-2);
	for(int i=0;i<n;++i) a[i]=a[i]*inv%P;
}
void polyinverse(int n,ll *a,ll *b) //当前位置
{
	b[0]=qp(a[0],P-2);
	memset(A,0,sizeof(A));
	for(int len=1,lim;len<(n<<1);len<<=1)
	{
		lim=len<<1;
		for(int i=0;i<len;++i) A[i]=a[i];
		makerev(lim);NTT(A,lim,1);NTT(b,lim,1);
		for(int i=0;i<lim;++i) b[i]=(2-A[i]*b[i]%P+P)%P*b[i]%P;
		NTT(b,lim,-1);
		for(int i=len;i<=lim;++i) b[i]=0;
	}
}
void integrate(int n,ll *a,ll *b)
{
	for(int i=1;i<n;++i){
		b[i]=a[i-1]*qp(i,P-2)%P;
	}
	b[0]=0;
}
void derivate(int n,ll *a,ll *b)
{
	for(int i=1;i<n;++i) b[i-1]=i*a[i]%P;
	b[n-1]=0;
}
void polyln(int n,ll *a,ll *b)
{
	polyinverse(n,a,b);
	derivate(n,a,Al);
	int m=n+n-1,lim;
	for(lim=1;lim<m;lim<<=1);
	makerev(lim);
	NTT(Al,lim,1);NTT(b,lim,1);
	for(int i=0;i<lim;++i) Al[i]=Al[i]*b[i]%P;
	NTT(Al,lim,-1);
	integrate(n,Al,b);
	for(int i=n;i<lim;++i) Al[i]=b[i]=0;
}
void polyexp(int n,ll *a,ll *b)
{
	b[0]=1;
	int len,lim;
	for(len=2,lim;len<(n<<1);len<<=1)
	{
		lim=len<<1;
		for(int i=0;i<len;++i) Be[i]=0;
		// for(int i=0;i<len;++i) Ae[i]=a[i];
		polyln(len,b,Be);
		makerev(lim);
		for(int i=0;i<len;++i) Be[i]=(a[i]-Be[i]+P)%P;
		Be[0]=(Be[0]+1)%P;
		NTT(b,lim,1);NTT(Be,lim,1);
		for(int i=0;i<lim;++i) b[i]=b[i]*Be[i]%P;
		NTT(b,lim,-1);
		// for(int i=len;i<lim;++i) b[i]=0;
	}
	for(int i=n;i<lim;++i) b[i]=0;
}
void polyqp(int n,ll *a,ll k)
{
	polyln(n,a,ans);
	memset(Al,0,sizeof(Al));
	for(int i=0;i<n;++i) ans[i]=ans[i]*k%P;
	polyexp(n,ans,ans2);
}
void init()
{
    n=getint();k=getint();
	for(int i=0;i<n;++i) a[i]=getint()%P;
}
int main()
{
	init();
	polyqp(n,a,k);
	for(int i=0;i<n;++i) cout<<ans2[i]<<" ";cout<<endl;
}
