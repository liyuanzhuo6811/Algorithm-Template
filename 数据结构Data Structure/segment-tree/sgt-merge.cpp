#include <cstdio>
#include <iostream>
using namespace std;
const int N = 100005, M = 100000;
int n, m, head[N], tot, ans[N];
struct edge
{
 int v, nxt;
} e[N << 1];
inline void add(int u, int v)
{
 e[++tot].v = v;
 e[tot].nxt = head[u];
 head[u] = tot;
}
int fa[N], dep[N], siz[N], hson[N], dfn[N], top[N], Time;
void dfs1(int u, int fath)
{
 fa[u] = fath, dep[u] = dep[fath] + 1, siz[u] = 1;
 for (int i = head[u]; i; i = e[i].nxt)
 {
  int v = e[i].v;
  if (v == fath) continue;
  dfs1(v, u);
  siz[u] += siz[v];
  if (!hson[u] || siz[v] > siz[hson[u]]) hson[u] = v;
 }
}
void dfs2(int u, int tp)
{
 top[u] = tp, dfn[u] = ++Time;
 if (hson[u]) dfs2(hson[u], tp);
 for (int i = head[u]; i; i = e[i].nxt)
  if (e[i].v != fa[u] && e[i].v != hson[u]) dfs2(e[i].v, e[i].v);
}
inline int LCA(int x, int y)
{
 while (top[x] != top[y])
 {
  if (dep[top[x]] < dep[top[y]]) swap(x, y);
  x = fa[top[x]];
 }
 return dep[x] <= dep[y] ? x : y;
}
int cnt = 0, rt[N];
struct node
{
 int mx, id;
 int ls, rs;
} t[N * 100];
void pushup(int p)
{
 if (t[t[p].ls].mx >= t[t[p].rs].mx) t[p].mx = t[t[p].ls].mx, t[p].id = t[t[p].ls].id;
 else t[p].mx = t[t[p].rs].mx, t[p].id = t[t[p].rs].id;
}
void update(int &p, int pl, int pr, int k, int val)
{
 if (!p) p = ++cnt;
 if (pl == pr)
 {
  t[p].mx += val, t[p].id = k;
  return;
 }
 int mid = (pl + pr) >> 1;
 if (k <= mid) update(t[p].ls, pl, mid, k, val);
 else update(t[p].rs, mid + 1, pr, k, val);
 pushup(p);
}
int merge(int &L, int &R, int pl, int pr)
{
 if (!L) return R;
 if (!R) return L;
 if (pl == pr)
 {
  t[L].mx += t[R].mx;
  return L;
 }
 int mid = (pl + pr) >> 1;
 t[L].ls = merge(t[L].ls, t[R].ls, pl, mid);
 t[L].rs = merge(t[L].rs, t[R].rs, mid + 1, pr);
 pushup(L);
 return L;
}
void dfs(int u)
{
 for (int i = head[u]; i; i = e[i].nxt)
 {
  int v = e[i].v;
  if (v == fa[u]) continue;
  dfs(v);
  rt[u] = merge(rt[u], rt[v], 1, M);
 }
 ans[u] = t[rt[u]].id;
 if (!t[rt[u]].mx) ans[u] = 0;
}
int main()
{
 ios::sync_with_stdio(false);
 cin.tie(0);
 cout.tie(0);
 cin >> n >> m;
 for (int i = 1; i < n; i++)
 {
  int u, v;
  cin >> u >> v;
  add(u, v);
  add(v, u);
 }
 dfs1(1, 0);
 dfs2(1, 1);
 while (m--)
 {
  int l, r, z;
  cin >> l >> r >> z;
  update(rt[l], 1, M, z, 1);
  update(rt[r], 1, M, z, 1);
  int lca = LCA(l, r);
  update(rt[lca], 1, M, z, -1);
  update(rt[fa[lca]], 1, M, z, -1);
 }
 dfs(1);
 for (int i = 1; i <= n; i++) cout << ans[i] << "\n";
 return 0;
}