#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
#define maxN 1000005
#define maxM 4005
#define mod 1000000007
#define eps 1e-10
using namespace std;
int nxt[maxN][22],n,dep[maxN],m,x,y;
char s[maxN];
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
void KMP()
{
	nxt[0][0]=nxt[1][0]=0;
	dep[0]=0;dep[1]=1;
	n=strlen(s+1);
	int j=0;
	for(int i=2;i<=n;++i){
		while(j && s[i]!=s[j+1]) j=nxt[j][0];
		if(s[i]==s[j+1]) ++j;
		nxt[i][0]=j;dep[i]=dep[j]+1;
	}
	// for(int i=1;i<=n;++i) cout<<nxt[i][0]<<" "<<s[i]<<endl;;cout<<endl;
}
void init()
{
	cin>>s+1;
	KMP();
	for(int i=1;i<=n;++i){
		for(int j=1;j<22;++j)
			nxt[i][j]=nxt[nxt[i][j-1]][j-1];
	}
}
void solve()
{
	m=getint();
	for(int i=1;i<=m;++i){
		x=getint();y=getint();
		if(dep[x]<dep[y]) swap(x,y);
		for(int i=21;i>=0;--i){
			if(dep[nxt[x][i]]>=dep[y]) x=nxt[x][i];
		}
		for(int i=21;i>=0;--i){
			if(nxt[x][i]!=nxt[y][i]){
				x=nxt[x][i];y=nxt[y][i];
			}
		}
		cout<<nxt[x][0]<<endl;
	}
}
int main()
{
	cin.tie(0);
	init();
	solve();
	//system("pause");
}