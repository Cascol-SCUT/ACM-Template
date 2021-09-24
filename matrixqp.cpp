#include<bits/stdc++.h>
#define mod 1000000009
#define maxN 2

typedef long long ll;
using namespace std;

struct Matrix{
	ll a[maxN][maxN];
	Matrix(){
		memset(a,0,sizeof a);
	}
	inline void build(){     //建造单位矩阵
		for(int i=0;i<maxN;++i)a[i][i]=1;
	}
    Matrix operator *(const Matrix &y){     //重载运算符
        Matrix z;
        for(int k=0;k<maxN;++k)
            for(int i=0;i<maxN;++i)
                for(int j=0;j<maxN;++j)
                    z.a[i][j]=(z.a[i][j]+a[i][k]*y.a[k][j]%mod)%mod;
        return z;
    }
}a;
Matrix mtqp(Matrix a,int b)
{
    Matrix ans;ans.build();
    while(b)
    {
        if(b&1) ans=ans*a;
        a=a*a;
        b>>=1;
    }
    return ans;
}
int main()
{
    a.a[0][0]=2;a.a[1][1]=3;
    a=mtqp(a,2);
    cout<<a.a[1][1];
}