// {"name":"outline_dp","intro":"维护轮廓线"}
#include <bits/stdc++.h>
using namespace std;
const int N = 26, mod = 1e9 + 7;
int n, m, E[N];
char s[N][N];
size_t dp[2][(1 << 24) + 5];
int main()
{
 ios_base::sync_with_stdio(false);
 cin.tie(nullptr);
 cout.tie(nullptr);
 cin >> n >> m;
 for (int i = 1; i <= n; ++i)
 {
  cin >> s[i];
  for (int j = 0; j < m; ++j)
   if (s[i][j] == '#') E[i] |= (1 << j);
 }
 int cur = 1, pre = 0;
 for (int S = 0; S < (1 << m); ++S)
  if ((S & E[1]) == 0 && (S & (S << 1)) == 0) dp[cur][S] = 1;
 for (int i = 2; i <= n; ++i)
 {
  swap(cur, pre), memset(dp[cur], 0, sizeof(dp[cur]));
  for (int j = 0; j < m; ++j)
   for (int S = 0; S < (1 << m); ++S)
    if (S & (1 << j)) (dp[pre][S] += dp[pre][S ^ (1 << j)]) %= mod;
  for (int S = 0; S < (1 << m); ++S)
   if ((S & E[i]) == 0 && (S & (S << 1)) == 0)
   {
    int T = (S | (S << 1) | (S >> 1)) & ((1 << m) - 1);
    dp[cur][S] = dp[pre][T ^ ((1 << m) - 1)];
   }
 }
 size_t ans = 0;
 for (int S = 0; S < (1 << m); ++S) (ans += dp[cur][S]) %= mod;
 cout << ans << endl;
 return 0;
}