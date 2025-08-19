#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
const int N = 5e5 + 10, M = 2e6 + 10;
int n, m, head[N], tot = 1;
struct edge
{
 int v, nxt;
 bool is_bridge;
} e[M << 1];
void add(int u, int v) { e[++tot].v = v, e[tot].nxt = head[u], head[u] = tot; }
int dfn[N], low[N], Time;
void tarjan(int u, int edge)
{
 dfn[u] = low[u] = ++Time;
 for (int i = head[u]; i; i = e[i].nxt)
 {
  int v = e[i].v;
  if (!dfn[v]) { tarjan(v, i), low[u] = min(low[u], low[v]); }
  else if (i != (edge ^ 1)) low[u] = min(low[u], dfn[v]);
  if (dfn[u] < low[v]) e[i].is_bridge = e[i ^ 1].is_bridge = true;
 }
}
int dc;
bool in_dcc[N];
vector<int> DCC[N];
void dfs(int u, int dc)
{
 in_dcc[u] = true;
 DCC[dc].push_back(u);
 for (int i = head[u]; i; i = e[i].nxt)
 {
  int v = e[i].v;
  if (in_dcc[v] || e[i].is_bridge) continue;
  dfs(v, dc);
 }
}
int main()
{
 ios::sync_with_stdio(false);
 cin.tie(0), cout.tie(0);
 cin >> n >> m;
 for (int i = 1; i <= m; i++)
 {
  int u, v;
  cin >> u >> v;
  add(u, v);
  add(v, u);
 }
 for (int i = 1; i <= n; i++)
  if (!dfn[i]) tarjan(i, 0);
 for (int i = 1; i <= n; i++)
  if (!in_dcc[i]) dfs(i, ++dc);
 cout << dc << "\n";
 for (int i = 1; i <= dc; i++)
 {
  cout << DCC[i].size() << " ";
  for (auto v : DCC[i]) cout << v << " ";
  cout << "\n";
 }
 return 0;
}