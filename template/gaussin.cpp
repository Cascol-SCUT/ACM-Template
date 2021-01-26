#include <iostream>
#include <algorithm>
#include <iomanip>
#include <queue>
#include<string>
#include<complex>
#include<string.h>
#include <vector>
#include <cstdio>
#include<map>
#include<cmath>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define maxN 1005
#define mod 1000000007
#define INF 0x3f3f3f3f
#define eps 1e-6
using namespace std;
long double mt[maxN][maxN];
int n;
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

void init()
{

}
void solve()
{
	n = getint();
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n+1; ++j)
			mt[i][j] = getint();
	}
	for (int i = 1; i <= n; ++i)
	{
		int pos = i;
		for (int j = i + 1; j <= n; ++j) if (mt[j][i] > mt[pos][i]) pos = j;
		if (pos != i) swap(mt[i], mt[pos]);
		if (fabsl(mt[i][i])<eps) {
			cout << "No Solution";
			return;
		}
		for (int j = n+1; j >= i; --j) {
			mt[i][j]/=mt[i][i];
		}
		for (int r = 1; r <= n; ++r)
		{
			if (r != i)
			{
				ld t = mt[r][i];
				for (int k = i; k <= n+1; ++k) {
					mt[r][k] -= (t * mt[i][k]);
				}
			}
		}
		// cout<<"--------------\n";
	}
	for(int i=1;i<=n;++i) cout<<setprecision(2)<<fixed<<mt[i][n+1]<<endl;
}
int main()
{
	//freopen("reflection.in","r", stdin);
	init();
	solve();
}