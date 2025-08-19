#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
int n, m, a[1010000], st[1010000][200];
int main()
{
 cin >> n >> m;
 for (int i = 1; i <= n; i++) scanf("%d", a + i), st[i][i] = a[i];
 for (int j = 1; 1 + (1 << j) <= n; j++)
  for (int i = 1; i + (1 << j) - 1 <= n; i++) st[i][j] = max(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
 while (m--)
 {
  int l, r, ans;
  scanf("%d%d", &l, &r);
  int t = log2(r - l + 1);
  ans = max(st[l][t], st[r - (1 << t) + 1][t]);
  printf("%d\n", ans);
 }
 return 0;
}