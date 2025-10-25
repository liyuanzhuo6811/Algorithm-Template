// {"name": "快速傅里叶变换", "intro": "迭代式 FFT"}
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
#define db double
int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') f ^= (c == '-'), c = getchar();
    while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return f ? x : -x;
}
void write(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const db PI = acos(-1.0);
struct CP {
    db re, im;
    CP() { re = im = 0; }
    CP(db x, db y) { re = x, im = y; }
    CP operator+(const CP &b) const { return CP(re + b.re, im + b.im); }
    CP operator-(const CP &b) const { return CP(re - b.re, im - b.im); }
    CP operator*(const CP &b) const { return CP(re * b.re - im * b.im, re * b.im + im * b.re); }
};
#define N 3000005
int n, m, rev[N];
CP a[N], b[N];
inline void init(int n) {
    int b = log2(n);
    for (int i = 1; i < n; i++) rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (b - 1));
}
inline void FFT(CP *a, int n, int op) {
    for (int i = 0; i < n; i++)
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int len = 1; len <= (n >> 1); len <<= 1) {
        CP wn = CP(cos(PI / len), sin(PI / len) * op);
        for (int i = 0; i < n; i += (len << 1)) {
            CP w = CP(1.0, 0.0);
            for (int j = 0; j < len; j++, w = w * wn) {
                CP a0 = a[i + j], a1 = w * a[i + j + len];
                a[i + j] = a0 + a1, a[i + j + len] = a0 - a1;
            }
        }
    }
}
inline void IFFT(CP *a, int n) {
    FFT(a, n, -1);
    for (int i = 0; i < n; i++) a[i].re = a[i].re / n + 0.5;
}
int main() {
    n = read(), m = read();
    for (int i = 0; i <= n; i++) a[i].re = read();
    for (int i = 0; i <= m; i++) b[i].re = read();
    int len = 1;
    while (len <= n + m) len <<= 1;
    init(len);
    FFT(a, len, 1), FFT(b, len, 1);
    for (int i = 0; i < len; i++) a[i] = a[i] * b[i];
    IFFT(a, len);
    for (int i = 0; i <= n + m; i++) write(a[i].re), putchar(' ');
    return 0;
}