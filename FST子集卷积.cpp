#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
#define maxN (1<<20)+5
#define maxM 4005
#define mod 1000000009
#define eps 1e-10
using namespace std;
int a[22][maxN],b[22][maxN],h[22][maxN];
int lim,n;

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
inline void g(int &x) { x=(x%mod+mod)%mod; }
inline int sz(int i) { return __builtin_popcount(i); }
void OR(int *f,int n,int x)
{
    for(int len=2,k=1;len<=n;len<<=1,k<<=1){
        for(int st=0;st<n;st+=len){
            for(int j=0;j<k;++j){
                f[st+j+k]+=f[st+j]*x;g(f[st+j+k]);
            }
        }
    }
}

void init()
{
    lim=getint();n=1<<lim;
    for(int i=0;i<n;++i) a[sz(i)][i]=getint();
    for(int i=0;i<n;++i) b[sz(i)][i]=getint();
    for(int i=0;i<=lim;++i){
        OR(a[i],n,1);OR(b[i],n,1);
    }
    for(int i=0;i<=lim;++i){
        for(int j=0;j<=i;++j){
            for(int k=0;k<n;++k){
                h[i][k]=(h[i][k]+((ll)a[j][k]*b[i-j][k])%mod)%mod;
            }
        }
    }
    for(int i=0;i<=lim;++i) OR(h[i],n,-1);
    for(int i=0;i<n;++i) cout<<h[sz(i)][i]<<" ";cout<<endl;
}
void solve()
{
    
}
int main()
{
	cin.tie(0);
	init();
	solve();
}