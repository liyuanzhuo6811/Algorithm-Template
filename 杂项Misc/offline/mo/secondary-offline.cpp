#include <bits/stdc++.h>
using namespace std;
using ll = long long;
inline int rd()
{
 int x = 0, f = 1;
 char c = getchar();
 while (c < '0' || c > '9') f ^= (c == '-'), c = getchar();
 while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
 return f ? x : -x;
}
inline void wr(ll x)
{
 if (x < 0) putchar('-'), x = -x;
 if (x > 9) wr(x / 10);
 putchar(x % 10 + '0');
}
const int N = 1e5 + 5;
int n, m, a[N], b[N], V, tot;
int st[N], ed[N], pos[N], B;
struct que
{
 int l, r, id;
 inline bool operator<(const que &b) const { return (l / tot == b.l / tot) ? r < b.r : l < b.l; }
} q[N];
ll ans[N];
struct ask
{
 int id, op, l, r;
 ask() { id = op = l = r = 0; }
 ask(int _id, int _op, int _l, int _r) { id = _id, op = _op, l = _l, r = _r; }
};
ll tr[N];
inline void add(int x, int v)
{
 for (; x <= n; x += x & -x) tr[x] += (ll)v;
}
inline ll qry(int x)
{
 ll res = 0;
 for (; x; x -= x & -x) res += tr[x];
 return res;
}
int le[N], ri[N];
ll sl[N], sr[N];
vector<ask> v1[N], v2[N];
inline void addl(int pos, int op, int l, int r, int id) { v1[pos].push_back(ask(id, op, l, r)); }
inline void addr(int pos, int op, int l, int r, int id) { v2[pos].push_back(ask(id, op, l, r)); }
ll val[N], tag[N];
inline void updl(int x)
{
 if (tag[pos[x]])
  for (int i = st[pos[x]]; i <= ed[pos[x]]; i++) val[i] += tag[pos[x]];
 tag[pos[x]] = 0;
 for (int i = st[pos[x]]; i <= x; i++) val[i]++;
 for (int i = 1; i < pos[x]; i++) tag[i]++;
}
inline void updr(int x)
{
 if (tag[pos[x]])
  for (int i = st[pos[x]]; i <= ed[pos[x]]; i++) val[i] += tag[pos[x]];
 tag[pos[x]] = 0;
 for (int i = x; i <= ed[pos[x]]; i++) val[i]++;
 for (int i = pos[x] + 1; i <= B; i++) tag[i]++;
}
signed main()
{
 n = rd(), m = rd(), tot = 355, sl[0] = sr[n + 1] = 0;
 for (int i = 1; i <= n; i++) b[i] = a[i] = rd();
 sort(b + 1, b + 1 + n);
 V = unique(b + 1, b + 1 + n) - (b + 1);
 for (int i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + 1 + V, a[i]) - b;
 for (int i = 1; i <= n; i++) le[i] += (i - 1 - qry(a[i])), add(a[i], 1), sl[i] = sl[i - 1] + le[i];
 for (int i = 0; i <= n; i++) tr[i] = 0;
 for (int i = n; i >= 1; i--) ri[i] += qry(a[i] - 1), add(a[i], 1), sr[i] = sr[i + 1] + ri[i];
 for (int i = 1; i <= m; i++) q[i].l = rd(), q[i].r = rd(), q[i].id = i;
 sort(q + 1, q + 1 + m);
 int l = 1, r = 0;
 for (int i = 1; i <= m; i++)
 {
  if (r < q[i].r) ans[q[i].id] += sl[q[i].r] - sl[r], addl(l, -1, r + 1, q[i].r, q[i].id), r = q[i].r;
  if (r > q[i].r) ans[q[i].id] -= sl[r] - sl[q[i].r], addl(l, 1, q[i].r + 1, r, q[i].id), r = q[i].r;
  if (l < q[i].l) ans[q[i].id] -= sr[l] - sr[q[i].l], addr(r, 1, l, q[i].l - 1, q[i].id), l = q[i].l;
  if (l > q[i].l) ans[q[i].id] += sr[q[i].l] - sr[l], addr(r, -1, q[i].l, l - 1, q[i].id), l = q[i].l;
 }
 B = sqrt(V);
 for (int i = 1; i <= B; i++) st[i] = (i - 1) * B + 1, ed[i] = i * B;
 if (ed[B] < V) ed[B] = V;
 for (int i = 1; i <= B; i++)
  for (int j = st[i]; j <= ed[i]; j++) pos[j] = i;
 for (int i = 1; i <= n; i++)
 {
  for (ask now : v1[i])
   for (int j = now.l; j <= now.r; j++) ans[now.id] += (ll)now.op * (tag[pos[a[j] + 1]] + val[a[j] + 1]);
  updl(a[i]);
 }
 for (int i = 0; i <= n; i++) tag[i] = val[i] = 0;
 for (int i = n; i >= 1; i--)
 {
  for (ask now : v2[i])
   for (int j = now.l; j <= now.r; j++) ans[now.id] += (ll)now.op * (tag[pos[a[j] - 1]] + val[a[j] - 1]);
  updr(a[i]);
 }
 for (int i = 1; i <= m; i++) ans[q[i].id] += ans[q[i - 1].id];
 for (int i = 1; i <= m; i++) wr(ans[i]), puts("");
 return 0;
}