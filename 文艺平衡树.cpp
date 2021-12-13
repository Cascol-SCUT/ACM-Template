#include<bits/stdc++.h>
#define maxN 100005
#define INF 0x3f3f3f3f
using namespace std;
struct TREE{
    int fa,size,cnt,value,tag,son[2];
};
struct SPLAY_2B{
    int sz,a[maxN],original[maxN],n,m,root=1;
    TREE s[maxN];
    int get(int x){
        return s[s[x].fa].son[1]==x;
    }
    void update(int x){
        if(x){
            s[x].size=s[x].cnt;
            if(s[x].son[0]) s[x].size+=s[s[x].son[0]].size;
            if(s[x].son[1]) s[x].size+=s[s[x].son[1]].size;
        }
    }
    int build_tree(int l,int r,int fa){
        if(l>r) return 0;
        int now=++sz,mid=l+r>>1;
        s[now].fa=fa;
        s[now].son[0]=s[now].son[1]=0;
        s[now].cnt=1;s[now].size=1;
        s[now].value=original[mid];
        s[now].son[0]=build_tree(l,mid-1,now);
        s[now].son[1]=build_tree(mid+1,r,now);
        update(now);
        return now;
    }
    void init(){
        original[1]=INF;original[n+2]=-INF;
        for(int i=2;i<n+2;++i){
            original[i]=i-1;
        }
        build_tree(1,n+2,0);
    }
    void pushdown(int x){
        if(x&&s[x].tag){
            s[s[x].son[0]].tag^=1;
            s[s[x].son[1]].tag^=1;
            swap(s[x].son[1],s[x].son[0]);
            s[x].tag=0;
        }
    }
    void rotate(int x) {
        int old = s[x].fa, oldf = s[old].fa;
        pushdown(x);pushdown(old);
        int which = get(x);
        s[old].son[which] = s[x].son[which ^ 1]; // a
        if(s[old].son[which]) s[s[old].son[which]].fa = old;
        s[old].fa = x; s[x].son[which ^ 1] = old;
        s[x].fa = oldf;
        if (oldf)
            s[oldf].son[s[oldf].son[1] == old] = x;
        update(old); update(x);
    }
    void splay(int x,int goal){ // 不断翻转操作
        for(int fa;(fa=s[x].fa)!=goal;rotate(x))
        {
            if(s[fa].fa!=goal){
                rotate(get(x)==get(fa)?fa:x);
            }
        }
        if(!goal) root=x; 
    }
    int find(int x){ // 寻找到第x个数 路径上全都pushdown
        int cur=root;
        while(true){
            pushdown(cur);
            if(x<=s[s[cur].son[0]].size)cur=s[cur].son[0];
            else{
                x-=s[s[cur].son[0]].size+1;
                if(!x) return cur;
                cur=s[cur].son[1];
            }
        }
    }
    void reverse(int x,int y){
        int l=x,r=y+2;
        l=find(l);r=find(r);
        splay(l,0); // 翻转到最上面并且成为根
        splay(r,l); // 翻转到根的下边 因为l现在是根
        s[s[s[root].son[1]].son[0]].tag^=1;  //设置翻转tag
    }
    void dfs(int x,vector<int> &seq){
        if(!x) return;
        pushdown(x);
        dfs(s[x].son[0],seq);
        if(s[x].value!=INF && s[x].value!=-INF) seq.push_back(s[x].value);
        dfs(s[x].son[1],seq);
    }
    vector<int> get_seq(){
        vector<int> seq;
        dfs(root,seq);
        return seq;
    }
}sp;
int main()
{
	ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n,m; cin>>n>>m;
    sp.n=n; sp.m=m;
    sp.init();
    for(int i=1;i<=m;++i){
        int l,r; cin>>l>>r;
        sp.reverse(l,r);
    }
    auto ans = sp.get_seq();
    for(auto it:ans) cout<<it<<" ";cout<<"\n";
}