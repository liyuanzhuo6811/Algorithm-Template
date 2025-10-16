// {"name":"<线段树分治>","intro":"<看到相关的题就用>"}
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5, M = 2e5 + 5;
int n, m, k;
bool ans[N];
struct edge
{
 int u, v;
} e[M];
vector<edge> tr[N << 2];
inline void insert(int p, int pl, int pr, int L, int R, edge e)
{
 if (L <= pl && pr <= R) return tr[p].push_back(e), void();
 int mid = (pl + pr) >> 1;
 if (L <= mid) insert(p << 1, pl, mid, L, R, e);
 if (R > mid) insert(p << 1 | 1, mid + 1, pr, L, R, e);
}
int fa[N << 1], height[N << 1], top;
struct DSU_edge
{
 int x, y, deltah;
} st[N << 1];
inline int getf(int x)
{
 while (x ^ fa[x]) x = fa[x];
 return fa[x];
}
inline void merge(int x, int y)
{
 int fx = getf(x), fy = getf(y);
 if (fx == fy) return;
 if (height[fx] > height[fy]) swap(fx, fy);
 fa[fx] = fy, st[++top] = {fx, fy, height[fx] == height[fy]};
 if (height[fy] == height[fx]) ++height[fy];
}
void solve(int p, int pl, int pr)
{
 bool flg = 1;
 int cnt = 0;
 for (edge E : tr[p])
 {
  int u = E.u, v = E.v;
  if (getf(u) == getf(v))
  {
   for (int i = pl; i <= pr; ++i) ans[i] = false;
   flg = false;
   break;
  }
  if (getf(u) != getf(v + n)) ++cnt, merge(u, v + n);
  if (getf(v) != getf(u + n)) ++cnt, merge(v, u + n);
 }
 if (flg && pl != pr)
 {
  int mid = (pl + pr) >> 1;
  solve(p << 1, pl, mid), solve(p << 1 | 1, mid + 1, pr);
 }
 while (cnt--)
 {
  DSU_edge now = st[top--];
  fa[now.x] = now.x, height[now.y] -= now.deltah;
 }
}
signed main()
{
 cin.tie(0)->sync_with_stdio(false);
 cout.tie(0);
 cin >> n >> m >> k;
 for (int i = 1; i <= n * 2; ++i) fa[i] = i, height[i] = 1;
 for (int i = 1, l, r; i <= m; ++i)
 {
  cin >> e[i].u >> e[i].v >> l >> r;
  if (l ^ r) insert(1, 1, k, l + 1, r, e[i]);
 }
 for (int i = 1; i <= k; ++i) ans[i] = true;
 solve(1, 1, k);
 for (int i = 1; i <= k; ++i) cout << (ans[i] ? "Yes" : "No") << "\n";
 return 0;
}