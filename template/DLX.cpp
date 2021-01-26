#include<bits/stdc++.h>
#define maxN 250050
using namespace std;
int n,m,cnt;
int l[maxN],r[maxN],u[maxN],d[maxN],row[maxN],col[maxN]; //每个点的左，右，上下，行，列信息
int h[maxN],s[maxN];//每行的头节点 每列的结点数
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
void init()
{
    for(int i=0;i<=m;++i)
    {
        r[i]=i+1;l[i]=i-1;
        u[i]=d[i]=i;
    }
    r[m]=0;l[0]=m;
    memset(h,-1,sizeof(h));
    memset(s,0,sizeof(s));
    cnt=m+1;
}
inline void add(int R,int C)
{
    s[C]++;
    row[cnt]=R;col[cnt]=C;
    u[cnt]=C;
    d[cnt]=d[C];
    u[d[C]]=cnt;
    d[C]=cnt;
    if(h[R]<0) h[R]=r[cnt]=l[cnt]=cnt;
    else{
        r[cnt]=h[R];
        l[cnt]=l[h[R]];
        r[l[cnt]]=cnt;
        l[h[R]]=cnt;
    }
    cnt++;
}
inline void remove(int c) //删除c列
{
    r[l[c]]=r[c];l[r[c]]=l[c];
    for(int i=d[c];i!=c;i=d[i]){ //寻找行
        for(int j=r[i];j!=i;j=r[j]){ //寻找行中元素
            u[d[j]]=u[j];
            d[u[j]]=d[j];
            s[col[j]]--;
        }
    }
}
inline void resume(int c) //完全反过来的
{
    for(int i=u[c];i!=c;i=u[i]){
        for(int j=l[i];j!=i;j=l[j]){
            u[d[j]]=j;
            d[u[j]]=j;
            s[col[j]]++;
        }
    }
    r[l[c]]=l[r[c]]=c;
}
int ans[505];
bool dance(int deep)
{
    if(r[0]==0){
        return true;
    }
    int c=r[0];
    for(int i=r[0];i!=0;i=r[i]) if(s[i]<s[c]) c=i;
    remove(c);
    for(int i=d[c];i!=c;i=d[i]){
        ans[deep]=row[i];
        for(int j=r[i];j!=i;j=r[j]) remove(col[j]);
        if(dance(deep+1)) return true;
        for(int j=l[i];j!=i;j=l[j]) resume(col[j]); //注意这里是l[i] 顺序很重要 不然遍历时会出错
    }
    resume(c);
    return false;
}
int main()
{
    n=getint();m=getint();
    init();
    int x;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            x=getint();
            if(x){
                add(i,j);
            }
        }
    }
    // for(int i=0;i<cnt;++i) cout<<row[i]<<" "<<col[i]<<" "<<l[i]<<" "<<r[i]<<" "<<u[i]<<" "<<d[i]<<"\n";
    // return 0;
    if(dance(0)){
        int i=0;
        while(ans[i]) cout<<ans[i++]<<" ";cout<<"\n";
    }
    else{
        cout<<"No Solution!\n";
    }
}