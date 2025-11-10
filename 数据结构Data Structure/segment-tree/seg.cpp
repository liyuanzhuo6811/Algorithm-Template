#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
struct Tag {
    Tag operator+(const Tag &b) const {}
    bool operator==(const Tag &b) const {}
} T0;
struct info {
    info operator+(const info &b) const {}
    info operator+(const Tag &b) const {}
} I0;
struct treenode {
    int pl, pr;
    info i = I0;
    Tag t = T0;
} tr[N << 2];
inline void up(int p) { tr[p].i = tr[p << 1].i + tr[p << 1 | 1].i; }
inline void pt(int p, Tag t) { tr[p].i = tr[p].i + t, tr[p].t = tr[p].t + t; }
inline void spread(int p) {
    if (tr[p].t == T0) return;
    pt(p << 1, tr[p].t), pt(p << 1 | 1, tr[p].t);
    tr[p].t = T0;
}
inline void build(int p, int pl, int pr) {
    tr[p].pl = pl, tr[p].pr = pr;
    if (pl == pr) return;
    int mid = (pl + pr) >> 1;
    build(p << 1, pl, mid), build(p << 1 | 1, mid + 1, pr);
    up(p);
}
inline void update(int p, int L, int R, Tag t) {
    if (L <= tr[p].pl && tr[p].pr <= R) return pt(p, t);
    int mid = (tr[p].pl + tr[p].pr) >> 1;
    spread(p);
    if (L <= mid) update(p << 1, L, R, t);
    if (R > mid) update(p << 1 | 1, L, R, t);
    up(p);
}
inline info query(int p, int L, int R) {
    if (L <= tr[p].pl && tr[p].pr <= R) return tr[p].i;
    int mid = (tr[p].pl + tr[p].pr) >> 1;
    spread(p);
    info res = I0;
    if (L <= mid) res = res + query(p << 1, L, R);
    if (R > mid) res = res + query(p << 1 | 1, L, R);
    return res;
}
int main() { return 0; }
