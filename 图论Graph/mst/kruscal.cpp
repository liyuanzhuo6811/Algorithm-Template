#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
struct E
{
 int u, v, w;
 bool operator<(const E &b) const { return w < b.w; }
} Edge[N];
int f[N];
int getf(int x) { return f[x] == x ? x : f[x] = getf(f[x]); }
vector<int> tr[N];
int main()
{
 int n, m;
 cin >> n >> m;
 for (int i = 1; i <= n; i++) f[i] = i;
 for (int i = 1; i <= m; i++) cin >> Edge[i].u >> Edge[i].v >> Edge[i].w;
 sort(Edge + 1, Edge + 1 + m);
 for (int i = 1; i <= m; i++)
 {
  int fu = getf(Edge[i].u), fv = getf(Edge[i].v);
  if (fu == fv) continue;
  tr[Edge[i].u].push_back(Edge[i].v);
  tr[Edge[i].v].push_back(Edge[i].u);
 }
 return 0;
}