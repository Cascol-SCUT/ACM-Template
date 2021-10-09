#include<bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
#define maxN 20005
#define maxK 10005
#define mod 1000000007
#define INF 1000000009
using namespace std;
int ch[maxN][26], cnt[maxN], fail[maxN],nxt[maxN];
bool ed[maxN];
vector<int> fi;
unordered_map<int, string> mp;
string s;
int n, tot;

inline void clear(int v)
{
	for(int i=0;i<26;++i) ch[v][i]=0;
	cnt[v]=fail[v]=nxt[v]=0;
}
void insert(string x)
{
	int p = 0;
	for (int i = 0; i < x.length(); ++i)
	{
		int t = x[i] - 'a';
		if (ch[p][t]) p = ch[p][t];
		else {
			ch[p][t] = ++tot;
			p = tot;clear(tot);
		}
	}
	//cout << "p: " << p << endl;
	ed[p] = true; fi.push_back(p);
	mp[p] = x;
}
void buildfail()
{
	queue<int> q;
	for (int i = 0; i < 26; ++i)
		if (ch[0][i]) {
			fail[ch[0][i]] = 0;
			q.push(ch[0][i]);
		}
	while (!q.empty())
	{
		int u = q.front(); q.pop();
		for (int i = 0; i < 26; ++i) {
			if (ch[u][i]) {
				fail[ch[u][i]] = ch[fail[u]][i];
				nxt[ch[u][i]]=ed[fail[ch[u][i]]]?fail[ch[u][i]]:nxt[fail[ch[u][i]]];
				q.push(ch[u][i]);
			}
			else
				ch[u][i] = ch[fail[u]][i];
		}
	}
}
void find(string s)
{
	int p = 0, ans = 0;
	for (int i = 0; i < s.length(); ++i) {
		int t = s[i] - 'a';
		p = ch[p][t];
		for (int cur = p; cur; cur = nxt[cur]) {
			if (ed[cur]) cnt[cur]++;
		}
	}
}
void init()
{
    // memset(fail,0,sizeof(fail));
    // memset(nxt,0,sizeof(nxt));
	// memset(cnt, 0, sizeof(cnt));
	// memset(ch, 0, sizeof(ch));
	// memset(ed, 0, sizeof(ed));
	clear(0);
	fi.clear();
	tot = 0;
}
void solve()
{
	while (cin >> n && n != 0) {
		init();
		for (int i = 1; i <= n; ++i) {
			cin >> s;
			insert(s);
		}
		buildfail();
		cin >> s;
		find(s);
		string ans = "";
		int nt = -1, id = -1;
		for (int i = 0; i < fi.size(); ++i) {
			if (cnt[fi[i]] > nt) {
				nt = cnt[fi[i]];
				ans = mp[fi[i]];
				id = i;
			}
		}
		cout << nt << endl << ans << endl;
		for (int i = id + 1; i < fi.size(); ++i) {
			if (cnt[fi[i]] == nt) {
				cout << mp[fi[i]] << endl;
			}
		}
	}
}
int main()
{
	//freopen("reflection.in","r", stdin);
	solve();
	system("pause");
}