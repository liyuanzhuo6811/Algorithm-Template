#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
using namespace std;
namespace fr {
constexpr int L = (1 << 21);
char buf[L], obuf[L], *p1 = buf, *p2 = buf, *O = obuf;
#define gc() ((p1==p2 && (p2=(p1=buf)+fread(buf,1,L,stdin),p1==p2))?EOF:(*(p1++)))
#define prc(c) (((O==(obuf+L))?(fwrite(obuf,1,O-obuf,stdout),O=obuf):(0)),(*(O++))=(c))
template<typename T>
void rd(T &x) {
    bool flg = false;
    x = 0;
    char c = gc();

    while (isspace(c))
        c = gc();

    if (c == '-')
        flg = true, c = gc();

    while (isdigit(c))
        x = x * 10 + c - '0', c = gc();

    if (flg)
        x = -x;
}
void rd(char *&x) {
    char c = gc();

    while (isspace(c))
        c = gc();

    while (!isspace(c))
        (*(x++)) = c, c = gc();

    (*(x++)) = '\0';
}
template<typename T>
void wr(T x) {
    static char stk[40];
    int top = 0;

    if (x == 0) {
        prc('0');
        return;
    }

    if (x < 0)
        x = -x, prc('-');

    while (x)
        stk[top++] = int(x % 10) + '0', x /= 10;

    for (int i = top - 1; i >= 0; --i)
        prc(stk[i]);
}
void wr(const char *s) {
    int len = strlen(s);

    for (int i = 0; i < len; ++i)
        prc(s[i]);
}
void pc(char s) {
    prc(s);
}
void flush() {
    fwrite(obuf, 1, O - obuf, stdout);
    O = obuf;
}
}
using fr::rd;
using fr::wr;
using fr::pc;
using fr::flush;
namespace max_flow {
constexpr int N = 210, M = 11010;
int hd[N], nxt[M << 1], tv[M << 1], ecnt = 1, cur[N], tag[N];
long long w[M << 1];
void _add_edge(int u, int v, long long w0) {
    nxt[++ecnt] = hd[u];
    tv[ecnt] = v;
    w[ecnt] = w0;
    hd[u] = ecnt;
}
void add_edge(int u, int v, long long w0) {
    _add_edge(u, v, w0);
    _add_edge(v, u, 0);
}
bool bfs(int s, int t, int tot) {
    static int qq[N];
    int l = 0, r = 0;
    qq[r++] = s;
    memset(tag, 0, sizeof(int) * (tot + 1));
    tag[s] = 1;

    while (l < r) {
        int u = qq[l++];

        for (int tp = hd[u]; tp; tp = nxt[tp])
            if (w[tp] && !tag[tv[tp]]) {
                qq[r++] = tv[tp];
                tag[tv[tp]] = tag[u] + 1;
            }
    }

    return tag[t] != 0;
}
long long dfs(int u, int t, long long fl) {
    if (u == t)
        return fl;

    long long ret = 0;

    for (int &tp = cur[u]; tp; tp = nxt[tp])
        if (w[tp] && tag[tv[tp]] == tag[u] + 1) {
            auto k = dfs(tv[tp], t, min<long long>(fl, w[tp]));
            w[tp] -= k;
            w[tp ^ 1] += k;
            ret += k;
            fl -= k;

            if (!fl)
                break;
        }

    return ret;
}
long long dinic(int s, int t, int tot) {
    long long ans = 0;

    while (bfs(s, t, tot)) {
        memcpy(cur, hd, sizeof(int) * (tot + 1));
        ans += dfs(s, t, (long long)1e18);
    }

    return ans;
}
}
#include <tuple>
#include <vector>
constexpr int N = 210, M = 11010;
long long d[N];
int b[M];
int main() {
    int n, m, s, t;
    rd(n);
    rd(m);
    rd(s);
    rd(t);

    for (int i = 1, u, v, lw, up; i <= m; ++i) {
        rd(u);
        rd(v);
        rd(lw);
        rd(up);
        d[u] -= lw;
        d[v] += lw;
        max_flow::add_edge(u, v, up - lw);
    }

    long long tot = 0;
    int S = n + 1, T = S + 1;

    for (int i = 1; i <= n; ++i) {
        if (d[i] > 0) {
            tot += d[i];
            max_flow::add_edge(S, i, d[i]);
        } else {
            max_flow::add_edge(i, T, -d[i]);
        }
    }

    max_flow::add_edge(t, s, 1e17);
    auto res = max_flow::dinic(S, T, T);

    if (res != tot) {
        wr("please go home to sleep\n");
    } else {
        for (int i = m + 1; i < max_flow::ecnt / 2; ++i)
            max_flow::w[i << 1] = max_flow::w[i << 1 | 1] = 0;

        auto ans = max_flow::dinic(s, t, n);
        ans += max_flow::w[max_flow::ecnt];
        wr(ans);
        pc('\n');
    }

    flush();
    return 0;
}