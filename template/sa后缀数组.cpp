#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
#define maxN 1000005
#define maxM 4005
#define mod 1000000007
#define eps 1e-10
using namespace std;
int rk[maxN],sa[maxN],tmp[maxN],n,k;
string s;
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
bool compare_sa(int i,int j)
{
	if(rk[i]!=rk[j]) return rk[i]<rk[j];
	else{
		int ri=(i+k<=n?rk[i+k]:-1);
		int rj=(j+k<=n?rk[j+k]:-1);
		return ri<rj;
	}
}
void pr()
{
	for(int i=0;i<=n;++i) cout<<s.substr(sa[i],k)<<" ";cout<<endl;
}
void init()
{
	cin>>s;
	n=s.length();
	for(int i=0;i<=n;++i){
		rk[i]=s[i];
		sa[i]=i;
	}
	rk[n]=-1;sa[n]=n;
	for(k=1;k<=n;k<<=1){
		sort(sa,sa+n+1,compare_sa);
		// pr();
		tmp[sa[0]]=0;
		for(int i=1;i<=n;++i){
			tmp[sa[i]]=tmp[sa[i-1]]+(compare_sa(sa[i-1],sa[i])?1:0);
		}
		for(int i=0;i<=n;++i) rk[i]=tmp[i];
	}

}
void solve()
{
	for(int i=1;i<=n;++i) cout<<sa[i]+1<<" ";cout<<endl;
}
int main()
{
	cin.tie(0);
	init();
	solve();
	//system("pause");
}