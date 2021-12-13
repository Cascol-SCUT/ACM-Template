#include<bits/stdc++.h>
#define maxN 200005
#define N 1000000
#define INF 1000000000
typedef long long ll;
using namespace std;
struct node{
	int l,r;
	ll v; // 存在的数字的个数
};
struct SM_SEG{
	int rt[maxN],a[maxN],tot,totr,n,m;
	vector<int> bac;
	node tr[400005<<5];
	void build(int l,int r,int &k){
		if(!k) tr[k=++tot]=node{0,0,0};
		if(l==r){
			tr[k].v=a[l];
			return;
		}
		int mid=l+r>>1;
		build(l,mid,tr[k].l);
		build(mid+1,r,tr[k].r);
		tr[k].v=tr[tr[k].l].v+tr[tr[k].r].v;
	}
	void update(int x){
		tr[x].v=tr[tr[x].l].v+tr[tr[x].r].v;
	}
	void del(int x){
		tr[x].l=tr[x].r=tr[x].v=0;
		bac.push_back(x);
	}
	int newnode(){
		if(bac.size()){
			auto tmp=bac.back();bac.pop_back();
			return tmp;
		}
		return ++tot;
	}
	// 查询之前判断总数大于k
	int kth(int x,int l,int r,ll k){
		if(!x) return -1;
		if(l==r) return l;
		int mid=l+r>>1;
		if(tr[tr[x].l].v>=k) return kth(tr[x].l,l,mid,k);
		return kth(tr[x].r,mid+1,r,k-tr[tr[x].l].v);
	}
	int merge(int x,int y){ // 合并线段树
		if(!x||!y) return x+y;
		tr[x].v+=tr[y].v;
		tr[x].l=merge(tr[x].l,tr[y].l);
		tr[x].r=merge(tr[x].r,tr[y].r);
		del(y);
		return x;
	}
	void add(int x,int v,int &k,int l,int r){ //每个y值
		if(!k) tr[k=newnode()]=node{0,0,0};
		tr[k].v+=v;
		if(l==r) return;
		int mid=l+r>>1;
		if(x<=mid) add(x,v,tr[k].l,l,mid);
		if(x>=mid+1) add(x,v,tr[k].r,mid+1,r);
	}
	void split(int pl,int pr,int &x,int &y,int l,int r){ //把pl<= res <=pr的部分划分新的线段树
		if(pl==l&&pr==r){
			swap(x,y);return;
		}
		if(!y) y=newnode();
		int mid=l+r>>1;
		if(pr<=mid) split(pl,pr,tr[x].l,tr[y].l,l,mid);
		else if(pl>mid) split(pl,pr,tr[x].r,tr[y].r,mid+1,r);
		else split(pl,mid,tr[x].l,tr[y].l,l,mid),split(mid+1,pr,tr[x].r,tr[y].r,mid+1,r);
		update(x);
		update(y);
	}
	ll query(int x,int y,int k,int l,int r){ //查询大于等于x 小于等于y的个数
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
	void init(){
		// 不是多组数据
		cin>>n>>m;
		for(int i=1;i<=n;++i) cin>>a[i];
		build(1,n,rt[1]);
		totr=1;
	}
}seg;
int main()
{
	seg.init();
	int x,y,z,p,rt;
	for(int i=0;i<seg.m;++i)
	{
		int tmp; cin>>tmp;
		switch(tmp)
		{
			case 0:{
				cin>>rt>>x>>y;
				seg.split(x,y,seg.rt[rt],seg.rt[++seg.totr],1,seg.n);
				break;
			}
			case 1:{
				cin>>x>>y;
				seg.rt[x]=seg.merge(seg.rt[x],seg.rt[y]);
				break;
			}
			case 2:{
				cin>>rt>>x>>z;
				seg.add(z,x,seg.rt[rt],1,seg.n);
				break;
			}
			case 3:{
				cin>>rt>>x>>y;
				cout<<seg.query(x,y,seg.rt[rt],1,seg.n)<<"\n";
				break;
			}
			case 4:{
				cin>>x;
				ll k;cin>>k;
				if(seg.tr[seg.rt[x]].v<k) cout<<"-1\n";
				else cout<<seg.kth(seg.rt[x],1,seg.n,k)<<"\n";
				break;
			}
		}
	}
}