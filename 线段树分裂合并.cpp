#include<bits/stdc++.h>
#define maxN 200005
#define N 1000000
#define INF 1000000000
typedef long long ll;
using namespace std;
struct node{
	int l,r;
	ll v;
}tr[400005<<5];
int rt[maxN],tot,totr;
int n,m;
int a[maxN];
vector<int> bac;
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
void pushup(int x)
{
	tr[x].v=tr[tr[x].l].v+tr[tr[x].r].v;
}
void del(int x)
{
	tr[x].l=tr[x].r=tr[x].v=0;
	bac.push_back(x);
}
int newnode()
{
	int res;
	if(bac.size()){
		res=bac.back();bac.pop_back();
	}
	else res=++tot;
	return res;
}
int kth(int x,int l,int r,ll k)
{
	if(!x) return -1;
	if(l==r) return l;
	int mid=l+r>>1;
	if(tr[tr[x].l].v>=k) return kth(tr[x].l,l,mid,k);
	return kth(tr[x].r,mid+1,r,k-tr[tr[x].l].v);
}
void build(int l,int r,int &k)
{
	if(!k) tr[k=++tot]=node{0,0,0};
	if(l==r)
	{
		tr[k].v=a[l];
		return;
	}
	int mid=l+r>>1;
	build(l,mid,tr[k].l);
	build(mid+1,r,tr[k].r);
	tr[k].v=tr[tr[k].l].v+tr[tr[k].r].v;
}
int merge(int x,int y)
{
	if(!x||!y) return x+y;
	tr[x].v+=tr[y].v;
	tr[x].l=merge(tr[x].l,tr[y].l);
	tr[x].r=merge(tr[x].r,tr[y].r);
	del(y);
	return x;
}
void add(int x,int v,int &k,int l,int r) //每个y值
{
	if(!k) tr[k=newnode()]=node{0,0,0};
	tr[k].v+=v;
	if(l==r) return;
	int mid=l+r>>1;
	if(x<=mid) add(x,v,tr[k].l,l,mid);
	if(x>=mid+1) add(x,v,tr[k].r,mid+1,r);
}
void split(int pl,int pr,int &x,int &y,int l,int r)
{
	if(pl==l&&pr==r){
		swap(x,y);return;
	}
	if(!y) y=newnode();
	int mid=l+r>>1;
	if(pr<=mid) split(pl,pr,tr[x].l,tr[y].l,l,mid);
	else if(pl>mid) split(pl,pr,tr[x].r,tr[y].r,mid+1,r);
	else split(pl,mid,tr[x].l,tr[y].l,l,mid),split(mid+1,pr,tr[x].r,tr[y].r,mid+1,r);
	pushup(x);
	pushup(y);
}
void split(int x,int &y,ll k)
{
	if(!x) return;
	if(!y) y=newnode();
	ll v=tr[tr[x].l].v;
	if(v<k){
		split(tr[x].r,tr[y].r,k-v);
	}
	else{
		swap(tr[y].r,tr[x].r);
		if(k<v)split(tr[x].l,tr[y].l,k);	
	}
	tr[y].v=tr[x].v-k;
	tr[x].v=k;
}
bool fd;
ll query(int x,int y,int k,int l,int r) //查询大于等于x 小于等于y的个数
{
	if(!k||x>r||y<l) return 0;
	if(x<=l&&r<=y){
		return tr[k].v;
	}
	int mid=l+r>>1;
	ll sum=0;
	if(x<=mid) sum+=query(x,y,tr[k].l,l,mid);
	if(mid+1<=y) sum+=query(x,y,tr[k].r,mid+1,r);
	return sum;
}
void init()
{
	memset(rt,0,sizeof(rt));
	tot=0;
}
void pr()
{
	// for(int i=1;i<=totr;++i)
	// {
	// 	cout<<"tree "<<i<<": ";
	// 	for(int j=1;j<=5;++j) cout<<query(j,j,rt[i],1,n)<<" ";cout<<endl;
	// }
}
int main()
{
	n=getint();m=getint();
	for(int i=1;i<=n;++i) a[i]=getint();
	build(1,n,rt[1]);
	totr=1;
	int x,y,z,p;
	for(int i=0;i<m;++i)
	{
		switch(getint())
		{
			case 0:{
				p=getint();x=getint();y=getint();
				// 两种方法
				// ll k1=query(1,y,rt[p],1,n);
				// ll k2=query(x,y,rt[p],1,n);
				// split(rt[p],rt[++totr],k1-k2);
				// int tmp=0;
				// split(rt[totr],tmp,k2);
				// merge(rt[p],tmp);
				split(x,y,rt[p],rt[++totr],1,n);
				pr();
				break;
			}
			case 1:{
				x=getint();y=getint();
				rt[x]=merge(rt[x],rt[y]);
				pr();
				break;
			}
			case 2:{
				x=getint();y=getint();z=getint();
				add(z,y,rt[x],1,n);
				pr();
				break;
			}
			case 3:{
				x=getint();y=getint();z=getint();
				cout<<query(y,z,rt[x],1,n)<<"\n";
				break;
			}
			case 4:{
				x=getint();
				ll k;cin>>k;
				if(tr[rt[x]].v<k) cout<<"-1\n";
				else cout<<kth(rt[x],1,n,k)<<"\n";
				break;
			}
		}
	}
}