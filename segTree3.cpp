#include<bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define maxN 500005
#define INF (2e9+15)
#define eps 1e-10
using namespace std;
inline int getint() 
{
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
int n,m,a[maxN];
struct SegmentTree
{
    struct Node{
        int l,r;
        int mx,mx_,se,cnt;
        ll sum;
        int add1,add1_,add2,add2_; //k1是min操作转化成的加操作
    }tr[4*maxN];
    #define lc (o<<1)
    #define rc (o<<1|1)
    void pushup(int o)
    {
        tr[o].sum=tr[lc].sum+tr[rc].sum;
        // cout<<tr[o].l<<" "<<tr[o].r<<" sum: "<<tr[o].sum<<endl;
        tr[o].mx_=max(tr[lc].mx_,tr[rc].mx_);
        tr[o].mx=max(tr[lc].mx,tr[rc].mx);
        if(tr[lc].mx==tr[rc].mx)
        {
            tr[o].se=max(tr[lc].se,tr[rc].se);
            tr[o].cnt=tr[lc].cnt+tr[rc].cnt;
        }
        else if(tr[lc].mx>tr[rc].mx)
        {
            tr[o].se=max(tr[rc].mx,tr[lc].se);
            tr[o].cnt=tr[lc].cnt;
        }
        else{
            tr[o].se=max(tr[lc].mx,tr[rc].se);
            tr[o].cnt=tr[rc].cnt;
        }
    }
    void update(int o,int k1,int k1_,int k2,int k2_) //k1_从上一次下传add到现在，区间加标记达到的最大值
    {
        tr[o].sum+=1ll*k1*tr[o].cnt+1ll*k2*(tr[o].r-tr[o].l+1-tr[o].cnt); //前半部分是针对最大值的
        tr[o].mx_=max(tr[o].mx_,tr[o].mx+k1_);
        tr[o].add1_=max(tr[o].add1_,tr[o].add1+k1_);
        tr[o].mx+=k1;tr[o].add1+=k1;
        tr[o].add2_=max(tr[o].add2_,tr[o].add2+k2_);
        if(tr[o].se!=-INF) tr[o].se+=k2;
        tr[o].add2+=k2;
    }
    void pushdown(int o)
    {
        int tmp=max(tr[lc].mx,tr[rc].mx);
        if(tr[lc].mx==tmp)
            update(lc,tr[o].add1,tr[o].add1_,tr[o].add2,tr[o].add2_);
        else update(lc,tr[o].add2,tr[o].add2_,tr[o].add2,tr[o].add2_); //lc不是
        if(tr[rc].mx==tmp)
            update(rc,tr[o].add1,tr[o].add1_,tr[o].add2,tr[o].add2_);
        else update(rc,tr[o].add2,tr[o].add2_,tr[o].add2,tr[o].add2_);
        tr[o].add1=tr[o].add1_=tr[o].add2=tr[o].add2_=0;
    }
    void build(int o,int l,int r,int *a)
    {
        tr[o].l=l;tr[o].r=r;
        tr[o].add1=tr[o].add1_=tr[o].add2=tr[o].add2_=0;
        if(l==r)
        {
            tr[o].sum=tr[o].mx_=tr[o].mx=a[l];
            // cout<<tr[o].l<<" "<<tr[o].sum<<endl;
            tr[o].se=-INF;tr[o].cnt=1;
            return;
        }
        int mid=l+r>>1;
        build(lc,l,mid,a);
        build(rc,mid+1,r,a);
        pushup(o);
    }
    void modify1(int o,int l,int r,int k) // 区间加v
    {
        if(tr[o].l>r||tr[o].r<l) return;
        if(l<=tr[o].l&&tr[o].r<=r){
            update(o,k,k,k,k);return;
        }
        pushdown(o);
        modify1(lc,l,r,k);modify1(rc,l,r,k);
        pushup(o);
    }
    void modify2(int o,int l,int r,int k) //区间取min v
    {
        if(tr[o].l>r||tr[o].r<l||k>=tr[o].mx) return;
        if(l<=tr[o].l&&tr[o].r<=r&&k>tr[o].se){
            update(o,k-tr[o].mx,k-tr[o].mx,0,0);
            return;
        }
        pushdown(o);
        modify2(lc,l,r,k);modify2(rc,l,r,k);
        pushup(o);
    }
    ll query3(int o,int l,int r) //区间和
    {
        if(tr[o].l>r||tr[o].r<l) return 0;
        if(l<=tr[o].l&&tr[o].r<=r){
            // cout<<tr[o].l<<" "<<tr[o].r<<" "<<tr[o].sum<<endl;
            return tr[o].sum;
        }
        pushdown(o);
        return query3(lc,l,r)+query3(rc,l,r);
    }
    ll query4(int o,int l,int r) // Ai区间最大
    {
        if(tr[o].l>r||tr[o].r<l) return -INF;
        if(l<=tr[o].l&&tr[o].r<=r){
            return tr[o].mx;
        }
        pushdown(o);
        return max(query4(lc,l,r),query4(rc,l,r));
    }
    ll query5(int o,int l,int r) // Bi区间最大 Bi为max(Bi,Ai)
    {
        if(tr[o].l>r||tr[o].r<l) return -INF;
        if(l<=tr[o].l&&tr[o].r<=r){
            return tr[o].mx_;
        }
        pushdown(o);
        return max(query5(lc,l,r),query5(rc,l,r));
    }
}seg;
int main()
{
	n=getint();m=getint();
    for(int i=1;i<=n;++i) a[i]=getint();
    seg.build(1,1,n,a);
    // for(int i=1;i<=n;++i) cout<<seg.query3(1,i,i)<<" ";cout<<endl;
    // for(int i=1;i<=n;++i) cout<<seg.query4(1,i,i)<<" ";cout<<endl;
    // for(int i=1;i<=n;++i) cout<<seg.query5(1,i,i)<<" ";cout<<endl;
    int opt,l,r,v;
    for(int i=1;i<=m;++i)
    {
        opt=getint();l=getint();r=getint();
        switch(opt)
        {
            case 1:{
                v=getint();
                seg.modify1(1,l,r,v); // 区间加v
                break;
            }
            case 2:{
                v=getint();
                seg.modify2(1,l,r,v); //区间取min v
                break;
            }
            case 3:{
                cout<<seg.query3(1,l,r)<<"\n"; //区间和
                break;
            }
            case 4:{
                cout<<seg.query4(1,l,r)<<"\n"; // Ai区间最大
                break;
            }
            case 5:{
                cout<<seg.query5(1,l,r)<<"\n"; // Bi区间最大 Bi为max(Bi,Ai)
                break;
            }
        }
        // for(int i=1;i<=n;++i) cout<<seg.query3(1,i,i)<<" ";cout<<endl;
    }
}