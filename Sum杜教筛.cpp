#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define maxN 2000005
#define maxK 10000005
#define mod 1000000007
#define INF 0x3f3f3f3f
#define eps 1e-6
using namespace std;
ll phi[maxN];
int mu[maxN],vis[maxN];
vector<int>pri;
unordered_map<int,int> Sumu;
unordered_map<int,ull> Sump;
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
int getmu(int n) //
{
    if(n<maxN) return mu[n];
    if(Sumu[n]) return Sumu[n];
    int ret=1;
    for(ll l=2,r;l<=n;l=r+1)
    {
        r=n/(n/l);
        ret-=(r-l+1)*getmu(n/l);
    }
    return Sumu[n]=ret;
}
ll getphi(ll n)
{
    if(n<maxN) return phi[n];
    if(Sump[n]) return Sump[n];
    ull ret= (ull)n*(n+1ll)/2;
    for(ll l=2,r;l<=n;l=r+1)
    {
        r=n/(n/l);
        ret-=(r-l+1)*getphi(n/l);
    }
    return Sump[n]=ret;
}
void init()
{
    phi[1]=mu[1]=1;
    for(int i=2;i<maxN;++i)
    {
        if(!vis[i])
        {
            vis[i]=i;
            pri.push_back(i);
            phi[i]=i-1;mu[i]=-1;
        }
        int cnt=pri.size();
        for(int j=0;j<cnt && pri[j]*i<maxN && pri[j]<=vis[i];++j){
            vis[i*pri[j]]=i;
            if(i%pri[j]==0) {phi[i*pri[j]]=phi[i]*pri[j];break;}
            phi[i*pri[j]]=phi[i]*phi[pri[j]];
            mu[i*pri[j]]=-mu[i];
        }
    }
    for(int i=1;i<maxN;++i) mu[i]+=mu[i-1],phi[i]+=phi[i-1];
}
void solve()
{
    int T;cin>>T;
    while(T--)
    {
        ll n;cin>>n;
        cout<<getphi(n)<<" "<<getmu(n)<<endl;
    }
}
int main()
{
	// freopen("D:\\","w+",stdout);
    cin.tie(0);
	init();
	solve();
}