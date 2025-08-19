#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
const int N = 500005;
const int M = 2000005;
int n, m, head[N], tot;
struct edge
{
 int v, nxt;
} e[M << 1];
void add(int u, int v)
{
 e[++tot].v = v;
 e[tot].nxt = head[u];
 head[u] = tot;
}
int dfn[N], low[N], Time;
vector<int> dcc[N];
int cnt, stk[N], top;
void tarjan(int u, int rt)
{
 dfn[u] = low[u] = ++Time, stk[++top] = u;
 if (u == rt && head[u] == 0)
 {
  dcc[++cnt].push_back(u);
  return;
 }
 for (int i = head[u]; i; i = e[i].nxt)
 {
  int v = e[i].v;
  if (!dfn[v])
  {
   tarjan(v, rt);
   low[u] = min(low[u], low[v]);
   if (dfn[u] <= low[v])
   {
    ++cnt;
    do {
     dcc[cnt].push_back(stk[top--]);
    } while (stk[top + 1] != v);
    dcc[cnt].push_back(u);
   }
  }
  else low[u] = min(low[u], dfn[v]);
 }
}
int main()
{
 cin.tie(0)->sync_with_stdio(false);
 cout.tie(0);
 cin >> n >> m;
 for (int i = 1; i <= m; i++)
 {
  int u, v;
  cin >> u >> v;
  if (u == v) continue;
  add(u, v);
  add(v, u);
 }
 for (int i = 1; i <= n; i++)
  if (!dfn[i]) tarjan(i, i);
 cout << cnt << "\n";
 for (int i = 1; i <= cnt; i++)
 {
  cout << dcc[i].size() << " ";
  for (auto x : dcc[i]) cout << x << " ";
  cout << "\n";
 }
 return 0;
}