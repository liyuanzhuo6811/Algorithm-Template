#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5;
int n, m, fa[N], ch[N][2], val[N], tag[N], sum[N];
inline int get(int p) { return ch[fa[p]][1] == p; }
inline bool is_root(int p) { return ch[fa[p]][0] != p && ch[fa[p]][1] != p; }
inline void pushup(int p) { sum[p] = sum[ch[p][0]] ^ val[p] ^ sum[ch[p][1]]; }
inline void reverse(int p) { swap(ch[p][0], ch[p][1]), tag[p] ^= 1; }
inline void pushdown(int p)
{
 if (!tag[p]) return;
 reverse(ch[p][0]), reverse(ch[p][1]), tag[p] = 0;
}
inline void push(int p)
{
 if (!is_root(p)) push(fa[p]);
 pushdown(p);
}
inline void rotate(int p)
{
 int f = fa[p], g = fa[f], k = get(p);
 if (!is_root(f)) ch[g][get(f)] = p;
 ch[f][k] = ch[p][k ^ 1], fa[ch[p][k ^ 1]] = f;
 ch[p][k ^ 1] = f, fa[f] = p, fa[p] = g;
 pushup(f), pushup(p);
}
void splay(int p)
{
 push(p);
 for (int f; f = fa[p], !is_root(p); rotate(p))
  if (!is_root(f)) rotate(get(p) == get(f) ? f : p);
}
inline void access(int p)
{
 for (int child = 0; p; child = p, p = fa[p]) splay(p), ch[p][1] = child, pushup(p);
}
inline void makeroot(int p) { access(p), splay(p), reverse(p); }
inline void split(int u, int v) { makeroot(u), access(v), splay(v); }
inline int findroot(int p)
{
 access(p), splay(p), pushdown(p);
 while (ch[p][0]) p = ch[p][0], pushdown(p);
 return splay(p), p;
}
inline void link(int u, int v) { makeroot(u), fa[u] = v; }
inline void cut(int u, int v)
{
 makeroot(u);
 if (findroot(v) == u && fa[v] == u && !ch[v][0]) fa[v] = ch[u][1] = 0, pushup(u);
}
int main()
{
 cin.tie(0)->sync_with_stdio(false);
 cout.tie(0);
 cin >> n >> m;
 for (int i = 1; i <= n; i++) cin >> val[i];
 for (int op, x, y; m--;)
 {
  cin >> op >> x >> y;
  switch (op)
  {
  case 0: split(x, y), cout << sum[y] << '\n'; break;
  case 1:
   if (findroot(x) != findroot(y)) link(x, y);
   break;
  case 2: cut(x, y); break;
  case 3: splay(x), val[x] = y; break;
  }
 }
 return 0;
}
