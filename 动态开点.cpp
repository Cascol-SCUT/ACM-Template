#include<iostream>
#include<algorithm>
#include<cstring>
#define maxN 3000005
#define N 1000000
#define INF 1000000000
using namespace std;
struct node{
	int l,r,v;
}tr[maxN];
int rt[55],tot;
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
void add(int x,int v,int &k,int l=1,int r=N) //每个y值
{
	if(!k) tr[k=++tot]=node{0,0,v};
	if(tr[k].v>v) tr[k].v=v;
	if(l==r) return;
	int mid=l+r>>1;
	if(x<=mid) add(x,v,tr[k].l,l,mid);
	if(x>=mid+1) add(x,v,tr[k].r,mid+1,r);
}
bool fd;
void query(int x1,int x2,int k,int v,int l=1,int r=N)
{
	if(!k||fd) return;
	if(x1<=l&&r<=x2){
		fd=tr[k].v<=v;
		return;
	}
	int mid=l+r>>1;
	if(x1<=mid) query(x1,x2,tr[k].l,v,l,mid);
	if(fd) return;
	if(x2>=mid+1) query(x1,x2,tr[k].r,v,mid+1,r);
	return;
}
void init()
{
	memset(rt,0,sizeof(rt));
	tot=0;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int x;
	while(true)
	{
		switch(getint()){
			case 0:{
				init();
				break;
			}
			case 1:{
				int x,y,c;
				x=getint();y=getint();c=getint();
				add(y,x,rt[c]);
				break;
			}
			case 2:{
				int x,y1,y2;
				x=getint();y1=getint();y2=getint();
				int cnt=0;
				for(int i=0;i<=50;++i){
					fd=false;
					query(y1,y2,rt[i],x);
					if(fd) cnt++;
				}
				cout<<cnt<<"\n";
				break;
			}
			case 3:{
				return 0;
			}
		}
	}
}