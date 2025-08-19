#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
double map[111][111];
double ans[111];
double eps = 1e-7;
int main()
{
 int n;
 cin >> n;
 for (int i = 1; i <= n; i++)
  for (int j = 1; j <= n + 1; j++) scanf("%lf", &map[i][j]);
 for (int i = 1; i <= n; i++)
 {
  int r = i;
  for (int j = i + 1; j <= n; j++)
   if (fabs(map[r][i]) < fabs(map[j][i])) r = j; // find_the_biggest_number_of_the_first_column（at present)
  if (fabs(map[r][i]) < eps)
  {
   printf("No Solution");
   return 0;
  }
  if (i != r) swap(map[i], map[r]); // 对换一行或一列,属于找最大当前系数的其中一步。（这样就可以只处理当前行的系数啦！）
  double div = map[i][i];
  for (int j = i; j <= n + 1; j++) map[i][j] /= div;
  for (int j = i + 1; j <= n; j++)
  {
   div = map[j][i];
   for (int k = i; k <= n + 1; k++) map[j][k] -= map[i][k] * div;
  }
 }
 ans[n] = map[n][n + 1];
 for (int i = n - 1; i >= 1; i--)
 {
  ans[i] = map[i][n + 1];
  for (int j = i + 1; j <= n; j++) ans[i] -= (map[i][j] * ans[j]);
 } // 回带操作
 for (int i = 1; i <= n; i++) printf("%.2lf\n", ans[i]);
 return 0;
}