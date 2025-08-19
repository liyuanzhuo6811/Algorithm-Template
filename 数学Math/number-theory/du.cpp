#include <cstdio>
#include <iostream>
#include <map>
#define int long long
using namespace std;
const int N = 2000005;
int p[N], mu[N], sum[N], cnt;
bool flg[N];
map<int, int> mp;
void init(int n)
{
 mu[1] = 1ll;
 for (int i = 2; i <= n; i++)
 {
  if (!flg[i]) p[++cnt] = i, mu[i] = -1;
  for (int j = 1; j <= cnt && i * p[j] <= n; j++)
  {
   flg[i * p[j]] = true;
   if (i % p[j] == 0)
   {
    mu[i * p[j]] = 0;
    break;
   }
   mu[i * p[j]] = -mu[i];
  }
 }
 for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + mu[i];
}
int sum_mu(int n)
{
 if (n < N) return sum[n];
 if (mp.find(n) != mp.end()) return mp[n];
 int res = 1ll;
 for (int i = 2, j; i <= n; i = j + 1)
 {
  j = n / (n / i);
  res -= sum_mu(n / i) * (j - i + 1);
 }
 return mp[n] = res;
}
int sum_phi(int n)
{
 int res = 0ll;
 for (int i = 1, j; i <= n; i = j + 1)
 {
  j = n / (n / i);
  res += (sum_mu(j) - sum_mu(i - 1)) * (n / i) * (n / i);
 }
 return (res - 1) / 2 + 1;
}
signed main()
{
 cin.tie(0)->sync_with_stdio(false);
 cout.tie(0);
 init(N - 1);
 int T, n;
 cin >> T;
 while (T--)
 {
  cin >> n;
  cout << sum_phi(n) << " " << sum_mu(n) << "\n";
 }
 return 0;
}