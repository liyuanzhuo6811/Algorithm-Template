#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
vector<int> pf(string s)
{
 int n = (int)s.length();
 vector<int> pi(n);
 for (int i = 1; i < n; i++)
 {
  int j = pi[i - 1];
  while (j && s[j] != s[i]) j = pi[j - 1];
  if (s[i] == s[j]) ++j;
  pi[i] = j;
 }
 return pi;
}
int main() { return 0; }