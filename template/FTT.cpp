#include<bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define maxN 4200005
#define mod 1000000007
#define INF 0x3f3f3f3f
#define eps 1e-10
using namespace std;
const double PI = acos(-1);
complex<ld> f[maxN],g[maxN],wn[maxN];
// ll f[maxN],g[maxN];
int n,m,tax[maxN];
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
void init()
{
	cin>>n>>m;
	for(int i=0;i<=n;++i) f[i].real(getint());
	for(int i=0;i<=m;++i) f[i].imag(getint());
	// for(int i=0;i<=n;++i) f[i]=getint();
	// for(int i=0;i<=m;++i) g[i]=getint();
	m+=n;
	for(n=1;n<=m;n<<=1);
	makerev(n);
	for(int i=0;i<n;++i){
		wn[i]=complex<ld>(cos(PI/n*i),sin(PI/n*i));
	}
    FFT(f,n,1);
	for(int i=0;i<=n;++i) f[i]=f[i]*f[i];
	FFT(f,n,-1);
    for(int i=0;i<=m;++i){
		cout<<int(fabsl(f[i].imag()))<<" ";
		// cout<<int(fabsl(f[i].imag()/(2*n))+0.5)<<" ";
	}
	cout<<endl;
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