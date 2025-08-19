#include <cstring>
#include <iostream>
using namespace std;
const int N = 2.2e7 + 10;
inline bool chk(char c) { return c >= 'a' && c <= 'z'; }
int n, f[N];
char s[N], c;
int main()
{
 s[0] = '~';
 while (chk(c = getchar())) s[++n] = '|', s[++n] = c;
 s[++n] = '|';
 for (int i = 1, maxr = 0, mid = 0; i <= n; i++)
 {
  if (i < maxr) f[i] = min(f[2 * mid - i], maxr - i);
  for (int j = i + f[i] + 1; j <= n; j++)
  {
   if (s[j] == s[2 * i - j]) ++f[i];
   else break;
  }
  if (i + f[i] > maxr) maxr = i + f[i], mid = i;
 }
 int ans = 0;
 for (int i = 1; i <= n; i++)
  if (f[i] > ans) ans = f[i];
 cout << ans;
 return 0;
}