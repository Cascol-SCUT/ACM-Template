#include<bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
#define maxN 20005
#define maxK 10005
#define mod 1000000007
#define INF 1000000009
using namespace std;
unordered_map<int, string> mp;
string s;
int n;
struct ACTrie{
	int tot;
	int ch[maxN][26], cnt[maxN], fail[maxN],nxt[maxN];
	bool ed[maxN];
	vector<int> fi;
	inline void clear(int v)
	{
		for(int i=0;i<26;++i) ch[v][i]=0;
		cnt[v]=fail[v]=nxt[v]=0;
	}
	void insert(string x){
		int p = 0;
		for (int i = 0; i < x.length(); ++i){
			int t = x[i] - 'a';
			if(!ch[p][t]) ch[p][t]=++tot,clear(tot);
			p = ch[p][t];
		}
		ed[p] = true; fi.push_back(p);
		mp[p] = x;
	}
	void buildfail(){ //找到最长匹配的后缀
		queue<int> q;
		for (int i = 0; i < 26; ++i)
			if (ch[0][i]) {
				fail[ch[0][i]] = 0;
				q.push(ch[0][i]);
			}
		while (!q.empty()){
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
	void find(string s){
		int p = 0, ans = 0;
		for (int i = 0; i < s.length(); ++i) {
			int t = s[i] - 'a';
			p = ch[p][t];
			for (int cur = p; cur; cur = nxt[cur]) {
				if (ed[cur]) cnt[cur]++;
			}
		}
	}
	void init(){
		clear(0); fi.clear(); tot = 0;
	}
}ac;
void solve()
{
	while (cin >> n && n != 0) {
		ac.init();
		for (int i = 1; i <= n; ++i) {
			cin >> s;
			ac.insert(s);
		}
		ac.buildfail();
		cin >> s;
		ac.find(s);
		string ans = "";
		int nt = -1, id = -1;
		for (int i = 0; i < ac.fi.size(); ++i) {
			if (ac.cnt[ac.fi[i]] > nt) {
				nt = ac.cnt[ac.fi[i]];
				ans = mp[ac.fi[i]];
				id = i;
			}
		}
		cout << nt << endl << ans << endl;
		for (int i = id + 1; i < ac.fi.size(); ++i) {
			if (ac.cnt[ac.fi[i]] == nt) {
				cout << mp[ac.fi[i]] << endl;
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