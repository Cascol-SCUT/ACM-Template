#include <bits/stdc++.h>
#define maxN 200005
#define INF 0x3f3f3f3f
typedef long long ll;
using namespace std;
ll sum[maxN*4],a[maxN],mi[maxN*4],mx[maxN*4];
ll lz[maxN*4];
int n;
void build(int k,int l,int r)
{
    if(l==r){
        sum[k]=mi[k]=mx[k]=a[l];
        return;
    }
    int mid=l+r>>1;
    build(k*2,l,mid);
    build(k*2+1,mid+1,r);
    sum[k]=sum[k*2]+sum[k*2+1];
    mi[k]=mi[k*2+1];mx[k]=mx[k*2];
}
void mark(int k,int l,int r,ll v)
{
    lz[k]=mi[k]=mx[k]=v;
    sum[k]=(r-l+1)*v;
}
void pushdown(int k,int l,int r)
{
    if(lz[k]){
        int mid=l+r>>1;
        mark(k*2,l,mid,lz[k]);
        mark(k*2+1,mid+1,r,lz[k]);
        lz[k]=0;
    }
}
void modify(int k,int l,int r,int x,ll v)// 1-x
{
    if(mi[k]>=v) return;
    if(r<=x&&mx[k]<=v){
        mark(k,l,r,v);
        return;
    }
    pushdown(k,l,r);
    int mid=l+r>>1;
    modify(k*2,l,mid,x,v);
    if(mid+1<=x) modify(k*2+1,mid+1,r,x,v);
    sum[k]=sum[k*2]+sum[k*2+1];
    mi[k]=mi[k*2+1];mx[k]=mx[k*2];
}
int find(int k,int l,int r,int x,ll v)// [x,n]中第一个小于等于v的
{
    if(mi[k]>v) return 0;
    if(l==r) return l;
    int mid=l+r>>1;
    int res=0;
    if(x<=mid) res=find(k*2,l,mid,x,v);
    return res?res:find(k*2+1,mid+1,r,x,v);
}
int query(int k,int l,int r,int x,ll &v)
{
    // if(mi[k]>v) return 0;
    if(l>=x&&sum[k]<=v){
        v-=sum[k];
        return r;
    }
    if(l==r){
        v-=mi[k];
        return l;
    }
    pushdown(k,l,r);
    int mid=l+r>>1;
    int res=0;
    if(x<=mid) {
        res=query(k*2,l,mid,x,v);
        if(res<mid) return res;
    }
    if(x>=mid+1) res=max(res,query(k*2+1,mid+1,r,x,v));
    return res;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int q;
    cin>>n>>q;
    for(int i=1;i<=n;++i) cin>>a[i];
    build(1,1,n);
    for(int i=1;i<=q;++i){
        int t,x;
        ll v;cin>>t>>x>>v;
        if(t==1) modify(1,1,n,x,v);
        else{
            int cur=x,nx=0;
            int ans=0;
            while(cur<=n&&(nx=find(1,1,n,cur,v))){
                cur=nx;
                int r=query(1,1,n,cur,v);
                ans+=r-cur+1;cur=r+1;
            }
            cout<<ans<<"\n";
        }
    }
}