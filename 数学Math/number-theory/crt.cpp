#include <iostream>
using LL = long long;
LL ex_gcd(LL a, LL b, LL &x, LL &y)
{
 if (!b) return x = 1, y = 0, a;
 LL g = ex_gcd(b, a % b, x, y), t = x;
 x = y, y = t - (a / b) * y;
 return g;
}
LL CRT(int k, LL *a, LL *r)
{
 LL n = 1, ans = 0;
 for (int i = 1; i <= k; i++) n = n * r[i];
 for (int i = 1; i <= k; i++)
 {
  LL m = n / r[i], b, y;
  ex_gcd(m, r[i], b, y); // b * m mod r[i] = 1
  ans = (ans + a[i] * m * b % n) % n;
 }
 return (ans % n + n) % n;
}
int main() { return 0; }