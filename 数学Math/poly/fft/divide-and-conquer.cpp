// {"name": "快速傅里叶变换", "intro": "递归实现"}
#include <cmath>
#include <cstdio>
#define MAXN 4000005
using namespace std;
int n, m;
const double PI = acos(-1.0);
struct CP {
    CP(double xx = 0, double yy = 0) { x = xx, y = yy; }
    double x, y;
    CP operator+(const CP &B) const { return CP(x + B.x, y + B.y); }
    CP operator-(const CP &B) const { return CP(x - B.x, y - B.y); }
    CP operator*(const CP &B) const { return CP(x * B.x - y * B.y, x * B.y + y * B.x); }
} f[MAXN], g[MAXN], sav[MAXN];
void FFT(CP *f, int limit, int type) {
    if (limit == 1) return;
    CP *fl = f, *fr = f + limit / 2;
    for (int i = 0; i < limit; i++) sav[i] = f[i];
    for (int i = 0; i < limit / 2; i++) fl[i] = sav[i << 1], fr[i] = sav[i << 1 | 1];
    FFT(fl, limit / 2, type);
    FFT(fr, limit / 2, type);
    CP Omega(cos(2.0 * PI / limit), type * sin(2.0 * PI / limit)), w(1, 0);
    for (int i = 0; i < limit / 2; i++, w = w * Omega)
        sav[i] = fl[i] + fr[i] * w, sav[i + limit / 2] = fl[i] - fr[i] * w;
    for (int i = 0; i < limit; i++) f[i] = sav[i];
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; i++) scanf("%lf", &f[i].x);
    for (int i = 0; i <= m; i++) scanf("%lf", &g[i].x);
    m += n, n = 1;
    while (n <= m) n <<= 1;
    FFT(f, n, 1), FFT(g, n, 1);
    for (int i = 0; i < n; i++) f[i] = f[i] * g[i];
    FFT(f, n, -1);
    for (int i = 0; i <= m; i++) printf("%d ", (int)(f[i].x / n + 0.5));
    return 0;
}