#include<bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define maxN 20005
#define maxM 1005
#define INF 1e18
#define eps 1e-10
#define P 1000000007
using namespace std;
const double PI = acos(-1);
const int M=sqrt(P)+1;
const complex<ld> I(0,1);
complex<ld> wn[maxN],a0[maxN],a1[maxN],b0[maxN],b1[maxN],p[maxN],q[maxN];
ll ans[maxM];
int tax[maxN];
struct EDGE{
    int from,to,next;
}edge[maxM*2];
int tot,head[maxM];
int n,m,pn,pm;
ll dp[maxM][2][maxM];
void add(int u,int v)
{
    edge[++tot]={u,v,head[u]};
    head[u]=tot;
}
inline void FFT(complex<ld> *a,int n,int opt)
{
	for(int i=1;i<n;++i){
		if(tax[i]>i) swap(a[i],a[tax[i]]);
	}
	complex<ld> w,*a0,*a1,t;
	int len;
	for(int i=1;i<n;i<<=1){
		len=i<<1;
		for(int st=0;st<n;st+=len){
			a0=a+st;a1=a0+i;
			for(int k=0;k<i;++k){
				w=wn[1ll*k*n/i];
				if(opt!=1) w=conj(w);
				t=*a1*w;*a1=*a0-t;*a0+=t;
				++a0;++a1;
			}
		}
	}
	if(opt==-1){
		for(int i=0;i<n;++i) a[i]/=n;
	}
}
void makerev(int n)
{
	int d=n>>1,p=0;
	tax[p++]=0;tax[p++]=d;
	for(int w=2;w<=n;w<<=1){
		d>>=1;
		for(int i=0;i<w;++i){
			tax[p++]=tax[i]|d;
		}
	}
}
inline void qDFT(complex<ld> *a,complex<ld> *b,int m,int n)
{
	for(int i=0;i<n;++i) a[i]+=b[i]*I;
	FFT(a,n,1);
	for(int i=0;i<n;++i) b[i]=conj(a[i?n-i:0]);
	complex<ld> p,q,t=complex<ld>(0.5,0);
	for(int i=0;i<n;++i){
		p=a[i];q=b[i];
		// complex<ld> t=p-q;
		a[i]=(p+q)*t;
		b[i]=(q-p)*t*I;
	}
}
inline ll num(ld x)
{
	ld res=x;
	return res>0?(ll)(x+0.5)%P:(ll)(x-0.5)%P;
}
inline void MTT(ll *a,ll *b)
{
	int x;
	for(int i=0;i<=pm;++i){
		a0[i]=a[i]/M;
		b0[i]=a[i]%M;
	}
	for(int i=0;i<=pm;++i){
		a1[i]=b[i]/M;
		b1[i]=b[i]%M;
	}
    for(int i=pm+1;i<=n;++i) a0[i]=a1[i]=b0[i]=b1[i]=0;
	qDFT(a0,b0,pm,n); //一次DFT把两个数组都进行了DFT
	qDFT(a1,b1,pm,n);
	for(int i=0;i<=n;++i){
		p[i]=a0[i]*a1[i]+b0[i]*a1[i]*I;
		q[i]=a0[i]*b1[i]+b0[i]*b1[i]*I;
	}
	FFT(p,n,-1);FFT(q,n,-1);
	for(int i=0;i<=pm;++i){
		ans[i]=num(p[i].real())*M*M%P+(num(p[i].imag())+num(q[i].real()))*M%P+num(q[i].imag())%P;
		ans[i]=(ans[i]%P+P)%P;
	}
	// for(int i=0;i<=pm;++i) cout<<ans[i]<<" ";cout<<endl;
}
ll tmp[2][maxM];
map<int,ll> mp[maxM][2];
void merge(int u,int v)
{
    memset(tmp,0,sizeof(tmp));
    if(mp[u][1].size()*mp[v][0].size()<n){ //启发式
        for(int x=0;x<=1;++x){
            for(int y=0;y<=1;++y){
                for(auto iu:mp[u][x]){
                    for(auto iv:mp[v][y]){
                        if(iu.first+iv.first>pm) continue;
                        tmp[x&y][iu.first+iv.first]=(tmp[x&y][iu.first+iv.first]+iu.second*iv.second)%P;
                    }
                }
            }
        }
    }
    else{
        for(int x=0;x<=1;++x){
            for(int y=0;y<=1;++y){
                MTT(dp[u][x],dp[v][y]);
                for(int j=0;j<=pm;++j) tmp[x&y][j]=(tmp[x&y][j]+ans[j])%P;
            }
        }
    }
    mp[u][0].clear();mp[u][1].clear();
    for(int i=0;i<=1;++i){
        for(int j=0;j<=pm;++j) {
            dp[u][i][j]=tmp[i][j];
            if(dp[u][i][j]) mp[u][i][j]=dp[u][i][j];
        }
    }
}
void pr()
{
    for(int i=1;i<=pn;++i){
        cout<<"i="<<i<<":\n";
        for(int j=0;j<=1;++j){
            for(int k=0;k<=pm;++k) cout<<dp[i][j][k]<<" ";
            cout<<"\n";
        }
        cout<<"------------\n";
    }
}
void dfs(int u,int p)
{
    vector<int> vec;
    for(int i=head[u];i;i=edge[i].next)
    {
        int v=edge[i].to;
        if(v==p) continue;
        vec.push_back(v);
        dfs(v,u);
    }
    if(vec.size()==0){
        dp[u][0][1]=1;
        dp[u][1][0]=1;
        mp[u][0][1]=1;
        mp[u][1][0]=1;
        // pr();
        // cout<<"==================================\n";
        return;
    }
    while(vec.size()>1){
        int x=vec.back();vec.pop_back();
        int y=vec.back();vec.pop_back();
        merge(y,x);
        vec.push_back(y);
    }
    int v=vec[0];
    for(int i=0;i<=pm;++i){
        dp[u][0][i]=(dp[v][0][i]+(i-1>=0?dp[v][1][i-1]:0))%P;
        if(dp[u][0][i]) mp[u][0][i]=dp[u][0][i];
        dp[u][1][i]=(dp[v][0][i]+dp[v][1][i])%P;
        if(dp[u][1][i]) mp[u][1][i]=dp[u][1][i];
    }
    // pr();
    // cout<<"==================================\n";
}
void init()
{
    pm=m;pn=n;
    m*=2;
    for(n=1;n<=m;n<<=1);
    assert(n<maxN);
    makerev(n);
    for(int i=0;i<n;++i){
		wn[i]=complex<ld>(cos(PI/n*i),sin(PI/n*i));
	}
}
int main()
{
    cin>>n>>m;
    int u,v;
    for(int i=1;i<n;++i){
        cin>>u>>v;
        add(u,v);add(v,u);
    }
    init();
    dfs(1,0);
    // pr();
    cout<<(dp[1][0][pm]%P+P)%P<<"\n";
}