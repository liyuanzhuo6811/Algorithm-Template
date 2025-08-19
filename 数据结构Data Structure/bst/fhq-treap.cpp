#include <bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int N = 1e5 + 10;
int n, rt, L, R, p, cnt;
struct node
{
 int ls, rs, val, pri, siz;
 node() {}
 node(int _l, int _r, int _v, int _p, int _s) { ls = _l, rs = _r, val = _v, pri = _p, siz = _s; }
} t[N];
void pushup(int u) { t[u].siz = t[t[u].ls].siz + t[t[u].rs].siz + 1; }
void newnode(int x) { t[++cnt] = node(0, 0, x, rng(), 1); }
void split(int u, int x, int &L, int &R)
{
 if (!u) return L = R = 0, void();
 if (t[u].val <= x) L = u, split(t[u].rs, x, t[u].rs, R);
 else R = u, split(t[u].ls, x, L, t[u].ls);
 pushup(u);
}
int merge(int L, int R)
{
 if (!L || !R) return L | R;
 if (t[L].pri <= t[R].pri) return t[L].rs = merge(t[L].rs, R), pushup(L), L;
 else return t[R].ls = merge(L, t[R].ls), pushup(R), R;
}
inline void Insert(int x) { newnode(x), split(rt, x, L, R), rt = merge(merge(L, cnt), R); }
inline void Delete(int x)
{
 split(rt, x - 1, L, R), split(R, x, p, R);
 p = merge(t[p].ls, t[p].rs), rt = merge(merge(L, p), R);
}
inline int get_rank(int x)
{
 split(rt, x - 1, L, R);
 int y = t[L].siz + 1;
 rt = merge(L, R);
 return y;
}
inline int get_val(int u, int k)
{
 int now = u;
 while (now)
 {
  int x = t[t[now].ls].siz + 1;
  if (x == k) return t[now].val;
  if (x < k) now = t[now].rs, k -= x;
  else now = t[now].ls;
 }
}
inline int get_pre(int x)
{
 split(rt, x - 1, L, R);
 int y = get_val(L, t[L].siz);
 rt = merge(L, R);
 return y;
}
inline int get_nxt(int x)
{
 split(rt, x, L, R);
 int y = get_val(R, 1);
 rt = merge(L, R);
 return y;
}
signed main() { return 0; }