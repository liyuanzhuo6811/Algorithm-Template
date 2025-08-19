#include <bits/stdc++.h>
using namepace std;
const int N = 1e5 + 5;
int n;
vector<int> g[N];
int fa[N], dep[N], siz[N], hson[N], dfn[N], idx, top[N];
void hld1(int u, int fath)
{
 fa[u] = fath, dep[u] = dep[fath] + 1, siz[u] = 1;
 for (int v : g[u])
 {
  if (v == fath) continue;
  hld1(v, u), siz[u] += siz[v];
  if (siz[v] > siz[hson[u]]) hson[u] = v;
 }
}
void hld2(int u, int nowtp)
{
 top[u] = nowtp, dfn[u] = ++idx;
 if (hson[u]) hld2(hson[u], nowtp);
 for (int v : g[u])
  if (v != fa[u] && v != hson[u]) hld2(v, v);
}
inline int LCA(int x, int y)
{
 while (top[x] != top[y]) return dep[top[x]] < dep[top[y]] ? y = fa[top[y]] : x = fa[top[x]];
 return dep[x] < dep[y] ? x : y;
}
int main() { return 0; }