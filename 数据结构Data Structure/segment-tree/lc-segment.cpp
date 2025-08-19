#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pdi = pair<double, int>;
constexpr int N = 4e4 + 5, M1 = 39989, M2 = 1e9;
constexpr double eps = 1e-9;
int comp(double a, double b)
{
 if (a - b > eps) return 1;
 if (b - a > eps) return -1;
 return 0;
}
struct LiChaoT
{
 int cnt, t[N << 2];
 struct line
 {
  double k, b;
  double operator()(int x) { return k * x + b; }
 } seg[N << 2];
 void add(int x1, int y1, int x2, int y2)
 {
  double k, b;
  if (x2 == x1) k = 0, b = max(y1, y2);
  else k = 1.0 * (y2 - y1) / (x2 - x1), b = y1 - x1 * k;
  seg[++cnt] = {k, b};
 }
 void update(int rt, int L, int R, int x)
 {
  int &v = t[rt];
  int mid = (L + R) / 2;
  if (comp(seg[v](mid), seg[x](mid)) < 0) swap(v, x);
  if (comp(seg[v](L), seg[x](L)) < 0) update(rt << 1, L, mid, x);
  if (comp(seg[v](R), seg[x](R)) < 0) update(rt << 1 | 1, mid + 1, R, x);
 }
 void insert(int rt, int L, int R, int l, int r, int x)
 {
  if (l <= L && R <= r) return update(rt, L, R, x);
  int mid = (L + R) / 2;
  if (l <= mid) insert(rt << 1, L, mid, l, r, x);
  if (r > mid) insert(rt << 1 | 1, mid + 1, R, l, r, x);
 }
 pdi mx(pdi a, pdi b)
 {
  int c = comp(a.first, b.first);
  if (c > 0) return a;
  if (c < 0) return b;
  return a.second < b.second ? a : b;
 }
 pdi query(int rt, int L, int R, int x)
 {
  if (x < L || x > R) return {0, 0};
  pdi ret = {seg[t[rt]](x), t[rt]};
  if (L == R) return ret;
  int mid = (L + R) / 2;
  return mx(ret, mx(query(rt << 1, L, mid, x), query(rt << 1 | 1, mid + 1, R, x)));
 }
} t;
int main()
{
 cin.tie(nullptr), cout.tie(nullptr);
 ios::sync_with_stdio(0);
 int n, last = 0;
 cin >> n;
 for (int i = 1; i <= n; i++)
 {
  int op, k, x, y, xx, yy;
  cin >> op;
  if (op == 0)
  {
   cin >> k;
   k = (k + last - 1) % M1 + 1;
   cout << (last = t.query(1, 0, 40000, k).second) << '\n';
  }
  else
  {
   cin >> x >> y >> xx >> yy;
   x = (x + last - 1) % M1 + 1, xx = (xx + last - 1) % M1 + 1;
   y = (y + last - 1) % M2 + 1, yy = (yy + last - 1) % M2 + 1;
   t.add(x, y, xx, yy), t.insert(1, 0, 40000, min(x, xx), max(x, xx), t.cnt);
  }
 }
 return 0;
}