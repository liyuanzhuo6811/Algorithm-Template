#include <bitset>
#include <iostream>
#include <vector>
using std::bitset;
using std::vector;
using ll = long long;
const int N = 1e7 + 5;
bitset<N> not_prime;
vector<int> pr;
int mu[N];
inline void sieve(int n)
{
 mu[1] = 1;
 for (int i = 2; i <= n; i++)
 {
  if (!not_prime[i]) mu[i] = -1, pr.push_back(i);
  for (int x : pr)
  {
   if (i * x > n) break;
   not_prime[i * x] = true;
   if (i % x == 0) break;
   mu[i * x] = -mu[i];
  }
 }
}
int main() { return 0; }