#include <bits/stdc++.h>
using namespace std;
const int N = 6e5 + 5, H = 28;
int n, m, a[N], s[N], rt[N], ch[N * 33][2], cnt[N * 33], tot;
void Insert(int u, int pre, int x)
{
 for (int i = H; i >= 0; i--)
 {
  cnt[u] = cnt[pre] + 1;
  int c = ((x & (1 << i)) ? 1 : 0);
  if (!ch[u][c]) ch[u][c] = ++tot;
  ch[u][c ^ 1] = ch[pre][c ^ 1];
  u = ch[u][c], pre = ch[pre][c];
 }
 cnt[u] = cnt[pre] + 1;
}
int query(int u, int v, int x)
{
 int res = 0;
 for (int i = H; i >= 0; i--)
 {
  int c = ((x & (1 << i)) ? 1 : 0);
  if (cnt[ch[u][!c]] - cnt[ch[v][!c]]) u = ch[u][!c], v = ch[v][!c], res += (1 << i);
  else u = ch[u][c], v = ch[v][c];
 }
 return res;
}
int main()
{
 cin.tie(nullptr)->sync_with_stdio(false);
 cout.tie(nullptr);
 cin >> n >> m;
 for (int i = 1, x; i <= n; i++) cin >> a[i], s[i] = s[i - 1] ^ a[i];
 for (int i = 1; i <= n; i++) rt[i] = ++tot, Insert(rt[i], rt[i - 1], s[i]);
 char op;
 for (int l, r, val; m; m--)
 {
  cin >> op;
  if (op == 'A')
  {
   n++, cin >> a[n];
   s[n] = s[n - 1] ^ a[n], rt[n] = ++tot;
   Insert(rt[n], rt[n - 1], s[n]);
  }
  if (op == 'Q')
  {
   cin >> l >> r >> val;
   l--, r--;
   if (!l) cout << max(s[n] ^ val, query(rt[r], rt[0], s[n] ^ val)) << '\n';
   else cout << query(rt[r], rt[l - 1], s[n] ^ val) << '\n';
  }
 }
 return 0;
}