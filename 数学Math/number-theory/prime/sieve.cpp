#include <bitset>
#include <iostream>
#include <vector>
using std::bitset;
using std::vector;
const int N = 1e7 + 5;
bitset<N> not_prime;
vector<int> sieve(int n)
{
 vector<int> prime;
 for (int i = 2; i <= n; i++)
 {
  if (!not_prime[i]) prime.emplace_back(i);
  for (int x : prime)
  {
   if (x * i > n) break;
   not_prime[x * i] = true;
   if (i % x == 0) break;
  }
 }
 return prime;
}
int main() { return 0; }