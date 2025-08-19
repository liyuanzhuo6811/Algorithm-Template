#include <iostream>
using namespace std;
const int N = 500005;
int n, m, a[N], s[N], t[N];
inline int lowbit(int s) { return s & -s; }
inline void add(int x, int k)
{
 for (; x <= n; x += lowbit(x)) t[x] += k;
}
inline int query(int x)
{
 int res = 0;
 for (; x; x -= lowbit(x)) res += t[x];
 return res;
}
int main()
{
 ios::sync_with_stdio(false);
 cin.tie(0);
 cout.tie(0);
 cin >> n >> m;
 for (int i = 1; i <= n; i++) cin >> a[i];
 while (m--)
 {
  int op, x, y, k;
  cin >> op >> x;
  if (op == 1)
  {
   cin >> y >> k;
   add(x, k);
   add(y + 1, -k);
  }
  else cout << a[x] + query(x) << "\n";
 }
 return 0;
}