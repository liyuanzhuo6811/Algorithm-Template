#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 1e6 + 10;
typedef long long ll;
template <typename T> inline void gm(T *&bas, int siz, T *&op) { op = bas, bas += siz; }
#define pus(x) (sa[cur[a[x]]--] = x)
#define pul(x) (sa[cur[a[x]]++] = x)
#define inds(lms)                                                                                                      \
 for (int i = 1; i <= n; i++) sa[i] = -1;                                                                              \
 for (int i = 1; i <= n; i++) sum[i] = 0;                                                                              \
 for (int i = 1; i <= n; i++) sum[a[i]]++;                                                                             \
 for (int i = 1; i <= n; i++) sum[i] += sum[i - 1];                                                                    \
 for (int i = 1; i <= n; i++) cur[i] = sum[i];                                                                         \
 for (int i = m; i >= 1; i--) pus(lms[i]);                                                                             \
 for (int i = 1; i <= n; i++) cur[i] = sum[i - 1] + 1;                                                                 \
 for (int i = 1; i <= n; i++)                                                                                          \
  if (sa[i] > 1 && !tp[sa[i] - 1]) pul(sa[i] - 1);                                                                     \
 for (int i = 1; i <= n; i++) cur[i] = sum[i];                                                                         \
 for (int i = n; i >= 1; i--)                                                                                          \
  if (sa[i] > 1 && tp[sa[i] - 1]) pus(sa[i] - 1);
int sa[N], sum[N], cur[N], rk[N], A_bas[N << 4], *A_t;
inline void sais(int n, int *a)
{
 int *tp, *p;
 gm(A_t, n + 1, tp), gm(A_t, n + 2, p);
 tp[n] = 1;
 for (int i = n - 1; i >= 1; i--) tp[i] = (a[i] == a[i + 1]) ? tp[i + 1] : (a[i] < a[i + 1]);
 int m = 0;
 for (int i = 1; i <= n; i++) rk[i] = (tp[i] && !tp[i - 1]) ? (p[++m] = i, m) : -1;
 inds(p);
 int tot = 0, *a1;
 gm(A_t, m + 1, a1);
 p[m + 1] = n;
 for (int i = 1, x, y; i <= n; i++)
  if ((x = rk[sa[i]]) != -1)
  {
   if (tot == 0 || p[x + 1] - p[x] != p[y + 1] - p[y]) tot++;
   else
    for (int p1 = p[x], p2 = p[y]; p2 <= p[y + 1]; p1++, p2++)
     if ((a[p1] << 1 | tp[p1]) != (a[p2] << 1 | tp[p2]))
     {
      tot++;
      break;
     }
   a1[y = x] = tot;
  }
 if (tot == m)
  for (int i = 1; i <= m; i++) sa[a1[i]] = i;
 else sais(m, a1);
 for (int i = 1; i <= m; i++) a1[i] = p[sa[i]];
 inds(a1);
}
char mde[N];
int n;
int a[N];
int tr[300];
char buf[20];
int cnt;
int main()
{
 A_t = A_bas;
 scanf("%s", mde + 1);
 while (mde[n + 1] != '\0') n++;
 for (int i = 1; i <= n; i++) tr[mde[i]] = 1;
 for (int i = 1; i < 300; i++) tr[i] += tr[i - 1];
 for (int i = 1; i <= n; i++) a[i] = tr[mde[i]] + 1;
 a[++n] = 1;
 sais(n, a);
 for (int i = 2; i <= n; i++)
 {
  int tmp = sa[i];
  while (tmp) buf[++cnt] = tmp % 10 + 48, tmp /= 10;
  while (cnt) putchar(buf[cnt--]);
  putchar(' ');
 }
 return 0;
}