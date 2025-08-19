#include <bits/stdc++.h>
using namespace std;
bool millerRabin(int n)
{
 if (n < 3 || n % 2 == 0) return n == 2;
 if (n % 3 == 0) return n == 3;
 int u = n - 1, t = 0;
 while (u % 2 == 0) u /= 2, ++t;
 // test_time 为测试次数，建议设为不小于 8
 // 的整数以保证正确率，但也不宜过大，否则会影响效率
 for (int i = 0; i < test_time; ++i)
 {
  // 0, 1, n-1 可以直接通过测试, a 取值范围 [2, n-2]
  int a = rand() % (n - 3) + 2, v = quickPow(a, u, n);
  if (v == 1) continue;
  int s;
  for (s = 0; s < t; ++s)
  {
   if (v == n - 1) break; // 得到平凡平方根 n-1，通过此轮测试
   v = (long long)v * v % n;
  }
  // 如果找到了非平凡平方根，则会由于无法提前 break; 而运行到 s == t
  // 如果 Fermat 素性测试无法通过，则一直运行到 s == t 前 v 都不会等于 -1
  if (s == t) return 0;
 }
 return 1;
}
int main() { return 0; }