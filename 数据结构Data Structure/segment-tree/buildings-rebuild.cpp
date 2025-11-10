#include <stdbool.h>
#include <stdio.h>
#define N 100005
#define ls(p) (p << 1)
#define rs(p) (p << 1 | 1)
#define max(a, b) ((a) > (b) ? (a) : (b))
#define rep(i, s, t) for (int i = (s); i <= (t); i++)
#define per(i, s, t) for (int i = (s); i >= (t); i--)
int n, m;
int c[N << 2];
double mx[N << 2];
int calc(int p, int pl, int pr, double v) {
    if (v >= mx[p]) return 0;
    if (pl == pr) return (mx[p] > v);
    int mid = (pl + pr) >> 1;
    if (mx[ls(p)] <= v) return calc(rs(p), mid + 1, pr, v);
    else return calc(ls(p), pl, mid, v) + c[p] - c[ls(p)];
}
void update(int p, int pl, int pr, int pos, int v) {
    if (pl == pr) {
        mx[p] = 1.0 * v / pos, c[p] = 1;
        return;
    }
    int mid = (pl + pr) >> 1;
    if (pos <= mid) update(ls(p), pl, mid, pos, v);
    else update(rs(p), mid + 1, pr, pos, v);
    mx[p] = max(mx[ls(p)], mx[rs(p)]);
    c[p] = c[ls(p)] + calc(rs(p), mid + 1, pr, mx[ls(p)]);
}
int main() {
    scanf("%d%d", &n, &m);
    while (m--) {
        int x, y;
        scanf("%d%d", &x, &y);
        update(1, 1, n, x, y);
        printf("%d\n", c[1]);
    }
    return 0;
}
