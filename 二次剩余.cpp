#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define int long long
ll n,p,ii;
ll add(ll x,ll y){
    return (x+y)%p;
}
ll sub(ll x,ll y){
    return (x-y+p)%p;
}
ll mul(ll x,ll y){
    return x*y%p;
}
// struct comp{
// 	long long x,y;
// 	comp (long long xx=0,long long yy=0){ x=xx; y=yy; return ;}
// };

// comp operator *(comp a,comp b){return comp(add(mul(a.x,b.x),mul(a.y,mul(b.y,ii))),add(mul(a.x,b.y),mul(a.y,b.x)));}

ll qp(ll a,ll b)
{
    ll ans=1;
    while(b){
        if(b&1) ans=ans*a%p;
        a=a*a%p;
        b>>=1;
    }
    return ans;
}
int cqp(comp a,ll b)
{
    comp ans=comp(1,0);
    while(b){
        if(b&1) ans=ans*a;
        a=a*a;
        b>>=1;
    }
    return ans.x;
}
bool find(ll a)
{
    add(mul(a,a),-n);
    return qp(sub(mul(a,a),n),(p-1)/2) ==p-1;
}
void Cipolla()
{
    int a=rand()%p;
    while(!a || !find(a)) a=rand()%p;
    ii=sub(mul(a,a),n);
    int x1,x2;
    x1=cqp(comp(a,1),(p+1)/2);
    x2=p-x1;
    if(x1>x2) swap(x1,x2); 
    cout<<x1;
    if(x1!=x2) cout<<" "<<x2<<endl;
    else cout<<endl;
}
void solve()
{
    int T;cin>>T;
    srand(time(0));
    while(T--)
    {
        cin>>n>>p;
        n%=p;
        if(n==0) cout<<0<<endl;
        else if(qp(n,(p-1)/2)==p-1) cout<<"Hola!\n";
        else Cipolla();
    }
}
struct Cipolla2{
    ll n,p,ii;
    struct comp{
        ll x,y;
        comp (ll xx=0,ll yy=0){ x=xx; y=yy; return ;}
    };

    comp operator *(comp a,comp b){return comp(add(mul(a.x,b.x),mul(a.y,mul(b.y,ii))),add(mul(a.x,b.y),mul(a.y,b.x)));}
    void cipolla(){
        int a=rand()%p;
        while(!a || !find(a)) a=rand()%p;
        ii=sub(mul(a,a),n);
        int x1,x2;
        x1=cqp(comp(a,1),(p+1)/2);
        x2=p-x1;
        if(x1>x2) swap(x1,x2);
    }
}
signed main()
{
	// freopen("D:\\","w+",stdout);
    cin.tie(0);
	solve();
}