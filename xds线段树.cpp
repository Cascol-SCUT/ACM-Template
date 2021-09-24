#include <iostream>
#include <algorithm>
#include <iomanip>
#include <queue>
#include<string>
#include<string.h>
#include <vector>
#include <cstdio>
#include<map>
#include<cmath>
#define maxN 1000010
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
int n, m, p;
ll sum[maxN], addSum[maxN], mul[maxN];
vector<int> a;
ll query(int, int, int, int, int);
inline int getint() {
	int num = 0, bj = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == EOF)
			return EOF;
		bj = (c == '-' || bj == -1) ? -1 : 1; c = getchar();
	}
	while (c >= '0' && c <= '9') num = num * 10 + c - '0', c = getchar();
	return num * bj;
}
void pushdown(int k, int l, int r)
{
	if (addSum[k] == 0 && mul[k] == 1)return;
	int mid = l + r >> 1;
	sum[k * 2] = (sum[k * 2] * mul[k] + addSum[k] * (mid - l + 1)) % p;
	sum[k * 2 + 1] = (sum[k * 2 + 1] * mul[k] + addSum[k] * (r - mid)) % p;
	addSum[k * 2] = (addSum[k * 2] * mul[k] + addSum[k]) % p;
	addSum[k * 2 + 1] = (addSum[k * 2 + 1] * mul[k] + addSum[k]) % p;
	mul[k * 2] = (mul[k * 2] * mul[k]) % p;
	mul[k * 2 + 1] = (mul[k * 2 + 1] *mul[k]) % p;
	addSum[k] = 0;
	mul[k] = 1;
}
void build(int k,int l,int r)
{
	mul[k] = 1;
	if (l == r) {
		sum[k] = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(k * 2, l, mid);
	build(k * 2 + 1, mid + 1, r);
	sum[k] = sum[k * 2] + sum[k * 2 + 1];
}
void add(int k, int l, int r, int x, int y,int v)
{
	if (x <= l && r <= y) {
		addSum[k] = (addSum[k] + v) % p;
		sum[k] = (sum[k] + (r - l + 1)*v) % p;
		return;
	}
	int mid = l + r >> 1;
	pushdown(k, l, r);
	if (mid >= x) add(k * 2, l, mid, x, y, v);
	if (mid + 1 <= y) add(k * 2 + 1, mid + 1, r, x, y, v);
	sum[k] = sum[k * 2] + sum[k * 2 + 1];
}
void time(int k, int l, int r, int x, int y,int v)
{
	if (x <= l && r <= y) {
		sum[k] = (sum[k] * v) % p;
		addSum[k] = (addSum[k] * v) % p;
		mul[k] = (mul[k] * v) % p;
		return;
	}
	int mid = l + r >> 1;
	pushdown(k, l, r);
	if (mid >= x) time(k * 2, l, mid, x, y, v);
	if (mid + 1 <= y) time(k * 2 + 1, mid + 1, r, x, y, v);
	sum[k] = sum[k * 2] + sum[k * 2 + 1];
}
ll query(int k, int l, int r, int x, int y)
{
	if (x <= l && r <= y) return sum[k];
	int mid = l + r >> 1;
	pushdown(k, l, r);
	ll res = 0;
	if (mid >= x) res = (res + query(k * 2, l, mid, x, y)) % p;
	if (mid + 1 <= y) res = (res + query(k * 2 + 1, mid + 1, r, x, y)) % p;
	return res;
}
void init()
{
	n = getint(); m = getint(); p = getint();
	a.push_back(0);
	for (int i = 0; i < n; ++i) a.push_back(getint());
	build(1, 1, n);
	//cout << query(1, 1, n, 1, n) << endl;
}
void pr() {
	for (int i = 1; i <= n; ++i) {
		cout << query(1, 1, n, i, i) << " ";
	}
}
void solve()
{
	int x, y, k;
	for (int i = 0; i < m; ++i)
	{
		int ch = getint();
		if (ch == 1)
		{
			x = getint(); y = getint(); k = getint();
			time(1, 1, n, x, y, k);
			//cout << "´ð°¸:"; pr();cout << endl;
			//query(1, 1, n, 2, 2,0);
		}
		else if (ch == 2)
		{
			x = getint(); y = getint(); k = getint();
			add(1, 1, n, x, y, k);
			//cout << "´ð°¸:"; pr();cout << endl;
		}
		else {
			x = getint(); y = getint();
			cout << query(1, 1, n, x, y) << endl;
		}
	}
}
int main()
{
	//freopen("reflection.in","r", stdin);
	init();
	solve();
	system("pause");
}