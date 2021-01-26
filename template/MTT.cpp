#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define maxN 4200005
#define mod 1000000007
#define INF 0x3f3f3f3f
#define eps 1e-10
using namespace std;
const double PI = acos(-1);
const complex<ld> I(0,1);
complex<ld> wn[maxN],a0[maxN],a1[maxN],b0[maxN],b1[maxN],p[maxN],q[maxN];
ll P,ans[maxN];
int n,m,M,tax[maxN];
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
void FFT(complex<ld> *a,int n,int opt)
{
	for(int i=1;i<n;++i){
		if(tax[i]>i) swap(a[i],a[tax[i]]);
	}
	complex<ld> w,*a0,*a1,t;
	int len;
	for(int i=1;i<n;i<<=1){
		len=i<<1;
		for(int st=0;st<n;st+=len){
			a0=a+st;a1=a0+i;
			for(int k=0;k<i;++k){
				w=wn[1ll*k*n/i];
				if(opt!=1) w=conj(w);
				t=*a1*w;*a1=*a0-t;*a0+=t;
				++a0;++a1;
			}
		}
	}
	if(opt==-1){
		for(int i=0;i<n;++i) a[i]/=n;
	}
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
void qDFT(complex<ld> *a,complex<ld> *b,int m,int n)
{
	for(int i=0;i<n;++i) a[i]+=b[i]*I;
	FFT(a,n,1);
	for(int i=0;i<n;++i) b[i]=conj(a[i?n-i:0]);
	complex<ld> p,q,t=complex<ld>(0.5,0);
	for(int i=0;i<n;++i){
		p=a[i];q=b[i];
		// complex<ld> t=p-q;
		a[i]=(p+q)*t;
		b[i]=(q-p)*t*I;
	}
}
inline ll num(ld x)
{
	ld res=x;
	return res>0?(ll)(x+0.5)%P:(ll)(x-0.5)%P;
}
void init()
{
	cin>>n>>m>>P;
	M=sqrt(P)+1;
	int x;
	for(int i=0;i<=n;++i){
		x=getint()%P;
		a0[i]=x/M;
		b0[i]=x%M;
	}
	for(int i=0;i<=m;++i){
		x=getint()%P;
		a1[i]=x/M;
		b1[i]=x%M;
	}
	m+=n;
	for(n=1;n<=m;n<<=1);
	makerev(n);
	for(int i=0;i<n;++i){
		wn[i]=complex<ld>(cos(PI/n*i),sin(PI/n*i));
	}
	qDFT(a0,b0,m,n); //一次DFT把两个数组都进行了DFT
	qDFT(a1,b1,m,n);
	for(int i=0;i<=n;++i){
		p[i]=a0[i]*a1[i]+b0[i]*a1[i]*I;
		q[i]=a0[i]*b1[i]+b0[i]*b1[i]*I;
	}
	FFT(p,n,-1);FFT(q,n,-1);
	for(int i=0;i<=m;++i){
		ans[i]=num(p[i].real())*M*M%P+(num(p[i].imag())+num(q[i].real()))*M%P+num(q[i].imag())%P;
		ans[i]=(ans[i]%P+P)%P;
	}
	for(int i=0;i<=m;++i) cout<<ans[i]<<" ";cout<<endl;
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