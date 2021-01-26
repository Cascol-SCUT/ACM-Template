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
typedef long long ll;
typedef unsigned long long ull;
#define maxN 1005
#define maxK 10005
#define mod 1000000007
#define INF 0x3f3f3f3f
#define eps 1e-10
using namespace std;
long double a,b,c,d,l,r;
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
long double f(long double x)
{
	return (c*x+d)/(a*x+b);
}
long double simpson(long double a,long double b)
{
	return (f(a)+f(b)+4*f((a+b)/2))/6*(b-a);
}
long double integral(long double l,long double r){
	long double mid=(l+r)/2;
	if(fabsl(simpson(l,r)-(simpson(l,mid)+simpson(mid,r)))<eps){
		return simpson(l,r);
	}
	return integral(l,mid)+integral(mid,r);
}
void init()
{
	cin>>a>>b>>c>>d>>l>>r;
}
void solve()
{
	cout<<setprecision(6)<<fixed<<integral(l,r)<<endl;
}
int main()
{
	//freopen("reflection.in","r", stdin);
	init();
	solve();
}