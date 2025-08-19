#include <iostream>
using ll = long long;
ll get_sum(int l, int r) { return r - l + 1; }
ll calc(int n)
{
 ll res = 0;
 for (int l = 1, r = 0; l <= n; l = r + 1)
 {
  r = n / (n / l);
  res += get_sum(l, r);
 }
 return res;
}
int main() { return 0; }