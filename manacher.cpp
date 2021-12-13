#include<bits/stdc++.h>
#define maxN 30000005
using namespace std;
struct Manacher{
	int p[maxN]; string s;
	void init(string k)
	{
		s.resize(k.size() * 2 + 3);
		s[0] = '&'; s[1] = '#';
		int cnt = 1;
		for (int i = 0; i < k.size(); ++i) {
			s[cnt * 2] = k[i];
			s[cnt * 2 + 1] = '#';
			++cnt;
		}
		s[cnt*2]='$';
	}
	int manacher()
	{
		int index = 1, r = 0, ans=-1;
		for (int i = 1; i < s.size(); ++i) {
			p[i] = min(p[2 * index - i], r - i + 1);
			while (s[i + p[i]] == s[i - p[i]]) ++p[i];
			if (i+p[i]-1 > r) {
				r = p[i] + i - 1;
				index = i;
			}
			ans = max(ans, p[i]);
		}
		return ans-1;
	}
}mac;
int main() {
	//cin.tie(0);
	string s;cin>> s;
	mac.init(s);
	cout<<mac.manacher()<<"\n";
}