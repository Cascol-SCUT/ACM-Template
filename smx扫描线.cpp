#include <iostream>
#include <algorithm>
#include <iomanip>
#include <queue>
#include<string>
#include <vector>
#include <cstdio>
#include<map>
#include<cmath>
#include<set>
#define mod 100
#define maxN 1000005
#define INF 1000000000
typedef long long ll;
using namespace std;
struct EDGE {
	int x1, x2, y, v;
	bool operator<(const EDGE e) const {
		return y < e.y;
	}
}edge[maxN];
int tot = 0, n, X[2*maxN], cnt[4 * maxN], sum[4 * maxN], change[4 * maxN];
vector<int> x;
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
int find(int k)
{
	int l = 0, r = x.size() - 1;
	while (l <= r)
	{
		int mid = l + r >> 1;
		if (x[mid] == k) return mid;
		else if (x[mid] > k) r = mid - 1;
		else l = mid + 1;
	}
	return -1;
}
void pushup(int k, int l, int r)
{
	if (cnt[k] > 0) sum[k] = x[r+1] - x[l];
	else if (l == r) sum[k] = 0;
	else sum[k] = sum[k * 2] + sum[k * 2 + 1];
}
void modify(int k, int l, int r, int x, int y, int v)
{
	if (l >= x && r <= y)
	{
		cnt[k] += v;
		pushup(k, l, r);
		return;
	}
	//pushdown(k, l, r);
	int mid = l + r >> 1;
	if (mid >= x) modify(k * 2 , l, mid, x, y, v);
	if (mid + 1 <= y) modify(k * 2 + 1, mid + 1, r, x, y, v);
	pushup(k,l,r);
}
ll query(int k, int l, int r, int x, int y)
{
	if (l >= x && r <= y)
	{
		return sum[k];
	}
	int mid = l + r >> 1;
	ll res = 0;
	if (mid >= x) res+=query(k * 2, l, mid, x, y);
	if (mid + 1 <= y) res+=query(k * 2 + 1, mid + 1, r, x, y);
	return res;
}
void init()
{
	
}
void solve()
{
	n = getint();
	int x1, y1, x2, y2;
	for(int i=1;i<=n;++i)
	{
		x1 = getint(); y1 = getint(); x2 = getint(); y2 = getint();
		X[tot] = x1;
		edge[tot++] = { x1,x2,y1,1 };
		X[tot] = x2;
		edge[tot++] = { x1,x2,y2,-1 };
	}
	sort(edge, edge + tot);
	sort(X, X + tot);
	X[tot] = -1;
	for (int i = 0; i < tot; ++i) {
		if (X[i] != X[i + 1])x.push_back(X[i]);
	}
	ll ans = 0;
	for (int i = 0; i < tot-1; ++i) {
		int l = find(edge[i].x1), r = find(edge[i].x2) - 1;
		modify(1, 0, x.size() - 2, l, r, edge[i].v);
		ans += (edge[i + 1].y - edge[i].y)*(query(1, 0, x.size() - 2, 0, x.size() - 2));
	}
	cout << ans << endl;
	//for (int i = 0; i < tot; ++i) {
	//	cout << edge[i].y << " " << edge[i].x1 << " " << edge[i].x2 << endl;
	//}

}
int main() {
	//cin.tie(0);
	init();
	solve();
}