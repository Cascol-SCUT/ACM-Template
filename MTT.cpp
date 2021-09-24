#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long u64;
const int MAX_N = 1 << 18;
const double Pi = acos(-1);
int n, m, P, a[MAX_N], b[MAX_N];
struct Complex{
    double re, im;
    
    Complex () {re = 0; im = 0;}
    Complex (double a, double b) : re(a), im(b) {}
    
    Complex operator + (const Complex &x) const {return Complex(re + x.re, im + x.im);}
    Complex operator - (const Complex &x) const {return Complex(re - x.re, im - x.im);}
    Complex operator * (const Complex &x) const {return Complex(re * x.re - im * x.im, re * x.im + im * x.re);}
    Complex& operator *= (const Complex &x) {return *this = *this * x;}
};

const Complex* init_w(const int &n) {
    static const Complex *w[MAX_N];
    if (w[n] == NULL) {
        register Complex *wn = new Complex[n];
        register Complex w0 = Complex(cos(Pi / n), sin(Pi / n));
        wn[0].re = 1;
        if (n > 1) {
            const register Complex *wm = init_w(n >> 1);
            for (int i = 0; i < n; i += 2)
                wn[i + 1] = (wn[i] = wm[i >> 1]) * w0;
        }
        w[n] = wn;
    }
    return w[n];
}

void fft(Complex *a, int n, int ty) {
    for (int i = 0, j = 0; i < n; i ++) {
        if (i < j) swap(a[i], a[j]);
        for (int k = n >> 1; (j ^= k) < k; k >>= 1);
    }
    for (int i = 1; i < n; i <<= 1) {
        const Complex *w = init_w(i);
        for (int j = 0; j < n; j += i << 1)
            for (int k = j; k < j + i; k ++) {
                const Complex t1 = a[k], t2 = a[k + i] * w[k - j];
                a[k] = t1 + t2; a[k + i] = t1 - t2;
            }
    }
    if (ty == 1) return ;
    reverse(a + 1, a + n);
    const double inv = 1.0 / n;
    for (int i = 0; i < n; i ++) {
        a[i].re *= inv; a[i].im *= inv;
    }
}

void mul(int *a, int *b, int *res, int n, int m, int p) {
    static int len;
    static Complex A[MAX_N], B[MAX_N], c0[MAX_N], c1[MAX_N];
    for (len = 1; len < n + m; len <<= 1);
    for (int i = 0; i < n; i ++) A[i] = Complex(a[i] & 32767, a[i] >> 15);
    for (int i = 0; i < m; i ++) B[i] = Complex(b[i] & 32767, b[i] >> 15);
    fft(A, len, 1); fft(B, len, 1);
    for (int i = 0; i < len; i ++) {
        const int conj = (len - i) & (len - 1);
        c0[i] = Complex(0.5 * (A[i].re + A[conj].re), 0.5 * (A[i].im - A[conj].im)) * B[i];
        c1[i] = Complex(0.5 * (A[i].im + A[conj].im), 0.5 * (A[conj].re - A[i].re)) * B[i];
    }
    for (int i = 0; i < len; i ++) A[i] = B[i] = Complex();
    fft(c0, len, -1); fft(c1, len, -1);
    for (int i = 0; i < len; i ++) {
        ll c00 = c0[i].re + 0.5, c01 = c0[i].im + 0.5, c10 = c1[i].re + 0.5, c11 = c1[i].im + 0.5;
        res[i] = (c00 + ((c01 + c10) % p << 15) + (c11 % P << 30)) % P; c0[i] = c1[i] = Complex();
    }
}

int main() {
    cin >> n >> m >> P;
    for (int i = 0; i <= n; i ++) cin >> a[i];
    for (int i = 0; i <= m; i ++) cin >> b[i];
    mul(a, b, a, n + 1, m + 1, P);
    for (int i = 0; i <= n + m; i ++) cout << a[i] << (i < n + m ? ' ' : '\n');
    return 0;
}