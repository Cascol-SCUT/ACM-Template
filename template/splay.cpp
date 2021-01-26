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
#define maxN 100005
#define INF 1000000000
typedef long long ll;
using namespace std;
int n, root, sz, f[maxN], son[maxN][2], siz[maxN], cnt[maxN], key[maxN];
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
void pr(int x) {
	cout << "x: " << x <<" father: "<<f[x] <<" leftChild: " << son[x][0] << " rightChild: " << son[x][1] << " value: " << key[x] << endl;
}
void clear(int x)
{
	son[x][0] = son[x][1] = f[x] = cnt[x] = key[x] = siz[x] = 0;
}
void update(int x)
{
	if (x) {
		siz[x] = cnt[x];
		if (son[x][0]) siz[x] += siz[son[x][0]];
		if (son[x][1]) siz[x] += siz[son[x][1]];
	}
}
bool get(int x)
{
	return son[f[x]][1] == x;
}
inline void rotate(int x) {
	int old = f[x], oldf = f[old], which = get(x);
	son[old][which] = son[x][which ^ 1];
	if(son[old][which]) f[son[old][which]] = old;
	f[old] = x; son[x][which ^ 1] = old;
	f[x] = oldf;
	if (oldf)
		son[oldf][son[oldf][1] == old] = x;
	update(old); update(x);
}
void splay(int x)
{
	//cout << "root:" << root << endl;
	//for (int i = 0; i <= sz; ++i) {
	//	pr(i);
	//}
	for (int fa; (fa=f[x]); rotate(x)){
		if (f[fa])
			rotate(get(x) == get(fa) ? fa : x);
	}
	root = x;
	//cout << "root:" << root << endl;
	//for (int i = 0; i <= sz; ++i) {
	//	pr(i);
	//}
}
void insert(int v)
{
	if (!root) {
		++sz;
		son[sz][0] = son[sz][1] = f[sz] = 0;
		key[sz] = v; cnt[sz] = 1; siz[sz] = 1;
		root = sz;
		return;
	}
	int now = root, fa = 0;
	while (true) {
		if (key[now] == v) {
			cnt[now]++; update(now); update(fa);
			splay(now); break;
		}
		fa = now;
		now = son[now][key[now] < v];
		if (!now) {
			sz++;
			son[sz][0] = son[sz][1] = 0; key[sz] = v;
			siz[sz] = 1;cnt[sz] = 1;
			f[sz] = fa; son[fa][key[fa] < v] = sz;
			update(fa); splay(sz);
			break;
		}
	}
}
int find(int v) //找值为v的排名
{
	int ans = 0, now = root;
	while (now) {
		if (v < key[now]) {
			now = son[now][0];
		}
		else {
			ans += (son[now][0] ? siz[son[now][0]] : 0);
			if (v == key[now]) {
				splay(now);
				return ans + 1;
			}
			ans += cnt[now];
			now = son[now][1];
		}
	}
}
int findx(int x) //找排名为v的值
{
	int now = root;
	while (now)
	{
		if (son[now][0] && x <= siz[son[now][0]]) {
			now = son[now][0];
		}
		else {
			int temp = (son[now][0] ? siz[son[now][0]] : 0) + cnt[now];
			if (x <= temp) return key[now];
			x -= temp; now = son[now][1];
		}
	}
	return -1;
}
int pre() //寻找x的前驱
{
	int now = son[root][0];
	while (son[now][1]) now = son[now][1];
	return now;
}
int next()
{
	int now = son[root][1];
	while (son[now][0]) now = son[now][0];
	return now;
}
void del(int x) // 删除x
{
	find(x);
	if (cnt[root] > 1) {
		cnt[root]--; update(root);
		return;
	}
	if (!son[root][0] && !son[root][1]) {
		clear(root); root = 0;
		return;
	}
	if (!son[root][0]) {
		int oldr = root;
		root = son[root][1]; f[root] = 0;
		clear(oldr);
		return;
	}
	else if (!son[root][1]) {
		int oldr = root;
		root = son[root][0]; f[root] = 0;
		clear(oldr);
		return;
	}
	// 两个孩子
	int lb = pre(), oldr = root;
	splay(lb);
	f[son[oldr][1]] = root;
	son[root][1] = son[oldr][1];
	clear(oldr);
	update(root);
	return;
}
void init()
{
	
}
void solve()
{
	n = getint();
	int opt, x;
	while (n--)
	{
		opt = getint(); x = getint();
		switch (opt)
		{
		case 1: {
			insert(x); break;
		}
		case 2: {
			del(x); break;
		}
		case 3: {
			cout <<find(x) << endl; break;
		}
		case 4: {
			cout <<findx(x) << endl; break;
		}
		case 5: {
			insert(x);
			cout <<key[pre()] << endl;
			del(x);
			break;
		}
		case 6: {
			insert(x);
			cout <<key[next()] << endl;
			del(x);
			break;
		}
		}
	}
}
int main() {
	//freopen("D://ans.txt", "w+", stdout);
	cin.tie(0);
	init();
	solve();
	system("pause");
}