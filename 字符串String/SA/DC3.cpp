#include <cstring>
#include <iostream>
#define f(x) (x / 3) + (x % 3 == 1 ? 0 : cd)          // f(x) 表示原串中后缀 x 在新串中的位置
#define g(x) (x >= cd ? (x - cd) * 3 + 2 : x * 3 + 1) // g(x) 表示新串后缀 x  在原串中的位置
using namespace std;
const int N = 1e6 + 5;
string s;
int n, sa[N * 3 + 100], rk[N * 3 + 100], buc[N], x[N], y[N], height[N];
void sort(int *rk, int *a, int *b, int n, int Sigma) // rk 表示待排序串, a 表示指标集, b 表示排序后的指标顺序
{
 for (int i = 0; i <= Sigma; i++) buc[i] = 0;
 for (int i = 0; i < n; i++) buc[rk[a[i]]]++;
 for (int i = 1; i <= Sigma; i++) buc[i] += buc[i - 1];
 for (int i = n - 1; i >= 0; i--) b[--buc[rk[a[i]]]] = a[i];
}
bool cmp3(int *r, int x, int y) { return r[x] == r[y] && r[x + 1] == r[y + 1] && r[x + 2] == r[y + 2]; }
bool cmps(int *r, int x, int y)
{
 if (r[x] != r[y]) return r[x] < r[y];
 if (x % 3 == 1) return buc[x + 1] < buc[y + 1];
 return !cmps(r, y + 1, x + 1);
}
void DC3(int *rk, int *sa, int n, int Sigma)
{
 bool h = (n % 3 == 1);
 if (h) rk[n++] = 0;
 int *nrk = rk + n + 2, *nsa = sa + n, cb = 0, p; // nrk, nsa 分别表示新的 rk 和 sa, cb 表示 B 类后缀的数量
 for (int i = 0; i < n; i++)
  if (i % 3) x[cb++] = i;
 rk[n] = rk[n + 1] = 0;
 sort(rk + 2, x, y, cb, Sigma), sort(rk + 1, y, x, cb, Sigma), sort(rk, x, y, cb, Sigma); // 指标顺序存在了 y 中
 int ca = 0, cd = (n + 1) / 3; // ca 表示 A 类后缀的数量，cd 表示 i % 3 = 1 的后缀的数量
 nrk[f(y[0])] = p = 1;
 for (int i = 1; i < cb; i++)
 {
  if (!cmp3(rk, y[i], y[i - 1])) p++;
  nrk[f(y[i])] = p;
 }
 if (p < cb) DC3(nrk, nsa, cb, p); // 递归求解 B 类后缀
 else
  for (int i = 0; i < cb; i++)
   if (nrk[i]) nsa[nrk[i] - 1] = i;
 for (int i = 0; i < cb; i++)
  if (nsa[i] < cd) y[ca++] = 3 * nsa[i];
 sort(rk, y, x, ca, Sigma);
 for (int i = 0; i < cb; i++) buc[y[i] = g(nsa[i])] = i; // 利用 buc 存 B 类后缀的排名
 buc[n] = -1, p = 0;
 int i = 0, j = h;
 while (i < ca && j < cb)
 {
  if (cmps(rk, y[j], x[i])) sa[p++] = y[j++];
  else sa[p++] = x[i++];
 }
 while (i < ca) sa[p++] = x[i++];
 while (j < cb) sa[p++] = y[j++];
}
int main()
{
 cin.tie(nullptr)->sync_with_stdio(false);
 cout.tie(nullptr);
 cin >> s;
 n = s.length();
 for (int i = 0; i < n; i++) rk[i] = s[i] - '0' + 1;
 DC3(rk, sa, n, 75);
 for (int i = 0; i < n; i++) cout << sa[i] + 1 << ' ';
 cout << '\n';
 for (int i = 0; i < n; i++) rk[sa[i]] = i;
 for (int i = 0, k = 0; i < n; i++)
 {
  if (!rk[i]) continue;
  if (k) --k;
  while (s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
  height[rk[i]] = k;
 }
 for (int i = 1; i < n; i++) cout << height[i] << ' ';
 return cout << '\n', 0;
}