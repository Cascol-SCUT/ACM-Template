#include<bits/stdc++.h>
#define Mod 998244353
#define maxN 2500005
#define ll long long
#define uint unsigned int
using namespace std;
inline uint Add(uint a, uint b) {return (a + b >= Mod) ? a + b - Mod : a + b;}
inline uint Dec(uint a, uint b) {return (a - b < 0) ? a - b + Mod : a - b;}
inline uint Mul(uint a, uint b) {return 1ll * a * b % Mod;}
inline uint qpow(uint a, int b) {uint res = 1; for(; b; b >>= 1, a = Mul(a, a))  if(b & 1)  res = Mul(res, a); return res;}
namespace NTT {
	int sz;
	uint w[maxN], w_mf[maxN];
	uint mf(int x) {return ((1ll * x) << 32) / Mod;}
	inline void init(int n) {
		for(sz = 2; sz < n; sz <<= 1);
		uint pr = qpow(3, (Mod - 1) / sz);
		w[sz / 2] = 1; w_mf[sz / 2] = mf(w[sz / 2]);
		for(int i = 1; i < sz / 2; i++)  w[sz / 2 + i] = Mul(w[sz / 2 + i - 1], pr), w_mf[sz / 2 + i] = mf(w[sz / 2 + i]);
		for(int i = sz / 2 - 1; i; i--)  w[i] = w[i << 1], w_mf[i] = w_mf[i << 1];
	}
	inline void NTT(vector<uint>& A, int L) {
		for(int d = L >> 1; d; d >>= 1)
			for(int i = 0; i != L; i += d << 1)
				for(int j = 0; j != d; j++) {
					uint x = A[i + j] + A[i + d + j];
					if(x >= Mod * 2)  x -= Mod * 2;
					ll t = A[i + j] + Mod * 2 - A[i + d + j];
					ll q = t * w_mf[d + j] >> 32;
					uint y = t * w[d + j] - q * Mod;
					A[i + j] = x; A[i + d + j] = y;
				}
	}
	inline void INTT(vector<uint>& A, int L) {
		for(int d = 1; d != L; d <<= 1)
			for(int i = 0; i != L; i += (d << 1))
				for(int j = 0; j != d; j++) {
					uint x = A[i + j];
					if(x >= Mod * 2)  x -= Mod * 2;
					ll y = A[i + d + j], q = y * w_mf[d + j] >> 32, t = y * w[d + j] - q * Mod;
					A[i + j] = x + t; A[i + d + j] = x + Mod * 2 - t;
				}
		reverse(A.begin() + 1, A.end());
		int k = __builtin_ctz(L);
		for(int i = 0; i != L; i++) {
			ll m = -A[i] & (L - 1);
			A[i] = (A[i] + m * Mod) >> k;
		}
	}
} // namespace NTT
struct poly {
	vector<uint> a;
	inline int deg() {return a.size() - 1;}
	inline uint& operator [] (const int &x) {return a[x];}
	inline poly(int d = 0, int t = 0) {a.resize(d + 1); a[d] = t;}
	inline poly extend(int len) {
		poly c = *this;
		c.a.resize(len + 1);
		return c;
	}
	inline friend poly operator * (poly A, poly B) {
		int len = A.deg() + B.deg() + 1, lim = 2;
		for(; lim <= len; lim <<= 1); NTT::init(lim);
		A.a.resize(lim); B.a.resize(lim);
		NTT::NTT(A.a, lim); NTT::NTT(B.a, lim);
		//A.Print(lim - 1);  B.Print(lim - 1); 
		for(int i = 0; i < lim; i++)  A[i] = Mul(A[i], B[i]);
		NTT::INTT(A.a, lim); A.a.resize(len);
		for(int i = 0; i < len; i++)  if(A[i] >= Mod)  A[i] -= Mod;
		return A;
	}
};
int main() {
	poly A, B;
	int n,m;cin>>n>>m;
	A.a.resize(n+1);for(int i=0;i<=n;++i) cin>>A.a[i];
	B.a.resize(m+1);for(int i=0;i<=m;++i) cin>>B.a[i];
	A = A * B;
	for(int i=0;i<=n+m;++i) cout<<A.a[i]<<" \n"[i==n+m];
}