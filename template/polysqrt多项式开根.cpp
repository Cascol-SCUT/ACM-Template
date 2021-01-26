#include<bits/stdc++.h>
#define maxN 1000005
#define INF 0x3f3f3f3f
#define P 998244353
#define lll __int128
typedef long long ll;
using namespace std;
ll G=3,Gi=(P+1)/G,len;
ll a[maxN],b[maxN],Av[maxN],As[maxN],sq[maxN],rev[maxN],inv2;
int tax[maxN];
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
void init()
{
	len=getint();
	for(int i=0;i<len;++i) a[i]=getint();
	inv2=qp(2,P-2);
}
void polyinverse(int n,const ll *a,ll *b) //当前位置
{
	b[0]=qp(a[0],P-2);
	ll *A=Av;
	int len,lim;
	for(len=1,lim;len<(n<<1);len<<=1)
	{
		lim=len<<1;
		for(int i=0;i<len;++i) A[i]=a[i];
		makerev(lim);NTT(A,lim,1);NTT(b,lim,1);
		for(int i=0;i<lim;++i) b[i]=(2-A[i]*b[i]%P+P)%P*b[i]%P;
		NTT(b,lim,-1);
		for(int i=len;i<=lim;++i) b[i]=0;
	}
	for(int i=0;i<len;++i) A[i]=0;
}
void polysqrt(int n,const ll *a,ll *b){
	b[0]= a[0];
	ll *A=As;
	for(int len=1,lim;len<(n<<1);len<<=1)
	{
		lim=len<<1;
		for(int i=0;i<len;++i) A[i]=a[i],rev[i]=0;
		polyinverse(len,b,rev);
		makerev(lim);NTT(A,lim,1);NTT(rev,lim,1);
		for(int i=0;i<lim;++i) A[i]=(A[i]*rev[i])%P;
		NTT(A,lim,-1);
		for(int i=0;i<len;++i) b[i]=(A[i]+b[i])%P*inv2%P;
		for(int i=len;i<lim;++i) b[i]=0;
	}
}
int main()
{
	// freopen("P4777_15.in","r", stdin);
	init();
	polysqrt(len,a,sq);
	for(int i=0;i<len;++i) cout<<sq[i]<<" ";cout<<endl;
}