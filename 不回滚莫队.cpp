#include<bits/stdc++.h>
typedef long long ll;
#define maxN 200005
using namespace std;
int n,m,a[maxN],tot;
unordered_map<int,int> mp;
int b[maxN];
struct que{
    int l,r,id;
    bool operator <(const que &x)const{
        return b[l]<b[x.l]||(b[l]==b[x.l]&&r<x.r);
    }
}q[maxN];
int clear[maxN],cr;
int la[maxN],st[maxN];
int ANS[maxN];
int calc(int l,int r)
{
    unordered_map<int,int> um;
    int ans=0;
    for(int i=r;i>=l;--i){
        if(um.find(a[i])==um.end()) um[a[i]]=i;
        else ans=max(ans,um[a[i]]-i);
    }
    return ans;
}
int main()
{
    // freopen("P5906_1.in","r+",stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    int len=sqrt(n);
    for(int i=1;i<=n;++i) b[i]=(i-1)/len+1;
    int x;
    for(int i=1;i<=n;++i){
        cin>>x;
        if(mp.find(x)==mp.end()) mp[x]=++tot;
        a[i]=mp[x];
    }
    cin>>m;
    for(int i=1;i<=m;++i) {
        cin>>q[i].l>>q[i].r;
        q[i].id=i;
    }
    sort(q+1,q+m+1);
    for(int i=1,j=1;j<=b[n]&&i<=n;++j)
    {
        int br=min(j*len,n),l=br+1,r=l-1,ans=0;
        cr=0;
        for(;b[q[i].l]==j;++i)
        {
            // cout<<l<<" "<<r<<" | "<<q[i].l<<" "<<q[i].r<<"\n";
            if(b[q[i].r]==j){
                ANS[q[i].id]=calc(q[i].l,q[i].r);
                continue;
            }
            while(r<q[i].r){
                ++r;
                la[a[r]]=r;
                if(!st[a[r]]) st[a[r]]=r,clear[++cr]=a[r];
                ans=max(ans,r-st[a[r]]);
            }
            int tmp=ans;
            while(l>q[i].l){
                --l;
                if(la[a[l]]) ans=max(ans,la[a[l]]-l);
                else la[a[l]]=l;
            }
            // cout<<ans<<"\n";
            ANS[q[i].id]=ans;
            ans=tmp;
            while(l<=br){
                if(la[a[l]]==l) la[a[l]]=0;
                ++l;
            }
        }
        for(int k=1;k<=cr;++k) st[clear[k]]=la[clear[k]]=0;
    }
    for(int i=1;i<=m;++i) cout<<ANS[i]<<"\n";
}
