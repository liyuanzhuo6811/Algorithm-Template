// g 是原图，g2 是反图
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
vector<vector<int>> g, g2;
vector<int> s;
bool vis[N];
int sccCnt, n, color[N];
void dfs1(int u)
{
 vis[u] = true;
 for (int v : g[u])
  if (!vis[v]) dfs1(v);
 s.push_back(u);
}
void dfs2(int u)
{
 color[u] = sccCnt;
 for (int v : g2[u])
  if (!color[v]) dfs2(v);
}
void kosaraju()
{
 sccCnt = 0;
 for (int i = 1; i <= n; ++i)
  if (!vis[i]) dfs1(i);
 for (int i = n; i >= 1; --i)
  if (!color[s[i]])
  {
   ++sccCnt;
   dfs2(s[i]);
  }
}