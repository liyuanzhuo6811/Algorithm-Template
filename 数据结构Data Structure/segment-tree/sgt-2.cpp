#include <cstdio>
#include <iostream>
#define int long long
using namespace std;
int n, m, mod, a[101000];
struct node
{
 int l, r, sum;
 int add, mul;
} t[401000];
void build(int p, int l, int r)
{
 t[p].l = l, t[p].r = r;
 t[p].mul = 1, t[p].add = 0;
 if (l == r)
 {
  t[p].sum = a[l];
  return;
 }
 int mid = (l + r) / 2;
 build(p * 2, l, mid);
 build(p * 2 + 1, mid + 1, r);
 t[p].sum = t[p * 2].sum + t[p * 2 + 1].sum;
}
void push_down(int p)
{
 if (t[p].mul != 1)
 {
  t[p * 2].mul *= t[p].mul, t[p * 2].mul %= mod;
  t[p * 2 + 1].mul *= t[p].mul, t[p * 2 + 1].mul %= mod;
  t[p * 2].sum *= t[p].mul, t[p * 2].sum %= mod;
  t[p * 2 + 1].sum *= t[p].mul, t[p * 2 + 1].sum %= mod;
  t[p * 2].add *= t[p].mul, t[p * 2].add %= mod;
  t[p * 2 + 1].add *= t[p].mul, t[p * 2 + 1].add %= mod;
  t[p].mul = 1;
 }
 if (t[p].add != 0)
 {
  t[p * 2].add += t[p].add, t[p * 2].add %= mod;
  t[p * 2 + 1].add += t[p].add, t[p * 2 + 1].add %= mod;
  t[p * 2].sum += t[p].add * (t[p * 2].r - t[p * 2].l + 1), t[p * 2].sum %= mod;
  t[p * 2 + 1].sum += t[p].add * (t[p * 2 + 1].r - t[p * 2 + 1].l + 1), t[p * 2 + 1].sum %= mod;
  t[p].add = 0;
 }
}
void mulnum(int p, int dat, int l, int r)
{
 if (l <= t[p].l && r >= t[p].r)
 {
  t[p].mul *= dat, t[p].mul %= mod;
  t[p].sum *= dat, t[p].sum %= mod;
  t[p].add *= dat, t[p].add %= mod;
  return;
 }
 push_down(p);
 int mid = (t[p].l + t[p].r) / 2;
 if (l <= mid) mulnum(p * 2, dat, l, r);
 if (r > mid) mulnum(p * 2 + 1, dat, l, r);
 t[p].sum = t[p * 2].sum + t[p * 2 + 1].sum;
}
void addnum(int p, int dat, int l, int r)
{
 if (l <= t[p].l && r >= t[p].r)
 {
  t[p].add += dat, t[p].add %= mod;
  t[p].sum += dat * (t[p].r - t[p].l + 1), t[p].sum %= mod;
  return;
 }
 push_down(p);
 int mid = (t[p].l + t[p].r) / 2;
 if (l <= mid) addnum(p * 2, dat, l, r);
 if (r > mid) addnum(p * 2 + 1, dat, l, r);
 t[p].sum = t[p * 2].sum + t[p * 2 + 1].sum;
}
int query(int p, int l, int r)
{
 if (l <= t[p].l && r >= t[p].r) return t[p].sum % mod;
 push_down(p);
 int mid = (t[p].l + t[p].r) / 2, val = 0;
 if (l <= mid) val += query(p * 2, l, r);
 if (r > mid) val += query(p * 2 + 1, l, r);
 return val % mod;
}
signed main()
{
 cin >> n >> m >> mod;
 for (int i = 1; i <= n; i++) cin >> a[i];
 build(1, 1, n);
 while (m--)
 {
  int op, x, y, k;
  cin >> op >> x >> y;
  if (op == 1)
  {
   cin >> k;
   mulnum(1, k, x, y);
  }
  else if (op == 2)
  {
   cin >> k;
   addnum(1, k, x, y);
  }
  else cout << query(1, x, y) << endl;
 }
 return 0;
}