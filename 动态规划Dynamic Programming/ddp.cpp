// {"name":"ddp","intro":"动态 dp"}
#include <bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
#define pn putchar(10)
#define fi first
#define se second
#define pp putchar(' ')
#define pii pair<int, int>
#define pdi pair<ll, ll>
#define mem(aa, bb) memset(aa, bb, sizeof(aa))
#define fo(i, a, b) for (int i = (a); i <= (b); ++i)
#define Fo(i, a, b) for (int i = (a); i >= (b); --i)
#define pb push_back
#define reg register
#define eb emplace_back
#define bct __builtin_popcount
#define mk make_pair
#define IT iterator
#define all(x) x.begin(), x.end()
#define lbd lower_bound
#define ubd upper_bound
#define lowbit(x) (x & (-x))
#define gb(x, i) ((x >> i) & 1)
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
// #pragma GCC optimize(2)
using namespace std;

typedef int32_t i32;
typedef int64_t i64;
typedef uint32_t u32;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef double db;
typedef long long ll;

#ifdef UNLINEJUDGE
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif

template <class T> inline bool ckmn(T &a, T b) {
    return a > b ? a = b, 1 : 0;
}
template <class T> inline bool ckmx(T &a, T b) {
    return a < b ? a = b, 1 : 0;
} // clang-format off
template <class T> inline void read(T &s)
{
 s = 0; int f = 1; char c = getchar(); while (!isdigit(c)) { if (c == '-') { f = -1; } c = getchar(); }
 while (isdigit(c)) { s = (s << 3) + (s << 1) + (c ^ 48), c = getchar(); } s *= f; return;
}
template <class T> inline void wr(T x) 
{ 
 if (x < 0) { putchar('-'), x = -x; } int buf[21], top = 0; while (x) { buf[++top] = x % 10, x /= 10; }
 if (!top) { buf[++top] = 0; } while (top) { putchar(buf[top--] ^ '0'); } return; 
}
template <class T, class... A> inline void read(T &x, A &...a) { read(x), read(a...); } // clang-format on
template <class T, class... A> inline bool ckmn(T &x, T y, A... a) {
    return ckmn(x, y) | ckmn(x, a...);
}
template <class T, class... A> inline bool ckmx(T &x, T y, A... a) {
    return ckmx(x, y) | ckmx(x, a...);
}

const int N = 1e6 + 5;
int n, m, a[N];
inline int my_max(int a, int b) { return a > b ? a : b; }
struct Matrix {
    int a[2][2];
    inline Matrix operator*(const Matrix &b) const {
        Matrix c;
        c.a[0][0] = my_max(a[0][0] + b.a[0][0], a[0][1] + b.a[1][0]);
        c.a[0][1] = my_max(a[0][0] + b.a[0][1], a[0][1] + b.a[1][1]);
        c.a[1][0] = my_max(a[1][0] + b.a[0][0], a[1][1] + b.a[1][0]);
        c.a[1][1] = my_max(a[1][0] + b.a[0][1], a[1][1] + b.a[1][1]);
        return c;
    }
} trans[N];
int head[N], Tot = 1;
struct edge {
    int v, nxt;
} e[N << 1];
inline void add(int u, int v) {
    e[++Tot] = {v, head[u]}, head[u] = Tot;
}
int fa[N], dep[N], siz[N], hson[N], top[N], bot[N], dfn[N], id[N],
    idx;
inline void dfs1(int u, int pa) {
    fa[u] = pa, dep[u] = dep[pa] + 1, siz[u] = 1;
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if (v == pa) continue;
        dfs1(v, u), siz[u] += siz[v];
        if (siz[v] > siz[hson[u]]) hson[u] = v;
    }
}
int f[N][2], g[N][2];
inline void dfs2(int u, int tp) {
    top[u] = tp, dfn[u] = ++idx, bot[tp] = idx, id[idx] = u;
    f[u][0] = g[u][0] = 0, f[u][1] = g[u][1] = a[u];
    if (hson[u]) {
        dfs2(hson[u], tp);
        f[u][0] += my_max(f[hson[u]][0], f[hson[u]][1]),
            f[u][1] += f[hson[u]][0];
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].v;
            if (v == fa[u] || v == hson[u]) continue;
            dfs2(v, v);
            f[u][0] += my_max(f[v][0], f[v][1]), f[u][1] += f[v][0];
            g[u][0] += my_max(f[v][0], f[v][1]), g[u][1] += f[v][0];
        }
    }
    trans[u].a[0][0] = g[u][0], trans[u].a[0][1] = g[u][0];
    trans[u].a[1][0] = g[u][1], trans[u].a[1][1] = -inf;
}
Matrix tr[N << 2];
int lc[N << 2], rc[N << 2], nodecnt, rt[N];
inline void up(int p) { tr[p] = tr[lc[p]] * tr[rc[p]]; }
inline void build(int &p, int pl, int pr) {
    p = ++nodecnt;
    if (pl == pr) return tr[p] = trans[id[pl]], void();
    int mid = (pl + pr) >> 1;
    build(lc[p], pl, mid), build(rc[p], mid + 1, pr), up(p);
}
inline void update(int p, int pl, int pr, int pos) {
    if (pl == pr) return tr[p] = trans[id[pl]], void();
    int mid = (pl + pr) >> 1;
    pos <= mid ? update(lc[p], pl, mid, pos)
               : update(rc[p], mid + 1, pr, pos);
    up(p);
}
inline void update_chain(int x, int val) {
    trans[x].a[1][0] += val - a[x], a[x] = val;
    while (x) {
        Matrix last = tr[rt[top[x]]];
        update(rt[top[x]], dfn[top[x]], bot[top[x]], dfn[x]);
        Matrix now = tr[rt[top[x]]];
        x = fa[top[x]];
        trans[x].a[0][0] += my_max(now.a[0][0], now.a[1][0]) -
                            my_max(last.a[0][0], last.a[1][0]);
        trans[x].a[0][1] = trans[x].a[0][0];
        trans[x].a[1][0] += now.a[0][0] - last.a[0][0];
    }
}
inline void solve() {
    read(n, m);
    fo(i, 1, n) read(a[i]);
    for (int i = 1, u, v; i < n; ++i)
        read(u, v), add(u, v), add(v, u);
    dfs1(1, 0), dfs2(1, 1);
    fo(i, 1, n) if (top[i] == i) build(rt[i], dfn[i], bot[i]);
    int lastans = 0, x, val;
    fo(i, 1, m) {
        read(x, val), x ^= lastans;
        update_chain(x, val);
        Matrix ans = tr[rt[1]];
        lastans = max(ans.a[0][0], ans.a[1][0]);
        wr(lastans), pn;
    }
}
i32 main() {
    auto begin = chrono::high_resolution_clock::now();
    int T = 1; // read(T);
    while (T--) solve();
    auto end = chrono::high_resolution_clock::now();
    auto elapsed =
        chrono::duration_cast<chrono::nanoseconds>(end - begin);
    cerr << "Time measured: " << elapsed.count() * 1e-9
         << " seconds.\n";
    return 0;
}
