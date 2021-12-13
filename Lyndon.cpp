#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
#define maxN 100005
#define maxM 4005
#define mod 1000000007
#define eps 1e-10
using namespace std;
string s;
void init()
{
	cin>>s;
}
void Lyndon()
{
	int i=0,j,k;
	int ans=0;
	while(i<s.length())
	{
		j=i;k=i+1;
		while(k<=s.length()&&s[k]>=s[j])
		{
			if(s[k]>s[j]) j=i;
			else ++j;
			++k;
		}
		while(i<=j)
		{
			i=i+k-j;
			ans^=i; //分割点
		}
	}
	cout<<ans<<endl;
}
int main()
{
	cin.tie(0);
	init();
	solve();
	//system("pause");
}