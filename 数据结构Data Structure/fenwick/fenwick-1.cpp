#include <iostream>
using namespace std;
const int N = 5e5 + 10;
int n, m, a[N];
struct BIT
{
 int tr[N];
 inline int lowbit(int x) { return x & -x; }
 inline void upd(int x, int c)
 {
  while (x <= n) tr[x] += c, x += lowbit(x);
 }
 inline int que(int x)
 {
  int res = 0;
  while (x) res += tr[x], x -= lowbit(x);
  return res;
 }
} tree;
int main()
{
 ios::sync_with_stdio(false);
 cin.tie(0);
 cout.tie(0);
 cin >> n >> m;
 for (int i = 1; i <= n; i++) cin >> a[i], tree.upd(i, a[i]);
 while (m--)
 {
  int op, x, y;
  cin >> op >> x >> y;
  if (op == 1) tree.upd(x, y);
  else cout << tree.que(y) - tree.que(x - 1) << "\n";
 }
 return 0;
}