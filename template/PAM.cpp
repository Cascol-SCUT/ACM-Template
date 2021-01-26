#include<bits/stdc++.h>
#define maxN 500005
#define INF 1e9
#define P 1000000007
#define lll __int128
typedef long long ll;
using namespace std;
string c;
int s[maxN];
struct node{
    int ch[26];
    int fail,len,num;
}tr[maxN];
int sz,last;
void init()
{
    tr[0].fail=1;tr[0].len=0;
    tr[1].fail=0;tr[1].len=-1;
    sz=1;last=0;
}
int get_fail(int x,int pos) // x是节点
{
    while(pos-tr[x].len-1<0 || s[pos-tr[x].len-1]!=s[pos]) x=tr[x].fail;
    return x;
}
int insert(int x,int pos) // x是要插入的元素
{
    int u=get_fail(last,pos); //找到最长合法的回文
    if(!tr[u].ch[x]){
        int tmp=get_fail(tr[u].fail,pos); //找最长合法的回文后缀
        tr[++sz].fail=tr[tmp].ch[x];
        tr[u].ch[x]=sz;
        tr[sz].len=tr[u].len+2;
        tr[sz].num=tr[tr[sz].fail].num+1; //num记录树的深度
    }
    last=tr[u].ch[x];
    return tr[last].num;
}
int main()
{
    // freopen("P5496_1.in","r",stdin);
    cin>>c;
    init();
    int ans=0;
    for(int i=0,len=c.length();i<len;++i)
    {
        s[i]=(c[i]-97+ans)%26;
        ans=insert(s[i],i);
        cout<<ans<<" \n"[i==len-1];
    }
    // for(int i=0,len=c.length();i<len;++i) cout<<s[i]<<" ";cout<<"\n";
}