#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int N = 10005, M = 100005;
int n, m, head[M], tot;
struct edge
{
 int v, nxt;
} e[M];
void add(int u, int v)
{
 e[++tot].v = v;
 e[tot].nxt = head[u];
 head[u] = tot;
}
int dfn[N], low[N];
int stk[N], top, Time;
bool ins[N], vis[N];
int fa[N], cnt;
vector<vector<int>> SCC;
void tarjan(int u)
{
 dfn[u] = ++Time, low[u] = dfn[u], stk[++top] = u, ins[u] = true;
 for (int i = head[u]; i; i = e[i].nxt)
 {
  int v = e[i].v;
  if (!dfn[v])
  {
   tarjan(v);
   low[u] = min(low[u], low[v]);
  }
  else if (ins[v]) low[u] = min(low[u], dfn[v]);
 }
 if (dfn[u] == low[u])
 {
  ++cnt;
  SCC.push_back(vector<int>());
  while (stk[top] != u)
  {
   SCC[cnt].push_back(stk[top]);
   fa[stk[top]] = cnt, ins[stk[top]] = false, top--;
  }
  SCC[cnt].push_back(stk[top]);
  fa[stk[top]] = cnt, ins[stk[top]] = false, top--;
 }
}
int main()
{
 ios::sync_with_stdio(false);
 cin.tie(0);
 cout.tie(0);
 cin >> n >> m;
 for (int i = 1; i <= m; i++)
 {
  int u, v;
  cin >> u >> v;
  add(u, v);
 }
 SCC.push_back(vector<int>());
 for (int i = 1; i <= n; i++)
  if (!dfn[i]) tarjan(i);
 cout << cnt << "\n";
 for (int i = 1; i <= cnt; i++) sort(SCC[i].begin(), SCC[i].end());
 for (int i = 1; i <= n; i++)
 {
  if (vis[fa[i]]) continue;
  else
  {
   for (auto x : SCC[fa[i]]) cout << x << " ";
   cout << "\n";
   vis[fa[i]] = true;
  }
 }
 return 0;
}