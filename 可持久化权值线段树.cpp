#include<bits/stdc++.h>
#pragma G++ optimize (2)
using namespace std;
#define For(i,a,b) for(int i=(a),(i##i)=(b);i<=(i##i);++i)
#define rep(i,n) for(int i=0,(i##i)=(n);i<(i##i);++i)
#define Fodn(i,a,b) for(int i=(a),(i##i)=(b);i>=(i##i);--i)
#define pln puts("")
#define il inline
#define pb push_back()
#define ff first
#define ss second
using LL=long long;
using U32=unsigned int;
using U64=unsigned LL;
using LD=long double;
template<typename T>
using pii=pair<T,T>;
template<typename T>
il bool read(T&x){
    x=0;char c=getchar();int f=1;
    while(!isdigit(c)&&(c!='-')&&(c!=EOF))c=getchar();
    if(c==EOF)return 0;if(c=='-')f=-1,c=getchar();
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c&15);c=getchar();}
    x*=f;return 1;
}
template<typename T,typename...Args>
il bool read(T&x,Args&...args){bool res=1;res&=read(x);res&=read(args...);return res;}
const double EPS=1e-6;
const int M=1000000007,INF=0x3f3f3f3f;
const LL INFLL=0x3f3f3f3f3f3f3f3fLL;
const int N=100010,NN=3000010;


int n,a[N],ans,m,ma;
struct dat{
    int l,r,k,num;
    bool operator<(const dat a)const{return r<a.r;}
}q[N];

struct segmenttree{
    int sum,lc,rc;
    LL res;
}tr[4500000];
int tot,rt[N];
int build(int l,int r){
    int x=(++tot);
    tr[x].sum=0;
    tr[x].res=0;
    if(l!=r){
        int mid=(l+r)>>1;
        tr[x].lc=build(l,mid);
        tr[x].rc=build(mid+1,r);
    }
    return x;
}
int insert(int now,int l,int r,int pos){
    int x=(++tot);
    tr[x]=tr[now];
    ++tr[x].sum;
    if(l==r){
        tr[x].res+=l;
        return x;
    }
    int mid=(l+r)>>1;
    if(pos<=mid)tr[x].lc=insert(tr[now].lc,l,mid,pos);
        else tr[x].rc=insert(tr[now].rc,mid+1,r,pos);
    tr[x].res=(tr[tr[x].lc].res+tr[tr[x].rc].res);
    return x;
}
LL ask(int p,int q,int l,int r,int k){
    if(l==r){
        return (LL)l*k;
    }
    int mid=(l+r)>>1;
    int rtot=tr[tr[q].rc].sum-tr[tr[p].rc].sum;
    if(k<=rtot)return ask(tr[p].rc,tr[q].rc,mid+1,r,k);
    else return ask(tr[p].lc,tr[q].lc,l,mid,k-rtot)+tr[tr[q].rc].res-tr[tr[p].rc].res;
}

il void init(){
    read(n);ma=0;
    For(i,1,n)read(a[i]),ma=max(a[i],ma);
    read(m);
    For(i,1,m){
        read(q[i].l,q[i].r,q[i].k);q[i].num=i;
    }
    //sort(q+1,q+1+m);
    tot=0;
    rt[0]=build(1,ma);
    For(i,1,n)rt[i]=insert(rt[i-1],1,ma,i);
}

il LL f(LL x){return x*(x+1)/2*(2*x+1)/3;}

il void solve(){
    For(i,1,m){
        printf("%lld\n",ask(rt[q[i].l-1],rt[q[i].r],1,ma,q[i].k)+f(q[i].r-q[i].l+1));
    }
}

signed main(){
    int t;read(t);
    while(t--){
        init();solve();
    }
    return 0;
}