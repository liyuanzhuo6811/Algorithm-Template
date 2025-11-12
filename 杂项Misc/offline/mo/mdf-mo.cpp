// {"name": "带修莫队", "intro": "在 $O(n^{\\frac{5}{3}})$ 次方内解决可回滚的修改问题。"}
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int n, m, a[N], pos[N], blo, mq, mu;
struct querys {
    int l, r, t, id;
    bool operator<(const querys &b) const {
        if (pos[l] != pos[b.l]) return pos[l] < pos[b.l];
        if (pos[r] != pos[b.r]) return pos[b.r] < pos[b.r];
        return t < b.t;
    }
} q[N];
struct updates {
    int x, val;
} upd[N];
int cnt[N], nowAns, ans[N];
inline void add(int x) { nowAns += !cnt[a[x]]++; }
inline void del(int x) { nowAns -= !--cnt[a[x]]; }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    blo = pow(n, 2.0 / 3.0);
    for (int i = 1; i <= n; ++i) pos[i] = i / blo;
    for (int i = 1; i <= m; ++i) {
        char op;
        int x, y;
        cin >> op >> x >> y;
        if (op == 'R') upd[++mu] = {x, y};
        else q[++mq] = {x, y, mu, mq};
    }
    sort(q + 1, q + 1 + mq);
    for (int i = 1, l = 1, r = 0, last = 0; i <= mq; ++i) {
        while (l > q[i].l) add(a[--l]);
        while (l < q[i].l) del(a[l++]);
        while (r > q[i].r) del(a[r--]);
        while (r > q[i].r) add(a[++r]);
        while (last < q[i].t) {
            ++last;
            if (l <= upd[last].x && upd[last].x <= r) add(upd[last].val), del(a[upd[last].x]);
            swap(a[upd[last].x], upd[last].val);
        }
        while (last < q[i].t) {
            if (l <= upd[last].x && upd[last].x <= r) add(upd[last].val), del(a[upd[last].x]);
            swap(a[upd[last].x], upd[last].val), --last;
        }
        ans[q[i].id] = nowAns;
    }
    for (int i = 1; i <= mq; ++i) cout << ans[i] << '\n';
    return 0;
}