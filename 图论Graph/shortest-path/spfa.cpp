#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n, m;
vector<pair<int, int>> g[N];
inline void add(int u, int v, int w) { g[u].push_back({v, w}); }
queue<int> q;
int dis[N];
bool inq[N];
inline void spfa(int s)
{
 memset(dis, 0x3f, sizeof(dis));
 memset(inq, false, sizeof(inq));
 inq[s] = true, dis[s] = 0;
 q.push(s);
 while (q.size())
 {
  int u = q.front();
  q.pop(), inq[u] = false;
  for (auto [v, w] : g[u])
   if (dis[v] > dis[u] + w)
   {
    dis[v] = dis[u] + w;
    if (!inq[v]) q.push(v);
   }
 }
}
int main()
{
 cin >> n >> m;
 for (int i = 1, u, v, w; i <= m; i++) cin >> u >> v >> w, add(u, v, w), add(v, u, w);
 spfa(1);
 return 0;
}