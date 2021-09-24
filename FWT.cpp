#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
#define maxN 1<<17+5
#define maxM 4005
#define mod 998244353
#define eps 1e-10
using namespace std;
ll A[maxN],B[maxN],a[maxN],b[maxN],n;

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
inline void g(ll &x)
{
    x=(x%mod+mod)%mod;
}
void exgcd(ll a,ll b,ll &d,ll &x,ll &y)
{
    if(!b){
        d=a;x=1;y=0;
        return;
    }
    exgcd(b,a%b,d,x,y);
    ll t=x;x=y;y=t-(a/b)*x;
}
int inverse(ll a)
{
    ll d,x,y;
    exgcd(a,mod,d,x,y);
    return (x%mod+mod)%mod;
}
void in()
{
    for(int i=0;i<n;++i) a[i]=A[i],b[i]=B[i];
}
void get()
{
    for(int i=0;i<n;++i) a[i]=a[i]*b[i]%mod;
}
void pr()
{
    for(int i=0;i<n;++i) cout<<a[i]<<" ";cout<<endl;
}
void OR(ll *f,int x)
{
    for(int len=2,k=1;len<=n;len<<=1,k<<=1){
        for(int st=0;st<n;st+=len){
            for(int j=0;j<k;++j){
                f[st+j+k]+=f[st+j]*x;g(f[st+j+k]);
            }
        }
    }
}
void AND(ll *f,int x)
{
    for(int len=2,k=1;len<=n;len<<=1,k<<=1){
        for(int st=0;st<n;st+=len){
            for(int j=0;j<k;++j){
                f[st+j]+=f[st+j+k]*x;g(f[st+j]);
            }
        }
    }
}
void XOR(ll *f,int x)
{
    for(int len=2,k=1;len<=n;len<<=1,k<<=1){
        for(int st=0;st<n;st+=len){
            for(int j=0;j<k;++j){
                f[st+j]+=f[st+j+k];g(f[st+j]);
                f[st+j+k]=f[st+j]-2*f[st+j+k];g(f[st+j+k]);
                f[st+j]=f[st+j]*x;g(f[st+j]);
                f[st+j+k]=f[st+j+k]*x;g(f[st+j+k]);
            }
        }
    }
}
void try_or()
{
    in();
    OR(a,1);OR(b,1);get();OR(a,mod-1);
    pr();
}
void try_and()
{
    in();
    AND(a,1);AND(b,1);get();AND(a,mod-1);
    pr();
}
void try_xor()
{
    in();
    XOR(a,1);XOR(b,1);get();XOR(a,inverse(2));
    pr();
}
void init()
{
    n=getint();n=1<<n;
    for(int i=0;i<n;++i) A[i]=getint();
    for(int i=0;i<n;++i) B[i]=getint();
}
void solve()
{
    try_or();
    try_and();
    try_xor();
}
int main()
{
	cin.tie(0);
	init();
	solve();
}
