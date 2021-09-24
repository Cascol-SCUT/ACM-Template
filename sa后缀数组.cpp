#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
#define maxN 1000005
#define maxM 4005
#define mod 1000000007
#define eps 1e-10
using namespace std;
int rk[maxN],sa[maxN],lcp[maxN],tmp[maxN],n,k;
string s;
bool compare_sa(int i,int j)
{
	if(rk[i]!=rk[j]) return rk[i]<rk[j];
	else{
		int ri=(i+k<=n?rk[i+k]:-1);
		int rj=(j+k<=n?rk[j+k]:-1);
		return ri<rj;
	}
}
void construct_sa(string s,int *sa)
{
	n=s.length();
	for(int i=0;i<=n;++i){
		rk[i]=s[i];
		sa[i]=i;
	}
	rk[n]=-1;sa[n]=n;
	for(k=1;k<=n;k<<=1){
		sort(sa,sa+n+1,compare_sa);
		tmp[sa[0]]=0;
		for(int i=1;i<=n;++i){
			tmp[sa[i]]=tmp[sa[i-1]]+(compare_sa(sa[i-1],sa[i])?1:0);
		}
		for(int i=0;i<=n;++i) rk[i]=tmp[i];
	}
}
void construct_lcp(string s,int *sa,int *lcp)
{
	int n=s.length();
	int h=0;
	lcp[0]=0;
	for(int i=0;i<n;++i){
		int j=sa[rk[i]-1];
		if(h>0) --h;
		while(i+h<n&&j+h<n&&s[i+h]==s[j+h]) ++h;
		lcp[rk[i]-1]=h; 
	}
}
int main()
{
	cin>>s;
	construct_sa(s,sa);
	construct_lcp(s,sa,lcp);
	int n=s.length();
	for(int i=0;i<=n;++i) cout<<sa[i]<<" \n"[i==n];
	for(int i=0;i<=n;++i) cout<<lcp[i]<<" \n"[i==n];
	for(int i=0;i<=n;++i) cout<<rk[i]<<" \n"[i==n];
}