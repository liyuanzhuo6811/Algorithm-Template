#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n, q, m, h[N], s[N], cnt;
vector<int> g[N], vt[N];
int fa[N], dep[N], siz[N], hson[N], dfn[N], top[N], idx;
void hld1(int u, int fath) { ... }
void hld2(int u, int fath) { ... }
int lca(int u, int v) { ... } // 重链剖分相关内容见 oi-algorithms/graph/tree/hld.cpp
bool cmp(int a, int b) { return dfn[a] < dfn[b]; }
inline void buildVtree()
{
 sort(h + 1, h + 1 + m, cmp);
 s[cnt = 1] = 1;
 for (int i = 1; i <= m; i++) s[++cnt] = h[i], s[++cnt] = lca(h[i], h[i + 1]);
 s[++cnt] = h[m];
 sort(s + 1, s + 1 + cnt, cmp);
 cnt = unique(s + 1, s + 1 + cnt) - s - 1;
 for (int i = 1; i <= cnt; i++) vt[lca(s[i], s[i + 1])].push_back(s[i + 1]);
}
int main() { return 0; }