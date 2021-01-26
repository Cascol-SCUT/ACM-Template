#include <iostream>
#include <algorithm>
#include <iomanip>
#include <queue>
#include<string>
#include <vector>
#include <cstdio>
#include<map>
#include<cmath>
#include<cstring>
#include<set>
#define mod 1000000007
#define maxN 605
#define maxM 6005
#define INF 1000000000
typedef long long ll;
using namespace std;
int n, m, f[maxN][maxN], dis[maxN], s, t,nxt[maxN];
bool vis[maxN],bin[maxN];
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
int step()
{
	memset(vis, 0, sizeof(vis));
	memset(dis, 0, sizeof(dis));
	int ans = 0;
	for (int i = 1; i <= n; ++i)
	{
		int maxC = -1, np = -1, p = 0;
		for (int j = 1; j <= n; j=nxt[j]) {
			if (!bin[j] && !vis[j]) {
				nxt[p] = j;
				p = j;
				if (dis[j] > maxC) {
					maxC = dis[j];
					np = j;
				}
			}
		}
		if (np == -1) return ans;
		ans = maxC;
		s = t; t = np;
		vis[t] = true;
		p = 0;
		for (int j = 1; j <= n; j=nxt[j]) {
			if (!bin[j] && !vis[j]) {
				nxt[p] = j; p = j;
				dis[j] += f[t][j];
			}
		}
	}
	return ans;
}
void init()
{
	n = getint(); m = getint();
	int u, v, w;
	for (int i = 1; i <= m; ++i)
	{
		u = getint(); v = getint(); w = getint();
		f[u][v] += w; f[v][u] += w;
	}
	for (int i = 1; i <= n; ++i) {
		nxt[i] = i + 1;
	}
}
void solve()
{
	int ans = INF;
	for (int i = 1; i < n; ++i)
	{
		ans = min(ans, step());
		if (!ans) {
			cout << "0\n"; return;
		}
		bin[t] = 1;
		int p = 0;
		for (int j = 1; j <= n; ++j) {
			if (!bin[j]) {
				nxt[p] = j;p = j;
				f[s][j] += f[t][j];
				f[j][s] += f[j][t];
			}
		}
	}
	cout << ans << endl;
}
int main() {
	//freopen("D://ans.txt", "w+", stdout);
	cin.tie(0);
	init();
	solve();
	//system("pause");
}